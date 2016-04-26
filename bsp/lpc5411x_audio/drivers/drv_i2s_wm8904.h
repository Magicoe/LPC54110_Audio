#ifndef __CODEC_WM8978_I2C_H__
#define __CODEC_WM8978_I2C_H__

#include <stdint.h>

#define WM8904_CLK_MCLK							1
#define WM8904_CLK_FLL							2

#define WM8904_FLL_MCLK							1
#define WM8904_FLL_BCLK							2
#define WM8904_FLL_LRCLK						3
#define WM8904_FLL_FREE_RUNNING					4

/*
 * Register values.
 */
#define WM8904_SW_RESET_AND_ID					0x00
#define WM8904_REVISION							0x01
#define WM8904_BIAS_CONTROL_0					0x04
#define WM8904_VMID_CONTROL_0					0x05
#define WM8904_MIC_BIAS_CONTROL_0				0x06
#define WM8904_MIC_BIAS_CONTROL_1				0x07
#define WM8904_ANALOGUE_DAC_0					0x08
#define WM8904_MIC_FILTER_CONTROL				0x09
#define WM8904_ANALOGUE_ADC_0					0x0A
#define WM8904_POWER_MANAGEMENT_0				0x0C
#define WM8904_POWER_MANAGEMENT_2				0x0E
#define WM8904_POWER_MANAGEMENT_3				0x0F
#define WM8904_POWER_MANAGEMENT_6				0x12
#define WM8904_CLOCK_RATES_0					0x14
#define WM8904_CLOCK_RATES_1					0x15
#define WM8904_CLOCK_RATES_2					0x16
#define WM8904_AUDIO_INTERFACE_0				0x18
#define WM8904_AUDIO_INTERFACE_1				0x19
#define WM8904_AUDIO_INTERFACE_2				0x1A
#define WM8904_AUDIO_INTERFACE_3				0x1B
#define WM8904_DAC_DIGITAL_VOLUME_LEFT			0x1E
#define WM8904_DAC_DIGITAL_VOLUME_RIGHT			0x1F
#define WM8904_DAC_DIGITAL_0					0x20
#define WM8904_DAC_DIGITAL_1					0x21
#define WM8904_ADC_DIGITAL_VOLUME_LEFT			0x24
#define WM8904_ADC_DIGITAL_VOLUME_RIGHT			0x25
#define WM8904_ADC_DIGITAL_0					0x26
#define WM8904_DIGITAL_MICROPHONE_0				0x27
#define WM8904_DRC_0							0x28
#define WM8904_DRC_1							0x29
#define WM8904_DRC_2							0x2A
#define WM8904_DRC_3							0x2B
#define WM8904_ANALOGUE_LEFT_INPUT_0			0x2C
#define WM8904_ANALOGUE_RIGHT_INPUT_0			0x2D
#define WM8904_ANALOGUE_LEFT_INPUT_1			0x2E
#define WM8904_ANALOGUE_RIGHT_INPUT_1			0x2F
#define WM8904_ANALOGUE_OUT1_LEFT				0x39
#define WM8904_ANALOGUE_OUT1_RIGHT				0x3A
#define WM8904_ANALOGUE_OUT2_LEFT				0x3B
#define WM8904_ANALOGUE_OUT2_RIGHT				0x3C
#define WM8904_ANALOGUE_OUT12_ZC				0x3D
#define WM8904_DC_SERVO_0						0x43
#define WM8904_DC_SERVO_1						0x44
#define WM8904_DC_SERVO_2						0x45
#define WM8904_DC_SERVO_4						0x47
#define WM8904_DC_SERVO_5						0x48
#define WM8904_DC_SERVO_6						0x49
#define WM8904_DC_SERVO_7						0x4A
#define WM8904_DC_SERVO_8						0x4B
#define WM8904_DC_SERVO_9						0x4C
#define WM8904_DC_SERVO_READBACK_0				0x4D
#define WM8904_ANALOGUE_HP_0					0x5A
#define WM8904_ANALOGUE_LINEOUT_0				0x5E
#define WM8904_CHARGE_PUMP_0					0x62
#define WM8904_CLASS_W_0						0x68
#define WM8904_WRITE_SEQUENCER_0				0x6C
#define WM8904_WRITE_SEQUENCER_1				0x6D
#define WM8904_WRITE_SEQUENCER_2				0x6E
#define WM8904_WRITE_SEQUENCER_3				0x6F
#define WM8904_WRITE_SEQUENCER_4				0x70
#define WM8904_FLL_CONTROL_1					0x74
#define WM8904_FLL_CONTROL_2					0x75
#define WM8904_FLL_CONTROL_3					0x76
#define WM8904_FLL_CONTROL_4					0x77
#define WM8904_FLL_CONTROL_5					0x78
#define WM8904_GPIO_CONTROL_1					0x79
#define WM8904_GPIO_CONTROL_2					0x7A
#define WM8904_GPIO_CONTROL_3					0x7B
#define WM8904_GPIO_CONTROL_4					0x7C
#define WM8904_DIGITAL_PULLS					0x7E
#define WM8904_INTERRUPT_STATUS					0x7F
#define WM8904_INTERRUPT_STATUS_MASK			0x80
#define WM8904_INTERRUPT_POLARITY				0x81
#define WM8904_INTERRUPT_DEBOUNCE				0x82
#define WM8904_EQ1								0x86
#define WM8904_EQ2								0x87
#define WM8904_EQ3								0x88
#define WM8904_EQ4								0x89
#define WM8904_EQ5								0x8A
#define WM8904_EQ6								0x8B
#define WM8904_EQ7								0x8C
#define WM8904_EQ8								0x8D
#define WM8904_EQ9								0x8E
#define WM8904_EQ10								0x8F
#define WM8904_EQ11								0x90
#define WM8904_EQ12								0x91
#define WM8904_EQ13								0x92
#define WM8904_EQ14								0x93
#define WM8904_EQ15								0x94
#define WM8904_EQ16								0x95
#define WM8904_EQ17								0x96
#define WM8904_EQ18								0x97
#define WM8904_EQ19								0x98
#define WM8904_EQ20								0x99
#define WM8904_EQ21								0x9A
#define WM8904_EQ22								0x9B
#define WM8904_EQ23								0x9C
#define WM8904_EQ24								0x9D
#define WM8904_CONTROL_INTERFACE_TEST_1			0xA1
#define WM8904_ADC_TEST_0						0xC6
#define WM8904_ANALOGUE_OUTPUT_BIAS_0			0xCC
#define WM8904_FLL_NCO_TEST_0					0xF7
#define WM8904_FLL_NCO_TEST_1					0xF8

#define WM8904_MS_DELAY							0xFF							/* pseudo register: used to delay during multi-write sequences */

/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - SW Reset and ID
 */
#define WM8904_SW_RST_DEV_ID1_MASK				0xFFFF							/* SW_RST_DEV_ID1 - [15:0] */
#define WM8904_SW_RST_DEV_ID1_SHIFT					 0							/* SW_RST_DEV_ID1 - [15:0] */
#define WM8904_SW_RST_DEV_ID1_WIDTH					16							/* SW_RST_DEV_ID1 - [15:0] */

/*
 * R1 (0x01) - Revision
 */
#define WM8904_REVISION_MASK					0x000F							/* REVISION - [3:0] */
#define WM8904_REVISION_SHIFT						 0							/* REVISION - [3:0] */
#define WM8904_REVISION_WIDTH						16							/* REVISION - [3:0] */

/*
 * R4 (0x04) - Bias Control 0
 */
#define WM8904_POBCTRL							0x0010							/* POBCTRL */
#define WM8904_POBCTRL_MASK						0x0010							/* POBCTRL */
#define WM8904_POBCTRL_SHIFT						 4							/* POBCTRL */
#define WM8904_POBCTRL_WIDTH						 1							/* POBCTRL */
#define WM8904_ISEL_MASK						0x000C							/* ISEL - [3:2] */
#define WM8904_ISEL_SHIFT							 2							/* ISEL - [3:2] */
#define WM8904_ISEL_WIDTH							 2							/* ISEL - [3:2] */
#define WM8904_STARTUP_BIAS_ENA					0x0002							/* STARTUP_BIAS_ENA */
#define WM8904_STARTUP_BIAS_ENA_MASK			0x0002							/* STARTUP_BIAS_ENA */
#define WM8904_STARTUP_BIAS_ENA_SHIFT				 1							/* STARTUP_BIAS_ENA */
#define WM8904_STARTUP_BIAS_ENA_WIDTH				 1							/* STARTUP_BIAS_ENA */
#define WM8904_BIAS_ENA							0x0001							/* BIAS_ENA */
#define WM8904_BIAS_ENA_MASK					0x0001							/* BIAS_ENA */
#define WM8904_BIAS_ENA_SHIFT						 0							/* BIAS_ENA */
#define WM8904_BIAS_ENA_WIDTH						 1							/* BIAS_ENA */

/*
 * R5 (0x05) - VMID Control 0
 */
#define WM8904_VMID_BUF_ENA						0x0040							/* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_MASK				0x0040							/* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_SHIFT					 6							/* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA_WIDTH					 1							/* VMID_BUF_ENA */
#define WM8904_VMID_RES_MASK					0x0006							/* VMID_RES - [2:1] */
#define WM8904_VMID_RES_SHIFT						 1							/* VMID_RES - [2:1] */
#define WM8904_VMID_RES_WIDTH						 2							/* VMID_RES - [2:1] */
#define WM8904_VMID_ENA							0x0001							/* VMID_ENA */
#define WM8904_VMID_ENA_MASK					0x0001							/* VMID_ENA */
#define WM8904_VMID_ENA_SHIFT						 0							/* VMID_ENA */
#define WM8904_VMID_ENA_WIDTH						 1							/* VMID_ENA */

/*
 * R8 (0x08) - Analogue DAC 0
 */
#define WM8904_DAC_BIAS_SEL_MASK				0x0018							/* DAC_BIAS_SEL - [4:3] */
#define WM8904_DAC_BIAS_SEL_SHIFT					 3							/* DAC_BIAS_SEL - [4:3] */
#define WM8904_DAC_BIAS_SEL_WIDTH					 2							/* DAC_BIAS_SEL - [4:3] */
#define WM8904_DAC_VMID_BIAS_SEL_MASK			0x0006							/* DAC_VMID_BIAS_SEL - [2:1] */
#define WM8904_DAC_VMID_BIAS_SEL_SHIFT				 1							/* DAC_VMID_BIAS_SEL - [2:1] */
#define WM8904_DAC_VMID_BIAS_SEL_WIDTH				 2							/* DAC_VMID_BIAS_SEL - [2:1] */

/*
 * R9 (0x09) - mic Filter Control
 */
#define WM8904_MIC_DET_SET_THRESHOLD_MASK		0xF000							/* MIC_DET_SET_THRESHOLD - [15:12] */
#define WM8904_MIC_DET_SET_THRESHOLD_SHIFT			12							/* MIC_DET_SET_THRESHOLD - [15:12] */
#define WM8904_MIC_DET_SET_THRESHOLD_WIDTH			 4							/* MIC_DET_SET_THRESHOLD - [15:12] */
#define WM8904_MIC_DET_RESET_THRESHOLD_MASK		0x0F00							/* MIC_DET_RESET_THRESHOLD - [11:8] */
#define WM8904_MIC_DET_RESET_THRESHOLD_SHIFT		 8							/* MIC_DET_RESET_THRESHOLD - [11:8] */
#define WM8904_MIC_DET_RESET_THRESHOLD_WIDTH		 4							/* MIC_DET_RESET_THRESHOLD - [11:8] */
#define WM8904_MIC_SHORT_SET_THRESHOLD_MASK		0x00F0							/* MIC_SHORT_SET_THRESHOLD - [7:4] */
#define WM8904_MIC_SHORT_SET_THRESHOLD_SHIFT		 4							/* MIC_SHORT_SET_THRESHOLD - [7:4] */
#define WM8904_MIC_SHORT_SET_THRESHOLD_WIDTH		 4							/* MIC_SHORT_SET_THRESHOLD - [7:4] */
#define WM8904_MIC_SHORT_RESET_THRESHOLD_MASK	0x000F							/* MIC_SHORT_RESET_THRESHOLD - [3:0] */
#define WM8904_MIC_SHORT_RESET_THRESHOLD_SHIFT		 0							/* MIC_SHORT_RESET_THRESHOLD - [3:0] */
#define WM8904_MIC_SHORT_RESET_THRESHOLD_WIDTH		 4							/* MIC_SHORT_RESET_THRESHOLD - [3:0] */

/*
 * R10 (0x0A) - Analogue ADC 0
 */
#define WM8904_ADC_OSR128						0x0001							/* ADC_OSR128 */
#define WM8904_ADC_OSR128_MASK					0x0001							/* ADC_OSR128 */
#define WM8904_ADC_OSR128_SHIFT						 0							/* ADC_OSR128 */
#define WM8904_ADC_OSR128_WIDTH						 1							/* ADC_OSR128 */

/*
 * R12 (0x0C) - Power Management 0
 */
#define WM8904_INL_ENA							0x0002							/* INL_ENA */
#define WM8904_INL_ENA_MASK						0x0002							/* INL_ENA */
#define WM8904_INL_ENA_SHIFT						 1							/* INL_ENA */
#define WM8904_INL_ENA_WIDTH						 1							/* INL_ENA */
#define WM8904_INR_ENA							0x0001							/* INR_ENA */
#define WM8904_INR_ENA_MASK						0x0001							/* INR_ENA */
#define WM8904_INR_ENA_SHIFT						 0							/* INR_ENA */
#define WM8904_INR_ENA_WIDTH						 1							/* INR_ENA */

/*
 * R14 (0x0E) - Power Management 2
 */
#define WM8904_HPL_PGA_ENA						0x0002							/* HPL_PGA_ENA */
#define WM8904_HPL_PGA_ENA_MASK					0x0002							/* HPL_PGA_ENA */
#define WM8904_HPL_PGA_ENA_SHIFT					 1							/* HPL_PGA_ENA */
#define WM8904_HPL_PGA_ENA_WIDTH					 1							/* HPL_PGA_ENA */
#define WM8904_HPR_PGA_ENA						0x0001							/* HPR_PGA_ENA */
#define WM8904_HPR_PGA_ENA_MASK					0x0001							/* HPR_PGA_ENA */
#define WM8904_HPR_PGA_ENA_SHIFT					 0							/* HPR_PGA_ENA */
#define WM8904_HPR_PGA_ENA_WIDTH					 1							/* HPR_PGA_ENA */

/*
 * R15 (0x0F) - Power Management 3
 */
#define WM8904_LINEOUTL_PGA_ENA					0x0002							/* LINEOUTL_PGA_ENA */
#define WM8904_LINEOUTL_PGA_ENA_MASK			0x0002							/* LINEOUTL_PGA_ENA */
#define WM8904_LINEOUTL_PGA_ENA_SHIFT				 1							/* LINEOUTL_PGA_ENA */
#define WM8904_LINEOUTL_PGA_ENA_WIDTH				 1							/* LINEOUTL_PGA_ENA */
#define WM8904_LINEOUTR_PGA_ENA					0x0001							/* LINEOUTR_PGA_ENA */
#define WM8904_LINEOUTR_PGA_ENA_MASK			0x0001							/* LINEOUTR_PGA_ENA */
#define WM8904_LINEOUTR_PGA_ENA_SHIFT				 0							/* LINEOUTR_PGA_ENA */
#define WM8904_LINEOUTR_PGA_ENA_WIDTH				 1							/* LINEOUTR_PGA_ENA */

/*
 * R18 (0x12) - Power Management 6
 */
#define WM8904_DACL_ENA							0x0008							/* DACL_ENA */
#define WM8904_DACL_ENA_MASK					0x0008							/* DACL_ENA */
#define WM8904_DACL_ENA_SHIFT						 3							/* DACL_ENA */
#define WM8904_DACL_ENA_WIDTH						 1							/* DACL_ENA */
#define WM8904_DACR_ENA							0x0004							/* DACR_ENA */
#define WM8904_DACR_ENA_MASK					0x0004							/* DACR_ENA */
#define WM8904_DACR_ENA_SHIFT						 2							/* DACR_ENA */
#define WM8904_DACR_ENA_WIDTH						 1							/* DACR_ENA */
#define WM8904_ADCL_ENA							0x0002							/* ADCL_ENA */
#define WM8904_ADCL_ENA_MASK					0x0002							/* ADCL_ENA */
#define WM8904_ADCL_ENA_SHIFT						 1							/* ADCL_ENA */
#define WM8904_ADCL_ENA_WIDTH						 1							/* ADCL_ENA */
#define WM8904_ADCR_ENA							0x0001							/* ADCR_ENA */
#define WM8904_ADCR_ENA_MASK					0x0001							/* ADCR_ENA */
#define WM8904_ADCR_ENA_SHIFT						 0							/* ADCR_ENA */
#define WM8904_ADCR_ENA_WIDTH						 1							/* ADCR_ENA */

/*
 * R20 (0x14) - Clock Rates 0
 */
#define WM8904_TOCLK_RATE_DIV16					0x4000							/* TOCLK_RATE_DIV16 */
#define WM8904_TOCLK_RATE_DIV16_MASK			0x4000							/* TOCLK_RATE_DIV16 */
#define WM8904_TOCLK_RATE_DIV16_SHIFT				14							/* TOCLK_RATE_DIV16 */
#define WM8904_TOCLK_RATE_DIV16_WIDTH				 1							/* TOCLK_RATE_DIV16 */
#define WM8904_TOCLK_RATE_X4					0x2000							/* TOCLK_RATE_X4 */
#define WM8904_TOCLK_RATE_X4_MASK				0x2000							/* TOCLK_RATE_X4 */
#define WM8904_TOCLK_RATE_X4_SHIFT					13							/* TOCLK_RATE_X4 */
#define WM8904_TOCLK_RATE_X4_WIDTH					 1							/* TOCLK_RATE_X4 */
#define WM8904_SR_MODE							0x1000							/* SR_MODE */
#define WM8904_SR_MODE_MASK						0x1000							/* SR_MODE */
#define WM8904_SR_MODE_SHIFT						12							/* SR_MODE */
#define WM8904_SR_MODE_WIDTH						 1							/* SR_MODE */
#define WM8904_MCLK_DIV							0x0001							/* MCLK_DIV */
#define WM8904_MCLK_DIV_MASK					0x0001							/* MCLK_DIV */
#define WM8904_MCLK_DIV_SHIFT						 0							/* MCLK_DIV */
#define WM8904_MCLK_DIV_WIDTH						 1							/* MCLK_DIV */

/*
 * R21 (0x15) - Clock Rates 1
 */
#define WM8904_CLK_SYS_RATE_MASK				0x3C00							/* CLK_SYS_RATE - [13:10] */
#define WM8904_CLK_SYS_RATE_SHIFT					10							/* CLK_SYS_RATE - [13:10] */
#define WM8904_CLK_SYS_RATE_WIDTH					 4							/* CLK_SYS_RATE - [13:10] */
#define WM8904_SAMPLE_RATE_MASK					0x0007							/* SAMPLE_RATE - [2:0] */
#define WM8904_SAMPLE_RATE_SHIFT					 0							/* SAMPLE_RATE - [2:0] */
#define WM8904_SAMPLE_RATE_WIDTH					 3							/* SAMPLE_RATE - [2:0] */

/*
 * R22 (0x16) - Clock Rates 2
 */
#define WM8904_MCLK_INV							0x8000							/* MCLK_INV */
#define WM8904_MCLK_INV_MASK					0x8000							/* MCLK_INV */
#define WM8904_MCLK_INV_SHIFT						15							/* MCLK_INV */
#define WM8904_MCLK_INV_WIDTH						 1							/* MCLK_INV */
#define WM8904_SYSCLK_SRC						0x4000							/* SYSCLK_SRC */
#define WM8904_SYSCLK_SRC_MASK					0x4000							/* SYSCLK_SRC */
#define WM8904_SYSCLK_SRC_SHIFT						14							/* SYSCLK_SRC */
#define WM8904_SYSCLK_SRC_WIDTH						 1							/* SYSCLK_SRC */
#define WM8904_TOCLK_RATE						0x1000							/* TOCLK_RATE */
#define WM8904_TOCLK_RATE_MASK					0x1000							/* TOCLK_RATE */
#define WM8904_TOCLK_RATE_SHIFT						12							/* TOCLK_RATE */
#define WM8904_TOCLK_RATE_WIDTH						 1							/* TOCLK_RATE */
#define WM8904_OPCLK_ENA						0x0008							/* OPCLK_ENA */
#define WM8904_OPCLK_ENA_MASK					0x0008							/* OPCLK_ENA */
#define WM8904_OPCLK_ENA_SHIFT						 3							/* OPCLK_ENA */
#define WM8904_OPCLK_ENA_WIDTH						 1							/* OPCLK_ENA */
#define WM8904_CLK_SYS_ENA						0x0004							/* CLK_SYS_ENA */
#define WM8904_CLK_SYS_ENA_MASK					0x0004							/* CLK_SYS_ENA */
#define WM8904_CLK_SYS_ENA_SHIFT					 2							/* CLK_SYS_ENA */
#define WM8904_CLK_SYS_ENA_WIDTH					 1							/* CLK_SYS_ENA */
#define WM8904_CLK_DSP_ENA						0x0002							/* CLK_DSP_ENA */
#define WM8904_CLK_DSP_ENA_MASK					0x0002							/* CLK_DSP_ENA */
#define WM8904_CLK_DSP_ENA_SHIFT					 1							/* CLK_DSP_ENA */
#define WM8904_CLK_DSP_ENA_WIDTH					 1							/* CLK_DSP_ENA */
#define WM8904_TOCLK_ENA						0x0001							/* TOCLK_ENA */
#define WM8904_TOCLK_ENA_MASK					0x0001							/* TOCLK_ENA */
#define WM8904_TOCLK_ENA_SHIFT						 0							/* TOCLK_ENA */
#define WM8904_TOCLK_ENA_WIDTH						 1							/* TOCLK_ENA */

/*
 * R24 (0x18) - Audio Interface 0
 */
#define WM8904_DACL_DATINV						0x1000							/* DACL_DATINV */
#define WM8904_DACL_DATINV_MASK					0x1000							/* DACL_DATINV */
#define WM8904_DACL_DATINV_SHIFT					12							/* DACL_DATINV */
#define WM8904_DACL_DATINV_WIDTH					 1							/* DACL_DATINV */
#define WM8904_DACR_DATINV						0x0800							/* DACR_DATINV */
#define WM8904_DACR_DATINV_MASK					0x0800							/* DACR_DATINV */
#define WM8904_DACR_DATINV_SHIFT					11							/* DACR_DATINV */
#define WM8904_DACR_DATINV_WIDTH					 1							/* DACR_DATINV */
#define WM8904_DAC_BOOST_MASK					0x0600							/* DAC_BOOST - [10:9] */
#define WM8904_DAC_BOOST_SHIFT						 9							/* DAC_BOOST - [10:9] */
#define WM8904_DAC_BOOST_WIDTH						 2							/* DAC_BOOST - [10:9] */
#define WM8904_LOOPBACK							0x0100							/* LOOPBACK */
#define WM8904_LOOPBACK_MASK					0x0100							/* LOOPBACK */
#define WM8904_LOOPBACK_SHIFT						 8							/* LOOPBACK */
#define WM8904_LOOPBACK_WIDTH						 1							/* LOOPBACK */
#define WM8904_AIFADCL_SRC						0x0080							/* AIFADCL_SRC */
#define WM8904_AIFADCL_SRC_MASK					0x0080							/* AIFADCL_SRC */
#define WM8904_AIFADCL_SRC_SHIFT					 7							/* AIFADCL_SRC */
#define WM8904_AIFADCL_SRC_WIDTH					 1							/* AIFADCL_SRC */
#define WM8904_AIFADCR_SRC						0x0040							/* AIFADCR_SRC */
#define WM8904_AIFADCR_SRC_MASK					0x0040							/* AIFADCR_SRC */
#define WM8904_AIFADCR_SRC_SHIFT					 6							/* AIFADCR_SRC */
#define WM8904_AIFADCR_SRC_WIDTH					 1							/* AIFADCR_SRC */
#define WM8904_AIFDACL_SRC						0x0020							/* AIFDACL_SRC */
#define WM8904_AIFDACL_SRC_MASK					0x0020							/* AIFDACL_SRC */
#define WM8904_AIFDACL_SRC_SHIFT					 5							/* AIFDACL_SRC */
#define WM8904_AIFDACL_SRC_WIDTH					 1							/* AIFDACL_SRC */
#define WM8904_AIFDACR_SRC						0x0010							/* AIFDACR_SRC */
#define WM8904_AIFDACR_SRC_MASK					0x0010							/* AIFDACR_SRC */
#define WM8904_AIFDACR_SRC_SHIFT					 4							/* AIFDACR_SRC */
#define WM8904_AIFDACR_SRC_WIDTH					 1							/* AIFDACR_SRC */
#define WM8904_ADC_COMP							0x0008							/* ADC_COMP */
#define WM8904_ADC_COMP_MASK					0x0008							/* ADC_COMP */
#define WM8904_ADC_COMP_SHIFT						 3							/* ADC_COMP */
#define WM8904_ADC_COMP_WIDTH						 1							/* ADC_COMP */
#define WM8904_ADC_COMPMODE						0x0004							/* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_MASK				0x0004							/* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_SHIFT					 2							/* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE_WIDTH					 1							/* ADC_COMPMODE */
#define WM8904_DAC_COMP							0x0002							/* DAC_COMP */
#define WM8904_DAC_COMP_MASK					0x0002							/* DAC_COMP */
#define WM8904_DAC_COMP_SHIFT						 1							/* DAC_COMP */
#define WM8904_DAC_COMP_WIDTH						 1							/* DAC_COMP */
#define WM8904_DAC_COMPMODE						0x0001							/* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_MASK				0x0001							/* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_SHIFT					 0							/* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE_WIDTH					 1							/* DAC_COMPMODE */

/*
 * R25 (0x19) - Audio Interface 1
 */
#define WM8904_AIFDAC_TDM						0x2000							/* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_MASK					0x2000							/* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_SHIFT						13							/* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_WIDTH						 1							/* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM_CHAN					0x1000							/* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_MASK				0x1000							/* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_SHIFT				12							/* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN_WIDTH				 1							/* AIFDAC_TDM_CHAN */
#define WM8904_AIFADC_TDM						0x0800							/* AIFADC_TDM */
#define WM8904_AIFADC_TDM_MASK					0x0800							/* AIFADC_TDM */
#define WM8904_AIFADC_TDM_SHIFT						11							/* AIFADC_TDM */
#define WM8904_AIFADC_TDM_WIDTH						 1							/* AIFADC_TDM */
#define WM8904_AIFADC_TDM_CHAN					0x0400							/* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_MASK				0x0400							/* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_SHIFT				10							/* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN_WIDTH				 1							/* AIFADC_TDM_CHAN */
#define WM8904_AIF_TRIS							0x0100							/* AIF_TRIS */
#define WM8904_AIF_TRIS_MASK					0x0100							/* AIF_TRIS */
#define WM8904_AIF_TRIS_SHIFT						 8							/* AIF_TRIS */
#define WM8904_AIF_TRIS_WIDTH						 1							/* AIF_TRIS */
#define WM8904_AIF_BCLK_INV						0x0080							/* AIF_BCLK_INV */
#define WM8904_AIF_BCLK_INV_MASK				0x0080							/* AIF_BCLK_INV */
#define WM8904_AIF_BCLK_INV_SHIFT					 7							/* AIF_BCLK_INV */
#define WM8904_AIF_BCLK_INV_WIDTH					 1							/* AIF_BCLK_INV */
#define WM8904_BCLK_DIR							0x0040							/* BCLK_DIR */
#define WM8904_BCLK_DIR_MASK					0x0040							/* BCLK_DIR */
#define WM8904_BCLK_DIR_SHIFT						 6							/* BCLK_DIR */
#define WM8904_BCLK_DIR_WIDTH						 1							/* BCLK_DIR */
#define WM8904_AIF_LRCLK_INV					0x0010							/* AIF_LRCLK_INV */
#define WM8904_AIF_LRCLK_INV_MASK				0x0010							/* AIF_LRCLK_INV */
#define WM8904_AIF_LRCLK_INV_SHIFT					 4							/* AIF_LRCLK_INV */
#define WM8904_AIF_LRCLK_INV_WIDTH					 1							/* AIF_LRCLK_INV */
#define WM8904_AIF_WL_MASK						0x000C							/* AIF_WL - [3:2] */
#define WM8904_AIF_WL_SHIFT							 2							/* AIF_WL - [3:2] */
#define WM8904_AIF_WL_WIDTH							 2							/* AIF_WL - [3:2] */
#define WM8904_AIF_FMT_MASK						0x0003							/* AIF_FMT - [1:0] */
#define WM8904_AIF_FMT_SHIFT						 0							/* AIF_FMT - [1:0] */
#define WM8904_AIF_FMT_WIDTH						 2							/* AIF_FMT - [1:0] */

/*
 * R26 (0x1A) - Audio Interface 2
 */
#define WM8904_OPCLK_DIV_MASK					0x0F00							/* OPCLK_DIV - [11:8] */
#define WM8904_OPCLK_DIV_SHIFT						 8							/* OPCLK_DIV - [11:8] */
#define WM8904_OPCLK_DIV_WIDTH						 4							/* OPCLK_DIV - [11:8] */
#define WM8904_BCLK_DIV_MASK					0x001F							/* BCLK_DIV - [4:0] */
#define WM8904_BCLK_DIV_SHIFT						 0							/* BCLK_DIV - [4:0] */
#define WM8904_BCLK_DIV_WIDTH						 5							/* BCLK_DIV - [4:0] */

/*
 * R27 (0x1B) - Audio Interface 3
 */
#define WM8904_LRCLK_DIR						0x0800							/* LRCLK_DIR */
#define WM8904_LRCLK_DIR_MASK					0x0800							/* LRCLK_DIR */
#define WM8904_LRCLK_DIR_SHIFT						11							/* LRCLK_DIR */
#define WM8904_LRCLK_DIR_WIDTH						 1							/* LRCLK_DIR */
#define WM8904_LRCLK_RATE_MASK					0x07FF							/* LRCLK_RATE - [10:0] */
#define WM8904_LRCLK_RATE_SHIFT						 0							/* LRCLK_RATE - [10:0] */
#define WM8904_LRCLK_RATE_WIDTH						11							/* LRCLK_RATE - [10:0] */

/*
 * R30 (0x1E) - DAC Digital Volume Left
 */
#define WM8904_DAC_VU							0x0100							/* DAC_VU */
#define WM8904_DAC_VU_MASK						0x0100							/* DAC_VU */
#define WM8904_DAC_VU_SHIFT							 8							/* DAC_VU */
#define WM8904_DAC_VU_WIDTH							 1							/* DAC_VU */
#define WM8904_DACL_VOL_MASK					0x00FF							/* DACL_VOL - [7:0] */
#define WM8904_DACL_VOL_SHIFT						 0							/* DACL_VOL - [7:0] */
#define WM8904_DACL_VOL_WIDTH						 8							/* DACL_VOL - [7:0] */

/*
 * R31 (0x1F) - DAC Digital Volume Right
 */
#define WM8904_DAC_VU							0x0100							/* DAC_VU */
#define WM8904_DAC_VU_MASK						0x0100							/* DAC_VU */
#define WM8904_DAC_VU_SHIFT							 8							/* DAC_VU */
#define WM8904_DAC_VU_WIDTH							 1							/* DAC_VU */
#define WM8904_DACR_VOL_MASK					0x00FF							/* DACR_VOL - [7:0] */
#define WM8904_DACR_VOL_SHIFT						 0							/* DACR_VOL - [7:0] */
#define WM8904_DACR_VOL_WIDTH						 8							/* DACR_VOL - [7:0] */

/*
 * R32 (0x20) - DAC Digital 0
 */
#define WM8904_ADCL_DAC_SVOL_MASK				0x0F00							/* ADCL_DAC_SVOL - [11:8] */
#define WM8904_ADCL_DAC_SVOL_SHIFT					 8							/* ADCL_DAC_SVOL - [11:8] */
#define WM8904_ADCL_DAC_SVOL_WIDTH					 4							/* ADCL_DAC_SVOL - [11:8] */
#define WM8904_ADCR_DAC_SVOL_MASK				0x00F0							/* ADCR_DAC_SVOL - [7:4] */
#define WM8904_ADCR_DAC_SVOL_SHIFT					 4							/* ADCR_DAC_SVOL - [7:4] */
#define WM8904_ADCR_DAC_SVOL_WIDTH					 4							/* ADCR_DAC_SVOL - [7:4] */
#define WM8904_ADC_TO_DACL_MASK					0x000C							/* ADC_TO_DACL - [3:2] */
#define WM8904_ADC_TO_DACL_SHIFT					 2							/* ADC_TO_DACL - [3:2] */
#define WM8904_ADC_TO_DACL_WIDTH					 2							/* ADC_TO_DACL - [3:2] */
#define WM8904_ADC_TO_DACR_MASK					0x0003							/* ADC_TO_DACR - [1:0] */
#define WM8904_ADC_TO_DACR_SHIFT					 0							/* ADC_TO_DACR - [1:0] */
#define WM8904_ADC_TO_DACR_WIDTH					 2							/* ADC_TO_DACR - [1:0] */

/*
 * R33 (0x21) - DAC Digital 1
 */
#define WM8904_DAC_MONO							0x1000							/* DAC_MONO */
#define WM8904_DAC_MONO_MASK					0x1000							/* DAC_MONO */
#define WM8904_DAC_MONO_SHIFT						12							/* DAC_MONO */
#define WM8904_DAC_MONO_WIDTH						 1							/* DAC_MONO */
#define WM8904_DAC_SB_FILT						0x0800							/* DAC_SB_FILT */
#define WM8904_DAC_SB_FILT_MASK					0x0800							/* DAC_SB_FILT */
#define WM8904_DAC_SB_FILT_SHIFT					11							/* DAC_SB_FILT */
#define WM8904_DAC_SB_FILT_WIDTH					 1							/* DAC_SB_FILT */
#define WM8904_DAC_MUTERATE						0x0400							/* DAC_MUTERATE */
#define WM8904_DAC_MUTERATE_MASK				0x0400							/* DAC_MUTERATE */
#define WM8904_DAC_MUTERATE_SHIFT					10							/* DAC_MUTERATE */
#define WM8904_DAC_MUTERATE_WIDTH					 1							/* DAC_MUTERATE */
#define WM8904_DAC_UNMUTE_RAMP					0x0200							/* DAC_UNMUTE_RAMP */
#define WM8904_DAC_UNMUTE_RAMP_MASK				0x0200							/* DAC_UNMUTE_RAMP */
#define WM8904_DAC_UNMUTE_RAMP_SHIFT				 9							/* DAC_UNMUTE_RAMP */
#define WM8904_DAC_UNMUTE_RAMP_WIDTH				 1							/* DAC_UNMUTE_RAMP */
#define WM8904_DAC_OSR128						0x0040							/* DAC_OSR128 */
#define WM8904_DAC_OSR128_MASK					0x0040							/* DAC_OSR128 */
#define WM8904_DAC_OSR128_SHIFT						 6							/* DAC_OSR128 */
#define WM8904_DAC_OSR128_WIDTH						 1							/* DAC_OSR128 */
#define WM8904_DAC_MUTE							0x0008							/* DAC_MUTE */
#define WM8904_DAC_MUTE_MASK					0x0008							/* DAC_MUTE */
#define WM8904_DAC_MUTE_SHIFT						 3							/* DAC_MUTE */
#define WM8904_DAC_MUTE_WIDTH						 1							/* DAC_MUTE */
#define WM8904_DEEMPH_MASK						0x0006							/* DEEMPH - [2:1] */
#define WM8904_DEEMPH_SHIFT							 1							/* DEEMPH - [2:1] */
#define WM8904_DEEMPH_WIDTH							 2							/* DEEMPH - [2:1] */

/*
 * R36 (0x24) - ADC Digital Volume Left
 */
#define WM8904_ADC_VU							0x0100							/* ADC_VU */
#define WM8904_ADC_VU_MASK						0x0100							/* ADC_VU */
#define WM8904_ADC_VU_SHIFT							 8							/* ADC_VU */
#define WM8904_ADC_VU_WIDTH							 1							/* ADC_VU */
#define WM8904_ADCL_VOL_MASK					0x00FF							/* ADCL_VOL - [7:0] */
#define WM8904_ADCL_VOL_SHIFT						 0							/* ADCL_VOL - [7:0] */
#define WM8904_ADCL_VOL_WIDTH						 8							/* ADCL_VOL - [7:0] */

/*
 * R37 (0x25) - ADC Digital Volume Right
 */
#define WM8904_ADC_VU							0x0100							/* ADC_VU */
#define WM8904_ADC_VU_MASK						0x0100							/* ADC_VU */
#define WM8904_ADC_VU_SHIFT							 8							/* ADC_VU */
#define WM8904_ADC_VU_WIDTH							 1							/* ADC_VU */
#define WM8904_ADCR_VOL_MASK					0x00FF							/* ADCR_VOL - [7:0] */
#define WM8904_ADCR_VOL_SHIFT						 0							/* ADCR_VOL - [7:0] */
#define WM8904_ADCR_VOL_WIDTH						 8							/* ADCR_VOL - [7:0] */

/*
 * R38 (0x26) - ADC Digital 0
 */
#define WM8904_ADC_HPF_CUT_MASK					0x0060							/* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT_SHIFT					 5							/* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT_WIDTH					 2							/* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF							0x0010							/* ADC_HPF */
#define WM8904_ADC_HPF_MASK						0x0010							/* ADC_HPF */
#define WM8904_ADC_HPF_SHIFT						 4							/* ADC_HPF */
#define WM8904_ADC_HPF_WIDTH						 1							/* ADC_HPF */
#define WM8904_ADCL_DATINV						0x0002							/* ADCL_DATINV */
#define WM8904_ADCL_DATINV_MASK					0x0002							/* ADCL_DATINV */
#define WM8904_ADCL_DATINV_SHIFT					 1							/* ADCL_DATINV */
#define WM8904_ADCL_DATINV_WIDTH					 1							/* ADCL_DATINV */
#define WM8904_ADCR_DATINV						0x0001							/* ADCR_DATINV */
#define WM8904_ADCR_DATINV_MASK					0x0001							/* ADCR_DATINV */
#define WM8904_ADCR_DATINV_SHIFT					 0							/* ADCR_DATINV */
#define WM8904_ADCR_DATINV_WIDTH					 1							/* ADCR_DATINV */

/*
 * R39 (0x27) - Digital Microphone 0
 */
#define WM8904_DMIC_ENA							0x1000							/* DMIC_ENA */
#define WM8904_DMIC_ENA_MASK					0x1000							/* DMIC_ENA */
#define WM8904_DMIC_ENA_SHIFT						12							/* DMIC_ENA */
#define WM8904_DMIC_ENA_WIDTH						 1							/* DMIC_ENA */
#define WM8904_DMIC_SRC							0x0800							/* DMIC_SRC */
#define WM8904_DMIC_SRC_MASK					0x0800							/* DMIC_SRC */
#define WM8904_DMIC_SRC_SHIFT						11							/* DMIC_SRC */
#define WM8904_DMIC_SRC_WIDTH						 1							/* DMIC_SRC */

/*
 * R40 (0x28) - DRC 0
 */
#define WM8904_DRC_ENA							0x8000							/* DRC_ENA */
#define WM8904_DRC_ENA_MASK						0x8000							/* DRC_ENA */
#define WM8904_DRC_ENA_SHIFT						15							/* DRC_ENA */
#define WM8904_DRC_ENA_WIDTH						 1							/* DRC_ENA */
#define WM8904_DRC_DAC_PATH						0x4000							/* DRC_DAC_PATH */
#define WM8904_DRC_DAC_PATH_MASK				0x4000							/* DRC_DAC_PATH */
#define WM8904_DRC_DAC_PATH_SHIFT					14							/* DRC_DAC_PATH */
#define WM8904_DRC_DAC_PATH_WIDTH					 1							/* DRC_DAC_PATH */
#define WM8904_DRC_GS_HYST_LVL_MASK				0x1800							/* DRC_GS_HYST_LVL - [12:11] */
#define WM8904_DRC_GS_HYST_LVL_SHIFT				11							/* DRC_GS_HYST_LVL - [12:11] */
#define WM8904_DRC_GS_HYST_LVL_WIDTH				 2							/* DRC_GS_HYST_LVL - [12:11] */
#define WM8904_DRC_STARTUP_GAIN_MASK			0x07C0							/* DRC_STARTUP_GAIN - [10:6] */
#define WM8904_DRC_STARTUP_GAIN_SHIFT				 6							/* DRC_STARTUP_GAIN - [10:6] */
#define WM8904_DRC_STARTUP_GAIN_WIDTH				 5							/* DRC_STARTUP_GAIN - [10:6] */
#define WM8904_DRC_FF_DELAY						0x0020							/* DRC_FF_DELAY */
#define WM8904_DRC_FF_DELAY_MASK				0x0020							/* DRC_FF_DELAY */
#define WM8904_DRC_FF_DELAY_SHIFT					 5							/* DRC_FF_DELAY */
#define WM8904_DRC_FF_DELAY_WIDTH					 1							/* DRC_FF_DELAY */
#define WM8904_DRC_GS_ENA						0x0008							/* DRC_GS_ENA */
#define WM8904_DRC_GS_ENA_MASK					0x0008							/* DRC_GS_ENA */
#define WM8904_DRC_GS_ENA_SHIFT						 3							/* DRC_GS_ENA */
#define WM8904_DRC_GS_ENA_WIDTH						 1							/* DRC_GS_ENA */
#define WM8904_DRC_QR							0x0004							/* DRC_QR */
#define WM8904_DRC_QR_MASK						0x0004							/* DRC_QR */
#define WM8904_DRC_QR_SHIFT							 2							/* DRC_QR */
#define WM8904_DRC_QR_WIDTH							 1							/* DRC_QR */
#define WM8904_DRC_ANTICLIP						0x0002							/* DRC_ANTICLIP */
#define WM8904_DRC_ANTICLIP_MASK				0x0002							/* DRC_ANTICLIP */
#define WM8904_DRC_ANTICLIP_SHIFT					 1							/* DRC_ANTICLIP */
#define WM8904_DRC_ANTICLIP_WIDTH					 1							/* DRC_ANTICLIP */
#define WM8904_DRC_GS_HYST						0x0001							/* DRC_GS_HYST */
#define WM8904_DRC_GS_HYST_MASK					0x0001							/* DRC_GS_HYST */
#define WM8904_DRC_GS_HYST_SHIFT					 0							/* DRC_GS_HYST */
#define WM8904_DRC_GS_HYST_WIDTH					 1							/* DRC_GS_HYST */

/*
 * R41 (0x29) - DRC 1
 */
#define WM8904_DRC_ATK_MASK						0xF000							/* DRC_ATK - [15:12] */
#define WM8904_DRC_ATK_SHIFT						12							/* DRC_ATK - [15:12] */
#define WM8904_DRC_ATK_WIDTH						 4							/* DRC_ATK - [15:12] */
#define WM8904_DRC_DCY_MASK						0x0F00							/* DRC_DCY - [11:8] */
#define WM8904_DRC_DCY_SHIFT						 8							/* DRC_DCY - [11:8] */
#define WM8904_DRC_DCY_WIDTH						 4							/* DRC_DCY - [11:8] */
#define WM8904_DRC_QR_THR_MASK					0x00C0							/* DRC_QR_THR - [7:6] */
#define WM8904_DRC_QR_THR_SHIFT						 6							/* DRC_QR_THR - [7:6] */
#define WM8904_DRC_QR_THR_WIDTH						 2							/* DRC_QR_THR - [7:6] */
#define WM8904_DRC_QR_DCY_MASK					0x0030							/* DRC_QR_DCY - [5:4] */
#define WM8904_DRC_QR_DCY_SHIFT						 4							/* DRC_QR_DCY - [5:4] */
#define WM8904_DRC_QR_DCY_WIDTH						 2							/* DRC_QR_DCY - [5:4] */
#define WM8904_DRC_MINGAIN_MASK					0x000C							/* DRC_MINGAIN - [3:2] */
#define WM8904_DRC_MINGAIN_SHIFT					 2							/* DRC_MINGAIN - [3:2] */
#define WM8904_DRC_MINGAIN_WIDTH					 2							/* DRC_MINGAIN - [3:2] */
#define WM8904_DRC_MAXGAIN_MASK					0x0003							/* DRC_MAXGAIN - [1:0] */
#define WM8904_DRC_MAXGAIN_SHIFT					 0							/* DRC_MAXGAIN - [1:0] */
#define WM8904_DRC_MAXGAIN_WIDTH					 2							/* DRC_MAXGAIN - [1:0] */

/*
 * R42 (0x2A) - DRC 2
 */
#define WM8904_DRC_HI_COMP_MASK					0x0038							/* DRC_HI_COMP - [5:3] */
#define WM8904_DRC_HI_COMP_SHIFT					 3							/* DRC_HI_COMP - [5:3] */
#define WM8904_DRC_HI_COMP_WIDTH					 3							/* DRC_HI_COMP - [5:3] */
#define WM8904_DRC_LO_COMP_MASK					0x0007							/* DRC_LO_COMP - [2:0] */
#define WM8904_DRC_LO_COMP_SHIFT					 0							/* DRC_LO_COMP - [2:0] */
#define WM8904_DRC_LO_COMP_WIDTH					 3							/* DRC_LO_COMP - [2:0] */

/*
 * R43 (0x2B) - DRC 3
 */
#define WM8904_DRC_KNEE_IP_MASK					0x07E0							/* DRC_KNEE_IP - [10:5] */
#define WM8904_DRC_KNEE_IP_SHIFT					 5							/* DRC_KNEE_IP - [10:5] */
#define WM8904_DRC_KNEE_IP_WIDTH					 6							/* DRC_KNEE_IP - [10:5] */
#define WM8904_DRC_KNEE_OP_MASK					0x001F							/* DRC_KNEE_OP - [4:0] */
#define WM8904_DRC_KNEE_OP_SHIFT					 0							/* DRC_KNEE_OP - [4:0] */
#define WM8904_DRC_KNEE_OP_WIDTH					 5							/* DRC_KNEE_OP - [4:0] */

/*
 * R44 (0x2C) - Analogue Left Input 0
 */
#define WM8904_LINMUTE							0x0080							/* LINMUTE */
#define WM8904_LINMUTE_MASK						0x0080							/* LINMUTE */
#define WM8904_LINMUTE_SHIFT						 7							/* LINMUTE */
#define WM8904_LINMUTE_WIDTH						 1							/* LINMUTE */
#define WM8904_LIN_VOL_MASK						0x001F							/* LIN_VOL - [4:0] */
#define WM8904_LIN_VOL_SHIFT						 0							/* LIN_VOL - [4:0] */
#define WM8904_LIN_VOL_WIDTH						 5							/* LIN_VOL - [4:0] */

/*
 * R45 (0x2D) - Analogue Right Input 0
 */
#define WM8904_RINMUTE							0x0080							/* RINMUTE */
#define WM8904_RINMUTE_MASK						0x0080							/* RINMUTE */
#define WM8904_RINMUTE_SHIFT						 7							/* RINMUTE */
#define WM8904_RINMUTE_WIDTH						 1							/* RINMUTE */
#define WM8904_RIN_VOL_MASK						0x001F							/* RIN_VOL - [4:0] */
#define WM8904_RIN_VOL_SHIFT						 0							/* RIN_VOL - [4:0] */
#define WM8904_RIN_VOL_WIDTH						 5							/* RIN_VOL - [4:0] */

/*
 * R46 (0x2E) - Analogue Left Input 1
 */
#define WM8904_INL_CM_ENA						0x0040							/* INL_CM_ENA */
#define WM8904_INL_CM_ENA_MASK					0x0040							/* INL_CM_ENA */
#define WM8904_INL_CM_ENA_SHIFT						 6							/* INL_CM_ENA */
#define WM8904_INL_CM_ENA_WIDTH						 1							/* INL_CM_ENA */
#define WM8904_L_IP_SEL_N_MASK					0x0030							/* L_IP_SEL_N - [5:4] */
#define WM8904_L_IP_SEL_N_SHIFT						 4							/* L_IP_SEL_N - [5:4] */
#define WM8904_L_IP_SEL_N_WIDTH						 2							/* L_IP_SEL_N - [5:4] */
#define WM8904_L_IP_SEL_P_MASK					0x000C							/* L_IP_SEL_P - [3:2] */
#define WM8904_L_IP_SEL_P_SHIFT						 2							/* L_IP_SEL_P - [3:2] */
#define WM8904_L_IP_SEL_P_WIDTH						 2							/* L_IP_SEL_P - [3:2] */
#define WM8904_L_MODE_MASK						0x0003							/* L_MODE - [1:0] */
#define WM8904_L_MODE_SHIFT							 0							/* L_MODE - [1:0] */
#define WM8904_L_MODE_WIDTH							 2							/* L_MODE - [1:0] */

/*
 * R47 (0x2F) - Analogue Right Input 1
 */
#define WM8904_INR_CM_ENA						0x0040							/* INR_CM_ENA */
#define WM8904_INR_CM_ENA_MASK					0x0040							/* INR_CM_ENA */
#define WM8904_INR_CM_ENA_SHIFT						 6							/* INR_CM_ENA */
#define WM8904_INR_CM_ENA_WIDTH						 1							/* INR_CM_ENA */
#define WM8904_R_IP_SEL_N_MASK					0x0030							/* R_IP_SEL_N - [5:4] */
#define WM8904_R_IP_SEL_N_SHIFT						 4							/* R_IP_SEL_N - [5:4] */
#define WM8904_R_IP_SEL_N_WIDTH						 2							/* R_IP_SEL_N - [5:4] */
#define WM8904_R_IP_SEL_P_MASK					0x000C							/* R_IP_SEL_P - [3:2] */
#define WM8904_R_IP_SEL_P_SHIFT						 2							/* R_IP_SEL_P - [3:2] */
#define WM8904_R_IP_SEL_P_WIDTH						 2							/* R_IP_SEL_P - [3:2] */
#define WM8904_R_MODE_MASK						0x0003							/* R_MODE - [1:0] */
#define WM8904_R_MODE_SHIFT							 0							/* R_MODE - [1:0] */
#define WM8904_R_MODE_WIDTH							 2							/* R_MODE - [1:0] */

/*
 * R57 (0x39) - Analogue OUT1 Left
 */
#define WM8904_HPOUTL_MUTE						0x0100							/* HPOUTL_MUTE */
#define WM8904_HPOUTL_MUTE_MASK					0x0100							/* HPOUTL_MUTE */
#define WM8904_HPOUTL_MUTE_SHIFT					 8							/* HPOUTL_MUTE */
#define WM8904_HPOUTL_MUTE_WIDTH					 1							/* HPOUTL_MUTE */
#define WM8904_HPOUT_VU							0x0080							/* HPOUT_VU */
#define WM8904_HPOUT_VU_MASK					0x0080							/* HPOUT_VU */
#define WM8904_HPOUT_VU_SHIFT						 7							/* HPOUT_VU */
#define WM8904_HPOUT_VU_WIDTH						 1							/* HPOUT_VU */
#define WM8904_HPOUTLZC							0x0040							/* HPOUTLZC */
#define WM8904_HPOUTLZC_MASK					0x0040							/* HPOUTLZC */
#define WM8904_HPOUTLZC_SHIFT						 6							/* HPOUTLZC */
#define WM8904_HPOUTLZC_WIDTH						 1							/* HPOUTLZC */
#define WM8904_HPOUTL_VOL_MASK					0x003F							/* HPOUTL_VOL - [5:0] */
#define WM8904_HPOUTL_VOL_SHIFT						 0							/* HPOUTL_VOL - [5:0] */
#define WM8904_HPOUTL_VOL_WIDTH						 6							/* HPOUTL_VOL - [5:0] */

/*
 * R58 (0x3A) - Analogue OUT1 Right
 */
#define WM8904_HPOUTR_MUTE						0x0100							/* HPOUTR_MUTE */
#define WM8904_HPOUTR_MUTE_MASK					0x0100							/* HPOUTR_MUTE */
#define WM8904_HPOUTR_MUTE_SHIFT					 8							/* HPOUTR_MUTE */
#define WM8904_HPOUTR_MUTE_WIDTH					 1							/* HPOUTR_MUTE */
#define WM8904_HPOUT_VU							0x0080							/* HPOUT_VU */
#define WM8904_HPOUT_VU_MASK					0x0080							/* HPOUT_VU */
#define WM8904_HPOUT_VU_SHIFT						 7							/* HPOUT_VU */
#define WM8904_HPOUT_VU_WIDTH						 1							/* HPOUT_VU */
#define WM8904_HPOUTRZC							0x0040							/* HPOUTRZC */
#define WM8904_HPOUTRZC_MASK					0x0040							/* HPOUTRZC */
#define WM8904_HPOUTRZC_SHIFT						 6							/* HPOUTRZC */
#define WM8904_HPOUTRZC_WIDTH						 1							/* HPOUTRZC */
#define WM8904_HPOUTR_VOL_MASK					0x003F							/* HPOUTR_VOL - [5:0] */
#define WM8904_HPOUTR_VOL_SHIFT						 0							/* HPOUTR_VOL - [5:0] */
#define WM8904_HPOUTR_VOL_WIDTH						 6							/* HPOUTR_VOL - [5:0] */

/*
 * R59 (0x3B) - Analogue OUT2 Left
 */
#define WM8904_LINEOUTL_MUTE					0x0100							/* LINEOUTL_MUTE */
#define WM8904_LINEOUTL_MUTE_MASK				0x0100							/* LINEOUTL_MUTE */
#define WM8904_LINEOUTL_MUTE_SHIFT					 8							/* LINEOUTL_MUTE */
#define WM8904_LINEOUTL_MUTE_WIDTH					 1							/* LINEOUTL_MUTE */
#define WM8904_LINEOUT_VU						0x0080							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_MASK					0x0080							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_SHIFT						 7							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_WIDTH						 1							/* LINEOUT_VU */
#define WM8904_LINEOUTLZC						0x0040							/* LINEOUTLZC */
#define WM8904_LINEOUTLZC_MASK					0x0040							/* LINEOUTLZC */
#define WM8904_LINEOUTLZC_SHIFT						 6							/* LINEOUTLZC */
#define WM8904_LINEOUTLZC_WIDTH						 1							/* LINEOUTLZC */
#define WM8904_LINEOUTL_VOL_MASK				0x003F							/* LINEOUTL_VOL - [5:0] */
#define WM8904_LINEOUTL_VOL_SHIFT					 0							/* LINEOUTL_VOL - [5:0] */
#define WM8904_LINEOUTL_VOL_WIDTH					 6							/* LINEOUTL_VOL - [5:0] */

/*
 * R60 (0x3C) - Analogue OUT2 Right
 */
#define WM8904_LINEOUTR_MUTE					0x0100							/* LINEOUTR_MUTE */
#define WM8904_LINEOUTR_MUTE_MASK				0x0100							/* LINEOUTR_MUTE */
#define WM8904_LINEOUTR_MUTE_SHIFT					 8							/* LINEOUTR_MUTE */
#define WM8904_LINEOUTR_MUTE_WIDTH					 1							/* LINEOUTR_MUTE */
#define WM8904_LINEOUT_VU						0x0080							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_MASK					0x0080							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_SHIFT						 7							/* LINEOUT_VU */
#define WM8904_LINEOUT_VU_WIDTH						 1							/* LINEOUT_VU */
#define WM8904_LINEOUTRZC						0x0040							/* LINEOUTRZC */
#define WM8904_LINEOUTRZC_MASK					0x0040							/* LINEOUTRZC */
#define WM8904_LINEOUTRZC_SHIFT						 6							/* LINEOUTRZC */
#define WM8904_LINEOUTRZC_WIDTH						 1							/* LINEOUTRZC */
#define WM8904_LINEOUTR_VOL_MASK				0x003F							/* LINEOUTR_VOL - [5:0] */
#define WM8904_LINEOUTR_VOL_SHIFT					 0							/* LINEOUTR_VOL - [5:0] */
#define WM8904_LINEOUTR_VOL_WIDTH					 6							/* LINEOUTR_VOL - [5:0] */

/*
 * R61 (0x3D) - Analogue OUT12 ZC
 */
#define WM8904_HPL_BYP_ENA						0x0008							/* HPL_BYP_ENA */
#define WM8904_HPL_BYP_ENA_MASK					0x0008							/* HPL_BYP_ENA */
#define WM8904_HPL_BYP_ENA_SHIFT					 3							/* HPL_BYP_ENA */
#define WM8904_HPL_BYP_ENA_WIDTH					 1							/* HPL_BYP_ENA */
#define WM8904_HPR_BYP_ENA						0x0004							/* HPR_BYP_ENA */
#define WM8904_HPR_BYP_ENA_MASK					0x0004							/* HPR_BYP_ENA */
#define WM8904_HPR_BYP_ENA_SHIFT					 2							/* HPR_BYP_ENA */
#define WM8904_HPR_BYP_ENA_WIDTH					 1							/* HPR_BYP_ENA */
#define WM8904_LINEOUTL_BYP_ENA					0x0002							/* LINEOUTL_BYP_ENA */
#define WM8904_LINEOUTL_BYP_ENA_MASK			0x0002							/* LINEOUTL_BYP_ENA */
#define WM8904_LINEOUTL_BYP_ENA_SHIFT				 1							/* LINEOUTL_BYP_ENA */
#define WM8904_LINEOUTL_BYP_ENA_WIDTH				 1							/* LINEOUTL_BYP_ENA */
#define WM8904_LINEOUTR_BYP_ENA					0x0001							/* LINEOUTR_BYP_ENA */
#define WM8904_LINEOUTR_BYP_ENA_MASK			0x0001							/* LINEOUTR_BYP_ENA */
#define WM8904_LINEOUTR_BYP_ENA_SHIFT				 0							/* LINEOUTR_BYP_ENA */
#define WM8904_LINEOUTR_BYP_ENA_WIDTH				 1							/* LINEOUTR_BYP_ENA */

/*
 * R67 (0x43) - DC Servo 0
 */
#define WM8904_DCS_ENA_CHAN_3					0x0008							/* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_MASK				0x0008							/* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_SHIFT					 3							/* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3_WIDTH					 1							/* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_2					0x0004							/* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_MASK				0x0004							/* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_SHIFT					 2							/* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2_WIDTH					 1							/* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_1					0x0002							/* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_MASK				0x0002							/* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_SHIFT					 1							/* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1_WIDTH					 1							/* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_0					0x0001							/* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_MASK				0x0001							/* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_SHIFT					 0							/* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0_WIDTH					 1							/* DCS_ENA_CHAN_0 */

/*
 * R68 (0x44) - DC Servo 1
 */
#define WM8904_DCS_TRIG_SINGLE_3				0x8000							/* DCS_TRIG_SINGLE_3 */
#define WM8904_DCS_TRIG_SINGLE_3_MASK			0x8000							/* DCS_TRIG_SINGLE_3 */
#define WM8904_DCS_TRIG_SINGLE_3_SHIFT				15							/* DCS_TRIG_SINGLE_3 */
#define WM8904_DCS_TRIG_SINGLE_3_WIDTH				 1							/* DCS_TRIG_SINGLE_3 */
#define WM8904_DCS_TRIG_SINGLE_2				0x4000							/* DCS_TRIG_SINGLE_2 */
#define WM8904_DCS_TRIG_SINGLE_2_MASK			0x4000							/* DCS_TRIG_SINGLE_2 */
#define WM8904_DCS_TRIG_SINGLE_2_SHIFT				14							/* DCS_TRIG_SINGLE_2 */
#define WM8904_DCS_TRIG_SINGLE_2_WIDTH				 1							/* DCS_TRIG_SINGLE_2 */
#define WM8904_DCS_TRIG_SINGLE_1				0x2000							/* DCS_TRIG_SINGLE_1 */
#define WM8904_DCS_TRIG_SINGLE_1_MASK			0x2000							/* DCS_TRIG_SINGLE_1 */
#define WM8904_DCS_TRIG_SINGLE_1_SHIFT				13							/* DCS_TRIG_SINGLE_1 */
#define WM8904_DCS_TRIG_SINGLE_1_WIDTH				 1							/* DCS_TRIG_SINGLE_1 */
#define WM8904_DCS_TRIG_SINGLE_0				0x1000							/* DCS_TRIG_SINGLE_0 */
#define WM8904_DCS_TRIG_SINGLE_0_MASK			0x1000							/* DCS_TRIG_SINGLE_0 */
#define WM8904_DCS_TRIG_SINGLE_0_SHIFT				12							/* DCS_TRIG_SINGLE_0 */
#define WM8904_DCS_TRIG_SINGLE_0_WIDTH				 1							/* DCS_TRIG_SINGLE_0 */
#define WM8904_DCS_TRIG_SERIES_3				0x0800							/* DCS_TRIG_SERIES_3 */
#define WM8904_DCS_TRIG_SERIES_3_MASK			0x0800							/* DCS_TRIG_SERIES_3 */
#define WM8904_DCS_TRIG_SERIES_3_SHIFT				11							/* DCS_TRIG_SERIES_3 */
#define WM8904_DCS_TRIG_SERIES_3_WIDTH				 1							/* DCS_TRIG_SERIES_3 */
#define WM8904_DCS_TRIG_SERIES_2				0x0400							/* DCS_TRIG_SERIES_2 */
#define WM8904_DCS_TRIG_SERIES_2_MASK			0x0400							/* DCS_TRIG_SERIES_2 */
#define WM8904_DCS_TRIG_SERIES_2_SHIFT				10							/* DCS_TRIG_SERIES_2 */
#define WM8904_DCS_TRIG_SERIES_2_WIDTH				 1							/* DCS_TRIG_SERIES_2 */
#define WM8904_DCS_TRIG_SERIES_1				0x0200							/* DCS_TRIG_SERIES_1 */
#define WM8904_DCS_TRIG_SERIES_1_MASK			0x0200							/* DCS_TRIG_SERIES_1 */
#define WM8904_DCS_TRIG_SERIES_1_SHIFT				 9							/* DCS_TRIG_SERIES_1 */
#define WM8904_DCS_TRIG_SERIES_1_WIDTH				 1							/* DCS_TRIG_SERIES_1 */
#define WM8904_DCS_TRIG_SERIES_0				0x0100							/* DCS_TRIG_SERIES_0 */
#define WM8904_DCS_TRIG_SERIES_0_MASK			0x0100							/* DCS_TRIG_SERIES_0 */
#define WM8904_DCS_TRIG_SERIES_0_SHIFT				 8							/* DCS_TRIG_SERIES_0 */
#define WM8904_DCS_TRIG_SERIES_0_WIDTH				 1							/* DCS_TRIG_SERIES_0 */
#define WM8904_DCS_TRIG_STARTUP_3				0x0080							/* DCS_TRIG_STARTUP_3 */
#define WM8904_DCS_TRIG_STARTUP_3_MASK			0x0080							/* DCS_TRIG_STARTUP_3 */
#define WM8904_DCS_TRIG_STARTUP_3_SHIFT				 7							/* DCS_TRIG_STARTUP_3 */
#define WM8904_DCS_TRIG_STARTUP_3_WIDTH				 1							/* DCS_TRIG_STARTUP_3 */
#define WM8904_DCS_TRIG_STARTUP_2				0x0040							/* DCS_TRIG_STARTUP_2 */
#define WM8904_DCS_TRIG_STARTUP_2_MASK			0x0040							/* DCS_TRIG_STARTUP_2 */
#define WM8904_DCS_TRIG_STARTUP_2_SHIFT				 6							/* DCS_TRIG_STARTUP_2 */
#define WM8904_DCS_TRIG_STARTUP_2_WIDTH				 1							/* DCS_TRIG_STARTUP_2 */
#define WM8904_DCS_TRIG_STARTUP_1				0x0020							/* DCS_TRIG_STARTUP_1 */
#define WM8904_DCS_TRIG_STARTUP_1_MASK			0x0020							/* DCS_TRIG_STARTUP_1 */
#define WM8904_DCS_TRIG_STARTUP_1_SHIFT				 5							/* DCS_TRIG_STARTUP_1 */
#define WM8904_DCS_TRIG_STARTUP_1_WIDTH				 1							/* DCS_TRIG_STARTUP_1 */
#define WM8904_DCS_TRIG_STARTUP_0				0x0010							/* DCS_TRIG_STARTUP_0 */
#define WM8904_DCS_TRIG_STARTUP_0_MASK			0x0010							/* DCS_TRIG_STARTUP_0 */
#define WM8904_DCS_TRIG_STARTUP_0_SHIFT				 4							/* DCS_TRIG_STARTUP_0 */
#define WM8904_DCS_TRIG_STARTUP_0_WIDTH				 1							/* DCS_TRIG_STARTUP_0 */
#define WM8904_DCS_TRIG_DAC_WR_3				0x0008							/* DCS_TRIG_DAC_WR_3 */
#define WM8904_DCS_TRIG_DAC_WR_3_MASK			0x0008							/* DCS_TRIG_DAC_WR_3 */
#define WM8904_DCS_TRIG_DAC_WR_3_SHIFT				 3							/* DCS_TRIG_DAC_WR_3 */
#define WM8904_DCS_TRIG_DAC_WR_3_WIDTH				 1							/* DCS_TRIG_DAC_WR_3 */
#define WM8904_DCS_TRIG_DAC_WR_2				0x0004							/* DCS_TRIG_DAC_WR_2 */
#define WM8904_DCS_TRIG_DAC_WR_2_MASK			0x0004							/* DCS_TRIG_DAC_WR_2 */
#define WM8904_DCS_TRIG_DAC_WR_2_SHIFT				 2							/* DCS_TRIG_DAC_WR_2 */
#define WM8904_DCS_TRIG_DAC_WR_2_WIDTH				 1							/* DCS_TRIG_DAC_WR_2 */
#define WM8904_DCS_TRIG_DAC_WR_1				0x0002							/* DCS_TRIG_DAC_WR_1 */
#define WM8904_DCS_TRIG_DAC_WR_1_MASK			0x0002							/* DCS_TRIG_DAC_WR_1 */
#define WM8904_DCS_TRIG_DAC_WR_1_SHIFT				 1							/* DCS_TRIG_DAC_WR_1 */
#define WM8904_DCS_TRIG_DAC_WR_1_WIDTH				 1							/* DCS_TRIG_DAC_WR_1 */
#define WM8904_DCS_TRIG_DAC_WR_0				0x0001							/* DCS_TRIG_DAC_WR_0 */
#define WM8904_DCS_TRIG_DAC_WR_0_MASK			0x0001							/* DCS_TRIG_DAC_WR_0 */
#define WM8904_DCS_TRIG_DAC_WR_0_SHIFT				 0							/* DCS_TRIG_DAC_WR_0 */
#define WM8904_DCS_TRIG_DAC_WR_0_WIDTH				 1							/* DCS_TRIG_DAC_WR_0 */

/*
 * R69 (0x45) - DC Servo 2
 */
#define WM8904_DCS_TIMER_PERIOD_23_MASK			0x0F00							/* DCS_TIMER_PERIOD_23 - [11:8] */
#define WM8904_DCS_TIMER_PERIOD_23_SHIFT			 8							/* DCS_TIMER_PERIOD_23 - [11:8] */
#define WM8904_DCS_TIMER_PERIOD_23_WIDTH			 4							/* DCS_TIMER_PERIOD_23 - [11:8] */
#define WM8904_DCS_TIMER_PERIOD_01_MASK			0x000F							/* DCS_TIMER_PERIOD_01 - [3:0] */
#define WM8904_DCS_TIMER_PERIOD_01_SHIFT			 0							/* DCS_TIMER_PERIOD_01 - [3:0] */
#define WM8904_DCS_TIMER_PERIOD_01_WIDTH			 4							/* DCS_TIMER_PERIOD_01 - [3:0] */

/*
 * R71 (0x47) - DC Servo 4
 */
#define WM8904_DCS_SERIES_NO_23_MASK			0x007F							/* DCS_SERIES_NO_23 - [6:0] */
#define WM8904_DCS_SERIES_NO_23_SHIFT				 0							/* DCS_SERIES_NO_23 - [6:0] */
#define WM8904_DCS_SERIES_NO_23_WIDTH				 7							/* DCS_SERIES_NO_23 - [6:0] */

/*
 * R72 (0x48) - DC Servo 5
 */
#define WM8904_DCS_SERIES_NO_01_MASK			0x007F							/* DCS_SERIES_NO_01 - [6:0] */
#define WM8904_DCS_SERIES_NO_01_SHIFT				 0							/* DCS_SERIES_NO_01 - [6:0] */
#define WM8904_DCS_SERIES_NO_01_WIDTH				 7							/* DCS_SERIES_NO_01 - [6:0] */

/*
 * R73 (0x49) - DC Servo 6
 */
#define WM8904_DCS_DAC_WR_VAL_3_MASK			0x00FF							/* DCS_DAC_WR_VAL_3 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_3_SHIFT				 0							/* DCS_DAC_WR_VAL_3 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_3_WIDTH				 8							/* DCS_DAC_WR_VAL_3 - [7:0] */

/*
 * R74 (0x4A) - DC Servo 7
 */
#define WM8904_DCS_DAC_WR_VAL_2_MASK			0x00FF							/* DCS_DAC_WR_VAL_2 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_2_SHIFT				 0							/* DCS_DAC_WR_VAL_2 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_2_WIDTH				 8							/* DCS_DAC_WR_VAL_2 - [7:0] */

/*
 * R75 (0x4B) - DC Servo 8
 */
#define WM8904_DCS_DAC_WR_VAL_1_MASK			0x00FF							/* DCS_DAC_WR_VAL_1 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_1_SHIFT				 0							/* DCS_DAC_WR_VAL_1 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_1_WIDTH				 8							/* DCS_DAC_WR_VAL_1 - [7:0] */

/*
 * R76 (0x4C) - DC Servo 9
 */
#define WM8904_DCS_DAC_WR_VAL_0_MASK			0x00FF							/* DCS_DAC_WR_VAL_0 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_0_SHIFT				 0							/* DCS_DAC_WR_VAL_0 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_0_WIDTH				 8							/* DCS_DAC_WR_VAL_0 - [7:0] */

/*
 * R77 (0x4D) - DC Servo Readback 0
 */
#define WM8904_DCS_CAL_COMPLETE_MASK			0x0F00							/* DCS_CAL_COMPLETE - [11:8] */
#define WM8904_DCS_CAL_COMPLETE_SHIFT				 8							/* DCS_CAL_COMPLETE - [11:8] */
#define WM8904_DCS_CAL_COMPLETE_WIDTH				 4							/* DCS_CAL_COMPLETE - [11:8] */
#define WM8904_DCS_DAC_WR_COMPLETE_MASK			0x00F0							/* DCS_DAC_WR_COMPLETE - [7:4] */
#define WM8904_DCS_DAC_WR_COMPLETE_SHIFT			 4							/* DCS_DAC_WR_COMPLETE - [7:4] */
#define WM8904_DCS_DAC_WR_COMPLETE_WIDTH			 4							/* DCS_DAC_WR_COMPLETE - [7:4] */
#define WM8904_DCS_STARTUP_COMPLETE_MASK		0x000F							/* DCS_STARTUP_COMPLETE - [3:0] */
#define WM8904_DCS_STARTUP_COMPLETE_SHIFT			 0							/* DCS_STARTUP_COMPLETE - [3:0] */
#define WM8904_DCS_STARTUP_COMPLETE_WIDTH			 4							/* DCS_STARTUP_COMPLETE - [3:0] */

/*
 * R90 (0x5A) - Analogue HP 0
 */
#define WM8904_HPL_RMV_SHORT					0x0080							/* HPL_RMV_SHORT */
#define WM8904_HPL_RMV_SHORT_MASK				0x0080							/* HPL_RMV_SHORT */
#define WM8904_HPL_RMV_SHORT_SHIFT					 7							/* HPL_RMV_SHORT */
#define WM8904_HPL_RMV_SHORT_WIDTH					 1							/* HPL_RMV_SHORT */
#define WM8904_HPL_ENA_OUTP						0x0040							/* HPL_ENA_OUTP */
#define WM8904_HPL_ENA_OUTP_MASK				0x0040							/* HPL_ENA_OUTP */
#define WM8904_HPL_ENA_OUTP_SHIFT					 6							/* HPL_ENA_OUTP */
#define WM8904_HPL_ENA_OUTP_WIDTH					 1							/* HPL_ENA_OUTP */
#define WM8904_HPL_ENA_DLY						0x0020							/* HPL_ENA_DLY */
#define WM8904_HPL_ENA_DLY_MASK					0x0020							/* HPL_ENA_DLY */
#define WM8904_HPL_ENA_DLY_SHIFT					 5							/* HPL_ENA_DLY */
#define WM8904_HPL_ENA_DLY_WIDTH					 1							/* HPL_ENA_DLY */
#define WM8904_HPL_ENA							0x0010							/* HPL_ENA */
#define WM8904_HPL_ENA_MASK						0x0010							/* HPL_ENA */
#define WM8904_HPL_ENA_SHIFT						 4							/* HPL_ENA */
#define WM8904_HPL_ENA_WIDTH						 1							/* HPL_ENA */
#define WM8904_HPR_RMV_SHORT					0x0008							/* HPR_RMV_SHORT */
#define WM8904_HPR_RMV_SHORT_MASK				0x0008							/* HPR_RMV_SHORT */
#define WM8904_HPR_RMV_SHORT_SHIFT					 3							/* HPR_RMV_SHORT */
#define WM8904_HPR_RMV_SHORT_WIDTH					 1							/* HPR_RMV_SHORT */
#define WM8904_HPR_ENA_OUTP						0x0004							/* HPR_ENA_OUTP */
#define WM8904_HPR_ENA_OUTP_MASK				0x0004							/* HPR_ENA_OUTP */
#define WM8904_HPR_ENA_OUTP_SHIFT					 2							/* HPR_ENA_OUTP */
#define WM8904_HPR_ENA_OUTP_WIDTH					 1							/* HPR_ENA_OUTP */
#define WM8904_HPR_ENA_DLY						0x0002							/* HPR_ENA_DLY */
#define WM8904_HPR_ENA_DLY_MASK					0x0002							/* HPR_ENA_DLY */
#define WM8904_HPR_ENA_DLY_SHIFT					 1							/* HPR_ENA_DLY */
#define WM8904_HPR_ENA_DLY_WIDTH					 1							/* HPR_ENA_DLY */
#define WM8904_HPR_ENA							0x0001							/* HPR_ENA */
#define WM8904_HPR_ENA_MASK						0x0001							/* HPR_ENA */
#define WM8904_HPR_ENA_SHIFT						 0							/* HPR_ENA */
#define WM8904_HPR_ENA_WIDTH						 1							/* HPR_ENA */

/*
 * R94 (0x5E) - Analogue Lineout 0
 */
#define WM8904_LINEOUTL_RMV_SHORT				0x0080							/* LINEOUTL_RMV_SHORT */
#define WM8904_LINEOUTL_RMV_SHORT_MASK			0x0080							/* LINEOUTL_RMV_SHORT */
#define WM8904_LINEOUTL_RMV_SHORT_SHIFT				 7							/* LINEOUTL_RMV_SHORT */
#define WM8904_LINEOUTL_RMV_SHORT_WIDTH				 1							/* LINEOUTL_RMV_SHORT */
#define WM8904_LINEOUTL_ENA_OUTP				0x0040							/* LINEOUTL_ENA_OUTP */
#define WM8904_LINEOUTL_ENA_OUTP_MASK			0x0040							/* LINEOUTL_ENA_OUTP */
#define WM8904_LINEOUTL_ENA_OUTP_SHIFT				 6							/* LINEOUTL_ENA_OUTP */
#define WM8904_LINEOUTL_ENA_OUTP_WIDTH				 1							/* LINEOUTL_ENA_OUTP */
#define WM8904_LINEOUTL_ENA_DLY					0x0020							/* LINEOUTL_ENA_DLY */
#define WM8904_LINEOUTL_ENA_DLY_MASK			0x0020							/* LINEOUTL_ENA_DLY */
#define WM8904_LINEOUTL_ENA_DLY_SHIFT				 5							/* LINEOUTL_ENA_DLY */
#define WM8904_LINEOUTL_ENA_DLY_WIDTH				 1							/* LINEOUTL_ENA_DLY */
#define WM8904_LINEOUTL_ENA						0x0010							/* LINEOUTL_ENA */
#define WM8904_LINEOUTL_ENA_MASK				0x0010							/* LINEOUTL_ENA */
#define WM8904_LINEOUTL_ENA_SHIFT					 4							/* LINEOUTL_ENA */
#define WM8904_LINEOUTL_ENA_WIDTH					 1							/* LINEOUTL_ENA */
#define WM8904_LINEOUTR_RMV_SHORT				0x0008							/* LINEOUTR_RMV_SHORT */
#define WM8904_LINEOUTR_RMV_SHORT_MASK			0x0008							/* LINEOUTR_RMV_SHORT */
#define WM8904_LINEOUTR_RMV_SHORT_SHIFT				 3							/* LINEOUTR_RMV_SHORT */
#define WM8904_LINEOUTR_RMV_SHORT_WIDTH				 1							/* LINEOUTR_RMV_SHORT */
#define WM8904_LINEOUTR_ENA_OUTP				0x0004							/* LINEOUTR_ENA_OUTP */
#define WM8904_LINEOUTR_ENA_OUTP_MASK			0x0004							/* LINEOUTR_ENA_OUTP */
#define WM8904_LINEOUTR_ENA_OUTP_SHIFT				 2							/* LINEOUTR_ENA_OUTP */
#define WM8904_LINEOUTR_ENA_OUTP_WIDTH				 1							/* LINEOUTR_ENA_OUTP */
#define WM8904_LINEOUTR_ENA_DLY					0x0002							/* LINEOUTR_ENA_DLY */
#define WM8904_LINEOUTR_ENA_DLY_MASK			0x0002							/* LINEOUTR_ENA_DLY */
#define WM8904_LINEOUTR_ENA_DLY_SHIFT				 1							/* LINEOUTR_ENA_DLY */
#define WM8904_LINEOUTR_ENA_DLY_WIDTH				 1							/* LINEOUTR_ENA_DLY */
#define WM8904_LINEOUTR_ENA						0x0001							/* LINEOUTR_ENA */
#define WM8904_LINEOUTR_ENA_MASK				0x0001							/* LINEOUTR_ENA */
#define WM8904_LINEOUTR_ENA_SHIFT					 0							/* LINEOUTR_ENA */
#define WM8904_LINEOUTR_ENA_WIDTH					 1							/* LINEOUTR_ENA */

/*
 * R98 (0x62) - Charge Pump 0
 */
#define WM8904_CP_ENA							0x0001							/* CP_ENA */
#define WM8904_CP_ENA_MASK						0x0001							/* CP_ENA */
#define WM8904_CP_ENA_SHIFT							 0							/* CP_ENA */
#define WM8904_CP_ENA_WIDTH							 1							/* CP_ENA */

/*
 * R104 (0x68) - Class W 0
 */
#define WM8904_CP_DYN_PWR						0x0001							/* CP_DYN_PWR */
#define WM8904_CP_DYN_PWR_MASK					0x0001							/* CP_DYN_PWR */
#define WM8904_CP_DYN_PWR_SHIFT						 0							/* CP_DYN_PWR */
#define WM8904_CP_DYN_PWR_WIDTH						 1							/* CP_DYN_PWR */

/*
 * R108 (0x6C) - Write Sequencer 0
 */
#define WM8904_WSEQ_ENA							0x0100							/* WSEQ_ENA */
#define WM8904_WSEQ_ENA_MASK					0x0100							/* WSEQ_ENA */
#define WM8904_WSEQ_ENA_SHIFT						 8							/* WSEQ_ENA */
#define WM8904_WSEQ_ENA_WIDTH						 1							/* WSEQ_ENA */
#define WM8904_WSEQ_WRITE_INDEX_MASK			0x001F							/* WSEQ_WRITE_INDEX - [4:0] */
#define WM8904_WSEQ_WRITE_INDEX_SHIFT				 0							/* WSEQ_WRITE_INDEX - [4:0] */
#define WM8904_WSEQ_WRITE_INDEX_WIDTH				 5							/* WSEQ_WRITE_INDEX - [4:0] */

/*
 * R109 (0x6D) - Write Sequencer 1
 */
#define WM8904_WSEQ_DATA_WIDTH_MASK				0x7000							/* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_WIDTH_SHIFT				12							/* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_WIDTH_WIDTH				 3							/* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_START_MASK				0x0F00							/* WSEQ_DATA_START - [11:8] */
#define WM8904_WSEQ_DATA_START_SHIFT				 8							/* WSEQ_DATA_START - [11:8] */
#define WM8904_WSEQ_DATA_START_WIDTH				 4							/* WSEQ_DATA_START - [11:8] */
#define WM8904_WSEQ_ADDR_MASK					0x00FF							/* WSEQ_ADDR - [7:0] */
#define WM8904_WSEQ_ADDR_SHIFT						 0							/* WSEQ_ADDR - [7:0] */
#define WM8904_WSEQ_ADDR_WIDTH						 8							/* WSEQ_ADDR - [7:0] */

/*
 * R110 (0x6E) - Write Sequencer 2
 */
#define WM8904_WSEQ_EOS							0x4000							/* WSEQ_EOS */
#define WM8904_WSEQ_EOS_MASK					0x4000							/* WSEQ_EOS */
#define WM8904_WSEQ_EOS_SHIFT						14							/* WSEQ_EOS */
#define WM8904_WSEQ_EOS_WIDTH						 1							/* WSEQ_EOS */
#define WM8904_WSEQ_DELAY_MASK					0x0F00							/* WSEQ_DELAY - [11:8] */
#define WM8904_WSEQ_DELAY_SHIFT						 8							/* WSEQ_DELAY - [11:8] */
#define WM8904_WSEQ_DELAY_WIDTH						 4							/* WSEQ_DELAY - [11:8] */
#define WM8904_WSEQ_DATA_MASK					0x00FF							/* WSEQ_DATA - [7:0] */
#define WM8904_WSEQ_DATA_SHIFT						 0							/* WSEQ_DATA - [7:0] */
#define WM8904_WSEQ_DATA_WIDTH						 8							/* WSEQ_DATA - [7:0] */

/*
 * R111 (0x6F) - Write Sequencer 3
 */
#define WM8904_WSEQ_ABORT						0x0200							/* WSEQ_ABORT */
#define WM8904_WSEQ_ABORT_MASK					0x0200							/* WSEQ_ABORT */
#define WM8904_WSEQ_ABORT_SHIFT						 9							/* WSEQ_ABORT */
#define WM8904_WSEQ_ABORT_WIDTH						 1							/* WSEQ_ABORT */
#define WM8904_WSEQ_START						0x0100							/* WSEQ_START */
#define WM8904_WSEQ_START_MASK					0x0100							/* WSEQ_START */
#define WM8904_WSEQ_START_SHIFT						 8							/* WSEQ_START */
#define WM8904_WSEQ_START_WIDTH						 1							/* WSEQ_START */
#define WM8904_WSEQ_START_INDEX_MASK			0x003F							/* WSEQ_START_INDEX - [5:0] */
#define WM8904_WSEQ_START_INDEX_SHIFT				 0							/* WSEQ_START_INDEX - [5:0] */
#define WM8904_WSEQ_START_INDEX_WIDTH				 6							/* WSEQ_START_INDEX - [5:0] */

/*
 * R112 (0x70) - Write Sequencer 4
 */
#define WM8904_WSEQ_CURRENT_INDEX_MASK			0x03F0							/* WSEQ_CURRENT_INDEX - [9:4] */
#define WM8904_WSEQ_CURRENT_INDEX_SHIFT				 4							/* WSEQ_CURRENT_INDEX - [9:4] */
#define WM8904_WSEQ_CURRENT_INDEX_WIDTH				 6							/* WSEQ_CURRENT_INDEX - [9:4] */
#define WM8904_WSEQ_BUSY						0x0001							/* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_MASK					0x0001							/* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_SHIFT						 0							/* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY_WIDTH						 1							/* WSEQ_BUSY */

/*
 * R116 (0x74) - FLL Control 1
 */
#define WM8904_FLL_FRACN_ENA					0x0004							/* FLL_FRACN_ENA */
#define WM8904_FLL_FRACN_ENA_MASK				0x0004							/* FLL_FRACN_ENA */
#define WM8904_FLL_FRACN_ENA_SHIFT					 2							/* FLL_FRACN_ENA */
#define WM8904_FLL_FRACN_ENA_WIDTH					 1							/* FLL_FRACN_ENA */
#define WM8904_FLL_OSC_ENA						0x0002							/* FLL_OSC_ENA */
#define WM8904_FLL_OSC_ENA_MASK					0x0002							/* FLL_OSC_ENA */
#define WM8904_FLL_OSC_ENA_SHIFT					 1							/* FLL_OSC_ENA */
#define WM8904_FLL_OSC_ENA_WIDTH					 1							/* FLL_OSC_ENA */
#define WM8904_FLL_ENA							0x0001							/* FLL_ENA */
#define WM8904_FLL_ENA_MASK						0x0001							/* FLL_ENA */
#define WM8904_FLL_ENA_SHIFT						 0							/* FLL_ENA */
#define WM8904_FLL_ENA_WIDTH						 1							/* FLL_ENA */

/*
 * R117 (0x75) - FLL Control 2
 */
#define WM8904_FLL_OUTDIV_MASK					0x3F00							/* FLL_OUTDIV - [13:8] */
#define WM8904_FLL_OUTDIV_SHIFT						 8							/* FLL_OUTDIV - [13:8] */
#define WM8904_FLL_OUTDIV_WIDTH						 6							/* FLL_OUTDIV - [13:8] */
#define WM8904_FLL_CTRL_RATE_MASK				0x0070							/* FLL_CTRL_RATE - [6:4] */
#define WM8904_FLL_CTRL_RATE_SHIFT					 4							/* FLL_CTRL_RATE - [6:4] */
#define WM8904_FLL_CTRL_RATE_WIDTH					 3							/* FLL_CTRL_RATE - [6:4] */
#define WM8904_FLL_FRATIO_MASK					0x0007							/* FLL_FRATIO - [2:0] */
#define WM8904_FLL_FRATIO_SHIFT						 0							/* FLL_FRATIO - [2:0] */
#define WM8904_FLL_FRATIO_WIDTH						 3							/* FLL_FRATIO - [2:0] */

/*
 * R118 (0x76) - FLL Control 3
 */
#define WM8904_FLL_K_MASK						0xFFFF							/* FLL_K - [15:0] */
#define WM8904_FLL_K_SHIFT							 0							/* FLL_K - [15:0] */
#define WM8904_FLL_K_WIDTH							16							/* FLL_K - [15:0] */

/*
 * R119 (0x77) - FLL Control 4
 */
#define WM8904_FLL_N_MASK						0x7FE0							/* FLL_N - [14:5] */
#define WM8904_FLL_N_SHIFT							 5							/* FLL_N - [14:5] */
#define WM8904_FLL_N_WIDTH							10							/* FLL_N - [14:5] */
#define WM8904_FLL_GAIN_MASK					0x000F							/* FLL_GAIN - [3:0] */
#define WM8904_FLL_GAIN_SHIFT						 0							/* FLL_GAIN - [3:0] */
#define WM8904_FLL_GAIN_WIDTH						 4							/* FLL_GAIN - [3:0] */

/*
 * R120 (0x78) - FLL Control 5
 */
#define WM8904_FLL_CLK_REF_DIV_MASK				0x0018							/* FLL_CLK_REF_DIV - [4:3] */
#define WM8904_FLL_CLK_REF_DIV_SHIFT				 3							/* FLL_CLK_REF_DIV - [4:3] */
#define WM8904_FLL_CLK_REF_DIV_WIDTH				 2							/* FLL_CLK_REF_DIV - [4:3] */
#define WM8904_FLL_CLK_REF_SRC_MASK				0x0003							/* FLL_CLK_REF_SRC - [1:0] */
#define WM8904_FLL_CLK_REF_SRC_SHIFT				 0							/* FLL_CLK_REF_SRC - [1:0] */
#define WM8904_FLL_CLK_REF_SRC_WIDTH				 2							/* FLL_CLK_REF_SRC - [1:0] */

/*
 * R126 (0x7E) - Digital Pulls
 */
#define WM8904_MCLK_PU							0x0080							/* MCLK_PU */
#define WM8904_MCLK_PU_MASK						0x0080							/* MCLK_PU */
#define WM8904_MCLK_PU_SHIFT						 7							/* MCLK_PU */
#define WM8904_MCLK_PU_WIDTH						 1							/* MCLK_PU */
#define WM8904_MCLK_PD							0x0040							/* MCLK_PD */
#define WM8904_MCLK_PD_MASK						0x0040							/* MCLK_PD */
#define WM8904_MCLK_PD_SHIFT						 6							/* MCLK_PD */
#define WM8904_MCLK_PD_WIDTH						 1							/* MCLK_PD */
#define WM8904_DACDAT_PU						0x0020							/* DACDAT_PU */
#define WM8904_DACDAT_PU_MASK					0x0020							/* DACDAT_PU */
#define WM8904_DACDAT_PU_SHIFT						 5							/* DACDAT_PU */
#define WM8904_DACDAT_PU_WIDTH						 1							/* DACDAT_PU */
#define WM8904_DACDAT_PD						0x0010							/* DACDAT_PD */
#define WM8904_DACDAT_PD_MASK					0x0010							/* DACDAT_PD */
#define WM8904_DACDAT_PD_SHIFT						 4							/* DACDAT_PD */
#define WM8904_DACDAT_PD_WIDTH						 1							/* DACDAT_PD */
#define WM8904_LRCLK_PU							0x0008							/* LRCLK_PU */
#define WM8904_LRCLK_PU_MASK					0x0008							/* LRCLK_PU */
#define WM8904_LRCLK_PU_SHIFT						 3							/* LRCLK_PU */
#define WM8904_LRCLK_PU_WIDTH						 1							/* LRCLK_PU */
#define WM8904_LRCLK_PD							0x0004							/* LRCLK_PD */
#define WM8904_LRCLK_PD_MASK					0x0004							/* LRCLK_PD */
#define WM8904_LRCLK_PD_SHIFT						 2							/* LRCLK_PD */
#define WM8904_LRCLK_PD_WIDTH						 1							/* LRCLK_PD */
#define WM8904_BCLK_PU							0x0002							/* BCLK_PU */
#define WM8904_BCLK_PU_MASK						0x0002							/* BCLK_PU */
#define WM8904_BCLK_PU_SHIFT						 1							/* BCLK_PU */
#define WM8904_BCLK_PU_WIDTH						 1							/* BCLK_PU */
#define WM8904_BCLK_PD							0x0001							/* BCLK_PD */
#define WM8904_BCLK_PD_MASK						0x0001							/* BCLK_PD */
#define WM8904_BCLK_PD_SHIFT						 0							/* BCLK_PD */
#define WM8904_BCLK_PD_WIDTH						 1							/* BCLK_PD */

/*
 * R127 (0x7F) - Interrupt Status
 */
#define WM8904_IRQ								0x0400							/* IRQ */
#define WM8904_IRQ_MASK							0x0400							/* IRQ */
#define WM8904_IRQ_SHIFT							10							/* IRQ */
#define WM8904_IRQ_WIDTH							 1							/* IRQ */
#define WM8904_GPIO_BCLK_EINT					0x0200							/* GPIO_BCLK_EINT */
#define WM8904_GPIO_BCLK_EINT_MASK				0x0200							/* GPIO_BCLK_EINT */
#define WM8904_GPIO_BCLK_EINT_SHIFT					 9							/* GPIO_BCLK_EINT */
#define WM8904_GPIO_BCLK_EINT_WIDTH					 1							/* GPIO_BCLK_EINT */
#define WM8904_WSEQ_EINT						0x0100							/* WSEQ_EINT */
#define WM8904_WSEQ_EINT_MASK					0x0100							/* WSEQ_EINT */
#define WM8904_WSEQ_EINT_SHIFT						 8							/* WSEQ_EINT */
#define WM8904_WSEQ_EINT_WIDTH						 1							/* WSEQ_EINT */
#define WM8904_GPIO3_EINT						0x0080							/* GPIO3_EINT */
#define WM8904_GPIO3_EINT_MASK					0x0080							/* GPIO3_EINT */
#define WM8904_GPIO3_EINT_SHIFT						 7							/* GPIO3_EINT */
#define WM8904_GPIO3_EINT_WIDTH						 1							/* GPIO3_EINT */
#define WM8904_GPIO2_EINT						0x0040							/* GPIO2_EINT */
#define WM8904_GPIO2_EINT_MASK					0x0040							/* GPIO2_EINT */
#define WM8904_GPIO2_EINT_SHIFT						 6							/* GPIO2_EINT */
#define WM8904_GPIO2_EINT_WIDTH						 1							/* GPIO2_EINT */
#define WM8904_GPIO1_EINT						0x0020							/* GPIO1_EINT */
#define WM8904_GPIO1_EINT_MASK					0x0020							/* GPIO1_EINT */
#define WM8904_GPIO1_EINT_SHIFT						 5							/* GPIO1_EINT */
#define WM8904_GPIO1_EINT_WIDTH						 1							/* GPIO1_EINT */
#define WM8904_GPI8_EINT						0x0010							/* GPI8_EINT */
#define WM8904_GPI8_EINT_MASK					0x0010							/* GPI8_EINT */
#define WM8904_GPI8_EINT_SHIFT						 4							/* GPI8_EINT */
#define WM8904_GPI8_EINT_WIDTH						 1							/* GPI8_EINT */
#define WM8904_GPI7_EINT						0x0008							/* GPI7_EINT */
#define WM8904_GPI7_EINT_MASK					0x0008							/* GPI7_EINT */
#define WM8904_GPI7_EINT_SHIFT						 3							/* GPI7_EINT */
#define WM8904_GPI7_EINT_WIDTH						 1							/* GPI7_EINT */
#define WM8904_FLL_LOCK_EINT					0x0004							/* FLL_LOCK_EINT */
#define WM8904_FLL_LOCK_EINT_MASK				0x0004							/* FLL_LOCK_EINT */
#define WM8904_FLL_LOCK_EINT_SHIFT					 2							/* FLL_LOCK_EINT */
#define WM8904_FLL_LOCK_EINT_WIDTH					 1							/* FLL_LOCK_EINT */
#define WM8904_MIC_SHRT_EINT					0x0002							/* MIC_SHRT_EINT */
#define WM8904_MIC_SHRT_EINT_MASK				0x0002							/* MIC_SHRT_EINT */
#define WM8904_MIC_SHRT_EINT_SHIFT					 1							/* MIC_SHRT_EINT */
#define WM8904_MIC_SHRT_EINT_WIDTH					 1							/* MIC_SHRT_EINT */
#define WM8904_MIC_DET_EINT						0x0001							/* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_MASK				0x0001							/* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_SHIFT					 0							/* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT_WIDTH					 1							/* MIC_DET_EINT */

/*
 * R128 (0x80) - Interrupt Status Mask
 */
#define WM8904_IM_GPIO_BCLK_EINT				0x0200							/* IM_GPIO_BCLK_EINT */
#define WM8904_IM_GPIO_BCLK_EINT_MASK			0x0200							/* IM_GPIO_BCLK_EINT */
#define WM8904_IM_GPIO_BCLK_EINT_SHIFT				 9							/* IM_GPIO_BCLK_EINT */
#define WM8904_IM_GPIO_BCLK_EINT_WIDTH				 1							/* IM_GPIO_BCLK_EINT */
#define WM8904_IM_WSEQ_EINT						0x0100							/* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_MASK				0x0100							/* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_SHIFT					 8							/* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT_WIDTH					 1							/* IM_WSEQ_EINT */
#define WM8904_IM_GPIO3_EINT					0x0080							/* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_MASK				0x0080							/* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_SHIFT					 7							/* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT_WIDTH					 1							/* IM_GPIO3_EINT */
#define WM8904_IM_GPIO2_EINT					0x0040							/* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_MASK				0x0040							/* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_SHIFT					 6							/* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT_WIDTH					 1							/* IM_GPIO2_EINT */
#define WM8904_IM_GPIO1_EINT					0x0020							/* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_MASK				0x0020							/* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_SHIFT					 5							/* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT_WIDTH					 1							/* IM_GPIO1_EINT */
#define WM8904_IM_GPI8_EINT						0x0010							/* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_MASK				0x0010							/* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_SHIFT					 4							/* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT_WIDTH					 1							/* IM_GPI8_EINT */
#define WM8904_IM_GPI7_EINT						0x0008							/* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_MASK				0x0008							/* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_SHIFT					 3							/* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT_WIDTH					 1							/* IM_GPI7_EINT */
#define WM8904_IM_FLL_LOCK_EINT					0x0004							/* IM_FLL_LOCK_EINT */
#define WM8904_IM_FLL_LOCK_EINT_MASK			0x0004							/* IM_FLL_LOCK_EINT */
#define WM8904_IM_FLL_LOCK_EINT_SHIFT				 2							/* IM_FLL_LOCK_EINT */
#define WM8904_IM_FLL_LOCK_EINT_WIDTH				 1							/* IM_FLL_LOCK_EINT */
#define WM8904_IM_MIC_SHRT_EINT					0x0002							/* IM_MIC_SHRT_EINT */
#define WM8904_IM_MIC_SHRT_EINT_MASK			0x0002							/* IM_MIC_SHRT_EINT */
#define WM8904_IM_MIC_SHRT_EINT_SHIFT				 1							/* IM_MIC_SHRT_EINT */
#define WM8904_IM_MIC_SHRT_EINT_WIDTH				 1							/* IM_MIC_SHRT_EINT */
#define WM8904_IM_MIC_DET_EINT					0x0001							/* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_MASK				0x0001							/* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_SHIFT				 0							/* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT_WIDTH				 1							/* IM_MIC_DET_EINT */

/*
 * R129 (0x81) - Interrupt Polarity
 */
#define WM8904_GPIO_BCLK_EINT_POL				0x0200							/* GPIO_BCLK_EINT_POL */
#define WM8904_GPIO_BCLK_EINT_POL_MASK			0x0200							/* GPIO_BCLK_EINT_POL */
#define WM8904_GPIO_BCLK_EINT_POL_SHIFT				 9							/* GPIO_BCLK_EINT_POL */
#define WM8904_GPIO_BCLK_EINT_POL_WIDTH				 1							/* GPIO_BCLK_EINT_POL */
#define WM8904_WSEQ_EINT_POL					0x0100							/* WSEQ_EINT_POL */
#define WM8904_WSEQ_EINT_POL_MASK				0x0100							/* WSEQ_EINT_POL */
#define WM8904_WSEQ_EINT_POL_SHIFT					 8							/* WSEQ_EINT_POL */
#define WM8904_WSEQ_EINT_POL_WIDTH					 1							/* WSEQ_EINT_POL */
#define WM8904_GPIO3_EINT_POL					0x0080							/* GPIO3_EINT_POL */
#define WM8904_GPIO3_EINT_POL_MASK				0x0080							/* GPIO3_EINT_POL */
#define WM8904_GPIO3_EINT_POL_SHIFT					 7							/* GPIO3_EINT_POL */
#define WM8904_GPIO3_EINT_POL_WIDTH					 1							/* GPIO3_EINT_POL */
#define WM8904_GPIO2_EINT_POL					0x0040							/* GPIO2_EINT_POL */
#define WM8904_GPIO2_EINT_POL_MASK				0x0040							/* GPIO2_EINT_POL */
#define WM8904_GPIO2_EINT_POL_SHIFT					 6							/* GPIO2_EINT_POL */
#define WM8904_GPIO2_EINT_POL_WIDTH					 1							/* GPIO2_EINT_POL */
#define WM8904_GPIO1_EINT_POL					0x0020							/* GPIO1_EINT_POL */
#define WM8904_GPIO1_EINT_POL_MASK				0x0020							/* GPIO1_EINT_POL */
#define WM8904_GPIO1_EINT_POL_SHIFT					 5							/* GPIO1_EINT_POL */
#define WM8904_GPIO1_EINT_POL_WIDTH					 1							/* GPIO1_EINT_POL */
#define WM8904_GPI8_EINT_POL					0x0010							/* GPI8_EINT_POL */
#define WM8904_GPI8_EINT_POL_MASK				0x0010							/* GPI8_EINT_POL */
#define WM8904_GPI8_EINT_POL_SHIFT					 4							/* GPI8_EINT_POL */
#define WM8904_GPI8_EINT_POL_WIDTH					 1							/* GPI8_EINT_POL */
#define WM8904_GPI7_EINT_POL					0x0008							/* GPI7_EINT_POL */
#define WM8904_GPI7_EINT_POL_MASK				0x0008							/* GPI7_EINT_POL */
#define WM8904_GPI7_EINT_POL_SHIFT					 3							/* GPI7_EINT_POL */
#define WM8904_GPI7_EINT_POL_WIDTH					 1							/* GPI7_EINT_POL */
#define WM8904_FLL_LOCK_EINT_POL				0x0004							/* FLL_LOCK_EINT_POL */
#define WM8904_FLL_LOCK_EINT_POL_MASK			0x0004							/* FLL_LOCK_EINT_POL */
#define WM8904_FLL_LOCK_EINT_POL_SHIFT				 2							/* FLL_LOCK_EINT_POL */
#define WM8904_FLL_LOCK_EINT_POL_WIDTH				 1							/* FLL_LOCK_EINT_POL */
#define WM8904_MIC_SHRT_EINT_POL				0x0002							/* MIC_SHRT_EINT_POL */
#define WM8904_MIC_SHRT_EINT_POL_MASK			0x0002							/* MIC_SHRT_EINT_POL */
#define WM8904_MIC_SHRT_EINT_POL_SHIFT				 1							/* MIC_SHRT_EINT_POL */
#define WM8904_MIC_SHRT_EINT_POL_WIDTH				 1							/* MIC_SHRT_EINT_POL */
#define WM8904_MIC_DET_EINT_POL					0x0001							/* MIC_DET_EINT_POL */
#define WM8904_MIC_DET_EINT_POL_MASK			0x0001							/* MIC_DET_EINT_POL */
#define WM8904_MIC_DET_EINT_POL_SHIFT				 0							/* MIC_DET_EINT_POL */
#define WM8904_MIC_DET_EINT_POL_WIDTH				 1							/* MIC_DET_EINT_POL */

/*
 * R130 (0x82) - Interrupt Debounce
 */
#define WM8904_GPIO_BCLK_EINT_DB				0x0200							/* GPIO_BCLK_EINT_DB */
#define WM8904_GPIO_BCLK_EINT_DB_MASK			0x0200							/* GPIO_BCLK_EINT_DB */
#define WM8904_GPIO_BCLK_EINT_DB_SHIFT				 9							/* GPIO_BCLK_EINT_DB */
#define WM8904_GPIO_BCLK_EINT_DB_WIDTH				 1							/* GPIO_BCLK_EINT_DB */
#define WM8904_WSEQ_EINT_DB						0x0100							/* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_MASK				0x0100							/* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_SHIFT					 8							/* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB_WIDTH					 1							/* WSEQ_EINT_DB */
#define WM8904_GPIO3_EINT_DB					0x0080							/* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_MASK				0x0080							/* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_SHIFT					 7							/* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB_WIDTH					 1							/* GPIO3_EINT_DB */
#define WM8904_GPIO2_EINT_DB					0x0040							/* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_MASK				0x0040							/* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_SHIFT					 6							/* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB_WIDTH					 1							/* GPIO2_EINT_DB */
#define WM8904_GPIO1_EINT_DB					0x0020							/* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_MASK				0x0020							/* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_SHIFT					 5							/* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB_WIDTH					 1							/* GPIO1_EINT_DB */
#define WM8904_GPI8_EINT_DB						0x0010							/* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_MASK				0x0010							/* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_SHIFT					 4							/* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB_WIDTH					 1							/* GPI8_EINT_DB */
#define WM8904_GPI7_EINT_DB						0x0008							/* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_MASK				0x0008							/* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_SHIFT					 3							/* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB_WIDTH					 1							/* GPI7_EINT_DB */
#define WM8904_FLL_LOCK_EINT_DB					0x0004							/* FLL_LOCK_EINT_DB */
#define WM8904_FLL_LOCK_EINT_DB_MASK			0x0004							/* FLL_LOCK_EINT_DB */
#define WM8904_FLL_LOCK_EINT_DB_SHIFT				 2							/* FLL_LOCK_EINT_DB */
#define WM8904_FLL_LOCK_EINT_DB_WIDTH				 1							/* FLL_LOCK_EINT_DB */
#define WM8904_MIC_SHRT_EINT_DB					0x0002							/* MIC_SHRT_EINT_DB */
#define WM8904_MIC_SHRT_EINT_DB_MASK			0x0002							/* MIC_SHRT_EINT_DB */
#define WM8904_MIC_SHRT_EINT_DB_SHIFT				 1							/* MIC_SHRT_EINT_DB */
#define WM8904_MIC_SHRT_EINT_DB_WIDTH				 1							/* MIC_SHRT_EINT_DB */
#define WM8904_MIC_DET_EINT_DB					0x0001							/* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_MASK				0x0001							/* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_SHIFT				 0							/* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB_WIDTH				 1							/* MIC_DET_EINT_DB */

/*
 * R134 (0x86) - EQ1
 */
#define WM8904_EQ_ENA							0x0001							/* EQ_ENA */
#define WM8904_EQ_ENA_MASK						0x0001							/* EQ_ENA */
#define WM8904_EQ_ENA_SHIFT							 0							/* EQ_ENA */
#define WM8904_EQ_ENA_WIDTH							 1							/* EQ_ENA */

/*
 * R135 (0x87) - EQ2
 */
#define WM8904_EQ_B1_GAIN_MASK					0x001F							/* EQ_B1_GAIN - [4:0] */
#define WM8904_EQ_B1_GAIN_SHIFT						 0							/* EQ_B1_GAIN - [4:0] */
#define WM8904_EQ_B1_GAIN_WIDTH						 5							/* EQ_B1_GAIN - [4:0] */

/*
 * R136 (0x88) - EQ3
 */
#define WM8904_EQ_B2_GAIN_MASK					0x001F							/* EQ_B2_GAIN - [4:0] */
#define WM8904_EQ_B2_GAIN_SHIFT						 0							/* EQ_B2_GAIN - [4:0] */
#define WM8904_EQ_B2_GAIN_WIDTH						 5							/* EQ_B2_GAIN - [4:0] */

/*
 * R137 (0x89) - EQ4
 */
#define WM8904_EQ_B3_GAIN_MASK					0x001F							/* EQ_B3_GAIN - [4:0] */
#define WM8904_EQ_B3_GAIN_SHIFT						 0							/* EQ_B3_GAIN - [4:0] */
#define WM8904_EQ_B3_GAIN_WIDTH						 5							/* EQ_B3_GAIN - [4:0] */

/*
 * R138 (0x8A) - EQ5
 */
#define WM8904_EQ_B4_GAIN_MASK					0x001F							/* EQ_B4_GAIN - [4:0] */
#define WM8904_EQ_B4_GAIN_SHIFT						 0							/* EQ_B4_GAIN - [4:0] */
#define WM8904_EQ_B4_GAIN_WIDTH						 5							/* EQ_B4_GAIN - [4:0] */

/*
 * R139 (0x8B) - EQ6
 */
#define WM8904_EQ_B5_GAIN_MASK					0x001F							/* EQ_B5_GAIN - [4:0] */
#define WM8904_EQ_B5_GAIN_SHIFT						 0							/* EQ_B5_GAIN - [4:0] */
#define WM8904_EQ_B5_GAIN_WIDTH						 5							/* EQ_B5_GAIN - [4:0] */

/*
 * R140 (0x8C) - EQ7
 */
#define WM8904_EQ_B1_A_MASK						0xFFFF							/* EQ_B1_A - [15:0] */
#define WM8904_EQ_B1_A_SHIFT						 0							/* EQ_B1_A - [15:0] */
#define WM8904_EQ_B1_A_WIDTH						16							/* EQ_B1_A - [15:0] */

/*
 * R141 (0x8D) - EQ8
 */
#define WM8904_EQ_B1_B_MASK						0xFFFF							/* EQ_B1_B - [15:0] */
#define WM8904_EQ_B1_B_SHIFT						 0							/* EQ_B1_B - [15:0] */
#define WM8904_EQ_B1_B_WIDTH						16							/* EQ_B1_B - [15:0] */

/*
 * R142 (0x8E) - EQ9
 */
#define WM8904_EQ_B1_PG_MASK					0xFFFF							/* EQ_B1_PG - [15:0] */
#define WM8904_EQ_B1_PG_SHIFT						 0							/* EQ_B1_PG - [15:0] */
#define WM8904_EQ_B1_PG_WIDTH						16							/* EQ_B1_PG - [15:0] */

/*
 * R143 (0x8F) - EQ10
 */
#define WM8904_EQ_B2_A_MASK						0xFFFF							/* EQ_B2_A - [15:0] */
#define WM8904_EQ_B2_A_SHIFT						 0							/* EQ_B2_A - [15:0] */
#define WM8904_EQ_B2_A_WIDTH						16							/* EQ_B2_A - [15:0] */

/*
 * R144 (0x90) - EQ11
 */
#define WM8904_EQ_B2_B_MASK						0xFFFF							/* EQ_B2_B - [15:0] */
#define WM8904_EQ_B2_B_SHIFT						 0							/* EQ_B2_B - [15:0] */
#define WM8904_EQ_B2_B_WIDTH						16							/* EQ_B2_B - [15:0] */

/*
 * R145 (0x91) - EQ12
 */
#define WM8904_EQ_B2_C_MASK						0xFFFF							/* EQ_B2_C - [15:0] */
#define WM8904_EQ_B2_C_SHIFT						 0							/* EQ_B2_C - [15:0] */
#define WM8904_EQ_B2_C_WIDTH						16							/* EQ_B2_C - [15:0] */

/*
 * R146 (0x92) - EQ13
 */
#define WM8904_EQ_B2_PG_MASK					0xFFFF							/* EQ_B2_PG - [15:0] */
#define WM8904_EQ_B2_PG_SHIFT						 0							/* EQ_B2_PG - [15:0] */
#define WM8904_EQ_B2_PG_WIDTH						16							/* EQ_B2_PG - [15:0] */

/*
 * R147 (0x93) - EQ14
 */
#define WM8904_EQ_B3_A_MASK						0xFFFF							/* EQ_B3_A - [15:0] */
#define WM8904_EQ_B3_A_SHIFT						 0							/* EQ_B3_A - [15:0] */
#define WM8904_EQ_B3_A_WIDTH						16							/* EQ_B3_A - [15:0] */

/*
 * R148 (0x94) - EQ15
 */
#define WM8904_EQ_B3_B_MASK						0xFFFF							/* EQ_B3_B - [15:0] */
#define WM8904_EQ_B3_B_SHIFT						 0							/* EQ_B3_B - [15:0] */
#define WM8904_EQ_B3_B_WIDTH						16							/* EQ_B3_B - [15:0] */

/*
 * R149 (0x95) - EQ16
 */
#define WM8904_EQ_B3_C_MASK						0xFFFF							/* EQ_B3_C - [15:0] */
#define WM8904_EQ_B3_C_SHIFT						 0							/* EQ_B3_C - [15:0] */
#define WM8904_EQ_B3_C_WIDTH						16							/* EQ_B3_C - [15:0] */

/*
 * R150 (0x96) - EQ17
 */
#define WM8904_EQ_B3_PG_MASK					0xFFFF							/* EQ_B3_PG - [15:0] */
#define WM8904_EQ_B3_PG_SHIFT						 0							/* EQ_B3_PG - [15:0] */
#define WM8904_EQ_B3_PG_WIDTH						16							/* EQ_B3_PG - [15:0] */

/*
 * R151 (0x97) - EQ18
 */
#define WM8904_EQ_B4_A_MASK						0xFFFF							/* EQ_B4_A - [15:0] */
#define WM8904_EQ_B4_A_SHIFT						 0							/* EQ_B4_A - [15:0] */
#define WM8904_EQ_B4_A_WIDTH						16							/* EQ_B4_A - [15:0] */

/*
 * R152 (0x98) - EQ19
 */
#define WM8904_EQ_B4_B_MASK						0xFFFF							/* EQ_B4_B - [15:0] */
#define WM8904_EQ_B4_B_SHIFT						 0							/* EQ_B4_B - [15:0] */
#define WM8904_EQ_B4_B_WIDTH						16							/* EQ_B4_B - [15:0] */

/*
 * R153 (0x99) - EQ20
 */
#define WM8904_EQ_B4_C_MASK						0xFFFF							/* EQ_B4_C - [15:0] */
#define WM8904_EQ_B4_C_SHIFT						 0							/* EQ_B4_C - [15:0] */
#define WM8904_EQ_B4_C_WIDTH						16							/* EQ_B4_C - [15:0] */

/*
 * R154 (0x9A) - EQ21
 */
#define WM8904_EQ_B4_PG_MASK					0xFFFF							/* EQ_B4_PG - [15:0] */
#define WM8904_EQ_B4_PG_SHIFT						 0							/* EQ_B4_PG - [15:0] */
#define WM8904_EQ_B4_PG_WIDTH						16							/* EQ_B4_PG - [15:0] */

/*
 * R155 (0x9B) - EQ22
 */
#define WM8904_EQ_B5_A_MASK						0xFFFF							/* EQ_B5_A - [15:0] */
#define WM8904_EQ_B5_A_SHIFT						 0							/* EQ_B5_A - [15:0] */
#define WM8904_EQ_B5_A_WIDTH						16							/* EQ_B5_A - [15:0] */

/*
 * R156 (0x9C) - EQ23
 */
#define WM8904_EQ_B5_B_MASK						0xFFFF							/* EQ_B5_B - [15:0] */
#define WM8904_EQ_B5_B_SHIFT						 0							/* EQ_B5_B - [15:0] */
#define WM8904_EQ_B5_B_WIDTH						16							/* EQ_B5_B - [15:0] */

/*
 * R157 (0x9D) - EQ24
 */
#define WM8904_EQ_B5_PG_MASK					0xFFFF							/* EQ_B5_PG - [15:0] */
#define WM8904_EQ_B5_PG_SHIFT						 0							/* EQ_B5_PG - [15:0] */
#define WM8904_EQ_B5_PG_WIDTH						16							/* EQ_B5_PG - [15:0] */

/*
 * R161 (0xA1) - Control Interface Test 1
 */
#define WM8904_USER_KEY							0x0002							/* USER_KEY */
#define WM8904_USER_KEY_MASK					0x0002							/* USER_KEY */
#define WM8904_USER_KEY_SHIFT						 1							/* USER_KEY */
#define WM8904_USER_KEY_WIDTH						 1							/* USER_KEY */

/*
 * R198 (0xC6) - ADC Test 0
 */
#define WM8904_ADC_128_OSR_TST_MODE				0x0004							/* ADC_128_OSR_TST_MODE */
#define WM8904_ADC_128_OSR_TST_MODE_SHIFT			 2							/* ADC_128_OSR_TST_MODE */
#define WM8904_ADC_128_OSR_TST_MODE_WIDTH			 1							/* ADC_128_OSR_TST_MODE */
#define WM8904_ADC_BIASX1P5						0x0001							/* ADC_BIASX1P5 */
#define WM8904_ADC_BIASX1P5_SHIFT					 0							/* ADC_BIASX1P5 */
#define WM8904_ADC_BIASX1P5_WIDTH					 1							/* ADC_BIASX1P5 */

/*
 * R204 (0xCC) - Analogue Output Bias 0
 */
#define WM8904_PGA_BIAS_MASK					0x0070							/* PGA_BIAS - [6:4] */
#define WM8904_PGA_BIAS_SHIFT						 4							/* PGA_BIAS - [6:4] */
#define WM8904_PGA_BIAS_WIDTH						 3							/* PGA_BIAS - [6:4] */

/*
 * R247 (0xF7) - FLL NCO Test 0
 */
#define WM8904_FLL_FRC_NCO						0x0001							/* FLL_FRC_NCO */
#define WM8904_FLL_FRC_NCO_MASK					0x0001							/* FLL_FRC_NCO */
#define WM8904_FLL_FRC_NCO_SHIFT					 0							/* FLL_FRC_NCO */
#define WM8904_FLL_FRC_NCO_WIDTH					 1							/* FLL_FRC_NCO */

/*
 * R248 (0xF8) - FLL NCO Test 1
 */
#define WM8904_FLL_FRC_NCO_VAL_MASK				0x003F							/* FLL_FRC_NCO_VAL - [5:0] */
#define WM8904_FLL_FRC_NCO_VAL_SHIFT				 0							/* FLL_FRC_NCO_VAL - [5:0] */
#define WM8904_FLL_FRC_NCO_VAL_WIDTH				 6							/* FLL_FRC_NCO_VAL - [5:0] */

/* register setting constants */
#define WM8904_FLL_1288MHZ_K                    (0x3127)
#define WM8904_FLL_1288MHZ_N                    (0x8 << 5)
#define WM8904_FLL_1128MHZ_K                    (0x86C2)
#define WM8904_FLL_1128MHZ_N                    (0x7 << 5)

#define WM8904_BDIV_256FS_2_64FS                (0x0004)
#define WM8904_BDIV_256FS_2_32FS                (0x0008)
#define WM8904_BDIV_384FS_2_64FS                (0x0007)
#define WM8904_BDIV_384FS_2_32FS                (0x000B)
#define WM8904_LRDIV_64FS                       (0x0840)
#define WM8904_LRDIV_32FS                       (0x0820)

#define WM8904_AIF123_256FS_2_32FS              { 0x4042, WM8904_BDIV_256FS_2_32FS, WM8904_LRDIV_32FS}
#define WM8904_AIF123_256FS_2_64FS              { 0x404A, WM8904_BDIV_256FS_2_64FS, WM8904_LRDIV_64FS}
#define WM8904_AIF123_384FS_2_32FS              { 0x4042, WM8904_BDIV_384FS_2_32FS, WM8904_LRDIV_32FS}
#define WM8904_AIF123_384FS_2_64FS              { 0x404A, WM8904_BDIV_384FS_2_64FS, WM8904_LRDIV_64FS}

#define WM8904_DAC_DIGITAL_1_VALUE              0x0240

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
//	typedef structures
//------------------------------------------------------------------------------
/*
 * Register configuration tuple
 */
typedef struct  {
	uint16_t	reg;
	uint16_t	val;
} REG_CONFIG_T;

/*
 * CODEC configuration tuple
 */
typedef struct {
    uint16_t fll_k;
    uint16_t fll_n;
} CODEC_CONFIG_T;

typedef enum {
	CONFIG_ANALOG_BYPASS,
	CONFIG_DIGITAL_LOOPBACK,
	CONFIG_DIGITAL_IO,
	CONFIG_DAC_OUT,
} WM8904_CONFIG_T;

typedef enum {
	SR_48KHZ,
	SR_441KHZ,
} WM8904_SR_T;

/**
 * @brief	Sample frequency to MCLK ratios
 */
typedef enum {
	MCLK_FS_64X,     /* MCLK is 64   times sample rate */
	MCLK_FS_128X,    /* MCLK is 128  times sample rate */
	MCLK_FS_192X,    /* MCLK is 192  times sample rate */
	MCLK_FS_256X,    /* MCLK is 256  times sample rate */
	MCLK_FS_384X,    /* MCLK is 384  times sample rate */
	MCLK_FS_512X,    /* MCLK is 512  times sample rate */
	MCLK_FS_768X,    /* MCLK is 768  times sample rate */
	MCLK_FS_1024X,   /* MCLK is 1024 times sample rate */
	MCLK_FS_1408X,   /* MCLK is 1408 times sample rate */
	MCLK_FS_1536X,   /* MCLK is 1536 times sample rate */
} WM8904_FS_RATIO_T;


/* Device Control Commands */
#define CODEC_CMD_RESET			0
#define CODEC_CMD_VOLUME		1
#define CODEC_CMD_SAMPLERATE	2
#define CODEC_CMD_EQ			3
#define CODEC_CMD_3D			4

#define CODEC_VOLUME_MAX		(63)

//------------------------------------------------------------------------------
//	wm8904 driver functions
//------------------------------------------------------------------------------
void wm8904_reset(void);
bool wm8904_fll_init(WM8904_SR_T rate);
void wm8904_config(WM8904_CONFIG_T cfg);

void wm8904_pga_gain(uint8_t gain);
void wm8904_pga_mute(bool mute);

void wm8904_hp_vol(uint8_t gain);
void wm8904_hp_mute(bool mute);

void wm8904_id_read(void);
void wm8904_reg_dump(void);
int WM8904_SetSampleRate(WM8904_FS_RATIO_T ratio, uint32_t sample_rate, uint8_t res_bits);


//------------------------------------------------------------------------------
//	title:	DAC to headphone playback
//	input:	DAC
//	output:	headphones[LR]
//	path:	DAC --> headphones
//------------------------------------------------------------------------------
//
const REG_CONFIG_T dac_hp_arr[] = {
	{ 0x6C, 0x0100 },		//	WSEQ_ENA=1, WSEQ_WRITE_INDEX=0_0000
	{ 0x6F, 0x0100 },		//	WSEQ_ABORT=0, WSEQ_START=1, WSEQ_START_INDEX=00_0000
	{ 0x14, 0x845E },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_X4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	{ 0x39, 0x0039 },		//	HPOUTL_MUTE=0, HPOUT_VU=1, HPOUTLZC=0, HPOUTL_VOL=11_1001
	{ 0x3A, 0x00B9 },		//	HPOUTR_MUTE=0, HPOUT_VU=1, HPOUTRZC=0, HPOUTR_VOL=11_1001
	{ 0x21, 0x0000 },		//	DAC_MONO=0, DAC_SB_FILT=0, DAC_MUTERATE=0, DAC_UNMUTE_RAMP=0, DAC_OSR128=0, DAC_MUTE=0,D?????=00
	{ 0x68, 0x0005 },		//	CP_DYN_PWR=1
};
const uint32_t dac_hp_ct = sizeof(dac_hp_arr)/sizeof(REG_CONFIG_T);

const REG_CONFIG_T i2_io_arr[] = {
	{ 0x06, 0x0001 },		// MICDET_THR=0.070mA, MICSHORT_THR=0.520mA, MICDET_ENA=0, MIC_BIAS_ENA=1
	{ 0x07, 0x0004 },		// MICBIAS_SEL=2.7V

	{ 0x04, 0x0019 },		//	POBCTRL=1, ISEL=10, STARTUP_BIAS_ENA=0, BIAS_ENA=1
	{ 0x05, 0x0043 },		//	VMID_BUF_ENA=1, VMID_RES=01, VMID_ENA=1
	{ 0x14, 0x845E }, // Magicoe 0x845F },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	//{ 0x14, 0x1 },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	{ 0x0C, 0x0003 },		//	INL_ENA=1, INR ENA=1
	{ 0x0E, 0x0003 },		//	HPL_PGA_ENA=1, HPR_PGA_ENA=1
	{ 0x0F, 0x0003 },		//	LINEOUTL_PGA_ENA=1, LINEOUTR_PGA_ENA=1
	{ 0x12, 0x000F },		//	DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1
	{ 0x18, 0x0050 },		//	DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=0, AIFADCL_SRC=0, AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0, DAC_COMP=0, DAC_COMPMODE=0
	{ 0x19, 0x0002 },		//	BCLK_DIR=0 (input), AIF_WL=00 (16-bits)
	{ 0x1a, 0x0008 },		//	OPCLK_DIV=0 (sysclk), BCLK_DIV=08 (sysclk/8)
	{ 0x1b, 0x0020 },		//	LRCLK_DIR=0 (input), LRCLK_RATE=0010_0000_0000 (BCLK / 32)
	{ 0x20, 0x0CC6 },		//	ADCL_DAC_SVOL=0dB, ADCR_DAC_SVOL=0dB, ADC_TO_DACL= 01 (left), ADC_TO_DACR= 10 (right)
	{ 0x21, 0x0000 },		//	DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0, DAC_OSR128=0, DAC_MUTE=0, DEEMPH=00
	{ 0x2E, 0x0010 },		//	INL_CM_ENA=0, L_IP_SEL_N=10, L_IP_SEL_P=01, L_MODE=00
	{ 0x2F, 0x0010 },		//	INR CM_ENA=0, R_IP_SEL_N=10, R_IP_SEL_P=01, R_MODE=00
	{ 0x2C, 0x0005 },		//	LINMUTE=0, LIN_VOL=0_0101
	{ 0x2D, 0x0005 },		//	RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1, LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1, LINEOUTR_ENA_OUTP=1,
	{ 0x3D, 0x0000 },		//	HPL_BYP_ENA=0, HPR_BYP_ENA=0, LINEOUTL_BYP ENA=0, LINEOUTR_BYP ENA=0

	{ 0x39, 0x0039 },		//	HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=11_1001
	{ 0x3A, 0x00B9 }, // Magicoe 0x0039 },		//	HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=11_1001

	{ 0x43, 0x000f },		//	Enable DC servos

	{ 0x5A, 0x00FF },		//	HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1, HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1
	{ 0x5E, 0x00FF },		//	LINEOUTR_ENA_DLY=1, LINEOUTR_ENA=1
	{ 0x68, 0x0005 },		//	CP_DYN_PWR=1
	{ 0x62, 0x0001 },		//	CP_ENA=1
	{ 0x79, 0x0001 },       //  CLK OUT in GPIO1
};
const uint32_t i2_io_ct = sizeof(i2_io_arr)/sizeof(REG_CONFIG_T);

const REG_CONFIG_T i2_abp_hp_arr[] = {
	{ 0x06, 0x0001 },		// MICDET_THR=0.070mA, MICSHORT_THR=0.520mA, MICDET_ENA=0, MIC_BIAS_ENA=1
	{ 0x07, 0x0004 },		// MICBIAS_SEL=2.7V

	{ 0x04, 0x0009 },		//	POBCTRL=0, ISEL=10, STARTUP_BIAS_ENA=0, BIAS_ENA=1
	{ 0x05, 0x0043 },		//	VMID_BUF_ENA=1, VMID_RES=01, VMID_ENA=1
	{ 0x14, 0x845E },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	{ 0x0C, 0x0003 },		//	INL_ENA=1, INR_ENA=1
	{ 0x0E, 0x0003 },		//	HPL_PGA_ENA=1, HPR_PGA_ENA=1
	{ 0x0F, 0x0003 },		//	LINEOUTL_PGA_ENA=1, LINEOUTR_PGA_ENA=1
	{ 0x2E, 0x0014 },		//	INL_CM_ENA=0, L_IP_SEL_N=01, L_IP_SEL_P=01, L_MODE=00
	{ 0x2F, 0x0014 },		//	INR CM_ENA=0, R_IP_SEL_N=01, R_IP_SEL_P=01, R_MODE=00
	{ 0x2C, 0x0005 },		//	LINMUTE=0, LIN_VOL=0_0101
	{ 0x2D, 0x0005 },		//	RINMUTE=0, RIN VOL=0_0101
	{ 0x3D, 0x000f },		//	HPL_BYP_ENA=1, HPR_BYP_ENA=1, LINEOUTL_BYP ENA=1, LINEOUTR_BYP ENA=1

	{ 0x39, 0x0039 },		//	HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=11_1001
	{ 0x3A, 0x0039 },		//	HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=11_1001

	{ 0x43, 0x000f },		//	Enable DC servos

	{ 0x5A, 0x00FF },		//	HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1, HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1
	{ 0x5E, 0x00FF },		//	LINEOUTL_RMV_SHORT=1, LINEOUTL_ENA_OUTP=1, LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT=1, LINEOUTR_ENA_OUTP=1, LINEOUTR_ENA_DLY=1, LINEOUTR_ENA=1
	{ 0x62, 0x0001 },		//	CP_ENA=1
	{ 0x68, 0x0005 },		//	CP_DYN_PWR=1
};
const uint32_t i2_abp_hp_ct = sizeof(i2_abp_hp_arr)/sizeof(REG_CONFIG_T);

const REG_CONFIG_T i3_abp_line_arr[] = {
	{ 0x04, 0x0009 },		//	POBCTRL=0, ISEL=10, STARTUP_BIAS_ENA=0, BIAS_ENA=1
	{ 0x05, 0x0043 },		//	VMID_BUF_ENA=1, VMID_RES=01, VMID_ENA=1
	{ 0x0C, 0x0003 },		//	INL_ENA=1, INR_ENA=1
	{ 0x0F, 0x0003 },		//	LINEOUTL_PGA ENA=1, LINEOUTR_PGA ENA=1
	{ 0x2E, 0x0024 },		//	INL_CM_ENA=0, L_IP_SEL_N=10, L_IP_SEL_P=01, L_MODE=00
	{ 0x2F, 0x0024 },		//	INR CM_ENA=0, R_IP_SEL_N=10, R_IP_SEL_P=01, R_MODE=00
	{ 0x2C, 0x0005 },		//	LINMUTE=0, LIN_VOL=0_0101
	{ 0x2D, 0x0005 },		//	RINMUTE=0, RIN VOL=0_0101HPL_BYP ENA=0, HPR_BYP ENA=0, LINEOUTL_BYP ENA=1
	{ 0x3D, 0x0003 },		//	HPL_BYP_ENA=0, HPR_BYP_ENA=0, LINEOUTL_BYP ENA=1, LINEOUTR_BYP ENA=1
	{ 0x5E, 0x00FF },		//	LINEOUTL_RMV_SHORT=1, LINEOUTL_ENA_OUTP=1, LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT=1, LINEOUTR_ENA_OUTP=1, LINEOUTR_ENA_DLY=1, LINEOUTR_ENA=1
	{ 0x62, 0x0001 },		//	CP_ENA=1
};
const uint32_t i3_abp_line_ct = sizeof(i3_abp_line_arr)/sizeof(REG_CONFIG_T);

//------------------------------------------------------------------------------
//	title:	IN3LR to line-out L/R (digital loop-back)
//	input:	IN3[LR]
//	output:	LINEOUT[LR]
//	path:	IN3[LR] --> PGA --> ADC -->DAC --> line-out
//------------------------------------------------------------------------------
//
const REG_CONFIG_T digital_loopback_arr[] = {
	{ 0x04, 0x0019 },		//	POBCTRL=1, ISEL=10, STARTUP_BIAS_ENA=0, BIAS_ENA=1
	{ 0x05, 0x0043 },		//	VMID_BUF_ENA=1, VMID_RES=01, VMID_ENA=1
	{ 0x14, 0x845E },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	{ 0x0C, 0x0003 },		//	INL_ENA=1, INR ENA=1
	{ 0x0F, 0x0003 },		//	LINEOUTL_PGA_ENA=1, LINEOUTR_PGA_ENA=1
	{ 0x12, 0x000F },		//	DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1
	{ 0x18, 0x0150 },		//	DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=1, AIFADCL_SRC=0, AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0, DAC_COMP=0, DAC_COMPMODE=0
	{ 0x21, 0x0000 },		//	DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0, DAC_OSR128=0, DAC_MUTE=0, DEEMPH=00
	{ 0x2E, 0x0024 },		//	INL_CM_ENA=0, L_IP_SEL_N=10, L_IP_SEL_P=01, L_MODE=00
	{ 0x2F, 0x0024 },		//	INR CM_ENA=0, R_IP_SEL_N=10, R_IP_SEL_P=01, R_MODE=00
	{ 0x2C, 0x0005 },		//	LINMUTE=0, LIN_VOL=0_0101
	{ 0x2D, 0x0005 },		//	RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1, LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1, LINEOUTR_ENA_OUTP=1,
	{ 0x5E, 0x00FF },		//	LINEOUTR_ENA_DLY=1, LINEOUTR_ENA=1
	{ 0x68, 0x0005 },		//	CP_DYN_PWR=1
	{ 0x62, 0x0001 },		//	CP_ENA=1
};
const uint32_t digital_loopback_ct = sizeof(digital_loopback_arr)/sizeof(REG_CONFIG_T);

//------------------------------------------------------------------------------
//	title:	IN3LR to line-out L/R (digital loop-back)
//	input:	IN3[LR]
//	output:	LINEOUT[LR]
//	path:	IN3[LR] --> PGA --> ADC -->DAC --> line-out/headphone-out
//------------------------------------------------------------------------------
//
const REG_CONFIG_T i2_loop_arr[] = {
	{ 0x06, 0x0001 },		// MICDET_THR=0.070mA, MICSHORT_THR=0.520mA, MICDET_ENA=0, MIC_BIAS_ENA=1
	{ 0x07, 0x0004 },		// MICBIAS_SEL=2.7V

	{ 0x04, 0x0019 },		//	POBCTRL=1, ISEL=10, STARTUP_BIAS_ENA=0, BIAS_ENA=1
	{ 0x05, 0x0043 },		//	VMID_BUF_ENA=1, VMID_RES=01, VMID_ENA=1
	{ 0x14, 0x845E },		//	TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=0, SR_MODE=0, MCLK_DIV=0 (Required for MMCs: SGY, KRT see erratum CE000546)
	{ 0x0C, 0x0003 },		//	INL_ENA=1, INR ENA=1
	{ 0x0E, 0x0003 },		//	HPL_PGA_ENA=1, HPR_PGA_ENA=1
	{ 0x0F, 0x0003 },		//	LINEOUTL_PGA_ENA=1, LINEOUTR_PGA_ENA=1
	{ 0x12, 0x000F },		//	DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1
	{ 0x18, 0x0150 },		//	DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=1, AIFADCL_SRC=0, AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0, DAC_COMP=0, DAC_COMPMODE=0
	{ 0x20, 0x0CC9 },		//	ADCL_DAC_SVOL=0dB, ADCR_DAC_SVOL=0dB, ADC_TO_DACL= 01 (left ADC), ADC_TO_DACR= 10 (right ADC)
	{ 0x21, 0x0000 },		//	DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0, DAC_OSR128=0, DAC_MUTE=0, DEEMPH=00
	{ 0x2E, 0x0014 },		//	INL_CM_ENA=0, L_IP_SEL_N=10, L_IP_SEL_P=01, L_MODE=00
	{ 0x2F, 0x0014 },		//	INR CM_ENA=0, R_IP_SEL_N=10, R_IP_SEL_P=01, R_MODE=00
	{ 0x2C, 0x0005 },		//	LINMUTE=0, LIN_VOL=0_0101
	{ 0x2D, 0x0005 },		//	RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1, LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1, LINEOUTR_ENA_OUTP=1,
	{ 0x3D, 0x0000 },		//	HPL_BYP_ENA=0, HPR_BYP_ENA=0, LINEOUTL_BYP ENA=0, LINEOUTR_BYP ENA=0

	{ 0x39, 0x0039 },		//	HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=11_1001
	{ 0x3A, 0x0039 },		//	HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=11_1001

	{ 0x43, 0x000f },		//	Enable DC servos

	{ 0x5A, 0x00FF },		//	HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1, HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1
	{ 0x5E, 0x00FF },		//	LINEOUTR_ENA_DLY=1, LINEOUTR_ENA=1
	{ 0x68, 0x0005 },		//	CP_DYN_PWR=1
	{ 0x62, 0x0001 },		//	CP_ENA=1
};
const uint32_t i2_loop_ct = sizeof(i2_loop_arr)/sizeof(REG_CONFIG_T);

//------------------------------------------------------------------------------
//	Register default configuration
//------------------------------------------------------------------------------
const REG_CONFIG_T	wm8904_default_arr[] = {
	{ 4,   0x0018 },	 	// R4	 - Bias Control 0
	{ 5,   0x0000 },	 	// R5	 - VMID Control 0
	{ 6,   0x0000 },	 	// R6	 - Mic Bias Control 0
	{ 7,   0x0000 },	 	// R7	 - Mic Bias Control 1
	{ 8,   0x0001 },	 	// R8	 - Analogue DAC 0
	{ 9,   0x9696 },	 	// R9	 - mic Filter Control
	{ 10,  0x0001 },	 	// R10	 - Analogue ADC 0
	{ 12,  0x0000 },	 	// R12	 - Power Management 0
	{ 14,  0x0000 },	 	// R14	 - Power Management 2
	{ 15,  0x0000 },	 	// R15	 - Power Management 3
	{ 18,  0x0000 },	 	// R18	 - Power Management 6
	{ 20,  0x845E },// Magicoe 0x945E },	 	// R20	 - Clock Rates 0
	{ 21,  0x0C05 },	 	// R21	 - Clock Rates 1
	{ 22,  0x0006 },	 	// R22	 - Clock Rates 2
	{ 24,  0x0050 },	 	// R24	 - Audio Interface 0
	{ 25,  0x000A },	 	// R25	 - Audio Interface 1
	{ 26,  0x00E4 },	 	// R26	 - Audio Interface 2
	{ 27,  0x0040 },	 	// R27	 - Audio Interface 3
	{ 30,  0x00C0 },	 	// R30	 - DAC Digital Volume Left
	{ 31,  0x00C0 },	 	// R31	 - DAC Digital Volume Right
	{ 32,  0x0000 },	 	// R32	 - DAC Digital 0
	{ 33,  0x0000 }, // Magicoe 0x0008 },	 	// R33	 - DAC Digital 1
	{ 36,  0x00C0 },	 	// R36	 - ADC Digital Volume Left
	{ 37,  0x00C0 },	 	// R37	 - ADC Digital Volume Right
	{ 38,  0x0010 },	 	// R38	 - ADC Digital 0
	{ 39,  0x0000 },	 	// R39	 - Digital Microphone 0
	{ 40,  0x01AF },	 	// R40	 - DRC 0
	{ 41,  0x3248 },	 	// R41	 - DRC 1
	{ 42,  0x0000 },	 	// R42	 - DRC 2
	{ 43,  0x0000 },	 	// R43	 - DRC 3
	{ 44,  0x0085 },	 	// R44	 - Analogue Left Input 0
	{ 45,  0x0085 },	 	// R45	 - Analogue Right Input 0
	{ 46,  0x0044 },	 	// R46	 - Analogue Left Input 1
	{ 47,  0x0044 },	 	// R47	 - Analogue Right Input 1
	{ 57,  0x0039 }, // Magicoe 0x002D },	 	// R57	 - Analogue OUT1 Left
	{ 58,  0x00B9 }, // Magicoe 0x002D },	 	// R58	 - Analogue OUT1 Right
	{ 59,  0x0039 },	 	// R59	 - Analogue OUT2 Left
	{ 60,  0x0039 },	 	// R60	 - Analogue OUT2 Right
	{ 61,  0x0000 },	 	// R61	 - Analogue OUT12 ZC
	{ 67,  0x0000 },	 	// R67	 - DC Servo 0
	{ 69,  0xAAAA },	 	// R69	 - DC Servo 2
	{ 71,  0xAAAA },	 	// R71	 - DC Servo 4
	{ 72,  0xAAAA },	 	// R72	 - DC Servo 5
	{ 90,  0x0000 },	 	// R90	 - Analogue HP 0
	{ 94,  0x0000 },	 	// R94	 - Analogue Lineout 0
	{ 98,  0x0000 },	 	// R98	 - Charge Pump 0
	{ 104, 0x0005 }, // Magicoe 0x0004 },	 	// R104 - Class W 0
	{ 108, 0x0000 },	 	// R108 - Write Sequencer 0
	{ 109, 0x0000 },	 	// R109 - Write Sequencer 1
	{ 110, 0x0000 },	 	// R110 - Write Sequencer 2
	{ 111, 0x0000 },	 	// R111 - Write Sequencer 3
	{ 112, 0x0000 },	 	// R112 - Write Sequencer 4
	{ 116, 0x0000 },	 	// R116 - FLL Control 1
	{ 117, 0x0007 },	 	// R117 - FLL Control 2
	{ 118, 0x0000 },	 	// R118 - FLL Control 3
	{ 119, 0x2EE0 },	 	// R119 - FLL Control 4
	{ 120, 0x0004 },	 	// R120 - FLL Control 5
	{ 121, 0x0014 },	 	// R121 - GPIO Control 1
	{ 122, 0x0010 },	 	// R122 - GPIO Control 2
	{ 123, 0x0010 },	 	// R123 - GPIO Control 3
	{ 124, 0x0000 },	 	// R124 - GPIO Control 4
	{ 126, 0x0000 },	 	// R126 - Digital Pulls
	{ 128, 0xFFFF },	 	// R128 - Interrupt Status Mask
	{ 129, 0x0000 },	 	// R129 - Interrupt Polarity
	{ 130, 0x0000 },	 	// R130 - Interrupt Debounce
	{ 134, 0x0000 },	 	// R134 - EQ1
	{ 135, 0x000C },	 	// R135 - EQ2
	{ 136, 0x000C },	 	// R136 - EQ3
	{ 137, 0x000C },	 	// R137 - EQ4
	{ 138, 0x000C },	 	// R138 - EQ5
	{ 139, 0x000C },	 	// R139 - EQ6
	{ 140, 0x0FCA },	 	// R140 - EQ7
	{ 141, 0x0400 },	 	// R141 - EQ8
	{ 142, 0x00D8 },	 	// R142 - EQ9
	{ 143, 0x1EB5 },	 	// R143 - EQ10
	{ 144, 0xF145 },	 	// R144 - EQ11
	{ 145, 0x0B75 },	 	// R145 - EQ12
	{ 146, 0x01C5 },	 	// R146 - EQ13
	{ 147, 0x1C58 },	 	// R147 - EQ14
	{ 148, 0xF373 },	 	// R148 - EQ15
	{ 149, 0x0A54 },	 	// R149 - EQ16
	{ 150, 0x0558 },	 	// R150 - EQ17
	{ 151, 0x168E },	 	// R151 - EQ18
	{ 152, 0xF829 },	 	// R152 - EQ19
	{ 153, 0x07AD },	 	// R153 - EQ20
	{ 154, 0x1103 },	 	// R154 - EQ21
	{ 155, 0x0564 },	 	// R155 - EQ22
	{ 156, 0x0559 },	 	// R156 - EQ23
	{ 157, 0x4000 },	 	// R157 - EQ24
	{ 161, 0x0000 },	 	// R161 - Control Interface Test 1
	{ 204, 0x0000 },	 	// R204 - Analogue Output Bias 0
	{ 247, 0x0000 },	 	// R247 - FLL NCO Test 0
	{ 248, 0x0019 },	 	// R248 - FLL NCO Test 1
};
const uint32_t wm8904_default_ct = sizeof(wm8904_default_arr)/sizeof(REG_CONFIG_T);

const REG_CONFIG_T	wm8904_reset_arr[] = {
		{ 0x00, 0x0000}, 					//	SW Reset
		{ 0x16, 0x000F}, 					//	Clock Rates 2(16H):      0006  MCLK_INV=0, SYSCLK_SRC=0, TOCLK_RATE=0, OPCLK_ENA=1, CLK_SYS_ENA=1, CLK_DSP_ENA=1, TOCLK_ENA=1

		/* execute default start=up sequence */
		{ 0x6C, 0x0100},					//	Write Sequencer 0(6CH):  0100  WSEQ_ENA=1, WSEQ_WRITE_INDEX=0_0000
		{ 0x6F, 0x0100},					//	Write Sequencer 3(6FH):  0100  WSEQ_ABORT=0, WSEQ_START=1, WSEQ_START_INDEX=00_0000
		{ 0xFF, 500},							//	Up to 500ms pause for write sequencer to finish before further writes

		{ 0x80, 0xFFFB},					// enable FLL lock interrupt
		{ 0x7F, 0x0004},					// clear FLL Lock interrupt status if set

		{ WM8904_GPIO_CONTROL_1, 0x1},		//	output sysclock
		{ WM8904_FLL_CONTROL_2, 0x0700},	//* FLL_OUTDIV=00_0111, FLL_CTRL_RATE=000, FLL_FRATIO=000 */

};

static const uint8_t dbg_reg_adr[] = {
	0x00, 0x04, 0x05, 0x06, 0x07, 0x0A, 0x0C, 0x0E, 0x0F, 0x12, 0x14,
	0x15, 0x16, 0x18, 0x19, 0x1A, 0x1B, 0x1E, 0x1F, 0x20, 0x21, 0x24,
	0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2c, 0x2d, 0x2e, 0x2f,
	0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x43, 0x44, 0x45, 0x47, 0x48, 0x49,
	0x4a, 0x4b, 0x4c, 0x4d, 0x5a, 0x5e, 0x62, 0x68, 0x6c, 0x6d, 0x6e,
	0x6f, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c,
	0x7e, 0x7f, 0x80, 0x81, 0x82, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b,
	0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0xc6, 0xf7, 0xf8
};
static const uint32_t dbg_reg_adr_ct = sizeof(dbg_reg_adr)/sizeof(uint8_t);

const uint32_t wm8904_reset_ct = sizeof(wm8904_reset_arr)/sizeof(REG_CONFIG_T);


#ifdef __cplusplus
}
#endif

//
//	End: wm8904.h
//
#endif  /* __WM8904_H */
