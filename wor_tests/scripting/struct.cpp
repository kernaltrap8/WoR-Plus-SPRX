#include "struct.h"

namespace Script {
	opd_t allocate_cstruct_t = { (0x34F508), BASE_TOC };
	CStruct*(*AllocateCStruct)(int64_t, int64_t) = (CStruct* (*)(int64_t const_1, int64_t const_8))&allocate_cstruct_t;	

	opd_t destroy_cstruct_t = { (0x34FF50), BASE_TOC };
	void(*DestroyCStruct)(CStruct *cstruct) = (void(*)(CStruct*))&destroy_cstruct_t;

	opd_t addchecksum_t = { (0x352290), BASE_TOC };
	int64_t (*AddChecksum)(CStruct *, int64_t crc, uint32_t value) = (int64_t (*)(CStruct *, int64_t , uint32_t))&addchecksum_t;
}