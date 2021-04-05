#include "main.h"
 
void GetInfoTargetDebug(char* result, int bufflen, int playerid)
{

	if (playerid != INVALID)
	{
		int version = cheat_state->PrivateControlPanel.ControlProjectUser[playerid].bytes.Version;
		actor_info* actor = getGTAPedFromSAMPPlayerID(playerid);
		if (cheat_state->PrivateControlPanel.ControlProjectUser[playerid].have_projectattack)
		{
				sprintf_s(result, bufflen, "[Yakında]%s[ID:%i]:Versiyon: %i", getPlayerName(playerid), playerid, cheat_state->PrivateControlPanel.ControlProjectUser[playerid].projectver);
		}else
			strcpy(result, "");
		// Bunu(altındaki satırı) commentline yaptım ama test etmedim...
		//sprintf_s(result, bufflen, "%s ",result); //CT: %i  compile_type, 
		//if (cheat_state->PrivateControlPanel.ControlProjectUser[playerid].projectver != BEMOD_CONTROL_DEFAULT)
		//	sprintf_s(result, bufflen, "%s sürüm: %i", result, cheat_state->PrivateControlPanel.ControlProjectUser[playerid].projectver);
		return;
	}
	
}
int OnRecieveControlPanelHook(WORD playerid, stAimBEData* BE_sync)
{
	if (BE_sync->wIdentification6 != BEMOD_IDENTIFIER
		|| BE_sync->wIdentification5 != BEMOD_IDENTIFIER
		|| BE_sync->wIdentification1 != BEMOD_IDENTIFIER
		
		)
		return 0;
	
	DWORD	recieve_value = BE_sync->w_BE_Value;
	byte	compile_type = BE_sync->info.bytes.Compile_Type;
	byte	ver = BE_sync->info.bytes.Version;
	DWORD	for_playerid = BE_sync->info.for_playerid;

	cheat_state->PrivateControlPanel.ControlProjectUser[playerid].have_projectattack = true;
	cheat_state->PrivateControlPanel.ControlProjectUser[playerid].projectver = recieve_value;
	cheat_state->PrivateControlPanel.ControlProjectUser[playerid].bytes.Compile_type = compile_type;
	cheat_state->PrivateControlPanel.ControlProjectUser[playerid].bytes.Version = ver;

	return 1;
}
void OnSendControlPanelHook(stAimBEData* BE_sync)
{

	static long tick = 0;
	if (tick++ < 5)
		return;
	tick = 0;
	BE_sync->wIdentification6 =
	BE_sync->wIdentification5 =
	BE_sync->wIdentification1 =
	BEMOD_IDENTIFIER;

	BE_sync->w_BE_Value = BEMOD_CONTROL_DEFAULT;
	// 17.11.2020 | 01:15 ~ Proje, her sürüm atladığında bunu update et.
	BE_sync->info.bytes.Version = DETECTOR_PROJECTVERSION_ID;
	// FİXLE.
	/*
	#define COMPILE_TYPE_ENGLISH 1
	#define COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION 2
	#define COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION 3
	#define COMPILE_TYPE_TURKISH_HELPER_VERSION 4
	#define COMPILE_TYPE_TURKISH_THELIFE_VERSION 5
	#define COMPILE_TYPE_TURKISH_HELLSIDE_VERSION 6
	#define COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION 7
	*/
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE; 
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION;
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION;
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_HELPER_VERSION;
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_THELIFE_VERSION;
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_HELLSIDE_VERSION;
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	BE_sync->info.bytes.Compile_Type = COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION;
#endif
}
void ProjectAttack_initialize()
{

	cheat_state->PrivateControlPanel.exit = false;
	cheat_state->PrivateControlPanel.ThreadProjectAttack = CreateThread(NULL, NULL, ProjectAttack_Thread, NULL, NULL, NULL);
	//bemod->bemod_protection.ignore_bemod_players = false;
	//bemod->bemod_protection.send_protect_packets = true;
	//bemod->LoadingScreen = true;
	//bemod->fHelper.OnGameInit();

}


DWORD WINAPI ProjectAttack_Thread(LPVOID lpThreadParameter)
{
#define THREAD_SLEEP 2
	for (; true; Sleep(THREAD_SLEEP))
	{
		traceLastFunc("BEMod_Thread()");
		if (cheat_state->PrivateControlPanel.exit)
			break;

		if (!g_SAMP)
			continue;

		if (!g_Players)
			continue;

		if (!g_RakClient->GetInterface()->IsConnected())
		{
			for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
				cheat_state->PrivateControlPanel.ControlProjectUser[i].have_projectattack = false;
		}
		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!g_Players->iIsListed[i] && cheat_state->PrivateControlPanel.ControlProjectUser[i].have_projectattack)
				cheat_state->PrivateControlPanel.ControlProjectUser[i].have_projectattack = false;
		}
	}

	return 0;
}
