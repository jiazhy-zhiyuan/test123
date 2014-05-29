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
RTMPSDK_API void* RtmpSDK_CreateMetaData();//����MetaData
RTMPSDK_API int RtmpSDK_ReleaseConnInfo(PCONN_INFO pServer);//�Ͽ������ͷ���Դ
RTMPSDK_API int RtmpSDK_Connect(PCONN_INFO pConnInfo,const char* strUrl);//����FMS������
RTMPSDK_API int RtmpSDK_ConnectAdmin(PCONN_INFO pConnInfo,const char* strUrl,const char* strLogin,const char* strPswd);//����FMS admin server
RTMPSDK_API int RtmpSDK_SetStreamName(PCONN_INFO pConnInfo,const char*  strStreamName);//��������������
RTMPSDK_API int RtmpSDK_SetVideoOut(PCONN_INFO pConnInfo, FunStreamOut fnStreamOut,void* hOut);//��Ƶ���� ���ûص�
RTMPSDK_API int RtmpSDK_SetAudioOut(PCONN_INFO serverInfo, FunStreamOut fnStreamOut, void* hOut);//��Ƶ���� ���ûص�
RTMPSDK_API int RtmpSDK_SetMsgCallBack(PCONN_INFO pConnInfo, FunCallBack fnCallBack);//��Ϣ�ص�
RTMPSDK_API int RtmpSDK_SetMsgCallBackEx(PCONN_INFO pConnInfo, FunCallBackEx fnCallBack, void* hOut);//��Ϣ�ص� ������
RTMPSDK_API int RtmpSDK_CallServer(PCONN_INFO pConnInfo,const char* params[], int paramCount);//���÷���������
RTMPSDK_API int RtmpSDK_CallTwoway(PCONN_INFO pConnInfo,const char* params[], int paramCount, char*  strResultBuf, int nBufLen);//������ʽ���÷��������� strResult��ӦC#�е�StringBuild 
RTMPSDK_API int RtmpSDK_StreamControl(PCONN_INFO pConnInfo, RtmpControlType controlType);//�����ƣ����� ���� ֹͣ ¼�� ׷�� ��
RTMPSDK_API int RtmpSDK_SendStream(PCONN_INFO pConnInfo,const char*  buf,  int size,  int dataType,  int timeStamp);//��������Ƶ���� �����H.264��Ƶͷ0x00000001 aac��Ƶͷ0xFFF1
RTMPSDK_API int RtmpSDK_SetDbgOut(PCONN_INFO pConnInfo, BOOL dbgPrint, BOOL dbgLog);//��־���� �Ƿ��ӡ �Ƿ��¼���ļ�
RTMPSDK_API int RtmpSDK_GetConnState(PCONN_INFO pConnInfo);//��ȡrtmp����״̬
RTMPSDK_API int RtmpSDK_AddMetaData(void* pMetaData, const char* strKey, const char* strValue);//���MetaData����
RTMPSDK_API int RtmpSDK_AddMetaDataDouble(void* pMetaData, const char* strKey, double dValue);//
RTMPSDK_API int RtmpSDK_SetMetaData(PCONN_INFO pConnInfo,void* pMetaData);//����MetaData ��publish֮�����
RTMPSDK_API int RtmpSDK_GetVersion(PCONN_INFO pConnInfo, char*  strResultBuf);//��ȡ�汾
RTMPSDK_API int RtmpSDK_SetStreamFmt(PCONN_INFO pConnInfo, StreamFormat fmt);//��������װ��ʽ

#ifdef __cplusplus
} 
#endif
#endif /* end define H */
