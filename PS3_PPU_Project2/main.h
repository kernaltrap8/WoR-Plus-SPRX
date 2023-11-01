#ifndef _MAIN_H
#define _MAIN_H
#include <cellstatus.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>

#define TEMP_SERVER_IP 167838056
#define TEMP_SERVER_PORT 5150

#include "syscalls.h"
//#define printf printf_

//sysPrxForUser -- not syscall
extern "C" int _sys_printf(const char* format, ...);
#define printf _sys_printf
extern "C" int console_write(const char *data, unsigned long len);
//

#define BASE_TOC 0xE7D9A0

struct opd_s
{
    uint32_t sub;
    uint32_t toc;
};

typedef struct _branchInstruction {
	uint8_t OP:6;
	uint32_t LI:24;
	uint8_t AA:1;
	uint8_t LK:1;		
} branchInstruction;

void install_sys_hooks();
#endif //_MAIN_H