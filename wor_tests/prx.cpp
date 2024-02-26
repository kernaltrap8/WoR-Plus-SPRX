#include <cellstatus.h>
#include <sys/prx.h>
#include "main.h"
#include "printf.h"
#include "syscalls.h"
#include "detour\Detour.h"
#include "scripting/script.h"
#define VERSION "v1.3r2 alpha-release"

SYS_MODULE_INFO( ghwor_plugin, 0, 1, 1);
SYS_MODULE_START( _wor_tests_prx_entry );
SYS_MODULE_STOP(_wor_tests_prx_stop);

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _wor_tests_export_function, LIBNAME );

sys_ppu_thread_t gWORTthreadID = SYS_PPU_THREAD_ID_INVALID;

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _wor_tests_export_function(void)
{
    return CELL_OK;
}

namespace QSymbol {
	void EditSymbol(uint32_t symbol, int symbolData, int g_EnablePrintf) {
		Script::CSymbolTableEntry* gSymbol = Script::Resolve(symbol);
		if (g_EnablePrintf == 1) {
			printf("symbol address: %p\n", gSymbol);
			printf("symbol data: %p %d %d\n", gSymbol->union_type, gSymbol->type, gSymbol->sourceFileNameChecksum);
		}
		if (gSymbol) {
			gSymbol->union_type = symbolData;
		}
	}
}

namespace ghwor {
	void ApplyPatches() {
		int gCD = 1;
		int g_EnablePatches = 1;
		if (g_EnablePatches == 1) {
			if (gCD == 1) {
				printf("gCD = %i\n", gCD);
				QSymbol::EditSymbol(720971780, 1, 1);
				QSymbol::EditSymbol(1776699150, 1, 1);
				QSymbol::EditSymbol(2792038869, 1, 1)
			}
			QSymbol::EditSymbol(3786639802, 0, 1);
			QSymbol::EditSymbol(42529484, 0, 1);
			QSymbol::EditSymbol(2590800659, 1, 1);
			QSymbol::EditSymbol(2634030452, 1, 1);
			printf("Applied patches successfully.\n");
		} else {
			printf("QSymbol patches are disabled on this build.\n");
		}
	}
}

void wor_test_main_thread(uint64_t args) {
	//Sleep 30sec before patches
	int DebugPrintfStuff = 0;
	printf("ghwor_plugin %s loaded.\nSleeping for 30sec before applying patches.\n", VERSION);
	if (DebugPrintfStuff == 1) {
		printf("Patching CFuncs...\n");
		CFuncs::RegisterCFuncs();
	}
	else {
		printf("CFunc patches are disabled on this build.\n");
	}
	_sys_timer_sleep(30);
	ghwor::ApplyPatches();
}

extern "C" int _wor_tests_prx_entry(void)
{
	sys_ppu_thread_create(&gWORTthreadID, wor_test_main_thread, 0, 3000, 4096 * 16, SYS_PPU_THREAD_CREATE_JOINABLE, "WoR+_MainThread");
    return SYS_PRX_RESIDENT;
}


extern "C" int _wor_tests_prx_stop(void)
{
	uint64_t retVal;
	sys_ppu_thread_join(gWORTthreadID, &retVal);

	return SYS_PRX_RESIDENT;
}
