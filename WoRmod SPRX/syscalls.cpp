#include <sys\syscall.h>
#include "syscalls.h"

#include <string.h>

int _sys_fs_open(const char *path, int flags, int *fd, uint64_t mode, const void *arg, uint64_t size) {
	system_call_6(801, (uint64_t)path, flags, (uint64_t)fd, mode, (uint64_t)arg, size);
	return_to_user_prog(int);
}
int _sys_fs_read(int fd, void *buf, uint64_t nbytes, uint64_t *nread) {
	system_call_4(802, fd, (uint64_t)buf, nbytes, (uint64_t)nread);
	return_to_user_prog(int);
}
int _sys_fs_write(int fd, const void *buf, uint64_t nbytes, uint64_t *nwrite) {
	system_call_4(803, (uint64_t)fd, (uint64_t)buf, nbytes, (uint64_t)nwrite);
	return_to_user_prog(int);
}
int _sys_fs_close(int fd) {
	system_call_1(804, fd);
	return_to_user_prog(int);
}

void _sys_timer_sleep(int sleep_time) {
	system_call_1(142,(uint64_t)sleep_time);
}

void _sys_ppu_thread_exit(int exit_code) {
	system_call_1(41,(uint64_t)exit_code);
}
int _sys_dbg_write_process_memory(sys_pid_t pid, uint64_t process_ea, uint32_t size, const void* data) {
	system_call_4(905,(uint64_t)(uint32_t)pid, process_ea, (uint64_t)size, (uint64_t)(uint32_t)data);
	return_to_user_prog(int);
}
sys_pid_t _sys_process_getpid() {
	system_call_0(1);
    return (int32_t)p1;
}

void _sys_console_write(const char *s, uint32_t len) {
	system_call_2(398,(uint64_t)s, len);
}


size_t our_wcstombs(char *dest, const wchar_t *src, size_t n)
{
	uint8_t *s = (uint8_t *)src;
	char *p = (char *)dest;
	int i = 0;
	while(*s != 0 && i < n) {
		*p++ = (*s);
		i++;
		s += 2;
	}
	*p++ = 0;
	return i;
}

size_t our_mbstowcs(wchar_t *dest, const char *src, size_t n)
{
	uint16_t *p = (uint16_t *)dest;
	int sz = strlen(src);
	for(int i=0;i<sz;i++) {
		uint8_t ch = *src;
		uint16_t c = ch;
		src++;
		//*p++ = (c>>8) | (c<<8);
		*p++ = c;
	}
	*p++ = 0;
	return sz;
}

extern "C" {
	void _putchar(char ch) {
		_sys_console_write((char *)&ch, 1);
	}
}