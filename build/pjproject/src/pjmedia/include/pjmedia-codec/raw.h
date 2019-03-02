/* $Id: speex.h 3553 2011-05-05 06:14:19Z nanang $ */
/* 
 * Copyright (C) 2008-2011 Teluu Inc. (http://www.teluu.com)
 * Copyright (C) 2003-2008 Benny Prijono <benny@prijono.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */
#ifndef __PJMEDIA_CODEC_RAW_H__
#define __PJMEDIA_CODEC_RAW_H__

/**
 * @file raw.h
 * @brief raw codec header.
 */

#include <pjmedia-codec/types.h>
#include <pjmedia/silencedet.h>
#include <pjmedia/plc.h>

PJ_BEGIN_DECL

struct raw_data
{
    pj_pool_t       *pool;
    unsigned         frame_size;    /* Frame size, in bytes */
    unsigned         clock_rate;    /* Clock rate */
    pj_bool_t        plc_enabled;
    pjmedia_plc     *plc;

    pj_bool_t        vad_enabled;
    pjmedia_silence_det *vad;
    pj_timestamp     last_tx;

};


typedef int(* vt_pjmedia_raw_codec_parse_cb) 
	(pjmedia_codec *codec,
	 void* data,
     void *pkt,
     pj_size_t pkt_size,
     const pj_timestamp *ts,
     unsigned *frame_cnt,
     pjmedia_frame frames[]);


typedef pj_status_t(* vt_pjmedia_raw_codec_encode_cb) (
	 pjmedia_codec *codec, 
	 void* data,
	 const struct pjmedia_frame *input,
	 unsigned output_buf_len, 
	 struct pjmedia_frame *output);


typedef pj_status_t(* vt_pjmedia_raw_codec_decode_cb) (
	 pjmedia_codec *codec, 
	 void* data,
     const struct pjmedia_frame *input,
     unsigned output_buf_len, 
     struct pjmedia_frame *output);

typedef pj_status_t(* vt_pjmedia_raw_codec_recover_cb) (
	pjmedia_codec *codec,
	void* data,
    unsigned output_buf_len,
    struct pjmedia_frame *output);

typedef pj_status_t(* vt_pjmedia_raw_codec_default_att_cb) (
	const pjmedia_codec_info *id, 
    pjmedia_codec_param *attr);

typedef pj_status_t(* vt_pjmedia_raw_codec_open_cb) (
	pjmedia_codec *codec, 
	void* data,
    pjmedia_codec_param *attr);

typedef pj_status_t(* vt_pjmedia_raw_codec_close_cb) (
	pjmedia_codec *codec, 
	void* data);

typedef pj_status_t(* vt_pjmedia_raw_codec_modify_cb) (
	pjmedia_codec *codec, 
	void* data,
    pjmedia_codec_param *attr);


PJ_DECL(pj_status_t) pjmedia_codec_raw_init( pjmedia_endpt *endpt);


PJ_DECL(pj_status_t) pjmedia_codec_raw_init_default(pjmedia_endpt *endpt);


PJ_DECL(pj_status_t) pjmedia_codec_raw_set_param(unsigned clock_rate,
						   int quality,
						   int complexity);


PJ_DECL(pj_status_t) pjmedia_codec_raw_deinit(void);


PJ_DECL(pj_status_t)
vt_raw_codec_set_cb(
	void* codec,
	vt_pjmedia_raw_codec_open_cb open_cb,
	vt_pjmedia_raw_codec_close_cb close_cb,
	vt_pjmedia_raw_codec_modify_cb modify_cb,
	vt_pjmedia_raw_codec_parse_cb parse_cb,
	vt_pjmedia_raw_codec_encode_cb encode_cb,
	vt_pjmedia_raw_codec_decode_cb decode_cb,
	vt_pjmedia_raw_codec_recover_cb recover_cb,
    vt_pjmedia_raw_codec_default_att_cb default_attr_cb
	);

PJ_DECL(pj_status_t)
vt_raw_codec_clear_cb();


PJ_END_DECL

/**
 * @}
 */

#endif	/* __PJMEDIA_CODEC_RAW_H__ */

