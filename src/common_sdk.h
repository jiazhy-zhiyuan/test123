#ifndef __COMMON_SDK_ETHAH_20130625_H_
#define __COMMON_SDK_ETHAH_20130625_H_

#include <osa.h>
#include <osa_thr.h>
#include <osa_sem.h>

#include <alsa/asoundlib.h>

#include <ti_vdis_common_def.h>
#include <ti_vdec_common_def.h>
#include <ti_vsys.h>
#include <ti_vcap.h>
#include <ti_venc.h>
#include <ti_vdec.h>
#include <ti_vdis.h>
#include <ti_vdis_timings.h>
#include <ti_audio.h>

#include "mcfw/interfaces/link_api/system_tiler.h"
#include "mcfw/interfaces/common_def/ti_vsys_common_def.h"
#include "mcfw/src_linux/mcfw_api/ti_vsys_priv.h"
#include "mcfw/src_common/utils/inc/ringbuf.h"

#include "common.h"
#include "decode.h"
#include "encode.h"
#include "split.h"
#include "system.h"

extern SwMsLink_CreateParams		g_swms[];
extern SYSTEM_DEBUG_INFO		g_debug_info;
#endif
