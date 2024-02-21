#ifndef _MAIN_H
#define _MAIN_H

#include "syscalls.h"
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

#define BASE_TOC 0x980FF0

typedef struct _opd_s
{
	uint32_t sub;
	uint32_t toc;
} opd_t;

typedef struct _branchInstruction {
	uint8_t OP : 6;
	uint32_t LI : 24;
	uint8_t AA : 1;
	uint8_t LK : 1;
} branchInstruction;


#define printf printf_

void _sys_ppu_thread_exit(int exit_code);

#endif // _MAIN_H