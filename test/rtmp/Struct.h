#if !defined(RTMP_STRUCT_H)
#define RTMP_STRUCT_H

/************************************************************************
							define                               
************************************************************************/
//const string //d
#define STR_RTMP_VER		"3.130121.01"

//publish metaData
#define METADATA_AUDIO_CHANNELS		"audiochannels"		//音频声道数量
#define METADATA_AUDIO_SAMPLERATE	"audiosamplerate"	//音频采样率 例如：24000
#define METADATA_WIDTH				"width"				//视频宽度
#define METADATA_HEIGHT				"height"			//视频高度
#define METADATA_VIDEO_FRAMERATE	"videoframerate"	//视频帧率

//vod metaData
#define METADATA_DURATION			"duration"			//点播时间长度
#define METADATA_CANSEEK			"canSeekToEnd"		//是否能seek
#define METADATA_CREATEDATE			"creationdate"		//录制时间

//const value
#define FALSE				0
#define TRUE				1
#define FILE_BUF			512

//AMF
#define AUDIO_DATA			0x08
#define VIDEO_DATA			0x09

//Rtmp
#define NO_FLAGS_SET		(0)
#define RTMP_PORT			(1935)

#ifdef WINCE
	#define MAX_PACKET_SIZE		(1024) 
#else
	#define MAX_PACKET_SIZE		(1024*20) 
#endif

#define N_TIME_WAITRESULT	(3000)	//connect改为等待返回方式 最长等待3秒
#define TIMESTAMP_FIX	1


/************************************************************************
							enum                               
************************************************************************/
typedef enum{
	EX_HEAD_BYTE,
	EX_WRITE_FAILUE,
	EX_AMF_SIZE,
	EX_READ_FAILUE,
	EX_UNKNOWN
} MyException;

typedef enum 
{	
	CFG_PUBLISH_VIDIO,
	CFG_PUBLISH_AUDIO,
	CFG_RECEIVE_VIDIO,
	CFG_RECEIVE_AUDIO,
	CFG_LOG_FILE,
	CFG_SERVER,
	CFG_APP,
	CFG_STREAM_NAME,
	CFG_LOGIN_NAME,
	CFG_MAX_NUM 
}ConfigParam;

typedef enum 
{
	START_PUBLISH,
	START_PUBLISH_FLV,
	START_PUBLISH_MIX,
	START_PLAY,
	START_CALL,
	START_NULL
}StartType;

typedef enum {
	Disconnect ,		//断开连接
	StreamSTART ,		//开始播放
    StreamSTOP ,		//停止播放
    StreamPAUSE ,		//暂停播放
    StreamRESUME,		//恢复播放
    StreamFAST,			//快放
    StreamSLOW,			//慢放
    StreamNORMAL,		//正常速度	
	StreamRECORD,		//开始录制
	StreamLIVE,			//开始实时
	StreamAPPEND,		//开始添加
	//StreamLIVEH264,		//开始实时直播H264
}RtmpControlType;

typedef enum{
	DBG_LOG			=	0x0001,
	DBG_BUFFER		=	0x0010,
	DBG_TCPSTREAM	=	0x0100,
} DebugType;

typedef enum{
	FLV,
	MP4,
} StreamFormat;//流媒体封装格式

/************************************************************************
							typedef                               
************************************************************************/
typedef int BOOL;
typedef unsigned int UINT;
typedef void* HANDLE;
typedef int (*FunCallBack)(char* str);//call from server
typedef int (*FunCallBackEx)(void* hOut, char* buf, int  bufLen);//call from server whith handle
typedef long (*FunStreamOut)(void* hOut, char* buf, long bufLen, int timmer);// stream call back

typedef union tagDouble
{
   double dData;
   int nData[2];
}UNION_DOUBLE, *PUNION_DOUBLE;

typedef struct tagHeader 
{
	int nChannelId ;
	int nTimer ;
	int nAMFSize ;
	int nAMFType ;
	int nStreamID;
	//BOOL bTimerRelative;
	BOOL bCreate;
}RTMP_HEADER, *PRTMP_HEADER;

typedef struct tagCONN_INFO
{
	void* pMediaPlayer;
	void* pConn;
	void* hWndPlayer;
	BOOL  bHasAudio;
	char strUrl[FILE_BUF];			//rtmp://127.0.0.1/mediaserver
	char strServerIP[FILE_BUF];		//127.0.0.1
	char strAppName[FILE_BUF];		//mediaserver
	char strStreamName[FILE_BUF];	//streamRecode
	char strLoginName[FILE_BUF];	//""
	char strLoginPswd[FILE_BUF];	//""
	
}CONN_INFO, *PCONN_INFO;

typedef struct tagCALL_RESULT
{
	int nInvokeID;
	volatile BOOL bInvokeComplete;//标志twoway调用结束，可以返回
	volatile BOOL bInvokeSuccess;//返回的结果是成功还是失败
	char* strInvokeName;
	char* strResult;
	int nResultBufLen;
}CALL_RESULT, *PCALL_RESULT;


#endif //STRUCT_H
