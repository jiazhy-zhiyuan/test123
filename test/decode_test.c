
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "rtmp/Struct.h"
#include "rtmp/RtmpInterface.h"
#include <sys/time.h>
#include <pthread.h>

#define KEY_OFFSET	4
#define STAMP_DISPLAY_RANGE		60
#define TM_AUTO_CONN		1
#define WM_AUTO_CONN		WM_USER+101
#define AUTO_CONN_SECONDS	1000 * 10  // 10��


void my_printf(const char * fmt,...);
void Play();
void Release();
void Connect();
PCONN_INFO pConnInfo = NULL;
long video_packet_count=1;
long audio_packet_count=1;


#include "decode.h"
#include "split.h"
#include "encode.h"
#include "common.h"
#include "system.h"

#define VSYS_STD_1080P_60 13

//extern "C" void SystemInit();
//extern "C" void SystemSetProductID(const char *productID);


void *test_set_split_11_thread(void *arg)
{
	VIDEO_RECT rect[SWMS_MAX_WIN_PER_LINK];

	// 1���󴰿�
	rect[0].channelNum = 0;
	rect[0].startX = 0;
	rect[0].startY = 0;
	rect[0].width = 1920 * 4 / 4 + 0;
	rect[0].height = 1080 * 4 / 4 + 0;

	SplitSetCompositorMosaic(0, 1, rect);
	SplitSetCompositorMosaic(1, 1, rect);
	sleep(9999999);
	return NULL;
}




int main2(int argc, char *argv[])
{
  #if 1
	SystemInit();
	SystemSetProductID("ESVR-6000");
	DecodeInit(0);
	DecodeInit(1);
	DecodeInit(2);
	DecodeInit(3);
	DecodeStart(0);	
	//pthread_t tid = 0;
	//pthread_create(&tid, NULL, test_set_split_11_thread, NULL);
	#endif
	
	Play();
	for(;;);
}


BOOL IsKeyFrame(char* buf, long size)
{
	if(size < 10)
		return FALSE;
	int i ;
	for( i = 4; i<size-6; i++)
	{
		if(buf[i] == 0x67 || (buf[i] & 0x1f) == 0x05) 
		{
			if(buf[i-4] == 0 && buf[i-3] == 0 && buf[i-2] == 0 && buf[i-1] == 1)
				return TRUE;
		}
	}
	
	return FALSE;
}


long StreamOutV(void* hOut, char* buf, long size, int timmer)
{
	printf("vsize=%ld\n",size);
	DecodePutBuffer(0,buf,size);
	return size;
}

long StreamOutA(void* hOut, char* buf, long size, int timmer)
{
	return size;
}

void Play()
{
	Release();
	Connect();
	if(NULL == pConnInfo)
	{
		return;
	}
	RtmpSDK_SetStreamName(pConnInfo, NULL);   
	RtmpSDK_SetVideoOut(pConnInfo, StreamOutV, pConnInfo);
	RtmpSDK_SetAudioOut(pConnInfo, StreamOutA, pConnInfo);
	RtmpSDK_StreamControl(pConnInfo, StreamSTART);
}

void Stop()
{		
	if (NULL == pConnInfo)
	{
		return;
	}

	RtmpSDK_StreamControl(pConnInfo, StreamSTOP);
}

void Release()
{
	Stop();

	if (pConnInfo)
	{			
		RtmpSDK_StreamControl(pConnInfo, Disconnect);			
		RtmpSDK_ReleaseConnInfo(pConnInfo);
		pConnInfo = NULL;	 //�������ⲿ����������Ϊ��
	}
}

void Connect()
{	
	PCONN_INFO conn = RtmpSDK_CreateConnInfo();
	conn->hWndPlayer = NULL;
	conn->bHasAudio = FALSE;
	
	char url[]="rtmp://172.16.1.125/teach_app/130318TGC00004_h"; //FMS4.5����֧�ֵĲ�̫�ã���Ϊ����Ƶ����Ƶ�ľۺϰ�

	RtmpSDK_Connect(conn, url);
	my_printf("Play url = %s \n",url);
	
	if(NULL == conn->pConn)
	{
		RtmpSDK_Connect(conn, url);
		if(NULL == conn->pConn)
		{
			RtmpSDK_Connect(conn, url);
			if(NULL == conn->pConn)
			{
				my_printf("ERROR Cann't Connect Server,url=%s\n",url);
				return;
			}
		}
	}
	pConnInfo = conn;
}

 

/*�Զ��岻��������ӡ���*/
/* #include <stdarg.h> */
void my_printf(const char * fmt,...)
{
	va_list _ap;
	va_start(_ap,fmt);
	char _tmp[500]={0};
	//sprintf(_tmp,"%s",fmt);
	//printf(_tmp,_ap);//���������ֱ�����		
	//����൱���ǽ�fmt��ʽ��_ap������ʽ����_tmp��,��sprintf�е�����,����vsnprintf���������һ��������va_list���͵�
	vsnprintf(_tmp, sizeof(_tmp)-1, fmt, _ap); 
	va_end(_ap);	
	printf("%s",_tmp);
}
