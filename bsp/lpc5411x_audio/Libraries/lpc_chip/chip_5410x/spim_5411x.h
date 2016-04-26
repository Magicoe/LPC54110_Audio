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

#ifndef __SPIM_5411X_H_
#define __SPIM_5411X_H_

#include "spi_common_5411x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SPI_MASTER_5411X CHIP: LPC5411X SPI master driver
 * @ingroup SPI_COMMON_5411X
 * @{
 */

/**
 * @brief	Get SPI master bit rate
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	The actual SPI clock bit rate
 */
__STATIC_INLINE uint32_t Chip_SPIM_GetClockRate(LPC_SPI_T *pSPI)
{
	return Chip_Clock_GetFLEXCOMMClockRate(Chip_FLEXCOMM_GetIndex(pSPI)) / (pSPI->DIV + 1);
}

/**
 * @brief	Set SPI master bit rate
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	rate	: Desired clock bit rate for the SPI interface
 * @return	The actual SPI clock bit rate
 * @note	This function will set the SPI clock divider to get closest
 * to the desired rate as possible.
 */
uint32_t Chip_SPIM_SetClockRate(LPC_SPI_T *pSPI, uint32_t rate);

/**
 * @brief SPI Delay Configure Struct
 */
typedef struct {
	uint8_t PreDelay;					/** Pre-delay value in SPI clocks, 0 - 15 */
	uint8_t PostDelay;					/** Post-delay value in SPI clocks, 0 - 15 */
	uint8_t FrameDelay;					/** Delay value between frames of a transfer in SPI clocks, 0 - 15 */
	uint8_t TransferDelay;				/** Delay value between transfers in SPI clocks, 1 - 16 */
} SPIM_DELAY_CONFIG_T;

/**
 * @brief	Config SPI Delay parameters
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	pConfig	: SPI Delay Configure Struct (See #SPIM_DELAY_CONFIG_T)
 * @return	Nothing
 */
void Chip_SPIM_DelayConfig(LPC_SPI_T *pSPI, SPIM_DELAY_CONFIG_T *pConfig);

/**
 * @brief	Forces an end of transfer for the current master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Use this function to perform an immediate end of trasnfer for the
 * current master operation. If the master is currently transferring data started
 * with the Chip_SPIM_Xfer function, this terminates the transfer after the
 * current byte completes and completes the transfer.
 */
__STATIC_INLINE void Chip_SPIM_ForceEndOfTransfer(LPC_SPI_T *pSPI)
{
	pSPI->STAT = SPI_STAT_EOT;
}

/**
 * @brief	Assert a SPI select
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	sselNum	: SPI select to assert, 0 - 3
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPIM_AssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum)
{
	pSPI->TXCTRL = pSPI->TXCTRL & (SPI_TXDATCTL_CTRLMASK & ~SPI_TXDATCTL_DEASSERTNUM_SSEL(sselNum));
}

/**
 * @brief	Deassert a SPI select
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	sselNum	: SPI select to deassert, 0 - 3
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPIM_DeAssertSSEL(LPC_SPI_T *pSPI, uint8_t sselNum)
{
	pSPI->TXCTRL = (pSPI->TXCTRL & SPI_TXDATCTL_CTRLMASK) | SPI_TXDATCTL_DEASSERTNUM_SSEL(sselNum);
}

/**
 * @brief	Enable loopback mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin.
 */
__STATIC_INLINE void Chip_SPIM_EnableLoopBack(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_LBM_EN);
}

/**
 * @brief	Disable loopback mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPIM_DisableLoopBack(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_LBM_EN);
}

struct SPIM_XFER;

/**
 * @brief	SPI master Xfer events
 */
typedef enum {
	SPIM_EVENT_WAIT,         /*!< SPI Xfer is waiting to be complete */
	SPIM_EVENT_ERROR,        /*!< SPI Xfer ended with an error! */
	SPIM_EVENT_DONE,         /*!< SPI Xfer completed without errors */
}SPIM_EVENT_T;

/**
 * @brief	States of SPI Master Xfer
 */
typedef enum {
	SPI_XFER_STATE_IDLE,    /*!< Transfer is idle and not started */
	SPI_XFER_STATE_BUSY,    /*!< Transfer has started and in progress */
	SPI_XFER_STATE_DONE,    /*!< Transfer is complete without errors */
	SPI_XFER_STATE_STALL,   /*!< SPI Bus stalled */
	SPI_XFER_STATE_ERROR,   /*!< SPI transfer terminated with errors */
} SPIM_XFER_STATE_T;

/**
 * Enable end of frame; after transmit of every data a frame dealy is inserted
 * [see @a FrameDelay in #SPIM_DELAY_CONFIG_T set using Chip_SPIM_DelayConfig()];
 * this flag has no effect if @a FrameDelay was set to 0.
 */
#define SPI_XFER_OPT_EOF            (1UL << 20)

/**
 * Enable end of transfer; Every data transfered will have SSEL asserted and deasserted
 */
#define SPI_XFER_OPT_EOT            (1UL << 19)

/**
 * DMA is used for this transfer [DMA needs to be setup by the application]
 */
#define SPI_XFER_OPT_DMA            (1UL << 31)

/**
 * @brief SPI Master transfer data context
 *
 * @note When structure member @a  dataWidth > 8; @a txData and @a rxData must be of type (uint16_t *)
 * otherwise it should be of type (uint8_t *)<br> Member @a options must be OR'd values from SPI_XFER_OPT_* (see #SPI_XFER_OPT_EOF)
 *
 */
typedef struct SPIM_XFER {
	/* User initialized members */
	int (*eventCB) (LPC_SPI_T *pSPI, SPIM_EVENT_T evt, struct SPIM_XFER *xfer); /** Pointer to SPI master transfer event callback functions */
	void *txData;              /*!< Pointer to buffer having transmit data */
	void *rxData;              /*!< Pointer to buffer where received data be stored */
	uint16_t txCount;          /*!< Number of data to be transmitted [Not in bytes] */
	uint16_t rxCount;          /*!< Number of data to be received [Not in bytes] */
	uint16_t dataWidth;        /*!< Width of the data [Valid values: 1 to 16] */
	uint16_t sselNum;          /*!< Slave select number to be asserted when transfering data [Valid values: 0 to 3] */
	uint32_t option;           /*!< Dummy data to be transfered when rxCount > txCount ORed with #SPI_XFER_OPT_EOF (if this functionality is required) */
	void *usrData;             /*!< User data associated with this Xfer structure */
	/* Internal members */
	uint16_t txIndex;          /*!< Index of the next item to be transfered [If this is same as txCount then tx is complete] */
	uint16_t rxIndex;          /*!< Index of memory to which next received data be stored */
	SPIM_XFER_STATE_T state;   /*!< State of the transfer */
} SPIM_XFER_T;

/**
 * @brief	SPI master transfer state change handler
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	See @ref SPIM_XFER_T for more information on this function. When using
 * this function, the SPI master interrupts should be enabled and setup in the SPI
 * interrupt handler to call this function when they fire. This function is meant
 * to be called from the interrupt handler.
 */
void Chip_SPIM_XferHandler(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @brief	Start non-blocking SPI master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	This function starts a non-blocking SPI master transfer with the
 * parameters setup in the passed @ref SPIM_XFER_T structure. Once the transfer is
 * started, the interrupt handler must call Chip_SPIM_XferHandler to keep the
 * transfer going and fed with data. This function should only be called when
 * the master is idle.<br>
 *
 * This function must be called with the options and sselNum fields correctly
 * setup. Initial data buffers and the callback pointer must also be setup. No
 * sanity checks are performed on the passed data.<br>
 *
 * Example call:<br>
 * SPIM_XFER_T mxfer;
 * mxfer.pCB = (&)masterCallbacks;
 * mxfer.sselNum = 2; // Use chip select 2
 * mxfer.options = SPI_TXCTL_FLEN(8); // 8 data bits, supports 1 - 16 bits
 * mxfer.options |= SPI_TXCTL_EOT | SPI_TXCTL_EOF; // Apply frame and transfer delays to master transfer
 * mxfer.options |= SPI_TXCTL_RXIGNORE; // Ignore RX data, will toss receive data regardless of pRXData8 or pRXData16 buffer
 * mxfer.pTXData8 = SendBuffer;
 * mxfer.txCount = 16; // Number of bytes to send before SPIMasterXferSend callback is called
 * mxfer.pRXData8 = RecvBuffer; // Will not receive data if pRXData8/pRXData16 is NULL or SPI_TXCTL_RXIGNORE option is set
 * mxfer.rxCount = 16; // Number of bytes to receive before SPIMasterXferRecv callback is called
 * Chip_SPIM_Xfer(LPC_SPI0, &mxfer); // Start transfer
 *
 * Note that the transfer, once started, needs to be constantly fed by the callbacks.
 * The txCount and rxCount field only indicate the buffer size before the callbacks are called.
 * To terminate the transfer, the SPIMasterXferSend callback must set the terminate field.
 */
void Chip_SPIM_Xfer(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @brief	Perform blocking SPI master transfer
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	xfer	: Pointer to a SPIM_XFER_T structure see notes below
 * @return	Nothing
 * @note	This function starts a blocking SPI master transfer with the
 * parameters setup in the passed @ref SPIM_XFER_T structure. Once the transfer is
 * started, the callbacks in Chip_SPIM_XferHandler may be called to keep the
 * transfer going and fed with data. SPI interrupts must be disabled prior to
 * calling this function. It is not recommended to use this function.<br>
 */
void Chip_SPIM_XferBlocking(LPC_SPI_T *pSPI, SPIM_XFER_T *xfer);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SPIM_5411X_H_ */
