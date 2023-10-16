#include "main.h"
#include "task.h"

namespace Tsk {
	void *gMlpMgrInstance = (void *)0xE7A9C8;


	opd_s add_task_t = { (0x214B9C),  BASE_TOC };
	int64_t (*AddTask)(void *, void*) = (int64_t (*)(void *, void*))&add_task_t;

	typedef struct {
		void *function_address; //0-4
		uint16_t priority; //?? 4-6
		void* function_address_2; //6-10
		uint8_t unk[22];
	} TaskEntry;

	void do_test_task(void *unk) {
		printf("TEST TASK!\n");
	}
	void test_tasks() {

		static opd_s *our_opd = (opd_s *)&do_test_task;	
		static opd_s **ref_2 = &our_opd;
		static opd_s ***ref_3 = &ref_2;

		static TaskEntry entry;
		entry.function_address = &do_test_task;
		entry.function_address_2 = &do_test_task;

		void *x = *(void **)gMlpMgrInstance;
		void *unk_offset = (void *)((uint64_t)x);
		AddTask(unk_offset,&entry);
	}
}