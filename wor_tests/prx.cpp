#include <cellstatus.h>
#include <sys/prx.h>
#include "main.h"
#include "printf.h"
#include "syscalls.h"
#include "detour\Detour.h"
#include "scripting/script.h"
#define VERSION "v1.1r1 alpha"

SYS_MODULE_INFO( wor_tests, 0, 1, 1);
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

void wor_test_main_thread(uint64_t args) {
	for (;;) {
		printf("i am injected\n");
		_sys_timer_sleep(1);
	}
	
	_sys_ppu_thread_exit(0);
}


extern "C" uint64_t strlen(const char *s) {
	uint64_t r = 0;
	while (*s) {
		r++;
		s++;
	}
	return r;
}

extern "C" int _wor_tests_prx_entry(void)
{
	//Sleep 30sec before patches
	printf("Sleeping for 30sec before applying patches.\nWoRmod %s loaded.\n", VERSION);
	_sys_timer_sleep(30);
	// enable_button_cheats | for debug menu
	Script::CSymbolTableEntry* enable_button_cheats_symbol = Script::Resolve(720971780);
	printf("enable_button_cheats symbol: %p\n", enable_button_cheats_symbol);

	if (enable_button_cheats_symbol) {
		printf("enable_button_cheats symbol data: %p %d %d\n", enable_button_cheats_symbol->union_type, enable_button_cheats_symbol->type, enable_button_cheats_symbol->sourceFileNameChecksum);
		enable_button_cheats_symbol->union_type = 1;
	}
	// debug_use_screen_noise | post processing FX disable
	Script::CSymbolTableEntry* debug_use_screen_noise_symbol = Script::Resolve(3786639802);
	printf("debug_use_screen_noise symbol: %p\n", debug_use_screen_noise_symbol);
	
	if (debug_use_screen_noise_symbol) {
		printf("debug_use_screen_noise symbol data: %p %d %d\n", debug_use_screen_noise_symbol->union_type, debug_use_screen_noise_symbol->type, debug_use_screen_noise_symbol->sourceFileNameChecksum);
		debug_use_screen_noise_symbol->union_type = 0;
	}
	// debug_use_motion_blur | post processing FX disable
	Script::CSymbolTableEntry* debug_use_motion_blur_symbol = Script::Resolve(42529484);
	printf("debug_use_motion_blur symbol: %p\n", debug_use_motion_blur_symbol);

	if (debug_use_motion_blur_symbol) {
		printf("debug_use_motion_blur symbol data: %p %d %d\n", debug_use_motion_blur_symbol->union_type, debug_use_motion_blur_symbol->type, debug_use_motion_blur_symbol->sourceFileNameChecksum);
		debug_use_motion_blur_symbol->union_type = 0;
	}
	// allow_controller_for_all_instruments
	Script::CSymbolTableEntry* allow_controller_for_all_instruments_symbol = Script::Resolve(2590800659);
	printf("allow_controller_for_all_instruments symbol: %p\n", allow_controller_for_all_instruments_symbol);

	if (allow_controller_for_all_instruments_symbol) {
		printf("allow_controller_for_all_instruments data: %p %d %d\n", allow_controller_for_all_instruments_symbol->union_type, allow_controller_for_all_instruments_symbol->type, allow_controller_for_all_instruments_symbol->sourceFileNameChecksum);
		allow_controller_for_all_instruments_symbol->union_type = 1;
	}
	// g_career_skip_naration
	Script::CSymbolTableEntry* g_career_skip_naration_symbol = Script::Resolve(2634030452);
	printf("g_career_skip_naration symbol: %p\n", g_career_skip_naration_symbol);

	if (g_career_skip_naration_symbol) {
		printf("g_career_skip_naration symbol data: %p %d %d\n", g_career_skip_naration_symbol->union_type, g_career_skip_naration_symbol->type, g_career_skip_naration_symbol->sourceFileNameChecksum);
		g_career_skip_naration_symbol->union_type = 1;
	}
	// unlock_Cheat_SuperUser
	Script::CSymbolTableEntry* unlock_Cheat_SuperUser_symbol = Script::Resolve(785547704);
	printf("unlock_Cheat_SuperUser symbol: %p\n", unlock_Cheat_SuperUser_symbol);

	if (unlock_Cheat_SuperUser_symbol) {
		printf("unlock_Cheat_SuperUser symbol data: %p %d %d\n", unlock_Cheat_SuperUser_symbol->union_type, unlock_Cheat_SuperUser_symbol->type, unlock_Cheat_SuperUser_symbol->sourceFileNameChecksum);
		unlock_Cheat_SuperUser_symbol->union_type = 1;
	}
	// QString patches | NOT YET WORKING
	Script::CSymbolTableEntry* debug_menu_qsymbol = Script::Resolve(2950671652);
	printf("debug_menu qsymbol: %p\n", debug_menu_qsymbol);

	if (debug_menu_qsymbol) {
		printf("debug_menu qsymbol data: %p %d %d\n", debug_menu_qsymbol->union_type, debug_menu_qsymbol->type, debug_menu_qsymbol->sourceFileNameChecksum);
		debug_menu_qsymbol->union_type = 623432161;
	}
	//Debug Menu
	Script::CSymbolTableEntry* debug_menu_popup_qsymbol = Script::Resolve(681849159);
	printf("debug_menu_popup qsymbol: %p\n", debug_menu_qsymbol);

	if (debug_menu_popup_qsymbol) {
		printf("debug_menu_popup qsymbol data: %p %d %d\n", debug_menu_popup_qsymbol->union_type, debug_menu_popup_qsymbol->type, debug_menu_popup_qsymbol->sourceFileNameChecksum);
		debug_menu_popup_qsymbol->union_type = 2381295399;
	}
	// apply patches
	CFuncs::RegisterCFuncs();
	// Exit thread using syscall directly and not the user mode library or else we will crash
	_sys_ppu_thread_exit(0);
    return SYS_PRX_RESIDENT;
}


extern "C" int _wor_tests_prx_stop(void)
{
	//uint64_t retVal;
	//sys_ppu_thread_join(gWORTthreadID, &retVal);

	// Exit thread using directly the syscall and not the user mode library or else we will crash
	_sys_ppu_thread_exit(0);

	return SYS_PRX_RESIDENT;
}
