#include <sys\syscall.h>
#include "syscalls.h"

#include <string.h>

void _sys_timer_sleep(int sleep_time) {
	system_call_1(142,(uint64_t)sleep_time);
}

void _sys_ppu_thread_exit(int exit_code) {
	system_call_1(41,(uint64_t)exit_code);
}

void _sys_console_write(const char *s, uint32_t len) {
	system_call_2(398,(uint64_t)s, len);
}

void _sys_tty_write(uint32_t ch, const void *buf, uint32_t len, uint32_t *pwritelen) {
	system_call_4(403, (uint64_t)ch, (uint64_t)buf, (uint64_t)len, (uint64_t)pwritelen);
}

extern "C" {
	void _putchar(char ch) {
		uint32_t write_len = 0;
		_sys_tty_write(0, &ch, 1, &write_len);
	}
}