/*
 * @brief LPC5411X SPI slave driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2015
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
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

#ifndef __SPIS_5411X_H_
#define __SPIS_5411X_H_

#include "spi_common_5411x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SPI_SLAVE_5411X CHIP: LPC5411X SPI slave driver
 * @ingroup SPI_COMMON_5411X
 * @{
 */

/** @brief	Slave callback events */
typedef enum
{
	SPIS_EVENT_SASSERT,      /*!< Slave select line asserted */
	SPIS_EVENT_SDEASSERT,    /*!< Slave select line de-asserted */
	SPIS_EVENT_DONE,         /*!< Slave done with this transfer [More data can be provided] */
	SPIS_EVENT_ERRORTX,      /*!< TX Underflow error */
	SPIS_EVENT_ERRORRX,      /*!< RX Overflow error */
	SPIS_EVENT_THRESHOLD,    /*!< Slave transfer has reached its threshold */
} SPIS_EVENT_T;

/** Slave transfer data context */
typedef struct SPIS_XFER {
	int (*eventCB) (LPC_SPI_T *pSPI, SPIS_EVENT_T evt, struct SPIS_XFER *xfer); /*!< Pointer to SPI slave callback functions */
	void *txData;                   /*!< TX Data pointer */
	void *rxData;                   /*!< RX Data pointer */
	uint16_t rxCount;               /*!< Size of the pRXData buffer in items (not bytes), modified by driver */
	uint16_t txCount;               /*!< Number of items (not bytes) to send in pTXData buffer, modified by driver */
	uint16_t txIndex;               /*!< Total items (not bytes) received, modified by driver */
	uint16_t rxIndex;               /*!< Total items (not bytes) transmitted, modified by driver */
	uint16_t thresCount;            /*!< Number of data to receive to trigger #SPIS_EVENT_THRESHOLD event */
	uint16_t dataWidth;             /*!< Width of the data [Valid values: 1 to 16] */
	uint8_t sselNum;                /*!< Slave number assigned to this transfer, 0 - 3, modified by driver */
} SPIS_XFER_T;

/**
 * @brief	SPI slave transfer state change handler
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure see notes below
 * @return	Nothing
 * @note	See @ref SPIS_XFER_T for more information on this function. When using
 * this function, the SPI slave interrupts should be enabled and setup in the SPI
 * interrupt handler to call this function when they fire. This function is meant
 * to be called from the interrupt handler. The @ref SPIS_XFER_T data does not need
 * to be setup prior to the call and should be setup by the callbacks instead.<br>
 *
 * The callbacks are handled in the interrupt handler. If you are getting overflow
 * or underflow errors, you might need to lower the speed of the master clock or
 * extend the master's select assetion time.<br>
 */
void Chip_SPIS_XferHandler(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer);

/**
 * @brief	Pre-buffers slave transmit data
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure see notes below
 * @return	Nothing
 * @note Pre-buffering allows the slave to prime the transmit FIFO with data prior to
 * the master starting a transfer. If data is not pre-buffered, the initial slave
 * transmit data will always be 0x0 with a slave transmit underflow status.
 * Pre-buffering is best used when only a single slave select is used by an
 * application.
 */
__STATIC_INLINE void Chip_SPIS_PreBuffSlave(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer)
{
	Chip_SPIS_XferHandler(pSPI, xfer);
}

/**
 * @brief	SPI slave transfer blocking function
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIS_XFER_T structure
 * @return	Nothing
 * @note	This function performs a blocking transfer on the SPI slave interface.
 * It is not recommended to use this function. Once this function is called, it
 * will block forever until a slave transfer consisting of a slave SSEL assertion,
 * and de-assertion occur. The callbacks are still used for slave data buffer
 * management. SPI interrupts must be disabled prior to calling this function.
 */
void Chip_SPIS_XferBlocking(LPC_SPI_T *pSPI, SPIS_XFER_T *xfer);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SPIS_5411X_H_ */
