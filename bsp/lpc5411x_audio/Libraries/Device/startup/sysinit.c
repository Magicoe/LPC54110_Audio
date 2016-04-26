/*
 * @brief Common SystemInit function for LPC54xxx chips
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
/* Clock rate on the CLKIN pin */
const uint32_t ExtClockIn = 0;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

LPC_ASYNC_SYSCON_T* g_ASYNC_SYSCON;
LPC_SYSCON_T *g_LPC_SYSCON;
/* Set up and initialize hardware prior to call to main */
void SystemInit(void)
{
	g_ASYNC_SYSCON = LPC_ASYNC_SYSCON;
	Chip_SYSCON_PowerUp(SYSCON_PDRUNCFG_PD_SRAM0 | SYSCON_PDRUNCFG_PD_SRAM1 | SYSCON_PDRUNCFG_PD_SRAM2|SYSCON_PDRUNCFG_PD_SRAMX);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAM1);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAM2);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAMX);
#if defined(__CODE_RED)
	extern void(*const g_pfnVectors[]) (void);
	SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
	//extern void *__Vectors;
	//SCB->VTOR = (uint32_t) &isr_vector;
	SCB->VTOR  = 0x00000000 & 0x3FFFFF80;
#endif

//#if defined(CORE_M4)
//#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
	fpuInit();
//#endif
//#endif

#if !defined(__MULTICORE_M0SLAVE) && !defined(__MULTICORE_M4SLAVE)
	/* Chip specific SystemInit */
	Chip_SystemInit();
#endif
	g_ASYNC_SYSCON = LPC_ASYNC_SYSCON;
	Chip_SYSCON_PowerUp(SYSCON_PDRUNCFG_PD_SRAM0 | SYSCON_PDRUNCFG_PD_SRAM1 | SYSCON_PDRUNCFG_PD_SRAM2|SYSCON_PDRUNCFG_PD_SRAMX);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAM1);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAM2);
	Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_SRAMX);
}
