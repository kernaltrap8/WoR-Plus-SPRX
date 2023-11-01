#include "script.h"
#include "stdafx.h"
#include <cellstatus.h>
#include <sys/prx.h>

SYS_MODULE_INFO( ghwor_plugin, 0, 1, 1);
SYS_MODULE_START( _ghwor_plugin_prx_entry );
SYS_MODULE_STOP( _ghwor_plugin_prx_stop );

namespace Script {
	void *sp_script_manager = (void *)0x5AC78; /*possibly the script manager??? dunno yet :3
												0x5AC78 | ?WoR? script pointer
												0xE7C4F0 | THPG/?GH3? script pointer*/

	//needs to be updated for WoR to allow script running :3
	//opd_s runscript_t = { (0x441530LL),  BASE_TOC };
	//int64_t (*RunScript)(int64_t, CStruct*, unsigned int*, int64_t)  = (int64_t (*)(int64_t crc, CStruct* cstruct,  unsigned int *unk, int64_t cscript))&runscript_t;	

	//Resolve global symbols
	CSymbolTableEntry* Resolve(int32_t checksum) {
		CSymbolTableEntry *entry = NULL;
		uint32_t* script_singleton = (uint32_t*)sp_script_manager;
		uint32_t* type_offset = (uint32_t*)(((4 * checksum) & 0x1FFFCu) + *(int32_t*)script_singleton[0]);		
		if(*type_offset) {
			entry = (CSymbolTableEntry*)*type_offset;
			if(entry->checksum == checksum) {
				return entry;
			}
			do {
				if(!entry->next) {
					return NULL;
				}
				entry = (CSymbolTableEntry *)entry->next;
				
			} while(entry->checksum != checksum);
		}
		return entry;
	}

	
	void InsertSymbol(CSymbolTableEntry *entry) {
		uint32_t* script_singleton = (uint32_t*)sp_script_manager;
		uint32_t* type_offset = (uint32_t*)(((4 * entry->checksum) & 0x1FFFCu) + *(int32_t*)script_singleton[0]);	

		if(*type_offset) {
			CSymbolTableEntry *symbol = (CSymbolTableEntry*)*type_offset;
			while(symbol->next != NULL) {
				symbol = (CSymbolTableEntry *)symbol->next;
			}
			symbol->next = entry;
		} else {
			*type_offset = (uint32_t)entry;
		}

	}
};

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _ghwor_plugin_export_function(void)
{
    return CELL_OK;
}

extern "C" int _ghwor_plugin_prx_entry(void)
{
    // Below are all the SectionIntegers edited for WoRmod, they are in checksum format (uint32)
	Script::CSymbolTableEntry* join_symbol_5 = Script::Resolve(720971780); //enable_button_cheats | debug menu!!!
	if (join_symbol_5) {
		join_symbol_5->union_type = 1; // use this to enable/disable
	}


	Script::CSymbolTableEntry* join_symbol_1 = Script::Resolve(-508327494); //debug_use_screen_noise
	if (join_symbol_1) {
		//printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type);
		join_symbol_1->union_type = 0; // use this to enable/disable
	}


	Script::CSymbolTableEntry* join_symbol_2 = Script::Resolve(42529484); //debug_use_motion_blur
	if (join_symbol_2) {
		join_symbol_2->union_type = 0; // use this to enable/disable
	}


	Script::CSymbolTableEntry* join_symbol_3 = Script::Resolve(1037972114); //g_debug_highway_visible
	if (join_symbol_3) {
		join_symbol_3->union_type = 0; // use this to enable/disable
	}


	Script::CSymbolTableEntry* join_symbol_4 = Script::Resolve(-1704166637); //allow_controller_for_all_instruments
	if (join_symbol_4) {
		join_symbol_4->union_type = 1; // use this to enable/disable
	}


	Script::CSymbolTableEntry* join_symbol_6 = Script::Resolve(1776699150); //enable_debug_menus
	if (join_symbol_6) {
		join_symbol_6->union_type = 1; // use this to enable/disable
	}

    return SYS_PRX_RESIDENT;
}

extern "C" int _ghwor_plugin_prx_stop(void)
{
    return SYS_PRX_RESIDENT;
}
