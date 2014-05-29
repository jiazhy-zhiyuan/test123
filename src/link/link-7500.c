#include "link_def-7500.h"
#include "../osd/osd.h"

MultiChHdDvr_Context_7500 gHdDvrUsecaseContext_7500 = {0 };

static Void multich_hddvr_reset_link_prms_7500()
{
	memset(&gHdDvrUsecaseContext_7500, 0x0, sizeof(MultiChHdDvr_Context_7500));


	MULTICH_INIT_STRUCT(IpcFramesOutLinkRTOS_CreateParams,gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm);
	MULTICH_INIT_STRUCT(IpcFramesInLinkRTOS_CreateParams,gHdDvrUsecaseContext_7500.ipcFramesInDspPrm);
	//IpcBitsOutLinkRTOS_CreateParams_Init(&gHdDvrUsecaseContext_7500.ipcBitsOutDspPrm);
	AlgLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.dspAlgPrm);
	
	
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gHdDvrUsecaseContext_7500.ipcInVpssPrm);
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gHdDvrUsecaseContext_7500.ipcOutVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsOutLinkHLOS_CreateParams,	gHdDvrUsecaseContext_7500.ipcBitsOutHostPrm);
	MULTICH_INIT_STRUCT(IpcBitsInLinkRTOS_CreateParams,	gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm);
	MULTICH_INIT_STRUCT(DecLink_CreateParams,		gHdDvrUsecaseContext_7500.decPrm);
	

	CaptureLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.capturePrm);
	DeiLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.dei0Prm);
	DeiLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.dei1Prm);
	SelectLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.selectPrm);
	NsfLink_CreateParams_Init(&gHdDvrUsecaseContext_7500.nsf0Prm);
	
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gHdDvrUsecaseContext_7500.ipcOutVpssPrm);
	MULTICH_INIT_STRUCT(IpcLink_CreateParams,		gHdDvrUsecaseContext_7500.ipcInVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsOutLinkRTOS_CreateParams,	gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm);
	MULTICH_INIT_STRUCT(IpcBitsInLinkHLOS_CreateParams,	gHdDvrUsecaseContext_7500.ipcBitsInHostPrm);
	MULTICH_INIT_STRUCT(EncLink_CreateParams,		gHdDvrUsecaseContext_7500.encPrm);

	AvsyncLink_LinkSynchConfigParams_Init(&gHdDvrUsecaseContext_7500.avsyncCfg);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gHdDvrUsecaseContext_7500.displayPrm[0]);
	MULTICH_INIT_STRUCT(DisplayLink_CreateParams,		gHdDvrUsecaseContext_7500.displayPrm[1]);

	
}

static Void multich_hddvr_set_link_ids_7500()
{
	gHdDvrUsecaseContext_7500.ipcBitsOutHLOSId	= SYSTEM_HOST_LINK_ID_IPC_BITS_OUT_0;
	gHdDvrUsecaseContext_7500.ipcBitsInRTOSId	= SYSTEM_VIDEO_LINK_ID_IPC_BITS_IN_0;
	gHdDvrUsecaseContext_7500.decId			= SYSTEM_LINK_ID_VDEC_0;
	gHdDvrUsecaseContext_7500.ipcOutVideoId		= SYSTEM_VIDEO_LINK_ID_IPC_OUT_M3_0;
	gHdDvrUsecaseContext_7500.ipcInVpssId		= SYSTEM_VPSS_LINK_ID_IPC_IN_M3_0;
	
	gHdDvrUsecaseContext_7500.dup0Id		= SYSTEM_VPSS_LINK_ID_DUP_0;
	gHdDvrUsecaseContext_7500.dup1Id		= SYSTEM_VPSS_LINK_ID_DUP_1;
	gHdDvrUsecaseContext_7500.merge0Id		= SYSTEM_VPSS_LINK_ID_MERGE_0;
	gHdDvrUsecaseContext_7500.merge1Id		= SYSTEM_VPSS_LINK_ID_MERGE_1;
	gHdDvrUsecaseContext_7500.nsf0Id		= SYSTEM_LINK_ID_NSF_0;
	gHdDvrUsecaseContext_7500.dei0Id     		= SYSTEM_LINK_ID_DEI_HQ_0;
	gHdDvrUsecaseContext_7500.dei1Id     		= SYSTEM_LINK_ID_DEI_HQ_1;
	
	gHdDvrUsecaseContext_7500.selectId   		= SYSTEM_VPSS_LINK_ID_SELECT_0;

	
	gHdDvrUsecaseContext_7500.swMsId[0]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_0;
	gHdDvrUsecaseContext_7500.swMsId[1]		= SYSTEM_LINK_ID_SW_MS_MULTI_INST_1;

	gHdDvrUsecaseContext_7500.displayId[0]		= SYSTEM_LINK_ID_DISPLAY_0;
	gHdDvrUsecaseContext_7500.displayId[1]		= SYSTEM_LINK_ID_DISPLAY_1;
	//gHdDvrUsecaseContext_7500.displayId[1]		= Vdis_getDisplayId(VDIS_DEV_DVO2);

	//printf("HDMI : %d\nDVO2 : %d\n", gHdDvrUsecaseContext_7500.displayId[0], gHdDvrUsecaseContext_7500.displayId[1]);
	
	gHdDvrUsecaseContext_7500.captureId		= SYSTEM_LINK_ID_CAPTURE;

	gHdDvrUsecaseContext_7500.ipcOutVpssId		= SYSTEM_VPSS_LINK_ID_IPC_OUT_M3_0;
	gHdDvrUsecaseContext_7500.ipcInVideoId		= SYSTEM_VIDEO_LINK_ID_IPC_IN_M3_0;
	gHdDvrUsecaseContext_7500.encId			= SYSTEM_LINK_ID_VENC_0;
	gHdDvrUsecaseContext_7500.ipcBitsOutRTOSId	= SYSTEM_VIDEO_LINK_ID_IPC_BITS_OUT_0;
	gHdDvrUsecaseContext_7500.ipcBitsInHLOSId	= SYSTEM_HOST_LINK_ID_IPC_BITS_IN_0;

	gHdDvrUsecaseContext_7500.ipcFramesOutVpssId 	= SYSTEM_VPSS_LINK_ID_IPC_FRAMES_OUT_0;
    gHdDvrUsecaseContext_7500.ipcFramesInDspId   	= SYSTEM_DSP_LINK_ID_IPC_FRAMES_IN_0;
    gHdDvrUsecaseContext_7500.dspAlgId           	= SYSTEM_LINK_ID_ALG_0;
	

}

Void multich_hddvr_register_created_link_7500(MultiChHdDvr_Context_7500 *pContext, UInt32 linkID)
{
	OSA_assert(pContext->createdLinkCount < OSA_ARRAYSIZE(pContext->createdLinks));
	pContext->createdLinks[pContext->createdLinkCount] = linkID;
	pContext->createdLinkCount++;
}

static Void multich_hddvr_connect_links_7500()
{
	printf("Yes it's 7500\n");
	
	DeiLink_OutputScaleFactor outScaleFactorDeiSc, outScaleFactorVipSc;

	gVcapModuleContext.captureId		= gHdDvrUsecaseContext_7500.captureId;
	gVcapModuleContext.vcapConfig.enableConfigExtVideoDecoder = FALSE;
	gVcapModuleContext.nsfId[0]		= gHdDvrUsecaseContext_7500.nsf0Id;
	
	gVcapModuleContext.deiId[0]		= gHdDvrUsecaseContext_7500.dei0Id;
	gVcapModuleContext.deiId[2] 		= gHdDvrUsecaseContext_7500.dei1Id;
	

	gVcapModuleContext.ipcFramesOutVpssId[0]= gHdDvrUsecaseContext_7500.ipcFramesOutVpssId;
	gVcapModuleContext.ipcFramesInDspId[0]  = gHdDvrUsecaseContext_7500.ipcFramesInDspId;
	

	gVencModuleContext.encId		= gHdDvrUsecaseContext_7500.encId;
	gVencModuleContext.ipcBitsInHLOSId	= gHdDvrUsecaseContext_7500.ipcBitsInHLOSId;
	gVencModuleContext.ipcBitsOutRTOSId	= gHdDvrUsecaseContext_7500.ipcBitsOutRTOSId;

	
	gVdisModuleContext.swMsId[0]		= gHdDvrUsecaseContext_7500.swMsId[0];
	gVdisModuleContext.swMsId[1]		= gHdDvrUsecaseContext_7500.swMsId[1];

	gVdecModuleContext.ipcBitsOutHLOSId	= gHdDvrUsecaseContext_7500.ipcBitsOutHLOSId;
	gVdecModuleContext.ipcBitsInRTOSId	= gHdDvrUsecaseContext_7500.ipcBitsInRTOSId;
	gVdecModuleContext.decId		= gHdDvrUsecaseContext_7500.decId;

	gVdisModuleContext.displayId[0]		= gHdDvrUsecaseContext_7500.displayId[0];		// ON CHIP HDMI
	gVdisModuleContext.displayId[2]		= gHdDvrUsecaseContext_7500.displayId[1];		// ON CHIP YCbCr
	
    gVcapModuleContext.dspAlgId[0] = gHdDvrUsecaseContext_7500.dspAlgId;

	
	multich_hddvr_set_capture_prm_7500(&gHdDvrUsecaseContext_7500.capturePrm);
	gHdDvrUsecaseContext_7500.capturePrm.outQueParams[0].nextLink = gHdDvrUsecaseContext_7500.dup1Id;
	//gHdDvrUsecaseContext_7500.capturePrm.outQueParams[1].nextLink = gHdDvrUsecaseContext_7500.merge0Id; //gHdDvrUsecaseContext_7500.selectId;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.captureId, gHdDvrUsecaseContext_7500.capturePrm);

	gHdDvrUsecaseContext_7500.dup1Prm.inQueParams.prevLinkId		= gHdDvrUsecaseContext_7500.captureId;
	gHdDvrUsecaseContext_7500.dup1Prm.inQueParams.prevLinkQueId		= 0;
	gHdDvrUsecaseContext_7500.dup1Prm.numOutQue				= 2;
	gHdDvrUsecaseContext_7500.dup1Prm.notifyNextLink			= TRUE;
	gHdDvrUsecaseContext_7500.dup1Prm.outQueParams[0].nextLink		= gHdDvrUsecaseContext_7500.selectId;
	gHdDvrUsecaseContext_7500.dup1Prm.outQueParams[1].nextLink		= gHdDvrUsecaseContext_7500.merge1Id;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.dup1Id  , gHdDvrUsecaseContext_7500.dup1Prm);



	
	gHdDvrUsecaseContext_7500.selectPrm.numOutQue = 2;
	gHdDvrUsecaseContext_7500.selectPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.dup1Id;
	gHdDvrUsecaseContext_7500.selectPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.selectPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext_7500.dei0Id;
	gHdDvrUsecaseContext_7500.selectPrm.outQueParams[1].nextLink  = gHdDvrUsecaseContext_7500.dei1Id;
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[0].outQueId  = 0;
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[0].numOutCh  = 1;
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[0].inChNum[0]= 0;
	
	
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[1].outQueId  = 1;
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[1].numOutCh  = 1;
	gHdDvrUsecaseContext_7500.selectPrm.outQueChInfo[1].inChNum[0]= 1;
	
	
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.selectId, gHdDvrUsecaseContext_7500.selectPrm);
	
	
	outScaleFactorVipSc.scaleMode = DEI_SCALE_MODE_RATIO;		// 主码流: 1:1 scaling, output is 420
	outScaleFactorVipSc.ratio.widthRatio.numerator     = 1;
	outScaleFactorVipSc.ratio.widthRatio.denominator   = 1;
	outScaleFactorVipSc.ratio.heightRatio.numerator    = 1;
	outScaleFactorVipSc.ratio.heightRatio.denominator  = 1;
	outScaleFactorDeiSc.scaleMode = DEI_SCALE_MODE_RATIO;		// 次码流: 1/2 scaling, output is 422, need NSF link
	outScaleFactorDeiSc.ratio.widthRatio.numerator     = 1;
	outScaleFactorDeiSc.ratio.widthRatio.denominator   = 2;
	outScaleFactorDeiSc.ratio.heightRatio.numerator    = 1;
	outScaleFactorDeiSc.ratio.heightRatio.denominator  = 2;

	multich_hddvr_set_dei_prm_7500(&gHdDvrUsecaseContext_7500.dei0Prm, &outScaleFactorDeiSc, &outScaleFactorVipSc);
	gHdDvrUsecaseContext_7500.dei0Prm.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.selectId;
	gHdDvrUsecaseContext_7500.dei0Prm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.dei0Prm.outQueParams[DEI_LINK_OUT_QUE_VIP_SC].nextLink = gHdDvrUsecaseContext_7500.merge0Id;

	gHdDvrUsecaseContext_7500.dei0Prm.outQueParams[DEI_LINK_OUT_QUE_DEI_SC].nextLink = SYSTEM_VPSS_LINK_ID_NULL_0;	// 本地不要次码流
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.dei0Id, gHdDvrUsecaseContext_7500.dei0Prm);
	
	multich_hddvr_set_dei_prm_7500(&gHdDvrUsecaseContext_7500.dei1Prm, &outScaleFactorDeiSc, &outScaleFactorVipSc);
	gHdDvrUsecaseContext_7500.dei1Prm.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.selectId;
	gHdDvrUsecaseContext_7500.dei1Prm.inQueParams.prevLinkQueId = 1;
	gHdDvrUsecaseContext_7500.dei1Prm.outQueParams[DEI_LINK_OUT_QUE_VIP_SC].nextLink = gHdDvrUsecaseContext_7500.merge0Id;

	gHdDvrUsecaseContext_7500.dei1Prm.outQueParams[DEI_LINK_OUT_QUE_DEI_SC].nextLink = SYSTEM_VPSS_LINK_ID_NULL_0;	// 本地不要次码流

	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.dei1Id, gHdDvrUsecaseContext_7500.dei1Prm);	
	

	gHdDvrUsecaseContext_7500.merge0Prm.inQueParams[1].prevLinkId		= gHdDvrUsecaseContext_7500.dei1Id;
	gHdDvrUsecaseContext_7500.merge0Prm.inQueParams[1].prevLinkQueId	= DEI_LINK_OUT_QUE_VIP_SC;
	gHdDvrUsecaseContext_7500.merge0Prm.inQueParams[0].prevLinkId		= gHdDvrUsecaseContext_7500.dei0Id;
	gHdDvrUsecaseContext_7500.merge0Prm.inQueParams[0].prevLinkQueId	= DEI_LINK_OUT_QUE_VIP_SC;
	gHdDvrUsecaseContext_7500.merge0Prm.numInQue 				= 2;
	gHdDvrUsecaseContext_7500.merge0Prm.notifyNextLink			= TRUE;
	gHdDvrUsecaseContext_7500.merge0Prm.outQueParams.nextLink		= gHdDvrUsecaseContext_7500.ipcFramesOutVpssId;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.merge0Id, gHdDvrUsecaseContext_7500.merge0Prm);
	

	
	if(g_dev.decode_channel_num > 0) {
		// ipcBitsOutHostId ---Q0---> ipcBitsInRtosId
		multich_hddvr_set_ipcbitsout_hlos_prms_7500(&gHdDvrUsecaseContext_7500.ipcBitsOutHostPrm);
		gHdDvrUsecaseContext_7500.ipcBitsOutHostPrm.baseCreateParams.outQueParams[0].nextLink    = gHdDvrUsecaseContext_7500.ipcBitsInRTOSId;
		MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcBitsOutHLOSId,gHdDvrUsecaseContext_7500.ipcBitsOutHostPrm);
		
		// ipcBitsInRtosId ---Q0---> decId
		gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkId	= gHdDvrUsecaseContext_7500.ipcBitsOutHLOSId;
		gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkQueId	= 0;
		gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm.baseCreateParams.outQueParams[0].nextLink	= gHdDvrUsecaseContext_7500.decId;
		gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm.baseCreateParams.numOutQue			= 1;
		MultiCh_ipcBitsInitCreateParams_BitsInRTOS(&gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm, TRUE);
		MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcBitsInRTOSId,gHdDvrUsecaseContext_7500.ipcBitsInVideoPrm);

		// decId---Q0--->ipcOutVideoId
		multich_hddvr_set_declink_prms_7500(&gHdDvrUsecaseContext_7500.decPrm);
		gHdDvrUsecaseContext_7500.decPrm.inQueParams.prevLinkId					= gHdDvrUsecaseContext_7500.ipcBitsInRTOSId;
		gHdDvrUsecaseContext_7500.decPrm.inQueParams.prevLinkQueId				= 0;
		gHdDvrUsecaseContext_7500.decPrm.outQueParams.nextLink					= gHdDvrUsecaseContext_7500.ipcOutVideoId;
		MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.decId, gHdDvrUsecaseContext_7500.decPrm);
		
		// ipcOutVideoId---Q0-->ipcInVpssId
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.inQueParams.prevLinkId				= gHdDvrUsecaseContext_7500.decId;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.inQueParams.prevLinkQueId			= 0;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.numOutQue					= 1;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.outQueParams[0].nextLink				= gHdDvrUsecaseContext_7500.ipcInVpssId;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.notifyNextLink					= TRUE;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.notifyPrevLink					= TRUE;
		gHdDvrUsecaseContext_7500.ipcOutVideoPrm.noNotifyMode					= TRUE;
		MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcOutVideoId, gHdDvrUsecaseContext_7500.ipcOutVideoPrm);
		
		// ipcInVpssId---Q0--> mergeId[MERGE_DISPLAY]
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.inQueParams.prevLinkId				= gHdDvrUsecaseContext_7500.ipcOutVideoId;
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.inQueParams.prevLinkQueId				= 0;
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.numOutQue						= 1;
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.outQueParams[0].nextLink				= gHdDvrUsecaseContext_7500.merge1Id;
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.notifyNextLink					= TRUE;
		gHdDvrUsecaseContext_7500.ipcInVpssPrm.notifyPrevLink					= FALSE;
		MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcInVpssId, gHdDvrUsecaseContext_7500.ipcInVpssPrm);
	}	

	// dup1: 已经是2路的合并list，复制给2个swms

	gHdDvrUsecaseContext_7500.merge1Prm.inQueParams[0].prevLinkId		= gHdDvrUsecaseContext_7500.dup1Id;
	gHdDvrUsecaseContext_7500.merge1Prm.inQueParams[0].prevLinkQueId	= 1;
	gHdDvrUsecaseContext_7500.merge1Prm.inQueParams[1].prevLinkId		= gHdDvrUsecaseContext_7500.ipcInVpssId;
	gHdDvrUsecaseContext_7500.merge1Prm.inQueParams[1].prevLinkQueId	= 0;
	gHdDvrUsecaseContext_7500.merge1Prm.numInQue 				= 2;
	gHdDvrUsecaseContext_7500.merge1Prm.notifyNextLink			= TRUE;
	gHdDvrUsecaseContext_7500.merge1Prm.outQueParams.nextLink		= gHdDvrUsecaseContext_7500.dup0Id;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.merge1Id, gHdDvrUsecaseContext_7500.merge1Prm);
	

	gHdDvrUsecaseContext_7500.dup0Prm.inQueParams.prevLinkId		= gHdDvrUsecaseContext_7500.merge1Id;
	gHdDvrUsecaseContext_7500.dup0Prm.inQueParams.prevLinkQueId	= 0;
	gHdDvrUsecaseContext_7500.dup0Prm.numOutQue			= 2;
	gHdDvrUsecaseContext_7500.dup0Prm.notifyNextLink			= TRUE;
	gHdDvrUsecaseContext_7500.dup0Prm.outQueParams[0].nextLink	= gHdDvrUsecaseContext_7500.swMsId[0];
	gHdDvrUsecaseContext_7500.dup0Prm.outQueParams[1].nextLink	= gHdDvrUsecaseContext_7500.swMsId[1];
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.dup0Id  , gHdDvrUsecaseContext_7500.dup0Prm);


	//multich_hddvr_set_avsync_prm_7500(&gHdDvrUsecaseContext_7500.avsyncCfg, 0, gHdDvrUsecaseContext_7500.dup0Id, 0);
	g_swms[0].inQueParams.prevLinkId	= gHdDvrUsecaseContext_7500.dup0Id;
	g_swms[0].inQueParams.prevLinkQueId	= 0;
	multich_set_swms_prm_7500(0);
	g_swms[0].outQueParams.nextLink		= gHdDvrUsecaseContext_7500.displayId[0];
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.swMsId[0], g_swms[0]);

	g_swms[1].inQueParams.prevLinkId	= gHdDvrUsecaseContext_7500.dup0Id;
	g_swms[1].inQueParams.prevLinkQueId	= 1;
	multich_set_swms_prm_7500(1);
	g_swms[1].outQueParams.nextLink		= gHdDvrUsecaseContext_7500.displayId[1];
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.swMsId[1], g_swms[1]);


	//multich_set_display_prms_7500(&gHdDvrUsecaseContext_7500.displayPrm[0], 0);
	gHdDvrUsecaseContext_7500.displayPrm[0].displayRes			= ETAH_DISPLAY_STD_1080P_60;
	gHdDvrUsecaseContext_7500.displayPrm[0].inQueParams[0].prevLinkId 	= gHdDvrUsecaseContext_7500.swMsId[0];
	gHdDvrUsecaseContext_7500.displayPrm[0].inQueParams[0].prevLinkQueId	= 0;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.displayId[0], gHdDvrUsecaseContext_7500.displayPrm[0]);

	
	gHdDvrUsecaseContext_7500.displayPrm[1].inQueParams[0].prevLinkId 	= gHdDvrUsecaseContext_7500.swMsId[1];
	gHdDvrUsecaseContext_7500.displayPrm[1].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext_7500.displayPrm[1].displayRes			= ETAH_DISPLAY_STD_1080P_60;	
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.displayId[1], gHdDvrUsecaseContext_7500.displayPrm[1]);
	
	//----------------------------osd-------------------------------------------------
		
	int i;
	// IpcFramesOut Link for OSD
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.inQueParams.prevLinkId	 = gHdDvrUsecaseContext_7500.merge0Id;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.inQueParams.prevLinkQueId  = 0;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.numOutQue		 = 1;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.notifyNextLink		 = TRUE;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.outQueParams[0].nextLink  = gHdDvrUsecaseContext_7500.ipcOutVpssId;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.processLink		 = gHdDvrUsecaseContext_7500.ipcFramesInDspId;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.notifyProcessLink	 = TRUE;
	gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm.baseCreateParams.noNotifyMode		 = FALSE;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcFramesOutVpssId,gHdDvrUsecaseContext_7500.ipcFramesOutVpssPrm);
	
	
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.inQueParams.prevLinkId	= gHdDvrUsecaseContext_7500.ipcFramesOutVpssId;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.inQueParams.prevLinkQueId	= 0;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.numOutQue			= 1;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.outQueParams[0].nextLink	= gHdDvrUsecaseContext_7500.dspAlgId;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.notifyPrevLink		= TRUE;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.notifyNextLink		= TRUE;
	gHdDvrUsecaseContext_7500.ipcFramesInDspPrm.baseCreateParams.noNotifyMode		= FALSE;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcFramesInDspId, gHdDvrUsecaseContext_7500.ipcFramesInDspPrm);

	gHdDvrUsecaseContext_7500.dspAlgPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.ipcFramesInDspId;
	gHdDvrUsecaseContext_7500.dspAlgPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.dspAlgPrm.enableOSDAlg = TRUE;
	gHdDvrUsecaseContext_7500.dspAlgPrm.enableSCDAlg = FALSE;
	gHdDvrUsecaseContext_7500.dspAlgPrm.outQueParams[ALG_LINK_SCD_OUT_QUE].nextLink = SYSTEM_LINK_ID_INVALID;

	for(i = 0; i < g_dev.vi_channel_num; i++) {
		gHdDvrUsecaseContext_7500.dspAlgPrm.osdChCreateParams[i].maxWidth			= g_dev.osd_win_max_width;
		gHdDvrUsecaseContext_7500.dspAlgPrm.osdChCreateParams[i].maxHeight			= g_dev.osd_win_max_height;
		gHdDvrUsecaseContext_7500.dspAlgPrm.osdChCreateParams[i].chDefaultParams.chId		= i;
		gHdDvrUsecaseContext_7500.dspAlgPrm.osdChCreateParams[i].chDefaultParams.numWindows	= 0;
	}


	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.dspAlgId, gHdDvrUsecaseContext_7500.dspAlgPrm);
	
	//-----------------------------------------------enc--------------------------------------------
	// ipcOutVpssIdisOutVpssId ---Q0---> ipcInVideoId
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.inQueParams.prevLinkId	  = gHdDvrUsecaseContext_7500.ipcFramesOutVpssId;
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext_7500.ipcInVideoId;
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.notifyNextLink	      = FALSE;
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.notifyPrevLink	      = TRUE;
	gHdDvrUsecaseContext_7500.ipcOutVpssPrm.noNotifyMode	      = TRUE;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcOutVpssId, gHdDvrUsecaseContext_7500.ipcOutVpssPrm);

	// ipcInVideoId ---Q0---> encId
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.inQueParams.prevLinkId	  = gHdDvrUsecaseContext_7500.ipcOutVpssId;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.numOutQue		      = 1;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext_7500.encId;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.notifyNextLink	      = TRUE;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.notifyPrevLink	      = FALSE;
	gHdDvrUsecaseContext_7500.ipcInVideoPrm.noNotifyMode	      = TRUE;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcInVideoId, gHdDvrUsecaseContext_7500.ipcInVideoPrm);
	
	// encId ---Q0---> ipcBitsOutRTOSId
	multich_hddvr_set_enclink_prm_7500(&gHdDvrUsecaseContext_7500.encPrm);
	gHdDvrUsecaseContext_7500.encPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.ipcInVideoId;
	gHdDvrUsecaseContext_7500.encPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.encPrm.outQueParams.nextLink	   = gHdDvrUsecaseContext_7500.ipcBitsOutRTOSId;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.encId, gHdDvrUsecaseContext_7500.encPrm);
	
	// ipcBitsOutVideoId ---Q0---> ipcBitsInHostId
	gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm.baseCreateParams.inQueParams.prevLinkId	= gHdDvrUsecaseContext_7500.encId;
	gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm.baseCreateParams.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm.baseCreateParams.numOutQue 	    = 1;
	gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm.baseCreateParams.outQueParams[0].nextLink	= gHdDvrUsecaseContext_7500.ipcBitsInHLOSId;
	MultiCh_ipcBitsInitCreateParams_BitsOutRTOS(&gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm, TRUE);
	gHdDvrUsecaseContext_7500.ipcBitsInHostPrm.baseCreateParams.inQueParams.prevLinkId    = gHdDvrUsecaseContext_7500.ipcBitsOutRTOSId;
	gHdDvrUsecaseContext_7500.ipcBitsInHostPrm.baseCreateParams.inQueParams.prevLinkQueId = 0;
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcBitsOutRTOSId, gHdDvrUsecaseContext_7500.ipcBitsOutVideoPrm);

	// 
	MultiCh_ipcBitsInitCreateParams_BitsInHLOS(&gHdDvrUsecaseContext_7500.ipcBitsInHostPrm);
	MULTICH_HDDVR_CREATE_LINK_7500(gHdDvrUsecaseContext_7500.ipcBitsInHLOSId, gHdDvrUsecaseContext_7500.ipcBitsInHostPrm);

	//-------------------------------------------enc end ------------------------------------------



	printf("%s Out\n", __func__);
}



static char *gMultiCh_cpuName[SYSTEM_PLATFORM_CPU_REV_MAX] = {
	"ES1.0",
	"ES1.1",
	"ES2.0",
	"ES2.1",
	"UNKNOWN",
};

static int MultiCh_detectBoard_7500()
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

void MultiCh_createHdDvr_7500()			// MultiCh_createHdDvr
{
	multich_hddvr_reset_link_prms_7500();		// link 参数
	multich_hddvr_set_link_ids_7500();			// link ID
	MultiCh_detectBoard_7500();

	printf("============System init links entry>>>>>>>>>>>>\n");
	System_linkControl(SYSTEM_LINK_ID_M3VPSS, SYSTEM_M3VPSS_CMD_RESET_VIDEO_DEVICES, NULL, 0, TRUE);
	System_linkControl(SYSTEM_LINK_ID_M3VIDEO, SYSTEM_COMMON_CMD_SET_CH2IVAHD_MAP_TBL, &systemVid_encDecIvaChMapTbl_7500, sizeof(SystemVideo_Ivahd2ChMap_Tbl), TRUE);

	multich_hddvr_connect_links_7500();			// 设置和连接
	printf("============System init links leave<<<<<<<<<<<<\n");
}

void MultiCh_deleteHdDvr_7500()
{
	UInt32 i;

	for (i = 0; i < gHdDvrUsecaseContext_7500.createdLinkCount; i++)
	{
		printf("delete link: %d-0x%x\n", gHdDvrUsecaseContext_7500.createdLinks[i], gHdDvrUsecaseContext_7500.createdLinks[i]);
		System_linkDelete (gHdDvrUsecaseContext_7500.createdLinks[i]);
	}
	gHdDvrUsecaseContext_7500.createdLinkCount = 0;
}

