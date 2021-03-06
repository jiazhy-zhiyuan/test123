#include "link_def-6800A.h"
#include "../osd/osd.h"

Void multich_hddvr_connect_osd_links()
{
	int i;
	// IpcFramesOut Link for OSD
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.inQueParams.prevLinkId     = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.inQueParams.prevLinkQueId  = 0;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.numOutQue                  = 1;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.notifyNextLink             = TRUE;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.outQueParams[0].nextLink   = gHdDvrUsecaseContext1.ipcOutVpssId;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.processLink                = gVcapModuleContext.ipcFramesInDspId[0];;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.notifyProcessLink          = TRUE;
	gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0].baseCreateParams.noNotifyMode               = FALSE;
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.ipcFramesOutVpssId[0],gHdDvrUsecaseContext1.ipcFramesOutVpssPrm[0]);

	/* IpcFramesInDsp ---Q0--- dspAlg0(SCD) */
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.inQueParams.prevLinkId	= gVcapModuleContext.ipcFramesOutVpssId[0];
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.inQueParams.prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.numOutQue			= 1;
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.outQueParams[0].nextLink	= gVcapModuleContext.dspAlgId[0];
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.notifyPrevLink		= TRUE;
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.notifyNextLink		= TRUE;
	gHdDvrUsecaseContext1.ipcFramesInDspPrm[0].baseCreateParams.noNotifyMode 		= FALSE;
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.ipcFramesInDspId[0], gHdDvrUsecaseContext1.ipcFramesInDspPrm[0]);

	gHdDvrUsecaseContext1.dspAlgPrm[0].inQueParams.prevLinkId    = gVcapModuleContext.ipcFramesInDspId[0];
	gHdDvrUsecaseContext1.dspAlgPrm[0].inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.dspAlgPrm[0].enableOSDAlg = TRUE;
	gHdDvrUsecaseContext1.dspAlgPrm[0].enableSCDAlg = FALSE;
	gHdDvrUsecaseContext1.dspAlgPrm[0].outQueParams[ALG_LINK_SCD_OUT_QUE].nextLink = SYSTEM_LINK_ID_INVALID;
#if 1
	for(i = 0; i < (g_dev.vi_channel_num + g_dev.swms_encode_num) * g_dev.stream_type; i++) {
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].maxWidth			= g_dev.osd_win_max_width;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].maxHeight			= g_dev.osd_win_max_height;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].chDefaultParams.chId		= i;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].chDefaultParams.numWindows	= 0;
	}
#else
	// 只需要1个osd，每路都有几个osd会因为dsp性能的影响降低帧率，2014.2.11
	{
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].maxWidth			= g_dev.osd_win_max_width;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].maxHeight			= g_dev.osd_win_max_height;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].chDefaultParams.chId		= OSD_ENCODE_CHANNELI_ID;
		gHdDvrUsecaseContext1.dspAlgPrm[0].osdChCreateParams[0].chDefaultParams.numWindows	= 0;
	}
#endif
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.dspAlgId[0], gHdDvrUsecaseContext1.dspAlgPrm[0]);
}

Void multich_hddvr_connect_encode_links()
{
	// ipcOutVpssIdisOutVpssId ---Q0---> ipcInVideoId
#ifdef ETAH_6800A_USE_OSD
	gHdDvrUsecaseContext1.ipcOutVpssPrm.inQueParams.prevLinkId    = gVcapModuleContext.ipcFramesOutVpssId[0];
#else
	gHdDvrUsecaseContext1.ipcOutVpssPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
#endif
	gHdDvrUsecaseContext1.ipcOutVpssPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.ipcOutVpssPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext1.ipcInVideoId;
	gHdDvrUsecaseContext1.ipcOutVpssPrm.notifyNextLink            = FALSE;
	gHdDvrUsecaseContext1.ipcOutVpssPrm.notifyPrevLink            = TRUE;
	gHdDvrUsecaseContext1.ipcOutVpssPrm.noNotifyMode              = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.ipcOutVpssId, gHdDvrUsecaseContext1.ipcOutVpssPrm);

	// ipcInVideoId ---Q0---> encId
	gHdDvrUsecaseContext1.ipcInVideoPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext1.ipcOutVpssId;
	gHdDvrUsecaseContext1.ipcInVideoPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.ipcInVideoPrm.numOutQue                 = 1;
	gHdDvrUsecaseContext1.ipcInVideoPrm.outQueParams[0].nextLink  = gVencModuleContext.encId;
	gHdDvrUsecaseContext1.ipcInVideoPrm.notifyNextLink            = TRUE;
	gHdDvrUsecaseContext1.ipcInVideoPrm.notifyPrevLink            = FALSE;
	gHdDvrUsecaseContext1.ipcInVideoPrm.noNotifyMode              = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.ipcInVideoId, gHdDvrUsecaseContext1.ipcInVideoPrm);

	// encId ---Q0---> ipcBitsOutRTOSId
	multich_hddvr_set_enclink_prm(&gHdDvrUsecaseContext1.encPrm);
	gHdDvrUsecaseContext1.encPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext1.ipcInVideoId;
	gHdDvrUsecaseContext1.encPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.encPrm.outQueParams.nextLink     = gVencModuleContext.ipcBitsOutRTOSId;
	MULTICH_HDDVR_CREATE_LINK(gVencModuleContext.encId, gHdDvrUsecaseContext1.encPrm);

	// ipcBitsOutVideoId ---Q0---> ipcBitsInHostId
	gHdDvrUsecaseContext1.ipcBitsOutVideoPrm.baseCreateParams.inQueParams.prevLinkId    = gVencModuleContext.encId;
	gHdDvrUsecaseContext1.ipcBitsOutVideoPrm.baseCreateParams.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.ipcBitsOutVideoPrm.baseCreateParams.numOutQue                 = 1;
	gHdDvrUsecaseContext1.ipcBitsOutVideoPrm.baseCreateParams.outQueParams[0].nextLink  = gVencModuleContext.ipcBitsInHLOSId;
	MultiCh_ipcBitsInitCreateParams_BitsOutRTOS(&gHdDvrUsecaseContext1.ipcBitsOutVideoPrm, TRUE);
	gHdDvrUsecaseContext1.ipcBitsInHostPrm[0].baseCreateParams.inQueParams.prevLinkId    = gVencModuleContext.ipcBitsOutRTOSId;
	gHdDvrUsecaseContext1.ipcBitsInHostPrm[0].baseCreateParams.inQueParams.prevLinkQueId = 0;
	MULTICH_HDDVR_CREATE_LINK(gVencModuleContext.ipcBitsOutRTOSId, gHdDvrUsecaseContext1.ipcBitsOutVideoPrm);

	// 
	MultiCh_ipcBitsInitCreateParams_BitsInHLOS(&gHdDvrUsecaseContext1.ipcBitsInHostPrm[0]);
	MULTICH_HDDVR_CREATE_LINK(gVencModuleContext.ipcBitsInHLOSId, gHdDvrUsecaseContext1.ipcBitsInHostPrm[0]);
}

Void multich_hddvr_connect_decode_links()
{
	// ipcBitsOutHostId ---Q0---> ipcBitsInRtosId
	multich_hddvr_set_ipcbitsout_hlos_prms(&gHdDvrUsecaseContext1.ipcBitsOutHostPrm);
	gHdDvrUsecaseContext1.ipcBitsOutHostPrm.baseCreateParams.outQueParams[0].nextLink    = gVdecModuleContext.ipcBitsInRTOSId;
	MULTICH_HDDVR_CREATE_LINK(gVdecModuleContext.ipcBitsOutHLOSId, gHdDvrUsecaseContext1.ipcBitsOutHostPrm);

	// ipcBitsInRtosId ---Q0---> decId
	gHdDvrUsecaseContext1.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkId      = gVdecModuleContext.ipcBitsOutHLOSId;
	gHdDvrUsecaseContext1.ipcBitsInVideoPrm.baseCreateParams.inQueParams.prevLinkQueId   = 0;
	gHdDvrUsecaseContext1.ipcBitsInVideoPrm.baseCreateParams.numOutQue                    = 1;
	gHdDvrUsecaseContext1.ipcBitsInVideoPrm.baseCreateParams.outQueParams[0].nextLink     = gVdecModuleContext.decId;
	MultiCh_ipcBitsInitCreateParams_BitsInRTOS(&gHdDvrUsecaseContext1.ipcBitsInVideoPrm, TRUE);
	MULTICH_HDDVR_CREATE_LINK(gVdecModuleContext.ipcBitsInRTOSId, gHdDvrUsecaseContext1.ipcBitsInVideoPrm);

	// decId---Q0--->ipcOutVideoId
	multich_hddvr_set_declink_prms(&gHdDvrUsecaseContext1.decPrm);
	gHdDvrUsecaseContext1.decPrm.inQueParams.prevLinkId    = gVdecModuleContext.ipcBitsInRTOSId;
	gHdDvrUsecaseContext1.decPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.decPrm.outQueParams.nextLink  = gHdDvrUsecaseContext1.ipcOutVideoId;
	MULTICH_HDDVR_CREATE_LINK(gVdecModuleContext.decId, gHdDvrUsecaseContext1.decPrm);

	// ipcOutVideoId---Q0-->ipcInVpssId
	gHdDvrUsecaseContext1.ipcOutVideoPrm.inQueParams.prevLinkId    = gVdecModuleContext.decId;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.numOutQue                 = 1;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext1.ipcInVpssId;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.notifyNextLink            = FALSE;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.notifyPrevLink            = TRUE;
	gHdDvrUsecaseContext1.ipcOutVideoPrm.noNotifyMode              = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.ipcOutVideoId, gHdDvrUsecaseContext1.ipcOutVideoPrm);

	// ipcInVpssId---Q0--> mergeId[MERGE_DISPLAY]
	gHdDvrUsecaseContext1.ipcInVpssPrm.inQueParams.prevLinkId    = gHdDvrUsecaseContext1.ipcOutVideoId;
	gHdDvrUsecaseContext1.ipcInVpssPrm.inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.ipcInVpssPrm.numOutQue                 = 1;
	gHdDvrUsecaseContext1.ipcInVpssPrm.outQueParams[0].nextLink  = gHdDvrUsecaseContext1.mergeId[MERGE_DISPLAY];
	gHdDvrUsecaseContext1.ipcInVpssPrm.notifyNextLink            = TRUE;
	gHdDvrUsecaseContext1.ipcInVpssPrm.notifyPrevLink            = FALSE;
	gHdDvrUsecaseContext1.ipcInVpssPrm.noNotifyMode              = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.ipcInVpssId, gHdDvrUsecaseContext1.ipcInVpssPrm);
}

#if 0
static void swms0_cfg()
{
	multich_hddvr_set_avsync_prm(&gHdDvrUsecaseContext1.avsyncCfg[0], ETAH_SWMS_ID_HDMI, gHdDvrUsecaseContext1.dupId[DUP_DISPLAY], 0);
	g_swms[ETAH_SWMS_ID_HDMI].inQueParams.prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	g_swms[ETAH_SWMS_ID_HDMI].inQueParams.prevLinkQueId	= 0;
	multich_set_swms_prm(ETAH_SWMS_ID_HDMI);
	g_swms[ETAH_SWMS_ID_HDMI].enableOuputDup	      = FALSE;
	g_swms[ETAH_SWMS_ID_HDMI].enableProcessTieWithDisplay = TRUE;
	g_swms[ETAH_SWMS_ID_HDMI].outQueParams.nextLink 	= gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI];
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI], g_swms[ETAH_SWMS_ID_HDMI]);

	// 显示设备0
	//gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkId 	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkId	= gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].displayRes		= VSYS_STD_1080P_30;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI], gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI]);
}
#else
static void swms0_cfg(int prevLinkQueId)
{
	multich_hddvr_set_avsync_prm(&gHdDvrUsecaseContext1.avsyncCfg[0], ETAH_SWMS_ID_HDMI, gHdDvrUsecaseContext1.dupId[DUP_DISPLAY], 0);
	g_swms[ETAH_SWMS_ID_HDMI].inQueParams.prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	g_swms[ETAH_SWMS_ID_HDMI].inQueParams.prevLinkQueId	= prevLinkQueId;
	multich_set_swms_prm(ETAH_SWMS_ID_HDMI);
	g_swms[ETAH_SWMS_ID_HDMI].enableOuputDup	      = FALSE;
	g_swms[ETAH_SWMS_ID_HDMI].enableProcessTieWithDisplay = TRUE;
	g_swms[ETAH_SWMS_ID_HDMI].outQueParams.nextLink		= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE];
	//g_swms[ETAH_SWMS_ID_HDMI].outQueParams.nextLink		= gVcapModuleContext.deiId[DEIHQ_Q_RES];
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI], g_swms[ETAH_SWMS_ID_HDMI]);

	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].inQueParams.prevLinkId	 = gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].numOutQue			 = 2;
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].outQueParams[0].nextLink	 = gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].outQueParams[1].nextLink	 = gVdisModuleContext.displayId[1];
	//gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].outQueParams[2].nextLink	 = gVcapModuleContext.deiId[DEIHQ_Q_RES];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE].notifyNextLink		 = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE],gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY_TO_ENCODE]);

	// 显示设备0
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkId 	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].displayRes		= VSYS_STD_1080P_30;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI], gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI]);

	// 显示设备1
	gHdDvrUsecaseContext1.displayPrm[1].inQueParams[0].prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE];
	gHdDvrUsecaseContext1.displayPrm[1].inQueParams[0].prevLinkQueId	= 1;
	gHdDvrUsecaseContext1.displayPrm[1].displayRes		= VSYS_STD_1080P_30;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[1], gHdDvrUsecaseContext1.displayPrm[1]);

/*
	// 降噪给拼接编码
	DeiLink_OutputScaleFactor outScaleFactorDeiSc, outScaleFactorVipSc;
	outScaleFactorVipSc.scaleMode = DEI_SCALE_MODE_ABSOLUTE;	// 主码流
	outScaleFactorVipSc.absoluteResolution.outWidth  = 1920;
	outScaleFactorVipSc.absoluteResolution.outHeight = 1080;
	outScaleFactorDeiSc.scaleMode = DEI_SCALE_MODE_ABSOLUTE;	// 次码流
	outScaleFactorDeiSc.absoluteResolution.outWidth  = 1280;
	outScaleFactorDeiSc.absoluteResolution.outHeight = 720;
	multich_hddvr_set_dei_prm(&gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES], &outScaleFactorDeiSc, &outScaleFactorVipSc);
	//gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkId    = gHdDvrUsecaseContext1.dupId[DUP_DISPLAY_TO_ENCODE];
	//gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkQueId = 2;
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkId    = gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].outQueParams[DEI_LINK_OUT_QUE_VIP_SC].nextLink = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].outQueParams[DEI_LINK_OUT_QUE_DEI_SC].nextLink = gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE];
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.deiId[DEIHQ_Q_RES], gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES]);

	multich_hddvr_set_nsf_prm(&gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE], NUM_BUFS_PER_CH_ENC_PRI, 30);
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].inQueParams.prevLinkId	  = gVcapModuleContext.deiId[DEIHQ_Q_RES];
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].inQueParams.prevLinkQueId = DEI_LINK_OUT_QUE_DEI_SC;
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].outQueParams[0].nextLink  = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE], gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE]);
	System_linkStart(gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE]);
*/
}
#endif

#define MAX_SD_PRIMARY_WIDTH           (720)
#define MAX_SD_PRIMARY_HEIGHT          (480)

static void swms1_cfg(int prevLinkQueId)
{
	// 拼接器1: 导播
	g_swms[ETAH_SWMS_ID_MOSAIC].inQueParams.prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	g_swms[ETAH_SWMS_ID_MOSAIC].inQueParams.prevLinkQueId	= prevLinkQueId;
	multich_set_swms_prm(ETAH_SWMS_ID_MOSAIC);
	g_swms[ETAH_SWMS_ID_MOSAIC].enableOuputDup		= FALSE;
	g_swms[ETAH_SWMS_ID_MOSAIC].enableProcessTieWithDisplay = FALSE;
	//g_swms[ETAH_SWMS_ID_MOSAIC].outQueParams.nextLink		= gVcapModuleContext.deiId[DEIHQ_Q_RES];
	g_swms[ETAH_SWMS_ID_MOSAIC].outQueParams.nextLink		= gHdDvrUsecaseContext1.dupId[DUP_Q_RES_CAPTURE];
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.swMsId[ETAH_SWMS_ID_MOSAIC], g_swms[ETAH_SWMS_ID_MOSAIC]);

#if 1
	gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].inQueParams.prevLinkId	 = gVdisModuleContext.swMsId[ETAH_SWMS_ID_MOSAIC];
	gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].numOutQue			 = 2;
	gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].outQueParams[0].nextLink	 = gVcapModuleContext.deiId[DEIHQ_Q_RES];
	//gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].outQueParams[1].nextLink	 = gVdisModuleContext.displayId[ETAH_SWMS_ID_SD];
	gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].outQueParams[1].nextLink	 = gVcapModuleContext.sclrId[0];
	gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE].notifyNextLink		 = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.dupId[DUP_Q_RES_CAPTURE],gHdDvrUsecaseContext1.dupPrm[DUP_Q_RES_CAPTURE]);

	gHdDvrUsecaseContext1.sclrPrm.enableLineSkipSc	= FALSE;
	gHdDvrUsecaseContext1.sclrPrm.inputFrameRate	= 30;
	gHdDvrUsecaseContext1.sclrPrm.outputFrameRate	= 30;
	gHdDvrUsecaseContext1.sclrPrm.inQueParams.prevLinkId	  = gHdDvrUsecaseContext1.dupId[DUP_Q_RES_CAPTURE];
	gHdDvrUsecaseContext1.sclrPrm.inQueParams.prevLinkQueId = 1;
	gHdDvrUsecaseContext1.sclrPrm.outQueParams.nextLink	  = gVdisModuleContext.displayId[ETAH_SWMS_ID_SD];
	/*
	gHdDvrUsecaseContext1.sclrPrm.scaleMode = DEI_SCALE_MODE_RATIO;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.ratio.heightRatio.numerator   = 2;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.ratio.heightRatio.denominator = 1;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.ratio.widthRatio.numerator    = 2;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.ratio.widthRatio.denominator  = 1;
	*/
	gHdDvrUsecaseContext1.sclrPrm.scaleMode = DEI_SCALE_MODE_ABSOLUTE;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.absoluteResolution.outWidth  = MAX_SD_PRIMARY_WIDTH;
	gHdDvrUsecaseContext1.sclrPrm.outScaleFactor.absoluteResolution.outHeight = MAX_SD_PRIMARY_HEIGHT;
	gHdDvrUsecaseContext1.sclrPrm.tilerEnable = FALSE; // force tiler disable;
	gHdDvrUsecaseContext1.sclrPrm.numBufsPerCh = 6;
	System_linkCreate(gVcapModuleContext.sclrId[0], &gHdDvrUsecaseContext1.sclrPrm, sizeof(gHdDvrUsecaseContext1.sclrPrm));

	// 显示器sd
	//gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_Q_RES_CAPTURE];
	//gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkQueId	= 1;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkId	= gVcapModuleContext.sclrId[0];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].displayRes		= ETAH_DISPLAY_STD_NTSC;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[ETAH_SWMS_ID_SD], gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD]);
#endif

	// 降噪给拼接编码
	DeiLink_OutputScaleFactor outScaleFactorDeiSc, outScaleFactorVipSc;
	outScaleFactorVipSc.scaleMode = DEI_SCALE_MODE_ABSOLUTE;	// 主码流
	outScaleFactorVipSc.absoluteResolution.outWidth  = 1920;
	outScaleFactorVipSc.absoluteResolution.outHeight = 1080;
	outScaleFactorDeiSc.scaleMode = DEI_SCALE_MODE_ABSOLUTE;	// 次码流
	outScaleFactorDeiSc.absoluteResolution.outWidth  = 1280;
	outScaleFactorDeiSc.absoluteResolution.outHeight = 720;
	multich_hddvr_set_dei_prm(&gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES], &outScaleFactorDeiSc, &outScaleFactorVipSc);
	//gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkId    = gVdisModuleContext.swMsId[ETAH_SWMS_ID_MOSAIC];
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkId    = gHdDvrUsecaseContext1.dupId[DUP_Q_RES_CAPTURE];
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].inQueParams.prevLinkQueId = 0;
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].outQueParams[DEI_LINK_OUT_QUE_VIP_SC].nextLink = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
	gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES].outQueParams[DEI_LINK_OUT_QUE_DEI_SC].nextLink = gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE];
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.deiId[DEIHQ_Q_RES], gHdDvrUsecaseContext1.deiPrm[DEIHQ_Q_RES]);

	multich_hddvr_set_nsf_prm(&gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE], NUM_BUFS_PER_CH_ENC_PRI, 30);
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].inQueParams.prevLinkId	  = gVcapModuleContext.deiId[DEIHQ_Q_RES];
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].inQueParams.prevLinkQueId = DEI_LINK_OUT_QUE_DEI_SC;
	gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE].outQueParams[0].nextLink  = gHdDvrUsecaseContext1.mergeId[MERGE_ENCODE];
	MULTICH_HDDVR_CREATE_LINK(gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE], gHdDvrUsecaseContext1.nsfPrm[NSF_MOSAIC_ENCODE]);
	System_linkStart(gVcapModuleContext.nsfId[NSF_MOSAIC_ENCODE]);
}

static void swms2_cfg(int prevLinkQueId)
{
	// 拼接器1: cvbs
	g_swms[ETAH_SWMS_ID_SD].inQueParams.prevLinkId	= gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	g_swms[ETAH_SWMS_ID_SD].inQueParams.prevLinkQueId	= prevLinkQueId;
	multich_set_swms_prm(ETAH_SWMS_ID_SD);
	g_swms[ETAH_SWMS_ID_SD].maxOutRes			= VSYS_STD_NTSC;
	g_swms[ETAH_SWMS_ID_SD].initOutRes			= VSYS_STD_NTSC;
	g_swms[ETAH_SWMS_ID_SD].outQueParams.nextLink		= gVdisModuleContext.displayId[ETAH_SWMS_ID_SD];
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.swMsId[ETAH_SWMS_ID_SD], g_swms[ETAH_SWMS_ID_SD]);

	// 显示器1
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkId 	= gVdisModuleContext.swMsId[ETAH_SWMS_ID_SD];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD].displayRes		= ETAH_DISPLAY_STD_NTSC;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[ETAH_SWMS_ID_SD], gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_SD]);
}

Void multich_hddvr_connect_display_links()
{
	// 拼接来源: 第一份是解码，第二份是本地视频输入
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].numInQue = 2;
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].inQueParams[0].prevLinkId    = gHdDvrUsecaseContext1.dupId[DUP_FULL_RES_CAPTURE];		// 采集
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].inQueParams[0].prevLinkQueId = 0;
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].inQueParams[1].prevLinkId    = gHdDvrUsecaseContext1.ipcInVpssId;				// 解码
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].inQueParams[1].prevLinkQueId = 0;
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].outQueParams.nextLink        = gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY].notifyNextLink               = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.mergeId[MERGE_DISPLAY],gHdDvrUsecaseContext1.mergePrm[MERGE_DISPLAY]);

	// 复制给2个或3个拼接器
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].inQueParams.prevLinkId       = gHdDvrUsecaseContext1.mergeId[MERGE_DISPLAY];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].numOutQue                      = 2;
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].outQueParams[0].nextLink       = gVdisModuleContext.swMsId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].outQueParams[1].nextLink       = gVdisModuleContext.swMsId[ETAH_SWMS_ID_MOSAIC];
	//gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].outQueParams[1].nextLink       = gVdisModuleContext.swMsId[ETAH_SWMS_ID_SD];
	//gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].outQueParams[1].nextLink       = gHdDvrUsecaseContext1.selectId[SELECT_FOR_DISPLAY];
	gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY].notifyNextLink                 = TRUE;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.dupId[DUP_DISPLAY],gHdDvrUsecaseContext1.dupPrm[DUP_DISPLAY]);

	swms0_cfg(0);
	swms1_cfg(1);
	//swms2_cfg(1);
/*
	// 4路编码: 分给两个dei处理: deihq和dei
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].numOutQue = 1;
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].inQueParams.prevLinkId    = gHdDvrUsecaseContext1.dupId[DUP_DISPLAY];
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].inQueParams.prevLinkQueId = 1;
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueParams[0].nextLink  = gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI];
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].outQueId  = 0;
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].numOutCh  = 1;
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].inChNum[0]= 0;
	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].inChNum[0]= 4;
	MULTICH_HDDVR_CREATE_LINK(gHdDvrUsecaseContext1.selectId[SELECT_FOR_DISPLAY], gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY]);

	// 显示设备0
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkId 	= gHdDvrUsecaseContext1.selectId[SELECT_FOR_DISPLAY];
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].inQueParams[0].prevLinkQueId	= 0;
	gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI].displayRes		= VSYS_STD_1080P_30;
	MULTICH_HDDVR_CREATE_LINK(gVdisModuleContext.displayId[ETAH_SWMS_ID_HDMI], gHdDvrUsecaseContext1.displayPrm[ETAH_SWMS_ID_HDMI]);
*/

	//dpline_stop();
}

// 参考sdk的selectDeiLiveChs()
void switch_display(int channel)
{
	Int32 status1 = System_linkControl(gHdDvrUsecaseContext1.selectId[SELECT_FOR_DISPLAY],
				    SELECT_LINK_CMD_GET_OUT_QUE_CH_INFO,
				    &gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY],
				    sizeof(gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY]),
				    TRUE);

	gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].inChNum[0]= channel;

	Int32 status2 = System_linkControl(gHdDvrUsecaseContext1.selectId[SELECT_FOR_DISPLAY],
				    SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO,
				    &gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY],
				    sizeof(gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY]),
				    TRUE);
	printf("switch_display() status1: %d, status2: %d, channel: %d, ----------%d\n"
		, status1, status2, channel
		, gHdDvrUsecaseContext1.selectPrm[SELECT_FOR_DISPLAY].outQueChInfo[0].numOutCh
		);
}

