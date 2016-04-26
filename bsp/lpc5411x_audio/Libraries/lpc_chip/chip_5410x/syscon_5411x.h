/*
 * @brief LPC5411X System & Control driver inclusion file
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

#ifndef __SYSCON_5411X_H_
#define __SYSCON_5411X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SYSCON_5411X CHIP: LPC5411X System and Control Driver
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

/**
 * @brief LPC5411X Main system configuration register block structure
 */
typedef struct {
	__IO uint32_t SYSMEMREMAP;			/*!< System Remap register */
	__I  uint32_t RESERVED0[3];
	__IO uint32_t AHBMATPRIO;           /*!< AHB Martix priority register */
	__I  uint32_t RESERVED1[11];
	__IO uint32_t SYSTCKCAL;			/*!< System Tick Calibration register */
	__I  uint32_t RESERVED2[1];
	__IO uint32_t NMISRC;				/*!< NMI Source select register */
	__IO uint32_t ASYNCAPBCTRL;			/*!< Asynch APB chiplet control register */
	__I  uint32_t RESERVED3[28];
	__I  uint32_t PIOPORCAP[2];         /*!< Power on Reset; port capture register */
	__I  uint32_t RESERVED4[2];
	__I  uint32_t PIORESCAP[2];         /*!< Reset; port capture register */
	__I  uint32_t RESERVED5[10];
	__IO uint32_t PRESETCTRL[2];		/*!< Peripheral Reset control */
	__I  uint32_t RESERVED6[6];
	__O  uint32_t PRESETCTRLSET[2];     /*!< Peripheral Reset Control set */
	__I  uint32_t RESERVED7[6];
	__O  uint32_t PRESETCTRLCLR[2];     /*!< Peripheral Reset Control set */
	__I  uint32_t RESERVED8[42];
	__IO uint32_t SYSRSTSTAT;			/*!< System Reset Stat register */
	__I  uint32_t RESERVED9[3];
	__IO uint32_t AHBCLKCTRL[2];        /*!< AHB Peripheral Clk Enable register */
	__I  uint32_t RESERVED10[6];
	__O  uint32_t AHBCLKCTRLSET[2];     /*!< AHB Peripheral Clk Enable Set register */
	__I  uint32_t RESERVED11[6];
	__O  uint32_t AHBCLKCTRLCLR[2];     /*!< AHB Peripheral Clk Enable Clr register */
	__I  uint32_t RESERVED12[14];
	__IO uint32_t MAINCLKSELA;			/*!< Main Clk sel Source Sel A register */
	__IO uint32_t MAINCLKSELB;			/*!< Main Clk sel Source Sel B register */
	__IO uint32_t CLKOUTSELA;			/*!< Clk Out Sel Source B register */
	__I  uint32_t RESERVED13;
	__IO uint32_t SYSPLLCLKSEL;			/*!< System PLL Clk Selregister */
	__I  uint32_t RESERVED14[3];
	__IO uint32_t SPIFICLKSEL;          /*!< SPIFI clock selection register */
	__IO uint32_t ADCCLKSEL;			/*!< ADC Async Clk Sel register */
	__IO uint32_t USBCLKSEL;			/*!< USB Async Clk Sel register */
	__I  uint32_t RESERVED15;
	__IO uint32_t FXCOMCLKSEL[8];       /*!< FlexCOM CLK sel register */
	__I  uint32_t RESERVED16[4];
	__IO uint32_t MCLKCLKSEL;           /*!< MCLK Clock select register */
	__I  uint32_t RESERVED16A;
	__IO uint32_t FRGCLKSEL;            /*!< FRG Clock select register */
	__IO uint32_t DMICCLKSEL;           /*!< DMIC Clock select register */
	__I  uint32_t RESERVED17[4];
	__IO uint32_t SYSTICKCLKDIV;		/*!< Systick Clock divider register */
	__I  uint32_t RESERVED18[31];
	__IO uint32_t AHBCLKDIV;            /*!< AHB Clock divider */
	__IO uint32_t CLKOUTDIV;            /*!< CLKOUT divider */
	__I  uint32_t RESERVED19[2];
	__IO uint32_t SPIFICLKDIV;          /*!< SPIFI clock divider register */
	__IO uint32_t ADCCLKDIV;            /*!< ADC Clock divider register */
	__IO uint32_t USBCLKDIV;            /*!< USB Clock divider register */
	__I  uint32_t RESERVED20;
	__IO uint32_t FRGCTRL;				/*!< Fraction Rate Generator Ctrl register */
	__I  uint32_t RESERVED21;
	__IO uint32_t DMICCLKDIV;            /*!< DMIC Clock divider register */
	__IO uint32_t I2SMCLKDIV;            /*!< I2S MClock divider register */
	__I  uint32_t RESERVED22[20];
	__IO uint32_t FLASHCFG;              /*!< Flash wait state configuration register */
	__I  uint32_t RESERVED23[2];
	__IO uint32_t USBCLKCTRL;            /*!< USB Clock control register */
	__IO uint32_t USBCLKSTAT;            /*!< USB Clock Status register */
	__I  uint32_t RESERVED24;
	__IO uint32_t FREQMECTRL;            /*!< Frequency measure register */
	__I  uint32_t RESERVED25;
	__IO uint32_t MCLKIO;                /*!< MCLK Input Output register */
	__I  uint32_t RESERVED26[55];
	__IO uint32_t FROCTRL;               /*!< FRO oscillator control register */
	__I  uint32_t RESERVED27;
	__IO uint32_t WDTOSCCTRL;            /*!< Watchdog Oscillator control */
	__IO uint32_t RTCOSCCTRL;            /*!< RTC Oscillator control register */
	__I  uint32_t RESERVED28[28];
	__IO uint32_t SYSPLLCTRL;            /*!< System PLL control register */
	__I  uint32_t SYSPLLSTAT;            /*!< System PLL status register */
	__IO uint32_t SYSPLLNDEC;            /*!< System PLL N-DEC register */
	__IO uint32_t SYSPLLPDEC;            /*!< System PLL P-DEC register */
	__IO uint32_t SYSPLLSSCTRL[2];       /*!< System PLL Spread-Spectrum control register */
	__I  uint32_t RESERVED29[30];
	__IO uint32_t PDRUNCFG[2];           /*!< Power Down configuration registers */
	__I  uint32_t RESERVED30[2];
	__O  uint32_t PDRUNCFGSET[2];        /*!< Power down configuartion set register */
	__I  uint32_t RESERVED31[2];
	__O  uint32_t PDRUNCFGCLR[2];        /*!< Power down configuartion clear register */
	__I  uint32_t RESERVED32[18];
	__IO uint32_t STARTERP[2];           /*!< Start logic wakeup enable register */
	__I  uint32_t RESERVED33[6];
	__O  uint32_t STARTERPSET[2];        /*!< Start logic wakeup enable set register */
	__I  uint32_t RESERVED34[6];
	__O  uint32_t STARTERPCLR[2];        /*!< Start logic wakeup enable clear register */
	__I  uint32_t RESERVED35[78];
	__IO uint32_t CPCTRL;                /*!< Coprocessor control register */
	__IO uint32_t CPBOOT;                /*!< Coprocessor boot address */
	__IO uint32_t CPSTACK;               /*!< Coprocessor stack address register */
	__I  uint32_t CPSTAT;                /*!< Coprocessor status register */
	__I  uint32_t RESERVED36[505];
	__I  uint32_t JTAGIDCODE;            /*!< JTAG ID Code register */
	__I  uint32_t DEVICE_ID[2];           /*!< Device ID Registers */
} LPC_SYSCON_T;

/**
 * @brief LPC5411X Asynchronous system configuration register block structure
 */
typedef struct {
	__IO uint32_t AYSNCPRESETCTRL;		/*!< peripheral reset register */
	__O  uint32_t ASYNCPRESETCTRLSET;	/*!< peripheral reset Set register */
	__O  uint32_t ASYNCPRESETCTRLCLR;	/*!< peripheral reset Clr register */
	__I  uint32_t RESERVED0;
	__IO uint32_t ASYNCAPBCLKCTRL;		/*!< clk enable register */
	__IO uint32_t ASYNCAPBCLKCTRLSET;	/*!< clk enable Set register */
	__IO uint32_t ASYNCAPBCLKCTRLCLR;	/*!< clk enable Clr register */
	__I  uint32_t RESERVED1;
	__IO uint32_t ASYNCAPBCLKSELA;		/*!< clk source mux A register */
} LPC_ASYNC_SYSCON_T;


/**
 * @brief	FROCTRL register bits
 */
#define SYSCON_FROCTRL_MASK            ((1 << 15) | (0xF << 26))  /**< MASK for reserved bits in FROCTRL register */
#define SYSCON_FROCTRL_WRTRIM          (1UL << 31)   /**< Enable Writes to FROCTRL register */
#define SYSCON_FROCTRL_HSPDCLK         (1UL << 30)   /**< High speed clock (FROHF) enable bit */
#define SYSCON_FROCTRL_USBMODCHG       (1UL << 25)   /**< When set Trim value is pending to be set by SOF from USB */
#define SYSCON_FROCTRL_USBCLKADJ       (1UL << 24)   /**< Automatically adjust FRO trim value based on SOF from USB */
#define SYSCON_FROCTRL_SEL96MHZ        (1UL << 14)   /**< When set FROHF will be 96MHz; else FROHF will be 48MHz */
/**
 * System memory remap modes used to remap interrupt vectors
 */
typedef enum CHIP_SYSCON_BOOT_MODE_REMAP {
	REMAP_BOOT_LOADER_MODE,	/*!< Interrupt vectors are re-mapped to Boot ROM */
	REMAP_USER_RAM_MODE,	/*!< Interrupt vectors are re-mapped to user Static RAM */
	REMAP_USER_FLASH_MODE	/*!< Interrupt vectors are not re-mapped and reside in Flash */
} CHIP_SYSCON_BOOT_MODE_REMAP_T;

/**
 * @brief	Re-map interrupt vectors
 * @param	remap	: system memory map value
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_Map(CHIP_SYSCON_BOOT_MODE_REMAP_T remap)
{
	LPC_SYSCON->SYSMEMREMAP = (uint32_t) remap;
}

/**
 * @brief	Get system remap setting
 * @return	System remap setting
 */
__STATIC_INLINE CHIP_SYSCON_BOOT_MODE_REMAP_T Chip_SYSCON_GetMemoryMap(void)
{
	return (CHIP_SYSCON_BOOT_MODE_REMAP_T) LPC_SYSCON->SYSMEMREMAP;
}

/**
 * @brief	Set System tick timer calibration value
 * @param	sysCalVal	: System tick timer calibration value
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_SetSYSTCKCAL(uint32_t sysCalVal)
{
	LPC_SYSCON->SYSTCKCAL = sysCalVal;
}

/**
 * Non-Maskable Interrupt Enable/Disable value
 */
#define SYSCON_NMISRC_M0_ENABLE   ((uint32_t) 1 << 30)	/*!< Enable the Non-Maskable Interrupt M0 (NMI) source */
#define SYSCON_NMISRC_M4_ENABLE   ((uint32_t) 1 << 31)	/*!< Enable the Non-Maskable Interrupt M4 (NMI) source */

/**
 * @brief	Set source for non-maskable interrupt (NMI)
 * @param	intsrc	: IRQ number to assign to the NMI
 * @return	Nothing
 * @note	The NMI source will be disabled upon exiting this function. Use the
 * Chip_SYSCON_EnableNMISource() function to enable the NMI source.
 */
void Chip_SYSCON_SetNMISource(uint32_t intsrc);

/**
 * @brief	Enable interrupt used for NMI source
 * @return	Nothing
 */
void Chip_SYSCON_EnableNMISource(void);

/**
 * @brief	Disable interrupt used for NMI source
 * @return	Nothing
 */
void Chip_SYSCON_DisableNMISource(void);

/**
 * @brief	Enable or disable asynchronous APB bridge and subsystem
 * @param	enable	: true to enable, false to disable
 * @return	Nothing
 * @note	This bridge must be enabled to access peripherals on the
 * associated bridge.
 */
void Chip_SYSCON_Enable_ASYNC_Syscon(bool enable);

/**
 * @brief	Set UART Fractional divider value
 * @param	fmul	: Fractional multiplier value
 * @param	fdiv	: Fractional divider value (Must always be 0xFF)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_SetUSARTFRGCtrl(uint8_t fmul, uint8_t fdiv)
{
	LPC_SYSCON->FRGCTRL = ((uint32_t) fmul << 8) | fdiv;
}

/**
 * System reset status values
 */
#define SYSCON_RST_POR    (1 << 0)	/*!< POR reset status */
#define SYSCON_RST_EXTRST (1 << 1)	/*!< External reset status */
#define SYSCON_RST_WDT    (1 << 2)	/*!< Watchdog reset status */
#define SYSCON_RST_BOD    (1 << 3)	/*!< Brown-out detect reset status */
#define SYSCON_RST_SYSRST (1 << 4)	/*!< software system reset status */

/**
 * @brief	Get system reset status
 * @return	An Or'ed value of SYSCON_RST_*
 * @note	This function returns the detected reset source(s).
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetSystemRSTStatus(void)
{
	return LPC_SYSCON->SYSRSTSTAT;
}

/**
 * @brief	Clear system reset status
 * @param	reset	: An Or'ed value of SYSCON_RST_* status to clear
 * @return	Nothing
 * @note	This function clears the specified reset source(s).
 */
__STATIC_INLINE void Chip_SYSCON_ClearSystemRSTStatus(uint32_t reset)
{
	LPC_SYSCON->SYSRSTSTAT = reset;
}

/**
 * Peripheral reset identifiers
 */
typedef enum {
	/* Peripheral reset enables for PRESETCTRL0 */
	RESET_FLASH = 7,                /*!< Flash Controller */
	RESET_FMC,                      /*!< Flash Accelerator */
	RESET_SPIFI = 10,               /*!< SPIFI Reset */
	RESET_MUX,                      /*!< IO MUX Reset */
	RESET_IOCON = 13,               /*!< IOCON Reset */
	RESET_GPIO0,                    /*!< GPIO Port-0 Reset */
	RESET_GPIO1,                    /*!< GPIO Port-1 Reset */
	RESET_PINT = 18,                /*!< Pin Interrupt Reset */
	RESET_GINT,                     /*!< Group Interrupt Reset */
	RESET_DMA,                      /*!< DMA Reset */
	RESET_CRC,                      /*!< CRC Engine Reset */
	RESET_WWDT,                     /*!< Windowed watchdog timer */
	RESET_ADC = 27,                 /*!< ADC Reset */
	RESET_ADC0 = 27,                /*!< ADC Reset */

	/* Peripheral reset enables for PRESETCTRL1 */
	RESET_MRT = 32,                 /*!< Multirate Timer */
	RESET_SCT0 = 32 + 2,            /*!< State configurable Timer */
	RESET_SCT = 32 + 2,             /*!< State configurable Timer */
	RESET_UTICK = 10,               /*!< Micro Tick Timer */
	RESET_FLEXCOMM0,                /*!< FlexComm 0 */
	RESET_FLEXCOMM1,                /*!< FlexComm 1 */
	RESET_FLEXCOMM2,                /*!< FlexComm 2 */
	RESET_FLEXCOMM3,                /*!< FlexComm 3 */
	RESET_FLEXCOMM4,                /*!< FlexComm 4 */
	RESET_FLEXCOMM5,                /*!< FlexComm 5 */
	RESET_FLEXCOMM6,                /*!< FlexComm 6 */
	RESET_FLEXCOMM7,                /*!< FlexComm 7 */
	RESET_DMIC,                     /*!< Digital MIC */
	RESET_TIMER2 = 32 + 22,         /*!< Timer2 Reset */
	RESET_USB,                      /*!< USB Reset */
	RESET_TIMER0,                   /*!< Timer0 Reset */
	RESET_TIMER1,                   /*!< Timer1 Reset */

	/* Async peripheral reset enables for ASYNCPRESETCTRL */
	RESET_TIMER3 = 128 + 13,		/*!< TIMER0 */
	RESET_TIMER4,					/*!< TIMER4 Reset*/
} CHIP_SYSCON_PERIPH_RESET_T;

/**
 * @brief	Resets a peripheral
 * @param	periph	:	Peripheral to reset (See #CHIP_SYSCON_PERIPH_RESET_T)
 * @return	Nothing
 * Will assert and de-assert reset for a peripheral.
 */
__STATIC_INLINE void Chip_SYSCON_PeriphReset(CHIP_SYSCON_PERIPH_RESET_T periph)
{
	uint32_t val = (uint32_t) periph;
	if (val < 128) {
		LPC_SYSCON->PRESETCTRLSET[val >> 5] = 1 << (val & 31);
	} else {
		LPC_ASYNC_SYSCON->ASYNCPRESETCTRLSET = 1 << (val - 128);
	}

	__NOP();
	__NOP();
	__NOP();
	__NOP();

	if (val < 128) {
		LPC_SYSCON->PRESETCTRLCLR[val >> 5] = 1 << (val & 31);
	} else {
		LPC_ASYNC_SYSCON->ASYNCPRESETCTRLCLR = 1 << (val - 128);
	}
}

/**
 * @brief	Read POR captured PIO status
 * @param	port	: 0 for port 0 pins, 1 for port 1 pins, 2 for port 2 pins, etc.
 * @return	captured Power-On-Reset (POR) PIO status
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetPORPIOStatus(uint8_t port)
{
	return LPC_SYSCON->PIOPORCAP[port];
}

/**
 * @brief	Read reset captured PIO status
 * @param	port	: 0 for port 0 pins, 1 for port 1 pins, 2 for port 2 pins, etc.
 * @return	captured reset PIO status
 * @note	Used when reset other than a Power-On-Reset (POR) occurs.
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetResetPIOStatus(uint8_t port)
{
	return LPC_SYSCON->PIORESCAP[port];
}

/**
 * @brief	Starts a frequency measurement cycle
 * @return	Nothing
 * @note	This function is meant to be used with the Chip_INMUX_SetFreqMeasRefClock()
 * and Chip_INMUX_SetFreqMeasTargClock() functions.
 */
__STATIC_INLINE void Chip_SYSCON_StartFreqMeas(void)
{
	LPC_SYSCON->FREQMECTRL = 0;
	LPC_SYSCON->FREQMECTRL = (1UL << 31);
}

/**
 * @brief	Indicates when a frequency measurement cycle is complete
 * @return	true if a measurement cycle is active, otherwise false
 */
__STATIC_INLINE bool Chip_SYSCON_IsFreqMeasComplete(void)
{
	return (bool) ((LPC_SYSCON->FREQMECTRL & (1UL << 31)) == 0);
}

/**
 * @brief	Returns the raw capture value for a frequency measurement cycle
 * @return	raw cpature value (this is not a frequency)
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetRawFreqMeasCapval(void)
{
	return LPC_SYSCON->FREQMECTRL & 0x3FFF;
}

/**
 * @brief	Returns the computed value for a frequency measurement cycle
 * @param	refClockRate	: Reference clock rate used during the frequency measurement cycle
 * @return	Computed cpature value
 */
uint32_t Chip_SYSCON_GetCompFreqMeas(uint32_t refClockRate);

/**
 * @brief FLASH Access time definitions
 */
typedef enum {
	SYSCON_FLASH_1CYCLE = 0,	/*!< Flash accesses use 1 CPU clock */
	FLASHTIM_20MHZ_CPU = SYSCON_FLASH_1CYCLE,
	SYSCON_FLASH_2CYCLE,		/*!< Flash accesses use 2 CPU clocks */
	SYSCON_FLASH_3CYCLE,		/*!< Flash accesses use 3 CPU clocks */
	SYSCON_FLASH_4CYCLE,		/*!< Flash accesses use 4 CPU clocks */
	SYSCON_FLASH_5CYCLE,		/*!< Flash accesses use 5 CPU clocks */
	SYSCON_FLASH_6CYCLE,		/*!< Flash accesses use 6 CPU clocks */
	SYSCON_FLASH_7CYCLE,		/*!< Flash accesses use 7 CPU clocks */
	SYSCON_FLASH_8CYCLE			/*!< Flash accesses use 8 CPU clocks */
} SYSCON_FLASHTIM_T;

/**
 * @brief	Set FLASH memory access time in clocks
 * @param	clks	: Clock cycles for FLASH access
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_SetFLASHAccess(SYSCON_FLASHTIM_T clks)
{
	uint32_t tmp;

	tmp = LPC_SYSCON->FLASHCFG & ~(0xF << 12);

	/* Don't alter lower bits */
	LPC_SYSCON->FLASHCFG = tmp | ((uint32_t) clks << 12);
}

/**
 * Power control definition bits (0 = powered, 1 = powered down)
 */
#define SYSCON_PDRUNCFG_PD_FRO           (1 << 4)		/*!< FRO oscillator */
#define SYSCON_PDRUNCFG_PD_FLASH         (1 << 5)		/*!< Flash memory */
#define SYSCON_PDRUNCFG_PD_TS            (1 << 6)		/*!< Temperature Sensor */
#define SYSCON_PDRUNCFG_PD_BOD_RST       (1 << 7)		/*!< Brown-out Detect reset */
#define SYSCON_PDRUNCFG_PD_BOD_INTR      (1 << 8)		/*!< Brown-out Detect interrupt */
#define SYSCON_PDRUNCFG_PD_ADC0          (1 << 10)		/*!< ADC0 */
#define SYSCON_PDRUNCFG_PD_SRAM0         (1 << 13)		/*!< SRAM0 */
#define SYSCON_PDRUNCFG_PD_SRAM1         (1 << 14)		/*!< SRAM1 */
#define SYSCON_PDRUNCFG_PD_SRAM2         (1 << 15)		/*!< SRAM2 */
#define SYSCON_PDRUNCFG_PD_SRAMX         (1 << 16)		/*!< SRAMX */
#define SYSCON_PDRUNCFG_PD_ROM           (1 << 17)		/*!< ROM */
#define SYSCON_PDRUNCFG_PD_VDDA_ENA      (1 << 19)		/*!< Vdda to the ADC, must be enabled for the ADC to work */
#define SYSCON_PDRUNCFG_PD_WDT_OSC       (1 << 20)		/*!< Watchdog oscillator */
#define SYSCON_PDRUNCFG_PD_USB_PHY       (1 << 21)      /*!< USB Phy */
#define SYSCON_PDRUNCFG_PD_SYS_PLL       (1 << 22)		/*!< PLL0 */
#define SYSCON_PDRUNCFG_PD_VREFP         (1 << 23)		/*!< Vrefp to the ADC, must be enabled for the ADC to work */
#define SYSCON_PDRUNCFG_PD_32K_OSC       (1 << 24)		/*!< 32 kHz RTC oscillator */

/**
 * @brief	Power up one or more blocks or peripherals
 * @return	OR'ed values of SYSCON_PDRUNCFG_* values
 * @note	A high state indicates the peripheral is powered down.
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetPowerStates(void)
{
	return LPC_SYSCON->PDRUNCFG[0];
}

/**
 * @brief	Power down one or more blocks or peripherals
 * @param	powerdownmask	: OR'ed values of SYSCON_PDRUNCFG_* values
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_PowerDown(uint32_t powerdownmask)
{
	/* Disable peripheral states by setting high */
	LPC_SYSCON->PDRUNCFGSET[0] = powerdownmask;
}

/**
 * @brief	Power up one or more blocks or peripherals
 * @param	powerupmask	: OR'ed values of SYSCON_PDRUNCFG_* values
 * @return	Nothing
 */
void Chip_SYSCON_PowerUp(uint32_t powerupmask);

/**
 * Start enable enumerations - for enabling and disabling peripheral wakeup
 */
typedef enum {
	SYSCON_STARTER_WWDT_BOD = 0,
	SYSCON_STARTER_DMA,
	SYSCON_STARTER_GINT0,
	SYSCON_STARTER_GINT1,
	SYSCON_STARTER_PINT0,
	SYSCON_STARTER_PINT1,
	SYSCON_STARTER_PINT2,
	SYSCON_STARTER_PINT3,
	SYSCON_STARTER_UTICK,
	SYSCON_STARTER_MRT,
	SYSCON_STARTER_TIMER0,
	SYSCON_STARTER_TIMER1,
	SYSCON_STARTER_SCT0,
	SYSCON_STARTER_TIMER3,
	SYSCON_STARTER_FLEXCOMM0,
	SYSCON_STARTER_FLEXCOMM1,
	SYSCON_STARTER_FLEXCOMM2,
	SYSCON_STARTER_FLEXCOMM3,
	SYSCON_STARTER_FLEXCOMM4,
	SYSCON_STARTER_FLEXCOMM5,
	SYSCON_STARTER_FLEXCOMM6,
	SYSCON_STARTER_FLEXCOMM7,
	SYSCON_STARTER_ADC0_SEQA,
	SYSCON_STARTER_ADC0_SEQB,
	SYSCON_STARTER_ADC0_THCMP,
	SYSCON_STARTER_DMIC,
	SYSCON_STARTER_HWVAD,
	SYSCON_STARTER_USBNEEDCLK,
	SYSCON_STARTER_USB,
	SYSCON_STARTER_RTC,
	SYSCON_STARTER_RESERVED0,
	SYSCON_STARTER_MAILBOX,
	SYSCON_STARTER_PINT4,
	SYSCON_STARTER_PINT5,
	SYSCON_STARTER_PINT6,
	SYSCON_STARTER_PINT7,
	SYSCON_STARTER_TIMER2,
	SYSCON_STARTER_TIMER4,
} CHIP_SYSCON_WAKEUP_T;

/**
 * @brief	Enables a pin's (PINT) wakeup logic
 * @param	periphId	: Peripheral identifier (See #CHIP_SYSCON_WAKEUP_T)
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_EnableWakeup(CHIP_SYSCON_WAKEUP_T periphId)
{
	LPC_SYSCON->STARTERPSET[(uint32_t) periphId >> 5] = 1 << ((uint32_t) periphId & 31);
}

/**
 * @brief	Disables peripheral's wakeup logic
 * @param	periphId	: Peripheral identifier
 * @return	Nothing
 */
__STATIC_INLINE void Chip_SYSCON_DisableWakeup(CHIP_SYSCON_WAKEUP_T periphId)
{
	LPC_SYSCON->STARTERPCLR[(uint32_t) periphId >> 5] = 1 << ((uint32_t) periphId & 31);
}

/**
 * @brief	Return the pointer to device ID registers
 * @return	Pointer to device ID registers
 */
__STATIC_INLINE uint32_t Chip_SYSCON_GetDeviceID(void)
{
	return LPC_SYSCON->DEVICE_ID[0];
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SYSCON_5411X_H_ */
