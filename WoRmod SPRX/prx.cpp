#include "main.h"
#include "mem\mem.h"
#include "scripting\script.h"
#include "task.h"

#include "detour\Detour.h"

#include "show_dump.h"

uint8_t **gCD = (uint8_t **)0xE7A1FC;

SYS_MODULE_INFO( WoRmod_SPRX, 0, 1, 1);
SYS_MODULE_START( _WoRmod_SPRX_prx_entry );
SYS_MODULE_STOP( _WoRmod_SPRX_prx_stop );

sys_ppu_thread_t gTHPGThreadId= SYS_PPU_THREAD_ID_INVALID;

//q script networkplatformcomplete is called when everything is done

extern int g_hack_spoof_server_list;
extern int temp_socket_id;
void add_test_server() {
	Script::CStruct *cstruct = Script::AllocateCStruct(8,1);
	Script::AddChecksum(cstruct, -407168696, 123);
	Script::AddStringW(cstruct, 710733849, L"OpenSpy test"); //server_name
	Script::AddStringW(cstruct, -1741372166, L"Graffiti"); //game_type
	Script::AddStringW(cstruct, 1695888364, L"World"); //level
	Script::AddInteger(cstruct, 2128900964, 6); //qos
	Script::AddInteger(cstruct, 481470128, 0); //num_players
	Script::AddInteger(cstruct, 1296229917, 8); //max_players
	Script::AddInteger(cstruct, -1475614134, 1); //freq
	
	Script::RunScript(-1857340574, cstruct, 0, 0); //net_view_goals_add_server
}

bool g_hooked_dispatchers = false;


//0xE3CC98;
void *m_dispatchers[256];

uint64_t hooked_dispatcher(void *msg_context)
{
	GameNet::MsgHandlerContext *context = (GameNet::MsgHandlerContext *)msg_context;
	uint64_t (*real_dispatcher)(void *msg_context) = (uint64_t (*)(void *))m_dispatchers[context->m_MsgId];
	uint64_t r = real_dispatcher(msg_context);
	printf("Got Dispatched msg - %d, len: %d, result: %d - (%p)\n",context->m_MsgId, context->m_MsgLength, r, real_dispatcher);
	//r = 1;
	return r;
}
void hook_dispatchers(GameNet::Connection *conn) {
	for(int i=0;i<216;i++) {
		GameNet::DispatchHandlerEntry *handler = GetDispatchHandlerFromConn(conn, i);
		if(handler) {
			m_dispatchers[i] = handler->m_dispatch_func;
			handler->m_dispatch_func = (void *)&hooked_dispatcher;
		}
	}

}


void thpg_test_main_thread(uint64_t args) {	
	printf("gCD is %d\n", **gCD);

	//**gCD = 0;

	install_sys_hooks();
	//Mem::InitHooks();
	GameNet::InitHooks();
	
	CFuncs::RegisterCFuncs();

	Script::CSymbolTableEntry* join_symbol = Script::Resolve(406531533); //ScriptFCFSRequestStartGame
	printf("symbol: %p\n", join_symbol);

	//Tsk::test_tasks();

	if(join_symbol) {
		printf("symbol data: %p %d %d\n", join_symbol->union_type, join_symbol->type, join_symbol->sourceFileNameChecksum);
	}

	while(g_hack_spoof_server_list == 0) {
		_sys_timer_sleep(5);
	}

	printf("Running tests in 2 secs\n");
	_sys_timer_sleep(2);

	

	//Script::RunScript(-1733495016, NULL, 0, 0); //net_goals_test
	add_test_server();
	Script::RunScript(-981019151, NULL, 0, 0); //net_view_goals_found_all_servers

	while(temp_socket_id == -1) {
		_sys_timer_sleep(1);
	}

	GameNet::Connection *connection = (GameNet::Connection *)0x613100a0;
	//GameNet::Connection *connection = (GameNet::Connection *)0x61309b00;

	printf("SOCKET OPENED!\n");

	while(temp_socket_id != -1) {
		//if(g_hooked_dispatchers == false) {
		//	hook_dispatchers(connection);
		//	g_hooked_dispatchers = true;
		//}

		//printf("recv ptr: %p\n", connection->m_read_ptr);

		//TEMP_SERVER_IP, TEMP_SERVER_PORT
		char rbuff[1300];
		sockaddr_in from;
		socklen_t from_len = sizeof(from);
		int rlen = recvfrom(temp_socket_id, rbuff, sizeof(rbuff), 0,(sockaddr *) &from, &from_len);
		if(rlen > 0) {
			char *p = connection->m_read_ptr;
			for(int i=0;i<rlen;i++) {
				*p++ = rbuff[i];
			}
			GameNet::UpdateCommTimes(connection, 0);
			connection->m_read_ptr = p;

		}
	}

	//uint32_t load_qb_crc = 804315689;
	////Script::CStruct *cstruct = Script::AllocateCStruct(8,1);
	////Script::AddStringW(cstruct, 0, L"TEST.QB");
	//Script::RunScript(load_qb_crc, NULL, 0, 0);


	_sys_ppu_thread_exit(0);
}

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _WoRmod_SPRX_export_function(void)
{
    return CELL_OK;
}

extern "C" int _WoRmod_SPRX_prx_entry(void)
{
	sys_ppu_thread_create(&gTHPGThreadId, thpg_test_main_thread, 0, 3000, 4096 * 16, SYS_PPU_THREAD_CREATE_JOINABLE, "THPGTest");


   // Exit thread using directly the syscall and not the user mode library or else we will crash
   _sys_ppu_thread_exit(0);
    return SYS_PRX_RESIDENT;
}


extern "C" int _WoRmod_SPRX_prx_stop(void)
{
   uint64_t retVal;
   sys_ppu_thread_join(gTHPGThreadId, &retVal);

   // Exit thread using directly the syscall and not the user mode library or else we will crash
   _sys_ppu_thread_exit(0);

    return SYS_PRX_RESIDENT;
}
