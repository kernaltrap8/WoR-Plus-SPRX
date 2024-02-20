#include "Detour.h"

BYTE   Detour::TrampolineBuffer[ 200 * 20 ] = {};
SIZE_T Detour::TrampolineSize = 0;

UINT32 *Detour::LocalExecutableScratchpad = (UINT32 *)0x10230;//0x6D2A28; //start of main entry point


#define PROCESS_BASE (uint64_t)0x10000
void * detour_memcpy( void * destination, const void * source, size_t num ) {
	//printf("DETOUR MEMCPY - %p to %p - (%d)!\n", destination, source, num);
	sys_pid_t pid = _sys_process_getpid();
	_sys_dbg_write_process_memory(pid, (uint64_t)destination, num, source);
	return destination;

}