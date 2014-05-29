#ifndef __LINK_DEF_ETAH_20130416_H_
#define __LINK_DEF_ETAH_20130416_H_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "decode.h"
#include "encode.h"
#include "split.h"
#include "system.h"

#include "../common_sdk.h"
#include "../common/system_def.h"

//SYSTEM_LINK_ID_NULL_0
//SYSTEM_VPSS_LINK_ID_NULL_0
//SYSTEM_VIDEO_LINK_ID_NULL_0

//SYSTEM_LINK_ID_INVALID
#define MULTICH_HD_DVR_USECASE_MAX_NUM_LINKS_7500    (64)


#define MAX_NUM_CAPTURE_DEVICES_7500     (4)
#define MAX_NUM_DECODE_CHANNELS_7500     (4)
#define MAX_NUM_CAPTURE_CHANNELS_7500    (4)

#define MAX_PRIMARY_WIDTH_7500           (1920)
#define MAX_PRIMARY_HEIGHT_7500          (1080)

#define MAX_SECONDARY_WIDTH_7500         (704)
#define MAX_SECONDARY_HEIGHT_7500        (480)


#define     NUM_BUFS_PER_CH_CAPTURE_7500              (12)
//4//
#define     NUM_BUFS_PER_CH_DEI_7500                  (4) //4        
#define     NUM_BUFS_PER_CH_DEC_7500                  (4)
#define     NUM_BUFS_PER_CH_SWMS_7500                 (12)
#define     NUM_BUFS_PER_CH_ENC_PRI_7500              (6)
#define     NUM_BUFS_PER_CH_ENC_SEC_7500              (6)
#define     NUM_BUFS_PER_CH_BITSOUT_7500              (50)
#define     NUM_BUFS_PER_CH_BITSOUT_SCD_7500          (2)
#define     NUM_BUFS_PER_CH_NSF_Q_RES_CAPTURE_7500    (4)
#define     NUM_BUFS_PER_CH_NSF_SCD_7500              (4)
#define     NUM_BUFS_PER_CH_NSF_MJPEG_7500            (2)

#define     ENC_LINK_SECONDARY_STREAM_POOL_ID_7500    (0)
#define     ENC_LINK_PRIMARY_STREAM_POOL_ID_7500      (1)

#define     BIT_BUF_LENGTH_LIMIT_FACTOR_HD_7500      (5)

#define     MAX_BUFFERING_QUEUE_LEN_PER_CH_7500           (6)

typedef struct MultiChHdDvr_Context_7500
{
	UInt32 ipcBitsOutDSPId;

	UInt32 grpxId[VDIS_DEV_MAX];


	UInt32 createdLinkCount;
	UInt32 createdLinks[MULTICH_HD_DVR_USECASE_MAX_NUM_LINKS_7500];

	UInt32					dup0Id;			// capture复制2份: 一个给编码，一个给拼接
	DupLink_CreateParams			dup0Prm;
	UInt32					dup1Id;			// capture复制2份: 一个给编码，一个给拼接
	DupLink_CreateParams			dup1Prm;

	UInt32					merge0Id;		
	MergeLink_CreateParams			merge0Prm;

	UInt32					merge1Id;		
	MergeLink_CreateParams			merge1Prm;

	UInt32					nsf0Id;
	NsfLink_CreateParams			nsf0Prm;
	
	UInt32					dei0Id;
	DeiLink_CreateParams		  	dei0Prm;
	UInt32					dei1Id;
	DeiLink_CreateParams			dei1Prm;

	UInt32					selectId;
	SelectLink_CreateParams 	  	selectPrm;

	//采集
	UInt32					captureId;
	CaptureLink_CreateParams		capturePrm;

	//显示
	UInt32					swMsId[2];
	AvsyncLink_LinkSynchConfigParams    	avsyncCfg;
	
	UInt32					displayId[2];
	DisplayLink_CreateParams		displayPrm[2];		// 4个显示设备
	UInt32					captureFps;

	UInt32			      	 	ipcFramesInDspId;
	UInt32			   		ipcFramesOutVpssId;
	UInt32                         		dspAlgId;
	IpcFramesOutLinkRTOS_CreateParams 	ipcFramesOutVpssPrm;
	IpcFramesInLinkRTOS_CreateParams  	ipcFramesInDspPrm;
	AlgLink_CreateParams		 	dspAlgPrm;

	//编码	
	UInt32					ipcOutVpssId;
	IpcLink_CreateParams			ipcOutVpssPrm;
	UInt32					ipcInVideoId;
	IpcLink_CreateParams			ipcInVideoPrm;
	UInt32					encId;
	EncLink_CreateParams			encPrm;
	UInt32					ipcBitsOutRTOSId;
	IpcBitsOutLinkRTOS_CreateParams		ipcBitsOutVideoPrm;
	UInt32					ipcBitsInHLOSId;
	IpcBitsInLinkHLOS_CreateParams		ipcBitsInHostPrm;

	//解码
	UInt32					decId;
	UInt32					ipcBitsInRTOSId;
	UInt32					ipcBitsOutHLOSId;
	UInt32					ipcOutVideoId;
	UInt32					ipcInVpssId;
	IpcBitsOutLinkHLOS_CreateParams		ipcBitsOutHostPrm;
	IpcBitsInLinkRTOS_CreateParams		ipcBitsInVideoPrm;
	DecLink_CreateParams			decPrm;
	IpcLink_CreateParams			ipcOutVideoPrm;
	IpcLink_CreateParams			ipcInVpssPrm;
	
	
	SwMsLink_LayoutPrm		  swmsLayoutPrm[VDIS_DEV_MAX];

}  MultiChHdDvr_Context_7500;

extern MultiChHdDvr_Context_7500			gHdDvrUsecaseContext_7500;
extern DEVICE_CAPABILITY			g_dev;
extern SystemVideo_Ivahd2ChMap_Tbl		systemVid_encDecIvaChMapTbl_7500;

Void multich_hddvr_set_capture_prm_7500(CaptureLink_CreateParams *capturePrm);
Void multich_register_created_link_7500(MultiChHdDvr_Context_7500 *pContext, UInt32 linkID);
Void multich_set_capture_prm_7500(CaptureLink_CreateParams *capturePrm);
Void multich_set_capture_fps_7500(UInt32 *captureFps);
Void multich_set_swms_prm_7500(UInt32 swMsId);
Void multich_set_display_prms_7500(DisplayLink_CreateParams *displayPrm, int displayId);
Void multich_set_enclink_prm_7500(EncLink_CreateParams *encPrm);
Void multich_set_dei_prm_7500(DeiLink_CreateParams *deiPrm, DeiLink_OutputScaleFactor *outScalerFactorDeiSc, DeiLink_OutputScaleFactor *outScalerFactorVipSc);
Void multich_set_nsf_prm_7500(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate);
Void multich_hddvr_set_nsf_prm_7500(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate);
Void multich_hddvr_connect_osd_links_7500();
Void multich_hddvr_connect_encode_links_7500();
Void multich_hddvr_connect_decode_links_7500();
Void multich_hddvr_connect_display_links_7500();
Void multich_hddvr_set_enclink_prm_7500(EncLink_CreateParams *encPrm);
Void multich_hddvr_set_ipcbitsout_hlos_prms_7500(IpcBitsOutLinkHLOS_CreateParams * ipcBitsOutHostPrm);
Void multich_hddvr_set_avsync_vidque_prm_7500(Avsync_SynchConfigParams *queCfg,Int chnum,UInt32 avsStartChNum,UInt32 avsEndChNum);
Void multich_hddvr_set_swms_default_layout_7500(SwMsLink_CreateParams *swMsPrm, UInt32 devId);

#define TILER_ENABLE_DECODE_7500      (TRUE)
#define TILER_ENABLE_ENCODE_7500      (TRUE)

#define MULTICH_HDDVR_CREATE_LINK_7500(linkID,createPrm)								\
do														\
{														\
	printf("====================" #linkID "(id:%d)(line:%d)====================\n", linkID, __LINE__);	\
	System_linkCreate(linkID,&createPrm,sizeof(createPrm));							\
	multich_hddvr_register_created_link_7500(&gHdDvrUsecaseContext_7500, linkID);     				\
} while (0)

#define ETAH_7500_USE_OSD
#endif

