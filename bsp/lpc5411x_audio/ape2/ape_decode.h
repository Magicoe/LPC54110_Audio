/* ape - Command-line ape encoder/decoder
 * Copyright (C) 2000,2001,2002,2003,2004,2005,2006,2007  Josh Coalson
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef ape_decode_h
#define ape_decode_h

//#include "ape_ordinals.h"
#include "codec.h"
//#include "parser.h"



CHP_RTN_T ape_decoder_init(CHP_AUD_DEC_INFO_T *p_dec_info,
					       CHP_U32 *bl_handle);

CHP_RTN_T ape_decode(	CHP_U32 bl_handle,
					CHP_AUD_DEC_DATA_T *p_dec_data);

CHP_RTN_T ape_get_info(CHP_U32 bl_handle,
					CHP_AUD_DEC_INFO_T *p_dec_info);


CHP_RTN_T ape_decoder_close(CHP_U32 bl_handle);

//int ape_decode_one_frame(void* inaddr, void* outaddr, 
//			unsigned buf_length, unsigned *p_size, 
//			unsigned *dec_pcm_size);



#endif
