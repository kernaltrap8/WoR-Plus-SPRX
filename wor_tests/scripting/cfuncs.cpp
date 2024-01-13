#include "script.h"
#include "struct.h"
#include "../printf.h"

#include "../show_dump.h"
#include "../detour/Detour.h"
namespace CFuncs {
	bool ScriptPrintf(Script::CStruct *pParams);
	opd_t s_get_string_from_params_opd = { 0x499E0, BASE_TOC };
	bool (*s_get_string_from_params)(char *buffer, int sz, Script::CStruct *pParams) = (bool(*)(char *, int, Script::CStruct *))&s_get_string_from_params_opd;
	void RegisterCFuncs() {

		//patch printf
		opd_t *printf_opd = (opd_t*)&ScriptPrintf;
		branchInstruction *popmemprofile_entry = (branchInstruction *)0x49FAC;
		branchInstruction popmemprofile_entry_cpy;
		popmemprofile_entry_cpy.OP = 0x12;
		popmemprofile_entry_cpy.AA = 1;
		popmemprofile_entry_cpy.LI = ((UINT32)Detour::LocalExecutableScratchpad) >> 2;
		popmemprofile_entry_cpy.LK = 0;

		Detour::LocalExecutableScratchpad += Detour::WriteFarBranch((UINT32 *)Detour::LocalExecutableScratchpad, (void *)printf_opd->sub, false, true);
		_sys_dbg_write_process_memory(_sys_process_getpid(), (uint64_t)popmemprofile_entry, sizeof(branchInstruction), &popmemprofile_entry_cpy);
		//
		
	}

	bool ScriptPrintf(Script::CStruct *pParams) {
		char str[1024];
		s_get_string_from_params(str, 1024, pParams);

		printf("%s", str);	
		
		return true;
	}
}