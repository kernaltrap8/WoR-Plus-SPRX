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
	//CFW/DEX write_proc_mem
	//system_call_4(905,(uint64_t)(uint32_t)pid, process_ea, (uint64_t)size, (uint64_t)(uint32_t)data);
	//return_to_user_prog(int);
	//HEN/CEX write_proc_mem
	system_call_6(8, 0x7777, 0x32, (uint64_t)pid, process_ea, (uint64_t)data, size);
	return_to_user_prog(int);
}
sys_pid_t _sys_process_getpid() {
	system_call_0(1);
    return (int32_t)p1;
}

void _sys_console_write(const char *s, uint32_t len) {
	system_call_2(398,(uint64_t)s, len);
}

void _sys_tty_write(uint32_t ch, const void *buf, uint32_t len, uint32_t *pwritelen) {
	system_call_4(403, (uint64_t)ch, (uint64_t)buf, (uint64_t)len, (uint64_t)pwritelen);
}

int _sys_ppu_thread_create(uint64_t *thread_id, void(*entry) (__CSTD uint64_t), void *args, uint64_t unk, uint64_t pri, uint64_t stack_size, uint64_t flags, const char *name) {
	system_call_8(52, (uint64_t)thread_id, (uint64_t)entry, (uint64_t)args, (uint64_t)unk, (uint64_t)pri, (uint64_t)stack_size, (uint64_t)flags, (uint64_t)name);
	return (int32_t)p1;
}

int _sys_ppu_thread_start(uint64_t thread_id) {
	system_call_1(53, thread_id);
	return_to_user_prog(int);
}

extern "C" {
	void _putchar(char ch) {
		//_sys_console_write((char *)&ch, 1);
		uint32_t write_len = 0;
		_sys_tty_write(0, &ch, 1, &write_len);
		//_sys_tty_write(1, &ch, 1, &write_len);
		//_sys_tty_write(2, &ch, 1, &write_len);
	}
}