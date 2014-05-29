/*
 
			  ,.---.   
		,,,,	 /    _ `.
		 \\\\	/      \  )
		  |||| /\/``-.__\/
		  ::::/\/_
  {{`-.__.-'(`(^^(^^^(^ 9 `.========='
 {{{{{{ { ( ( (  (   (-----:=
  {{.-'~~'-.(,(,,(,,,(__6_.'=========.
		  ::::\/\ 
		  |||| \/\  ,-'/\
		 ////	\ `` _/  )
		''''	 \  `	/
			  `---''

 */
#ifndef __SYSTEM_ETAH_20130412_H_
#define __SYSTEM_ETAH_20130412_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VI_CHN		8
#define MAX_DE_CHN		16

typedef struct {
	int		vi_channel_num;				// ���زɼ�·��, �������ģ����ܺ�select link�й�!
	int		decode_channel_num;			// ����·��
	int		stream_type;				// 1��ֻ����������2������������

	int		swms_encode_num;			// ƴ�ӵ���·��: ֻ�б���

	int		swms_display_num;			// ƴ����ʾ·��: ֻ����ʾ����������4��swms_support_������ӵ��ܺ�
	int		swms_support_hdmi;
	int		swms_support_ypbpr;
	int		swms_support_dvo2;
	int		swms_support_sd;

	int		ai_channel_num;				// ��Ƶ����·��
	int		ao_channel_num;				// ��Ƶ���·��
	int		ao_device_num;				// ��Ƶ����豸����(hdmi,3106)
	int		decode_max_width;			// �������������
	int		decode_max_height;			// �����������߶�

	int		osd_win_max_width;			// osd�����
	int		osd_win_max_height;			// osd���߶�
	int		osd_win_max_window;			// osd������
} DEVICE_CAPABILITY;

typedef struct {
	// ��Ƶ����
	int		video_encode_cnt[MAX_VI_CHN][2];	// ������������������ܹ�������С
	long long	video_encode_size[MAX_VI_CHN][2];

	// ��Ƶ����
	int		video_decode_cnt[MAX_DE_CHN];		// ����ͳ��
	long long	video_decode_size[MAX_DE_CHN];
} SYSTEM_DEBUG_INFO;

int SystemSetProductID(const char *productID);			// ���ò�Ʒ�ͺ�
int SystemOutputVpssVicpInfo(int flags);			// �ڲ�����1
int SystemGetDebug(SYSTEM_DEBUG_INFO *info);

int SystemInit();							// libcapture����api����ǰ�����ȵ����������
int SystemUninit();

int SystemGetProductCapability(DEVICE_CAPABILITY *cap);	// ��ȡ�豸����
int SystemGetVersion(char *version);				// ��ȡ��İ汾

#ifdef __cplusplus
}
#endif

#endif

