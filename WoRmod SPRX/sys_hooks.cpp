#include "main.h"

#include <np.h>

/*
void sub_36363C() = calls getnpid & _sceNp_sceNpManagerRequestTicket: 

 sub_354C0C = calls getcontentratingflag


  sub_346930 = some async callback??


  sub_347068 = online related cfunc?
*/

//games registers np callback
opd_s cb_t = { (0x354AEC),  BASE_TOC };
int64_t (*NPManagerCallback)(int64_t)  = (int64_t (*)(int64_t ))&cb_t;	

int hooked_sceNpManagerGetStatus(int *status) {
	printf("hooked_sceNpManagerGetStatus %p\n", status);
	*status = SCE_NP_MANAGER_STATUS_ONLINE;

	//fake NP manager callback

	NPManagerCallback(*status);
	return CELL_OK;
}


int hooked_sceNpInit(size_t poolsize,void *poolptr) {
	printf("hooked_sceNpInit %d %p\n", poolsize, poolptr);
	return CELL_OK;
}

int hooked_sceNpManagerRegisterCallback(void *callback, void *userdata) {
	printf("hooked_sceNpManagerRegisterCallback %p %p\n", callback, userdata);
	return CELL_OK;
}

int hooked_cellSysutilGetSystemParamInt( int id, int *value ) {
	printf("hooked_cellSysutil_cellSysutilGetSystemParamInt %d %p\n", id, value);

	if (id == 0x141) { //has np account
		*value = 1;
		printf("set has account\n");
	}
	return CELL_OK;
}

int hooked_cellNetCtlNetStartDialogLoadAsync( void *param ) {
	printf("hooked_cellNetCtlNetStartDialogLoadAsync %p\n", param);

	opd_s cb_t = { (0x354C8C),  BASE_TOC };
	int64_t (*NetCtlManagerCallback)(int64_t)  = (int64_t (*)(int64_t ))&cb_t;	
	NetCtlManagerCallback(0x0802); //CELL_SYSUTIL_NET_CTL_NETSTART_FINISHED

	return CELL_OK;
}

int hooked_cellNetCtlNetStartDialogUnloadAsync( void *param ) {
	printf("hooked_cellNetCtlNetStartDialogUnloadAsync %p\n", param);

	opd_s cb_t = { (0x354C8C),  BASE_TOC };
	int64_t (*NetCtlManagerCallback)(int64_t)  = (int64_t (*)(int64_t ))&cb_t;	
	NetCtlManagerCallback(0x0803); //CELL_SYSUTIL_NET_CTL_NETSTART_UNLOADED

	//int *p_test = (int *)param;
	//p_test[1] = 1; (simulate pre-demonware error)

	return CELL_OK;
}

int hooked_sceNpManagerGetNpId(SceNpId *onlineId) {
	printf("hooked_sceNpManagerGetNpId\n");

	//char *t = (char *)&onlineId->handle.data[0];
	//t[0] = 'H';
	//t[1] = 'e';
	//t[2] = 'l';
	//t[3] = 'l';
	//t[4] = 'o';
	//t[5] = 0;
	return CELL_OK;
}

int hooked_sceNpManagerRequestTicket(
	const SceNpId *npId,
	const char *serviceId,
	const void *cookie,
	size_t cookieSize,
	const char *entitlementId,
	unsigned int consumedCount
	) {
		printf("hooked_sceNpManagerRequestTicket\n");

		//char *t = (char *)&npId->handle.data[0];
		//t[0] = 'H';
		//t[1] = 'e';
		//t[2] = 'l';
		//t[3] = 'l';
		//t[4] = 'o';
		//t[5] = 0;
		return CELL_OK;
}

int hooked_sceNpManagerGetContentRatingFlag(
	int *isRestricted,
	int *age
	) {
	printf("sceNpManagerGetContentRatingFlag\n");
	*isRestricted = 0;
	return CELL_OK;
}

void install_sys_hooks() {
	int (**sceNpManagerGetStatusPtr)(int *) = (int (**)(int *))0xE0E358;
	*sceNpManagerGetStatusPtr = hooked_sceNpManagerGetStatus;

	int (**sceNpInitPtr)(size_t, void *) = (int (**)(size_t, void *))0xE0E360;
	*sceNpInitPtr = hooked_sceNpInit;

	int (**sceNpManagerRegisterCallbackPtr)(void *, void *) = (int (**)(void *, void *))0xE0E314;
	*sceNpManagerRegisterCallbackPtr = hooked_sceNpManagerRegisterCallback;

	int (**cellSysutilGetSystemParamIntPtr)(int, int *) = (int (**)(int, int *))0xE0E304;
	*cellSysutilGetSystemParamIntPtr = hooked_cellSysutilGetSystemParamInt;	

	int (**cellNetCtlNetStartDialogLoadAsyncPtr)(void *) = (int (**)(void *))0xE0E238;
	*cellNetCtlNetStartDialogLoadAsyncPtr = hooked_cellNetCtlNetStartDialogLoadAsync;

	int (**cellNetCtlNetStartDialogUnloadAsyncPtr)(void *) = (int (**)(void *))0xe0e23C;
	*cellNetCtlNetStartDialogUnloadAsyncPtr = hooked_cellNetCtlNetStartDialogUnloadAsync;

	int (**sceNpManagerGetNpIdPtr)(SceNpId *) = (int (**)(SceNpId *))0xE0E370;
	*sceNpManagerGetNpIdPtr = hooked_sceNpManagerGetNpId;

	int (**sceNpManagerRequestTicketPtr)(const SceNpId *, const char *, const void *,size_t , const char *, unsigned int ) = 
		(int (**)(const SceNpId *, const char *, const void *,size_t , const char *, unsigned int ))0xE0E354;
	*sceNpManagerRequestTicketPtr = hooked_sceNpManagerRequestTicket;

	int (**sceNpManagerGetContentRatingFlagPtr)(int *, int *) = (int (**)(int *, int *))0xE0E350;
	*sceNpManagerGetContentRatingFlagPtr = hooked_sceNpManagerGetContentRatingFlag;

	NPManagerCallback(3);
}