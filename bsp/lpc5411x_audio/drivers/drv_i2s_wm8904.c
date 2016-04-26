#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "chip.h"
#include "board.h"
#include "drv_i2s_wm8904.h"

#define I2S6_FLEXCOMM  			6
#define I2S7_FLEXCOMM  			7

#define I2S_PORT_TX				LPC_I2S7
#define I2S_TX_ISR				I2S7_IRQHandler
#define I2S_TX_IRQNUM			I2S7_IRQn

#define I2S_PORT_RX				LPC_I2S6
#define I2S_RX_ISR				I2S6_IRQHandler
#define I2S_RX_IRQNUM			I2S6_IRQn

#define BUFF_CT					12000

static I2S_AUDIO_FORMAT_T audio_fmt_tx = {
	I2S_TX,					/*!< Data direction: tx or rx */
	NORMAL_MASTER,			/*!< Master / Slave configuration */
	I2S_CLASSIC,			/*!< I2S mode */
	false,					/*!< right channel data in low portion of FIFO */
	false,					/*!< left justify data in FIFO */
	false,					/*!<  data source is the D-Mic subsystem */
	false,					/*!<  SCK polarity */
	false,					/*!<  WS polarity */
	16*LPC54110_IIS_MUL,						/*!< Flexcomm function clock divider */
	2,						/*!< Channel Number - 1 is mono, 2 is stereo */
	16,						/*!< Word Width */
	32,						/*!< Frame Width */
	0,						/*!< Data position in the frame */
	5,						/*!< FIFO depth (fifo config) */
};

static I2S_AUDIO_FORMAT_T audio_fmt_rx = {
	I2S_RX,					/*!< Data direction: tx or rx */
	NORMAL_SLAVE,			/*!< Master / Slave configuration */
	I2S_CLASSIC,			/*!< I2S mode */
	false,					/*!< right channel data in low portion of FIFO */
	false,					/*!< left justify data in FIFO */
	false,					/*!<  data source is the D-Mic subsystem */
	false,					/*!<  SCK polarity */
	false,					/*!<  WS polarity */
	1,						/*!< Flexcomm function clock divider */
	2,						/*!< Channel Number - 1 is mono, 2 is stereo */
	16,						/*!< Word Width */
	32,						/*!< Frame Width */
	0,						/*!< Data position in the frame */
	5,						/*!< FIFO depth (fifo config) */
};

/* CODEC port define */

void vol(uint16_t v);
static void codec_send(rt_uint8_t cmd, rt_uint16_t s_data);

#define DATA_NODE_MAX 5
/* data node for Tx Mode */
struct codec_data_node
{
    rt_uint16_t *data_ptr;
    rt_size_t  data_size;
};

struct codec_device
{
    struct rt_device parent;
    struct codec_data_node data_list[DATA_NODE_MAX];
    rt_uint16_t read_index, put_index;

    struct rt_i2c_bus_device * i2c_device;
};
struct codec_device codec;

static volatile uint32_t tx_irq_ctr = 0;										//	debugging only: interrupt count
static volatile uint32_t rx_irq_ctr = 0;

extern const uint16_t snd_buff_arr[];											//	pointer to the send buffer array
extern const uint16_t snd_buff_ct;												//	number of entries in the array
extern const uint16_t snd_buff_sz;												//	size of the array (in bytes)

volatile uint8_t *wav_buf0;//[2][19000];
volatile uint8_t *wav_buf1;
volatile uint8_t *play_temp_buffer;
//volatile uint8_t *wav_buf[2][19000];
//volatile int8_t  play_temp_buffer[19000];
volatile uint32_t wav_buf_cnt;
volatile uint32_t wav_buf_size = 0;
volatile uint32_t wav_play_index = 0;
volatile uint32_t wav_read_index = 0;
volatile uint32_t wav_play_flag = 0;
struct rt_semaphore wav_play_sem;

volatile uint32_t I2S_TR_DUMMY = 0xFFFFFFFF;
void I2S_TX_ISR(void)															//	I2S transmit interrupt
{
	rt_interrupt_enter();
	
	while (Chip_I2S_GetFIFOStatus(I2S_PORT_TX) & I2S_FIFO_STAT_TXNOTFULL) {		//	if FIFO is not full
		
		if(wav_play_flag != 0) {
			if( wav_buf_cnt <= (wav_buf_size-4) ) {
				if(wav_play_index == 0) {
					I2S_TR_DUMMY = *(uint32_t *)&wav_buf0[wav_buf_cnt]; // *(uint32_t *)&wav_buf[wav_play_index][wav_buf_cnt];
				}
				if(wav_play_index == 1) {
					I2S_TR_DUMMY = *(uint32_t *)&wav_buf1[wav_buf_cnt]; // *(uint32_t *)&wav_buf[wav_play_index][wav_buf_cnt];
				}
				Chip_I2S_Send(I2S_PORT_TX, I2S_TR_DUMMY);
				wav_buf_cnt = wav_buf_cnt + 4;
			}
			else {
				if(wav_play_index == 0)  wav_play_index = 1;
				else 		                 wav_play_index = 0;
				wav_play_flag = 1;
				wav_buf_cnt = 0;
				//I2S_TR_DUMMY = *(uint32_t *)&wav_buf[wav_play_index][wav_buf_cnt];
				if(wav_play_index == 0) {
					I2S_TR_DUMMY = *(uint32_t *)&wav_buf0[wav_buf_cnt]; // *(uint32_t *)&wav_buf[wav_play_index][wav_buf_cnt];
				}
				if(wav_play_index == 1) {
					I2S_TR_DUMMY = *(uint32_t *)&wav_buf1[wav_buf_cnt]; // *(uint32_t *)&wav_buf[wav_play_index][wav_buf_cnt];
				}
				Chip_I2S_Send(I2S_PORT_TX, I2S_TR_DUMMY);
				wav_buf_cnt = 4;
			}
			if( wav_play_flag == 1) {
				wav_play_flag = 2;
				if(wav_read_index == 0) wav_read_index = 1;
				else wav_read_index = 0;
				rt_sem_release(&wav_play_sem);
			}
		}
		else {
			Chip_I2S_Send(I2S_PORT_TX, I2S_TR_DUMMY);
		}
	}
	
	Chip_I2S_ClrFIFOStatus(I2S_PORT_TX);										//	clear FIFO status
	
	rt_interrupt_leave();
}

//volatile uint32_t i2s_rx_buf[0x20];
//volatile uint32_t i2s_rx_cnt = 0;
void I2S_RX_ISR(void)															//	I2S receive interrupt
{
	uint32_t data = 0x00;
	
	rt_interrupt_enter();
	while (Chip_I2S_GetFIFOStatus(I2S_PORT_RX) & I2S_FIFO_STAT_RXNOTEMPTY) {
		data = Chip_I2S_Receive(I2S_PORT_RX);		
	}
	Chip_I2S_ClrFIFOStatus(I2S_PORT_RX);										//	clear FIFO status
	
	rt_interrupt_leave();
}


/*
I2S3S_WS    PA15
I2S3_CK     PB3
I2S3ext_SD  PB4
I2S3_SD     PB5
*/
static void codec_gpio_config(void) //GPIO_Configuration(void)
{
		rt_kprintf("codec_gpio_config\r\n");
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 5, IOCON_FUNC1 | IOCON_DIGITAL_EN);								//	Flexcomm 6 / SDA
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 6, IOCON_FUNC1 | IOCON_DIGITAL_EN);								//	Flexcomm 6 / WS
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 7, IOCON_FUNC1 | IOCON_DIGITAL_EN);								//	Flexcomm 6 / SCK

    Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 6, IOCON_FUNC2 | IOCON_DIGITAL_EN);								//	Flexcomm 7 / SCK
    Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 7, IOCON_FUNC2 | IOCON_DIGITAL_EN);								//	Flexcomm 7 / SDA
    Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 8, IOCON_FUNC2 | IOCON_DIGITAL_EN);								//	Flexcomm 7 / WS
}

static void codec_dma_config(rt_uint32_t addr, rt_size_t size)
{

}

static void code_i2s_config(rt_uint32_t audiofreq)
{
		rt_kprintf("i2s config\r\n");
    Chip_I2S_Init(I2S_PORT_TX, &audio_fmt_tx);									//	initialize I2S port
    Chip_Clock_SetFLEXCOMMClockSource(I2S7_FLEXCOMM, SYSCON_FLEXCOMMCLKSELSRC_PLL);
    Chip_I2S_Config(I2S_PORT_TX, &audio_fmt_tx);								//	configure I2S port

    Chip_I2S_FIFO_Config(I2S_PORT_TX, &audio_fmt_tx);							//	configure I2S FIFO
    Chip_I2S_FIFO_Control(I2S_PORT_TX, &audio_fmt_tx, I2S_FIFO_TXZ_ENABLE);		//	send zeros if no data is available
    Chip_I2S_FIFO_Control(I2S_PORT_TX, &audio_fmt_tx, I2S_FIFO_ENABLE);			//	enable FIFO
	
    Chip_I2S_Init(I2S_PORT_RX, &audio_fmt_rx);									//	initialize I2S port
    Chip_Clock_SetFLEXCOMMClockSource(I2S6_FLEXCOMM, SYSCON_FLEXCOMMCLKSELSRC_PLL);
    Chip_I2S_Config(I2S_PORT_RX, &audio_fmt_rx);								//	configure I2S port

    Chip_I2S_FIFO_Config(I2S_PORT_RX, &audio_fmt_rx);							//	configure I2S FIFO
    Chip_I2S_FIFO_Control(I2S_PORT_RX, &audio_fmt_rx, I2S_FIFO_ENABLE);			//	enable FIFO

	  Chip_I2S_FIFO_SetInterrupt(I2S_PORT_TX, I2S_FIFO_INT_TXERR | I2S_FIFO_INT_TXLVL);	//	enable tx interrupts
    Chip_I2S_FIFO_SetInterrupt(I2S_PORT_RX, I2S_FIFO_INT_RXERR | I2S_FIFO_INT_RXLVL);	//	enable rx interrupts
}

static void codec_send(rt_uint8_t cmd, rt_uint16_t s_data)
{
    struct rt_i2c_msg msg;
    rt_uint8_t send_buffer[3];

    RT_ASSERT(codec.i2c_device != RT_NULL);

		send_buffer[0] = (rt_uint8_t)(cmd);
    send_buffer[1] = (rt_uint8_t)(s_data>>8);
    send_buffer[2] = (rt_uint8_t)(s_data);

    msg.addr = 0x1A;
    msg.flags = RT_I2C_WR;
    msg.len = 3;
    msg.buf = send_buffer;

    rt_i2c_transfer(codec.i2c_device, &msg, 1);
}

volatile uint8_t      tx_buff[16];
volatile uint8_t      rx_buff[16];
static I2CM_XFER_T    i2c_xfer;

#define I2C0_FLEXCOMM   			4
static volatile uint32_t i2c_tick_ct = 0;
bool i2c_io(I2CM_XFER_T *in)
{
	bool ret_val;

	/* Execute I2C transfer */
	Chip_I2CM_XferBlocking(LPC_I2C0, in);
	if (in->status == I2CM_STATUS_OK) {
		ret_val = true;
	} else {
		rt_kprintf("i2c transfer failed\r\n");
		ret_val = false;
	}

	return ret_val;
}

static bool wm8904_reg_read(uint8_t reg, uint16_t* val)
{
	bool ret_val;

	i2c_xfer.rxBuff = rx_buff;
	i2c_xfer.rxSz = 2;
	i2c_xfer.txBuff = tx_buff;
	i2c_xfer.txSz = 1;

	i2c_xfer.slaveAddr = 0x1A;
	tx_buff[0] = reg;
	i2c_xfer.status = I2CM_STATUS_OK;

	i2c_io(&i2c_xfer);
	if (i2c_xfer.status == I2CM_STATUS_OK) {
		*val = rx_buff[0]<<8 | rx_buff[1];
 		ret_val = true;
	} else {
		*val = 0;
 		ret_val = false;
	}
	return ret_val;
}

#define WM8904_ANALOGUE_LEFT_INPUT_0			0x2C
#define WM8904_ANALOGUE_RIGHT_INPUT_0			0x2D
#define WM8904_ANALOGUE_LEFT_INPUT_1			0x2E
#define WM8904_ANALOGUE_RIGHT_INPUT_1			0x2F
#define WM8904_ANALOGUE_OUT1_LEFT				  0x39
#define WM8904_ANALOGUE_OUT1_RIGHT				0x3A
#define WM8904_ANALOGUE_OUT2_LEFT				  0x3B
#define WM8904_ANALOGUE_OUT2_RIGHT				0x3C
#define WM8904_ANALOGUE_OUT12_ZC				  0x3D

static uint32_t volume_reg, pga_reg;
static bool wm8904_reg_write(uint8_t reg, uint16_t val)
{
	if (reg == WM8904_ANALOGUE_OUT1_LEFT) {
		volume_reg = (volume_reg & 0xFFFF) | (val << 16);
	} else if (reg == WM8904_ANALOGUE_OUT1_RIGHT) {
		volume_reg = (volume_reg & ~0xFFFF) | val;
	} else if (reg == WM8904_ANALOGUE_LEFT_INPUT_0) {
		pga_reg = (pga_reg & 0xFFFF) | (val << 16);
	} else if (reg == WM8904_ANALOGUE_RIGHT_INPUT_0) {
		pga_reg = (pga_reg & ~0xFFFF) | val;
	}
	i2c_xfer.rxBuff = rx_buff;
	i2c_xfer.rxSz = 0;
	i2c_xfer.txBuff = tx_buff;
	i2c_xfer.txSz = 3;

	i2c_xfer.slaveAddr = 0x1A;
	tx_buff[0] = reg;
	tx_buff[1] = (val >> 8) & 0xff;
	tx_buff[2] = val & 0xff;
	i2c_xfer.status = I2CM_STATUS_OK;

	i2c_io(&i2c_xfer);
	
	return  (i2c_xfer.status == I2CM_STATUS_OK) ? true : false;
}

volatile uint32_t loop_ct;
volatile uint32_t delayx = 0x1FFFF;
static void wm8904_multi_reg_write(const REG_CONFIG_T* seq, uint32_t cnt)
{
	uint16_t rd_val;
	uint32_t i ;
	bool r_test;

	loop_ct = 0;
	for (i=0; i<cnt; i++) {														//	loop through all the values
		if (seq[i].reg == 0xFF) {												//	test for delay dummy-register
			rt_kprintf("I2C register:0x%02x read:%x\r\n", 0x70, rd_val);
			loop_ct = 0;																	//	clear loop count
			do {																					//	if it's a dummy
				loop_ct += 1;													//	count loop iterations
				rt_thread_delay(50);
				wm8904_reg_read(0x70, &rd_val);									//	read the register
				rt_kprintf("I2C register:0x%02x read:%x\r\n", 0x70, rd_val);
			} while (rd_val & 1);												//	while the value is a 1
			rt_kprintf("delay: %dms\r\n",loop_ct*50);									//	display timing
		}
		else
		{																//	otherwise
			r_test = r_test;
			r_test = wm8904_reg_write(seq[i].reg, seq[i].val);					//	write the register
			rt_kprintf("I2C register:0x%02x write:%x\r\n", seq[i].reg, seq[i].val);//(r_test == true) ? "pass":"fail");
			if (r_test == false) rt_kprintf("I2C register failed\r\n");											//	break if write fails
			if (r_test == false) break;											//	break if write fails
		}
	}
}


static rt_err_t codec_init(rt_device_t dev)
{
		rt_uint32_t i;
	  rt_kprintf("codec_init\r\n");


    return RT_EOK;
}

void vol(uint16_t v) // 0~99
{
	wm8904_hp_vol(v);
}

rt_err_t sample_rate(int sr)
{
		wm8904_setSampleRate(sr);
    return RT_EOK;
}

void codec_id(void)
{
	uint16_t chip_id;
	bool r_test;

	r_test = wm8904_reg_read(WM8904_SW_RESET_AND_ID, &chip_id);
	rt_kprintf("I2C ID register read: %s\r\n", (r_test == true) ? "pass":"fail");
	rt_kprintf("WM8904 chip id: %04x\r\n", chip_id);
}

/* Audio mute in codec hardware */
uint32_t codec_mute(uint32_t x)
{
	wm8904_hp_mute(x);
	return true;
}

uint32_t codec_pga_mute(uint32_t x)
{
	wm8904_pga_mute(x);
}

uint32_t codec_set_reg(uint32_t x, uint32_t y)
{
	wm8904_reg_write(x, y);					//	write back out
}

/* Exported functions */
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(vol, Set volume);
//FINSH_FUNCTION_EXPORT(eq1, Set EQ1(Cut-off, Gain, Mode));
//FINSH_FUNCTION_EXPORT(eq2, Set EQ2(Center, Gain, Bandwidth));
//FINSH_FUNCTION_EXPORT(eq3, Set EQ3(Center, Gain, Bandwidth));
//FINSH_FUNCTION_EXPORT(eq4, Set EQ4(Center, Gain, Bandwidth));
//FINSH_FUNCTION_EXPORT(eq5, Set EQ5(Cut-off, Gain));
//FINSH_FUNCTION_EXPORT(eq3d, Set 3D(Depth));

FINSH_FUNCTION_EXPORT(sample_rate, Set sample rate);
FINSH_FUNCTION_EXPORT(codec_id, Read Codec ID);
FINSH_FUNCTION_EXPORT(codec_mute, Mute Codec);
FINSH_FUNCTION_EXPORT(codec_pga_mute, Mute Codec PGA);
FINSH_FUNCTION_EXPORT(codec_set_reg, codec_set_reg);
#endif

static rt_err_t codec_open(rt_device_t dev, rt_uint16_t oflag)
{
	rt_kprintf("codec_open\r\n");
	NVIC_EnableIRQ(I2S_TX_IRQNUM);	//	enable tx interrupt
	Chip_I2S_Start(I2S_PORT_TX);		//	start tx I2S port
	NVIC_SetPriority(I2S_TX_IRQNUM, ((0x01 << 3) | 0x01));
	
//		NVIC_EnableIRQ(I2S_RX_IRQNUM);	//	enable rx interrupt
//		Chip_I2S_Start(I2S_PORT_RX);		//	start rx I2S port
//		NVIC_SetPriority(I2S_RX_IRQNUM, ((0x01 << 3) | 0x01));
	
    return RT_EOK;
}

static rt_err_t codec_close(rt_device_t dev)
{
//#if CODEC_MASTER_MODE
//    if (r06 & MS)
//    {
//        NVIC_DisableIRQ(AUDIO_I2S_DMA_IRQ);
//        DMA_Cmd(AUDIO_I2S_DMA_STREAM, DISABLE);
//        /* Clear DMA Stream Transfer Complete interrupt pending bit */
//        DMA_ClearITPendingBit(AUDIO_I2S_DMA_STREAM, AUDIO_I2S_DMA_IT_TC);

//        while ((CODEC_I2S_PORT->SR & SPI_I2S_FLAG_TXE) == 0);
//        while ((CODEC_I2S_PORT->SR & SPI_I2S_FLAG_BSY) != 0);
//        I2S_Cmd(CODEC_I2S_PORT, DISABLE);

//        r06 &= ~MS;
//        codec_send(r06);

//        /* remove all data node */
//        if (codec.parent.tx_complete != RT_NULL)
//        {
//            rt_base_t level = rt_hw_interrupt_disable();

//            while (codec.read_index != codec.put_index)
//            {
//                codec.parent.tx_complete(&codec.parent, codec.data_list[codec.read_index].data_ptr);
//                codec.read_index++;
//                if (codec.read_index >= DATA_NODE_MAX)
//                {
//                    codec.read_index = 0;
//                }
//            }

//            rt_hw_interrupt_enable(level);
//        }
//    }
//#endif
		rt_kprintf("codec_close\r\n");
		NVIC_DisableIRQ(I2S_TX_IRQNUM);	//	enable tx interrupt
		Chip_I2S_Stop(I2S_PORT_TX);		//	start tx I2S port

//		NVIC_DisableIRQ(I2S_RX_IRQNUM);	//	enable rx interrupt
//		Chip_I2S_Stop(I2S_PORT_RX);		//	start rx I2S port
    return RT_EOK;
}

static rt_err_t codec_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    rt_err_t result = RT_EOK;
		rt_kprintf("codec control ");
    switch (cmd)
    {
    case CODEC_CMD_RESET:
				rt_kprintf("CODEC_CMD_RESET \r\n");
        result = codec_init(dev);
        break;

    case CODEC_CMD_VOLUME:
				rt_kprintf("CODEC_CMD_VOLUME \r\n");
        vol(*((uint16_t*) args));
        break;

    case CODEC_CMD_SAMPLERATE:
			  rt_kprintf("CODEC_CMD_SAMPLERATE \r\n");
        result = sample_rate(*((int*) args));
        break;

    case CODEC_CMD_EQ:
			  rt_kprintf("CODEC_CMD_EQ \r\n");
//        eq((codec_eq_args_t) args);
        break;

    case CODEC_CMD_3D:
			  rt_kprintf("CODEC_CMD_3D \r\n");
//        eq3d(*((uint8_t*) args));
        break;

    default:
        result = RT_ERROR;
    }
    return result;
}

static rt_size_t codec_write(rt_device_t dev, rt_off_t pos,
                             const void* buffer, rt_size_t size)
{
    struct codec_device* device;
    struct codec_data_node* node;
    rt_uint32_t level;
    rt_uint16_t next_index;

    device = (struct codec_device*) dev;
    RT_ASSERT(device != RT_NULL);

    next_index = device->put_index + 1;
    if (next_index >= DATA_NODE_MAX)
        next_index = 0;

    /* check data_list full */
    if (next_index == device->read_index)
    {
        rt_set_errno(-RT_EFULL);
        return 0;
    }

    level = rt_hw_interrupt_disable();
    node = &device->data_list[device->put_index];
    device->put_index = next_index;

    /* set node attribute */
    node->data_ptr = (rt_uint16_t*) buffer;
    node->data_size = size >> 1; /* size is byte unit, convert to half word unit */

    next_index = device->read_index + 1;
    if (next_index >= DATA_NODE_MAX)
        next_index = 0;

    /* check data list whether is empty */
    if (next_index == device->put_index)
    {

    }
    rt_hw_interrupt_enable(level);

    return size;
}



/* Interface to manage individual codecs */
typedef struct _CodecInterface_t {
	uint16_t volumeMin;
	uint16_t volumeMax;
	uint16_t volumeRes;
	uint16_t volumeDef;
	ErrorCode_t (*Init)(void);
	ErrorCode_t (*suspend)(void);
	ErrorCode_t (*resume)(void);
	ErrorCode_t (*mute)(uint32_t enable);
	ErrorCode_t (*setVolume)(int16_t volume);
	ErrorCode_t (*setSampleRate)(uint32_t rate);
} CodecInterface_t;

extern const REG_CONFIG_T	wm8904_reset_arr[];
extern const uint32_t		wm8904_reset_ct;

void wm8904_reset(void)
{
	wm8904_multi_reg_write(wm8904_reset_arr, wm8904_reset_ct);
}

void wm8904_config(WM8904_CONFIG_T cfg)
{
	switch (cfg) {
	case CONFIG_ANALOG_BYPASS:
		wm8904_multi_reg_write(i2_abp_hp_arr, i2_abp_hp_ct);
		break;
	case CONFIG_DIGITAL_LOOPBACK:
		wm8904_multi_reg_write(i2_loop_arr, i2_loop_ct);
		break;
	case CONFIG_DIGITAL_IO:
		wm8904_multi_reg_write(i2_io_arr, i2_io_ct);
		break;
	case CONFIG_DAC_OUT:
		wm8904_multi_reg_write(dac_hp_arr, dac_hp_ct);
		break;
	}
}

#define DEF_SAMPLE_RATE         48000		/* default sample rate */
#define DEF_RES_BITS            16          /* 16-Bits per sample per channel */
#define DEF_NUM_CHANNELS        2           /* 2-Channel Stereo in/out */

void wm8904_hp_vol(uint8_t vol)
{
	uint16_t curr_val_l = volume_reg >> 16;
	uint16_t curr_val_r = volume_reg & 0xFFFF;

//	wm8904_reg_read(WM8904_ANALOGUE_OUT1_LEFT, &curr_val_l);					//	read left / right PGA mute & gain
//	wm8904_reg_read(WM8904_ANALOGUE_OUT1_RIGHT, &curr_val_r);

	vol &= WM8904_HPOUTL_VOL_MASK;												//	limit gain to bits [5..0]
	curr_val_l &= ~WM8904_HPOUTL_VOL_MASK;										//	clear out gain (keep mute state)
	curr_val_r &= ~WM8904_HPOUTR_VOL_MASK;
	curr_val_l |= vol;															//	load in the gain
	curr_val_r |= vol;

	wm8904_reg_write(WM8904_ANALOGUE_OUT1_LEFT, curr_val_l);					//	write back out
	wm8904_reg_write(WM8904_ANALOGUE_OUT1_RIGHT, curr_val_r);
	wm8904_reg_write(WM8904_ANALOGUE_OUT1_RIGHT, curr_val_r | (1 << 7));
}

//------------------------------------------------------------------------------
//	WM8904 headphone PGA mute
//------------------------------------------------------------------------------
void wm8904_hp_mute(bool mute)
{
	uint16_t curr_val_l = volume_reg >> 16;
	uint16_t curr_val_r = volume_reg & 0xFFFF;

	//wm8904_reg_read(WM8904_ANALOGUE_OUT1_LEFT, &curr_val_l);					//	read left / right PGA mute & gain
	//wm8904_reg_read(WM8904_ANALOGUE_OUT1_RIGHT, &curr_val_r);

	if (mute == true) {															//	if mute is true, then set it
		curr_val_l |= WM8904_HPOUTL_MUTE;
		curr_val_r |= WM8904_HPOUTR_MUTE;
	} else {																	//	if mute is false, then clear it
		curr_val_l &= ~WM8904_HPOUTL_MUTE;
		curr_val_r &= ~WM8904_HPOUTR_MUTE;
	}

	wm8904_reg_write(WM8904_ANALOGUE_OUT1_LEFT, curr_val_l);					//	write left / right PGA mute & gain
	wm8904_reg_write(WM8904_ANALOGUE_OUT1_RIGHT, curr_val_r);
	wm8904_reg_write(WM8904_ANALOGUE_OUT1_RIGHT, curr_val_r | (1 << 7));
}


void wm8904_pga_gain(uint8_t gain)
{
	uint16_t curr_val_l = pga_reg >> 16;
	uint16_t curr_val_r = pga_reg & 0xFFFF;

//	wm8904_reg_read(WM8904_ANALOGUE_LEFT_INPUT_0, &curr_val_l);					//	read left / right PGA mute & gain
//	wm8904_reg_read(WM8904_ANALOGUE_RIGHT_INPUT_0, &curr_val_r);

	gain &= WM8904_LIN_VOL_MASK;												//	limit gain to bits [5..0]
	curr_val_l &= ~WM8904_LIN_VOL_MASK;											//	clear out gain (keep mute state)
	curr_val_r &= ~WM8904_RIN_VOL_MASK;
	curr_val_l |= gain;															//	load in the gain
	curr_val_r |= gain;

	wm8904_reg_write(WM8904_ANALOGUE_LEFT_INPUT_0, curr_val_l);					//	write back out
	wm8904_reg_write(WM8904_ANALOGUE_RIGHT_INPUT_0, curr_val_r);
}

void wm8904_pga_mute(bool mute)
{
	uint16_t curr_val_l = pga_reg >> 16;
	uint16_t curr_val_r = pga_reg & 0xFFFF;

	wm8904_reg_read(WM8904_ANALOGUE_LEFT_INPUT_0, &curr_val_l);					//	read left / right PGA mute & gain
	wm8904_reg_read(WM8904_ANALOGUE_RIGHT_INPUT_0, &curr_val_r);

	if (mute == true) {															//	if mute is true, then set it
		curr_val_l |= WM8904_LINMUTE;
		curr_val_r |= WM8904_RINMUTE;
	} else {																	//	if mute is false, then clear it
		curr_val_l &= ~WM8904_LINMUTE;
		curr_val_r &= ~WM8904_RINMUTE;
	}

	wm8904_reg_write(WM8904_ANALOGUE_LEFT_INPUT_0, curr_val_l);					//	write left / right PGA mute & gain
	wm8904_reg_write(WM8904_ANALOGUE_RIGHT_INPUT_0, curr_val_r);
}

void wm8904_reg_dump(void)
{
	uint16_t rd_value;
	uint32_t i;

	for (i=0; i<dbg_reg_adr_ct; i++) {
		wm8904_reg_read(dbg_reg_adr[i], &rd_value);
		rt_kprintf("%s", ((i & 0x07)==0) ? "\r\n" : "\t");
		rt_kprintf("%02x:%04x", dbg_reg_adr[i], rd_value);
	}
}

ErrorCode_t wm8904_init(void)
{
	wm8904_reset();
	rt_kprintf("------------- wm8904_reset -------------------");
	wm8904_config(CONFIG_DIGITAL_IO);// Magicoe (CONFIG_DIGITAL_IO);
	rt_kprintf("------------- wm8904_config -------------------");
	WM8904_SetSampleRate(MCLK_FS_256X, DEF_SAMPLE_RATE, DEF_RES_BITS);
	rt_kprintf("------------- WM8904_SetSampleRate -------------------");
	wm8904_pga_gain(0x5);														//	max out input gain (for electret microphone)
	rt_kprintf("------------- wm8904_pga_gain -------------------");
	wm8904_hp_vol(0x0018);													//	normalize gain (0dB) for headphone output
	wm8904_reg_dump();															//	display WM8904 registers (just the good ones)

	return LPC_OK;
}

/* Initialize the codec clocks for given audio frequency */
int WM8904_SetSampleRate(WM8904_FS_RATIO_T ratio, uint32_t sample_rate, uint8_t res_bits)
{
	int ret = 1;
	uint32_t tmp;
	if (sample_rate != 44100 && sample_rate != 48000) {
		/* Not supported yet */
		return 0;
	}
	ret &= wm8904_reg_write(WM8904_CLOCK_RATES_2, 0x00);							//	Disable the SYSCLK
	ret &= wm8904_reg_write(WM8904_CLOCK_RATES_1, ((uint32_t) ratio << 10) | 5); /* Set Clock ratio */
	tmp = 3;
	if (res_bits < 32) {
		tmp = (res_bits - 16) / 4;
	}
	ret &= wm8904_reg_write(WM8904_AUDIO_INTERFACE_1, ((uint32_t) tmp << 2) | 2); /* Set the bit resolution */

	ret &= wm8904_reg_write(WM8904_CLOCK_RATES_2, 0x0E);							//	Enable the SYSCLK
	return ret;
}


ErrorCode_t wm8904_setSampleRate(uint32_t rate)
{
	if (WM8904_SetSampleRate(MCLK_FS_256X, rate, DEF_RES_BITS)) {
		rt_kprintf("WM8904_SetSampleRate ok %d Hz\r\n", rate);
		wm8904_reg_dump();															//	display WM8904 registers (just the good ones)
		return LPC_OK;
	}
	rt_kprintf("WM8904_SetSampleRate failed %d Hz\r\n", rate);
	
	return ERR_FAILED;
}


rt_err_t codec_hw_init(const char * i2c_bus_device_name)
{
    struct rt_i2c_bus_device * i2c_device;
		uint32_t ret;
	
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 21, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGITAL_EN));
		Chip_Clock_SetCLKOUTSource(SYSCON_CLKOUTSRC_MAINCLK, 1);
		 
		rt_kprintf("read file page\r\n");		
		ret = Chip_Clock_GetMainClockRate();
		rt_kprintf("MainClk %d  ", ret);
		ret = Chip_Clock_GetSystemClockRate();
		rt_kprintf("SysClk %d  \r\n", ret);
	
		rt_kprintf("codec_hw_init_begin\r\n");
    i2c_device = rt_i2c_bus_device_find(i2c_bus_device_name);
    if(i2c_device == RT_NULL)
    {
        rt_kprintf("i2c bus device %s not found!\r\n", i2c_bus_device_name);
        return -RT_ENOSYS;
    }
    codec.i2c_device = i2c_device;
				
		/* Stop auto trimming of the FRO from USB */
		//Chip_USB_TrimOff(0);
#if Magicoe
		LPC_SYSCON->FROCTRL = LPC_SYSCON->FROCTRL & ~(SYSCON_FROCTRL_MASK | SYSCON_FROCTRL_USBCLKADJ);		
		Chip_Clock_SetMainClockSource(SYSCON_MAINCLKSRC_FRO12MHZ);
		Chip_Clock_SetSystemPLLSource(SYSCON_PLLCLKSRC_FRO12MHZ);
		Chip_Clock_SetPLLFreq(&pll_setup_48KHz);
		//Chip_Clock_SetPLLFreq(&pllSetup);
		Chip_Clock_SetMainClockSource(SYSCON_MAINCLKSRC_PLLOUT);
		
		Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 17, (IOCON_FUNC4 | IOCON_MODE_INACT | IOCON_DIGITAL_EN));
		Chip_Clock_SetMCLKDirOutput();
		Chip_Clock_SetMCLKClockSource(SYSCON_MCLKSRC_PLL, 2);
		
		Chip_SYSCON_SetFLASHAccess(SYSCON_FLASH_3CYCLE);
#else
		Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 17, (IOCON_FUNC4 | IOCON_MODE_INACT | IOCON_DIGITAL_EN));
		Chip_Clock_SetMCLKDirOutput();
		Chip_Clock_SetMCLKClockSource(SYSCON_MCLKSRC_PLL, (1*LPC54110_IIS_MUL));
#endif

		rt_kprintf("read file page\r\n");		
		ret = Chip_Clock_GetMainClockRate();
		rt_kprintf("MainClk %d  ", ret);
		ret = Chip_Clock_GetSystemClockRate();
		rt_kprintf("SysClk %d  \r\n", ret);
// Initial I2C here maybe
		
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 5, IOCON_FUNC1 | IOCON_DIGITAL_EN);						//	Flexcomm 6 / SDA
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 6, IOCON_FUNC1 | IOCON_DIGITAL_EN);						//	Flexcomm 6 / WS
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 7, IOCON_FUNC1 | IOCON_DIGITAL_EN);						//	Flexcomm 6 / SCK

		Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 6, IOCON_FUNC2 | IOCON_DIGITAL_EN);						//	Flexcomm 7 / SCK
		Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 7, IOCON_FUNC2 | IOCON_DIGITAL_EN);						//	Flexcomm 7 / SDA
		Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 8, IOCON_FUNC2 | IOCON_DIGITAL_EN);						//	Flexcomm 7 / WS
		
		Chip_I2S_Init(I2S_PORT_TX, &audio_fmt_tx);																				//	initialize I2S port
		
		Chip_Clock_SetFLEXCOMMClockSource(I2S7_FLEXCOMM, SYSCON_FLEXCOMMCLKSELSRC_PLL);
		Chip_I2S_Config(I2S_PORT_TX, &audio_fmt_tx);																			//	configure I2S port

		Chip_I2S_FIFO_Config (I2S_PORT_TX, &audio_fmt_tx);																//	configure I2S FIFO
		Chip_I2S_FIFO_Control(I2S_PORT_TX, &audio_fmt_tx, I2S_FIFO_TXZ_ENABLE);						//	send zeros if no data is available
		Chip_I2S_FIFO_Control(I2S_PORT_TX, &audio_fmt_tx, I2S_FIFO_ENABLE);								//	enable FIFO	
		
//		Chip_I2S_Init(I2S_PORT_RX, &audio_fmt_rx);																				//	initialize I2S port
//		Chip_Clock_SetFLEXCOMMClockSource(I2S6_FLEXCOMM, SYSCON_FLEXCOMMCLKSELSRC_PLL);
//		Chip_I2S_Config(I2S_PORT_RX, &audio_fmt_rx);																			//	configure I2S port

//		Chip_I2S_FIFO_Config(I2S_PORT_RX, &audio_fmt_rx);																	//	configure I2S FIFO
//		Chip_I2S_FIFO_Control(I2S_PORT_RX, &audio_fmt_rx, I2S_FIFO_ENABLE);								//	enable FIFO
		
		Chip_I2S_FIFO_SetInterrupt(I2S_PORT_TX, I2S_FIFO_INT_TXERR | I2S_FIFO_INT_TXLVL);	//	enable tx interrupts
//		Chip_I2S_FIFO_SetInterrupt(I2S_PORT_RX, I2S_FIFO_INT_RXERR | I2S_FIFO_INT_RXLVL);	//	enable rx interrupts
		
		/* init codec */
		ret = wm8904_init();
		if (ret == LPC_OK) {
			//g_codec.cur_rate = DEF_SAMPLE_RATE;
			/* suspend codec after init to conserve power */
			//Codec_Suspend();
		}
	
    codec.parent.type = RT_Device_Class_Sound;
    codec.parent.rx_indicate = RT_NULL;
    codec.parent.tx_complete = RT_NULL;
    codec.parent.user_data   = RT_NULL;

    codec.parent.control = codec_control;
    codec.parent.init    = codec_init;
    codec.parent.open    = codec_open;
    codec.parent.close   = codec_close;
    codec.parent.read    = RT_NULL;
    codec.parent.write   = codec_write;

    /* set read_index and put index to 0 */
    codec.read_index = 0;
    codec.put_index = 0;
//		NVIC_EnableIRQ(I2S_TX_IRQNUM);	//	enable tx interrupt
//		Chip_I2S_Start(I2S_PORT_TX);		//	start tx I2S port

//		NVIC_EnableIRQ(I2S_RX_IRQNUM);	//	enable rx interrupt
//		Chip_I2S_Start(I2S_PORT_RX);		//	start rx I2S port
    /* register the device */
    return rt_device_register(&codec.parent, "snd", RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);
}

void codec_removed(void)
{
	rt_device_unregister(&codec.parent);
}