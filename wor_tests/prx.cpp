#include <cellstatus.h>
#include <sys/prx.h>
#include <cstdlib.h>
#include <cstdio.h>
#include "main.h"
#include "printf.h"
#include "syscalls.h"
#include "detour/Detour.h"
#include "scripting/script.h"
#define VERSION "v1.3r4 alpha-release"

SYS_MODULE_INFO(ghwor_plugin, 0, 1, 1);
SYS_MODULE_START(_wor_tests_prx_entry);
SYS_MODULE_STOP(_wor_tests_prx_stop);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_wor_tests_export_function, LIBNAME);

sys_ppu_thread_t gWORTthreadID = SYS_PPU_THREAD_ID_INVALID;

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _wor_tests_export_function(void)
{
	return CELL_OK;
}

int file_parser(const char* file, const char* line_to_read) {
	FILE* fileptr = fopen(file, "r"); // open the file to parse
	if (fileptr == NULL) {
		return -1;
	}

	char line[256]; // char buffer for parsing
	while (fgets(line, sizeof(line), fileptr)) {
		int val;
		if (sscanf(line, line_to_read, &val) == 1) {
			fclose(fileptr);
			return val;
		}
	}

	fclose(fileptr); // close file
	return -1; // negative exit code - if we get here, an error occurred.
}

namespace QSymbol {
	void EditSymbol(uint32_t symbol, int symbolData, int g_EnablePrintf) {
		Script::CSymbolTableEntry* gSymbol = Script::Resolve(symbol);
		int g_EnablePrintf = file_parser("worplus.ini", "g_EnablePrintf = %d");
		if (g_EnablePrintf == 1) {
			printf("symbol address: %p\n", gSymbol);
			printf("symbol data: %p %d %d\n", gSymbol->union_type, gSymbol->type, gSymbol->sourceFileNameChecksum);
		}
		if (gSymbol) {
			gSymbol->union_type = symbolData;
		} else {
			printf("Could not resolve symbol %d!\n", symbol);
		}
	}
}

namespace ghwor {
	void ApplyPatches() {
		int gCD = file_parser("worplus.ini", "gCD = %d");
		int g_EnablePatches = file_parser("worplus.ini", "g_EnablePatches = %d");
		if (g_EnablePatches == 1) {
			if (gCD == 1) {
				printf("gCD = %i\n", gCD);
				QSymbol::EditSymbol(720971780, 1, 1);
				QSymbol::EditSymbol(1776699150, 1, 1);
			}
			QSymbol::EditSymbol(3786639802, 0, 1);
			QSymbol::EditSymbol(42529484, 0, 1);
			QSymbol::EditSymbol(2590800659, 1, 1);
			QSymbol::EditSymbol(2634030452, 1, 1);
			printf("Applied patches successfully.\n");
		}
		else {
			printf("QSymbol patches are disabled on this build.\n");
		}
	}
}

void wor_test_main_thread(uint64_t args) {
	//Sleep 30sec before patches
	int DebugPrintfStuff = file_parser("worplus.ini", "DebugPrintfStuff = %d");
	int sleepTime = file_parser("worplus.ini", "sleepTime = %d");
	printf("ghwor_plugin %s loaded.\nSleeping for 30sec before applying patches.\n", VERSION);
	if (DebugPrintfStuff == 1) {
		printf("Patching CFuncs...\n");
		CFuncs::RegisterCFuncs();
	}
	else {
		printf("CFunc patches are disabled on this build.\n");
	}
	_sys_timer_sleep(sleepTime);
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
