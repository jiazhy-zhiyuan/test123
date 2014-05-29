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

#define	MULTICH_MAX_USECASE_MAX_NUM_LINKS		(64)
#define	MULTICH_MAX_NUM_CAPTURE_DEVICES			(4)
#define MULTICH_NUM_CAPTURE_BUFFERS			(8)

#define MULTICH_NUM_SWMS_0_BUFFERS			(4)
#define MULTICH_NUM_SWMS_1_BUFFERS			(4)
#define MULTICH_NUM_SWMS_2_BUFFERS			(4)
#define MULTICH_NUM_SWMS_3_BUFFERS			(4)

typedef struct MultichDevice_Context
{
	UInt32					createdLinks[MULTICH_MAX_USECASE_MAX_NUM_LINKS];
	UInt32					createdLinkCount;

	VCAP_DEVICE_CREATE_PARAM_S		vidDecVideoModeArgs[MULTICH_MAX_NUM_CAPTURE_DEVICES];

	UInt32					captureId;
	CaptureLink_CreateParams		capturePrm;

	//CPU暂不支持
	//UInt32				deiId;
	//DeiLink_CreateParams			deiPrm[2];

	UInt32					dup0Id;			// capture复制2份: 一个给编码，一个给拼接
	DupLink_CreateParams			dup0Prm;

    UInt32 dup2Id;
    DupLink_CreateParams dup2Prm;
	UInt32					merge0Id;		// N路本地视频+最多2路拼接视频
	MergeLink_CreateParams			merge0Prm;

	// 拼接时钟源
	AvsyncLink_LinkSynchConfigParams avsyncCfg[2];

	// 2个编码后降噪，1个次码流缩放降噪
	UInt32					nsfId[3];
	NsfLink_CreateParams			nsfPrm[3];

	// 编码
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

	// 合并后dup4份拼接
	UInt32					merge1Id;		// N路本地视频+最多2路拼接视频
	MergeLink_CreateParams			merge1Prm;

	UInt32					dup1Id;			// XX
	DupLink_CreateParams			dup1Prm;
	UInt32					swMsId[4];

	UInt32					displayId[4];
	DisplayLink_CreateParams		displayPrm[4];		// 4个显示设备
	UInt32					captureFps;

	// 次码流，上面的nsfId[2]也用于次码流
	UInt32					dup3Id;
	DupLink_CreateParams			dup3Prm;
	UInt32					merge3Id;
	MergeLink_CreateParams			merge3Prm;
	UInt32					sclrId[MAX_SCLR_LINK];
	SclrLink_CreateParams			sclrPrm;

	// 解码
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

	// OSD
	UInt32					dspAlgId[MAX_ALG_LINK];
	UInt32					ipcFramesInDspId[MAX_IPC_FRAMES_LINK];
	UInt32					ipcFramesOutVpssId[MAX_IPC_FRAMES_LINK];
	IpcFramesInLinkRTOS_CreateParams	ipcFramesInDspPrm;
	IpcFramesOutLinkRTOS_CreateParams	ipcFramesOutVpssPrm;
	AlgLink_CreateParams			dspAlgPrm;
}  MultichDevice_Context;

#define MULTICH_CREATE_LINK(linkID,createPrm,createPrmSize)				\
do											\
{											\
	printf("====================%d====================\n", __LINE__);		\
	printf("before create link: ---" #linkID "---\n");				\
	System_linkCreate(linkID,createPrm,createPrmSize);				\
	printf("create link: ---" #linkID "--- finish\n");				\
	usleep(1000 * 1);								\
	multich_5300a_register_created_link(&gUsecaseContext, linkID);			\
} while (0)

extern MultichDevice_Context			gUsecaseContext;
extern DEVICE_CAPABILITY			g_dev;
extern SystemVideo_Ivahd2ChMap_Tbl		systemVid_encDecIvaChMapTbl;

#define MULTICH_GET_CAPTURE_FIELDS_PER_SEC()           (gUsecaseContext.captureFps)
#define MULTICH_GET_CAPTURE_FRAMES_PER_SEC()           (gUsecaseContext.captureFps/2)

Void multich_register_created_link(MultichDevice_Context *pContext, UInt32 linkID);
Void multich_set_capture_prm(CaptureLink_CreateParams *capturePrm);
Void multich_set_capture_fps(UInt32 *captureFps);
Void multich_set_swms_prm(UInt32 swMsId);
Void multich_set_display_prms(DisplayLink_CreateParams *displayPrm, int displayId);

#endif

