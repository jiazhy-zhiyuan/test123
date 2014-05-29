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
#define MULTICH_HD_DVR_USECASE_MAX_NUM_LINKS    (64)

#define DUP_FULL_RES_CAPTURE        (0)
#define DUP_Q_RES_CAPTURE           (1)
#define DUP_DISPLAY                 (2)
#define DUP_DISPLAY_TO_ENCODE       (3)
#define NUM_DUP_LINK                (4)

#define MERGE_Q_RES_CAPTURE         (0)
#define MERGE_DISPLAY               (1)
#define MERGE_ENCODE                (2)
#define NUM_MERGE_LINK              (3)

#define SELECT_FULL_RES_CAPTURE     (0)
#define SELECT_FOR_DISPLAY          (1)
#define NUM_SELECT_LINK             (2)

#define NSF_MJPEG                   (0)
#define NSF_MOSAIC_ENCODE	    (0)
#define NSF_Q_RES_CAPTURE           (1)
#define NSF_SCD                     (2)
#define NUM_NSF_LINK                (3)

#define DEIHQ_FULL_RES              (0)
#define DEIHQ_Q_RES                 (1)
#define DEI_FULL_RES                (2)
#define NUM_DEI_LINK                (3)

#define MAX_NUM_CAPTURE_DEVICES     (4)
#define MAX_NUM_DECODE_CHANNELS     (4)
#define MAX_NUM_CAPTURE_CHANNELS    (4)

#define MAX_PRIMARY_WIDTH           (1920)
#define MAX_PRIMARY_HEIGHT          (1080)

#define MAX_SECONDARY_WIDTH         (704)
#define MAX_SECONDARY_HEIGHT        (480)


#define     NUM_BUFS_PER_CH_CAPTURE              (12)
#define     NUM_BUFS_PER_CH_DEI                  (4)
#define     NUM_BUFS_PER_CH_DEC                  (4)
#define     NUM_BUFS_PER_CH_SWMS                 (12)
#define     NUM_BUFS_PER_CH_ENC_PRI              (6)
#define     NUM_BUFS_PER_CH_ENC_SEC              (6)
#define     NUM_BUFS_PER_CH_BITSOUT              (50)
#define     NUM_BUFS_PER_CH_BITSOUT_SCD          (2)
#define     NUM_BUFS_PER_CH_NSF_Q_RES_CAPTURE    (4)
#define     NUM_BUFS_PER_CH_NSF_SCD              (4)
#define     NUM_BUFS_PER_CH_NSF_MJPEG            (2)

#define     ENC_LINK_SECONDARY_STREAM_POOL_ID    (0)
#define     ENC_LINK_PRIMARY_STREAM_POOL_ID      (1)

#define     BIT_BUF_LENGTH_LIMIT_FACTOR_HD      (5)

#define     MAX_BUFFERING_QUEUE_LEN_PER_CH           (6)

typedef struct MultiChHdDvr_Context
{
	UInt32 ipcBitsOutDSPId;

	UInt32 mergeId[NUM_MERGE_LINK];
	UInt32 dupId[NUM_DUP_LINK];

	UInt32 grpxId[VDIS_DEV_MAX];

	UInt32 ipcOutVpssId;
	UInt32 ipcInVpssId;
	UInt32 ipcOutVideoId;
	UInt32 ipcInVideoId;

	UInt32 selectId[NUM_SELECT_LINK];

	UInt32 createdLinkCount;
	UInt32 createdLinks[MULTICH_HD_DVR_USECASE_MAX_NUM_LINKS];

	CaptureLink_CreateParams	  capturePrm;
	NsfLink_CreateParams		  nsfPrm[NUM_NSF_LINK];
	DeiLink_CreateParams		  deiPrm[NUM_DEI_LINK];
	SwMsLink_CreateParams		  swMsPrm[VDIS_DEV_MAX];
	AvsyncLink_LinkSynchConfigParams  avsyncCfg[2];
	DisplayLink_CreateParams	  displayPrm[VDIS_DEV_MAX];
	SclrLink_CreateParams             sclrPrm;
	UInt32                            sclrId[2];

	SelectLink_CreateParams 	  selectPrm[NUM_SELECT_LINK];
	MergeLink_CreateParams		  mergePrm[NUM_MERGE_LINK];
	DupLink_CreateParams		  dupPrm[NUM_DUP_LINK];

	IpcLink_CreateParams		  ipcOutVideoPrm;
	IpcLink_CreateParams		  ipcInVpssPrm;
	IpcLink_CreateParams		  ipcOutVpssPrm;
	IpcLink_CreateParams		  ipcInVideoPrm;
	IpcBitsOutLinkHLOS_CreateParams   ipcBitsOutHostPrm;
	IpcBitsInLinkRTOS_CreateParams	  ipcBitsInVideoPrm;
	IpcBitsOutLinkRTOS_CreateParams   ipcBitsOutVideoPrm;
	IpcBitsOutLinkRTOS_CreateParams   ipcBitsOutDspPrm;
	IpcBitsInLinkHLOS_CreateParams	  ipcBitsInHostPrm[2];
	IpcFramesOutLinkRTOS_CreateParams ipcFramesOutVpssPrm[2];
	IpcFramesInLinkRTOS_CreateParams  ipcFramesInDspPrm[2];

	EncLink_CreateParams		  encPrm;
	DecLink_CreateParams		  decPrm;

	AlgLink_CreateParams		  dspAlgPrm[2];

	VCAP_DEVICE_CREATE_PARAM_S	  vidDecVideoModeArgs[MAX_NUM_CAPTURE_DEVICES];

	SwMsLink_LayoutPrm		  swmsLayoutPrm[VDIS_DEV_MAX];

}  MultiChHdDvr_Context;

extern MultiChHdDvr_Context			gHdDvrUsecaseContext1;
extern DEVICE_CAPABILITY			g_dev;
extern SystemVideo_Ivahd2ChMap_Tbl		systemVid_encDecIvaChMapTbl;

Void multich_hddvr_set_capture_prm(CaptureLink_CreateParams *capturePrm);
Void multich_register_created_link(MultiChHdDvr_Context *pContext, UInt32 linkID);
Void multich_set_capture_prm(CaptureLink_CreateParams *capturePrm);
Void multich_set_capture_fps(UInt32 *captureFps);
Void multich_set_swms_prm(UInt32 swMsId);
Void multich_set_display_prms(DisplayLink_CreateParams *displayPrm, int displayId);
Void multich_set_enclink_prm(EncLink_CreateParams *encPrm);
Void multich_set_dei_prm(DeiLink_CreateParams *deiPrm, DeiLink_OutputScaleFactor *outScalerFactorDeiSc, DeiLink_OutputScaleFactor *outScalerFactorVipSc);
Void multich_set_nsf_prm(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate);
Void multich_hddvr_set_nsf_prm(NsfLink_CreateParams * nsfPrm, UInt32 numBufPerCh, UInt32 outputFrameRate);
Void multich_hddvr_connect_osd_links();
Void multich_hddvr_connect_encode_links();
Void multich_hddvr_connect_decode_links();
Void multich_hddvr_connect_display_links();
Void multich_hddvr_set_enclink_prm(EncLink_CreateParams *encPrm);
Void multich_hddvr_set_ipcbitsout_hlos_prms(IpcBitsOutLinkHLOS_CreateParams * ipcBitsOutHostPrm);
Void multich_hddvr_set_avsync_vidque_prm(Avsync_SynchConfigParams *queCfg,Int chnum,UInt32 avsStartChNum,UInt32 avsEndChNum);
Void multich_hddvr_set_swms_default_layout(SwMsLink_CreateParams *swMsPrm, UInt32 devId);
Void multich_hddvr_set_swms_prm2(SwMsLink_CreateParams *swMsPrm, UInt32 swMsIdx);

#define TILER_ENABLE_DECODE      (TRUE)
#define TILER_ENABLE_ENCODE      (TRUE)

#define MULTICH_HDDVR_CREATE_LINK(linkID,createPrm)								\
do														\
{														\
	printf("====================" #linkID "(id:%d)(line:%d)====================\n", linkID, __LINE__);	\
	System_linkCreate(linkID,&createPrm,sizeof(createPrm));							\
	multich_hddvr_register_created_link(&gHdDvrUsecaseContext1, linkID);     				\
} while (0)

#define ETAH_6800A_USE_OSD
#endif

