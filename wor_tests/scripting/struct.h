#ifndef _STRUCT_H
#define _STRUCT_H
#include "../main.h"
namespace Script {
	typedef void *CStruct;
	extern CStruct* (*AllocateCStruct)(int64_t, int64_t);
	extern int64_t (*AddStringW)(CStruct *, int64_t crc, wchar_t *string);
	extern int64_t (*AddChecksum)(CStruct *, int64_t crc, uint32_t value);
	extern int64_t (*GetChecksum)(CStruct *, int64_t crc, uint32_t *value);
	extern int64_t (*AddInteger)(CStruct *, int64_t crc, uint32_t value);

	extern int64_t (*GetInteger)(CStruct *, int64_t crc, uint32_t *value);
	extern int64_t (*GetString)(CStruct *, int64_t crc, wchar_t **value);


	extern int64_t (*ContainsFlag)(CStruct *, int64_t crc);

}
#endif //_STRUCT_H