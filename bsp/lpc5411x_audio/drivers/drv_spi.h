#ifndef __LPC54110__SPI_H_INCLUDED__
#define __LPC54110__SPI_H_INCLUDED__

#include <rtdevice.h>

#include "chip.h"
#include "board.h"

//#define SPI_USE_DMA

struct lpc54110_spi_bus
{
    struct rt_spi_bus parent;
    LPC_SPI_T * SPI;
#ifdef SPI_USE_DMA
//    DMA_Channel_TypeDef * DMA_Channel_TX;
//    DMA_Channel_TypeDef * DMA_Channel_RX;
//    uint32_t DMA_Channel_TX_FLAG_TC;
//    uint32_t DMA_Channel_TX_FLAG_TE;
//    uint32_t DMA_Channel_RX_FLAG_TC;
//    uint32_t DMA_Channel_RX_FLAG_TE;
#endif /* SPI_USE_DMA */
};

struct lpc54110_spi_cs
{
    LPC_GPIO_T * GPIOx;
	  uint8_t  GPIO_Port;
    uint32_t GPIO_Pin;
};

/* public function list */
rt_err_t lpc54110_spi_register(LPC_SPI_T * SPI,
                            struct lpc54110_spi_bus * lpc_spi,
                            const char * spi_bus_name);

extern void rt_hw_spi_init(void);
														
#endif // __LPC54110__SPI_H_INCLUDED__
