/*
 * @brief DMIC driver declarations and functions
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

#include "chip.h"

// Descriptors for packed dma transfers (i.e consecutive data)	
dma_peripheral_context_t DMIC_CH0_DMA_CONTEXT = {
	DMAREQ_DMIC0,                    // dma channel
	&LPC_DMIC->CHANNEL[0].FIFO_DATA,  // register to read from
	DMA_XFERCFG_WIDTH_16,            // width 16bits
	DMA_XFERCFG_SRCINC_0,            // source incr
	DMA_XFERCFG_DSTINC_1,            // dst incr by 1 * width
	false                            // not write 
};


dma_peripheral_context_t DMIC_CH1_DMA_CONTEXT = {
	DMAREQ_DMIC1,                    // dma channel
	&LPC_DMIC->CHANNEL[1].FIFO_DATA,  // register to read from
	DMA_XFERCFG_WIDTH_16,            // width 16bits
	DMA_XFERCFG_SRCINC_0,            // source incr
	DMA_XFERCFG_DSTINC_1,            // dst incr by 1 * width
	false                            // not write 
};


// Descriptors for interleaved dma transfers (i.e transfer one data, leave next open, eg for interleaving left and right)	
dma_peripheral_context_t DMIC_CH0_DMA_INTERLEAVED_CONTEXT = {
	DMAREQ_DMIC0,                    // dma channel
	&LPC_DMIC->CHANNEL[0].FIFO_DATA,  // register to read from
	DMA_XFERCFG_WIDTH_16,            // width 16bits
	DMA_XFERCFG_SRCINC_0,            // source incr
	DMA_XFERCFG_DSTINC_2,            // dst incr by 2 * width
	false                            // not write 
};


dma_peripheral_context_t DMIC_CH1_DMA_INTERLEAVED_CONTEXT = {
	DMAREQ_DMIC1,                    // dma channel
	&LPC_DMIC->CHANNEL[1].FIFO_DATA,  // register to read from
	DMA_XFERCFG_WIDTH_16,            // width 16bits
	DMA_XFERCFG_SRCINC_0,            // source incr
	DMA_XFERCFG_DSTINC_2,            // dst incr by 2 * width
	false                            // not write 
};


void Chip_DMIC_Init(const CHIP_SYSCON_CLOCK_T clock, const CHIP_SYSCON_PERIPH_RESET_T reset)
{
	/* Enable the clock to the register interface */
	Chip_Clock_EnablePeriphClock(clock);

	/* Reset DMIC */
	Chip_SYSCON_PeriphReset(reset);
}


void Chip_DMIC_CfgIO(LPC_DMIC_T * pDMIC, dmic_io_t cfg)
{
      pDMIC->IOCFG = cfg;
};


void Chip_DMIC_SetOpMode(LPC_DMIC_T * pDMIC, op_mode_t mode)
{
   if (mode == dmic_op_intr) {
		  pDMIC->CHANNEL[0].FIFO_CTRL   |=   (1<<DMIC_FIFO_INTREN_P); // enable intr
		  pDMIC->CHANNEL[1].FIFO_CTRL   |=   (1<<DMIC_FIFO_INTREN_P); // enable intr
		  pDMIC->CHANNEL[0].FIFO_CTRL   &= ~ (1<<DMIC_FIFO_DMAEN_P);  // disable DMA
		  pDMIC->CHANNEL[1].FIFO_CTRL   &= ~ (1<<DMIC_FIFO_DMAEN_P);  // disable DMA
	 }
   if (mode == dmic_op_dma) {
 		  pDMIC->CHANNEL[0].FIFO_CTRL   &= ~ (1<<DMIC_FIFO_INTREN_P); // disable intr
		  pDMIC->CHANNEL[1].FIFO_CTRL   &= ~ (1<<DMIC_FIFO_INTREN_P); // disable intr
	 		pDMIC->CHANNEL[0].FIFO_CTRL   |=   (1<<DMIC_FIFO_DMAEN_P);  // enable DMA
		  pDMIC->CHANNEL[1].FIFO_CTRL   |=   (1<<DMIC_FIFO_DMAEN_P);  // enable DMA
	 }	 
 };


void Chip_DMIC_CfgChannel(LPC_DMIC_T * pDMIC, uint32_t channel, dmic_channel_config_t * channel_cfg)
{
   pDMIC->CHANNEL[channel].DIVHFCLK      = channel_cfg->divhfclk;  
   pDMIC->CHANNEL[channel].OSR           = channel_cfg->osr;       
   pDMIC->CHANNEL[channel].GAINSHFT      = channel_cfg->gainshft;  
   pDMIC->CHANNEL[channel].PREAC2FSCOEF  = channel_cfg->preac2coef;  
   pDMIC->CHANNEL[channel].PREAC4FSCOEF  = channel_cfg->preac4coef;  
   pDMIC->CHANNEL[channel].PHY_CTRL      = (channel_cfg->side<<DMIC_PHY_FALL_P);
};


void Chip_DMIC_CfgChannelDc(LPC_DMIC_T * pDMIC, uint32_t channel, dc_removal_t  dc_cut_level, uint32_t post_dc_gain_reduce, bool saturate16bit) 
{
	pDMIC->CHANNEL[channel].DC_CTRL = (dc_cut_level<<DMIC_DCPOLE_P) | (post_dc_gain_reduce<<DMIC_DCGAIN_REDUCE_P | (saturate16bit? (1<<DMIC_SATURATE_AT16BIT_P) : 0));  
};


void Chip_DMIC_Use2fs(LPC_DMIC_T * pDMIC, bool use2fs)
{
	pDMIC->USE2FS = (use2fs)? 0x1 : 0x0;
}


void Chip_DMIC_EnableChannnel(LPC_DMIC_T * pDMIC, uint32_t channelmask)
{
	pDMIC->CHANEN = channelmask;
};


void Chip_DMIC_FifoChannel(LPC_DMIC_T * pDMIC, uint32_t channel, uint32_t trig_level, uint32_t enable, uint32_t resetn)
{
	pDMIC->CHANNEL[channel].FIFO_CTRL   |=  (trig_level<<DMIC_FIFO_TLVL_P)|(enable<<DMIC_FIFO_ENABLE_P) | (resetn<<DMIC_FIFO_RESETN_P);
}
