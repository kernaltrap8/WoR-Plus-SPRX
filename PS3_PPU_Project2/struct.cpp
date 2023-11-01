#include "struct.h"

namespace Script {
	opd_s allocate_cstruct_t = { (0x34918),  BASE_TOC };
	CStruct*(*AllocateCStruct)(int64_t, int64_t) = (CStruct* (*)(int64_t const_1, int64_t const_8))&allocate_cstruct_t;	

	opd_s addstring_t = { (0x4504AC),  BASE_TOC };
	int64_t (*AddStringW)(CStruct *, int64_t crc, wchar_t *string) = (int64_t (*)(CStruct *, int64_t , wchar_t *))&addstring_t;

	opd_s addchecksum_t = { (0x4501EC),  BASE_TOC };
	int64_t (*AddChecksum)(CStruct *, int64_t crc, uint32_t value) = (int64_t (*)(CStruct *, int64_t , uint32_t))&addchecksum_t;

	opd_s getchecksum_t = { (0x4450CC),  BASE_TOC };
	int64_t (*GetChecksum)(CStruct *, int64_t crc, uint32_t *value) = (int64_t (*)(CStruct *, int64_t , uint32_t *))&getchecksum_t;

	opd_s addinteger_t = { (0x45034C),  BASE_TOC };
	int64_t (*AddInteger)(CStruct *, int64_t crc, uint32_t value) = (int64_t (*)(CStruct *, int64_t , uint32_t))&addinteger_t;

	opd_s addvector_t = { (0x4500E8),  BASE_TOC };
	int64_t (*AddVector)(CStruct *, int64_t crc, double x, double y, double z) = (int64_t (*)(CStruct *, int64_t, double, double, double))&addvector_t;


	opd_s containsflag_t = { (0x444B58),  BASE_TOC };
	int64_t (*ContainsFlag)(CStruct *, int64_t crc) = (int64_t (*)(CStruct *, int64_t crc))&containsflag_t;

	opd_s getinteger_t = { (0x444768),  BASE_TOC };
	int64_t (*GetInteger)(CStruct *, int64_t crc, uint32_t *value) = (int64_t (*)(CStruct *, int64_t , uint32_t*))&getinteger_t;

	opd_s getstring_t = { (0x4447B8),  BASE_TOC };
	int64_t (*GetString)(CStruct *, int64_t crc, wchar_t **value) = (int64_t (*)(CStruct *, int64_t , wchar_t **))&getstring_t;
}