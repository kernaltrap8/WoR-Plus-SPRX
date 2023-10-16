#include "mem.h"
#include "../detour/Detour.h"
namespace Mem {
	void PushMemProfile(uint32_t crc, uint32_t p1, uint32_t p2);
	void PopMemProfile();
	void InitHooks() {
		printf("@ Installing Mem hooks\n");
		//Hook push mem profile
		opd_s *memprofile_push_detour_opd = (opd_s*)&PushMemProfile;
		

		branchInstruction *pushmemprofile_entry = (branchInstruction *)0x685610;
		branchInstruction pushmemprofile_entry_cpy = *pushmemprofile_entry;
		pushmemprofile_entry_cpy.OP = 0x12;
		pushmemprofile_entry_cpy.AA = 1;
		pushmemprofile_entry_cpy.LI = ((UINT32)Detour::LocalExecutableScratchpad) >> 2;
		pushmemprofile_entry_cpy.LK = 0;

		Detour::LocalExecutableScratchpad += Detour::WriteFarBranch(Detour::LocalExecutableScratchpad, (void *)memprofile_push_detour_opd->sub, false, true);
		_sys_dbg_write_process_memory(_sys_process_getpid(), (uint64_t)pushmemprofile_entry, sizeof(branchInstruction), &pushmemprofile_entry_cpy);


		//Hook pop mem profile
		opd_s *memprofile_pop_detour_opd = (opd_s*)&PopMemProfile;
		branchInstruction *popmemprofile_entry = (branchInstruction *)0x685618;
		branchInstruction popmemprofile_entry_cpy = *popmemprofile_entry;
		popmemprofile_entry_cpy.OP = 0x12;
		popmemprofile_entry_cpy.AA = 1;
		popmemprofile_entry_cpy.LI = ((UINT32)Detour::LocalExecutableScratchpad) >> 2;
		popmemprofile_entry_cpy.LK = 0;

		Detour::LocalExecutableScratchpad += Detour::WriteFarBranch((UINT32 *)Detour::LocalExecutableScratchpad, (void *)memprofile_pop_detour_opd->sub, false, true);
		_sys_dbg_write_process_memory(_sys_process_getpid(), (uint64_t)popmemprofile_entry, sizeof(branchInstruction), &popmemprofile_entry_cpy);
	}
	void PushMemProfile(uint32_t crc, uint32_t p1, uint32_t p2) {
		printf("! PushMemProfile (%d - %d - %d)\n", crc, p1, p2);
	}
	void PopMemProfile() {
		printf("! PopMemProfile\n");
	}
}