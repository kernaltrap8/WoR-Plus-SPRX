#include "script.h"

namespace Script {
	void *sp_script_manager = (void *)0xE7C4F0;

	opd_s runscript_t = { (0x441530LL),  BASE_TOC };
	int64_t (*RunScript)(int64_t, CStruct*, unsigned int*, int64_t)  = (int64_t (*)(int64_t crc, CStruct* cstruct,  unsigned int *unk, int64_t cscript))&runscript_t;	

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

	// Below are all the SectionIntegers edited for WoRmod, they are in checksum format (uint32)

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(-508327494); //debug_use_screen_noise
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 0; // use this to enable/disable
    }

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(42529484); //debug_use_motion_blur
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 0; // use this to enable/disable
    }

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(1037972114); //g_debug_highway_visible
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 0; // use this to enable/disable
    }

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(-1704166637); //allow_controller_for_all_instruments
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 1; // use this to enable/disable
    }


	if(Script::Resolve(720971780) = join_symbol->union_type = 0) {
	Script::CSymbolTableEntry* join_symbol = Script::Resolve(720971780); //enable_button_cheats | debug menu!!!
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 1; // use this to enable/disable
    }
	}

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(1776699150); //enable_debug_menus
    printf("symbol: %p\n", join_symbol);

    if(join_symbol) {
        printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
        join_symbol->union_type = 1; // use this to enable/disable
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