/*
 * @brief LPC5411X DMIC driver declarations and functions
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

#ifndef __DMIC_5411X_H
#define __DMIC_5411X_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup DMIC_5411X CHIP: LPC5411X DMIC driver
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

typedef struct {
  __IO uint32_t OSR;         // 0x00  
  __IO uint32_t DIVHFCLK;    // 0x04  
  __IO uint32_t PREAC2FSCOEF;// 0x08  
  __IO uint32_t PREAC4FSCOEF;// 0x0c  
  __IO uint32_t GAINSHFT;    // 0x10  
  __IO uint32_t TDM96EN;     // 0x14  
  __IO uint32_t TDM19EN;     // 0x18  
  __IO uint32_t reserved[25];  
  __IO uint32_t FIFO_CTRL;   // 0x80
  __IO uint32_t FIFO_STATUS; // 0x84
  __IO uint32_t FIFO_DATA;   // 0x88
  __IO uint32_t PHY_CTRL;    // 0x8C
  __IO uint32_t DC_CTRL;     // 0x90
  __IO uint32_t reserved1[27];//
} LPC_DMIC_Channel_Type;


typedef struct {
  __IO LPC_DMIC_Channel_Type CHANNEL[15]; // 0x000 - 0xefc  with 0x100 per channel
  // common
  __IO uint32_t CHANEN;       // 0xf00
  __IO uint32_t ONRATIO;      // 0xf04
  __IO uint32_t INFREQSEL;    // 0xf08  
  __IO uint32_t IOCFG;        // 0xf0C  
  __IO uint32_t USE2FS;       // 0xf10  
  __IO uint32_t reserved[27]; // 0xf14 - 0xf7c  
  // HWVAD
  __IO uint32_t HWVADGAIN;    // 0xf80
  __IO uint32_t HWVADHPFS;    // 0xf84  
  __IO uint32_t HWVADST10;    // 0xf88
  __IO uint32_t HWVADRSTT;    // 0xf8c  
  __IO uint32_t HWVADTHGN;    // 0xf90
  __IO uint32_t HWVADTHGS;    // 0xf94  
  __IO uint32_t HWVADLOWZ;    // 0xf98  
  __IO uint32_t reserved1[24];// 0xf9c - 0xff8 
  __O uint32_t ID;           // 0xffc
} LPC_DMIC_T;


// INFREQ SEL selection
//
//  OSR     Infreq SEL
// -------------------------
//  16   ->   0
//  32   ->   1  
//  64   ->   2
//  128  ->   3
//  256  ->   4
//  512  ->   5

// FIFO CTRL bits
#define DMIC_FIFO_ENABLE_P 0
#define DMIC_FIFO_RESETN_P 1
#define DMIC_FIFO_INTREN_P 2
#define DMIC_FIFO_DMAEN_P  3



#define DMIC_FIFO_TLVL_P   16

#define DMIC_FIFO_ENABLE (1<<DMIC_FIFO_ENABLE_P)
#define DMIC_FIFO_RESETN (1<<DMIC_FIFO_RESETN_P)
#define DMIC_FIFO_INTREN (1<<DMIC_FIFO_INTREN_P)
#define DMIC_FIFO_DMAEN  (1<<DMIC_FIFO_DMAEN_P )


// FIFO STATUS bits
#define DMIC_FIFO_INT_P      0
#define DMIC_FIFO_OVERRUN_P  1
#define DMIC_FIFO_UNDERRUN_P 2

#define DMIC_FIFO_INT      (1<<DMIC_FIFO_INT_P     )
#define DMIC_FIFO_OVERRUN  (1<<DMIC_FIFO_OVERRUN_P )
#define DMIC_FIFO_UNDERRUN (1<<DMIC_FIFO_UNDERRUN_P)

// PHY CTRL bits
#define DMIC_PHY_FALL_P 0
#define DMIC_PHY_HALF_P 1

#define DMIC_PHY_FALL (1<<DMIC_PHY_FALL_P)
#define DMIC_PHY_HALF (1<<DMIC_PHY_HALF_P)

// DC Block ctrl

#define DMIC_DCPOLE_P 0
#define DMIC_DCGAIN_REDUCE_P 4
#define DMIC_SATURATE_AT16BIT_P 8

/* note that the polling mode can be achieved without the driver, it is in 
any way not recommended due to its overhead, this link should normally use dma or irq */
typedef enum 
{
	dmic_op_poll,
	dmic_op_intr, 
	dmic_op_dma,
} op_mode_t;

typedef enum {
	dmic_left=0,
	dmic_right=1,
} stereo_side_t;

typedef enum {
	dmic_pdm_div1  =0,
	dmic_pdm_div2  =1,
	dmic_pdm_div3  =2,
	dmic_pdm_div4  =3,
	dmic_pdm_div6  =4,
	dmic_pdm_div8  =5,
	dmic_pdm_div12 =6,
	dmic_pdm_div16 =7,
	dmic_pdm_div24 =8,
	dmic_pdm_div32 =9,
	dmic_pdm_div48 =10,
	dmic_pdm_div64 =11,
	dmic_pdm_div96 =12,
	dmic_pdm_div128=13,
} pdm_div_t;
    
typedef enum {    
	dmic_comp0_0  =0,
	dmic_comp0_16 =1, 
	dmic_comp0_15 =2, 
	dmic_comp0_13 =3,
} compensation_t;

typedef enum {    
	dmic_dc_noremove  =0,
	dmic_dc_cut155    =1, 
	dmic_dc_cut78     =2, 
	dmic_dc_cut39     =3,
} dc_removal_t;

typedef enum {    
	pdm_dual    =0,      /*!< Two separate pairs of PDM wires */
	pdm_stereo  =4,      /*!< Stereo Mic */
	pdm_bypass  =3,      /*!< Clk Bypas clocks both channels */
	pdm_bypass_clk0  =1, /*!< Clk Bypas clocks only channel0 */
	pdm_bypass_clk1  =2  /*!< Clk Bypas clocks only channel1 */
} dmic_io_t;
								
typedef struct {
	stereo_side_t  side;
	pdm_div_t      divhfclk;
	uint32_t       osr;
	int32_t        gainshft;
	compensation_t preac2coef; 
	compensation_t preac4coef;
} dmic_channel_config_t;

/**
 * @brief	Initialize DMIC interface
 * @param	clock	: DMIC clock assignment
 * @param	reset	: DMIC reset assignment
 * @return	Nothing
 */
void Chip_DMIC_Init(const CHIP_SYSCON_CLOCK_T clock, const CHIP_SYSCON_PERIPH_RESET_T reset);

/**
 * @brief	Configure DMIC io
 * @param	pDMIC	: The base address of DMIC interface
 * @param	cfg	    : DMIC io configuration
 * @return	Nothing
 */
void Chip_DMIC_CfgIO(LPC_DMIC_T * pDMIC, dmic_io_t cfg);

/**
 * @brief	Set DMIC operating mode
 * @param	pDMIC	: The base address of DMIC interface
 * @param	mode	: DMIC mode
 * @return	Nothing
 */
void Chip_DMIC_SetOpMode(LPC_DMIC_T * pDMIC, op_mode_t mode);

/**
 * @brief	Configure DMIC channel
 * @param	pDMIC	    : The base address of DMIC interface
 * @param	channel	    : DMIC channel
 * @param	channel_cfg	: Channel configuration
 * @return	Nothing
 */
void Chip_DMIC_CfgChannel(LPC_DMIC_T * pDMIC, uint32_t channel, dmic_channel_config_t * channel_cfg);

/**
 * @brief	Configure DMIC channel DC removal setting
 * @param	pDMIC	            : The base address of DMIC interface
 * @param	channel	            : DMIC channel
 * @param	dc_cut_level        : DC cut level
 * @param	post_dc_gain_reduce : Post DC cut gain adjustment
 * @param	saturate16bit       : Saturation setting
 * @return	Nothing
 */
void Chip_DMIC_CfgChannelDc(LPC_DMIC_T * pDMIC, uint32_t channel, dc_removal_t  dc_cut_level, uint32_t post_dc_gain_reduce, bool saturate16bit);

/**
 * @brief	Configure Clock scaling
 * @param	pDMIC	    : The base address of DMIC interface
 * @param	use2fs	    : clock scaling
 * @return	Nothing
 */
void Chip_DMIC_Use2fs(LPC_DMIC_T * pDMIC, bool use2fs);

/**
 * @brief	Configure Clock scaling
 * @param	pDMIC	    : The base address of DMIC interface
 * @param	channelmask	: Channel selection
 * @return	Nothing
 */
void Chip_DMIC_EnableChannnel(LPC_DMIC_T * pDMIC, uint32_t channelmask);

/**
 * @brief	Configure fifo settings for DMIC channel
 * @param	pDMIC	    : The base address of DMIC interface
 * @param	channel	    : DMIC channel
 * @param	trig_level  : FIFO trigger level
 * @param	enable      : FIFO level
 * @param	resetn      : FIFO reset
 * @return	Nothing
 */
void Chip_DMIC_FifoChannel(LPC_DMIC_T * pDMIC, uint32_t channel, uint32_t trig_level, uint32_t enable, uint32_t resetn);

extern dma_peripheral_context_t DMIC_CH0_DMA_CONTEXT;
extern dma_peripheral_context_t DMIC_CH1_DMA_CONTEXT;
extern dma_peripheral_context_t DMIC_CH0_DMA_INTERLEAVED_CONTEXT;
extern dma_peripheral_context_t DMIC_CH1_DMA_INTERLEAVED_CONTEXT;

#ifdef __cplusplus
}
#endif

#endif /* __DMIC_5411X_H */
