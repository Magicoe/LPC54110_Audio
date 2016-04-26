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

#ifndef __CLOCK_5411X_H_
#define __CLOCK_5411X_H_

#include "pll_5411x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CLOCK_5411X CHIP: LPC5411X Clock Driver
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

/* Internal oscillator frequency */
#define SYSCON_FRO12MHZ_FREQ     (12000000)
#define SYSCON_FRO48MHZ_FREQ     (48000000)
#define SYSCON_FRO96MHZ_FREQ     (96000000)
#define SYSCON_WDTOSC_FREQ       (500000)
#define SYSCON_RTC_FREQ          (32768)


#define Chip_Clock_GetIntOscRate()      SYSCON_FRO12MHZ_FREQ

/**
 * @brief	Returns the external clock input rate
 * @return	External clock input rate
 */
__STATIC_INLINE uint32_t Chip_Clock_GetExtClockInRate(void)
{
	return ExtClockIn;
}

/**
 * @brief	Returns the RTC clock rate
 * @return	RTC oscillator clock rate in Hz
 */
__STATIC_INLINE uint32_t Chip_Clock_GetRTCOscRate(void)
{
	return SYSCON_RTC_FREQ;
}

/** @brief	WDT Osc frequency value table */
typedef enum {
	WDT_FREQ_RESERVED, /*!< Reserved value */
	WDT_FREQ_400000,   /*!< WDT Freq 400 KHz */
	WDT_FREQ_600000,   /*!< WDT Freq 600 KHz */
	WDT_FREQ_750000,   /*!< WDT Freq 750 KHz */
	WDT_FREQ_900000,   /*!< WDT Freq 900 KHz */
	WDT_FREQ_1000000,  /*!< WDT Freq 1.0 MHz */
	WDT_FREQ_1200000,  /*!< WDT Freq 1.2 MHz */
	WDT_FREQ_1300000,  /*!< WDT Freq 1.3 MHz */
	WDT_FREQ_1400000,  /*!< WDT Freq 1.4 MHz */
	WDT_FREQ_1500000,  /*!< WDT Freq 1.5 MHz */
	WDT_FREQ_1600000,  /*!< WDT Freq 1.6 MHz */
	WDT_FREQ_1700000,  /*!< WDT Freq 1.7 MHz */
	WDT_FREQ_1800000,  /*!< WDT Freq 1.8 MHz */
	WDT_FREQ_1900000,  /*!< WDT Freq 1.9 MHz */
	WDT_FREQ_2000000,  /*!< WDT Freq 2.0 MHz */
	WDT_FREQ_2050000,  /*!< WDT Freq 2.05 MHz */
	WDT_FREQ_2100000,  /*!< WDT Freq 2.1 MHz */
	WDT_FREQ_2200000,  /*!< WDT Freq 2.2 MHz */
	WDT_FREQ_2250000,  /*!< WDT Freq 2.25 MHz */
	WDT_FREQ_2300000,  /*!< WDT Freq 2.3 MHz */
	WDT_FREQ_2400000,  /*!< WDT Freq 2.4 MHz */
	WDT_FREQ_2450000,  /*!< WDT Freq 2.45 MHz */
	WDT_FREQ_2500000,  /*!< WDT Freq 2.5 MHz */
	WDT_FREQ_2600000,  /*!< WDT Freq 2.6 MHz */
	WDT_FREQ_2650000,  /*!< WDT Freq 2.65 MHz */
	WDT_FREQ_2700000,  /*!< WDT Freq 2.7 MHz */
	WDT_FREQ_2800000,  /*!< WDT Freq 2.8 MHz */
	WDT_FREQ_2850000,  /*!< WDT Freq 2.85 MHz */
	WDT_FREQ_2900000,  /*!< WDT Freq 2.9 MHz */
	WDT_FREQ_2950000,  /*!< WDT Freq 2.95 MHz */
	WDT_FREQ_3000000,  /*!< WDT Freq 3.0 MHz */
	WDT_FREQ_3050000,  /*!< WDT Freq 3.05 MHz */
} WDT_OSC_FREQ_T;

/**
 * @brief	Set the WDT Oscillator frequency and divider
 * @param	freq	: WDT OSC Frequency to set [See #WDT_OSC_FREQ_T]
 * @param	div		: Divider value [Valid values are 2, 4, 6, 8 ... 64]
 * @return	Nothing
 * @note	The actual frequency of the WDT Oscillator can be +/- 40% of
 * frequency set in @a freq.
 */
__STATIC_INLINE void Chip_Clock_SetWDTOSCRate(WDT_OSC_FREQ_T freq, uint32_t div)
{
	LPC_SYSCON->WDTOSCCTRL = (freq << 5) | (((div >> 1) - 1) & 0x1F);
}

/**
 * @brief	Return estimated watchdog oscillator rate
 * @return	Estimated watchdog oscillator rate
 * @note	This rate is accurate to plus or minus 40%.
 */
uint32_t Chip_Clock_GetWDTOSCRate(void);

/**
 * Clock source selections for only the main A system clock. The main A system
 * clock is used as an input into the main B system clock selector. Main clock A
 * only needs to be setup if the main clock A input is used in the main clock
 * system selector.
 */
typedef enum {
	SYSCON_MAIN_A_CLKSRC_FRO12MHZ = 0,  /*!< 12MHz FRO */
	SYSCON_MAIN_A_CLKSRCA_CLKIN,        /*!< Crystal (main) oscillator in */
	SYSCON_MAIN_A_CLKSRCA_WDTOSC,       /*!< Watchdog oscillator rate */
	SYSCON_MAIN_A_CLKSRCA_FROHF,        /*!< 48MHz or 96MHz HF-FRO */
} CHIP_SYSCON_MAIN_A_CLKSRC_T;

/**
 * @brief	Gets the HF-FRO Frequency rate
 * @return	Nothing
 */
__STATIC_INLINE uint32_t Chip_Clock_GetFROHFRate(void)
{
	if (LPC_SYSCON->FROCTRL & SYSCON_FROCTRL_SEL96MHZ) {
		return SYSCON_FRO96MHZ_FREQ;
	} else {
		return SYSCON_FRO48MHZ_FREQ;
	}
}

/**
 * @brief	Sets the High Frequency FRO rate to (48MHz or 96MHz)
 * @param	freq	: Input frequency (must be one of #SYSCON_FRO48MHZ_FREQ or #SYSCON_FRO96MHZ_FREQ)
 * @return	Nothing
 * @note	This API turns on the FRO-HF (output) if it was not turned on before calling the API.
 */
__STATIC_INLINE void Chip_Clock_SetFROHFRate(uint32_t freq)
{
	uint32_t val = (LPC_SYSCON->FROCTRL & ~SYSCON_FROCTRL_MASK) |
					SYSCON_FROCTRL_WRTRIM | SYSCON_FROCTRL_HSPDCLK;
	if (freq == SYSCON_FRO48MHZ_FREQ) {
		LPC_SYSCON->FROCTRL = val & ~SYSCON_FROCTRL_SEL96MHZ;
	} else if (freq == SYSCON_FRO96MHZ_FREQ) {
		LPC_SYSCON->FROCTRL = val | SYSCON_FROCTRL_SEL96MHZ;
	}
}

/**
 * @brief	Set main A system clock source
 * @param	src	: Clock source for main A
 * @return	Nothing
 * @note	This function only needs to be setup if main clock A will be
 * selected in the Chip_Clock_GetMain_B_ClockRate() function.
 */
__STATIC_INLINE void Chip_Clock_SetMain_A_ClockSource(CHIP_SYSCON_MAIN_A_CLKSRC_T src)
{
	LPC_SYSCON->MAINCLKSELA = (uint32_t) src;
}

/**
 * @brief	USB Clock source
 */
typedef enum {
	SYSCON_USBCLKSRC_FROHF,           /**< High frequency FRO 48MHz or 96MHz */
	SYSCON_USBCLKSRC_PLL,             /**< USB PLL */
	SYSCON_USBCLKSRC_DISABLED = 7     /**< USB Clock disabled */
} CHIP_SYSCON_USBCLKSRC_T;

/**
 * @brief	Set USB clock source
 * @param	src	: Clock source for USB (See #CHIP_SYSCON_USBCLKSRC_T)
 * @param	div	: Value by which the clock must be divided (valid range: 1 - 256)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetUSBClockSource(CHIP_SYSCON_USBCLKSRC_T src, uint32_t div)
{
	LPC_SYSCON->USBCLKSEL = src;
	// FIXME: Find the use for HALT and other bits
	LPC_SYSCON->USBCLKDIV = (div - 1) & 0xFF;
}

/**
 * @brief   Gets the clock source used by USB
 * @return	Returns which clock is used for USB
 */
__STATIC_INLINE CHIP_SYSCON_USBCLKSRC_T Chip_Clock_GetUSBClockSource(void)
{
	return (CHIP_SYSCON_USBCLKSRC_T) (LPC_SYSCON->USBCLKSEL & 0x07);
}

/**
 * @brief	MCLK Clock sources
 */
typedef enum {
	SYSCON_MCLKSRC_FROHF,             /*!< HF-FRO 48MHz or 96MHz */
	SYSCON_MCLKSRC_PLL,               /*!< Main pll */
	SYSCON_MCLKSRC_MCLKIN,            /*!< MCLK INPUT Clock pin set by IOCON */
	SYSCON_MCLKSRC_DISABLED = 7       /*!< Disable clock source to MCLK */
} CHIP_SYSCON_MCLKSRC_T;

/**
 * @brief	Set the MCLK clock source
 * @param	src: Clock Source for MCLK (see #CHIP_SYSCON_MCLKSRC_T)
 * @param	div: Value by which the source clock rate be divided (must be greater than 0)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMCLKClockSource(CHIP_SYSCON_MCLKSRC_T src, uint32_t div)
{
	LPC_SYSCON->MCLKCLKSEL  = (uint32_t) src;
	LPC_SYSCON->I2SMCLKDIV     = (uint32_t) ((div-1) & 0xff);
}

/**
 * @brief	Get MCLK clock div
 * @return	MCLK divider
 */
__STATIC_INLINE uint32_t Chip_Clock_GetMCLKDiv(void)
{
	return (LPC_SYSCON->I2SMCLKDIV & 0xff) + 1;
}

/**
 * @brief	Get MCLK clock source
 * @return	MCLK clock source
 */
__STATIC_INLINE CHIP_SYSCON_MCLKSRC_T Chip_Clock_GetMCLKSource(void)
{
	return (CHIP_SYSCON_MCLKSRC_T) (LPC_SYSCON->MCLKCLKSEL & 0x07);
}

/**
 * @brief	Set MCLK pin direction to INPUT
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMCLKDirInput(void)
{
	LPC_SYSCON->MCLKIO = 0;
}

/**
 * @brief	Set MCLK pin direction to OUTPUT
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMCLKDirOutput(void)
{
	LPC_SYSCON->MCLKIO = 1;
}

/**
 * @brief	Set MCLK pin direction to INPUT or OUTPUT
 * @param	dir	:	0 => INPUT, anything else => OUTPUT
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMCLKDir(int dir)
{
	if (dir) {
		Chip_Clock_SetMCLKDirInput();
	} else {
		Chip_Clock_SetMCLKDirOutput();
	}
}


/**
 * @brief   Returns the main A clock source
 * @return	Returns which clock is used for the main A
 */
__STATIC_INLINE CHIP_SYSCON_MAIN_A_CLKSRC_T Chip_Clock_GetMain_A_ClockSource(void)
{
	return (CHIP_SYSCON_MAIN_A_CLKSRC_T) (LPC_SYSCON->MAINCLKSELA & 0x3);
}

/**
 * @brief	Return main A clock rate
 * @return	main A clock rate in Hz
 */
uint32_t Chip_Clock_GetMain_A_ClockRate(void);

/**
 * Clock sources for only main B system clock
 */
typedef enum {
	SYSCON_MAIN_B_CLKSRC_MAINCLKSELA = 0,   /*!< main clock A */
	SYSCON_MAIN_B_CLKSRC_PLL = 2,           /*!< System PLL output */
	SYSCON_MAIN_B_CLKSRC_RTC,               /*!< RTC oscillator 32KHz output */
} CHIP_SYSCON_MAIN_B_CLKSRC_T;

/**
 * @brief	Set main B system clock source
 * @param	src	: Clock source for main B
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMain_B_ClockSource(CHIP_SYSCON_MAIN_B_CLKSRC_T src)
{
	LPC_SYSCON->MAINCLKSELB = (uint32_t) src;
}

/**
 * @brief   Returns the main B clock source
 * @return	Returns which clock is used for the main B
 */
__STATIC_INLINE CHIP_SYSCON_MAIN_B_CLKSRC_T Chip_Clock_GetMain_B_ClockSource(void)
{
	return (CHIP_SYSCON_MAIN_B_CLKSRC_T) (LPC_SYSCON->MAINCLKSELB);
}

/**
 * @brief	Return main B clock rate
 * @return	main B clock rate
 */
uint32_t Chip_Clock_GetMain_B_ClockRate(void);

/**
 * Clock sources for CLKOUT
 */
typedef enum {
	SYSCON_CLKOUTSRC_MAINCLK = 0,       /*!< Main system clock for CLKOUT */
	SYSCON_CLKOUTSRC_CLKIN,             /*!< CLKIN for CLKOUT */
	SYSCON_CLKOUTSRC_WDTOSC,            /*!< Watchdog oscillator for CLKOUT */
	SYSCON_CLKOUTSRC_FROHF,             /*!< 48MHz or 96MHz FRO */
	SYSCON_CLKOUTSRC_PLL,               /*!< Output of the PLL */
	SYSCON_CLKOUTSRC_FRO12MHZ,          /*!< 12MHz FRO */
	SYSCON_CLKOUTSRC_RTC,               /*!< RTC oscillator 32KHz for CLKOUT */
	SYSCON_CLKOUTSRC_DISABLED           /*!< Disable clock source for CLKOUT */
} CHIP_SYSCON_CLKOUTSRC_T;

/**
 * @brief	Set CLKOUT clock source and divider
 * @param	src	: Clock source for CLKOUT (see #CHIP_SYSCON_CLKOUTSRC_T)
 * @param	div	: divider for CLKOUT clock [Valid range 1 to 256]
 * @return	Nothing
 * @note	The CLKOUT clock
 * rate is the clock source divided by the divider. This function will
 * also toggle the clock source update register to update the clock
 * source.
 */
__STATIC_INLINE void Chip_Clock_SetCLKOUTSource(CHIP_SYSCON_CLKOUTSRC_T src, uint32_t div)
{
	/* Using a clock A source, select A and then switch B to A */
	LPC_SYSCON->CLKOUTSELA = (uint32_t) src & 0x07;
	if (div)
		LPC_SYSCON->CLKOUTDIV = (div - 1);
}

/**
 * System and peripheral clocks enum
 */
typedef enum CHIP_SYSCON_CLOCK {
	/* Peripheral clock enables for SYSAHBCLKCTRL0 */
	SYSCON_CLOCK_ROM = 1,               /*!< ROM clock */
	SYSCON_CLOCK_SRAM1 = 3,             /*!< SRAM1 clock */
	SYSCON_CLOCK_SRAM2,                 /*!< SRAM2 clock */
	SYSCON_CLOCK_SRAMX,                 /*!< SRAMX Clock */
	SYSCON_CLOCK_FLASH = 7,             /*!< FLASH controller clock */
	SYSCON_CLOCK_FMC,                   /*!< FMC clock */
	SYSCON_CLOCK_SPIFI = 10,            /*!< SPIFI Clock */
	SYSCON_CLOCK_INPUTMUX,              /*!< Input mux clock */
	SYSCON_CLOCK_IOCON = 13,            /*!< IOCON clock */
	SYSCON_CLOCK_GPIO0,                 /*!< GPIO0 clock */
	SYSCON_CLOCK_GPIO1,                 /*!< GPIO1 clock */
	SYSCON_CLOCK_PINT = 18,             /*!< PININT clock */
	SYSCON_CLOCK_GINT,                  /*!< grouped pin interrupt block clock */
	SYSCON_CLOCK_DMA,                   /*!< DMA clock */
	SYSCON_CLOCK_CRC,                   /*!< CRC clock */
	SYSCON_CLOCK_WWDT,                  /*!< WDT clock */
	SYSCON_CLOCK_RTC,                   /*!< RTC clock */
	SYSCON_CLOCK_MAILBOX = 26,          /*!< Mailbox clock */
	SYSCON_CLOCK_ADC0,                  /*!< ADC0 clock */

	/* Peripheral clock enables for SYSAHBCLKCTRL1 */
	SYSCON_CLOCK_MRT = 32,              /*!< multi-rate timer clock */
	SYSCON_CLOCK_SCT0 = 32 + 2,         /*!< SCT0 clock */
	SYSCON_CLOCK_UTICK = 32 + 10,       /*!< UTICK clock */
	SYSCON_CLOCK_FLEXCOMM0,             /*!< FLEXCOMM0 Clock */
	SYSCON_CLOCK_FLEXCOMM1,             /*!< FLEXCOMM1 Clock */
	SYSCON_CLOCK_FLEXCOMM2,             /*!< FLEXCOMM2 Clock */
	SYSCON_CLOCK_FLEXCOMM3,             /*!< FLEXCOMM3 Clock */
	SYSCON_CLOCK_FLEXCOMM4,             /*!< FLEXCOMM4 Clock */
	SYSCON_CLOCK_FLEXCOMM5,             /*!< FLEXCOMM5 Clock */
	SYSCON_CLOCK_FLEXCOMM6,             /*!< FLEXCOMM6 Clock */
	SYSCON_CLOCK_FLEXCOMM7,             /*!< FLEXCOMM7 Clock */
	SYSCON_CLOCK_DMIC,                  /*!< D-MIC Clock */
	SYSCON_CLOCK_TIMER2 = 32 + 22,      /*!< TIMER2 clock */
	SYSCON_CLOCK_USB = 32 + 25,         /*!< USB clock */
	SYSCON_CLOCK_TIMER0,                /*!< TIMER0 clock */
	SYSCON_CLOCK_TIMER1,                /*!< TIMER1 Clock */

	/* Peripheral clock enables for ASYNCAPBCLKCTRLCLR */
	SYSCON_CLOCK_TIMER3 = 128 + 13,     /*!< TIMER3 clock */
	SYSCON_CLOCK_TIMER4,                /*!< TIMER4 clock */
} CHIP_SYSCON_CLOCK_T;

/**
 * @brief	Enable a system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
void Chip_Clock_EnablePeriphClock(CHIP_SYSCON_CLOCK_T clk);

/**
 * @brief	Disable a system or peripheral clock
 * @param	clk	: Clock to disable
 * @return	Nothing
 */
void Chip_Clock_DisablePeriphClock(CHIP_SYSCON_CLOCK_T clk);

/**
 * @brief	Set system tick clock divider (external CLKIN as SYSTICK reference only)
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system tick
 * rate is the external CLKIN rate divided by this value. The extern CLKIN pin
 * signal, divided by the SYSTICKCLKDIV divider, is selected by clearing
 * CLKSOURCE bit 2 in the System Tick CSR register. The core clock must be at least
 * 2.5 times faster than the reference system tick clock otherwise the count
 * values are unpredictable.
 */
__STATIC_INLINE void Chip_Clock_SetSysTickClockDiv(uint32_t div)
{
	LPC_SYSCON->SYSTICKCLKDIV = div;
}

/**
 * @brief	Returns system tick clock divider
 * @return	system tick clock divider
 */
__STATIC_INLINE uint32_t Chip_Clock_GetSysTickClockDiv(void)
{
	return LPC_SYSCON->SYSTICKCLKDIV;
}

/**
 * @brief	Returns the system tick rate as used with the system tick divider
 * @return	the system tick rate
 */
uint32_t Chip_Clock_GetSysTickClockRate(void);

/**
 * @brief	Set system clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system clock
 * rate is the main system clock divided by this value.
 */
__STATIC_INLINE void Chip_Clock_SetSysClockDiv(uint32_t div)
{
	LPC_SYSCON->AHBCLKDIV = (div - 1);
}

/**
 * @brief	Set system tick clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system tick
 * rate is the main system clock divided by this value. Use caution when using
 * the CMSIS SysTick_Config() functions as they typically use SystemCoreClock
 * for setup.
 */
__STATIC_INLINE void Chip_Clock_SetADCClockDiv(uint32_t div)
{
	/* FIXME : Need to find the usage for HALT/RESET and other bits */
	LPC_SYSCON->ADCCLKDIV = (div & 0xFF);
}

/**
 * @brief	Returns ADC clock divider
 * @return	ADC clock divider, 0 = disabled
 */
__STATIC_INLINE uint32_t Chip_Clock_GetADCClockDiv(void)
{
	return (LPC_SYSCON->ADCCLKDIV & 0xFF);
}

/**
 * Clock sources for FLEXCOMM clock source select
 */
typedef enum {
	SYSCON_FLEXCOMMCLKSELSRC_FRO12MHZ = 0,		/*!< FRO 12-MHz */
	SYSCON_FLEXCOMMCLKSELSRC_FROHF,             /*!< HF-FRO 48-MHz or 96-MHz */
	SYSCON_FLEXCOMMCLKSELSRC_PLL,               /*!< PLL output */
	SYSCON_FLEXCOMMCLKSELSRC_MCLK,              /*!< MCLK output */
	SYSCON_FLEXCOMMCLKSELSRC_FRG,               /*!< FRG output */
	SYSCON_FLEXCOMMCLKSELSRC_NONE = 7           /*!< NONE output */
} CHIP_SYSCON_FLEXCOMMCLKSELSRC_T;

/**
 * @brief	Set the FLEXCOMM clock source
 * @param	idx	: Index of the flexcomm (0 to 7)
 * @param	src	: FLEXCOMM clock source (See #CHIP_SYSCON_FLEXCOMMCLKSELSRC_T)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetFLEXCOMMClockSource(uint32_t idx, CHIP_SYSCON_FLEXCOMMCLKSELSRC_T src)
{
	LPC_SYSCON->FXCOMCLKSEL[idx] = (uint32_t) src;
}

/**
 * @brief   Returns the FLEXCOMM clock source
 * @param	idx	: Index of the flexcomm (0 to 7)
 * @return	Returns which clock is used for the FLEXCOMM clock source
 */
__STATIC_INLINE CHIP_SYSCON_FLEXCOMMCLKSELSRC_T Chip_Clock_GetFLEXCOMMClockSource(uint32_t idx)
{
	return (CHIP_SYSCON_FLEXCOMMCLKSELSRC_T) (LPC_SYSCON->FXCOMCLKSEL[idx] & 0x07);
}

/**
 * @brief	Return FlexCOMM clock rate
 * @param	id	: FlexCOMM ID (Valid range: 0 to 7)
 * @return	FlexCOMM clock rate
 */
uint32_t Chip_Clock_GetFLEXCOMMClockRate(uint32_t id);

/**
 * Clock sources for ADC clock source select
 */
typedef enum {
	SYSCON_ADCCLKSELSRC_MAINCLK = 0,        /*!< Main clock */
	SYSCON_ADCCLKSELSRC_SYSPLLOUT,          /*!< PLL output */
	SYSCON_ADCCLKSELSRC_FROHF               /*!< High frequency FRO 48MHz or 96MHz */
} CHIP_SYSCON_ADCCLKSELSRC_T;

/**
 * @brief	Set the ADC clock source
 * @param	src	: ADC clock source
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetADCClockSource(CHIP_SYSCON_ADCCLKSELSRC_T src)
{
	LPC_SYSCON->ADCCLKSEL = (uint32_t) src;
}

/**
 * @brief   Returns the ADC clock source
 * @return	Returns which clock is used for the ADC clock source
 */
__STATIC_INLINE CHIP_SYSCON_ADCCLKSELSRC_T Chip_Clock_GetADCClockSource(void)
{
	return (CHIP_SYSCON_ADCCLKSELSRC_T) (LPC_SYSCON->ADCCLKSEL & 0x07);
}

/**
 * @brief	Return ADC clock rate
 * @return	ADC clock rate
 */
uint32_t Chip_Clock_GetADCClockRate(void);

/**
 * @brief	Enable the RTC 32KHz output
 * @return	Nothing
 * @note	This clock can be used for the main clock directly, but
 *			do not use this clock with the system PLL.
 */
__STATIC_INLINE void Chip_Clock_EnableRTCOsc(void)
{
	LPC_SYSCON->RTCOSCCTRL  = 1;
}

/**
 * @brief	Disable the RTC 32KHz output
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_DisableRTCOsc(void)
{
	LPC_SYSCON->RTCOSCCTRL  = 0;
}

/**
 * Clock source selections for the asynchronous APB clock
 */
typedef enum {
	SYSCON_ASYNC_MAINCLK = 0,       /*!< Main System clock */
	SYSCON_ASYNC_FRO12MHZ,			/*!< 12MHz FRO */
} CHIP_ASYNC_SYSCON_SRC_T;

/**
 * @brief	Set asynchronous APB clock source
 * @param	src	: Clock source for asynchronous APB clock
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetAsyncSysconClockSource(CHIP_ASYNC_SYSCON_SRC_T src)
{
	LPC_ASYNC_SYSCON->ASYNCAPBCLKSELA = (uint32_t) src;
}

/**
 * @brief	Get asynchronous APB clock source
 * @return	Clock source for asynchronous APB clock
 */
__STATIC_INLINE CHIP_ASYNC_SYSCON_SRC_T Chip_Clock_GetAsyncSysconClockSource(void)
{
	return (CHIP_ASYNC_SYSCON_SRC_T) (LPC_ASYNC_SYSCON->ASYNCAPBCLKSELA & 0x3);
}

/**
 * @brief	Return asynchronous APB clock rate
 * @return	Asynchronous APB clock rate
 * @note	Includes adjustments by Async clock divider (ASYNCCLKDIV).
 */
uint32_t Chip_Clock_GetAsyncSyscon_ClockRate(void);

/**
 * Clock sources for main system clock. This is a mix of both main clock A
 * and B selections.
 */
typedef enum {
	SYSCON_MAINCLKSRC_FRO12MHZ = 0,         /*!< 12-MHz FRO */
	SYSCON_MAINCLKSRC_CLKIN,				/*!< Crystal (main) oscillator in */
	SYSCON_MAINCLKSRC_WDTOSC,				/*!< Watchdog oscillator rate */
	SYSCON_MAINCLKSRC_FROHF,                /*!< 48MHz or 96-MHz HF-FRO */
	SYSCON_MAINCLKSRC_PLLOUT = 6,			/*!< System PLL output */
	SYSCON_MAINCLKSRC_RTC					/*!< RTC oscillator 32KHz output */
} CHIP_SYSCON_MAINCLKSRC_T;

/**
 * @brief	Set main system clock source
 * @param	src	: Clock source for main system (See #CHIP_SYSCON_MAINCLKSRC_T)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_Clock_SetMainClockSource(CHIP_SYSCON_MAINCLKSRC_T src)
{
	uint32_t clkSrc = (uint32_t) src;

	if (clkSrc >= 4) {
		/* Main B source only, not using main A */
		Chip_Clock_SetMain_B_ClockSource((CHIP_SYSCON_MAIN_B_CLKSRC_T) (clkSrc - 4));
	}
	else {
		/* Select main A clock source and set main B source to use main A */
		Chip_Clock_SetMain_A_ClockSource((CHIP_SYSCON_MAIN_A_CLKSRC_T) clkSrc);
		Chip_Clock_SetMain_B_ClockSource(SYSCON_MAIN_B_CLKSRC_MAINCLKSELA);
	}
}

/**
 * @brief	Get main system clock source
 * @return	Clock source for main system
 * @note
 */
CHIP_SYSCON_MAINCLKSRC_T Chip_Clock_GetMainClockSource(void);

/**
 * @brief	Return main clock rate
 * @return	main clock rate
 */
uint32_t Chip_Clock_GetMainClockRate(void);

/**
 * @brief	Return system clock rate
 * @return	system clock rate
 * @note	This is the main clock rate divided by AHBCLKDIV.
 */
uint32_t Chip_Clock_GetSystemClockRate(void);

/**
 * @brief	Fractional Divider clock sources
 */
typedef enum {
	SYSCON_FRGCLKSRC_MAINCLK,     /*!< Main Clock */
	SYSCON_FRGCLKSRC_PLL,         /*!< Output clock from PLL */
	SYSCON_FRGCLKSRC_FRO12MHZ,    /*!< FRO 12-MHz */
	SYSCON_FRGCLKSRC_FROHF,       /*!< FRO High Frequency (48 or 96) MHz */
	SYSCON_FRGCLKSRC_NONE = 7     /*!< No clock input */
}CHIP_SYSCON_FRGCLKSRC_T;

/**
 * @brief	Get the input clock frequency of FRG
 * @return	Frequency in Hz on success (0 on failure)
 */
uint32_t Chip_Clock_GetFRGInClockRate(void);

/**
 * @brief	Set clock source used by FRG
 * @return	Clock source used by FRG
 * @note
 */
__STATIC_INLINE void Chip_Clock_SetFRGClockSource(CHIP_SYSCON_FRGCLKSRC_T src)
{
	LPC_SYSCON->FRGCLKSEL = (uint32_t) src;
}

/**
 * @brief	Get clock source used by FRG
 * @return	Clock source used by FRG
 * @note
 */
__STATIC_INLINE CHIP_SYSCON_FRGCLKSRC_T Chip_Clock_GetFRGClockSource(void)
{
	return (CHIP_SYSCON_FRGCLKSRC_T)(LPC_SYSCON->FRGCLKSEL & 0x07);
}

/**
 * @brief	Get Fraction Rate Generator (FRG) clock rate
 * @return	UART base clock rate
 */
uint32_t Chip_Clock_GetFRGClockRate(void);

/**
 * @brief	Set FRG rate to given rate
 * @return	Actual FRG clock rate
 * @note	If FRG is used for UART base clock, @a rate
 * is recommended to be 16 times desired baud rate;
 * <b>This API must only be called after setting the source using
 * Chip_Clock_SetFRGClockSource()</b>
 */
uint32_t Chip_Clock_SetFRGClockRate(uint32_t rate);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_5411X_H_ */
