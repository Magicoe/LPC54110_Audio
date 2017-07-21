/*
 * @brief LPC5411X clock driver
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

#include "chip.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Frequency table * 10000 + 600000 */
#define WDT_FREQ_LOOKUP \
	"\x0\x0F\x1E\x28\x3C\x46\x50\x5A\x64\x6E"\
	"\x78\x82\x8C\x91\x96\xA0\xA5\xAA\xB4\xB9"\
	"\xBE\xC8\xCD\xD2\xDC\xE1\xE6\xEB\xF0\xF5"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
//WEAK uint32_t mclk_in_rate = 0;
uint32_t mclk_in_rate = 0;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Return asynchronous APB clock rate (no regard for divider) */
static uint32_t Chip_Clock_GetAsyncSyscon_ClockRate_NoDiv(void)
{
	CHIP_ASYNC_SYSCON_SRC_T src;
	uint32_t clkRate;

	src = Chip_Clock_GetAsyncSysconClockSource();
	switch (src) {

	case SYSCON_ASYNC_FRO12MHZ:
		clkRate = SYSCON_FRO12MHZ_FREQ;
		break;

	case SYSCON_ASYNC_MAINCLK:
		clkRate = Chip_Clock_GetMainClockRate();
		break;

	default:
		clkRate = 0;
		break;
	}

	return clkRate;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Return main A clock rate */
uint32_t Chip_Clock_GetMain_A_ClockRate(void)
{
	uint32_t clkRate = 0;

	switch (Chip_Clock_GetMain_A_ClockSource()) {
	case SYSCON_MAIN_A_CLKSRC_FRO12MHZ:
		clkRate = SYSCON_FRO12MHZ_FREQ;
		break;

	case SYSCON_MAIN_A_CLKSRCA_CLKIN:
		clkRate = Chip_Clock_GetExtClockInRate();
		break;

	case SYSCON_MAIN_A_CLKSRCA_WDTOSC:
		clkRate = Chip_Clock_GetWDTOSCRate();
		break;

	case SYSCON_MAIN_A_CLKSRCA_FROHF:
		clkRate = Chip_Clock_GetFROHFRate();
		break;

	default:
		clkRate = 0;
		break;
	}

	return clkRate;
}

/* Return main B clock rate */
uint32_t Chip_Clock_GetMain_B_ClockRate(void)
{
	uint32_t clkRate = 0;

	switch (Chip_Clock_GetMain_B_ClockSource()) {
	case SYSCON_MAIN_B_CLKSRC_MAINCLKSELA:
		clkRate = Chip_Clock_GetMain_A_ClockRate();
		break;

	case SYSCON_MAIN_B_CLKSRC_PLL:
		clkRate = Chip_Clock_GetSystemPLLOutClockRate(false);
		break;

	case SYSCON_MAIN_B_CLKSRC_RTC:
		clkRate = Chip_Clock_GetRTCOscRate();
		break;
	}

	return clkRate;
}


/* Enable a system or peripheral clock */
void Chip_Clock_EnablePeriphClock(CHIP_SYSCON_CLOCK_T clk)
{
	uint32_t clkEnab = (uint32_t) clk;

	if (clkEnab >= 128) {
		clkEnab = clkEnab - 128;

		LPC_ASYNC_SYSCON->ASYNCAPBCLKCTRLSET |= (1 << clkEnab);
	}
	else if (clkEnab >= 32) {
		LPC_SYSCON->AHBCLKCTRLSET[1] |= (1 << (clkEnab - 32));
	}
	else {
		LPC_SYSCON->AHBCLKCTRLSET[0] |= (1 << clkEnab);
	}
}

/* Disable a system or peripheral clock */
void Chip_Clock_DisablePeriphClock(CHIP_SYSCON_CLOCK_T clk)
{
	uint32_t clkEnab = (uint32_t) clk;

	if (clkEnab >= 128) {
		clkEnab = clkEnab - 128;

		LPC_ASYNC_SYSCON->ASYNCAPBCLKCTRLCLR = (1 << clkEnab);
	}
	else if (clkEnab >= 32) {
		LPC_SYSCON->AHBCLKCTRLCLR[1] = (1 << (clkEnab - 32));
	}
	else {
		LPC_SYSCON->AHBCLKCTRLCLR[0] = (1 << clkEnab);
	}
}

/* Returns the system tick rate as used with the system tick divider */
uint32_t Chip_Clock_GetSysTickClockRate(void)
{
	uint32_t sysRate, div;

	div = LPC_SYSCON->SYSTICKCLKDIV;

	/* If divider is 0, the system tick clock is disabled */
	if (div == 0) {
		sysRate = 0;
	}
	else {
		sysRate = Chip_Clock_GetSystemClockRate() / LPC_SYSCON->SYSTICKCLKDIV;
	}

	return sysRate;
}

/* Return ADC clock rate */
uint32_t Chip_Clock_GetADCClockRate(void)
{
	uint32_t div, clkRate = 0;

	div = Chip_Clock_GetADCClockDiv();

	/* ADC clock only enabled if div>0 */
	if (div > 0) {
		switch (Chip_Clock_GetADCClockSource()) {
		case SYSCON_ADCCLKSELSRC_MAINCLK:
			clkRate = Chip_Clock_GetMainClockRate();
			break;

		case SYSCON_ADCCLKSELSRC_SYSPLLOUT:
			clkRate = Chip_Clock_GetSystemPLLOutClockRate(false);
			break;

		case SYSCON_ADCCLKSELSRC_FROHF:
			clkRate = Chip_Clock_GetFROHFRate();
			break;
		}

		clkRate = clkRate / div;
	}

	return clkRate;
}

/* Return asynchronous APB clock rate */
uint32_t Chip_Clock_GetAsyncSyscon_ClockRate(void)
{
	uint32_t clkRate;

	clkRate = Chip_Clock_GetAsyncSyscon_ClockRate_NoDiv();

	return clkRate;
}

/* Returns the main clock source */
CHIP_SYSCON_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void)
{
	CHIP_SYSCON_MAIN_B_CLKSRC_T srcB;
	uint32_t clkSrc;

	/* Get main B clock source */
	srcB = Chip_Clock_GetMain_B_ClockSource();
	if (srcB == SYSCON_MAIN_B_CLKSRC_MAINCLKSELA) {
		/* Using source A, so return source A */
		clkSrc = (uint32_t) Chip_Clock_GetMain_A_ClockSource();
	}
	else {
		/* Using source B */
		clkSrc = 4 + (uint32_t) srcB;
	}

	return (CHIP_SYSCON_MAINCLKSRC_T) clkSrc;
}

/* Return main clock rate */
uint32_t Chip_Clock_GetMainClockRate(void)
{
	uint32_t clkRate;

	if (Chip_Clock_GetMain_B_ClockSource() == SYSCON_MAIN_B_CLKSRC_MAINCLKSELA) {
		/* Return main A clock rate */
		clkRate = Chip_Clock_GetMain_A_ClockRate();
	}
	else {
		/* Return main B clock rate */
		clkRate = Chip_Clock_GetMain_B_ClockRate();
	}

	return clkRate;
}

/* Return system clock rate */
uint32_t Chip_Clock_GetSystemClockRate(void)
{
	/* No point in checking for divide by 0 */
	return Chip_Clock_GetMainClockRate() / ((LPC_SYSCON->AHBCLKDIV & 0xFF) + 1);
}

/* Get UART base rate */
uint32_t Chip_Clock_GetFRGClockRate(void)
{
	uint64_t inclk;

	/* Get clock rate into FRG */
	inclk = (uint64_t) Chip_Clock_GetAsyncSyscon_ClockRate();

	if (inclk != 0) {
		uint32_t mult, divmult;

		divmult = LPC_SYSCON->FRGCTRL;
		if ((divmult & 0xFF) == 0xFF) {
			/* Fractional part is enabled, get multiplier */
			mult = (divmult >> 8) & 0xFF;

			/* Get fractional error */
			inclk = (inclk * 256) / (uint64_t) (256 + mult);
		}
	}

	return (uint32_t) inclk;
}

/* Get the base clock frequency of Fractional divider */
uint32_t Chip_Clock_GetFRGInClockRate(void)
{
	uint32_t inclk;

	/* Detect the input clock frequency */
	CHIP_SYSCON_FRGCLKSRC_T src = Chip_Clock_GetFRGClockSource();
	switch(src) {
		case SYSCON_FRGCLKSRC_MAINCLK:
			inclk = Chip_Clock_GetMainClockRate();
			break;

		case SYSCON_FRGCLKSRC_PLL:
			inclk = Chip_Clock_GetSystemPLLOutClockRate(false);
			break;

		case SYSCON_FRGCLKSRC_FRO12MHZ:
			inclk = SYSCON_FRO12MHZ_FREQ;
			break;

		case SYSCON_FRGCLKSRC_FROHF:
			inclk = Chip_Clock_GetFROHFRate();
			break;

		default:
			return 0;
	}
	return inclk;
}

/* Set UART base rate */
uint32_t Chip_Clock_SetFRGClockRate(uint32_t rate)
{

	uint32_t div, inclk, err;
	uint64_t uart_fra_multiplier;

	/* Input clock into FRG block is the main system cloock */
	inclk = Chip_Clock_GetFRGInClockRate();
	if (!inclk) {
		return 0;
	}

	/* Get integer divider for coarse rate */
	div = inclk / rate;
	if (div == 0) {
		div = 1;
	}

	err = inclk - (rate * div);
	uart_fra_multiplier = (((uint64_t) err + (uint64_t) rate) * 256) / (uint64_t) (rate * div);

	/* Enable fractional divider and set multiplier */
	LPC_SYSCON->FRGCTRL = 0xFF | (uart_fra_multiplier << 8);

	return Chip_Clock_GetFRGClockRate();
}

/* Get the MCLK clock rate */
uint32_t Chip_Clock_GetMCLKClockRate(void)
{
	uint32_t clkRate = 0;
	uint32_t div = Chip_Clock_GetMCLKDiv();
	CHIP_SYSCON_MCLKSRC_T src = Chip_Clock_GetMCLKSource();

	switch (src) {
	case SYSCON_MCLKSRC_FROHF:								/*!< HF-FRO 48MHz or 96MHz */
		clkRate = Chip_Clock_GetFROHFRate();
		break;

	case SYSCON_MCLKSRC_PLL:								/*!< Main pll */
		clkRate = Chip_Clock_GetSystemPLLOutClockRate(false);
		break;

	case SYSCON_MCLKSRC_MCLKIN:								/*!< MCLK INPUT Clock pin set by IOCON */
		clkRate = mclk_in_rate;
		break;

	case SYSCON_MCLKSRC_DISABLED:							/*!< Disable clock source to MCLK */
		break;												/* return 0 */
	}
	return clkRate/div;
}

/* Get the clock rate at which FlexCOMM is operating now */
uint32_t Chip_Clock_GetFLEXCOMMClockRate(uint32_t id)
{
	uint32_t clk_rate = 0;
	CHIP_SYSCON_FLEXCOMMCLKSELSRC_T src;

	/* Check if the id is valid */
	if (id > 7) {
		return 0;
	}

	src = Chip_Clock_GetFLEXCOMMClockSource(id);
	switch(src) {
		case SYSCON_FLEXCOMMCLKSELSRC_FRO12MHZ:
			clk_rate = SYSCON_FRO12MHZ_FREQ;
			break;
		case SYSCON_FLEXCOMMCLKSELSRC_FROHF:
			clk_rate = Chip_Clock_GetFROHFRate();
			break;
		case SYSCON_FLEXCOMMCLKSELSRC_PLL:
			clk_rate = Chip_Clock_GetSystemPLLOutClockRate(false);
			break;
		case SYSCON_FLEXCOMMCLKSELSRC_MCLK:
			clk_rate = Chip_Clock_GetMCLKClockRate();
			break;
		case SYSCON_FLEXCOMMCLKSELSRC_FRG:
			clk_rate = Chip_Clock_GetFRGClockRate();
			break;
		default:
			break;
	}

	return clk_rate;
}

/* Get Watchdog OSC Frequency */
uint32_t Chip_Clock_GetWDTOSCRate(void)
{
	uint32_t val = LPC_SYSCON->WDTOSCCTRL, idx, freq;
	idx = (val >> 5) & 0x1F;
	if (!idx) return 0;
	freq = idx == 1 ? 400000 : (WDT_FREQ_LOOKUP[idx - 2] & 0xFF) * 10000 + 600000;
	return freq / (((val & 0x1F) + 1) * 2);
}
