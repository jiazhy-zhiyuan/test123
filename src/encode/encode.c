#include "common.h"

#include "decode.h"
#include "encode.h"
#include "split.h"
#include "../common_sdk.h"
#include "../common/system_def.h"
#include "../link/link_def-6800A.h"
#include "../osd/osd.h"
#include "../osd/demo.h"

ENCODE_FORMAT	g_encode_format[MAX_ENCODE_CHN]		= {0 };
int		encode_channel_state[MAX_ENCODE_CHN]	= {0 };

static int __encode_get_channel(int  ichannel, STREAM_TYPE dwType)
{
#if 0
	int chId;

	if(STREAM_TYPE_PRIMARY == dwType) {
		return ichannel;						// 本地4路和导播返回: 0,1,2,3,4
	} else {
		if(ichannel < g_dev.vi_channel_num) {
			return -1;
		} else {
			return g_dev.vi_channel_num + g_dev.swms_encode_num;	// 导播次码流返回: 5
		}
	}
#else
	if(STREAM_TYPE_PRIMARY == dwType) {
		return ichannel;						// 本地4路和导播返回: 0,1,2,3,4
	} else {
		return g_dev.vi_channel_num + g_dev.swms_encode_num + ichannel;
	}
#endif
}

int __Encode2ChannelID(int encode_channel)				// 编码通道获取本地视频通道号
{
#if 0
	if(encode_channel < g_dev.vi_channel_num + g_dev.swms_encode_num)
		return encode_channel;
	else
		return g_dev.vi_channel_num;
#else
	return encode_channel % (g_dev.vi_channel_num + g_dev.swms_encode_num);
#endif
}

int __Encode2ChannelStream(int encode_channel)
{
	if(encode_channel < g_dev.vi_channel_num + g_dev.swms_encode_num)
		return STREAM_TYPE_PRIMARY;
	else
		return STREAM_TYPE_SECOND;
}

int EncodeInit(int ichannel, STREAM_TYPE dwType)
{
	return 0;
}

int EncodeUninit(int ichannel, STREAM_TYPE dwType)
{
	return 0;
}

int EncodeStart(int ichannel, STREAM_TYPE dwType)
{
	int chId = __encode_get_channel(ichannel, dwType);
	if(chId < 0)
		return -1;

	encode_channel_state[chId] = 1;
	printf("EncodeStart(), ichannel: %d, dwType: %d, chid: %d\n", ichannel, dwType, chId);
	return 0;
}

int EncodeStop(int ichannel, STREAM_TYPE dwType)
{
	int chId = __encode_get_channel(ichannel, dwType);
	if(chId < 0)
		return -1;

	encode_channel_state[chId] = 0;
	return 0;
}

int EncodeForceIFrame(int  ichannel, STREAM_TYPE dwType)
{
	int chId = __encode_get_channel(ichannel, dwType);
	if(chId < 0)
		return -1;

	return Venc_forceIDR(chId, 0);
}

extern char g_productID[];
// ENC_LINK_CMD_SET_xxx系列
int EncodeSetFormat(int ichannel, STREAM_TYPE dwType, ENCODE_FORMAT *pFormat)
{
	VENC_CHN_DYNAMIC_PARAM_S params;
	int chId = __encode_get_channel(ichannel, dwType);
	printf("\nEncodeSetFormat(), chId: %d, dwType: %d, ichannel: %d\n", chId, dwType, ichannel);

	if(chId < 0) {
		printf("warning, not support 1-4 local video second stream.\n");
		return -1;
	}

	// 码率控制模式
	if(pFormat->BitRateControl != g_encode_format[chId].BitRateControl) {
		//printf("chId: %d, set BitRateControl: %d\n", chId, pFormat->BitRateControl);
		memset(&params, 0, sizeof(params));
		params.rcAlg = pFormat->BitRateControl;
		Venc_setDynamicParam(chId, 0, &params, VENC_RCALG);
	}

	// GOP
	if(pFormat->GOP != g_encode_format[chId].GOP) {
		//printf("chId: %d, set GOP: %d\n", chId, pFormat->GOP);
		memset(&params, 0, sizeof(params));
		params.intraFrameInterval = pFormat->GOP;
		Venc_setDynamicParam(chId, 0, &params, VENC_IPRATIO);
	}

	// 编码帧率
	if(pFormat->FrameRate != g_encode_format[chId].FrameRate) {
		//printf("chId: %d, set FrameRate: %d\n", chId, pFormat->FrameRate);
		memset(&params, 0, sizeof(params));
		params.frameRate = pFormat->FrameRate;
		Venc_setDynamicParam(chId, 0, &params, VENC_FRAMERATE);
	}

	// 参考码流值
	if(pFormat->BitRate != g_encode_format[chId].BitRate) {
		//printf("chId: %d, set BitRate: %d\n", chId, pFormat->BitRate);
		memset(&params, 0, sizeof(params));
		params.targetBitRate = pFormat->BitRate * 1000;
		Venc_setDynamicParam(chId, 0, &params, VENC_BITRATE);
	}

	// 编码分辨率: 通道和link流程有关系。修改分辨率必须根据设备类型定制!
	if(pFormat->width != g_encode_format[chId].width || pFormat->height != g_encode_format[chId].height) {
		printf("\nchannel: %d, old resolution: %dx%d, new resolution: %dx%d\n"
			, ichannel
			, g_encode_format[chId].width
			, g_encode_format[chId].height
			, pFormat->width
			, pFormat->height
			);

        //没有低码流
		if(0 == strcmp(g_productID,  "ECT-7200")){
			if(ichannel < g_dev.vi_channel_num){
				switch(ichannel){
                case 0:
                    __changeDeiResolution(gVcapModuleContext.deiId[0], DEI_LINK_OUT_QUE_VIP_SC, 0, pFormat->width, pFormat->height);
                    break;
                case 1:
                    __changeDeiResolution(gVcapModuleContext.deiId[2], DEI_LINK_OUT_QUE_VIP_SC, 0, pFormat->width, pFormat->height);
                    break;
				}
			}
		}


        
		if(0 == strcmp(g_productID, "ESVR-6800A") || 0 == strcmp(g_productID, "ESVR-8800D") || 0 == strcmp(g_productID, "ESVR-8800DI")) {
            printf("product id right\n");
			if(ichannel >= g_dev.vi_channel_num) {
            //if(chId >= g_dev.vi_channel_num) {
				int linkId = gVcapModuleContext.deiId[DEIHQ_Q_RES];
				int queId  = (STREAM_TYPE_PRIMARY == dwType)? DEI_LINK_OUT_QUE_VIP_SC: DEI_LINK_OUT_QUE_DEI_SC;

				printf("set encode resolution for mosaic.\n");
				__changeDeiResolution(linkId, queId, 0, pFormat->width, pFormat->height);
			} else if (STREAM_TYPE_PRIMARY == dwType) {
				printf("set encode resolution for local video, channel: %d\n", ichannel);
				switch(ichannel) {
					case 0:
						__changeDeiResolution(gVcapModuleContext.deiId[DEIHQ_FULL_RES], DEI_LINK_OUT_QUE_VIP_SC, 0, pFormat->width, pFormat->height);
						break;
					case 1:
						__changeDeiResolution(gVcapModuleContext.deiId[DEIHQ_FULL_RES], DEI_LINK_OUT_QUE_VIP_SC, 1, pFormat->width, pFormat->height);
						break;
					case 2:
						__changeDeiResolution(gVcapModuleContext.deiId[DEI_FULL_RES],   DEI_LINK_OUT_QUE_VIP_SC, 0, pFormat->width, pFormat->height);
						break;
					case 3:
						__changeDeiResolution(gVcapModuleContext.deiId[DEI_FULL_RES],   DEI_LINK_OUT_QUE_VIP_SC, 1, pFormat->width, pFormat->height);
						break;
					default:
						break;
				}
			}else if(STREAM_TYPE_SECOND == dwType){
                printf("set encode resolution for local video, second channel: %d\n", ichannel);
				switch(ichannel) {
					case 0:
						__changeDeiResolution(gVcapModuleContext.deiId[DEIHQ_FULL_RES], DEI_LINK_OUT_QUE_DEI_SC, 0, pFormat->width, pFormat->height);
						break;
					case 1:
						__changeDeiResolution(gVcapModuleContext.deiId[DEIHQ_FULL_RES], DEI_LINK_OUT_QUE_DEI_SC, 1, pFormat->width, pFormat->height);
						break;
					case 2:
						__changeDeiResolution(gVcapModuleContext.deiId[DEI_FULL_RES],   DEI_LINK_OUT_QUE_DEI_SC, 0, pFormat->width, pFormat->height);
						break;
					case 3:
						__changeDeiResolution(gVcapModuleContext.deiId[DEI_FULL_RES],   DEI_LINK_OUT_QUE_DEI_SC, 1, pFormat->width, pFormat->height);
						break;
					default:
						break;
				}
            }
		}
	}

	printf("%s() finish success.\n", __func__);
	memcpy(g_encode_format + chId, pFormat, sizeof(ENCODE_FORMAT));
	return 0;
}

int __changeDeiResolution(int linkId, int queId, int chId, int width, int height)
{
	int retVal = -1;
	DeiLink_chDynamicSetOutRes deiOutRes;
	printf("change dei resolution, linkid: %d, queId: %d, chId: %d, width: %d, height: %d\n", linkId, queId, chId, width, height);
	//dpline();getchar();

	deiOutRes.queId = queId;
	deiOutRes.chId	= chId;
	retVal = System_linkControl(linkId, DEI_LINK_CMD_GET_OUTPUTRESOLUTION, &deiOutRes, sizeof(deiOutRes), TRUE);
	if(0 != retVal) {
		printf("warning: get dei resolution failed.\n");
		return retVal;
	}
	printf("DEI_LINK_CMD_GET_OUTPUTRESOLUTION succ\n");

	deiOutRes.width  = width;
	deiOutRes.height = height;
	retVal = System_linkControl(linkId, DEI_LINK_CMD_SET_OUTPUTRESOLUTION, &deiOutRes, sizeof(deiOutRes), TRUE);
	if(0 != retVal) {
		printf("warning: set dei resolution failed.\n");
		return retVal;
	}
	//dpline();getchar();
	printf("DEI_LINK_CMD_SET_OUTPUTRESOLUTION succ\n");

	return 0;
}

EncodeGetBuffer_Callback g_EncodeGetCallback;
int EncodeSetGetBufferCallback(EncodeGetBuffer_Callback getCallback)
{
	g_EncodeGetCallback = getCallback;
	return 0;
}

extern void __osd_set_buffer(int chId, int index, ENCODE_TITLE_PARAM *pParam);
extern void __osd_set_position(int chId, int index, ENCODE_TITLE_PARAM *pParam);
int EncodeSetTitle(int ichannel, STREAM_TYPE dwType, int index, ENCODE_TITLE_PARAM *pParam)
{
	if(OSD_ENCODE_CHANNELI_ID != ichannel || STREAM_TYPE_PRIMARY != dwType) {
		printf("EncodeSetTitle() failed, not support channel: %d, type: %d.\n", ichannel, dwType);
	}

	int chId = __encode_get_channel(ichannel, dwType);
    printf("chid : %d\n", chId);
	__osd_set_buffer(chId, index, pParam);
	__osd_set_position(chId, index, pParam);
	return 0;
}

int EncodeShowTime(int ichannel, STREAM_TYPE dwType, int bShowTime)
{

    if(0 == strcmp(g_productID, "ECT-7200")){
        if(ichannel < 0 || ichannel > g_dev.vi_channel_num){
            printf("[LIBCAPTURE][%s] channel error!\n", __func__);
            return -1;            
        }
    }else{
        
        if(ichannel < 0 || ichannel > g_dev.vi_channel_num + g_dev.decode_channel_num){
            printf("[LIBCAPTURE][%s] channel error!\n", __func__);
            return -1;
        }
    }
    int chId = __encode_get_channel(ichannel, dwType);
    __EncodeShowTime(chId, bShowTime);
    return 0;
}




/* int EncodeSetProfile(int ichannel, STREAM_TYPE dwType, ETAH_VENC_CHN_H264_Profile_E profile) */
/* { */
/*     if(ichannel < 0 || ichannel > g_dev.vi_channel_num + g_dev.decode_channel_num){ */
/*         printf("[LIBCAPTURE][%s] channel error!\n", __func__); */
/*         return -1; */
/*     } */
/*     int chId = __encode_get_channel(ichannel, dwType); */
/*     printf("[LIBCAPTURE][%s] in", __func__); */
/*     printf ("[LIBCAPTURE][%s] chId : %d\n", __func__, chId); */
/*     VCODEC_TYPE_E codecType; */
/*     VENC_CHN_PARAMS_S		*pChPrm		= &gVencH264Context; */
/*     codecType == VCODEC_TYPE_H264; */
/*     Venc_switchCodecAlgCh2(pChPrm, codecType, profile, chId); */
/*     printf("[LIBCAPTURE][%s] out", __func__); */

/*     return 0; */
/* } */
