#ifndef __OSD_ETAH_20130425_H_
#define __OSD_ETAH_20130425_H_

#define OSD_TRANSPARENCY_ENABLE		1
#define OSD_ENABLE_WIN			1
#define OSD_GLOBAL_ALPHA		0x80

#define OSD_MAX_CH			16			// ����ͨ����(�������������Լ���osd), 16��ʾ����������8��
//#define OSD_MAX_NUM_WINDOWS		4			// RGB888 OSD����

#define OSD_ENCODE_CHANNELI_ID		4			// 0,1,2,3�Ǳ�������������Ҫosd��4�ǵ�����Ҫ2��osd������2014.2.11�ʼ�

void __OsdInit();
void __OsdInit_onechannel();
void __OsdUninit();
void __osd_set_buffer(int chId, int index, ENCODE_TITLE_PARAM *pParam);
void __osd_set_position(int chId, int index, ENCODE_TITLE_PARAM *pParam);
#endif
