#if 1
#include "demo.h"
#include "ti_swosd_logo_224x30_yuv420sp.h"
#include "ti_swosd_logo_224x30_yuv422i.h"
#include "ti_swosd_logo_224x30_rgb.h"
#include "demo_text.h"
#include <time.h>
#include <sys/time.h>

#define OSD_BUF_HEAP_SR_ID          (0)
#define LOGO_WINID                  (0)
#define DATA_WINID                  (1)
#define TIME_WINID                  (2)
#define CHANNEL_NAME_WINID          (3)


#include "font/unicode_cn_420sp_420_30.c"
#include "font/unicode_cn_422i_420_30.c"
#include "font/ascii_420sp_1078_28.c"
#include "font/ascii_422i_1078_28.c"

static UInt8   *osdBufBaseVirtAddr = NULL;
static UInt32   osdTotalBufSize = 0;
static UInt8   *osdChnlNameBaseVirtAddr = NULL;
static UInt32   osdChnlNameBufSize = 0;
static UInt8    *dateWin = 0, *timeWin = 0;
static Bitmap_Info *dynamicFont=NULL;
AlgLink_OsdChWinParams g_osdChParam[ALG_LINK_OSD_MAX_CH];
AlgLink_OsdChBlindWinParams g_osdChBlindParam[ALG_LINK_OSD_MAX_CH];
Vsys_AllocBufInfo bufInfo;
UInt32 osdBufSize;

static int gShowTime[ALG_LINK_OSD_MAX_CH];

extern int __EncodeShowTime(int ichannel, int bShowTime)
{
    printf("[%s] in\n", __func__);
    AlgLink_OsdChWinParams * chWinPrm = &g_osdChParam[ichannel];
    VCAP_PARAMS_S vcapParams;
    Vcap_params_init(&vcapParams);
    chWinPrm->chId = ichannel;
    chWinPrm->winPrm[TIME_WINID].enableWin        = bShowTime ? 1 : 0;
    
    vcapParams.channelParams[ichannel].dynamicParams.osdChWinPrm = &g_osdChParam[ichannel];
    Vcap_setDynamicParamChn(ichannel, &vcapParams.channelParams[ichannel].dynamicParams, VCAP_OSDWINPRM);
    printf("[%s] out\n", __func__);
}

void Demo_updateTime(int signo)
{
    
    static struct tm tmCur;
    static struct tm tmOld=
    {
        .tm_mday = 0,
    };
    time_t timeval ;
    char osdStr[40];
    //the windows attrib is already set in the init function
    //so here we don't really change window attrib.
    AlgLink_OsdWindowPrm dummy;
    UInt32 padingColor[3]={0x0,0x80,0x80};


    switch(signo){
        case SIGALRM:
            time(&timeval) ;

            localtime_r(&timeval, &tmCur);

            //update date only once one day
            if(tmOld.tm_mday != tmCur.tm_mday)
            {
                char temp[40]={0};

                //get day of week from this call only.
                ctime_r(&timeval, temp);

                /* sprintf(osdStr,"%02d-%02d-%02d",(int)tmCur.tm_year+1900 - 2000, */
                        /* (int)tmCur.tm_mon+1,(int)tmCur.tm_mday); */

                //strncat(osdStr,temp,3);

                //Demo_text_draw(*dynamicFont, &dummy, osdStr, strlen(osdStr),
                        /* (char*)dateWin,padingColor); */

                tmOld = tmCur;
            }

                
            sprintf(osdStr,"%02d-%02d-%02d  %02d:%02d:%02d",(int)tmCur.tm_year+1900 - 2000,
                    (int)tmCur.tm_mon+1,(int)tmCur.tm_mday, (int)tmCur.tm_hour,(int)tmCur.tm_min,(int)tmCur.tm_sec);
            
            //update time every time
            Demo_text_draw(*dynamicFont, &dummy, osdStr, strlen(osdStr),
                    (char*)timeWin,padingColor);
            break;
    }
    
}


Int32 Demo_osdInit(UInt32 numCh, UInt16 *osdFormat)
{
    printf("[%s] in \n", __func__);
    int chId, winId, status;
    UInt32 padingColor[3]={0x0,0x80,0x80};
    struct itimerval oneSec;

 
    Vsys_AllocBufInfo bufInfoChnlName;
    UInt32 osdBufSizeY, bufAlign;

    UInt32 bufOffset;
    UInt8 *curVirtAddr;

    for(chId = 0; chId < ALG_LINK_OSD_MAX_CH; ++chId){
        gShowTime[chId] = 1;
    }

    assert(numCh <= ALG_LINK_OSD_MAX_CH);

    osdBufSizeY = DEMO_OSD_WIN_PITCH_H*DEMO_OSD_WIN_PITCH_V;

    if(osdFormat[0] == SYSTEM_DF_RGB24_888)
       osdBufSize = osdBufSizeY * 3 ;  /* For RGB888 - 24 bit support */
    else
       osdBufSize = osdBufSizeY * 2 * 2;

    /* All channels share the same OSD window buffers, this is just for demo, actually each CH
       can have different OSD buffers
       */
    osdTotalBufSize = osdBufSize * DEMO_OSD_NUM_WINDOWS;
    bufAlign = 128;

    status = Vsys_allocBuf(OSD_BUF_HEAP_SR_ID, osdTotalBufSize, bufAlign, &bufInfo);
    OSA_assert(status==OSA_SOK);

    /* alloc memory for win 4, the channel name window */
    osdChnlNameBufSize = osdBufSize * numCh;

    status = Vsys_allocBuf(OSD_BUF_HEAP_SR_ID, osdChnlNameBufSize, bufAlign, &bufInfoChnlName);
    OSA_assert(status==OSA_SOK);


    osdBufBaseVirtAddr = bufInfo.virtAddr;
    osdChnlNameBaseVirtAddr = bufInfoChnlName.virtAddr;

    for(chId = 0; chId < numCh; chId++)
    {
        AlgLink_OsdChWinParams * chWinPrm = &g_osdChParam[chId];

        AlgLink_OsdChBlindWinParams *chBlindWinPrm = &g_osdChBlindParam[chId];

        chWinPrm->chId = chId;
        if(osdFormat[chId] == SYSTEM_DF_RGB24_888)
           chWinPrm->numWindows = 1;
        else
           chWinPrm->numWindows = DEMO_OSD_NUM_WINDOWS;

        chWinPrm->colorKey[0] = 0;// 0xfa; /* Y */
        chWinPrm->colorKey[1] = 0; //x7d; /* U */
        chWinPrm->colorKey[2] = 0; //x7d; /* V */

        chBlindWinPrm->chId = chId;
        chBlindWinPrm->numWindows = DEMO_OSD_NUM_BLIND_WINDOWS;

        for(winId=0; winId < chWinPrm->numWindows; winId++)
        {
            //if(winId != DATA_WINID && winId != TIME_WINID)continue;
            chWinPrm->winPrm[winId].startX             = DEMO_OSD_WIN0_STARTX ;
            chWinPrm->winPrm[winId].startY             = DEMO_OSD_WIN0_STARTY ; //+ 2 * (DEMO_OSD_WIN_HEIGHT+DEMO_OSD_WIN0_STARTY)*winId;
            chWinPrm->winPrm[winId].width              = 2 * 0; //DEMO_OSD_WIN_WIDTH;
            chWinPrm->winPrm[winId].height             = 2 * 0; //DEMO_OSD_WIN_HEIGHT;
            chWinPrm->winPrm[winId].lineOffset         = DEMO_OSD_WIN_PITCH_H;
            if(winId != CHANNEL_NAME_WINID)
                chWinPrm->winPrm[winId].globalAlpha        = DEMO_OSD_GLOBAL_ALPHA/(winId + 1);
            else
                chWinPrm->winPrm[winId].globalAlpha        = DEMO_OSD_GLOBAL_ALPHA;

            if(winId == CHANNEL_NAME_WINID)
                chWinPrm->winPrm[winId].globalAlpha        = 0;

            if(winId == LOGO_WINID)
                chWinPrm->winPrm[winId].globalAlpha        = 0;

            if(winId == DATA_WINID)
                chWinPrm->winPrm[winId].globalAlpha = 0;
            
            chWinPrm->winPrm[winId].transperencyEnable = DEMO_OSD_TRANSPARENCY;
            chWinPrm->winPrm[winId].enableWin          = DEMO_OSD_ENABLE_WIN;

            chBlindWinPrm->winPrm[winId].startX        = DEMO_OSD_WIN_WIDTH + 4 + DEMO_OSD_WIN0_STARTX ;
            chBlindWinPrm->winPrm[winId].startY        = DEMO_OSD_WIN0_STARTY + (DEMO_OSD_WIN_HEIGHT+DEMO_OSD_WIN0_STARTY)*winId;
            chBlindWinPrm->winPrm[winId].width         = 40;
            chBlindWinPrm->winPrm[winId].height        = DEMO_OSD_WIN_HEIGHT;
            chBlindWinPrm->winPrm[winId].fillColorYUYV = 0x80008000;
            chBlindWinPrm->winPrm[winId].enableWin     = DEMO_OSD_ENABLE_WIN;


            // winId == 3 is channel name window
            // each channel name window have it's own buf
            if(winId != CHANNEL_NAME_WINID)
            {
                bufOffset = osdBufSize * winId;

                chWinPrm->winPrm[winId].addr[0][0] = (bufInfo.physAddr + bufOffset);

                curVirtAddr = bufInfo.virtAddr + bufOffset;
            }
            else
            {
                bufOffset = osdBufSize * chId;
                chWinPrm->winPrm[winId].addr[0][0] = (bufInfoChnlName.physAddr + bufOffset);
                curVirtAddr = bufInfoChnlName.virtAddr + bufOffset;
            }

            /* copy logo to buffer  */
            if(osdFormat[chId] == SYSTEM_DF_YUV420SP_UV)
            {

                if (winId != LOGO_WINID)
                    dynamicFont = &ascii_420sp_1078_28;
                chWinPrm->winPrm[winId].format     = SYSTEM_DF_YUV420SP_UV;
                if (winId == LOGO_WINID)
                {
                    chWinPrm->winPrm[winId].addr[0][1] =  chWinPrm->winPrm[winId].addr[0][0] + osdBufSizeY;
                    OSA_assert(sizeof(gMCFW_swosdTiLogoYuv420sp)<= osdBufSize);
                    //memcpy(curVirtAddr, gMCFW_swosdTiLogoYuv420sp, sizeof(gMCFW_swosdTiLogoYuv420sp));
                }

                else if (winId == DATA_WINID)
                {
                    Demo_text_draw(*dynamicFont, &chWinPrm->winPrm[winId],
                                   "12-06-15", 8, (char*)curVirtAddr,padingColor);
                    dateWin = curVirtAddr;
                }
                else if (winId == TIME_WINID)
                {
                    Demo_text_draw(*dynamicFont, &chWinPrm->winPrm[winId],
                                   "12-06-15  00:00:00", 18, (char*)curVirtAddr,padingColor);
                    timeWin = curVirtAddr;
                }
                else if (winId == CHANNEL_NAME_WINID)
                {
                    char cnExample[20] = "ͨ��";
                    char channel[6];
                    unsigned int length = strlen(cnExample);

                    sprintf(channel,"%02d",chId);

                    cnExample[length++] = channel[0];
                    cnExample[length++] = 0;
                    cnExample[length++] = channel[1];
                    cnExample[length++] = 0;

                    //Demo_text_draw(cn_420sp_420_30, &chWinPrm->winPrm[winId],
                    /* cnExample, length/2, (char*)curVirtAddr,padingColor); */
                }
                //printf("dynamicFont : <%d - %d>\n", dynamicFont->height, dynamicFont->widthList[0]);

            }
          
            //printf("winParam : <%d - %d>\n", chWinPrm->winPrm[winId].height, chWinPrm->winPrm[winId].width);
        }
    }
    
    if(dynamicFont)
    {
        
        signal(SIGALRM, Demo_updateTime);
        oneSec.it_value.tv_sec = 1;
        oneSec.it_value.tv_usec = 0;
        oneSec.it_interval.tv_sec = 1;
        oneSec.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &oneSec, NULL);
    }
    printf("[%s] out \n", __func__);
    return status;
}

Void Demo_osdDeinit()
{
    if(osdBufBaseVirtAddr != NULL)
    {
        Vsys_freeBuf(OSD_BUF_HEAP_SR_ID, osdBufBaseVirtAddr, osdTotalBufSize);
    }
    if(osdChnlNameBaseVirtAddr != NULL)
    {
        Vsys_freeBuf(OSD_BUF_HEAP_SR_ID, osdChnlNameBaseVirtAddr, osdChnlNameBufSize);
    }

    if(dynamicFont)
    {
        struct itimerval stop;
        signal(SIGALRM, SIG_DFL);
        stop.it_value.tv_sec = 0;
        stop.it_value.tv_usec = 0;
        stop.it_interval.tv_sec = 0;
        stop.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &stop, NULL);
    }
}
#endif
