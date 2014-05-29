//Rtmp C Interface add by zyf 2008.12.8
#ifndef RTMP_INTERFACE_H
#define RTMP_INTERFACE_H


#ifdef WIN32
	#ifdef DEMO
		#define RTMPSDK_API 
	#else
		#ifdef RTMPSDK_EXPORTS
			#define RTMPSDK_API __declspec(dllexport)
		#else
			#define RTMPSDK_API __declspec(dllimport)
		#endif
	#endif
#else
	#define RTMPSDK_API   
#endif


#ifdef __cplusplus 
extern "C" { 
#endif

RTMPSDK_API PCONN_INFO RtmpSDK_CreateConnInfo();
RTMPSDK_API void* RtmpSDK_CreateMetaData();//创建MetaData
RTMPSDK_API int RtmpSDK_ReleaseConnInfo(PCONN_INFO pServer);//断开连接释放资源
RTMPSDK_API int RtmpSDK_Connect(PCONN_INFO pConnInfo,const char* strUrl);//连接FMS服务器
RTMPSDK_API int RtmpSDK_ConnectAdmin(PCONN_INFO pConnInfo,const char* strUrl,const char* strLogin,const char* strPswd);//连接FMS admin server
RTMPSDK_API int RtmpSDK_SetStreamName(PCONN_INFO pConnInfo,const char*  strStreamName);//更换播放流名字
RTMPSDK_API int RtmpSDK_SetVideoOut(PCONN_INFO pConnInfo, FunStreamOut fnStreamOut,void* hOut);//视频播放 设置回调
RTMPSDK_API int RtmpSDK_SetAudioOut(PCONN_INFO serverInfo, FunStreamOut fnStreamOut, void* hOut);//音频播放 设置回调
RTMPSDK_API int RtmpSDK_SetMsgCallBack(PCONN_INFO pConnInfo, FunCallBack fnCallBack);//消息回调
RTMPSDK_API int RtmpSDK_SetMsgCallBackEx(PCONN_INFO pConnInfo, FunCallBackEx fnCallBack, void* hOut);//消息回调 带参数
RTMPSDK_API int RtmpSDK_CallServer(PCONN_INFO pConnInfo,const char* params[], int paramCount);//调用服务器方法
RTMPSDK_API int RtmpSDK_CallTwoway(PCONN_INFO pConnInfo,const char* params[], int paramCount, char*  strResultBuf, int nBufLen);//阻塞方式调用服务器方法 strResult对应C#中的StringBuild 
RTMPSDK_API int RtmpSDK_StreamControl(PCONN_INFO pConnInfo, RtmpControlType controlType);//流控制，例如 播放 停止 录制 追加 等
RTMPSDK_API int RtmpSDK_SendStream(PCONN_INFO pConnInfo,const char*  buf,  int size,  int dataType,  int timeStamp);//发送音视频数据 输入的H.264视频头0x00000001 aac音频头0xFFF1
RTMPSDK_API int RtmpSDK_SetDbgOut(PCONN_INFO pConnInfo, BOOL dbgPrint, BOOL dbgLog);//日志开关 是否打印 是否纪录到文件
RTMPSDK_API int RtmpSDK_GetConnState(PCONN_INFO pConnInfo);//获取rtmp连接状态
RTMPSDK_API int RtmpSDK_AddMetaData(void* pMetaData, const char* strKey, const char* strValue);//添加MetaData数据
RTMPSDK_API int RtmpSDK_AddMetaDataDouble(void* pMetaData, const char* strKey, double dValue);//
RTMPSDK_API int RtmpSDK_SetMetaData(PCONN_INFO pConnInfo,void* pMetaData);//设置MetaData 在publish之后调用
RTMPSDK_API int RtmpSDK_GetVersion(PCONN_INFO pConnInfo, char*  strResultBuf);//获取版本
RTMPSDK_API int RtmpSDK_SetStreamFmt(PCONN_INFO pConnInfo, StreamFormat fmt);//设置流封装格式

#ifdef __cplusplus
} 
#endif
#endif /* end define H */
