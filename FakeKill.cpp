#include "main.h"
void F_FakeKill()
{
	//if (cheat_state->genel.iFakeKill)
	//{
	//	//cheat_state_text("12312321321");
	//	if (set.FakeKill_KillerID < 0)
	//		return;
	//	if (set.FakeKill_WeaponID < 0)
	//		return;
	//	if (set.FakeKill_Use_KillerID == true) // Eðer hedef seçme fonksiyonu açýksa.. if target choose is true..
	//	{
	//		int iKillerID = set.FakeKill_KillerID;
	//		if (set.FakeKill_Use_WeaponID == true)
	//		{
	//			int iWeaponID = set.FakeKill_WeaponID;
	//			g_RakClient->SendFakeKillDeath(set.FakeKill_KillerID, set.FakeKill_WeaponID);
	//		}
	//		else
	//		{
	//			int iWeaponID = rand() % 46;
	//			g_RakClient->SendFakeKillDeath(set.FakeKill_KillerID, iWeaponID);
	//		}
	//		//g_RakClient->SendFakeKillDeath(set.FakeKill_KillerID, rand() % 46);
	//	}
	//	else
	//	{
	//		int iWeaponID = rand() % 46;
	//		int iRandomKillerID = 0xFFFF + 1;
	//		while (!ValidPlayer(iRandomKillerID))
	//		{
	//			if (getPlayerCount() < 2)
	//			{
	//				iRandomKillerID = 0xFFFF;
	//				break;
	//			}

	//			iRandomKillerID = rand() % SAMP_MAX_PLAYERS;
	//		}
	//		if (iRandomKillerID != 0xFFFF + 1)
	//			g_RakClient->SendFakeKillDeath(iRandomKillerID, iWeaponID);
	//	}
	//}
}
void F_MultiFakeKill()
{
	//static DWORD dwMultiFakeKillDelay = GetTickCount();
	//int iMultiFakeKillWeaponID;
	//if (g_SAMP == NULL || g_Players == NULL || g_SAMP->iGameState != GAMESTATE_CONNECTED)
	//	return;
	//if (set.FakeKillSettings.bMultiFakeKill_UseSelectedWeapon == true)
	//	iMultiFakeKillWeaponID = set.FakeKillSettings.bMultiFakeKill_SelectedWeaponID;
	//else
	//	iMultiFakeKillWeaponID = rand() % 46;

	//if (cheat_state->genel.iMultiFakeKill && GetTickCount() - dwMultiFakeKillDelay >= set.FakeKillSettings.dwMultiFakeKill_Delay)
	//{
	//	int iRandomKillerID = 0xFFFF + 1;
	//	while (!ValidPlayer(iRandomKillerID))
	//	{
	//		if (getPlayerCount() < 2)
	//		{
	//			iRandomKillerID = 0xFFFF;
	//			break;
	//		}

	//		iRandomKillerID = rand() % SAMP_MAX_PLAYERS;
	//	}
	//	if (iRandomKillerID != 0xFFFF + 1)
	//		g_RakClient->SendFakeKillDeath(iRandomKillerID, iMultiFakeKillWeaponID);
	//	dwMultiFakeKillDelay = GetTickCount();
	//}
}
void FakeKill()
{
	F_FakeKill();
	F_MultiFakeKill();
}