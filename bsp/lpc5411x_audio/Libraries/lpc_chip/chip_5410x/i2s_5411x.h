/*
 * @brief LPC5411x I2S driver
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

#ifndef __I2S_5411X_H_
#define __I2S_5411X_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief I2S register block structure
 */
typedef struct {					/*!< I2S Structure */
	__IO uint32_t RESERVED0A[768];
	__IO uint32_t CFG1;				/*!< Offset: 0xC00 Configuration register #1 */
	__IO uint32_t CFG2;				/*!< Offset: 0xC04 Configuration register #2 */
	__IO uint32_t STAT;				/*!< Offset: 0xC08 Status register */
	__I  uint32_t RESERVED00[4];    /*!< Offset: 0xC0C Reserved registers */
	__IO uint32_t DIV;				/*!< Offset: 0xC1C Clock divider, used by all channel pairs. */
	__I  uint32_t RESERVED0[120];	/*!< Offset: 0xC10 Reserved member */

	/** I2S FIFO Specific registers @endcond */
	__IO uint32_t FIFOCFG;			/*!< Offset: 0xE00 FIFO Configuration register */
	__IO uint32_t FIFOSTAT;			/*!< Offset: 0xE04 FIFO Status register */
	__IO uint32_t FIFOTRIG;			/*!< Offset: 0xE08 FIFO Trigger level register @cond */
	__I  uint32_t RESERVED1;		/*!< Offset: 0xE0C Reserved register @endcond */
	__IO uint32_t FIFOINTENSET;		/*!< Offset: 0xE10 FIFO Interrupt enable SET register */
	__IO uint32_t FIFOINTENCLR;		/*!< Offset: 0xE14 FIFO Interrupt enable CLEAR register */
	__IO uint32_t FIFOINTSTAT;		/*!< Offset: 0xE18 FIFO Interrupt Status register @cond */
	__I  uint32_t RESERVED2;		/*!< Offset: 0xE1C Reserved register @endcond */
	__O  uint32_t FIFOWR;			/*!< Offset: 0xE20 FIFO Data write register @cond */
	__I  uint32_t FIFOWR48H;		/*!< Offset: 0xE24 FIFO write data for upper data bits */
	__I  uint32_t RESERVED3[2];		/*!< Offset: 0xE28 Reserved register @endcond */
	__I  uint32_t FIFORD;			/*!< Offset: 0xE30 FIFO Data read register @cond */
	__I  uint32_t FIFORD48H;		/*!< Offset: 0xE34 FIFO read data for upper data bits */
	__I  uint32_t RESERVED4[2];		/*!< Offset: 0xE38 Reserved register @endcond */
	__I  uint32_t FIFORDNOPOP;		/*!< Offset: 0xE40 FIFO data read with no FIFO pop */
	__I  uint32_t FIFORD48HNOPOP;	/*!< Offset: 0xE44 FIFO data read for upper data bits with no FIFO pop */
	__I  uint32_t RESERVED5[108];	/*!< Offset: 0xE48 Reserved register */

	/** FLEXCOMM Interface registers @endcond */
	__IO uint32_t PSELID;			/*!< Offset: 0xFF8 Peripheral select/identification register */
	__I  uint32_t PID;				/*!< Offset: 0xFFC Module identification register */
} LPC_I2S_T;

/**
 * @brief I2S CFG1 register bits
 */
#define I2S_CFG1_MAINENABLE			(0x01 << 0)					/*!< I2S Main enable */
#define I2S_CFG1_DATAPAUSE			(0x01 << 1)					/*!< Data flow Pause */
#define I2S_CFG1_2NDCOUNT(p)		(((p) & 0x03) << 2)			/*!< additional I2S channel pair ct (read only) */
#define I2S_CFG1_MSTSLVCFG(p)		(((p) & 0x03) << 4)			/*!< Master / slave configuration selection */
#define I2S_CFG1_MODE(p)			(((p) & 0x03) << 6)			/*!< Selects basic I2S operating mode */
#define I2S_CFG1_RIGHTLOW			(0x01 << 8)					/*!< Right channel data is in the Low portion of FIFO data */
#define I2S_CFG1_LEFTJUST			(0x01 << 9)					/*!< Left Justify data */
#define I2S_CFG1_ONECHANNEL			(0x01 << 10)				/*!< Single channel mode */
#define I2S_CFG1_PDMDATA			(0x01 << 11)				/*!< PDM Data selection */
#define I2S_CFG1_SCK_POL			(0x01 << 12)				/*!< SCK polarity */
#define I2S_CFG1_WS_POL				(0x01 << 13)				/*!< WS polarity */
#define I2S_CFG1_DATALEN(p)			(((p) & 0x1f) << 16)		/*!< Data Length (minus 1 encoded) */

/**
 * @brief I2S CFG2 register bits
 */
#define I2S_CFG2_FRAMELEN(p)		(((p) & 0x1ff) << 0)		/*!< I2S Main enable */
#define I2S_CFG2_POSITION(p)		(((p) & 0x1FF) << 16)		/*!< Data flow Pause */

/**
 * @brief I2S status register bits
 */
#define I2S_STAT_BUSY				(0x01 << 0)					/*!< Busy status for the primary channel pair */
#define I2S_STAT_SLVFRMERR			(0x01 << 1)					/*!< Slave Frame Error flag */
#define I2S_STAT_LR					(0x01 << 2)					/*!< Left/Right indication */
#define I2S_STAT_PAUSED				(0x01 << 3)					/*!< Data Paused status flag */

/**
 * @brief I2S FIFO configuration bits
 */
#define I2S_FIFO_CFG_ENABLETX		(0x01 << 0)					/*!< Enable the transmit FIFO */
#define I2S_FIFO_CFG_ENABLERX		(0x01 << 1)					/*!< Enable the receive FIFO */
#define I2S_FIFO_CFG_TXI2SE0		(0x01 << 2)					/*!< Transmit I2S empty 0 */
#define I2S_FIFO_CFG_PACK48			(0x01 << 3)					/*!< Packing format for 48-bit data */
#define I2S_FIFO_CFG_SIZE(p)		(((p) & 0x03) << 4)			/*!< FIFO size (READ ONLY) */
#define I2S_FIFO_CFG_DMATX			(0x01 << 12)				/*!< DMA configuration for transmit */
#define I2S_FIFO_CFG_DMARX			(0x01 << 13)				/*!< DMA configuration for receive */
#define I2S_FIFO_CFG_WAKETX			(0x01 << 14)				/*!< Wake-up for transmit FIFO level */
#define I2S_FIFO_CFG_WAKERX			(0x01 << 15)				/*!< Wake-up for receive FIFO level */
#define I2S_FIFO_CFG_EMPTYTX		(0x01 << 16)				/*!< Empty command for the transmit FIFO */
#define I2S_FIFO_CFG_EMPTYRX		(0x01 << 17)				/*!< Empty command for the receive FIFO */
#define I2S_FIFO_CFG_POPDBG			(0x01 << 18)				/*!< Pop FIFO for debug reads */

/**
 * @brief I2S FIFO status bits
 */
#define I2S_FIFO_STAT_TXERR			(0x01 << 0)					/*!< TX FIFO error */
#define I2S_FIFO_STAT_RXERR			(0x01 << 1)					/*!< RX FIFO error */
#define I2S_FIFO_STAT_PERINT		(0x01 << 3)					/*!< Peripheral interrupt */
#define I2S_FIFO_STAT_TXEMPTY		(0x01 << 4)					/*!< Transmit FIFO empty */
#define I2S_FIFO_STAT_TXNOTFULL		(0x01 << 5)					/*!< Transmit FIFO not full */
#define I2S_FIFO_STAT_RXNOTEMPTY	(0x01 << 6)					/*!< Receive FIFO not empty */
#define I2S_FIFO_STAT_RXFULL		(0x01 << 7)					/*!< Receive FIFO full */
#define I2S_FIFO_STAT_TXLVL(p)		(((p) & 0x0f) << 8)			/*!< Transmit FIFO current level */
#define I2S_FIFO_STAT_RXLVL(p)		(((p) & 0x0f) << 16)		/*!< Receive FIFO current level */

/**
 * @brief I2S FIFO trigger settings bits
 */
#define I2S_FIFO_TRIG_TXLVLENA		(0x01 << 0)					/*!< Transmit FIFO level trigger enable */
#define I2S_FIFO_TRIG_RXLVLENA		(0x01 << 1)					/*!< Receive FIFO level trigger enable */
#define I2S_FIFO_TRIG_TXLVL(p)		(((p) & 0x0f) << 8)			/*!< Transmit FIFO level trigger point */
#define I2S_FIFO_TRIG_RXLVL(p)		(((p) & 0x0f) << 16)		/*!< Receive FIFO level trigger point */

/**
 * @brief I2S FIFO interrupt enable.
 * Used for interrupt status too.
 */
#define I2S_FIFO_INT_TXERR			(0x01 << 0)					/*!< Interrupt on TX error */
#define I2S_FIFO_INT_RXERR			(0x01 << 1)					/*!< Interrupt on RX error */
#define I2S_FIFO_INT_TXLVL			(0x01 << 2)					/*!< Interrupt on TX level */
#define I2S_FIFO_INT_RXLVL			(0x01 << 3)					/*!< Interrupt on RX level */

typedef enum {
	I2S_FIFO_ENABLE,
	I2S_FIFO_DISABLE,
	I2S_FIFO_DMA_ENABLE,
	I2S_FIFO_DMA_DISABLE,
	I2S_FIFO_CLEAR,
	I2S_FIFO_TXZ_ENABLE,
	I2S_FIFO_TXZ_DISABLE,
} I2S_FIFO_CMD_T;

typedef enum {
	I2S_TX,
	I2S_RX,
} I2S_DIR_T;

typedef enum {
	NORMAL_SLAVE,
	WS_SYNC_MASTER,
	EXT_SCLCK_MASTER,
	NORMAL_MASTER,
} I2S_MSTSLVCFG_T;

typedef enum {
	I2S_CLASSIC,
	DSP_WS_50,
	DSP_WS_SHORT,
	DSP_WS_LONG,
} I2S_MODE_T;

typedef struct {
	I2S_DIR_T			Direction;			/*!< Data direction: tx or rx */
	I2S_MSTSLVCFG_T		MSCfg;				/*!< Master / Slave configuration */
	I2S_MODE_T			Mode;				/*!< I2S mode */
	bool				RightLow;			/*!< right channel data in low portion of FIFO */
	bool				LeftJust;			/*!< left justify data in FIFO */
	bool				PDMData;			/*!<  data source is the D-Mic subsystem */
	bool				SCKPol;				/*!<  SCK polarity */
	bool				WSPol;				/*!<  WS polarity */
	uint32_t			Divider;			/*!< Flexcomm function clock divider */
	uint8_t				ChannelNumber;		/*!< Channel Number - 1 is mono, 2 is stereo */
	uint16_t			WordWidth;			/*!< Word Width */
	uint16_t			FrameWidth;			/*!< Frame Width */
	uint16_t			DataPos;			/*!< Data position in the frame */
	uint16_t			FIFOdepth;			/*!< FIFO depth (fifo config) */
} I2S_AUDIO_FORMAT_T;

/**
 * @brief	Initialize I2S driver
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	0 - on success; #ERR_FLEXCOMM_FUNCNOTSUPPORTED or #ERR_FLEXCOMM_NOTFREE on failure
 */
int Chip_I2S_Init(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt);

__STATIC_INLINE int Chip_I2S_TX_Init(LPC_I2S_T *pI2S)
{
	return Chip_FLEXCOMM_Init(pI2S, FLEXCOMM_PERIPH_I2S_TX);
}
__STATIC_INLINE int Chip_I2S_RX_Init(LPC_I2S_T *pI2S)
{
	return Chip_FLEXCOMM_Init(pI2S, FLEXCOMM_PERIPH_I2S_RX);
}

/**
 * @brief	Shutdown I2S driver
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 * @note	Reset all relative registers (DMA, transmit/receive control, interrupt) to default value
 */
__STATIC_INLINE void Chip_I2S_DeInit(LPC_I2S_T *pI2S)
{
	Chip_FLEXCOMM_DeInit(pI2S);
}

/**
 * @brief	Send a 32-bit data to TXFIFO for transmition
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @param	data	: Data to be transmited
 * @return	Nothing
 * @note	The function writes to TXFIFO without checking any condition.
 */
__STATIC_INLINE void Chip_I2S_Send(LPC_I2S_T *pI2S, uint32_t data)
{
	pI2S->FIFOWR = data;
}

/**
 * @brief	Get received data from RXFIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Data received in RXFIFO
 * @note	The function reads from RXFIFO without checking any condition.
 */
__STATIC_INLINE uint32_t Chip_I2S_Receive(LPC_I2S_T *pI2S)
{
	return pI2S->FIFORD;
}

/**
 * @brief	Start I2S port
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_I2S_Start(LPC_I2S_T *pI2S)
{
	pI2S->CFG1 |= I2S_CFG1_MAINENABLE;
}

/**
 * @brief	Stop I2S asynchronously
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 * @note	Pause, resets the transmit channel and FIFO asynchronously
 */
__STATIC_INLINE void Chip_I2S_Stop(LPC_I2S_T *pI2S)
{
	pI2S->CFG1 &= ~I2S_CFG1_MAINENABLE;
}

/**
 * @brief	Pause the I2S port
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_I2S_Pause(LPC_I2S_T *pI2S)
{
	pI2S->CFG1 |= I2S_CFG1_DATAPAUSE;
}

/**
 * @brief	Play (un-Pause) the I2S port
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_I2S_Play(LPC_I2S_T *pI2S)
{
	pI2S->CFG1 &= ~I2S_CFG1_DATAPAUSE;
}

/**
 * @brief	Get FIFO status
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Current FIFO status
 */
__STATIC_INLINE uint32_t Chip_I2S_GetFIFOStatus(LPC_I2S_T *pI2S)
{
	return (pI2S->FIFOSTAT);
}

/**
 * @brief	Clear FIFO status
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	mothing
 */
__STATIC_INLINE void Chip_I2S_ClrFIFOStatus(LPC_I2S_T *pI2S)
{
	pI2S->FIFOSTAT = 3;
}

/**
 * @brief	Get the current level of the Transmit FIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Current level of the Transmit FIFO
 */
__STATIC_INLINE uint8_t Chip_I2S_GetTxLevel(LPC_I2S_T *pI2S)
{
	return (pI2S->FIFOSTAT >> 8) & 0xF;
}

/**
 * @brief	Get the current level of the Receive FIFO
 * @param	pI2S	: The base of I2S peripheral on the chip
 * @return	Current level of the Receive FIFO
 */
__STATIC_INLINE uint8_t Chip_I2S_GetRxLevel(LPC_I2S_T *pI2S)
{
	return (pI2S->FIFOSTAT >> 16) & 0xF;
}

/**
 * @brief   Configure I2S Port
 * @param	pI2S	: The base I2S peripheral on the chip
 * @param	fmt		: Audio Format
 * @return	SUCCESS or ERROR
 */
Status Chip_I2S_Config(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt);

/**
 * @brief   Configure I2S FIFO
 * @param	pI2S	: The base I2S peripheral on the chip
 * @param	fmpt	: Audio format information
 * @return	Nothing
 */
void Chip_I2S_FIFO_Config(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt);

/**
 * @brief   Execute I2S FIFO control commands
 * @param	pI2S	: The base I2S peripheral on the chip
 * @param	fmt		: Audio format information
 * @param	cmd		: FIFO command
 * @return	Nothing
 */
void Chip_I2S_FIFO_Control(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt, I2S_FIFO_CMD_T cmd);


/**
 * @brief   Set I2S FIFO interrupts
 * @param	pI2S	: The base I2S peripheral on the chip
 * @param	int_val	: Interrupts to set
 * @return	Nothing
 */
__STATIC_INLINE void Chip_I2S_FIFO_SetInterrupt(LPC_I2S_T *pI2S, uint32_t int_val)
{
	pI2S->FIFOINTENSET = int_val;
}

/**
 * @brief   Clear I2S FIFO interrupts
 * @param	pI2S	: The base I2S peripheral on the chip
 * @param	int_val	: Interrupts to clear
 * @return	Nothing
 */
__STATIC_INLINE void Chip_I2S_FIFO_ClrInterrupt(LPC_I2S_T *pI2S, uint32_t int_val)
{
	pI2S->FIFOINTENCLR = int_val;
}

/**
 * @brief   Get I2S FIFO interrupts status
 * @param	pI2S	: The base I2S peripheral on the chip
 * @return	interrupt status
 */
__STATIC_INLINE uint32_t Chip_I2S_FIFO_GetInterruptStatus(LPC_I2S_T *pI2S)
{
	return pI2S->FIFOINTSTAT;
}

/* I2S6 Defines */
#define LPC_I2S6_BASE		__APPEND3(LPC_FLEXCOMM,I2S6_FLEXCOMM,_BASE)
#define LPC_I2S6			((LPC_I2S_T *) LPC_I2S6_BASE)
#define I2S6_IRQHandler		__APPEND3(FLEXCOMM,I2S6_FLEXCOMM,_IRQHandler)
#define I2S6_IRQn			__APPEND3(FLEXCOMM,I2S6_FLEXCOMM,_IRQn)
#define DMAREQ_I2S6_RX		__APPEND3(DMAREQ_FLEXCOMM,I2S6_FLEXCOMM,_RX)
#define DMAREQ_I2S6_TX		__APPEND3(DMAREQ_FLEXCOMM,I2S6_FLEXCOMM,_TX)

/* I2S7 Defines */
#define LPC_I2S7_BASE		__APPEND3(LPC_FLEXCOMM,I2S7_FLEXCOMM,_BASE)
#define LPC_I2S7			((LPC_I2S_T *) LPC_I2S7_BASE)
#define I2S7_IRQHandler		__APPEND3(FLEXCOMM,I2S7_FLEXCOMM,_IRQHandler)
#define I2S7_IRQn			__APPEND3(FLEXCOMM,I2S7_FLEXCOMM,_IRQn)
#define DMAREQ_I2S7_RX		__APPEND3(DMAREQ_FLEXCOMM,I2S7_FLEXCOMM,_RX)
#define DMAREQ_I2S7_TX		__APPEND3(DMAREQ_FLEXCOMM,I2S7_FLEXCOMM,_TX)

#ifdef __cplusplus
}
#endif

#endif /* __I2S_5411X_H_ */
