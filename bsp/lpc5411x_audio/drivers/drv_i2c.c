#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#include "drv_i2c.h"
#include "chip.h"

/* GPIO define
SCL: I2C1_SCL PB6
SDA: I2C1_SDA PB7
*/
#define GPIO_PORT_I2C_SCL
#define I2C_SCL_PORT			0
#define I2C_SCL_PIN				25

#define GPIO_PORT_I2C_SDA
#define I2C_SDA_PORT			0
#define I2C_SDA_PIN				26

#define I2CM_STATUS_TIMEOUT   0x56
#define I2C0_FLEXCOMM   			4

#ifdef RT_USING_I2C_BITOPS

static struct rt_i2c_bus_device i2c_device;

static void gpio_set_sda(void *data, rt_int32_t state)
{
    if (state) {
        Chip_GPIO_SetPinState(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN, 1UL);
    }
    else {
			  Chip_GPIO_SetPinState(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN, 0UL);
    }
}

static void gpio_set_scl(void *data, rt_int32_t state)
{
    if (state) {
        Chip_GPIO_SetPinState(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN, 1UL);
    }
    else {
        Chip_GPIO_SetPinState(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN, 0UL);
    }
}

static rt_int32_t gpio_get_sda(void *data)
{
		rt_int32_t tmp;
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN);
		tmp = Chip_GPIO_ReadPortBit(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN);
		return tmp;
}

static rt_int32_t gpio_get_scl(void *data)
{
		rt_int32_t tmp;
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN);
		tmp = Chip_GPIO_ReadPortBit(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN);
		return tmp;
}

static void gpio_udelay(rt_uint32_t us)
{
    volatile rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 50;
        while(i--);
    }
}

static const struct rt_i2c_bit_ops bit_ops =
{
    RT_NULL,
    gpio_set_sda,
    gpio_set_scl,
    gpio_get_sda,
    gpio_get_scl,

    gpio_udelay,

    5,
    100
};

#else

#if 0
static rt_err_t lpc54110_i2c_configure(struct rt_i2c_bus_device * device,
                                    struct rt_i2c_configuration* configuration)
{
    return RT_EOK;
}

static rt_err_t lpc54110_i2c_start(struct rt_i2c_bus_device * device)
{
	
    return RT_EOK;
}

static rt_err_t lpc54110_i2c_stop(struct rt_i2c_bus_device * device)
{
	
    return RT_EOK;
}

static rt_size_t lpc54110_i2c_read(struct rt_i2c_bus_device * device,
                                struct rt_i2c_message * message,
                                rt_uint8_t * read_buffer,
                                rt_size_t size)
{
    uint16_t temp;

    return size;
}

static rt_size_t lpc54110_i2c_write(struct rt_i2c_bus_device * device,
                                 struct rt_i2c_message * message,
                                 const rt_uint8_t * write_buffer,
                                 rt_size_t size)
{


    return 0;
}
#endif

#if Magicoe
static rt_size_t lpc54110_i2c_recv_bytes(LPC_I2C_T* I2Cx, struct rt_i2c_msg *msg)
{
    rt_size_t bytes = 0;
    rt_size_t len = msg->len;

    while (len--)  {
//        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
//        msg->buf[bytes++] = (rt_uint8_t)I2Cx->DR;
    }

    return bytes;
}

static rt_size_t lpc54110_i2c_send_bytes(LPC_I2C_T* I2Cx, struct rt_i2c_msg *msg)
{
    rt_size_t bytes = 0;
    rt_size_t len = msg->len;

    while (len--)  {
//        I2Cx->DR = msg->buf[bytes++];
//        while(! I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    return bytes;
}

static void lpc54110_i2c_send_addr(LPC_I2C_T* I2Cx, struct rt_i2c_msg *msg) // I2C_SendAddress(LPC_I2C_T* I2Cx, struct rt_i2c_msg *msg)
{
    rt_uint16_t addr;
    rt_uint16_t flags = msg->flags;
    /* Check the parameters */
//    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Test on the direction to set/reset the read/write bit */
	  Chip_I2CM_ClearStatus(I2Cx, I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
    addr = msg->addr << 1;
    if (flags & RT_I2C_RD) {
        /* Set the address bit0 for read */
        addr |= 1;
    }
    /* Send the address */
		Chip_I2CM_WriteByte(I2Cx, addr);
		/* Enter to Master Transmitter mode */
		Chip_I2CM_SendStart(I2Cx);
}
#endif

#define I2C_BUFF_SZ					16
static uint8_t			        i2c_tx_buff[I2C_BUFF_SZ];
static uint8_t			        i2c_rx_buff[I2C_BUFF_SZ];
static I2CM_XFER_T          i2c_xfer;

static rt_size_t lpc54110_i2c_xfer(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_int32_t i, ret;
// Magicoe    rt_uint16_t ignore_nack;
		
	  if (msg->flags & RT_I2C_RD) {
			rt_kprintf("i2c rd  ");
			i2c_xfer.rxBuff = i2c_rx_buff;
			i2c_xfer.rxSz = num-1;
			i2c_xfer.txBuff = i2c_tx_buff;
			i2c_xfer.txSz = 1;

			i2c_xfer.slaveAddr = msg->addr;
//			for(i=0; i<(num-1); i++) {
//				i2c_tx_buff[i] = msg->buf[i] & 0xff;
//			}
			i2c_xfer.status = I2CM_STATUS_OK;
		}
		else {
			rt_kprintf("i2c wr  ");
			i2c_xfer.rxBuff = i2c_rx_buff;
			i2c_xfer.rxSz = 0;
			i2c_xfer.txBuff = i2c_tx_buff;
			i2c_xfer.txSz = num;

			i2c_xfer.slaveAddr = msg->addr;
			for(i=0; i<(num-1); i++) {
				i2c_tx_buff[i] = msg->buf[i] & 0xff;
			}
			i2c_xfer.status = I2CM_STATUS_OK;
		}
		
		Chip_I2CM_XferBlocking(LPC_I2C0, &i2c_xfer);
		
		if (i2c_xfer.status == I2CM_STATUS_OK) {
			rt_kprintf("------------i2c true----------------- %d\r\n", i2c_xfer.status);
			ret = true;
		} else {
//			i2c_error(false, in->status);
			rt_kprintf("------------i2c false----------------- %d\r\n", i2c_xfer.status);
			ret = false;
		}
		
		if (msg->flags & RT_I2C_RD) {
			rt_memcpy( msg->buf, i2c_rx_buff, num-1);
			rt_kprintf("i2c rd %x %x ", msg->buf[0], msg->buf[1]);
			ret = i2c_xfer.rxSz;
		}
    return ret;
}


static const struct rt_i2c_bus_device_ops i2c1_ops =
{
    lpc54110_i2c_xfer,
    RT_NULL,
    RT_NULL
};

static struct rt_i2c_bus_device lpc54110_i2c1;

#endif

void rt_hw_i2c_init(void)
{
    rt_kprintf("install i2c1 \r\n");
#ifdef RT_USING_I2C_BITOPS		
    Chip_IOCON_PinMuxSet(LPC_IOCON, I2C_SDA_PORT, I2C_SDA_PIN, IOCON_FUNC0 | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP);
    Chip_IOCON_PinMuxSet(LPC_IOCON, I2C_SCL_PORT, I2C_SCL_PIN, IOCON_FUNC0 | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP);
	
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN);
		Chip_GPIO_SetPinState(LPC_GPIO, I2C_SDA_PORT, I2C_SDA_PIN, 1UL);

		Chip_GPIO_SetPinDIROutput(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN);
		Chip_GPIO_SetPinState(LPC_GPIO, I2C_SCL_PORT, I2C_SCL_PIN, 1UL);
	

    rt_memset((void *)&i2c_device, 0, sizeof(struct rt_i2c_bus_device));
    i2c_device.priv = (void *)&bit_ops;
    rt_i2c_bit_add_bus(&i2c_device, "i2c1");

#else
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 25, IOCON_FUNC1 | IOCON_DIGITAL_EN | IOCON_FASTI2C_EN);
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 26, IOCON_FUNC1 | IOCON_DIGITAL_EN | IOCON_FASTI2C_EN);
		
		Chip_I2C_Init(LPC_I2C0);
		Chip_I2C_SetClockDiv(LPC_I2C0, 20);
		Chip_I2CM_SetBusSpeed(LPC_I2C0, 100000);
		Chip_I2CM_Enable(LPC_I2C0);
		
    rt_memset((void *)&lpc54110_i2c1, 0, sizeof(struct rt_i2c_bus_device));
    lpc54110_i2c1.ops = &i2c1_ops;

    rt_i2c_bus_device_register(&lpc54110_i2c1, "i2c1");

#endif
}
