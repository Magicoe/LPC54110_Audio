/*
 * @brief LPC5411X SPI common functions and definitions
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

#ifndef __SPI_COMMON_5411X_H_
#define __SPI_COMMON_5411X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SPI_COMMON_5411X CHIP: LPC5411X SPI driver
 *
 * The SPI interface is provided via FlexCOMM module in the CHIP, to associate a SPI to
 * a flexcom the source file must add a define like <b>\#define SPI0_FLEXCOMM   5</b> which
 * will make LPC_SPI0 use LPC_FLEXCOMM5, interrupt service function name and IRQ number
 * DMA REQUEST number will all be mapped automatically. <b> Note that this define must
 * be available/visible to all the sources that uses SPI.</b><br><br> The SPI driver
 * by default will use FIFOs for TX and RX. TX and RX FIFOs has a depth of 8 entries each.
 *
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure */
	__I  uint32_t  RESERVED0[256];
	__IO uint32_t  CFG;				/*!< SPI Configuration register */
	__IO uint32_t  DLY;				/*!< SPI Delay register */
	__IO uint32_t  STAT;			/*!< SPI Status register */
	__IO uint32_t  INTENSET;		/*!< SPI Interrupt Enable Set register */
	__IO uint32_t  INTENCLR;		/*!< SPI Interrupt Enable Clear register */
	__I  uint32_t  RESERVED1[3];
	__IO uint32_t  TXCTRL;			/*!< SPI Transmit Control register */
	__IO uint32_t  DIV;				/*!< SPI clock Divider register */
	__IO uint32_t  INTSTAT;			/*!< SPI Interrupt Status register @cond */
	__I  uint32_t RESERVED2[629];  /*!< Offset: 0x02C Reserved member */

	/** SPI FIFO Specific registers @endcond */
	__IO uint32_t FIFOCFG;         /*!< Offset: 0xE00 FIFO Configuration register */
	__IO uint32_t FIFOSTAT;        /*!< Offset: 0xE04 FIFO Status register */
	__IO uint32_t FIFOTRIG;        /*!< Offset: 0xE08 FIFO Trigger level register @cond */
	__I  uint32_t RESERVED3;       /*!< Offset: 0xE0C Reserved register @endcond */
	__IO uint32_t FIFOINTENSET;    /*!< Offset: 0xE10 FIFO Interrupt enable SET register */
	__IO uint32_t FIFOINTENCLR;    /*!< Offset: 0xE14 FIFO Interrupt enable CLEAR register */
	__IO uint32_t FIFOINTSTAT;     /*!< Offset: 0xE18 FIFO Interrupt Status register @cond */
	__I  uint32_t RESERVED4;       /*!< Offset: 0xE1C Reserved register @endcond */
	__O  uint32_t FIFOWR;          /*!< Offset: 0xE20 FIFO Data write register @cond */
	__I  uint32_t RESERVED5[3];    /*!< Offset: 0xE24 Reserved register @endcond */
	__I  uint32_t FIFORD;          /*!< Offset: 0xE30 FIFO Data read register @cond */
	__I  uint32_t RESERVED6[3];    /*!< Offset: 0xE24 Reserved register @endcond */
	__I  uint32_t FIFORDNOPOP;     /*!< Offset: 0xE40 FIFO Data peek (read without popping out of queue) register @cond */
	__I  uint32_t RESERVED7[109];  /*!< Offset: 0xE44 Reserved register */

	/** FLEXCOMM Interface registers @endcond */
	__IO uint32_t PSELID;          /*!< Offset: 0xFF8 Peripheral select/identification register */
	__I  uint32_t PID;             /*!< Offset: 0xFFC Module identification register */
} LPC_SPI_T;

/**
 * Macro defines for SPI Configuration register
 */
#define SPI_CFG_BITMASK         (0xFBD)						/** SPI register bit mask */
#define SPI_CFG_SPI_EN          (1 << 0)					/** SPI Slave Mode Select */
#define SPI_CFG_SLAVE_EN        (0 << 0)					/** SPI Master Mode Select */
#define SPI_CFG_MASTER_EN       (1 << 2)					/** SPI MSB First mode enable */
#define SPI_CFG_MSB_FIRST_EN    (0 << 3)					/** SPI LSB First mode enable */
#define SPI_CFG_LSB_FIRST_EN    (1 << 3)					/** SPI Clock Phase Select */
#define SPI_CFG_CPHA_FIRST      (0 << 4)					/** Capture data on the first edge, Change data on the following edge */
#define SPI_CFG_CPHA_SECOND     (1 << 4)					/** SPI Clock Polarity Select */
#define SPI_CFG_CPOL_LO         (0 << 5)					/** The rest state of the clock (between frames) is low. */
#define SPI_CFG_CPOL_HI         (1 << 5)					/** The rest state of the clock (between frames) is high. */
#define SPI_CFG_LBM_EN          (1 << 7)					/** SPI control 1 loopback mode enable */
#define SPI_CFG_SPOL_LO         (0 << 8)					/** SPI SSEL0 Polarity Select */
#define SPI_CFG_SPOL_HI         (1 << 8)					/** SSEL0 is active High */
#define SPI_CFG_SPOLNUM_HI(n)   (1 << ((n) + 8))			/** SSELN is active High, selects 0 - 3 */

/**
 * Macro defines for SPI Delay register
 */
#define  SPI_DLY_BITMASK            (0xFFFF)				/** SPI DLY Register Mask */
#define  SPI_DLY_PRE_DELAY(n)       (((n) & 0x0F) << 0)		/** Time in SPI clocks between SSEL assertion and the beginning of a data frame */
#define  SPI_DLY_POST_DELAY(n)      (((n) & 0x0F) << 4)		/** Time in SPI clocks between the end of a data frame and SSEL deassertion. */
#define  SPI_DLY_FRAME_DELAY(n)     (((n) & 0x0F) << 8)		/** Minimum time in SPI clocks between adjacent data frames. */
#define  SPI_DLY_TRANSFER_DELAY(n)  (((n) & 0x0F) << 12)	/** Minimum time in SPI clocks that the SSEL is deasserted between transfers. */

/**
 * Macro defines for SPI Status register
 */
#define SPI_STAT_BITMASK            (0x1FC)					/** SPI STAT Register BitMask */
#define SPI_STAT_RXOV               (1 << 2)				/** Receiver Overrun interrupt flag */
#define SPI_STAT_TXUR               (1 << 3)				/** Transmitter Underrun interrupt flag (In Slave Mode only) */
#define SPI_STAT_SSA                (1 << 4)				/** Slave Select Assert */
#define SPI_STAT_SSD                (1 << 5)				/** Slave Select Deassert */
#define SPI_STAT_STALLED            (1 << 6)				/** Stalled status flag */
#define SPI_STAT_EOT                (1 << 7)				/** End Transfer flag */
#define SPI_STAT_MSTIDLE            (1 << 8)				/** Idle status flag */

/**
 * @brief	Macro defines for FIFO Status register
 */
#define SPI_FIFOSTAT_BITMASK        (0x1FFFFB)
#define SPI_FIFOSTAT_TXERR          (1 << 0)
#define SPI_FIFOSTAT_RXERR          (1 << 1)
#define SPI_FIFOSTAT_PERINT         (1 << 3)
#define SPI_FIFOSTAT_TXEMPTY        (1 << 4)
#define SPI_FIFOSTAT_TXNOTFULL      (1 << 5)
#define SPI_FIFOSTAT_RXNOTEMPTY     (1 << 6)
#define SPI_FIFOSTAT_RXFULL         (1 << 7)
#define SPI_FIFOSTAT_TXLVL(val)     (((val) >> 8) & 0x1F)
#define SPI_FIFOSTAT_RXLVL(val)     (((val) >> 16) & 0x1F)


/**
 * Macro defines for SPI Receiver Data register
 */
#define SPI_RXDAT_BITMASK           (0x1FFFFF)				/** SPI RXDAT Register BitMask */
#define SPI_RXDAT_DATA(n)           ((n) & 0xFFFF)			/** Receiver Data  */
#define SPI_RXDAT_RXSSELN_ACTIVE    (0 << 16)				/** The state of SSEL pin is active */
#define SPI_RXDAT_RXSSELN_INACTIVE  ((1 << 16)				/** The state of SSEL pin is inactive */
#define SPI_RXDAT_RXSSELNUM_INACTIVE(n) (1 << ((n) + 16))	/** The state of SSELN pin is inactive */
#define SPI_RXDAT_SOT               (1 << 20)				/** Start of Transfer flag  */

/**
 * Macro defines for SPI Transmitter Data and Control register
 */
#define SPI_TXDATCTL_BITMASK        (0xF7FFFFF)         /** SPI TXDATCTL Register BitMask */
#define SPI_TXDATCTL_DATA(n)        ((n) & 0xFFFF)      /** SPI Transmit Data */
#define SPI_TXDATCTL_CTRLMASK       (0xF7F)             /** SPI TXDATCTL Register BitMask for control bits only */
#define SPI_TXDATCTL_ASSERT_SSEL    0                   /** Assert SSEL0 pin */
#define SPI_TXDATCTL_DEASSERT_SSEL  1                   /** Deassert SSEL0 pin */
#define SPI_TXDATCTL_DEASSERTNUM_SSEL(n)    (1 << (n))	/** Deassert SSELN pin */
#define SPI_TXDATCTL_DEASSERT_ALL   0xF                 /** Deassert all SSEL pins */
#define SPI_TXDATCTL_EOT            (1 << 4)            /** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame) */
#define SPI_TXDATCTL_EOF            (1 << 5)            /** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXDATCTL_RXIGNORE       (1 << 6)            /** Receive Ignore Flag */
#define SPI_TXDATCTL_FLEN(n)        (((n) & 0x0F) << 8) /** Frame length - 1 */

/**
 * Macro defines for SPI Transmitter Data Register
 */
#define SPI_TXDAT_DATA(n)           ((n) & 0xFFFF)			/** SPI Transmit Data */

/**
 * Macro defines for SPI Transmitter Control register
 */
#define SPI_TXCTL_BITMASK             (0xF7F)                 /** SPI TXDATCTL Register BitMask */
#define SPI_TXCTL_ASSERT_SSEL         (0)                     /** Assert SSEL0 pin */
#define SPI_TXCTL_DEASSERT_SSEL       (1)                     /** Deassert SSEL0 pin */
#define SPI_TXCTL_DEASSERTNUM_SSEL(n) (1 << (n))              /** Deassert SSELN pin */
#define SPI_TXCTL_DEASSERT_ALL        0xF                     /** Deassert all SSEL pins */
#define SPI_TXCTL_EOT                 (1 << 4)				  /** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame) */
#define SPI_TXCTL_EOF                 (1 << 5)                /** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXCTL_RXIGNORE            (1 << 6)				  /** Receive Ignore Flag */
#define SPI_TXCTL_FLEN(n)           ((((n) - 1) & 0x0F) << 8) /** Frame length, 0 - 16 */
#define SPI_TXCTL_FLENMASK          (0xF << 8)                /** Frame length mask */

/**
 * Macro defines for SPI Divider register
 */
#define SPI_DIV_VAL(n)          ((n) & 0xFFFF)				/** Rate divider value mask (In Master Mode only)*/

/** @brief SPI Clock Mode*/
typedef enum {
	ROM_SPI_CLOCK_CPHA0_CPOL0 = 0,						/**< CPHA = 0, CPOL = 0 */
	ROM_SPI_CLOCK_MODE0 = ROM_SPI_CLOCK_CPHA0_CPOL0,	/**< Alias for CPHA = 0, CPOL = 0 */
	ROM_SPI_CLOCK_CPHA1_CPOL0 = 1,						/**< CPHA = 0, CPOL = 1 */
	ROM_SPI_CLOCK_MODE1 = ROM_SPI_CLOCK_CPHA1_CPOL0,	/**< Alias for CPHA = 0, CPOL = 1 */
	ROM_SPI_CLOCK_CPHA0_CPOL1 = 2,						/**< CPHA = 1, CPOL = 0 */
	ROM_SPI_CLOCK_MODE2 = ROM_SPI_CLOCK_CPHA0_CPOL1,	/**< Alias for CPHA = 1, CPOL = 0 */
	ROM_SPI_CLOCK_CPHA1_CPOL1 = 3,						/**< CPHA = 1, CPOL = 1 */
	ROM_SPI_CLOCK_MODE3 = ROM_SPI_CLOCK_CPHA1_CPOL1,	/**< Alias for CPHA = 1, CPOL = 1 */
} ROM_SPI_CLOCK_MODE_T;

/**
 * @brief Macro defines for SPI Interrupt enable/disable/status [INTSET/INTCLR/INTSTAT and FIFOINTSET/FIFOINTCLR/FIFOINTSTAT registers]
 */
#define SPI_INT_BITMASK        (0x130)               /** SPI interrupt Enable/Disable bits */
#define SPI_INT_FIFOBITMASK    (0x1F)               /** FIFO interrupt Bit mask */
#define SPI_INT_TXERR          (1 << 0)             /** TX error interrupt [BIT-0 of FIFOINTENSET/FIFOINTENCLR/FIFOINTSTAT register] */
#define SPI_INT_RXERR          (1 << 1)             /** RX error interrupt [BIT-1 of FIFOINTENSET/FIFOINTENCLR/FIFOINTSTAT register] */
#define SPI_INT_TXDYEN         (1 << 2)             /** TX FIFO ready interrupt [BIT-2 of FIFOINTENSET/FIFOINTENCLR/FIFOINTSTAT register] */
#define SPI_INT_RXDYEN         (1 << 3)             /** RX Data ready interrupt [BIT-3 of FIFOINTENSET/FIFOINTENCLR/FIFOINTSTAT register] */
#define SPI_INT_RXOVEN         (1 << 1)             /**  RX Overrun interrupt [BIT-2 of INTENSET/INTENCLR/INTSTAT register]*/
#define SPI_INT_TXUREN         (1 << 0)             /**  TX underrun interrupt (In Slave Mode Only)  [BIT-3 of INTENSET/INTENCLR/INTSTAT register]*/
#define SPI_INT_SSAEN          (1 << 6)             /**  Slave Select is asserted interrupt [BIT-4 of INTENSET/INTENCLR/INTSTAT register] */
#define SPI_INT_SSDEN          (1 << 7)             /**  Slave Select is deasserted interrupt [BIT-5 of INTENSET/INTENCLR/INTSTAT register] */
#define SPI_INT_MSTIDLE        (1 << 10)            /** SPI master is Idle */

/**
 * @brief   Initialize the SPI
 * @param	pSPI	: The base SPI peripheral on the chip
 * @return	Nothing
 */
int Chip_SPI_Init(LPC_SPI_T *pSPI);

/**
 * @brief	Disable SPI operation
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	The SPI controller is disabled.
 */
__STATIC_INLINE void Chip_SPI_DeInit(LPC_SPI_T *pSPI)
{
	Chip_FLEXCOMM_DeInit(pSPI);
}

/**
 * @brief	Set SPI CFG register values
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: CFG register bits to set, amd OR'ed value of SPI_CFG_* definitions
 * @return	Nothing
 * @note	This function safely sets only the selected bits in the SPI CFG register.
 * It can be used to enable multiple bits at once.
 */
__STATIC_INLINE void Chip_SPI_SetCFGRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	pSPI->CFG = (pSPI->CFG & SPI_CFG_BITMASK) | bits;
}

/**
 * @brief	Clear SPI CFG register values
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: CFG register bits to clear, amd OR'ed value of SPI_CFG_* definitions
 * @return	Nothing
 * @note	This function safely clears only the selected bits in the SPI CFG register.
 * It can be used to disable multiple bits at once.
 */
__STATIC_INLINE void Chip_SPI_ClearCFGRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	pSPI->CFG = pSPI->CFG & (~bits & SPI_CFG_BITMASK);
}

/**
 * @brief	Enable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_Enable(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_SPI_EN);
}

/**
 * @brief	Disable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_Disable(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_SPI_EN);
}

/**
 * @brief	Enable SPI master mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note SPI slave mode will be disabled with this call. All SPI SSEL
 * lines will also be deasserted.
 */
__STATIC_INLINE void Chip_SPI_EnableMasterMode(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_MASTER_EN);

	/* Deassert all chip selects, only in master mode */
	pSPI->TXCTRL = SPI_TXDATCTL_DEASSERT_ALL;
}

/**
 * @brief	Enable SPI slave mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note SPI master mode will be disabled with this call.
 */
__STATIC_INLINE void Chip_SPI_EnableSlaveMode(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_MASTER_EN);
}

/**
 * @brief	Enable LSB First transfers
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_EnableLSBFirst(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_LSB_FIRST_EN);
}

/**
 * @brief	Enable MSB First transfers
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_EnableMSBFirst(LPC_SPI_T *pSPI)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_LSB_FIRST_EN);
}

/** @brief SPI Clock Mode*/
typedef enum IP_SPI_CLOCK_MODE {
	SPI_CLOCK_CPHA0_CPOL0 = SPI_CFG_CPOL_LO | SPI_CFG_CPHA_FIRST,		/**< CPHA = 0, CPOL = 0 */
	SPI_CLOCK_MODE0 = SPI_CLOCK_CPHA0_CPOL0,							/**< Alias for CPHA = 0, CPOL = 0 */
	SPI_CLOCK_CPHA1_CPOL0 = SPI_CFG_CPOL_LO | SPI_CFG_CPHA_SECOND,		/**< CPHA = 0, CPOL = 1 */
	SPI_CLOCK_MODE1 = SPI_CLOCK_CPHA1_CPOL0,							/**< Alias for CPHA = 0, CPOL = 1 */
	SPI_CLOCK_CPHA0_CPOL1 = SPI_CFG_CPOL_HI | SPI_CFG_CPHA_FIRST,		/**< CPHA = 1, CPOL = 0 */
	SPI_CLOCK_MODE2 = SPI_CLOCK_CPHA0_CPOL1,							/**< Alias for CPHA = 1, CPOL = 0 */
	SPI_CLOCK_CPHA1_CPOL1 = SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND,		/**< CPHA = 1, CPOL = 1 */
	SPI_CLOCK_MODE3 = SPI_CLOCK_CPHA1_CPOL1,							/**< Alias for CPHA = 1, CPOL = 1 */
} SPI_CLOCK_MODE_T;

/**
 * @brief	Set SPI mode
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	mode	: SPI mode to set the SPI interface to
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_SetSPIMode(LPC_SPI_T *pSPI, SPI_CLOCK_MODE_T mode)
{
	Chip_SPI_ClearCFGRegBits(pSPI, (SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND));
	Chip_SPI_SetCFGRegBits(pSPI, (uint32_t) mode);
}

/**
 * @brief	Set polarity on the SPI chip select high
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	csNum	: Chip select number, 0 - 3
 * @return	Nothing
 * @note	SPI chip select polarity is active high.
 */
__STATIC_INLINE void Chip_SPI_SetCSPolHigh(LPC_SPI_T *pSPI, uint8_t csNum)
{
	Chip_SPI_SetCFGRegBits(pSPI, SPI_CFG_SPOLNUM_HI(csNum));
}

/**
 * @brief	Set polarity on the SPI chip select low
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	csNum	: Chip select number, 0 - 3
 * @return	Nothing
 * @note	SPI chip select polarity is active low.
 */
__STATIC_INLINE void Chip_SPI_SetCSPolLow(LPC_SPI_T *pSPI, uint8_t csNum)
{
	Chip_SPI_ClearCFGRegBits(pSPI, SPI_CFG_SPOLNUM_HI(csNum));
}

/** SPI configuration structure used for setting up master/slave mode, LSB or
 * MSB first, and SPI mode in a single function call. */
typedef struct {
	uint32_t master             : 8;	/* Set to non-0 value to use master mode, 0 for slave */
	uint32_t lsbFirst           : 8;	/* Set to non-0 value to send LSB first, 0 for MSB first */
	SPI_CLOCK_MODE_T mode       : 8;	/* Mode selection */
	uint32_t reserved           : 8;	/* Reserved, for alignment only */
} SPI_CFGSETUP_T;

/**
 * @brief	Setup SPI configuration
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	pCFG	: Pointer to SPI configuration structure
 * @return	Nothing
 */
void Chip_SPI_ConfigureSPI(LPC_SPI_T *pSPI, SPI_CFGSETUP_T *pCFG);

/**
 * @brief	Get the current status of SPI controller
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	SPI Status (Or-ed bit value of SPI_STAT_*)
 * @note	Mask the return value with a value of type SPI_STAT_* to determine
 * if that status is active.
 */
__STATIC_INLINE uint32_t Chip_SPI_GetStatus(LPC_SPI_T *pSPI)
{
	return pSPI->STAT;
}

/**
 * @brief	Get the current status of SPI controller FIFO
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	SPI Status (Or-ed bit value of SPI_FIFOSTAT_*)
 * @note	Mask the return value with a value of type SPI_FIFOSTAT_* to determine
 * if that status is active.
 */
__STATIC_INLINE uint32_t Chip_SPI_GetFIFOStatus(LPC_SPI_T *pSPI)
{
	return pSPI->FIFOSTAT;
}

/**
 * @brief	Clear the FIFO status register
 * @param	pSPI	: The base of the SPI peripheral on the chip
 * @param	mask	: Mask of the status bits that needs to be cleared
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_ClearFIFOStatus(LPC_SPI_T *pSPI, uint32_t mask)
{
	pSPI->FIFOSTAT = mask;
}

/**
 * @brief	Setup the trigger level for SPI FIFO
 * @param	pSPI	: The base of the SPI peripheral on chip
 * @param	tx_lvl	: TX Trigger level [Valid values 0 to 7]
 * @param	rx_lvl	: RX Trigger level [Valid values 0 to 7]
 * @return	Nothing
 * @note	When @a tx_lvl = 0; trigger will happen when TX FIFO is empty
 * if @a tx_lvl = 7; trigger will happen when TX FIFO has at least one free space<br>
 * When @a rx_lvl = 0; trigger will happen when RX FIFO has at least one data in it,
 * if @a rx_lvl = 7; trigger will happen when RX FIFO is full and cannot receive anymore data
 */
__STATIC_INLINE void Chip_SPI_SetFIFOTrigLevel(LPC_SPI_T *pSPI, uint8_t tx_lvl, uint8_t rx_lvl)
{
	pSPI->FIFOTRIG = 3 | (tx_lvl << 8) | (rx_lvl << 16);
}

/**
 * @brief	Clear SPI status
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flag	: Clear Flag (Or-ed bit value of SPI_STAT_*)
 * @return	Nothing
 * @note	Only SPI_STAT_RXOV, SPI_STAT_TXUR, SPI_STAT_SSA, and
 * SPI_STAT_SSD statuses can be cleared.
 */
__STATIC_INLINE void Chip_SPI_ClearStatus(LPC_SPI_T *pSPI, uint32_t Flag)
{
	pSPI->STAT = Flag;
}

/**
 * @brief	Enable a SPI interrupt
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	intMask	: Or'ed value of SPI_INT_* values to enable
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_EnableInts(LPC_SPI_T *pSPI, uint32_t intMask)
{
	pSPI->INTENSET = (intMask >> 2) & SPI_INT_BITMASK;
	pSPI->FIFOINTENSET = intMask & SPI_INT_FIFOBITMASK;
}

/**
 * @brief	Disable a SPI interrupt
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	intMask	: Or'ed value of SPI_INT_* values to disable (See #SPI_INT_TXERR)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_DisableInts(LPC_SPI_T *pSPI, uint32_t intMask)
{
	pSPI->INTENCLR = (intMask >> 2) & SPI_INT_BITMASK;
	pSPI->FIFOINTENCLR = intMask & SPI_INT_FIFOBITMASK;
}

/**
 * @brief	Return enabled SPI interrupts
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	An Or'ed value of SPI_INT_* values
 * @note	Mask the return value with a SPI_INT_* value to determine (See #SPI_INT_TXERR)
 * if the interrupt is enabled.
 */
__STATIC_INLINE uint32_t Chip_SPI_GetEnabledInts(LPC_SPI_T *pSPI)
{
	return ((pSPI->INTENSET & SPI_INT_BITMASK) << 2) | (pSPI->FIFOINTENSET & SPI_INT_FIFOBITMASK);
}

/**
 * @brief	Return pending SPI interrupts
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	An Or'ed value of SPI_INT_* values
 * @note	Mask the return value with a SPI_INT_* value to determine (See #SPI_INT_TXERR)
 * if the interrupt is pending.
 */
__STATIC_INLINE uint32_t Chip_SPI_GetPendingInts(LPC_SPI_T *pSPI)
{
	uint32_t val = pSPI->FIFOINTSTAT & SPI_INT_FIFOBITMASK;
	if (val & (1 << 4)) {
		val |= (pSPI->INTSTAT & SPI_INT_BITMASK) << 2;
	}
	return val;
}

/**
 * @brief	SPI FIFO Configuration register bits
 * @cond
 */
#define SPI_FIFOCFG_MASK             0x7F033    /*!< Register mask bit @endcond */
#define SPI_FIFOCFG_ENABLETX         (1 << 0)   /*!< Enable TX FIFO */
#define SPI_FIFOCFG_ENABLERX         (1 << 1)   /*!< Enable RX FIFO */
#define SPI_FIFOCFG_DMATX            (1 << 12)  /*!< Enable DMA TX */
#define SPI_FIFOCFG_DMARX            (1 << 13)  /*!< Enable DMA RX */
#define SPI_FIFOCFG_WAKETX           (1 << 14)  /*!< Enable wakeup triggered by TX */
#define SPI_FIFOCFG_WAKERX           (1 << 15)  /*!< Enable wakeup triggered by RX */
#define SPI_FIFOCFG_EMPTYTX          (1 << 16)  /*!< Empty the TX FIFO */
#define SPI_FIFOCFG_EMPTYRX          (1 << 17)  /*!< Empty the RX FIFO */
#define SPI_FIFOCFG_POPDBG           (1 << 18)  /*!< Enable Debug POP from FIFO */

/**
 * @brief	Set FIFO Configuration register
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	cfg		: Configuration value mask (OR'ed SPI_FIFOCFG_* values like #SPI_FIFOCFG_ENABLETX)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_SetFIFOCfg(LPC_SPI_T *pSPI, uint32_t cfg)
{
	pSPI->FIFOCFG = (pSPI->FIFOCFG & SPI_FIFOCFG_MASK) | cfg;
}

/**
 * @brief	Clear FIFO Configuration register
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	cfg		: Configuration value mask (OR'ed SPI_FIFOCFG_* values like #SPI_FIFOCFG_ENABLETX)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_ClearFIFOCfg(LPC_SPI_T *pSPI, uint32_t cfg)
{
	pSPI->FIFOCFG = pSPI->FIFOCFG & (SPI_FIFOCFG_MASK & ~cfg);
}

/**
 * @brief	Flush FIFOs
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_FlushFifos(LPC_SPI_T *pSPI)
{
	Chip_SPI_SetFIFOCfg(pSPI, SPI_FIFOCFG_EMPTYTX | SPI_FIFOCFG_EMPTYRX);
}

/**
 * @brief	Read raw data from receive FIFO with status bits
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Current value in receive data FIFO plus status bits
 */
__STATIC_INLINE uint32_t Chip_SPI_ReadRawRXFifo(LPC_SPI_T *pSPI)
{
	return pSPI->FIFORD;
}

/**
 * @brief	Read receive FIFO status, masking off data bits
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Current status value in receive FIFO
 */
__STATIC_INLINE uint16_t Chip_SPI_ReadRXStat(LPC_SPI_T *pSPI)
{
	return *((__I uint16_t *) &pSPI->FIFORD + 1);
}

/**
 * @brief	Read data from receive FIFO masking off status bits
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Current value in receive data FIFO
 * @note	The return value is masked with 0xFFFF to not exceed 16-bits. All
 * other status bits are thrown away. This register should only be read if it
 * has data in it. This function is useful for systems that don't need SPI
 * select (SSEL) monitoring.
 */
__STATIC_INLINE uint16_t Chip_SPI_ReadRXData(LPC_SPI_T *pSPI)
{
	return *((__I uint16_t *) &pSPI->FIFORD);
}

/**
 * @brief	Write data to transmit FIFO
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	data	: Data to write
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_WriteTXData(LPC_SPI_T *pSPI, uint16_t data)
{
	*((__O uint16_t *) &pSPI->FIFOWR) = data;
}

/**
 * @brief	Set SPI TXCTRL register control options
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: TXCTRL register bits to set, amd OR'ed value of SPI_TXDATCTL_* definitions
 * @return	Nothing
 * @sa		Chip_SPI_SetTXCTRLData()
 * @note	This function safely sets only the selected bits in the SPI TXCTRL register.
 * It can be used to enable multiple bits at once. Use Chip_SPI_SetTXCTRLData() API instead of this
 * when the FIFO is enabled.
 */
__STATIC_INLINE void Chip_SPI_SetTXCTRLRegBits(LPC_SPI_T *pSPI, uint16_t bits)
{
	*((__O uint16_t *) &pSPI->FIFOWR + 1) = (*((__O uint16_t *) &pSPI->FIFOWR + 1) & SPI_TXDATCTL_CTRLMASK) | bits;
}

/**
 * @brief	Set SPI TXCTRL register control options, along with the data to be transfered
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	ctrl	: Control bits to be set
 * @param 	data	: Data to be transfered
 * @return	Nothing
 * @note	This function safely sets only the selected bits in the SPI TXCTRL register.
 * It can be used to enable multiple bits at once.
 */
__STATIC_INLINE void Chip_SPI_SetTXCTRLData(LPC_SPI_T *pSPI, uint16_t ctrl, uint16_t data)
{
	pSPI->FIFOWR = (ctrl << 16) | data;
}

/**
 * @brief	Clear SPI TXCTRL register control options
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	bits	: TXCTRL register bits to clear, amd OR'ed value of SPI_TXDATCTL_* definitions
 * @return	Nothing
 * @note	This function safely clears only the selected bits in the SPI TXCTRL register.
 * It can be used to disable multiple bits at once.
 */
__STATIC_INLINE void Chip_SPI_ClearTXCTRLRegBits(LPC_SPI_T *pSPI, uint32_t bits)
{
	*((__O uint16_t *) &pSPI->FIFOWR + 1) = *((__O uint16_t *) &pSPI->FIFOWR + 1) & (SPI_TXDATCTL_CTRLMASK & ~bits);
}

/**
 * @brief	Set TX control options (safe)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Or'ed control bits to set
 * @return	Nothing
 * @note	Selectable control states include SPI_TXCTL_DEASSERTNUM_SSEL(0/1/2/3),
 * SPI_TXCTL_EOT, SPI_TXCTL_EOF, SPI_TXCTL_RXIGNORE, and SPI_TXCTL_FLEN(bits).
 */
__STATIC_INLINE void Chip_SPI_SetTXCtl(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_SetTXCTRLRegBits(pSPI, ctrlBits);
}

/**
 * @brief	Clear TX control options (safe)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Or'ed control bits to clear
 * @return	Nothing
 * @note	Selectable control states include SPI_TXCTL_DEASSERTNUM_SSEL(0/1/2/3),
 * SPI_TXCTL_EOT, SPI_TXCTL_EOF, SPI_TXCTL_RXIGNORE, and SPI_TXCTL_FLEN(bits).
 */
__STATIC_INLINE void Chip_SPI_ClearTXCtl(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_ClearTXCTRLRegBits(pSPI, ctrlBits);
}

/**
 * @brief	Set TX data transfer size in bits
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	ctrlBits	: Number of bits to transmit and receive, must be 1 to 16
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SPI_SetXferSize(LPC_SPI_T *pSPI, uint32_t ctrlBits)
{
	Chip_SPI_ClearTXCTRLRegBits(pSPI, SPI_TXCTL_FLENMASK);
	Chip_SPI_SetTXCTRLRegBits(pSPI, SPI_TXCTL_FLEN(ctrlBits));
}

#ifndef __DOXYGEN__

/* SPI0 Defines */
#define LPC_SPI0_BASE   __APPEND3(LPC_FLEXCOMM,SPI0_FLEXCOMM,_BASE)
#define LPC_SPI0        ((LPC_SPI_T *) LPC_SPI0_BASE)
#define SPI0_IRQHandler __APPEND3(FLEXCOMM,SPI0_FLEXCOMM,_IRQHandler)
#define SPI0_IRQn       __APPEND3(FLEXCOMM,SPI0_FLEXCOMM,_IRQn)
#define DMAREQ_SPI0_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI0_FLEXCOMM,_RX)
#define DMAREQ_SPI0_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI0_FLEXCOMM,_TX)

/* SPI1 Defines */
#define LPC_SPI1_BASE   __APPEND3(LPC_FLEXCOMM,SPI1_FLEXCOMM,_BASE)
#define LPC_SPI1        ((LPC_SPI_T *) LPC_SPI1_BASE)
#define SPI1_IRQHandler __APPEND3(FLEXCOMM,SPI1_FLEXCOMM,_IRQHandler)
#define SPI1_IRQn       __APPEND3(FLEXCOMM,SPI1_FLEXCOMM,_IRQn)
#define DMAREQ_SPI1_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI1_FLEXCOMM,_RX)
#define DMAREQ_SPI1_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI1_FLEXCOMM,_TX)

/* SPI2 Defines */
#define LPC_SPI2_BASE   __APPEND3(LPC_FLEXCOMM,SPI2_FLEXCOMM,_BASE)
#define LPC_SPI2        ((LPC_SPI_T *) LPC_SPI2_BASE)
#define SPI2_IRQHandler __APPEND3(FLEXCOMM,SPI2_FLEXCOMM,_IRQHandler)
#define SPI2_IRQn       __APPEND3(FLEXCOMM,SPI2_FLEXCOMM,_IRQn)
#define DMAREQ_SPI2_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI2_FLEXCOMM,_RX)
#define DMAREQ_SPI2_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI2_FLEXCOMM,_TX)

/* SPI3 Defines */
#define LPC_SPI3_BASE   __APPEND3(LPC_FLEXCOMM,SPI3_FLEXCOMM,_BASE)
#define LPC_SPI3        ((LPC_SPI_T *) LPC_SPI3_BASE)
#define SPI3_IRQHandler __APPEND3(FLEXCOMM,SPI3_FLEXCOMM,_IRQHandler)
#define SPI3_IRQn       __APPEND3(FLEXCOMM,SPI3_FLEXCOMM,_IRQn)
#define DMAREQ_SPI3_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI3_FLEXCOMM,_RX)
#define DMAREQ_SPI3_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI3_FLEXCOMM,_TX)

/* SPI4 Defines */
#define LPC_SPI4_BASE   __APPEND3(LPC_FLEXCOMM,SPI4_FLEXCOMM,_BASE)
#define LPC_SPI4        ((LPC_SPI_T *) LPC_SPI4_BASE)
#define SPI4_IRQHandler __APPEND3(FLEXCOMM,SPI4_FLEXCOMM,_IRQHandler)
#define SPI4_IRQn       __APPEND3(FLEXCOMM,SPI4_FLEXCOMM,_IRQn)
#define DMAREQ_SPI4_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI4_FLEXCOMM,_RX)
#define DMAREQ_SPI4_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI4_FLEXCOMM,_TX)

/* SPI5 Defines */
#define LPC_SPI5_BASE   __APPEND3(LPC_FLEXCOMM,SPI5_FLEXCOMM,_BASE)
#define LPC_SPI5        ((LPC_SPI_T *) LPC_SPI5_BASE)
#define SPI5_IRQHandler __APPEND3(FLEXCOMM,SPI5_FLEXCOMM,_IRQHandler)
#define SPI5_IRQn       __APPEND3(FLEXCOMM,SPI5_FLEXCOMM,_IRQn)
#define DMAREQ_SPI5_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI5_FLEXCOMM,_RX)
#define DMAREQ_SPI5_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI5_FLEXCOMM,_TX)

/* SPI6 Defines */
#define LPC_SPI6_BASE   __APPEND3(LPC_FLEXCOMM,SPI6_FLEXCOMM,_BASE)
#define LPC_SPI6        ((LPC_SPI_T *) LPC_SPI6_BASE)
#define SPI6_IRQHandler __APPEND3(FLEXCOMM,SPI6_FLEXCOMM,_IRQHandler)
#define SPI6_IRQn       __APPEND3(FLEXCOMM,SPI6_FLEXCOMM,_IRQn)
#define DMAREQ_SPI6_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI6_FLEXCOMM,_RX)
#define DMAREQ_SPI6_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI6_FLEXCOMM,_TX)

/* SPI7 Defines */
#define LPC_SPI7_BASE   __APPEND3(LPC_FLEXCOMM,SPI7_FLEXCOMM,_BASE)
#define LPC_SPI7        ((LPC_SPI_T *) LPC_SPI7_BASE)
#define SPI7_IRQHandler __APPEND3(FLEXCOMM,SPI7_FLEXCOMM,_IRQHandler)
#define SPI7_IRQn       __APPEND3(FLEXCOMM,SPI7_FLEXCOMM,_IRQn)
#define DMAREQ_SPI7_RX  __APPEND3(DMAREQ_FLEXCOMM,SPI7_FLEXCOMM,_RX)
#define DMAREQ_SPI7_TX  __APPEND3(DMAREQ_FLEXCOMM,SPI7_FLEXCOMM,_TX)

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_COMMON_5411X_H_ */
