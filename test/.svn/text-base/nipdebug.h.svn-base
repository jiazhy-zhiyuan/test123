#ifndef __NIPDEBUG_NIPDEBUG_H__
#define __NIPDEBUG_NIPDEBUG_H__
#include <signal.h>

#ifdef __cplusplus
extern "C"{
#endif

#define NF_NOOMIT_FRAME_POINT	0x1000
#define NF_DEBUGTHREAD		0x4000

/* 
 * 说明：btsize最多显示回溯个数，为0则找到main函数为止
 * 	 symbol_file是符号文件（可执行文件本身包含符号表时会忽略此参数）
 *	 crushdump_file是程序异常的输出文件，为空会输出到控制台
 *	 signum信号id
 *	 NF_NOOMIT_FRAME_POINT针对没有优化堆栈帧的编译
 *	 NF_NO_DEBUGTHREAD表示不启用调试线程
 * 示例：init_nipdebug(0,  NULL, NULL, NF_NOOMIT_FRAME_POINT);
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

