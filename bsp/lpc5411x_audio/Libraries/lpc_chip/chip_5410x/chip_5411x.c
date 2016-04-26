/*
 * @brief LPC5411X Miscellaneous chip specific functions
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

/* System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Update system core clock rate, should be called if the system has
   a clock rate change */
void SystemCoreClockUpdate(void)
{
	/* CPU core speed (main clock speed adjusted by system clock divider) */
	SystemCoreClock = Chip_Clock_GetSystemClockRate();
}

void Chip_USB_Init(void)
{
	uint32_t div = 1;
	/* Turn ON FRO */
	Chip_SYSCON_PowerUp(SYSCON_PDRUNCFG_PD_FRO);

	/* Turn ON FRO HF and let it adjust TRIM value based on USB SOF */
	LPC_SYSCON->FROCTRL = (LPC_SYSCON->FROCTRL & ~SYSCON_FROCTRL_MASK) |
		SYSCON_FROCTRL_HSPDCLK | SYSCON_FROCTRL_USBCLKADJ;

	/* If we are running at 96 MHz we must use USBCLKDIV to
	 * bring frequency down to 48MHz */
	if (Chip_Clock_GetFROHFRate() == SYSCON_FRO96MHZ_FREQ) {
		div = 2;
	}

	/* Set the USB Clock source to 96 MHz FRO */
	Chip_Clock_SetUSBClockSource(SYSCON_USBCLKSRC_FROHF, div);

	/* Enable USB Peripheral clock */
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_USB);

	/* Enable waking-up of MCU from USB */
	Chip_SYSCON_EnableWakeup(SYSCON_STARTER_USB);

	/* Power on USB PHY */
	Chip_SYSCON_PowerUp(SYSCON_PDRUNCFG_PD_USB_PHY);

	/* Reset the USB peripheral */
	Chip_SYSCON_PeriphReset(RESET_USB);
}
