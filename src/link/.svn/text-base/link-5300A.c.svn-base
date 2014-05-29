#include "link_def-5300A.h"
#include "../osd/osd.h"


int links_init = 0;
MultichDevice_Context gUsecaseContext = {{0 },  };

#define     MAX_BUFFERING_QUEUE_LEN_PER_CH		(50)
#define     BIT_BUF_LENGTH_LIMIT_FACTOR_HD		(5)

static Void multich_reset_link_prms()
{
	memset(&gUsecaseContext, 0x0, sizeof(MultichDevice_Context));

	CaptureLink_CreateParams_Init(&gUsecaseContext.capturePrm);
	NsfLink_CreateParams_Init(&gUsecaseContext.nsfPrm[0]);
	NsfLink_CreateParams_Init(&gUsecaseContext.nsfPrm[1]);

	//MULTICH_INIT_STRUCT(SwMsLink_CreateParams,		gUsecaseContext.swMsPrm[0]);
	//MULTICH_INIT_STRUCT(SwMsLink_CreateParams,		gUsecaseContext.swMsPrm[1]);
	//MULTICH_INIT_STRUCT(SwMsLink_CreateParams,		gUsecaseContext.swMsPrm[2]);
	//MULTICH_INIT_STRUCT(SwMsLink_CreateParams,		gUsecaseContext.swMsPrm[3]);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gUsecaseContext.displayPrm[0]);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gUsecaseContext.displayPrm[1]);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gUsecaseContext.displayPrm[2]);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gUsecaseContext.displayPrm[3]);

	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gUsecaseContext.ipcOutVpssPrm);
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gUsecaseContext.ipcInVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsOutLinkRTOS_CreateParams,	gUsecaseContext.ipcBitsOutVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsInLinkHLOS_CreateParams,	gUsecaseContext.ipcBitsInHostPrm);
	MULTICH_INIT_STRUCT(EncLink_CreateParams,		gUsecaseContext.encPrm);

	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gUsecaseContext.ipcInVpssPrm);
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gUsecaseContext.ipcOutVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsOutLinkHLOS_CreateParams,	gUsecaseContext.ipcBitsOutHostPrm);
	MULTICH_INIT_STRUCT(IpcBitsInLinkRTOS_CreateParams,	gUsecaseContext.ipcBitsInVideoPrm);
	MULTICH_INIT_STRUCT(DecLink_CreateParams,		gUsecaseContext.decPrm);

	MULTICH_INIT_STRUCT(IpcFramesInLinkRTOS_CreateParams,	gUsecaseContext.ipcFramesInDspPrm);
	MULTICH_INIT_STRUCT(IpcFramesOutLinkRTOS_CreateParams,	gUsecaseContext.ipcFramesOutVpssPrm);
	MULTICH_INIT_STRUCT(AlgLink_CreateParams,		gUsecaseContext.dspAlgPrm);

	// 次码流
	SclrLink_CreateParams_Init(&gUsecaseContext.sclrPrm);
	NsfLink_CreateParams_Init(&gUsecaseContext.nsfPrm[2]);

    AvsyncLink_LinkSynchConfigParams_Init(&gUsecaseContext.avsyncCfg[0]);
    AvsyncLink_LinkSynchConfigParams_Init(&gUsecaseContext.avsyncCfg[1]);    
}

static Void multich_set_link_ids()
{
	gUsecaseContext.captureId		= SYSTEM_LINK_ID_CAPTURE;

	gUsecaseContext.dup0Id			= SYSTEM_VPSS_LINK_ID_DUP_0;
	gUsecaseContext.dup1Id			= SYSTEM_VPSS_LINK_ID_DUP_1;
	gUsecaseContext.merge0Id		= SYSTEM_VPSS_LINK_ID_MERGE_0;
	gUsecaseContext.merge1Id		= SYSTEM_VPSS_LINK_ID_MERGE_1;
	gUsecaseContext.nsfId[0]		= SYSTEM_LINK_ID_NSF_0;
	gUsecaseContext.nsfId[1]		= SYSTEM_LINK_ID_NSF_1;

	gUsecaseContext.ipcOutVpssId		= SYSTEM_VPSS_LINK_ID_IPC_OUT_M3_0;
	gUsecaseContext.ipcInVideoId		= SYSTEM_VIDEO_LINK_ID_IPC_IN_M3_0;
	gUsecaseContext.encId			= SYSTEM_LINK_ID_VENC_0;
	gUsecaseContext.ipcBitsOutRTOSId	= SYSTEM_VIDEO_LINK_ID_IPC_BITS_OUT_0;
	gUsecaseContext.ipcBitsInHLOSId		= SYSTEM_HOST_LINK_ID_IPC_BITS_IN_0;

	gUsecaseContext.swMsId[0]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_0;
	gUsecaseContext.swMsId[1]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_1;
	gUsecaseContext.swMsId[2]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_2;
	gUsecaseContext.swMsId[3]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_3;
	gUsecaseContext.displayId[0]		= SYSTEM_LINK_ID_DISPLAY_0;
	gUsecaseContext.displayId[1]		= SYSTEM_LINK_ID_DISPLAY_1;
	gUsecaseContext.displayId[2]		= SYSTEM_LINK_ID_DISPLAY_2;
	//gUsecaseContext.displayId[3]		= SYSTEM_LINK_ID_DISPLAY_3;

	// 次码流
    gUsecaseContext.dup2Id          = SYSTEM_VPSS_LINK_ID_DUP_2;
	gUsecaseContext.dup3Id			= SYSTEM_VPSS_LINK_ID_DUP_3;
	gUsecaseContext.merge3Id		= SYSTEM_VPSS_LINK_ID_MERGE_3;
	gUsecaseContext.sclrId[0]		= SYSTEM_LINK_ID_SCLR_INST_0;
	gUsecaseContext.nsfId[2]		= SYSTEM_LINK_ID_NSF_2;

	// 解码
	gUsecaseContext.ipcBitsOutHLOSId	= SYSTEM_HOST_LINK_ID_IPC_BITS_OUT_0;
	gUsecaseContext.ipcBitsInRTOSId		= SYSTEM_VIDEO_LINK_ID_IPC_BITS_IN_0;
	gUsecaseContext.decId			= SYSTEM_LINK_ID_VDEC_0;

	gUsecaseContext.ipcOutVideoId		= SYSTEM_VIDEO_LINK_ID_IPC_OUT_M3_0;
	gUsecaseContext.ipcInVpssId		= SYSTEM_VPSS_LINK_ID_IPC_IN_M3_0;

	// OSD
    gUsecaseContext.dspAlgId[0]		= SYSTEM_LINK_ID_ALG_0  ;
    gUsecaseContext.ipcFramesOutVpssId[0]	= SYSTEM_VPSS_LINK_ID_IPC_FRAMES_OUT_0;
    gUsecaseContext.ipcFramesInDspId[0]	= SYSTEM_DSP_LINK_ID_IPC_FRAMES_IN_0;
   
}

Void multich_5300a_register_created_link(MultichDevice_Context *pContext, UInt32 linkID)
{
	OSA_assert(pContext->createdLinkCount < OSA_ARRAYSIZE(pContext->createdLinks));
	pContext->createdLinks[pContext->createdLinkCount] = linkID;
	pContext->createdLinkCount++;
}

static Void multich_connect_links()
{
	int i;

	gVdisModuleContext.swMsId[0]		= gUsecaseContext.swMsId[0];
	gVdisModuleContext.swMsId[1]		= gUsecaseContext.swMsId[1];
	//gVdisModuleContext.swMsId[2]		= gUsecaseContext.swMsId[2];


	gVdisModuleContext.displayId[0]		= gUsecaseContext.displayId[0];		// ON CHIP HDMI
	gVdisModuleContext.displayId[1]		= gUsecaseContext.displayId[1];		// ON CHIP YCbCr
	gVdisModuleContext.displayId[2]		= gUsecaseContext.displayId[2];		// ON CHIP CVBS

	gVdecModuleContext.ipcBitsOutHLOSId	= gUsecaseContext.ipcBitsOutHLOSId;
	gVdecModuleContext.ipcBitsInRTOSId	= gUsecaseContext.ipcBitsInRTOSId;
	gVdecModuleContext.decId		= gUsecaseContext.decId;


	// 解码输出
	if(g_dev.decode_channel_num > 0) {
		// ipcBitsOutHostId ---Q0---> ipcBitsInRtosId
		multich_hddvr_set_ipcbitsout_hlos_prms(&gUsecaseContext.ipcBitsOutHostPrm);
		gUsecaseContext.ipcBitsOutHostPrm.baseCreateParams.outQueParams[0].nextLink    = gVdecModuleContext.ipcBitsInRTOSId;
		MULTICH_CREATE_LINK(gUsecaseContext.ipcBitsOutHLOSId,&gUsecaseContext.ipcBitsOutHostPrm,sizeof(gUsecaseContext.ipcBitsOutHostPrm));
		
		// ipcBitsInRtosId ---Q0---> decId
		gUsecaseContext.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkId	= gUsecaseContext.ipcBitsOutHLOSId;
		gUsecaseContext.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkQueId	= 0;
		gUsecaseContext.ipcBitsInVideoPrm.baseCreateParams.outQueParams[0].nextLink	= gUsecaseContext.decId;
		gUsecaseContext.ipcBitsInVideoPrm.baseCreateParams.numOutQue			= 1;
		MultiCh_ipcBitsInitCreateParams_BitsInRTOS(&gUsecaseContext.ipcBitsInVideoPrm, TRUE);
		MULTICH_CREATE_LINK(gUsecaseContext.ipcBitsInRTOSId,&gUsecaseContext.ipcBitsInVideoPrm,sizeof(gUsecaseContext.ipcBitsInVideoPrm));

		// decId---Q0--->ipcOutVideoId
		multich_hddvr_set_declink_prms(&gUsecaseContext.decPrm);
		gUsecaseContext.decPrm.inQueParams.prevLinkId					= gUsecaseContext.ipcBitsInRTOSId;
		gUsecaseContext.decPrm.inQueParams.prevLinkQueId				= 0;
		gUsecaseContext.decPrm.outQueParams.nextLink					= gUsecaseContext.ipcOutVideoId;
		MULTICH_CREATE_LINK(gUsecaseContext.decId, &gUsecaseContext.decPrm, sizeof(gUsecaseContext.decPrm));
		
		// ipcOutVideoId---Q0-->ipcInVpssId
		gUsecaseContext.ipcOutVideoPrm.inQueParams.prevLinkId				= gUsecaseContext.decId;
		gUsecaseContext.ipcOutVideoPrm.inQueParams.prevLinkQueId			= 0;
		gUsecaseContext.ipcOutVideoPrm.numOutQue					= 1;
		gUsecaseContext.ipcOutVideoPrm.outQueParams[0].nextLink				= gUsecaseContext.ipcInVpssId;
		gUsecaseContext.ipcOutVideoPrm.notifyNextLink					= TRUE;
		gUsecaseContext.ipcOutVideoPrm.notifyPrevLink					= TRUE;
		gUsecaseContext.ipcOutVideoPrm.noNotifyMode					= TRUE;
		MULTICH_CREATE_LINK(gUsecaseContext.ipcOutVideoId, &gUsecaseContext.ipcOutVideoPrm, sizeof(gUsecaseContext.ipcOutVideoPrm));
		
		// ipcInVpssId---Q0--> mergeId[MERGE_DISPLAY]
		gUsecaseContext.ipcInVpssPrm.inQueParams.prevLinkId				= gUsecaseContext.ipcOutVideoId;
		gUsecaseContext.ipcInVpssPrm.inQueParams.prevLinkQueId				= 0;
		gUsecaseContext.ipcInVpssPrm.numOutQue						= 1;
		gUsecaseContext.ipcInVpssPrm.outQueParams[0].nextLink				= gUsecaseContext.merge1Id;
		gUsecaseContext.ipcInVpssPrm.notifyNextLink					= TRUE;
		gUsecaseContext.ipcInVpssPrm.notifyPrevLink					= FALSE;
		gUsecaseContext.merge1Prm.inQueParams[gUsecaseContext.merge1Prm.numInQue].prevLinkId	= gUsecaseContext.ipcInVpssId;
		gUsecaseContext.merge1Prm.inQueParams[gUsecaseContext.merge1Prm.numInQue].prevLinkQueId	= 0;
		gUsecaseContext.merge1Prm.numInQue++;
		MULTICH_CREATE_LINK(gUsecaseContext.ipcInVpssId  , &gUsecaseContext.ipcInVpssPrm, sizeof(gUsecaseContext.ipcInVpssPrm));
	}

	// merge1: 现在暂时只有capture进来，没有decode
	gUsecaseContext.merge1Prm.notifyNextLink		= TRUE;
	gUsecaseContext.merge1Prm.outQueParams.nextLink		= gUsecaseContext.dup1Id;
	gUsecaseContext.dup1Prm.inQueParams.prevLinkId		= gUsecaseContext.merge1Id;
	gUsecaseContext.dup1Prm.inQueParams.prevLinkQueId	= 0;
	MULTICH_CREATE_LINK(gUsecaseContext.merge1Id, &gUsecaseContext.merge1Prm, sizeof(gUsecaseContext.merge1Prm));

	// dup1: 已经是N+M路的合并list，复制给4个swms
	gUsecaseContext.dup1Prm.numOutQue			= 2;
	gUsecaseContext.dup1Prm.notifyNextLink			= TRUE;
	gUsecaseContext.dup1Prm.outQueParams[0].nextLink	= gUsecaseContext.swMsId[0];
	gUsecaseContext.dup1Prm.outQueParams[1].nextLink	= gUsecaseContext.swMsId[1];
    //gUsecaseContext.dup1Prm.outQueParams[2].nextLink	= gUsecaseContext.swMsId[2];
    MULTICH_CREATE_LINK(gUsecaseContext.dup1Id, &gUsecaseContext.dup1Prm, sizeof(gUsecaseContext.dup1Prm));

    multich_hddvr_set_avsync_prm(&gUsecaseContext.avsyncCfg[0], 0, gUsecaseContext.dup1Id, 0);
	g_swms[0].inQueParams.prevLinkId	= gUsecaseContext.dup1Id;
	g_swms[0].inQueParams.prevLinkQueId	= 0;
	multich_set_swms_prm(0);
	g_swms[0].outQueParams.nextLink		= gUsecaseContext.dup2Id;//gUsecaseContext.displayId[0];
	MULTICH_CREATE_LINK(gUsecaseContext.swMsId[0], &g_swms[0], sizeof(g_swms[0]));

    
	gUsecaseContext.dup2Prm.inQueParams.prevLinkId		= gUsecaseContext.swMsId[0];
	gUsecaseContext.dup2Prm.inQueParams.prevLinkQueId	= 0;
	gUsecaseContext.dup2Prm.numOutQue			= 2;
	gUsecaseContext.dup2Prm.notifyNextLink			= TRUE;
	gUsecaseContext.dup2Prm.outQueParams[0].nextLink	= gUsecaseContext.displayId[0];
	gUsecaseContext.dup2Prm.outQueParams[1].nextLink	= gUsecaseContext.displayId[1];//SYSTEM_VPSS_LINK_ID_NULL_0; 
    MULTICH_CREATE_LINK(gUsecaseContext.dup2Id, &gUsecaseContext.dup2Prm, sizeof(gUsecaseContext.dup2Prm));


    //multich_hddvr_set_avsync_prm(&gUsecaseContext.avsyncCfg[1], 1, gUsecaseContext.dup1Id, 1);
	multich_set_swms_prm(1);
	g_swms[1].outQueParams.nextLink		= gUsecaseContext.sclrId[0]; //gUsecaseContext.dup0Id;
    g_swms[1].inQueParams.prevLinkId	= gUsecaseContext.dup1Id;
	g_swms[1].inQueParams.prevLinkQueId	= 1;
    g_swms[1].enableOuputDup		= FALSE;
    g_swms[1].enableProcessTieWithDisplay = FALSE;
    MULTICH_CREATE_LINK(gUsecaseContext.swMsId[1], &g_swms[1], sizeof(g_swms[1]));
        
    /*
	gUsecaseContext.dup0Prm.inQueParams.prevLinkId		= gUsecaseContext.swMsId[1];
	gUsecaseContext.dup0Prm.inQueParams.prevLinkQueId	= 0;
	gUsecaseContext.dup0Prm.numOutQue			= 2;
	gUsecaseContext.dup0Prm.notifyNextLink			= TRUE;
	gUsecaseContext.dup0Prm.outQueParams[0].nextLink	= gUsecaseContext.sclrId[0];//gUsecaseContext.displayId[1];
	gUsecaseContext.dup0Prm.outQueParams[1].nextLink	= SYSTEM_VPSS_LINK_ID_NULL_0; //gUsecaseContext.sclrId[0]; //gUsecaseContext.displayId[2];
    MULTICH_CREATE_LINK(gUsecaseContext.dup0Id, &gUsecaseContext.dup0Prm, sizeof(gUsecaseContext.dup0Prm));
    */
	gUsecaseContext.sclrPrm.enableLineSkipSc	= FALSE;
	gUsecaseContext.sclrPrm.inputFrameRate	= 30;
	gUsecaseContext.sclrPrm.outputFrameRate	= 30;
	gUsecaseContext.sclrPrm.inQueParams.prevLinkId	  = gUsecaseContext.swMsId[1];//gUsecaseContext.dup0Id;
	gUsecaseContext.sclrPrm.inQueParams.prevLinkQueId = 0;
	gUsecaseContext.sclrPrm.outQueParams.nextLink	  = gVdisModuleContext.displayId[2];
	gUsecaseContext.sclrPrm.scaleMode = DEI_SCALE_MODE_ABSOLUTE;
	gUsecaseContext.sclrPrm.outScaleFactor.absoluteResolution.outWidth  = 720;
	gUsecaseContext.sclrPrm.outScaleFactor.absoluteResolution.outHeight = 480;
	gUsecaseContext.sclrPrm.tilerEnable = FALSE; // force tiler disable;
	gUsecaseContext.sclrPrm.numBufsPerCh = 6;
	MULTICH_CREATE_LINK(gUsecaseContext.sclrId[0], &gUsecaseContext.sclrPrm, sizeof(gUsecaseContext.sclrPrm));
    

	gUsecaseContext.displayPrm[0].inQueParams[0].prevLinkId 	= gUsecaseContext.dup2Id;//gUsecaseContext.swMsId[0];
	gUsecaseContext.displayPrm[0].inQueParams[0].prevLinkQueId	= 0;

    gUsecaseContext.displayPrm[1].inQueParams[0].prevLinkId 	= gUsecaseContext.dup2Id;
	gUsecaseContext.displayPrm[1].inQueParams[0].prevLinkQueId	= 1;

    gUsecaseContext.displayPrm[2].inQueParams[0].prevLinkId 	= gUsecaseContext.sclrId[0];//gUsecaseContext.dup0Id;
	gUsecaseContext.displayPrm[2].inQueParams[0].prevLinkQueId	= 0;

    
	// 显示设备1,2
	//multich_set_display_prms(&gUsecaseContext.displayPrm[0], 0);
	gUsecaseContext.displayPrm[0].displayRes		= ETAH_DISPLAY_STD_1080P_60;
	gUsecaseContext.displayPrm[1].displayRes		= ETAH_DISPLAY_STD_1080P_60;
	gUsecaseContext.displayPrm[2].displayRes		= ETAH_DISPLAY_STD_NTSC;
	MULTICH_CREATE_LINK(gUsecaseContext.displayId[0], &gUsecaseContext.displayPrm[0], sizeof(gUsecaseContext.displayPrm[0]));
	MULTICH_CREATE_LINK(gUsecaseContext.displayId[1], &gUsecaseContext.displayPrm[1], sizeof(gUsecaseContext.displayPrm[1]));
	MULTICH_CREATE_LINK(gUsecaseContext.displayId[2], &gUsecaseContext.displayPrm[2], sizeof(gUsecaseContext.displayPrm[2]));
	return;
}

static char *gMultiCh_cpuName[SYSTEM_PLATFORM_CPU_REV_MAX] = {
	"ES1.0",
	"ES1.1",
	"ES2.0",
	"ES2.1",
	"UNKNOWN",
};

static int MultiCh_detectBoard()
{
	int status;
	int cpuRev;

	SystemVpss_PlatformInfo  platformInfo;

	status = System_linkControl(
		SYSTEM_LINK_ID_M3VPSS
		, SYSTEM_M3VPSS_CMD_GET_PLATFORM_INFO
		, &platformInfo
		, sizeof(platformInfo)
		, TRUE
		);
	UTILS_assert(status==OSA_SOK);

	// Get CPU version
	cpuRev = platformInfo.cpuRev;			// sdk里面的api接口获取cpu版本号错误，正确的用dmesg里面查看。
	if (cpuRev >= SYSTEM_PLATFORM_CPU_REV_MAX)
	{
		cpuRev = SYSTEM_PLATFORM_CPU_REV_UNKNOWN;
	}
	printf(" %u: MCFW  : CPU Revision [%s] !!! \r\n", OSA_getCurTimeInMsec(), gMultiCh_cpuName[cpuRev]);

	return 0;
}

SystemVideo_Ivahd2ChMap_Tbl systemVid_5300A_encDecIvaChMapTbl =
{
	.isPopulated = 1,
	.ivaMap[0] =
	{
		.EncNumCh  = 0,
		.EncChList = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 3,
		.DecChList = {0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	.ivaMap[1] =
	{
		.EncNumCh  = 0,
		.EncChList = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 3,
		.DecChList = {1, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	.ivaMap[2] =
	{
		.EncNumCh  = 0,
		.EncChList = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.DecNumCh  = 3,
		.DecChList = {2, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
};

void MultiCh_create5300A()			// MultiCh_createHdDvr
{
	MultiCh_detectBoard();
	printf("============System init links entry>>>>>>>>>>>>\n");
	System_linkControl(SYSTEM_LINK_ID_M3VPSS
			, SYSTEM_M3VPSS_CMD_RESET_VIDEO_DEVICES
			, NULL
			, 0
			, TRUE
			);
	System_linkControl(SYSTEM_LINK_ID_M3VIDEO
			, SYSTEM_COMMON_CMD_SET_CH2IVAHD_MAP_TBL
			, &systemVid_5300A_encDecIvaChMapTbl
			, sizeof(SystemVideo_Ivahd2ChMap_Tbl)
			, TRUE
			);

	multich_reset_link_prms();		// link 参数
	multich_set_link_ids();			// link ID
	multich_connect_links();		// 设置和连接
}

void MultiCh_delete5300A()
{
	UInt32 i;
	
	for (i = 0; i < gUsecaseContext.createdLinkCount; i++)
	{
		printf("delete link: %d-0x%x\n", gUsecaseContext.createdLinks[i], gUsecaseContext.createdLinks[i]);
		System_linkDelete (gUsecaseContext.createdLinks[i]);
	}
	gUsecaseContext.createdLinkCount = 0;
}

