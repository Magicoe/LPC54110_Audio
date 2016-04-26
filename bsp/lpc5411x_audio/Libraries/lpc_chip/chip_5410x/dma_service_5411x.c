/*
 * @brief DMA driver declarations and functions
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

dma_callback_t dma_pCallback_array[MAX_DMA_CHANNEL];  // callback array 
dma_callback_t dma_service_error_cb;

void Chip_DMASERVICE_Init(DMA_CHDESC_T * base)
{
	int32_t i;
	dma_service_error_cb = 0;
	for (i=0;i<=MAX_DMA_CHANNEL;i++){
	   dma_pCallback_array[i] = 0;
	}
	Chip_DMA_Init(LPC_DMA);
	Chip_DMA_SetSRAMBase(LPC_DMA, (uint32_t) base);
	Chip_DMA_Enable(LPC_DMA);
}


void Chip_DMASERVICE_ErrorHandler(void)
{
	if (LPC_DMA->DMACOMMON[0].ERRINT != 0) {
		// If handler for error is attached, we execute it
		if(dma_service_error_cb != (void *)0) {
		   dma_service_error_cb(0);
		} else {
			LPC_DMA->DMACOMMON[0].ERRINT = LPC_DMA->DMACOMMON[0].ERRINT; // if no callback, then we just clear all errors outselves
		}
	}
};


void Chip_DMASERVICE_Isr(void)
{
	int32_t i;
	uint32_t tempInta = 1;
	uint32_t tempIntb = 1;
	Chip_DMASERVICE_ErrorHandler();   // Handle any error should there be one

	for ( i=0;i<32 && ((tempInta|tempIntb) != 0);i++) {
		tempInta = LPC_DMA->DMACOMMON[0].INTA;
		if (tempInta & (1<<i)) {
			LPC_DMA->DMACOMMON[0].INTA = 1<<i;  // clears interrupt
			if (dma_pCallback_array[i] != NULL) {
				dma_pCallback_array[i](0);
			}
		}
		tempIntb = LPC_DMA->DMACOMMON[0].INTB;
		if (tempIntb & (1<<i)){
			LPC_DMA->DMACOMMON[0].INTB = 1<<i;  // clears interrupt
			if (dma_pCallback_array[i] != NULL) {
				dma_pCallback_array[i](1);
			}
		}
	}
}


void Chip_DMASERVICE_RegisterCb(const dma_peripheral_context_t * pContext,dma_callback_t pCallback)
{
	dma_pCallback_array[pContext->channel] = pCallback;
}


#define	DMA_XFERCFG_WIDTH_P  8
#define	DMA_XFERCFG_DSTINC_P 14


void Chip_DMASERVICE_SingleBuffer(const dma_peripheral_context_t * pContext, uint32_t  pMem, uint32_t length)
{
	uint32_t cfg_val;
	DMA_CHDESC_T * pTable;
	uint32_t  source; 
	uint32_t  destination;
	uint32_t  xfercount; 
	uint32_t  actual_width,actual_dst_inc;
	
	actual_width   = (pContext->width)>>DMA_XFERCFG_WIDTH_P;
	actual_dst_inc = (pContext->dst_increment)>>DMA_XFERCFG_DSTINC_P;

	xfercount      = (length)>>(actual_width<<(actual_dst_inc-1)); // we take length in bytes, divide in half for doublebuffer and then downshift by width
	source         = (pContext->write) ? (pMem + length - (1<<(actual_width<<(actual_dst_inc-1)))) : (uint32_t)pContext->register_location; 
	destination    = (pContext->write) ? (uint32_t)pContext->register_location : (pMem + length - (1<<(actual_width<<(actual_dst_inc-1)))); 

	pTable	= (DMA_CHDESC_T *) LPC_DMA->SRAMBASE; // get DMA table base
		
	cfg_val  = (pContext->width)| (pContext->src_increment) | (pContext->dst_increment);
	cfg_val |= DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SWTRIG   | DMA_XFERCFG_XFERCOUNT(xfercount);
	  
	pTable[pContext->channel].dest     = destination;
	pTable[pContext->channel].source   = source;
	pTable[pContext->channel].next     = (uint32_t) 0;
	LPC_DMA->DMACH[pContext->channel].CFG     = DMA_CFG_PERIPHREQEN;
	LPC_DMA->DMACH[pContext->channel].XFERCFG = cfg_val | DMA_XFERCFG_SETINTA;
}


void Chip_DMASERVICE_DoubleBuffer(const dma_peripheral_context_t * pContext, uint32_t  pMem, uint32_t length,dma_dual_descriptor_t * pD)
{
	uint32_t cfg_val;
	DMA_CHDESC_T * pTable;
	uint32_t  source[2]; 
	uint32_t  destination[2];
	uint32_t  xfercount; 
	uint32_t  actual_width,actual_dst_inc;

	actual_width   = (pContext->width)>>DMA_XFERCFG_WIDTH_P;
	actual_dst_inc = (pContext->dst_increment)>>DMA_XFERCFG_DSTINC_P;

	xfercount      = (length>>1)>>(actual_width<<(actual_dst_inc-1)); // we take length in bytes, divide in half for doublebuffer and then downshift by width
	source[0]      = (pContext->write) ? pMem : (uint32_t)pContext->register_location; 
	destination[0] = (pContext->write) ? (uint32_t)pContext->register_location : (pMem + (length>>1) - (1<<(actual_width<<(actual_dst_inc-1)))); 
	source[1]      = (pContext->write) ? pMem + (length>>1) : (uint32_t)pContext->register_location; 
	destination[1] = (pContext->write) ? (uint32_t)pContext->register_location : (pMem + (length>>0) - (1<<(actual_width<<(actual_dst_inc-1)))); // if double buffer into mem, then we know we always increment, note dest is specified as final write location

	pTable	= (DMA_CHDESC_T *) LPC_DMA->SRAMBASE; // get DMA table base

	cfg_val  = DMA_XFERCFG_RELOAD   | (pContext->width)| (pContext->src_increment) | (pContext->dst_increment);
	cfg_val |= DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SWTRIG   | DMA_XFERCFG_XFERCOUNT(xfercount);

	pD->descr[0].xfercfg = cfg_val | DMA_XFERCFG_SETINTB;
	pD->descr[0].source  = (uint32_t) source[1];
	pD->descr[0].dest    = (uint32_t) destination[1];
	pD->descr[0].next    = (uint32_t) &pD->descr[1]; // jump to next descriptor

	pD->descr[1].xfercfg = cfg_val | DMA_XFERCFG_SETINTA;
	pD->descr[1].source  = (uint32_t) source[0];
	pD->descr[1].dest    = (uint32_t) destination[0];
	pD->descr[1].next    = (uint32_t) &pD->descr[0]; // jump back to previous descriptor

	pTable[pContext->channel].dest     = destination[0];
	pTable[pContext->channel].source   = source[0];
	pTable[pContext->channel].next     = (uint32_t) pD;
	LPC_DMA->DMACH[pContext->channel].CFG     = DMA_CFG_PERIPHREQEN;
	LPC_DMA->DMACH[pContext->channel].XFERCFG = cfg_val | DMA_XFERCFG_SETINTA;
}
