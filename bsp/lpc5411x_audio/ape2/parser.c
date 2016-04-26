/*

libdemac - A Monkey's Audio decoder

Copyright (C) Dave Chapman 2007

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA

*/
#define inline __inline
#include "parser.h"
#include <dfs_posix.h>


/* Helper functions */

static int __inline read_uint16(int  fd, uint16_t* x)
{
    unsigned char tmp[2];
    int n;

    n = read(fd,tmp,2);

    if (n != 2)
        return -1;

    *x = tmp[0] | (tmp[1] << 8);

    return 0;
}

static int __inline read_int16(int  fd, int16_t* x)
{
    return read_uint16(fd, (uint16_t*)x);
}

static int __inline read_uint32(int fd, uint32_t* x)
{
    unsigned char tmp[4];
    int n;

    n = read(fd,tmp,4);

    if (n != 4)
        return -1;

    *x = tmp[0] | (tmp[1] << 8) | (tmp[2] << 16) | (tmp[3] << 24);

    return 0;
}

int ape_parseheader(int  fd,  ape_ctx_t* ape_ctx)
{
    int i,n;

    /* TODO: Skip any leading junk such as id3v2 tags */
    ape_ctx->junklength = 0;

    lseek(fd,ape_ctx->junklength,SEEK_SET);

    n = read(fd,&ape_ctx->magic,4);
    if (n != 4) return -1;

    if (rt_memcmp(ape_ctx->magic,"MAC ",4)!=0)
    {
        return -1;
    }

    if (read_int16(fd,&ape_ctx->fileversion) < 0)
        return -1;

    if (ape_ctx->fileversion >= 3980)
    {
        if (read_int16(fd,&ape_ctx->padding1) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->descriptorlength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->headerlength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->seektablelength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->wavheaderlength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->audiodatalength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->audiodatalength_high) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->wavtaillength) < 0)
            return -1;
        if (read(fd,&ape_ctx->md5,16) != 16)
            return -1;

        /* Skip any unknown bytes at the end of the descriptor.  This is for future
           compatibility */
        if (ape_ctx->descriptorlength > 52)
           	lseek(fd,ape_ctx->descriptorlength - 52, SEEK_CUR);

        /* Read header data */
        if (read_uint16(fd,&ape_ctx->compressiontype) < 0)
            return -1;
        if (read_uint16(fd,&ape_ctx->formatflags) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->blocksperframe) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->finalframeblocks) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->totalframes) < 0)
            return -1;
        if (read_uint16(fd,&ape_ctx->bps) < 0)
            return -1;
        if (read_uint16(fd,&ape_ctx->channels) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->samplerate) < 0)
            return -1;
			
    } else {
        ape_ctx->descriptorlength = 0;
        ape_ctx->headerlength = 32;

        if (read_uint16(fd,&ape_ctx->compressiontype) < 0)
            return -1;
        if (read_uint16(fd,&ape_ctx->formatflags) < 0)
            return -1;
        if (read_uint16(fd,&ape_ctx->channels) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->samplerate) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->wavheaderlength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->wavtaillength) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->totalframes) < 0)
            return -1;
        if (read_uint32(fd,&ape_ctx->finalframeblocks) < 0)
            return -1;

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_HAS_PEAK_LEVEL)
        {
            lseek(fd, 4, SEEK_CUR);   /* Skip the peak level */
            ape_ctx->headerlength += 4;
        }

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_HAS_SEEK_ELEMENTS)
        {
            if (read_uint32(fd,&ape_ctx->seektablelength) < 0)
                return -1;
            ape_ctx->headerlength += 4;
            ape_ctx->seektablelength *= sizeof(int32_t);
        } else {
            ape_ctx->seektablelength = ape_ctx->totalframes * sizeof(int32_t);
        }

        if (ape_ctx->formatflags & MAC_FORMAT_FLAG_8_BIT)
            ape_ctx->bps = 8;
        else if (ape_ctx->formatflags & MAC_FORMAT_FLAG_24_BIT)
            ape_ctx->bps = 24;
        else
            ape_ctx->bps = 16;

        if (ape_ctx->fileversion >= 3950)
            ape_ctx->blocksperframe = 73728 * 4;
        else if ((ape_ctx->fileversion >= 3900) || (ape_ctx->fileversion >= 3800 && ape_ctx->compressiontype >= 4000))
            ape_ctx->blocksperframe = 73728;
        else
            ape_ctx->blocksperframe = 9216;

        /* Skip any stored wav header */
        if (!(ape_ctx->formatflags & MAC_FORMAT_FLAG_CREATE_WAV_HEADER))
        {
            lseek(fd, ape_ctx->wavheaderlength, SEEK_CUR);
        }
    }

    ape_ctx->totalsamples = ape_ctx->finalframeblocks;
    if (ape_ctx->totalframes > 1)
        ape_ctx->totalsamples += ape_ctx->blocksperframe * (ape_ctx->totalframes-1);

    if (ape_ctx->seektablelength > 0)
    {
        ape_ctx->seektable = (uint32_t *)rt_malloc(ape_ctx->seektablelength);
        if (ape_ctx->seektable == NULL)
            return -1;
        for (i=0; i < ape_ctx->seektablelength / sizeof(uint32_t); i++)
        {
            if (read_uint32(fd,&ape_ctx->seektable[i]) < 0)
            {
                 rt_free(ape_ctx->seektable);
                 return -1;
            }
        }
    }

    ape_ctx->firstframe = ape_ctx->junklength + ape_ctx->descriptorlength +
                           ape_ctx->headerlength + ape_ctx->seektablelength +
                           ape_ctx->wavheaderlength;

    return 0;
}


void ape_dumpinfo(ape_ctx_t* ape_ctx)
{
  int i;

    rt_kprintf("\n\rDescriptor Block:\n");
    rt_kprintf("magic                = \"%c%c%c%c\"\n",
            ape_ctx->magic[0],ape_ctx->magic[1],
            ape_ctx->magic[2],ape_ctx->magic[3]);
    rt_kprintf("fileversion          = %d\n",ape_ctx->fileversion);
    rt_kprintf("descriptorlength     = %d\n",ape_ctx->descriptorlength);
    rt_kprintf("headerlength         = %d\n",ape_ctx->headerlength);
    rt_kprintf("seektablelength      = %d\n",ape_ctx->seektablelength);
    rt_kprintf("wavheaderlength      = %d\n",ape_ctx->wavheaderlength);
    rt_kprintf("audiodatalength      = %d\n",ape_ctx->audiodatalength);
    rt_kprintf("audiodatalength_high = %d\n",ape_ctx->audiodatalength_high);
    rt_kprintf("wavtaillength        = %d\n",ape_ctx->wavtaillength);
    rt_kprintf("md5                  = ");
    for (i = 0; i < 16; i++)
        rt_kprintf("%02x",ape_ctx->md5[i]);
    rt_kprintf("\n");

    rt_kprintf("\nHeader Block:\n");

    rt_kprintf("compressiontype      = %d\n",ape_ctx->compressiontype);
    rt_kprintf("formatflags          = %d\n",ape_ctx->formatflags);
    rt_kprintf("blocksperframe       = %d\n",ape_ctx->blocksperframe);
    rt_kprintf("finalframeblocks     = %d\n",ape_ctx->finalframeblocks);
    rt_kprintf("totalframes          = %d\n",ape_ctx->totalframes);
    rt_kprintf("bps                  = %d\n",ape_ctx->bps);
    rt_kprintf("channels             = %d\n",ape_ctx->channels);
    rt_kprintf("samplerate           = %d\n",ape_ctx->samplerate);

//    rt_kprintf("\nSeektable\n\n");
//    if ((ape_ctx->seektablelength / sizeof(uint32_t)) != ape_ctx->totalframes)
//    {
//        rt_kprintf("No seektable\n");
//    }
//    else
//    {
//        for ( i = 0; i < ape_ctx->seektablelength / sizeof(uint32_t) ; i++)
//        {
//            if (i < ape_ctx->totalframes-1) {
//                rt_kprintf("%8d   %d (%d bytes)\n",i,ape_ctx->seektable[i],ape_ctx->seektable[i+1]-ape_ctx->seektable[i]);
//            } else {
//                rt_kprintf("%8d   %d\n",i,ape_ctx->seektable[i]);
//            }
//        }
//    }
    rt_kprintf("\nCalculated information:\n\n");
    rt_kprintf("junklength           = %d\n",ape_ctx->junklength);
    rt_kprintf("firstframe           = %d\n",ape_ctx->firstframe);
    rt_kprintf("totalsamples         = %d\n",ape_ctx->totalsamples);
}

