/*
 * @brief LPC5411X DMA service driver declarations and functions
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

#ifndef __DMA_SERVICE_5411X_H
#define __DMA_SERVICE_5411X_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup DMA_SERVICE_5411X CHIP: LPC5411X DMA Service driver
 * @ingroup CHIP_5411X_DRIVERS
 * @{
 */

typedef void (* dma_callback_t)(int32_t);

typedef struct {
	uint32_t channel;
	volatile uint32_t *register_location;
	uint32_t width;
	uint32_t src_increment;
	uint32_t dst_increment;
	bool     write;
} dma_peripheral_context_t;

typedef struct {
   DMA_CHDESC_T  descr[2];
} dma_dual_descriptor_t;  // Note this type must be 16 byte aligned for it to work correctly!

/**
 * @brief	Initialize DMA service
 * @param	base	: The base address where the DMA descriptors will be stored
 * @return	Nothing
 */
void Chip_DMASERVICE_Init(DMA_CHDESC_T * base);

/**
 * @brief	DMA service interrupt handler
 * @param	None
 * @return	Nothing
 * @Note    Must be called from DMA_IRQHandler
 */
void Chip_DMASERVICE_Isr(void);

/**
 * @brief	Register callback function
 * @param	pContext Pointer to peripheral channel context
 * @param	pCallback Pointer to callback function
 * @return	Nothing
 */
void Chip_DMASERVICE_RegisterCb(const dma_peripheral_context_t * pContext,dma_callback_t pCallback);

/**
 * @brief	Use Single buffer mechanism
 * @param	pContext Pointer to peripheral channel context
 * @param	pMem Pointer to data memory
 * @param	length Data memory length
 * @return	Nothing
 */
void Chip_DMASERVICE_SingleBuffer(const dma_peripheral_context_t * pContext, uint32_t  pMem, uint32_t length);

/**
 * @brief	Use double buffer mechanism
 * @param	pContext Pointer to peripheral channel context
 * @param	pMem Pointer to data memory
 * @param	length Data memory length
 * @param   pD Pointer to dma dual descriptor
 * @return	Nothing
 */
void Chip_DMASERVICE_DoubleBuffer(const dma_peripheral_context_t * pContext, uint32_t  pMem, uint32_t length,dma_dual_descriptor_t * pD);

#ifdef __cplusplus
}
#endif

#endif /* __DMA_SERVICE_5411X_H */
