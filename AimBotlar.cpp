#include "main.h"

float CalculateDamage(void)
{
	WORD gun = g_Players->pLocalPlayer->byteCurrentWeapon;
	float dmg = 0.0f;
	if (gun == 24 || gun == 38) dmg = 46.200000762939453125f;
	if (gun == 22 || gun == 29) dmg = 8.25f;
	if (gun == 23) dmg = 13.200000762939453125f;
	if (gun == 28 || gun == 32) dmg = 6.6000003814697265625f;
	if (gun == 30 || gun == 31) dmg = 9.90000057220458984375f;
	if (gun == 33) dmg = 24.7500019073486328125f;
	if (gun == 34) dmg = 41.25f;
	if (gun == 25 || gun == 26)
	{
		int shotrandom = rand() % 8 + 1;
		switch (shotrandom)
		{
		case 1:
			dmg = 26.4000015258789f;
			break;
		case 2:
			dmg = 29.70000171661377f;
			break;
		case 3:
			dmg = 33.00000190734863f;
			break;
		case 4:
			dmg = 36.30000209808349f;
			break;
		case 5:
			dmg = 39.60000228881836f;
			break;
		case 6:
			dmg = 42.90000247955322f;
			break;
		case 7:
			dmg = 46.20000267028808f;
			break;
		case 8:
			dmg = 49.50000286102295f;
			break;
		}
	}
	if (gun == 27)
	{
		int shotrandom2 = rand() % 4 + 1;
		switch (shotrandom2)
		{
		case 1:
			dmg = 24.75000143051147f;
			break;
		case 2:
			dmg = 29.70000171661376f;
			break;
		case 3:
			dmg = 34.65000200271606f;
			break;
		case 4:
			dmg = 39.60000228881835f;
			break;
		}
	}
	return dmg;
}

byte CalculateSpreadOffset(WORD targetID, float* target_pos, float* out_spread)
{
	actor_info* actorInfo = g_Players->pRemotePlayer[targetID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
	if (actorInfo == nullptr) 
		return 255;
	CPed* Ped = pGameInterface->GetPools()->GetPed((DWORD*)actorInfo);
	if (Ped == nullptr) 
		return 255;
	byte player_state = g_Players->pRemotePlayer[targetID]->pPlayerData->bytePlayerState;
	if (player_state == PLAYER_STATE_ONFOOT)
	{
		CVector rbody;
		byte bodyIDs[28] = { 1, 2, 3, 4, 5, 6, 7, 8, 21, 22, 23, 24, 25, 26, 31, 32, 33, 34, 35, 36, 41, 42, 43, 44, 51, 52, 53, 54 };
		cheat_state->Silent.iSilentBone = bodyIDs[rand() % 27];
		Ped->GetTransformedBonePosition((eBone)bodyIDs[rand() % 27], &rbody);
		out_spread[0] = rbody.fX - target_pos[0];
		out_spread[1] = rbody.fY - target_pos[1];
		out_spread[2] = rbody.fZ - target_pos[2];
	}
	else if (player_state == PLAYER_STATE_DRIVER || player_state == PLAYER_STATE_PASSENGER)
	{
		byte bodyIDs[3] = { 8, 7, 6 };
		CVector head;
		cheat_state->Silent.iSilentBone = bodyIDs[rand() % 2]; // Buna elleme...
		Ped->GetTransformedBonePosition((eBone)bodyIDs[rand() % 2], &head);
		out_spread[0] = head.fX - target_pos[0];
		out_spread[1] = head.fY - target_pos[1];
		out_spread[2] = head.fZ - target_pos[2];
		return 9;
	}
	enum eBone {
		BONE_PELVIS1 = 1,
		BONE_PELVIS,
		BONE_SPINE1,
		BONE_UPPERTORSO, // 4
		BONE_NECK,
		BONE_HEAD2,
		BONE_HEAD1,
		BONE_HEAD,
		BONE_RIGHTUPPERTORSO = 21, //
		BONE_RIGHTSHOULDER,
		BONE_RIGHTELBOW,
		BONE_RIGHTWRIST,
		BONE_RIGHTHAND,
		BONE_RIGHTTHUMB,
		BONE_LEFTUPPERTORSO = 31,
		BONE_LEFTSHOULDER,
		BONE_LEFTELBOW,
		BONE_LEFTWRIST,
		BONE_LEFTHAND,
		BONE_LEFTTHUMB,
		BONE_LEFTHIP = 41,
		BONE_LEFTKNEE,
		BONE_LEFTANKLE,
		BONE_LEFTFOOT,
		BONE_RIGHTHIP = 51,
		BONE_RIGHTKNEE,
		BONE_RIGHTANKLE,
		BONE_RIGHTFOOT
	};
	if (cheat_state->Silent.iSilentBone == 5 || cheat_state->Silent.iSilentBone == 8 || cheat_state->Silent.iSilentBone == 7 || cheat_state->Silent.iSilentBone == 6) 
		return 9; // Head
	if (cheat_state->Silent.iSilentBone == 4 || cheat_state->Silent.iSilentBone == 21|| cheat_state->Silent.iSilentBone == 3|| cheat_state->Silent.iSilentBone == 31) 
		return 3; // Torso
	if (cheat_state->Silent.iSilentBone == 2 || cheat_state->Silent.iSilentBone == 1) 
		return 4; // Groin
	if (cheat_state->Silent.iSilentBone == 34 || cheat_state->Silent.iSilentBone == 33 || cheat_state->Silent.iSilentBone == 35 || cheat_state->Silent.iSilentBone == 32 || cheat_state->Silent.iSilentBone == 36)
		return 5; // Left Arm
	if (cheat_state->Silent.iSilentBone == 24 || cheat_state->Silent.iSilentBone == 23 || cheat_state->Silent.iSilentBone == 25 || cheat_state->Silent.iSilentBone == 22 || cheat_state->Silent.iSilentBone == 26) 
		return 6; // Right Arm
	if (cheat_state->Silent.iSilentBone == 43 || cheat_state->Silent.iSilentBone == 44 || cheat_state->Silent.iSilentBone == 42 || cheat_state->Silent.iSilentBone == 41) 
		return 7; // Left Leg
	if (cheat_state->Silent.iSilentBone == 53 || cheat_state->Silent.iSilentBone == 54 || cheat_state->Silent.iSilentBone == 52 || cheat_state->Silent.iSilentBone == 51) 
		return 8; // Right Leg
	return 255;
}
