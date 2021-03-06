#ifndef __OSD_ETAH_20130425_H_
#define __OSD_ETAH_20130425_H_

#define OSD_TRANSPARENCY_ENABLE		1
#define OSD_ENABLE_WIN			1
#define OSD_GLOBAL_ALPHA		0x80

#define OSD_MAX_CH			16			// 编码通道数(主次码流各有自己的osd), 16表示主次码流各8个
//#define OSD_MAX_NUM_WINDOWS		4			// RGB888 OSD数量

#define OSD_ENCODE_CHANNELI_ID		4			// 0,1,2,3是本地主码流不需要osd，4是导播需要2个osd，老李2014.2.11邮件

void __OsdInit();
void __OsdInit_onechannel();
void __OsdUninit();
void __osd_set_buffer(int chId, int index, ENCODE_TITLE_PARAM *pParam);
void __osd_set_position(int chId, int index, ENCODE_TITLE_PARAM *pParam);
#endif

