#include "script.h"

namespace Script {
	void *sp_symbol_table = (void *)0x9E1BFC;

	opd_t runscript_t = { (0x441530LL),  BASE_TOC };
	int64_t (*RunScript)(int64_t, CStruct*, unsigned int*, int64_t)  = (int64_t (*)(int64_t crc, CStruct* cstruct,  unsigned int *unk, int64_t cscript))&runscript_t;	

	//Resolve global symbols
	CSymbolTableEntry* Resolve(int32_t checksum) {
		CSymbolTableEntry *entry = NULL;
		uint32_t* script_singleton = (uint32_t*)sp_symbol_table;
		uint32_t* type_offset = (uint32_t*)(((4 * checksum) & 0x1FFFCu) + *(int32_t*)script_singleton);		
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
		uint32_t* script_singleton = (uint32_t*)sp_symbol_table;
		uint32_t* type_offset = (uint32_t*)(((4 * entry->checksum) & 0x1FFFCu) + *(int32_t*)script_singleton);	

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