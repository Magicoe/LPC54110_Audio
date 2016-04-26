/*
 * @brief LPC5411x I2S driver
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

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
int Chip_I2S_Init(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt)
{
	int ret_val = -1;															/* initialize error status to -1 */

	switch (fmt->Direction) {													/* switch on port direction */
	case I2S_TX:
		ret_val = Chip_FLEXCOMM_Init(pI2S, FLEXCOMM_PERIPH_I2S_TX);
		break;

	case I2S_RX:
		ret_val = Chip_FLEXCOMM_Init(pI2S, FLEXCOMM_PERIPH_I2S_RX);
		break;
	}

	return ret_val;
}

/* Configure I2S for Audio Format input */
Status Chip_I2S_Config(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt)
{
	volatile uint32_t	cfg1 = 0, cfg2 = 0;

	switch (fmt->MSCfg) {														/* program the correct master/slave configuration */
	case NORMAL_SLAVE:															/* set to normal slave */
		cfg1 |= I2S_CFG1_MSTSLVCFG(0);
		break;
	case WS_SYNC_MASTER:														/* set to WS sync master mode */
		cfg1 |= I2S_CFG1_MSTSLVCFG(1);
		break;
	case EXT_SCLCK_MASTER:														/* set to SCLK master mode */
		cfg1 |= I2S_CFG1_MSTSLVCFG(2);
		break;
	case NORMAL_MASTER:															/* set to normal master mode */
		cfg1 |= I2S_CFG1_MSTSLVCFG(3);
		break;
	}

	switch (fmt->Mode) {														/* set I2S mode */
	case I2S_CLASSIC:
		cfg1 |= I2S_CFG1_MODE(0);
		break;
	case DSP_WS_50:
		cfg1 |= I2S_CFG1_MODE(1);
		break;
	case DSP_WS_SHORT:
		cfg1 |= I2S_CFG1_MODE(2);
		break;
	case DSP_WS_LONG:
		cfg1 |= I2S_CFG1_MODE(3);
		break;
	}

	cfg1 |= (fmt->RightLow == true)		? I2S_CFG1_RIGHTLOW		: 0;			/* set right low (channel swap) */
	cfg1 |= (fmt->LeftJust == true)		? I2S_CFG1_LEFTJUST		: 0;			/* set data justification */
	cfg1 |= (fmt->PDMData == true)		? I2S_CFG1_PDMDATA		: 0;			/* set source to PDM dmic */
	cfg1 |= (fmt->SCKPol == true)		? I2S_CFG1_PDMDATA		: 0;			/* set SCLK polarity */
	cfg1 |= (fmt->WSPol == true)		? I2S_CFG1_PDMDATA		: 0;			/* set WS polarity */
	cfg1 |= (fmt->ChannelNumber == 1)	? I2S_CFG1_ONECHANNEL	: 0;			/* set mono mode */
	cfg1 |= I2S_CFG1_DATALEN(fmt->WordWidth-1);									/* set data length */

	cfg2 |= I2S_CFG2_FRAMELEN(fmt->FrameWidth-1);								/* set frame width */
	cfg2 |= I2S_CFG2_POSITION(fmt->DataPos);									/* set data position within the frame */

	pI2S->CFG1	= cfg1;															/* set configuration in registers */
	pI2S->CFG2	= cfg2;
	pI2S->DIV	= ((fmt->Divider-1) & 0x1ff);									/* set the clock divider */

	return SUCCESS;
}

/* Enable/Disable Interrupt with a specific FIFO depth */
void Chip_I2S_FIFO_Config(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt)
{
	I2S_DIR_T d = fmt->Direction;
	volatile uint32_t cfg=0, trig=0;

	if (d == I2S_TX) {
		cfg |= I2S_FIFO_CFG_ENABLETX;											/* enable TX FIFO */
		cfg |= I2S_FIFO_CFG_EMPTYTX;											/* empty TX FIFO */
		trig |=I2S_FIFO_TRIG_TXLVLENA;											/* enable TX FIFO trigger */
		trig |= I2S_FIFO_TRIG_TXLVL(fmt->FIFOdepth);							/* set TX FIFO trigger level */
	} else {
		cfg |= I2S_FIFO_CFG_ENABLERX;											/* enable RX FIFO */
		cfg |= I2S_FIFO_CFG_EMPTYRX;											/* empty RX FIFO */
		trig |=I2S_FIFO_TRIG_RXLVLENA;											/* enable RX FIFO trigger */
		trig |= I2S_FIFO_TRIG_RXLVL(fmt->FIFOdepth);							/* set RX FIFO trigger level */
	}
	pI2S->FIFOCFG = cfg;														/* set configuration in registers */
	pI2S->FIFOTRIG = trig;
}

static void fifo_ctrl_tx(LPC_I2S_T *pI2S, I2S_FIFO_CMD_T cmd)
{
	switch (cmd) {
	case I2S_FIFO_ENABLE:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_ENABLETX;									/* enable TX FIFO */
		break;
	case I2S_FIFO_DISABLE:
		pI2S->FIFOCFG &= ~I2S_FIFO_CFG_ENABLETX;								/* disable TX FIFO */
		break;
	case I2S_FIFO_DMA_ENABLE:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_DMATX;									/* enable DMA */
		break;
	case I2S_FIFO_DMA_DISABLE:
		pI2S->FIFOCFG &= ~I2S_FIFO_CFG_DMATX;									/* disable DMA */
		break;
	case I2S_FIFO_CLEAR:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_EMPTYTX;									/* clear TX FIFO */
		break;
	case I2S_FIFO_TXZ_ENABLE:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_TXI2SE0;									/* enable TX zero */
		break;
	case I2S_FIFO_TXZ_DISABLE:
		pI2S->FIFOCFG &= ~I2S_FIFO_CFG_TXI2SE0;									/* disable TX zero */
		break;
	}
}

static void fifo_ctrl_rx(LPC_I2S_T *pI2S, I2S_FIFO_CMD_T cmd)
{
	switch (cmd) {
	case I2S_FIFO_ENABLE:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_ENABLERX;									/* enable RX FIFO */
		break;
	case I2S_FIFO_DISABLE:
		pI2S->FIFOCFG &= ~I2S_FIFO_CFG_ENABLERX;								/* disable RX FIFO */
		break;
	case I2S_FIFO_DMA_ENABLE:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_DMARX;									/* enable DMA */
		break;
	case I2S_FIFO_DMA_DISABLE:
		pI2S->FIFOCFG &= ~I2S_FIFO_CFG_DMARX;									/* disable DMA */
		break;
	case I2S_FIFO_CLEAR:
		pI2S->FIFOCFG |= I2S_FIFO_CFG_EMPTYRX;									/* clear RX FIFO */
		break;
	case I2S_FIFO_TXZ_ENABLE:													/* not applicable to RX */
	case I2S_FIFO_TXZ_DISABLE:
		break;
	}
}

void Chip_I2S_FIFO_Control(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *fmt, I2S_FIFO_CMD_T cmd)
{
	I2S_DIR_T d = fmt->Direction;

	switch (d) {
	case I2S_TX:
		fifo_ctrl_tx(pI2S, cmd);
		break;

	case I2S_RX:
		fifo_ctrl_rx(pI2S, cmd);
		break;

	default:
		break;
	}
}
