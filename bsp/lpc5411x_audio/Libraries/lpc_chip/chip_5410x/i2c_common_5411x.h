/*
 * @brief LPC5411x I2C driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef __I2C_COMMON_5411X_H_
#define __I2C_COMMON_5411X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup I2C_5411X CHIP: LPC5411x I2C driver
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

/**
 * @brief I2C register block structure
 * @cond
 */
typedef struct {					/* I2C0 Structure         */
	__IO uint32_t RESERVED0A[512];
	__IO uint32_t CFG;				/*!< @endcond I2C Configuration Register common for Master, Slave and Monitor */
	__IO uint32_t STAT;				/*!< I2C Status Register common for Master, Slave and Monitor */
	__IO uint32_t INTENSET;			/*!< I2C Interrupt Enable Set Register common for Master, Slave and Monitor */
	__O  uint32_t INTENCLR;			/*!< I2C Interrupt Enable Clear Register common for Master, Slave and Monitor */
	__IO uint32_t TIMEOUT;			/*!< I2C Timeout value Register */
	__IO uint32_t CLKDIV;			/*!< I2C Clock Divider Register */
	__IO uint32_t INTSTAT;			/*!< I2C Interrupt Status Register */
	__I  uint32_t RESERVED0;
	__IO uint32_t MSTCTL;			/*!< I2C Master Control Register */
	__IO uint32_t MSTTIME;			/*!< I2C Master Time Register for SCL */
	__IO uint32_t MSTDAT;			/*!< I2C Master Data Register */
	__IO uint32_t RESERVED1[5];
	__IO uint32_t SLVCTL;			/*!< I2C Slave Control Register */
	__IO uint32_t SLVDAT;			/*!< I2C Slave Data Register */
	__IO uint32_t SLVADR[4];		/*!< I2C Slave Address Registers */
	__IO uint32_t SLVQUAL0;			/*!< I2C Slave Address Qualifier 0 Register */
	__IO uint32_t RESERVED2[9];
	__I  uint32_t MONRXDAT;			/*!< I2C Monitor Data Register @cond */
	__I  uint32_t RESERVED3[477];

	/** FLEXCOMM Interface registers @endcond */
	__IO uint32_t PSELID;          /*!< Offset: 0xFF8 Peripheral select/identification register */
	__I  uint32_t PID;             /*!< Offset: 0xFFC Module identification register */ 
} LPC_I2C_T;

/*
 * @brief I2C Configuration register Bit definition
 */
#define I2C_CFG_MSTEN             (1 << 0)			/*!< Master Enable/Disable Bit */
#define I2C_CFG_SLVEN             (1 << 1)			/*!< Slave Enable/Disable Bit */
#define I2C_CFG_MONEN             (1 << 2)			/*!< Monitor Enable/Disable Bit */
#define I2C_CFG_TIMEOUTEN         (1 << 3)			/*!< Timeout Enable/Disable Bit */
#define I2C_CFG_MONCLKSTR         (1 << 4)			/*!< Monitor Clock Stretching Bit */
#define I2C_CFG_MASK              ((uint32_t) 0x1F)	/*!< Configuration Register Mask */

/*
 * @brief I2C Status register Bit definition
 */
#define I2C_STAT_MSTPENDING       (1 << 0)		/*!< Master Pending Status Bit */
#define I2C_STAT_MSTSTATE         (0x7 << 1)	/*!< Master State Code */
#define I2C_STAT_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Bit */
#define I2C_STAT_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Bit */
#define I2C_STAT_SLVPENDING       (1 << 8)		/*!< Slave Pending Status Bit */
#define I2C_STAT_SLVSTATE         (0x3 << 9)	/*!< Slave State Code */
#define I2C_STAT_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Bit */
#define I2C_STAT_SLVIDX           (0x3 << 12)	/*!< Slave Address Index */
#define I2C_STAT_SLVSEL           (1 << 14)		/*!< Slave Selected Bit */
#define I2C_STAT_SLVDESEL         (1 << 15)		/*!< Slave Deselect Bit */
#define I2C_STAT_MONRDY           (1 << 16)		/*!< Monitor Ready Bit */
#define I2C_STAT_MONOV            (1 << 17)		/*!< Monitor Overflow Flag */
#define I2C_STAT_MONACTIVE        (1 << 18)		/*!< Monitor Active Flag */
#define I2C_STAT_MONIDLE          (1 << 19)		/*!< Monitor Idle Flag */
#define I2C_STAT_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Flag */
#define I2C_STAT_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Flag */

#define I2C_STAT_MSTCODE_IDLE       (0)			/*!< Master Idle State Code */
#define I2C_STAT_MSTCODE_RXREADY    (1)			/*!< Master Receive Ready State Code */
#define I2C_STAT_MSTCODE_TXREADY    (2)			/*!< Master Transmit Ready State Code */
#define I2C_STAT_MSTCODE_NACKADR    (3)			/*!< Master NACK by slave on address State Code */
#define I2C_STAT_MSTCODE_NACKDAT    (4)			/*!< Master NACK by slave on data State Code */

#define I2C_STAT_SLVCODE_ADDR         (0)		/*!< Master Idle State Code */
#define I2C_STAT_SLVCODE_RX           (1)		/*!< Received data is available Code */
#define I2C_STAT_SLVCODE_TX           (2)		/*!< Data can be transmitted Code */

/*
 * @brief I2C Interrupt Enable Set register Bit definition
 */
#define I2C_INTENSET_MSTPENDING       (1 << 0)		/*!< Master Pending Interrupt Enable Bit */
#define I2C_INTENSET_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Interrupt Enable Bit */
#define I2C_INTENSET_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Interrupt Enable Bit */
#define I2C_INTENSET_SLVPENDING       (1 << 8)		/*!< Slave Pending Interrupt Enable Bit */
#define I2C_INTENSET_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Interrupt Enable Bit */
#define I2C_INTENSET_SLVDESEL         (1 << 15)		/*!< Slave Deselect Interrupt Enable Bit */
#define I2C_INTENSET_MONRDY           (1 << 16)		/*!< Monitor Ready Interrupt Enable Bit */
#define I2C_INTENSET_MONOV            (1 << 17)		/*!< Monitor Overflow Interrupt Enable Bit */
#define I2C_INTENSET_MONIDLE          (1 << 19)		/*!< Monitor Idle Interrupt Enable Bit */
#define I2C_INTENSET_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Enable Bit */
#define I2C_INTENSET_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Enable Bit */

/*
 * @brief I2C Interrupt Enable Clear register Bit definition
 */
#define I2C_INTENCLR_MSTPENDING       (1 << 0)		/*!< Master Pending Interrupt Clear Bit */
#define I2C_INTENCLR_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Interrupt Clear Bit */
#define I2C_INTENCLR_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Interrupt Clear Bit */
#define I2C_INTENCLR_SLVPENDING       (1 << 8)		/*!< Slave Pending Interrupt Clear Bit */
#define I2C_INTENCLR_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Interrupt Clear Bit */
#define I2C_INTENCLR_SLVDESEL         (1 << 15)		/*!< Slave Deselect Interrupt Clear Bit */
#define I2C_INTENCLR_MONRDY           (1 << 16)		/*!< Monitor Ready Interrupt Clear Bit */
#define I2C_INTENCLR_MONOV            (1 << 17)		/*!< Monitor Overflow Interrupt Clear Bit */
#define I2C_INTENCLR_MONIDLE          (1 << 19)		/*!< Monitor Idle Interrupt Clear Bit */
#define I2C_INTENCLR_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Clear Bit */
#define I2C_INTENCLR_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Clear Bit */

/*
 * @brief I2C TimeOut Value Macro
 */
#define I2C_TIMEOUT_VAL(n)              (((uint32_t) ((n) - 1) & 0xFFF0) | 0x000F)		/*!< Macro for Timeout value register */

/*
 * @brief I2C Interrupt Status register Bit definition
 */
#define I2C_INTSTAT_MSTPENDING      (1 << 0)		/*!< Master Pending Interrupt Status Bit */
#define I2C_INTSTAT_MSTRARBLOSS     (1 << 4)		/*!< Master Arbitration Loss Interrupt Status Bit */
#define I2C_INTSTAT_MSTSTSTPERR     (1 << 6)		/*!< Master Start Stop Error Interrupt Status Bit */
#define I2C_INTSTAT_SLVPENDING      (1 << 8)		/*!< Slave Pending Interrupt Status Bit */
#define I2C_INTSTAT_SLVNOTSTR       (1 << 11)		/*!< Slave not stretching Clock Interrupt Status Bit */
#define I2C_INTSTAT_SLVDESEL        (1 << 15)		/*!< Slave Deselect Interrupt Status Bit */
#define I2C_INTSTAT_MONRDY          (1 << 16)		/*!< Monitor Ready Interrupt Status Bit */
#define I2C_INTSTAT_MONOV           (1 << 17)		/*!< Monitor Overflow Interrupt Status Bit */
#define I2C_INTSTAT_MONIDLE         (1 << 19)		/*!< Monitor Idle Interrupt Status Bit */
#define I2C_INTSTAT_EVENTTIMEOUT    (1 << 24)		/*!< Event Timeout Interrupt Status Bit */
#define I2C_INTSTAT_SCLTIMEOUT      (1 << 25)		/*!< SCL Timeout Interrupt Status Bit */

/*
 * @brief I2C Master Control register Bit definition
 */
#define I2C_MSTCTL_MSTCONTINUE  (1 << 0)		/*!< Master Continue Bit */
#define I2C_MSTCTL_MSTSTART     (1 << 1)		/*!< Master Start Control Bit */
#define I2C_MSTCTL_MSTSTOP      (1 << 2)		/*!< Master Stop Control Bit */
#define I2C_MSTCTL_MSTDMA       (1 << 3)		/*!< Master DMA Enable Bit */

/*
 * @brief I2C Master Time Register Field definition
 */
#define I2C_MSTTIME_MSTSCLLOW   (0x07 << 0)		/*!< Master SCL Low Time field */
#define I2C_MSTTIME_MSTSCLHIGH  (0x07 << 4)		/*!< Master SCL High Time field */

/*
 * @brief I2C Master Data Mask
 */
#define I2C_MSTDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Master data mask */

/*
 * @brief I2C Slave Control register Bit definition
 */
#define I2C_SLVCTL_SLVCONTINUE    (1 << 0)		/*!< Slave Continue Bit */
#define I2C_SLVCTL_SLVNACK        (1 << 1)		/*!< Slave NACK Bit */
#define I2C_SLVCTL_SLVDMA         (1 << 3)		/*!< Slave DMA Enable Bit */

/*
 * @brief I2C Slave Data Mask
 */
#define I2C_SLVDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Slave data mask */

/*
 * @brief I2C Slave Address register Bit definition
 */
#define I2C_SLVADR_SADISABLE      (1 << 0)		/*!< Slave Address n Disable Bit */
#define I2C_SLVADR_SLVADR         (0x7F << 1)	/*!< Slave Address field */
#define I2C_SLVADR_MASK           ((uint32_t) 0x00FF)	/*!< Slave Address Mask */

/*
 * @brief I2C Slave Address Qualifier 0 Register Bit definition
 */
#define I2C_SLVQUAL_QUALMODE0     (1 << 0)		/*!< Slave Qualifier Mode Enable Bit */
#define I2C_SLVQUAL_SLVQUAL0      (0x7F << 1)	/*!< Slave Qualifier Address for Address 0 */

/*
 * @brief I2C Monitor Data Register Bit definition
 */
#define I2C_MONRXDAT_DATA         (0xFF << 0)		/*!< Monitor Function Receive Data Field */
#define I2C_MONRXDAT_MONSTART     (1 << 8)			/*!< Monitor Received Start Bit */
#define I2C_MONRXDAT_MONRESTART   (1 << 9)			/*!< Monitor Received Repeated Start Bit */
#define I2C_MONRXDAT_MONNACK      (1 << 10)			/*!< Monitor Received Nack Bit */

/*
 * @brief I2C Configuration register Bit definition
 */
#define I2C_CFG_MSTEN             (1 << 0)	/*!< Master Enable/Disable Bit */
#define I2C_CFG_SLVEN             (1 << 1)	/*!< Slave Enable/Disable Bit */
#define I2C_CFG_MONEN             (1 << 2)	/*!< Monitor Enable/Disable Bit */
#define I2C_CFG_TIMEOUTEN         (1 << 3)	/*!< Timeout Enable/Disable Bit */
#define I2C_CFG_MONCLKSTR         (1 << 4)	/*!< Monitor Clock Stretching Bit */
#define I2C_CFG_MASK              ((uint32_t) 0x1F)	/*!< Configuration Register Mask */

/*
 * @brief I2C Status register Bit definition
 */
#define I2C_STAT_MSTPENDING       (1 << 0)		/*!< Master Pending Status Bit */
#define I2C_STAT_MSTSTATE         (0x7 << 1)	/*!< Master State Code */
#define I2C_STAT_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Bit */
#define I2C_STAT_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Bit */
#define I2C_STAT_SLVPENDING       (1 << 8)		/*!< Slave Pending Status Bit */
#define I2C_STAT_SLVSTATE         (0x3 << 9)	/*!< Slave State Code */
#define I2C_STAT_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Bit */
#define I2C_STAT_SLVIDX           (0x3 << 12)	/*!< Slave Address Index */
#define I2C_STAT_SLVSEL           (1 << 14)		/*!< Slave Selected Bit */
#define I2C_STAT_SLVDESEL         (1 << 15)		/*!< Slave Deselect Bit */
#define I2C_STAT_MONRDY           (1 << 16)		/*!< Monitor Ready Bit */
#define I2C_STAT_MONOV            (1 << 17)		/*!< Monitor Overflow Flag */
#define I2C_STAT_MONACTIVE        (1 << 18)		/*!< Monitor Active Flag */
#define I2C_STAT_MONIDLE          (1 << 19)		/*!< Monitor Idle Flag */
#define I2C_STAT_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Flag */
#define I2C_STAT_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Flag */

#define I2C_STAT_MSTCODE_IDLE       (0)			/*!< Master Idle State Code */
#define I2C_STAT_MSTCODE_RXREADY    (1)			/*!< Master Receive Ready State Code */
#define I2C_STAT_MSTCODE_TXREADY    (2)			/*!< Master Transmit Ready State Code */
#define I2C_STAT_MSTCODE_NACKADR    (3)			/*!< Master NACK by slave on address State Code */
#define I2C_STAT_MSTCODE_NACKDAT    (4)			/*!< Master NACK by slave on data State Code */

#define I2C_STAT_SLVCODE_ADDR         (0)		/*!< Master Idle State Code */
#define I2C_STAT_SLVCODE_RX           (1)		/*!< Received data is available Code */
#define I2C_STAT_SLVCODE_TX           (2)		/*!< Data can be transmitted Code */

/*
 * @brief I2C Interrupt Enable Set register Bit definition
 */
#define I2C_INTENSET_MSTPENDING       (1 << 0)		/*!< Master Pending Interrupt Enable Bit */
#define I2C_INTENSET_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Interrupt Enable Bit */
#define I2C_INTENSET_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Interrupt Enable Bit */
#define I2C_INTENSET_SLVPENDING       (1 << 8)		/*!< Slave Pending Interrupt Enable Bit */
#define I2C_INTENSET_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Interrupt Enable Bit */
#define I2C_INTENSET_SLVDESEL         (1 << 15)		/*!< Slave Deselect Interrupt Enable Bit */
#define I2C_INTENSET_MONRDY           (1 << 16)		/*!< Monitor Ready Interrupt Enable Bit */
#define I2C_INTENSET_MONOV            (1 << 17)		/*!< Monitor Overflow Interrupt Enable Bit */
#define I2C_INTENSET_MONIDLE          (1 << 19)		/*!< Monitor Idle Interrupt Enable Bit */
#define I2C_INTENSET_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Enable Bit */
#define I2C_INTENSET_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Enable Bit */

/*
 * @brief I2C Interrupt Enable Clear register Bit definition
 */
#define I2C_INTENCLR_MSTPENDING       (1 << 0)		/*!< Master Pending Interrupt Clear Bit */
#define I2C_INTENCLR_MSTRARBLOSS      (1 << 4)		/*!< Master Arbitration Loss Interrupt Clear Bit */
#define I2C_INTENCLR_MSTSTSTPERR      (1 << 6)		/*!< Master Start Stop Error Interrupt Clear Bit */
#define I2C_INTENCLR_SLVPENDING       (1 << 8)		/*!< Slave Pending Interrupt Clear Bit */
#define I2C_INTENCLR_SLVNOTSTR        (1 << 11)		/*!< Slave not stretching Clock Interrupt Clear Bit */
#define I2C_INTENCLR_SLVDESEL         (1 << 15)		/*!< Slave Deselect Interrupt Clear Bit */
#define I2C_INTENCLR_MONRDY           (1 << 16)		/*!< Monitor Ready Interrupt Clear Bit */
#define I2C_INTENCLR_MONOV            (1 << 17)		/*!< Monitor Overflow Interrupt Clear Bit */
#define I2C_INTENCLR_MONIDLE          (1 << 19)		/*!< Monitor Idle Interrupt Clear Bit */
#define I2C_INTENCLR_EVENTTIMEOUT     (1 << 24)		/*!< Event Timeout Interrupt Clear Bit */
#define I2C_INTENCLR_SCLTIMEOUT       (1 << 25)		/*!< SCL Timeout Interrupt Clear Bit */

/*
 * @brief I2C TimeOut Value Macro
 */
#define I2C_TIMEOUT_VAL(n)              (((uint32_t) ((n) - 1) & 0xFFF0) | 0x000F)		/*!< Macro for Timeout value register */

/*
 * @brief I2C Interrupt Status register Bit definition
 */
#define I2C_INTSTAT_MSTPENDING      (1 << 0)		/*!< Master Pending Interrupt Status Bit */
#define I2C_INTSTAT_MSTRARBLOSS     (1 << 4)		/*!< Master Arbitration Loss Interrupt Status Bit */
#define I2C_INTSTAT_MSTSTSTPERR     (1 << 6)		/*!< Master Start Stop Error Interrupt Status Bit */
#define I2C_INTSTAT_SLVPENDING      (1 << 8)		/*!< Slave Pending Interrupt Status Bit */
#define I2C_INTSTAT_SLVNOTSTR       (1 << 11)		/*!< Slave not stretching Clock Interrupt Status Bit */
#define I2C_INTSTAT_SLVDESEL        (1 << 15)		/*!< Slave Deselect Interrupt Status Bit */
#define I2C_INTSTAT_MONRDY          (1 << 16)		/*!< Monitor Ready Interrupt Status Bit */
#define I2C_INTSTAT_MONOV           (1 << 17)		/*!< Monitor Overflow Interrupt Status Bit */
#define I2C_INTSTAT_MONIDLE         (1 << 19)		/*!< Monitor Idle Interrupt Status Bit */
#define I2C_INTSTAT_EVENTTIMEOUT    (1 << 24)		/*!< Event Timeout Interrupt Status Bit */
#define I2C_INTSTAT_SCLTIMEOUT      (1 << 25)		/*!< SCL Timeout Interrupt Status Bit */

/*
 * @brief I2C Master Control register Bit definition
 */
#define I2C_MSTCTL_MSTCONTINUE  (1 << 0)		/*!< Master Continue Bit */
#define I2C_MSTCTL_MSTSTART     (1 << 1)		/*!< Master Start Control Bit */
#define I2C_MSTCTL_MSTSTOP      (1 << 2)		/*!< Master Stop Control Bit */
#define I2C_MSTCTL_MSTDMA       (1 << 3)		/*!< Master DMA Enable Bit */

/*
 * @brief I2C Master Time Register Field definition
 */
#define I2C_MSTTIME_MSTSCLLOW   (0x07 << 0)		/*!< Master SCL Low Time field */
#define I2C_MSTTIME_MSTSCLHIGH  (0x07 << 4)		/*!< Master SCL High Time field */

/*
 * @brief I2C Master Data Mask
 */
#define I2C_MSTDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Master data mask */

/*
 * @brief I2C Slave Control register Bit definition
 */
#define I2C_SLVCTL_SLVCONTINUE    (1 << 0)		/*!< Slave Continue Bit */
#define I2C_SLVCTL_SLVNACK        (1 << 1)		/*!< Slave NACK Bit */
#define I2C_SLVCTL_SLVDMA         (1 << 3)		/*!< Slave DMA Enable Bit */

/*
 * @brief I2C Slave Data Mask
 */
#define I2C_SLVDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Slave data mask */

/*
 * @brief I2C Slave Address register Bit definition
 */
#define I2C_SLVADR_SADISABLE      (1 << 0)		/*!< Slave Address n Disable Bit */
#define I2C_SLVADR_SLVADR         (0x7F << 1)	/*!< Slave Address field */
#define I2C_SLVADR_MASK           ((uint32_t) 0x00FF)	/*!< Slave Address Mask */

/*
 * @brief I2C Slave Address Qualifier 0 Register Bit definition
 */
#define I2C_SLVQUAL_QUALMODE0     (1 << 0)		/*!< Slave Qualifier Mode Enable Bit */
#define I2C_SLVQUAL_SLVQUAL0      (0x7F << 1)	/*!< Slave Qualifier Address for Address 0 */

/*
 * @brief I2C Monitor Data Register Bit definition
 */
#define I2C_MONRXDAT_DATA         (0xFF << 0)		/*!< Monitor Function Receive Data Field */
#define I2C_MONRXDAT_MONSTART     (1 << 8)			/*!< Monitor Received Start Bit */
#define I2C_MONRXDAT_MONRESTART   (1 << 9)			/*!< Monitor Received Repeated Start Bit */
#define I2C_MONRXDAT_MONNACK      (1 << 10)			/*!< Monitor Received Nack Bit */

/**
 * @brief	Initialize I2C Interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	0 - on success; #ERR_FLEXCOMM_FUNCNOTSUPPORTED or #ERR_FLEXCOMM_NOTFREE on failure
 * @note	This function enables the I2C clock for both the master and
 * slave interfaces if the I2C channel.

 */
__STATIC_INLINE int Chip_I2C_Init(LPC_I2C_T *pI2C)
{
	return Chip_FLEXCOMM_Init(pI2C, FLEXCOMM_PERIPH_I2C);
}

/**
 * @brief	Shutdown I2C Interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function disables the I2C clock for both the master and
 * slave interfaces if the I2C channel.
 */
__STATIC_INLINE void Chip_I2C_DeInit(LPC_I2C_T *pI2C)
{
	Chip_FLEXCOMM_DeInit(pI2C);
}

/**
 * @brief	Sets I2C Clock Divider registers
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	clkdiv	: Clock Divider value for I2C, value is between (1 - 65536)
 * @return	Nothing
 * @note	The clock to I2C block is determined by the following formula (I2C_PCLK
 *          is the frequency of the system clock): <br>
 *              I2C Clock Frequency = (I2C_PCLK)/clkdiv;<br>
 * This divider must be setup for both the master and slave modes of the
 * controller.
 */
__STATIC_INLINE void Chip_I2C_SetClockDiv(LPC_I2C_T *pI2C, uint32_t clkdiv)
{
	if ((clkdiv >= 1) && (clkdiv <= 65536)) {
		pI2C->CLKDIV = clkdiv - 1;
	}
	else {
		pI2C->CLKDIV = 0;
	}
}

/**
 * @brief	Get I2C Clock Divider registers
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Clock Divider value
 * @note	Return the divider value for the I2C block
 *          It is the CLKDIV register value + 1
 */
static INLINE uint32_t Chip_I2C_GetClockDiv(LPC_I2C_T *pI2C)
{
	return (pI2C->CLKDIV & 0xFFFF) + 1;
}

/**
 * @brief	Enable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intEn	: ORed Value of I2C_INTENSET_* values to enable
 * @return	Nothing
 */
static INLINE void Chip_I2C_EnableInt(LPC_I2C_T *pI2C, uint32_t intEn)
{
	pI2C->INTENSET = intEn;
}

/**
 * @brief	Disable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intClr	: ORed Value of I2C_INTENSET_* values to disable
 * @return	Nothing
 */
static INLINE void Chip_I2C_DisableInt(LPC_I2C_T *pI2C, uint32_t intClr)
{
	pI2C->INTENCLR = intClr;
}

/**
 * @brief	Disable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intClr	: ORed Value of I2C_INTENSET_* values to disable
 * @return	Nothing
 * @note	It is recommended to use the Chip_I2C_DisableInt() function
 * instead of this function.
 */
static INLINE void Chip_I2C_ClearInt(LPC_I2C_T *pI2C, uint32_t intClr)
{
	Chip_I2C_DisableInt(pI2C, intClr);
}

/**
 * @brief	Returns pending I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	All pending interrupts, mask with I2C_INTENSET_* to determine specific interrupts
 */
static INLINE uint32_t Chip_I2C_GetPendingInt(LPC_I2C_T *pI2C)
{
	return pI2C->INTSTAT;
}

#ifndef __DOXYGEN__

/* I2C0 Defines */
#define LPC_I2C0_BASE        __APPEND3(LPC_FLEXCOMM,I2C0_FLEXCOMM,_BASE)
#define LPC_I2C0             ((LPC_I2C_T *) LPC_I2C0_BASE)
#define I2C0_IRQHandler      __APPEND3(FLEXCOMM,I2C0_FLEXCOMM,_IRQHandler)
#define I2C0_IRQn            __APPEND3(FLEXCOMM,I2C0_FLEXCOMM,_IRQn)
#define DMAREQ_I2C0_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C0_FLEXCOMM,_RX)
#define DMAREQ_I2C0_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C0_FLEXCOMM,_TX)

/* I2C1 Defines */
#define LPC_I2C1_BASE        __APPEND3(LPC_FLEXCOMM,I2C1_FLEXCOMM,_BASE)
#define LPC_I2C1             ((LPC_I2C_T *) LPC_I2C1_BASE)
#define I2C1_IRQHandler      __APPEND3(FLEXCOMM,I2C1_FLEXCOMM,_IRQHandler)
#define I2C1_IRQn            __APPEND3(FLEXCOMM,I2C1_FLEXCOMM,_IRQn)
#define DMAREQ_I2C1_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C1_FLEXCOMM,_RX)
#define DMAREQ_I2C1_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C1_FLEXCOMM,_TX)

/* I2C2 Defines */
#define LPC_I2C2_BASE        __APPEND3(LPC_FLEXCOMM,I2C2_FLEXCOMM,_BASE)
#define LPC_I2C2             ((LPC_I2C_T *) LPC_I2C2_BASE)
#define I2C2_IRQHandler      __APPEND3(FLEXCOMM,I2C2_FLEXCOMM,_IRQHandler)
#define I2C2_IRQn            __APPEND3(FLEXCOMM,I2C2_FLEXCOMM,_IRQn)
#define DMAREQ_I2C2_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C2_FLEXCOMM,_RX)
#define DMAREQ_I2C2_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C2_FLEXCOMM,_TX)

/* I2C3 Defines */
#define LPC_I2C3_BASE        __APPEND3(LPC_FLEXCOMM,I2C3_FLEXCOMM,_BASE)
#define LPC_I2C3             ((LPC_I2C_T *) LPC_I2C3_BASE)
#define I2C3_IRQHandler      __APPEND3(FLEXCOMM,I2C3_FLEXCOMM,_IRQHandler)
#define I2C3_IRQn            __APPEND3(FLEXCOMM,I2C3_FLEXCOMM,_IRQn)
#define DMAREQ_I2C3_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C3_FLEXCOMM,_RX)
#define DMAREQ_I2C3_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C3_FLEXCOMM,_TX)

/* I2C4 Defines */
#define LPC_I2C4_BASE        __APPEND3(LPC_FLEXCOMM,I2C4_FLEXCOMM,_BASE)
#define LPC_I2C4             ((LPC_I2C_T *) LPC_I2C4_BASE)
#define I2C4_IRQHandler      __APPEND3(FLEXCOMM,I2C4_FLEXCOMM,_IRQHandler)
#define I2C4_IRQn            __APPEND3(FLEXCOMM,I2C4_FLEXCOMM,_IRQn)
#define DMAREQ_I2C4_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C4_FLEXCOMM,_RX)
#define DMAREQ_I2C4_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C4_FLEXCOMM,_TX)

/* I2C5 Defines */
#define LPC_I2C5_BASE        __APPEND3(LPC_FLEXCOMM,I2C5_FLEXCOMM,_BASE)
#define LPC_I2C5             ((LPC_I2C_T *) LPC_I2C5_BASE)
#define I2C5_IRQHandler      __APPEND3(FLEXCOMM,I2C5_FLEXCOMM,_IRQHandler)
#define I2C5_IRQn            __APPEND3(FLEXCOMM,I2C5_FLEXCOMM,_IRQn)
#define DMAREQ_I2C5_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C5_FLEXCOMM,_RX)
#define DMAREQ_I2C5_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C5_FLEXCOMM,_TX)

/* I2C6 Defines */
#define LPC_I2C6_BASE        __APPEND3(LPC_FLEXCOMM,I2C6_FLEXCOMM,_BASE)
#define LPC_I2C6             ((LPC_I2C_T *) LPC_I2C6_BASE)
#define I2C6_IRQHandler      __APPEND3(FLEXCOMM,I2C6_FLEXCOMM,_IRQHandler)
#define I2C6_IRQn            __APPEND3(FLEXCOMM,I2C6_FLEXCOMM,_IRQn)
#define DMAREQ_I2C6_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C6_FLEXCOMM,_RX)
#define DMAREQ_I2C6_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C6_FLEXCOMM,_TX)

/* I2C7 Defines */
#define LPC_I2C7_BASE        __APPEND3(LPC_FLEXCOMM,I2C7_FLEXCOMM,_BASE)
#define LPC_I2C7             ((LPC_I2C_T *) LPC_I2C7_BASE)
#define I2C7_IRQHandler      __APPEND3(FLEXCOMM,I2C7_FLEXCOMM,_IRQHandler)
#define I2C7_IRQn            __APPEND3(FLEXCOMM,I2C7_FLEXCOMM,_IRQn)
#define DMAREQ_I2C7_SLAVE    __APPEND3(DMAREQ_FLEXCOMM,I2C7_FLEXCOMM,_RX)
#define DMAREQ_I2C7_MASTER   __APPEND3(DMAREQ_FLEXCOMM,I2C7_FLEXCOMM,_TX)

#endif

/**
 * @}
 */

 #ifdef __cplusplus
}
#endif

#endif /* __I2C_COMMON_5411X_H_ */
