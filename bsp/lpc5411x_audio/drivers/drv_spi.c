#include "drv_spi.h"

//#define SPI0_FLEXCOMM   5      /* SPI0 associated with FLEXCOMM5 for Master */
#define SPI1_FLEXCOMM   3      /* SPI1 associated with FLEXCOMM3 for Slave */

static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops lpc54110_spi_ops =
{
    configure,
    xfer
};

#ifdef USING_SPI1
static struct lpc54110_spi_bus LPC_SPI1;
#endif /* #ifdef USING_SPI1 */

#ifdef USING_SPI2
static struct lpc54110_spi_bus LPC_SPI2;
#endif /* #ifdef USING_SPI2 */

#ifdef USING_SPI3
static struct lpc54110_spi_bus LPC_SPI3;
#endif /* #ifdef USING_SPI3 */

void SPI0_IRQHandler(void)
{
//	Chip_SPIM_XferHandler(LPC_SPI0, &spiMasterXfer);
}

void SPI1_IRQHandler(void)
{
//	Chip_SPIM_XferHandler(LPC_SPI1, &spiMasterXfer);
}


//------------------ DMA ------------------
#define SPI_USE_DMA 1

volatile LPC_DMA_T* g_DMAreg;
#ifdef SPI_USE_DMA
static uint8_t dummy = 0xFF;

DMA_CHDESC_T spi1_rx_dmaDesc, spi1_tx_dmaDesc;
volatile uint8_t spi1_tx_flag = 0;
volatile uint8_t spi1_rx_flag = 0;
volatile struct rt_semaphore spi1_tx_done_sem;
struct rt_semaphore spi1_rx_sem;

void DMA_IRQHandler(void)
{
	rt_interrupt_enter();
	/* Rrror interrupt on channel 0? */
	if ((Chip_DMA_GetIntStatus(LPC_DMA) & DMA_INTSTAT_ACTIVEERRINT) != 0) {
		/* This shouldn't happen for this simple DMA example, so set the LED
		   to indicate an error occurred. This is the correct method to clear
		   an abort. */
		Chip_DMA_DisableChannel(LPC_DMA, DMA_CH6);
		while ((Chip_DMA_GetBusyChannels(LPC_DMA) & (1 << DMA_CH6)) != 0) {}
		Chip_DMA_AbortChannel(LPC_DMA, DMA_CH6);
		Chip_DMA_ClearErrorIntChannel(LPC_DMA, DMA_CH6);
		Chip_DMA_EnableChannel(LPC_DMA, DMA_CH6);
			
		Chip_DMA_DisableChannel(LPC_DMA, DMA_CH7);
		while ((Chip_DMA_GetBusyChannels(LPC_DMA) & (1 << DMA_CH7)) != 0) {}
		Chip_DMA_AbortChannel(LPC_DMA, DMA_CH7);
		Chip_DMA_ClearErrorIntChannel(LPC_DMA, DMA_CH7);
		Chip_DMA_EnableChannel(LPC_DMA, DMA_CH7);
	}

	/* Clear DMA interrupt for the channel */
/* Clear DMA interrupt for the channel */
	if ( (Chip_DMA_GetIntStatus(LPC_DMA) & DMA_INTSTAT_ACTIVEINT) != 0 ) {
		if ( Chip_DMA_GetActiveIntAChannels(LPC_DMA) & (1 << DMA_CH6) ) {
			Chip_DMA_ClearActiveIntAChannel(LPC_DMA, DMA_CH6);
			spi1_rx_flag = 1;
			if( spi1_tx_flag == 1){
				spi1_tx_flag = spi1_rx_flag = 0;
				rt_sem_release(&spi1_tx_done_sem);				
			}
		}
		
		if ( Chip_DMA_GetActiveIntAChannels(LPC_DMA) & (1 << DMA_CH7) ) {
			Chip_DMA_ClearActiveIntAChannel(LPC_DMA, DMA_CH7);
			spi1_tx_flag = 1;
			if( spi1_rx_flag == 1){
				spi1_tx_flag = spi1_rx_flag = 0;
				rt_sem_release(&spi1_tx_done_sem);		
			}
		}
	}
	rt_interrupt_leave();
}

static void DMA_Init(void)
{
	if (rt_sem_init(&spi1_tx_done_sem, "spi1_tx_done_sem", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
		rt_kprintf("init spi1_tx_sem semaphore failed\n");
	
	rt_kprintf("Creat spi1_tx_sem and init ok \r\n");
	rt_sem_take(&spi1_tx_done_sem, 100);
	
	spi1_tx_flag = spi1_rx_flag = 0;
	g_DMAreg = LPC_DMA;
	Chip_DMA_Init(LPC_DMA);
	Chip_DMA_Enable(LPC_DMA);
	Chip_DMA_SetSRAMBase(LPC_DMA, DMA_ADDR(Chip_DMA_Table));
	
	LPC_DMA->DMACOMMON[0].ENABLESET |= (1UL<<DMA_CH6) | (1UL<<DMA_CH7);
	LPC_DMA->DMACOMMON[0].INTENSET  |= (1UL<<DMA_CH6) | (1UL<<DMA_CH7);
	LPC_DMA->DMACH[DMA_CH6].CFG = DMA_CFG_PERIPHREQEN | DMA_CFG_TRIGBURST_SNGL | DMA_CFG_CHPRIORITY(0);
	LPC_DMA->DMACH[DMA_CH7].CFG = DMA_CFG_PERIPHREQEN | DMA_CFG_TRIGBURST_SNGL | DMA_CFG_CHPRIORITY(1);
  /* Enable DMA interrupt */
	
	NVIC_EnableIRQ(DMA_IRQn);
}

volatile uint8_t DMARXDUMMY[4] = {0, };
volatile uint8_t DMATXDUMMY[4] = {0xFF, };
DMA_CHDESC_T *pDesc;
//static void DMA_Configuration(struct lpc54110_spi_bus * lpc_spi_bus, const void * send_addr, void * recv_addr, rt_size_t size)
static void DMA_Configuration(uint8_t * send_addr, uint8_t * recv_addr, rt_size_t size)
{
	uint32_t retry;
	pDesc = (DMA_CHDESC_T *) LPC_DMA->SRAMBASE;
	/* DMA descriptor for memory to memory operation - note that addresses must
	   be the END address for src and destination, not the starting address.
	     DMA operations moves from end to start. */
	Chip_SPI_ClearStatus(LPC_SPI1, SPI_STAT_RXOV | SPI_STAT_TXUR | SPI_STAT_SSA | SPI_STAT_SSD);
	// DMA Channle 6 RX
	if(recv_addr != NULL) {
		spi1_rx_dmaDesc.source    = DMA_ADDR(&LPC_SPI1->FIFORD);
		spi1_rx_dmaDesc.dest      = DMA_ADDR(&recv_addr[size-1]);
		spi1_rx_dmaDesc.next      = DMA_ADDR(0);
		spi1_rx_dmaDesc.xfercfg   = DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SETINTA |
																DMA_XFERCFG_SWTRIG | DMA_XFERCFG_WIDTH_8 | DMA_XFERCFG_SRCINC_0 |
																DMA_XFERCFG_DSTINC_1 | DMA_XFERCFG_XFERCOUNT(size);
	} else {
		spi1_rx_dmaDesc.source    = DMA_ADDR(&LPC_SPI1->FIFORD);
		spi1_rx_dmaDesc.dest      = DMA_ADDR(&DMARXDUMMY[0]);
		spi1_rx_dmaDesc.next      = DMA_ADDR(0);
		spi1_rx_dmaDesc.xfercfg   = DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SETINTA |
																DMA_XFERCFG_SWTRIG | DMA_XFERCFG_WIDTH_8 | DMA_XFERCFG_SRCINC_0 |
																DMA_XFERCFG_DSTINC_0 | DMA_XFERCFG_XFERCOUNT(size);	
	}
	/* DMA descriptor for memory to memory operation - note that addresses must
	   be the END address for src and destination, not the starting address.
	     DMA operations moves from end to start. */
	if(send_addr != NULL) {
		spi1_tx_dmaDesc.source    = DMA_ADDR(&send_addr[size-1]);
		spi1_tx_dmaDesc.dest      = DMA_ADDR(&LPC_SPI1->FIFOWR);
		spi1_tx_dmaDesc.next      = DMA_ADDR(0);
		spi1_tx_dmaDesc.xfercfg   = DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SETINTA |
																DMA_XFERCFG_SWTRIG | DMA_XFERCFG_WIDTH_8 | DMA_XFERCFG_SRCINC_1 |
																DMA_XFERCFG_DSTINC_0 | DMA_XFERCFG_XFERCOUNT(size);
	} else {
		spi1_tx_dmaDesc.source    = DMA_ADDR(&DMATXDUMMY[0]);
		spi1_tx_dmaDesc.dest      = DMA_ADDR(&LPC_SPI1->FIFOWR);
		spi1_tx_dmaDesc.next      = DMA_ADDR(0);
		spi1_tx_dmaDesc.xfercfg   = DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SETINTA |
																DMA_XFERCFG_SWTRIG | DMA_XFERCFG_WIDTH_8 | DMA_XFERCFG_SRCINC_0 |
																DMA_XFERCFG_DSTINC_0 | DMA_XFERCFG_XFERCOUNT(size);	
	}
	pDesc[DMA_CH6] = spi1_rx_dmaDesc;
	pDesc[DMA_CH7] = spi1_tx_dmaDesc;
	// wait until DMA channel is not active
	for (retry = 5432; retry !=0; retry--) {
		if (0 == (LPC_DMA->DMACOMMON[0].ACTIVE & (1UL<<DMA_CH6 | 1UL<<DMA_CH7)))
			break;
	}	
	
	if(recv_addr != NULL) {
		LPC_DMA->DMACH[DMA_CH6].XFERCFG = (DMA_XFERCFG_CFGVALID |  DMA_XFERCFG_SETINTA | DMA_XFERCFG_SWTRIG   |
																			 DMA_XFERCFG_WIDTH_8  | DMA_XFERCFG_SRCINC_0 | DMA_XFERCFG_DSTINC_1 |
																			 DMA_XFERCFG_XFERCOUNT(size));
	} else {
		LPC_DMA->DMACH[DMA_CH6].XFERCFG = (DMA_XFERCFG_CFGVALID |  DMA_XFERCFG_SETINTA | DMA_XFERCFG_SWTRIG   |
																			 DMA_XFERCFG_WIDTH_8  | DMA_XFERCFG_SRCINC_0 | DMA_XFERCFG_DSTINC_0 |
																			 DMA_XFERCFG_XFERCOUNT(size));	
	}
	if(send_addr != NULL) {
		LPC_DMA->DMACH[DMA_CH7].XFERCFG = (DMA_XFERCFG_CFGVALID |  DMA_XFERCFG_SETINTA | DMA_XFERCFG_SWTRIG   |
																			 DMA_XFERCFG_WIDTH_8  | DMA_XFERCFG_SRCINC_1 | DMA_XFERCFG_DSTINC_0 |
																			 DMA_XFERCFG_XFERCOUNT(size));
	} else {
		LPC_DMA->DMACH[DMA_CH7].XFERCFG = (DMA_XFERCFG_CFGVALID |  DMA_XFERCFG_SETINTA | DMA_XFERCFG_SWTRIG   |
																			 DMA_XFERCFG_WIDTH_8  | DMA_XFERCFG_SRCINC_0 | DMA_XFERCFG_DSTINC_0 |
																			 DMA_XFERCFG_XFERCOUNT(size));	
	}					 
}
#endif

volatile LPC_SPI_T * g_SPI1;
volatile uint8_t spi1_config_flag = 0;
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
		int ret;
		SPI_CFGSETUP_T spiSetup;
		SPIM_DELAY_CONFIG_T masterDelay;
	
    struct lpc54110_spi_bus * lpc_spi_bus = (struct lpc54110_spi_bus *)device->bus;

		g_SPI1 = LPC_SPI1;
	if(spi1_config_flag == 0) {
		spi1_config_flag = 1;
		/* Connect the SPI1 signals to port pins */
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 11, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN));	/* SPI1_SCK */
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 12, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN));	/* SPI1_MOSI */
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 13, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN));	/* SPI1_MISO */
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 14, (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN));	/* SPI1_SSEL0 */	
	
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 14);
		Chip_GPIO_SetPinState(LPC_GPIO, 0, 14, 1UL);

    /* data_width */
    if(configuration->data_width <= 8) {
			Chip_SPI_SetXferSize(LPC_SPI1, 8);
    }
    else if(configuration->data_width <= 16) {
			Chip_SPI_SetXferSize(LPC_SPI1, 16);
    }
    else {
			return RT_EIO;
    }
    /* CPOL & CPHA */
    if( ((configuration->mode & RT_SPI_CPOL) == RT_SPI_CPOL) && ((configuration->mode & RT_SPI_CPHA) == RT_SPI_CPHA) ) {
			  spiSetup.mode = SPI_CLOCK_MODE3;
    }
		else if( ((configuration->mode & RT_SPI_CPOL) == 0) && ((configuration->mode & RT_SPI_CPHA) == RT_SPI_CPHA) ) {
        spiSetup.mode = SPI_CLOCK_MODE2;
    }
		else if( ((configuration->mode & RT_SPI_CPOL) == RT_SPI_CPOL) && ((configuration->mode & RT_SPI_CPHA) == 0) ) {
        spiSetup.mode = SPI_CLOCK_MODE1;
    }
		else {
				spiSetup.mode = SPI_CLOCK_MODE0;
		}

    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB) {
				spiSetup.lsbFirst = 0;
    }
    else {
				spiSetup.lsbFirst = 1;
    }
		spiSetup.master = 1;
		
		Chip_SPI_ConfigureSPI(LPC_SPI1, &spiSetup);
		Chip_SPI_SetCSPolLow(LPC_SPI1, 0);

		/* Setup master delay (all chip selects) */
		masterDelay.PreDelay      = 0x1;
		masterDelay.PostDelay     = 0x1;
		masterDelay.FrameDelay    = 0x1;
		masterDelay.TransferDelay = 0x1;
		Chip_SPIM_DelayConfig(LPC_SPI1, &masterDelay);
		//LPC_SPI1->FIFOTRIG = (0<<16)|(1 << 1);
		Chip_SPI_SetFIFOTrigLevel(LPC_SPI1, 0, 0);
		
		
//		uart->UART->FIFOINTENSET |= (1<<3);
#ifdef SPI_USE_DMA
		LPC_SPI1->FIFOCFG = ((1 << 4) | SPI_FIFOCFG_ENABLETX | SPI_FIFOCFG_ENABLERX | SPI_FIFOCFG_DMATX | SPI_FIFOCFG_DMARX | SPI_FIFOCFG_WAKETX | SPI_FIFOCFG_WAKERX );
		Chip_SPI_DisableInts(LPC_SPI1, SPI_INT_TXDYEN | SPI_INT_RXDYEN);
		DMA_Init();
#endif

	}
    /* baudrate */
		ret = Chip_SPIM_SetClockRate(LPC_SPI1, configuration->max_hz);
		rt_kprintf("----------spi clock %d ----------\r\n", ret);

		/* For the SPI controller configured in master mode, enable SPI master interrupts
			 for interrupt service. Do not enable SPI_INTENSET_TXDYEN. */
//		Chip_SPI_EnableInts(LPC_SPI1, (SPI_INT_SSAEN | SPI_INT_SSDEN));
    return RT_EOK;
};

rt_uint8_t * xfer_send_ptr;
rt_uint8_t * xfer_recv_ptr;

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct lpc54110_spi_bus * lpc_spi_bus = (struct lpc54110_spi_bus *)device->bus;
    struct rt_spi_configuration * config = &device->config;
		uint32_t xfer_tmp;
		rt_err_t err;
	
	  LPC_SPI_T * SPI = lpc_spi_bus->SPI;
    struct lpc54110_spi_cs * lpc_spi_cs = device->parent.user_data;
    rt_uint32_t size = message->length;
		//rt_kprintf("send data %x %x %x %x    %d\r\n", send_addr[0], send_addr[1], send_addr[2], send_addr[3], size);
    /* take CS */
    if(message->cs_take)
    {
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 14, 0UL);
    }

#ifdef SPI_USE_DMA
    if(message->length > 32)
    {
        if(config->data_width <= 8)
        {
					LPC_SPI1->FIFOCFG = ((1 << 4) | SPI_FIFOCFG_ENABLETX | SPI_FIFOCFG_ENABLERX | SPI_FIFOCFG_DMATX | SPI_FIFOCFG_DMARX | SPI_FIFOCFG_WAKETX | SPI_FIFOCFG_WAKERX );
					DMA_Configuration((uint8_t *)message->send_buf, message->recv_buf, message->length);
        }
				err = rt_sem_take(&spi1_tx_done_sem, RT_WAITING_FOREVER);
//				rt_kprintf("rt_sem_take OK %x\r\n", err);
    }
    else
#endif
    {
        if(config->data_width <= 8) {
					LPC_SPI1->FIFOCFG = ((1 << 4) | SPI_FIFOCFG_ENABLETX | SPI_FIFOCFG_ENABLERX );
            xfer_send_ptr = (rt_uint8_t *)message->send_buf;
            xfer_recv_ptr = message->recv_buf;
						
            while(size--) {
                rt_uint8_t data = 0xFF;

                if(xfer_send_ptr != RT_NULL) {
                    data = *xfer_send_ptr++;
                }
								//Wait until the transmit buffer is empty
								while ((SPI->FIFOSTAT & (0x00000010)) == 0) {
									//__WFI();
								}
                SPI->FIFOWR = (0x00010000 | data);
								while ((SPI->FIFOSTAT & (0x00000040)) == 0) {	// RXNOTEMPTY
									//__WFI();
								}
								data = SPI->FIFORD;

                if(xfer_recv_ptr != RT_NULL) {
                    *xfer_recv_ptr++ = data;
                }
            }
        }
        else if(config->data_width <= 16) {
            const rt_uint16_t * send_ptr = message->send_buf;
            rt_uint16_t * recv_ptr = message->recv_buf;

            while(size--) {
                rt_uint16_t data = 0xFF;

                if(send_ptr != RT_NULL) {
                    data = *send_ptr++;
                }

								//Wait until the transmit buffer is empty
								while ((SPI->FIFOSTAT & (0x00000010)) == 0) {
									__WFI();
								}
                SPI->FIFOWR = (0x00010000 | data);
								while ((SPI->FIFOSTAT & (0x00000040)) == 0) {	// RXNOTEMPTY
									__WFI();
								}
								data = SPI->FIFORD;

                if(recv_ptr != RT_NULL) {
                    *recv_ptr++ = data;
                }
            }
        }
    }

    /* release CS */
    if(message->cs_release) {
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 14, 1UL);
    }

    return message->length;
};

/** \brief init and register stm32 spi bus.
 *
 * \param SPI: STM32 SPI, e.g: SPI1,SPI2,SPI3.
 * \param stm32_spi: stm32 spi bus struct.
 * \param spi_bus_name: spi bus name, e.g: "spi1"
 * \return
 *
 */
rt_err_t lpc_spi_register(LPC_SPI_T * SPI,
                            struct lpc54110_spi_bus * lpc_spi,
                            const char * spi_bus_name)
{
		int ret;
//		Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_INPUTMUX);
//		Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_IOCON);
//		Chip_GPIO_Init(LPC_GPIO);
		
    if(SPI == LPC_SPI1)
    {
    	lpc_spi->SPI = LPC_SPI1;
#ifdef SPI_USE_DMA

#endif
			/* Initialize SPI controller */
			rt_kprintf("Init SPI %s %s\r\n", __FILE__, __LINE__);
			ret = Chip_SPI_Init(LPC_SPI1);
			LPC_ASSERT(!ret, __FILE__, __LINE__);
		
			Chip_SPI_Enable(LPC_SPI1);
    }
    else
    {
        return RT_ENOSYS;
    }

    return rt_spi_bus_register(&lpc_spi->parent, spi_bus_name, &lpc54110_spi_ops);
}

void rt_hw_spi_init(void)
{
	static struct lpc54110_spi_bus lpc_spi;
  static struct lpc54110_spi_cs  spi_cs;
	static struct rt_spi_device    spi_device;
	
	spi_cs.GPIOx     = LPC_GPIO;
	spi_cs.GPIO_Port = 0;
	spi_cs.GPIO_Pin  = 14;
	lpc_spi_register(LPC_SPI1, &lpc_spi, "spi1");
	rt_spi_bus_attach_device(&spi_device, "spi10", "spi1", (void*)&spi_cs);

}
