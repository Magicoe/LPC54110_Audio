/*
 * @brief LPC5411X SPI master driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2015
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licenser disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Flag used to tell polling function (if used) that a deassert event
   happened */
static volatile bool deasserted;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Determine SSEL associated with the current data value */
static uint8_t Chip_SPIS_FindSSEL(LPC_SPI_T *pSPI)
{
	return "\0x00\x00\x01\x00\x02\x00\x00\x00\x03"[~Chip_SPI_ReadRXStat(pSPI) & 0xF];
}

__STATIC_INLINE uint16_t spis_get_data(const SPIS_XFER_T *xfer)
{
	if (!xfer->txData) {
		return 0;
	}

	if (xfer->dataWidth > 8) {
		return ((uint16_t *)xfer->txData)[MIN(xfer->txIndex, xfer->txCount)];
	}
	return (uint16_t) ((uint8_t *)xfer->txData)[MIN(xfer->txIndex, xfer->txCount)];
}

static void spis_do_txrx(LPC_SPI_T *pSPI, uint32_t stat, SPIS_XFER_T *xfer)
{
	if (stat & SPI_FIFOSTAT_TXNOTFULL) {
		Chip_SPI_WriteTXData(pSPI, spis_get_data(xfer));
		xfer->txIndex ++;
	}

	if (stat & SPI_FIFOSTAT_RXNOTEMPTY) {
		uint16_t data = Chip_SPI_ReadRXData(pSPI);
		if (xfer->rxIndex < xfer->rxCount) {
			if (xfer->dataWidth > 8) {
				((uint16_t *)xfer->rxData)[xfer->rxIndex] = data;
			} else {
				((uint8_t *)xfer->rxData)[xfer->rxIndex] = (uint8_t) data;
			}
			xfer->rxIndex ++;
		}
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/


/* SPI slave transfer state change handler */
void Chip_SPIS_XferHandler(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	uint32_t pend = Chip_SPI_GetPendingInts(pSPI);
	uint32_t val;


	/* Check for slave assert/deassert */
	if (pend & SPI_INT_SSAEN) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSA);
		xfer->sselNum = Chip_SPIS_FindSSEL(pSPI);

		/* SSEL assertion callback */
		if (xfer->eventCB) {
			xfer->eventCB(pSPI, SPIS_EVENT_SASSERT, xfer);
		}
		Chip_SPI_EnableInts(pSPI, SPI_INT_TXDYEN);
	} else if (pend & SPI_INT_SSDEN) {
		Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSD);

		/* SSEL de-assertion callback */
		if (xfer->eventCB)
			xfer->eventCB(pSPI, SPIS_EVENT_SDEASSERT, xfer);
		Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN);
		Chip_SPI_FlushFifos(pSPI);
	}

	while ((val = Chip_SPI_GetFIFOStatus(pSPI)) & (SPI_FIFOSTAT_TXNOTFULL | SPI_FIFOSTAT_RXNOTEMPTY)) {
		spis_do_txrx(pSPI, val, xfer);
		if ((val & SPI_FIFOSTAT_TXERR) && xfer->eventCB) {
			xfer->eventCB(pSPI, SPIS_EVENT_ERRORTX, xfer);
		} else if ((val & SPI_FIFOSTAT_TXERR) && xfer->eventCB) {
			xfer->eventCB(pSPI, SPIS_EVENT_ERRORRX, xfer);
		}

		/* Call threshold event */
		if (xfer->thresCount && xfer->rxIndex == xfer->thresCount && xfer->eventCB)
			xfer->eventCB(pSPI, SPIS_EVENT_THRESHOLD, xfer);

		if (xfer->rxIndex >= MAX(xfer->rxCount, xfer->txCount)) {
			xfer->eventCB(pSPI, SPIS_EVENT_DONE, xfer);
			if (xfer->txIndex >= xfer->txCount) {
				Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN);
			}
		}
	}
}

/* SPI slave transfer blocking function */
void Chip_SPIS_XferBlocking(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	/* Wait forever until deassertion event */
	deasserted = false;
	while (xfer->rxIndex < MAX(xfer->rxCount, xfer->txCount)) {
		Chip_SPIS_XferHandler(pSPI, xfer);
	}
}
