#ifndef _SCRIPT_H
#define _SCRIPT_H
#include "../main.h"
#include "struct.h"
namespace Script {
	typedef struct _CSymbolTableEntry{
		uint8_t unk[2]; //0, 1
		uint8_t type; //2
		uint8_t unk2; //3
		uint32_t checksum; //4
		uint32_t sourceFileNameChecksum;
		uint32_t union_type; //12
		void *next;
	} CSymbolTableEntry;


	extern int64_t(*RunScript)(int64_t crc, CStruct* cstruct, unsigned int *unk, uint8_t unk1, uint64_t unk2, uint64_t unk3);

	CSymbolTableEntry* Resolve(int32_t checksum);
	void InsertSymbol(CSymbolTableEntry *entry);

	

	extern void *sp_script_manager;
};

namespace CFuncs {
	void RegisterCFuncs();
};
#endif //_SCRIPT_H