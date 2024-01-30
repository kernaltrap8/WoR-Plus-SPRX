#include <sys\syscall.h>
#include "syscalls.h"

#include <string.h>

void _sys_timer_sleep(int sleep_time) {
	system_call_1(142,(uint64_t)sleep_time);
}

void _sys_ppu_thread_exit(int exit_code) {
	system_call_1(41,(uint64_t)exit_code);
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