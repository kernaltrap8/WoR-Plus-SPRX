#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdio.h>

//sysPrxForUser -- not syscall
extern "C" int _sys_printf(const char* format, ...);
#define printf _sys_printf
extern "C" int console_write(const char *data, unsigned long len);
size_t our_mbstowcs(wchar_t *dest, const char *src, size_t n);
size_t our_wcstombs(char *dest, const wchar_t *src, size_t n);
//

// Open Flags
#define SYS_O_RDONLY		000000
#define SYS_O_WRONLY		000001
#define SYS_O_RDWR			000002
#define SYS_O_ACCMODE		000003
#define SYS_O_CREAT			000100
#define SYS_O_EXCL			000200
#define SYS_O_TRUNC			001000
#define SYS_O_APPEND		002000
#define SYS_O_MSELF			010000

int _sys_fs_open(const char *path, int flags, int *fd, uint64_t mode, const void *arg, uint64_t size);
int _sys_fs_read(int fd, void *buf, uint64_t nbytes, uint64_t *nread); 
int _sys_fs_write(int fd, const void *buf, uint64_t nbytes, uint64_t *nwrite); 
int _sys_fs_close(int fd); 


void _sys_timer_sleep(int sleep_time);
void _sys_ppu_thread_exit(int exit_code);
int _sys_dbg_write_process_memory(sys_pid_t pid, uint64_t process_ea, uint32_t size, const void* data);
sys_pid_t _sys_process_getpid();




#endif //_SYSCALLS_H