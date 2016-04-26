#include <rtthread.h>
#include <dfs_posix.h>
#include <mp3/pub/mp3dec.h>
#include <string.h>

#include "board.h"
#include "netbuffer.h"
//#include "codec_wm8978_i2c.h"

// Magicoe #define MP3_AUDIO_BUF_SZ    (5 * 1024)
#define MP3_AUDIO_BUF_SZ    (8 * 1024)
#ifndef MIN
#define MIN(x, y)			((x) < (y)? (x) : (y))
#endif

//rt_uint8_t mp3_fd_buffer[MP3_AUDIO_BUF_SZ];
rt_uint8_t *mp3_fd_buffer; //[MP3_AUDIO_BUF_SZ];
int current_sample_rate = 0;

struct mp3_decoder
{
    /* mp3 information */
    HMP3Decoder decoder;
    MP3FrameInfo frame_info;
    rt_uint32_t frames;

    /* mp3 file descriptor */
    rt_size_t (*fetch_data)(void* parameter, rt_uint8_t *buffer, rt_size_t length);
    void* fetch_parameter;

    /* mp3 read session */
    rt_uint8_t *read_buffer, *read_ptr;
    rt_int32_t  read_offset;
    rt_uint32_t bytes_left, bytes_left_before_decoding;

	  /* audio device */
	  rt_device_t snd_device;
};

static rt_err_t mp3_decoder_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block */
// Magicoe	sbuf_release(buffer);

	return RT_EOK;
}

void mp3_decoder_init(struct mp3_decoder* decoder)
{
    RT_ASSERT(decoder != RT_NULL);

	/* init read session */
	decoder->read_ptr = RT_NULL;
	decoder->bytes_left_before_decoding = decoder->bytes_left = 0;
	decoder->frames = 0;

	// decoder->read_buffer = rt_malloc(MP3_AUDIO_BUF_SZ);
	decoder->read_buffer = &mp3_fd_buffer[0];
	if (decoder->read_buffer == RT_NULL) return;

	decoder->decoder = MP3InitDecoder();

	/* open audio device */
	decoder->snd_device = rt_device_find("snd");
	if (decoder->snd_device != RT_NULL)
	{
		/* set tx complete call back function */
		rt_device_set_tx_complete(decoder->snd_device, mp3_decoder_tx_done);
		rt_device_open(decoder->snd_device, RT_DEVICE_OFLAG_WRONLY);
	}
}

void mp3_decoder_detach(struct mp3_decoder* decoder)
{
    RT_ASSERT(decoder != RT_NULL);

	/* close audio device */
	if (decoder->snd_device != RT_NULL)
		rt_device_close(decoder->snd_device);

	/* release mp3 decoder */
    MP3FreeDecoder(decoder->decoder);
}

struct mp3_decoder* mp3_decoder_create()
{
    struct mp3_decoder* decoder;

	/* allocate object */
    decoder = (struct mp3_decoder*) rt_malloc (sizeof(struct mp3_decoder));

    if (decoder != RT_NULL)
    {
        mp3_decoder_init(decoder);
    }

    return decoder;
}

void mp3_decoder_delete(struct mp3_decoder* decoder)
{
	RT_ASSERT(decoder != RT_NULL);

	/* de-init mp3 decoder object */
	mp3_decoder_detach(decoder);
	/* release this object */
	rt_free(decoder);
}

rt_uint32_t current_offset = 0;
static rt_int32_t mp3_decoder_fill_buffer(struct mp3_decoder* decoder)
{
	rt_size_t bytes_read;
	rt_size_t bytes_to_read;

	if (decoder->bytes_left > 0) {
		// better: move unused rest of buffer to the start
		rt_memmove(decoder->read_buffer, decoder->read_ptr, decoder->bytes_left);
	}

	bytes_to_read = (MP3_AUDIO_BUF_SZ - decoder->bytes_left) & ~(512 - 1);

	bytes_read = decoder->fetch_data(decoder->fetch_parameter,
		(rt_uint8_t *)(decoder->read_buffer + decoder->bytes_left),
        bytes_to_read);

	if (bytes_read != 0)
	{
		decoder->read_ptr = decoder->read_buffer;
		decoder->read_offset = 0;
		decoder->bytes_left = decoder->bytes_left + bytes_read;
		return 0;
	}
	else
	{
		rt_kprintf("can't read more data\n");
		return -1;
	}
}

// Magicoe
extern volatile uint8_t *wav_buf0;
extern volatile uint8_t *wav_buf1;
extern volatile uint8_t *play_temp_buffer;
//extern volatile uint8_t wav_buf[2][19000];
extern volatile uint32_t wav_buf_cnt;
extern volatile uint32_t wav_play_index;
extern volatile uint32_t wav_read_index;
extern struct rt_semaphore wav_play_sem;
extern volatile uint32_t wav_play_flag;
extern volatile uint32_t wav_buf_size;
volatile uint8_t mp3_decoder_flag = 0;
volatile int outputSamps;

int mp3_decoder_run(struct mp3_decoder* decoder)
{
	int err;
//	rt_uint16_t* buffer;
	rt_uint32_t  delta;

//	RT_ASSERT(decoder != RT_NULL);
	
	if ((decoder->read_ptr == RT_NULL) || decoder->bytes_left < 2*MAINBUF_SIZE)
	{
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}
	
	decoder->read_offset = MP3FindSyncWord(decoder->read_ptr, decoder->bytes_left);
	if (decoder->read_offset < 0)
	{
		/* discard this data */
		rt_kprintf("outof sync, byte left: %d\n", decoder->bytes_left);
		decoder->bytes_left = 0;
		return 0;
	}

	decoder->read_ptr += decoder->read_offset;
	delta = decoder->read_offset;
	decoder->bytes_left -= decoder->read_offset;
	
	if (decoder->bytes_left < 1024)
	{
		/* fill more data */
		if(mp3_decoder_fill_buffer(decoder) != 0)
			return -1;
	}

    /* get a decoder buffer */
	decoder->bytes_left_before_decoding = decoder->bytes_left;
	if(wav_read_index == 0) {
		err = MP3Decode(decoder->decoder, &decoder->read_ptr, (int*)&decoder->bytes_left, (short*)&wav_buf0[0], 0);
	}
	if(wav_read_index == 1) {
		err = MP3Decode(decoder->decoder, &decoder->read_ptr, (int*)&decoder->bytes_left, (short*)&wav_buf1[0], 0);
	}
	delta += (decoder->bytes_left_before_decoding - decoder->bytes_left);

	current_offset += delta;

	decoder->frames++;

	if (err != ERR_MP3_NONE) {
		switch (err) {
		case ERR_MP3_INDATA_UNDERFLOW:
			rt_kprintf("ERR_MP3_INDATA_UNDERFLOW\n");
			decoder->bytes_left = 0;
			if(mp3_decoder_fill_buffer(decoder) != 0) {
				/* release this memory block */
				rt_kprintf("mp3_decoder_fill_buffer != 0\r\n");
				return -1;
			}
			break;

		case ERR_MP3_MAINDATA_UNDERFLOW:
			/* do nothing - next call to decode will provide more mainData */
			rt_kprintf("ERR_MP3_MAINDATA_UNDERFLOW\n");
			break;

		default:
			rt_kprintf("unknown error: %d, left: %d\n", err, decoder->bytes_left);
		
			if (decoder->bytes_left > 0) {
				decoder->bytes_left --;
				decoder->read_ptr ++;
			}
			else {
				RT_ASSERT(0);
			}
			break;
		}
	}
	else {
		
		/* no error */
		if(mp3_decoder_flag == 0) {
		MP3GetLastFrameInfo(decoder->decoder, &decoder->frame_info);
        /* set sample rate */
		if (decoder->frame_info.samprate != current_sample_rate){
			current_sample_rate = decoder->frame_info.samprate;
			rt_kprintf("samprate %d\r\n", decoder->frame_info.samprate);
			rt_kprintf("bitrate  %d\r\n", decoder->frame_info.bitrate );
			rt_kprintf("nChans   %d\r\n", decoder->frame_info.nChans );
			rt_kprintf("version  %d\r\n", decoder->frame_info.version );
			rt_kprintf("bitsPerSample  %d\r\n", decoder->frame_info.bitsPerSample );
			rt_kprintf("outputSamps  %d\r\n", decoder->frame_info.outputSamps );
			#define CODEC_CMD_SAMPLERATE	2 // Magicoe
			rt_device_control(decoder->snd_device, CODEC_CMD_SAMPLERATE, &current_sample_rate);
		}

		/* write to sound device */
		outputSamps = decoder->frame_info.outputSamps;
		mp3_decoder_flag = 1;
		}
		if (outputSamps > 0){
			if (decoder->frame_info.nChans == 1){
				int i;
				for (i = outputSamps - 1; i >= 0; i--){
					if(wav_read_index == 0) {
						wav_buf0[i * 2]     = wav_buf0[i];
						wav_buf0[i * 2 + 1] = wav_buf0[i];
					}
					if(wav_read_index == 1) {
						wav_buf1[i * 2]     = wav_buf1[i];
						wav_buf1[i * 2 + 1] = wav_buf1[i];
					}
				}
				outputSamps *= 2;
			}
			wav_buf_size = outputSamps * sizeof(rt_uint16_t);
//			rt_kprintf("mp3 read index %d size %d\r\n", wav_read_index, wav_buf_size);
			if(wav_play_flag == 0) wav_play_flag = 1;
			rt_sem_take(&wav_play_sem, RT_WAITING_FOREVER);
//			rt_device_write(decoder->snd_device, 0, buffer, outputSamps * sizeof(rt_uint16_t));
		}
		else {
			rt_kprintf("no output\r\n");
			/* no output */
		}
	}

	return 0;
}

#include <finsh.h>
rt_size_t fd_fetch(void* parameter, rt_uint8_t *buffer, rt_size_t length)
{
	int fd = (int)parameter;
	int read_bytes;

	read_bytes = read(fd, (char*)buffer, length);
	if (read_bytes <= 0) return 0;

	return read_bytes;
}

void mp3(char* filename)
{
	int fd;
	struct mp3_decoder* decoder;
	
	if(wav_buf0 == NULL) {
		wav_buf0 = rt_malloc(9000);
		if(wav_buf0 == NULL) {
			rt_kprintf("malloc wav_buf0 failed\n");
		}
	}
	if(wav_buf1 == NULL) {
		wav_buf1 = rt_malloc(9000);
		if(wav_buf1 == NULL) {
			rt_kprintf("malloc wav_buf1 failed\n");
		}		
	}
	rt_kprintf("malloc wav_buf0&1 ok %x %x\n", wav_buf0, wav_buf1);
	
	if(mp3_fd_buffer == NULL) {
		mp3_fd_buffer = rt_malloc(MP3_AUDIO_BUF_SZ);
		if(mp3_fd_buffer == NULL) {
			rt_kprintf("malloc mp3_fd_buffer failed\n");
		}		
	}
	rt_kprintf("malloc mp3_fd_buffer OK %x\n", mp3_fd_buffer);
	
	if (rt_sem_init(&wav_play_sem, "wav_play_sem", 2, RT_IPC_FLAG_FIFO) != RT_EOK)
		rt_kprintf("init flac_sem semaphore failed\n");
	
	rt_kprintf("Creat play sem and init ok \r\n");
	list_mem();

	wav_play_index = 0;
	wav_read_index = 0;
	wav_buf_cnt   = 0;
	wav_play_flag = 0;
	rt_sem_take(&wav_play_sem, 100);
	
	fd = open(filename, O_RDONLY, 0);
	if (fd >= 0)
	{
		decoder = mp3_decoder_create();
		
		if (decoder != RT_NULL)
		{
			decoder->fetch_data = fd_fetch;
			decoder->fetch_parameter = (void*)fd;
			
			current_offset = 0;
			while (mp3_decoder_run(decoder) != -1);

			/* delete decoder object */
			mp3_decoder_delete(decoder);
		}
		
		rt_free(wav_buf0);
		rt_free(wav_buf1);
		rt_free(mp3_fd_buffer);
		list_mem();
		
		rt_kprintf("mp3 play end \r\n");
		close(fd);
	}
}
FINSH_FUNCTION_EXPORT(mp3, mp3 decode test);
