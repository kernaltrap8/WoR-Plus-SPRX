#include "script.h"
#include "struct.h"

#include "../show_dump.h"

namespace NetSession {
	bool ScriptNetSessionFunc(Script::CStruct *pParams, void *pScript);
	bool ScriptCheckForSignin (Script::CStruct *pParams, void *pScript);
	bool ScriptJoinServer(Script::CStruct *pParams, void *pScript);
	bool ScriptNetMessage(Script::CStruct *pParams, void *pScript);

	bool ScriptFCFSRequestStartGame(Script::CStruct *pParams, void *pScript);
	bool ScriptFCFSRequestChangeLevel(Script::CStruct *pParams, void *pScript);
	bool ScriptFCFSRequestToggleProSet(Script::CStruct *pParams, void *pScript);
	bool ScriptFCFSRequestToggleGoalSelection(Script::CStruct *pParams, void *pScript);
	
}

namespace CFuncs {
	bool ScriptPrintf(Script::CStruct *pParams, void *pScript);
	bool (*s_get_string_from_params)(char *buffer, int sz, Script::CStruct *pParams) = (bool (*)(char *, int, Script::CStruct *))0x0E3C460;

	void RegisterCFuncs() {
		opd_s *game_printf_opd = (opd_s *)0xE3B638;
		opd_s *our_printf_opd = (opd_s *)&ScriptPrintf;		
		*game_printf_opd = *our_printf_opd;

		opd_s *game_networksessionfunc_opd = (opd_s*)0x0E3DDE8;
		opd_s *our_networksessionfunc_opd = (opd_s *)&NetSession::ScriptNetSessionFunc;		
		*game_networksessionfunc_opd = *our_networksessionfunc_opd;

		opd_s *game_checkforsignin_opd = (opd_s*)0xE5C010;
		opd_s *our_checkforsignin_opd = (opd_s *)&NetSession::ScriptCheckForSignin;		
		*game_checkforsignin_opd = *our_checkforsignin_opd;

		opd_s *game_joinserver_opd = (opd_s*)0xE5C548;
		opd_s *our_joinserver_opd = (opd_s *)&NetSession::ScriptJoinServer;		
		*game_joinserver_opd = *our_joinserver_opd;

		opd_s *game_netmsg_opd = (opd_s*)0xE5E050;
		opd_s *our_netmsg_opd = (opd_s *)&NetSession::ScriptNetMessage;		
		*game_netmsg_opd = *our_netmsg_opd;


		static Script::CSymbolTableEntry start_game_entry;
		start_game_entry.checksum = 406531533;
		start_game_entry.type = 8;
		start_game_entry.union_type = (uint32_t)&NetSession::ScriptFCFSRequestStartGame;
		Script::InsertSymbol(&start_game_entry);

		static Script::CSymbolTableEntry change_level_entry;
		change_level_entry.checksum = -405862342;
		change_level_entry.type = 8;
		change_level_entry.union_type = (uint32_t)&NetSession::ScriptFCFSRequestChangeLevel;
		Script::InsertSymbol(&change_level_entry);

		static Script::CSymbolTableEntry request_proset_entry;
		request_proset_entry.checksum = 2118360521;
		request_proset_entry.type = 8;
		request_proset_entry.union_type = (uint32_t)&NetSession::ScriptFCFSRequestToggleProSet;
		Script::InsertSymbol(&request_proset_entry);

		static Script::CSymbolTableEntry request_goalselection_entry;
		request_goalselection_entry.checksum = -40053512;
		request_goalselection_entry.type = 8;
		request_goalselection_entry.union_type = (uint32_t)&NetSession::ScriptFCFSRequestToggleGoalSelection;
		Script::InsertSymbol(&request_goalselection_entry);

		
	}

	bool ScriptPrintf(Script::CStruct *pParams, void *pScript) {
		char str[1024];
		s_get_string_from_params(str, 1024, pParams);

		printf("%s", str);	
		
		return true;
	}


	//bool ScriptPrintf(Script::CStruct *pParams, void *pScript) {
	//	char copy_buffer[1024];
	//	wchar_t *str = NULL;
	//	int r = Script::GetString(pParams, 0, &str);

	//	if (r == 0) {
	//		return false;
	//	}

	//	int sz = our_wcstombs(copy_buffer, str, sizeof(copy_buffer));
	//	if(sz <= 0) {
	//		return false;
	//	}
	//	copy_buffer[sz] = 0;
	//	printf("%s\n", copy_buffer);		
	//	return true;
	//}
}