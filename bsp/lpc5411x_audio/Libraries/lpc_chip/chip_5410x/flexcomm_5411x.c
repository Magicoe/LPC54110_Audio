/*
 * @brief LPC5411X FLEXCOMM specific functions
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

/*****************************************************************************
 * Public functions
 ****************************************************************************/

 /* Get the index corresponding to the flexcomm */
int Chip_FLEXCOMM_GetIndex(LPC_FLEXCOMM_T *pFCOMM)
{
	 switch ((uint32_t) pFCOMM) {
		case LPC_FLEXCOMM0_BASE:
			 return 0;
		case LPC_FLEXCOMM1_BASE:
			 return 1;
		case LPC_FLEXCOMM2_BASE:
			 return 2;
		case LPC_FLEXCOMM3_BASE:
			 return 3;
		case LPC_FLEXCOMM4_BASE:
			 return 4;
		case LPC_FLEXCOMM5_BASE:
			 return 5;
		case LPC_FLEXCOMM6_BASE:
			 return 6;
		case LPC_FLEXCOMM7_BASE:
			return 7;
		default:
			return ERR_FLEXCOMM_INVALIDBASE;
	}
}

/* Initialize FlexCOMM to a given peripheral */
int Chip_FLEXCOMM_Init(LPC_FLEXCOMM_T *pFCOMM, FLEXCOMM_PERIPH_T periph)
{
	int ret;
	int idx = Chip_FLEXCOMM_GetIndex(pFCOMM);

	if (idx < 0)
		return idx;

	/* Enable the peripheral clock */
	Chip_Clock_EnablePeriphClock((CHIP_SYSCON_CLOCK_T) (SYSCON_CLOCK_FLEXCOMM0 + idx));

	/* Reset FlexCOMM */
	Chip_SYSCON_PeriphReset((CHIP_SYSCON_PERIPH_RESET_T) (RESET_FLEXCOMM0 + idx));

	/* Set the FLEXCOMM to given peripheral */
	ret = Chip_FLEXCOMM_SetPeriph(pFCOMM, periph, 0);
	if (ret) {
		return ret;
	}

	/* By default enable wakeup from this peripheral */
	Chip_SYSCON_EnableWakeup((CHIP_SYSCON_WAKEUP_T) (SYSCON_STARTER_FLEXCOMM0 + idx));

	/* Set a default source for this flexcomm */
	Chip_Clock_SetFLEXCOMMClockSource(idx, SYSCON_FLEXCOMMCLKSELSRC_FRO12MHZ);

	return 0;
}

/* Initialize FlexCOMM to a given peripheral */
void Chip_FLEXCOMM_DeInit(LPC_FLEXCOMM_T *pFCOMM)
{
	int idx = Chip_FLEXCOMM_GetIndex(pFCOMM);
	if (idx < 0)
		return ;


	/* Disable source clock to this flexcomm */
	Chip_Clock_SetFLEXCOMMClockSource(idx, SYSCON_FLEXCOMMCLKSELSRC_NONE);

	/* Disable wakeup from this FlexCOMM */
	Chip_SYSCON_DisableWakeup((CHIP_SYSCON_WAKEUP_T) (SYSCON_STARTER_FLEXCOMM0 + idx));

	if (Chip_FLEXCOMM_IsLocked(pFCOMM)) {
		/* Reset FlexCOMM */
		Chip_SYSCON_PeriphReset((CHIP_SYSCON_PERIPH_RESET_T) (RESET_FLEXCOMM0 + idx));
	}
	Chip_FLEXCOMM_SetPeriph(pFCOMM, FLEXCOMM_PERIPH_NONE, 0);
	Chip_Clock_DisablePeriphClock((CHIP_SYSCON_CLOCK_T) (SYSCON_CLOCK_FLEXCOMM0 + idx));
}

/* Set a given flexcomm to a function */
int Chip_FLEXCOMM_SetPeriph(LPC_FLEXCOMM_T *pFCOMM, FLEXCOMM_PERIPH_T periph, int lock)
{
	volatile uint32_t *psel = &((volatile uint32_t *)pFCOMM)[FLEXCOMM_PSEL_OFFSET / 4];
	int fnum = (int) periph - 1;

	if (periph) {
		if (fnum == 4)
			fnum --;
		if (!(*psel & (0x10 << fnum)))
			return ERR_FLEXCOMM_FUNCNOTSUPPORTED;
	}

	/* Check if the flexcomm is already locked */
	if ((*psel & FLEXCOMM_LOCK) || (*psel & 7))
		return ERR_FLEXCOMM_NOTFREE;

	/* Check if we are asked to lock */
	if (lock)
		*psel = (uint32_t) periph | FLEXCOMM_LOCK;
	else
		*psel = (uint32_t) periph;

	return 0;
}

