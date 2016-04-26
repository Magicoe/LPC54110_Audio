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

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/* Make TXCTL value based on the given xfer pointer */
__STATIC_INLINE uint16_t spim_get_xfercfg(const SPIM_XFER_T *xfer)
{
	uint16_t val;

	/* Setup flags required for transfer */
	val = (SPI_TXDATCTL_DEASSERT_ALL & ~SPI_TXDATCTL_DEASSERTNUM_SSEL(xfer->sselNum)) |
		SPI_TXDATCTL_FLEN(xfer->dataWidth - 1) | (xfer->option >> 15);

	/* See if we need to ignore the recevied data */
	if (!xfer->rxCount || !xfer->rxData) {
		val |= SPI_TXDATCTL_RXIGNORE;
	}
	return val;
}

/* Do a single data read and/or write based on the given status */
static void spim_do_txrx(LPC_SPI_T *pSPI, uint32_t stat, SPIM_XFER_T *xfer)
{
	int len = MAX(xfer->rxCount, xfer->txCount);

	/* See if we have a data to read */
	if (stat & SPI_FIFOSTAT_RXNOTEMPTY) {
		uint16_t data = Chip_SPI_ReadRXData(pSPI);
		if (xfer->rxIndex < xfer->rxCount) {
			if (xfer->dataWidth > 8) {
				((uint16_t *) xfer->rxData)[xfer->rxIndex] = data;
			} else {
				((uint8_t *) xfer->rxData)[xfer->rxIndex] = (uint8_t) data;
			}
		}
		xfer->rxIndex ++;
	}

	/* Write data if required */
	if (xfer->txIndex < len && (stat & SPI_FIFOSTAT_TXNOTFULL)) {
		uint16_t data;
		if (xfer->txIndex < xfer->txCount) {
			if (xfer->dataWidth > 8) {
				data = ((uint16_t *) xfer->txData)[xfer->txIndex];
			} else {
				data = ((uint8_t *) xfer->txData)[xfer->txIndex];
			}
		} else {
			data = (uint16_t) (xfer->option & 0xFFFF);
		}

		if (xfer->txIndex + 1 == len) {
			Chip_SPI_SetTXCTRLData(pSPI, spim_get_xfercfg(xfer) | SPI_TXCTL_EOT, data);
		} else {
			Chip_SPI_WriteTXData(pSPI, data);
		}
		xfer->txIndex ++;
	}
}
/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set SPI master bit rate */
uint32_t Chip_SPIM_SetClockRate(LPC_SPI_T *pSPI, uint32_t rate)
{
	uint32_t div;
	uint32_t clk = Chip_Clock_GetFLEXCOMMClockRate(Chip_FLEXCOMM_GetIndex(pSPI));

	/* Check if we have a valid rate */
	LPC_ASSERT(rate, __FILE__, __LINE__);

	/* Check if CLK is a sane value */
	LPC_ASSERT(clk, __FILE__, __LINE__);

	/* Compute divider */
	div = clk / rate;

	/* Limit values */
	if (div == 0) {
		div = 1;
	}
	else if (div > 0x10000) {
		div = 0x10000;
	}
	pSPI->DIV = div - 1;

	return Chip_SPIM_GetClockRate(pSPI);
}

/* Configure SPI Delay parameters */
void Chip_SPIM_DelayConfig(LPC_SPI_T *pSPI, SPIM_DELAY_CONFIG_T *pConfig)
{
	pSPI->DLY = (SPI_DLY_PRE_DELAY(pConfig->PreDelay) |
				 SPI_DLY_POST_DELAY(pConfig->PostDelay) |
				 SPI_DLY_FRAME_DELAY(pConfig->FrameDelay) |
				 SPI_DLY_TRANSFER_DELAY(pConfig->TransferDelay - 1));
}

/* SPI master transfer state change handler */
void Chip_SPIM_XferHandler(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	uint32_t val;

	/* Check if the bus is stalled for any reason! */
	if (Chip_SPI_GetStatus(pSPI) & SPI_STAT_STALLED) {
		xfer->state = SPI_XFER_STATE_STALL;
	}

	/* Check if there is a problem in TX or RX */
	val = Chip_SPI_GetFIFOStatus(pSPI);
	if ((xfer->txCount && (val & SPI_FIFOSTAT_TXERR)) || (xfer->rxCount && (val & SPI_FIFOSTAT_RXERR))) {
		xfer->state = SPI_XFER_STATE_ERROR;
	}

	if (xfer->state != SPI_XFER_STATE_BUSY) {
		if (xfer->eventCB) {
			xfer->eventCB(pSPI, SPIM_EVENT_ERROR, xfer);
		}
		Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
		return ;
	}

	while ((val = Chip_SPI_GetFIFOStatus(pSPI)) & (SPI_FIFOSTAT_TXNOTFULL | SPI_FIFOSTAT_RXNOTEMPTY)) {
		/* Check if the Xfer is already done */
		if (xfer->txIndex >= MAX(xfer->rxCount, xfer->txCount) && xfer->rxIndex >= xfer->rxCount) {
			xfer->state = SPI_XFER_STATE_DONE;
			Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
			if (xfer->eventCB) {
				xfer->eventCB(pSPI, SPIM_EVENT_DONE, xfer);
			}
			break ;
		}
		spim_do_txrx(pSPI, val, xfer);
	}

	Chip_SPI_ClearStatus(pSPI, SPI_STAT_SSD | SPI_STAT_SSA);
}

/* Start non-blocking SPI master transfer */
void Chip_SPIM_Xfer(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	xfer->txIndex = xfer->rxIndex = 0;
	xfer->state = SPI_XFER_STATE_BUSY;

	/* Enable the required TXCTL bits */
	Chip_SPI_SetTXCTRLRegBits(pSPI, spim_get_xfercfg(xfer));

	/* Enable Error interrupts */
	Chip_SPI_EnableInts(pSPI, SPI_INT_TXERR | SPI_INT_RXERR);

	/* Set to defalt trigger levels */
	Chip_SPI_SetFIFOTrigLevel(pSPI, 4, 0);

	/* Setup for DMA if being used */
	if (xfer->option & SPI_XFER_OPT_DMA) {
		Chip_SPI_SetFIFOCfg(pSPI, SPI_FIFOCFG_DMATX | SPI_FIFOCFG_DMARX | SPI_FIFOCFG_WAKETX | SPI_FIFOCFG_WAKERX);
		Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
	} else {
		Chip_SPI_ClearFIFOCfg(pSPI, SPI_FIFOCFG_DMATX | SPI_FIFOCFG_DMARX);
		Chip_SPI_EnableInts(pSPI, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
	}

	if (xfer->eventCB) {
		xfer->eventCB(pSPI, SPIM_EVENT_WAIT, xfer);
	}

	if (xfer->option & SPI_XFER_OPT_DMA) {
		Chip_SPIM_ForceEndOfTransfer(pSPI);
		if (xfer->state == SPI_XFER_STATE_BUSY) {
			xfer->state = SPI_XFER_STATE_DONE;
		}
	}
	Chip_SPI_DisableInts(pSPI, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
}

/* Perform blocking SPI master transfer */
void Chip_SPIM_XferBlocking(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer)
{
	/* Start trasnfer */
	Chip_SPIM_Xfer(pSPI, xfer);

	/* Wait for termination */
	while (xfer->state == SPI_XFER_STATE_BUSY) {
		Chip_SPIM_XferHandler(pSPI, xfer);
	}
}
