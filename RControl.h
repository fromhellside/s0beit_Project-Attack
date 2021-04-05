#include "main.h"
 

void GetInfoTargetDebug(char* result, int bufflen, int playerid);
int OnRecieveControlPanelHook(WORD playerid, stAimBEData* BE_sync);

enum bemod_control_panel_value
{
	BEMOD_IDENTIFIER = 228,
	BEMOD_CONTROL_DEFAULT = 2, // max - 65535
};
void OnSendControlPanelHook(struct stAimBEData* BE_sync);
void ProjectAttack_initialize();
DWORD WINAPI ProjectAttack_Thread(LPVOID lpThreadParameter);