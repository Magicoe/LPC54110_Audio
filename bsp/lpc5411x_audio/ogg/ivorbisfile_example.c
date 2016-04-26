/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis 'TREMOR' CODEC SOURCE CODE.   *
 *                                                                  *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis 'TREMOR' SOURCE CODE IS (C) COPYRIGHT 1994-2002    *
 * BY THE Xiph.Org FOUNDATION http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: simple example decoder using vorbisidec

 ********************************************************************/

/* Takes a vorbis bitstream from stdin and writes raw stereo PCM to
   stdout using vorbisfile. Using vorbisfile is much simpler than
   dealing with libvorbis. */

#include "ivorbiscodec.h"
#include "ivorbisfile.h"

#include "codebook.h"
#include <inttypes.h>
#include <rtthread.h>
//#include "codec.h"
#include <dfs_posix.h>

//char* pcmout1; //[4096]; /* take 4k out of the data segment, not the stack */
//char pcmout2[4096]; /* take 4k out of the data segment, not the stack */

static rt_err_t flac_decoder_tx_done(rt_device_t dev, void *buffer)
{
	/* release memory block */
	return RT_EOK;
}

extern volatile uint8_t *wav_buf0;
extern volatile uint8_t *wav_buf1;
extern volatile uint8_t *play_temp_buffer;
//extern volatile uint8_t wav_buf[2][19000];
//extern volatile int8_t play_temp_buffer[19000];
extern volatile uint32_t wav_buf_cnt;
extern volatile uint32_t wav_play_index;
extern volatile uint32_t wav_read_index;
extern struct rt_semaphore wav_play_sem;
extern volatile uint32_t wav_play_flag;
extern volatile uint32_t wav_buf_size;

volatile char* ogg_ext_buffer;
volatile int   ogg_ext_total = 0;

volatile int ogg_current_section = 0;
volatile OggVorbis_File ogg_vf;
int ogg(char * path)
{
	
	int eof=0;
//	int current_section;
	int fd;//,i=0;
	long ret;
	/* audio device */
	rt_device_t snd_device;
	
	if (rt_sem_init(&wav_play_sem, "wav_play_sem", 2, RT_IPC_FLAG_FIFO) != RT_EOK)
		rt_kprintf("init wav_play_sem semaphore failed\n");
	
	rt_kprintf("Creat play sem and init ok \r\n");

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
	rt_memset(wav_buf0, 0xFF, 9000);
	rt_memset(wav_buf1, 0xFF, 9000);;
//	if(pcmout1 == NULL) {
//		pcmout1 = rt_malloc(4096);
//		if(pcmout1 == NULL) {
//			rt_kprintf("malloc pcmout1 failed\n");
//		}		
//	}
	if(ogg_ext_buffer == NULL) {
		ogg_ext_buffer = rt_malloc(OGG_EXT_BUFFERSIZE*4);
		if(ogg_ext_buffer == NULL) {
			rt_kprintf("malloc ogg_ext_buffer failed\n");
		}		
	}
	rt_kprintf("malloc wav_buf0&1 ogg_ext_buffer ok %x %x %x\n", wav_buf0, wav_buf1, ogg_ext_buffer);
	list_mem();
	
	wav_play_index = 0;
	wav_read_index = 0;
	wav_buf_cnt   = 0;
	wav_play_flag = 0;
	rt_sem_take(&wav_play_sem, 100);

	fd = open(path, 0, 0);

	if(ov_open(fd, &ogg_vf, NULL, 0) < 0) {
		rt_kprintf("Input does not appear to be an Ogg bitstream.\n");
		rt_sem_detach(&wav_play_sem);
		rt_free((void *)wav_buf0);
		rt_free((void *)wav_buf1);
//		rt_free((void *)pcmout1);
		rt_free((void *)ogg_ext_buffer);
		return -1;
	}
	rt_kprintf("Opened Ogg bitstream success.\n");

	  	/* open audio device */
	snd_device = rt_device_find("snd");
	
	if (snd_device != RT_NULL) {
		//设置回调函数,当DMA传输完毕时,会执行ogg_decoder_tx_done
		rt_device_set_tx_complete(snd_device, flac_decoder_tx_done);
		rt_device_open(snd_device, RT_DEVICE_OFLAG_WRONLY);
	}

  /* Throw the comments plus a few lines about the bitstream we're
     decoding */
	{
		vorbis_comment *pov_comment;
		char **ptr;
		vorbis_info *vi;

		pov_comment 	=(vorbis_comment *)ov_comment(&ogg_vf,-1);
    ptr= pov_comment->user_comments;

    vi=(vorbis_info *)ov_info(&ogg_vf,-1);
    while(*ptr){
      rt_kprintf("\n%s\n",*ptr);
      ++ptr;
    }
    rt_kprintf("\nBitstream is %d channel, %ldHz\n",  vi->channels,vi->rate);
    rt_kprintf("\nDecoded length: %ld samples\n",     (long)ov_pcm_total(&ogg_vf,-1));
    rt_kprintf("Encoded by: %s\n\n",                  pov_comment->vendor);

		#define CODEC_CMD_SAMPLERATE 2
		rt_device_control(snd_device, CODEC_CMD_SAMPLERATE, (void *)&vi->rate);
  }

  
	while(!eof) {
//		rt_kprintf("ov_read %d %d\r\n", sizeof(pcmout1), wav_read_index);
		if(wav_read_index == 0) {
			ret = ov_read(&ogg_vf, (void *)wav_buf0, 4096, &ogg_current_section); // sizeof(pcmout1),&current_section);
		}
		if(wav_read_index == 1) {
			ret = ov_read(&ogg_vf, (void *)wav_buf1, 4096, &ogg_current_section); // sizeof(pcmout1),&current_section);
		}
		rt_kprintf("ov_read ok\r\n");
		if (ret == 0) {
			/* EOF */
			eof=1;
		} else if (ret < 0) {
			/* error in the stream.  Not a problem, just reporting it incase we (the app) cares.  In this case, we don't. */
		} else {
			/* we don't bother dealing with sample rate changes, etc, but you'll have to*/
			//  fwrite(pcmout,1,ret,stdout);
//			rt_device_write(snd_device, 0, (int16_t *)pcmout1,  ret);
		}
		
		if(wav_play_flag == 0) wav_play_flag = 1;
		rt_kprintf("ogg play index %d size %d\r\n", wav_read_index, wav_buf_size);
		rt_sem_take(&wav_play_sem, RT_WAITING_FOREVER);
  }

  /* cleanup */
  ov_clear(&ogg_vf);
	rt_sem_detach(&wav_play_sem);
	
	rt_free((void *)wav_buf0);
	rt_free((void *)wav_buf1);
//	rt_free((void *)pcmout1);
	rt_free((void *)ogg_ext_buffer);
	list_mem();
	
	wav_play_flag = 0;
  rt_kprintf("OGG play Done.\n");
  return(0);
}

#include "finsh.h"
FINSH_FUNCTION_EXPORT(ogg, int ogg(char * path));

