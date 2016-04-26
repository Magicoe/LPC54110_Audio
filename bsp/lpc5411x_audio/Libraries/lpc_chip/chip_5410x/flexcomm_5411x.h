/*
 * @brief LPC5411X FLEXCOMM driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef __FLEXCOMM_5411X_H_
#define __FLEXCOMM_5411X_H_

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup FLEXCOMM_5411X CHIP: LPC5411X flexcomm API
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */
typedef void LPC_FLEXCOMM_T;

/** @brief	FLEXCOMM Peripheral functions */
typedef enum {
	FLEXCOMM_PERIPH_NONE,      /*!< No peripheral */
	FLEXCOMM_PERIPH_USART,     /*!< USART peripheral */
	FLEXCOMM_PERIPH_SPI,       /*!< SPI Peripheral */
	FLEXCOMM_PERIPH_I2C,       /*!< I2C Peripheral */
	FLEXCOMM_PERIPH_I2S_TX,    /*!< I2S TX Peripheral */
	FLEXCOMM_PERIPH_I2S_RX,    /*!< I2S RX Peripheral */
} FLEXCOMM_PERIPH_T;

/** @brief	FlexCOMM PSEL register bits */
#define FLEXCOMM_LOCK         (1 << 3)       /*!< Lock Bit */
#define FLEXCOMM_ID_USART     (1 << 4)       /*!< USART Support bit */
#define FLEXCOMM_ID_SPI       (1 << 5)       /*!< SPI Support bit */
#define FLEXCOMM_ID_I2C       (1 << 6)       /*!< I2C Support bit */
#define FLEXCOMM_ID_I2S       (1 << 7)       /*!< I2S Support bit */

/**	@brief Flexcomm error and offset values */
#define ERR_FLEXCOMM_FUNCNOTSUPPORTED     -1       /*!< Selected flexcomm does not support the function desired */
#define ERR_FLEXCOMM_NOTFREE              -2       /*!< FlexCOMM is not free (used as a different peripheral) */
#define ERR_FLEXCOMM_INVALIDBASE          -3       /*!< Invalid flexcomm base address */
#define FLEXCOMM_PSEL_OFFSET              0xFF8   /*!< Offset of the flexcomm PSEL register */

/**
 * @brief	Get currently enabled FLEXCOMM function
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @return	Enabled flexcomm peripheral (See #FLEXCOMM_PERIPH_T)
 */
__STATIC_INLINE FLEXCOMM_PERIPH_T Chip_FLEXCOMM_GetFunc(LPC_FLEXCOMM_T *pFCOMM)
{
	return (FLEXCOMM_PERIPH_T)(((volatile uint32_t *) pFCOMM)[FLEXCOMM_PSEL_OFFSET / 4] & 7);
}

/**
 * @brief	Checks if given FLEXCOMM is locked to a function
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @return	1 - FLEXCOMM is locked to a function; 0 - FLEXCOMM is not locked
 */
__STATIC_INLINE int Chip_FLEXCOMM_IsLocked(LPC_FLEXCOMM_T *pFCOMM)
{
	return (((volatile uint32_t *) pFCOMM)[FLEXCOMM_PSEL_OFFSET / 4] & FLEXCOMM_LOCK) != 0;
}

/**
 * @brief	Lock FLEXCOMM to a function
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @return	Nothing
 * @note	Once the FLEXCOMM is locked, it can only be unlocked by a reset
 */
__STATIC_INLINE void Chip_FLEXCOMM_Lock(LPC_FLEXCOMM_T *pFCOMM)
{
	volatile uint32_t *psel = &((volatile uint32_t *)pFCOMM)[FLEXCOMM_PSEL_OFFSET / 4];
	if (!(*psel & FLEXCOMM_LOCK))
		*psel = (*psel & 0xF) | FLEXCOMM_LOCK;
}

/**
 * @brief	Set FLEXCOMM to a peripheral function
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @param	periph	: Selected peripheral (See #FLEXCOMM_PERIPH_T)
 * @param	lock	: 1 - Flexcomm will be locked as given peripheral, 0 - Do not lock
 * @sa		Chip_FLEXCOMM_Init()
 * @return	0 on success, #ERR_FLEXCOMM_FUNCNOTSUPPORTED when the given FlexComm does not
 * support peripheral provided by @a periph, #ERR_FLEXCOMM_NOTFREE when the flexcomm is
 * being used already as a peripheral.
 * @note	Once the FLEXCOMM is locked, it can only be unlocked by a reset
 */
int Chip_FLEXCOMM_SetPeriph(LPC_FLEXCOMM_T *pFCOMM, FLEXCOMM_PERIPH_T periph, int lock);

/**
 * @brief	Get index of the FLEXCOMM corresponding to the given base address
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @return	Index of FLEXCOMM, #ERR_FLEXCOMM_INVALIDBASE - when base address is invalid
 */
int Chip_FLEXCOMM_GetIndex(LPC_FLEXCOMM_T *pFCOMM);

/**
 * @brief	Initialize FlexCOMM and associate it with a given peripheral
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @param	periph	: Peripheral to set the FlexCOMM to
 * @return	0 on success, #ERR_FLEXCOMM_FUNCNOTSUPPORTED when the given FlexComm does not
 * support peripheral provided by @a periph, #ERR_FLEXCOMM_NOTFREE when the flexcomm is
 * being used already as a peripheral.
 */
int Chip_FLEXCOMM_Init(LPC_FLEXCOMM_T *pFCOMM, FLEXCOMM_PERIPH_T periph);

/**
 * @brief	Uninitialize the FlexCOMM
 * @param	pFCOMM	: Base address of the flexcomm peripheral
 * @return	Nothing
 */
void Chip_FLEXCOMM_DeInit(LPC_FLEXCOMM_T *pFCOMM);

 /**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __FLEXCOMM_5411X_H_ */
