#ifndef __NIPDEBUG_NIPDEBUG_H__
#define __NIPDEBUG_NIPDEBUG_H__
#include <signal.h>

#ifdef __cplusplus
extern "C"{
#endif

#define NF_NOOMIT_FRAME_POINT	0x1000
#define NF_DEBUGTHREAD		0x4000

/* 
 * ˵����btsize�����ʾ���ݸ�����Ϊ0���ҵ�main����Ϊֹ
 * 	 symbol_file�Ƿ����ļ�����ִ���ļ�����������ű�ʱ����Դ˲�����
 *	 crushdump_file�ǳ����쳣������ļ���Ϊ�ջ����������̨
 *	 signum�ź�id
 *	 NF_NOOMIT_FRAME_POINT���û���Ż���ջ֡�ı���
 *	 NF_NO_DEBUGTHREAD��ʾ�����õ����߳�
 * ʾ����init_nipdebug(0,  NULL, NULL, NF_NOOMIT_FRAME_POINT);
 *	 init_nipdebug(10, NULL, "/usr/cursh.out", NF_NOOMIT_FRAME_POINT);
 *	 init_nipdebug(0,  "/bin/ebt.sym", "/usr/cursh.out", 0);
 *	 init_nipdebug2(SIGPIPE,  "/bin/ebt.sym", "/usr/cursh.out", 0);
 */
int init_nipdebug(int btsize, const char *symbol_file, const char *crushdump_file, int flags);
int init_nipdebug2(int signum, int btsize, const char *symbol_file, const char *crushdump_file, int flags);

/*
 * version information
 */
char *nipdebug_version();
#define NIPDEBUG__VERSION	"NIPDEBUG 1.1.5.20XXYYZZ #" __DATE__ " " __TIME__

#ifdef __cplusplus
}
#endif

#endif

