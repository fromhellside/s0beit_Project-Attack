#include "main.h"
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
void C_PassengerCrasher()
{
	if (cheat_state->crasher.iPublicPassengerCrasher)
	{
		static DWORD tick = 100;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 100)
		{
			actor_info *self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info * vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_CLOSEST |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			float fPos[3];// = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };
			float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F }; // Crasher için gerekli.

			fPos[0] += 0.5f;

			vect3_copy(&self->base.matrix[12], fPos);
			if (self->state == CHEAT_STATE_ACTOR)
			{
				g_RakClient->SendFakePassengerSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, vehicle->hitpoints, g_Players->pLocalPlayer->byteCurrentWeapon, 1, 128);
				g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//				cheat_state_text("Pass Roll Crasher!");
//#endif
				g_RakClient->SendFakeUnoccupiedSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
				g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));
				tick = now_tick;
			}
			tick = now_tick;
		}
	}
}

void C_HighfRollCrasher() 
{
	if (cheat_state->crasher.iRollCrasher1)
	{
		static DWORD tick = 150;
		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 150)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_CLOSEST |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			float fPos[3];
			float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };

			vect3_copy(&self->base.matrix[12], fPos);
		/*	vehicle->base.matrix[4 * 1 + 1];
			vehicle->base.matrix[4 * 1 - 1];*/

			//fPos[0] += 5.0;
			int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			if (GetTickCount() - tick > 150)
			{
			
				g_RakClient->SendEnterPlayerVehicle(iVehicleID, 1);
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//				cheat_state_text("High Roll Crasher!");
//#endif
				g_RakClient->SendFakeUnoccupiedSyncData(iVehicleID, 1, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
				g_RakClient->SendExitPlayerVehicle(iVehicleID);
				tick = now_tick;
			}
			tick = now_tick;
		}
	}
}

void C_RemovePlayerCrasher()
{
	if (cheat_state->crasher.iPublicRemovePlayerCrasher)
	{
		patch_set* pspp = &set.patch[18];
		patcher_install(pspp);
		float fPos_[3];
		float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
		fPos_[0] = coord[0], fPos_[1] = coord[1], fPos_[2] = coord[2];

		bool static foot_state = false;

		static DWORD tick = 150;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 150) // Delay 280'den 150'ye düşürüldü.
		{
			static bool normalize = false;

			if (!foot_state)
			{
				stOnFootData footData;
				ZeroMemory(&footData, sizeof(stOnFootData));

				footData.fPosition[0] = coord[0];
				footData.fPosition[1] = coord[1];
				footData.fPosition[2] = coord[2];

				footData.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
				footData.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
				footData.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

				footData.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
				footData.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

				RakNet::BitStream bsData;
				bsData.Write((BYTE)ID_PLAYER_SYNC);
				bsData.Write((PCHAR)&footData, sizeof(stOnFootData));
				for (int i = 0; i < 2; i++)
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				foot_state = true;
			}
			else
			{
				RakNet::BitStream bs;
				for (int i = 0; i < 2; i++)
				g_RakClient->RPC(RPC_Spawn, &bs);
				foot_state = false;
			}
			tick = now_tick;
		}
	}
	else
	{
		patch_set* pspp = &set.patch[18];
		patcher_remove(pspp);
	}
	/*if (cheat_state->crasher.iPublicRemovePlayerCrasher)
	{
		static bool bState = false;
		const auto near_players = NearPlayers(g_Players->sLocalPlayerID, 300, true);
		if (!near_players.size()) return;
		const int players_count = near_players.size();

		static DWORD dwRunDelay = 100;
		const auto near_vehicles = NearVehicles(g_Players->sLocalPlayerID, 300, true);
		if (!near_vehicles.size()) return;
		const auto index = random(0, near_vehicles.size());
		if (index >= near_vehicles.size()) return;
		const auto VehicleID = near_vehicles.at(index);
		if (GetTickCount() - dwRunDelay > 100)
		{
			if (!bState)
			{
				stOnFootData OnFootData;
				memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				RakNet::BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
				g_RakClient->Send(&bsOnFoot);
				bState = true;
			}
			else
			{
				cheat_state_text("[Private Detonator Crasher] Crashing %i players around...", players_count);
				stOnFootData OnFootData;
				memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				OnFootData.sSurfingVehicleID = -1;
				RakNet::BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
				g_RakClient->Send(&bsOnFoot);
				g_RakClient->SendEnterPlayerVehicle(VehicleID, 1);
				g_RakClient->SendExitPlayerVehicle(VehicleID);
				bState = false;
			}
			dwRunDelay = GetTickCount();
		}
	}*/
}
void C_TuningCrasher()
{
	if (cheat_state->crasher.iPublicTuningCrasher)
	{
		actor_info *me = actor_info_get(VEHICLE_SELF, NULL);
		if (me->state != CHEAT_STATE_VEHICLE)
		{
			vehicle_info * vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_CARS_ONLY |
					VEHICLE_NOT_TRAIN);
			if (!vehicle)
				return;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//			cheat_state_text("Tuning Crasher!");
//#endif
			g_RakClient->SendFakeDriverSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), vehicle->base.matrix + 12, vehicle->hitpoints, vehicle->speed);
			sendSCMEvent(2, getSAMPVehicleIDFromGTAVehicle(vehicle), 1000 + rand() % 199, NULL);
		}
		else
		{
			sendSCMEvent(2, g_Players->pLocalPlayer->sLastVehicleID, 1000 + rand() % 199, NULL);
		}

	}
}
 
/*
-> Crash atılabilecek datalar.
	
	int16_t sVehicleID;
	uint8_t byteSeatID;
	float	fRoll[3];
	float	fDirection[3];
	float	fPosition[3];
	float	fMoveSpeed[3];
	float	fTurnSpeed[3];
	
*/

void C_InvalidBulletsCrasher1()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher1)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{
	
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = 0x15F90;
					unSync.fTurnSpeed[1] = 0x15F90;
					unSync.fTurnSpeed[2] = 0x15F90;
					unSync.byteSeatID = 1;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("fTurnSpeed -> X: %0.2f", unSync.fTurnSpeed[0]);
//#endif
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}

void C_InvalidBulletsCrasher2()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher2)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{

			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = 50000.0f;
					unSync.fTurnSpeed[1] = 50000.0f;
					unSync.fTurnSpeed[2] = 50000.0f;
					unSync.byteSeatID = 1;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("fTurnSpeed -> X: %0.2f", unSync.fTurnSpeed[0]);
//#endif
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}

void C_InvalidBulletsCrasher3()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher3)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{

			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];

				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));

				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					float frandomcrasher = random_float(1500.0f, 10000.0f);
					if(set.invalidBullets.bSendGiveDamage)
						g_RakClient->SendGiveDamage(PlayerID, fWeaponDamage[WeaponID], WeaponID, 3);
					else
						g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					stUnoccupiedData unSync;
					ZeroMemory(&unSync, sizeof(stUnoccupiedData));
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = frandomcrasher;
					unSync.fTurnSpeed[1] = frandomcrasher;
					unSync.fTurnSpeed[2] = frandomcrasher;
					unSync.byteSeatID = 1;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("fTurnSpeed -> X: %0.2f", unSync.fTurnSpeed[0]);
//#endif
					g_RakClient->SendEnterPlayerVehicle(VehicleID, unSync.byteSeatID);
					RakNet::BitStream bsUnoccupiedSync;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		/*			g_RakClient->SendExitPlayerVehicle(VehicleID);*/
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}
/*
	bu n surf ile posiyonu kopyalayip karşinin invaild value gönnderiyor
	siksen çalişmaz hiç bi yerde
	ben olsam unocu surfu vs çikaririm direk direc ve dur neydi onun adı
	bi sn
	posX ve Y noplar Zye neg value koyarim, noplu spec atar camtypeı 3e çekerim
	invaid bullette spec bypassliyr ve millet hala bunu bilmiyosa aq
	tabi ilk yapilacak şey fbllet kullanmamak bunun için, fakebullet vs eyvallah valid bi silahın emülasyonunu yapsan daa garantisi olur
	bunuda iki şeyle başarirsin, ateş ettiğinde kickleyen serverler genelde onWepShot kullanir ve sahte pos gönderirsin her saniyede 0.0.0 gibi mesela ondan sonra kendi posiyonunu atarsin ve silah modelini destroylarsin
	~ Ezel.
*/
void C_InvalidBulletsCrasher4()
{
	if (cheat_state->crasher.iInvalidBulletsCrasher4)
	{
		static DWORD tick = set.invalidBullets.dwDelayOfInvalidBullets;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > set.invalidBullets.dwDelayOfInvalidBullets)
		{
			

			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;

			vehicle_info* vehicle =
				GetVehicleInfoStandart(
					VEHICLE_NO_BE_PROTECT |
					VEHICLE_NOT_FRIEND |
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NOT_CLOSED,
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE |
					VEHICLE_NOT_TRAIN);

			if (!vehicle)
				return;

			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			if (KEY_DOWN(VK_LBUTTON))
			{
				float fPos[3];
				vect3_copy(vehicle->base.matrix + 12, fPos);
				int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));
				float fOrigin[3], fTarget[3], fCenter[3];
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;
				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					float frandomcrasher = random_float(-1000.0f, -10000.0f);
					g_RakClient->SendGiveDamage(PlayerID, fWeaponDamage[WeaponID], WeaponID, 3);
					//g_RakClient->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = set.invalidBullets.fOnFootPosZ;
					onSync.fSurfingOffsets[2] = -5.4f;
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					float fSpin[3] = { -1000.0f, -1000.0f,-1000.0f }, fRoll[3] = { -2500.0f,-5000.0f,-5000.0f };
					g_RakClient->SendFakeUnoccupiedSyncData(VehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints, fSpin, fRoll);
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}
void C_RollCrasher1()
{
	if (cheat_state->crasher.iRollCrasher1)
	{
		static DWORD tick = 150;
		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 150)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;
			
			float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };
			float fPos[3];
			fPos[0] += 5.0;

			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					vehicle_info* vehicle =
						GetVehicleInfoStandart(
							VEHICLE_NO_BE_PROTECT |
							VEHICLE_NOT_FRIEND |
							VEHICLE_NOT_OCCUPIED |
							VEHICLE_NOT_CLOSED,
							VEHICLE_NEXT |
							VEHICLE_NOT_MY |
							VEHICLE_ALIVE |
							VEHICLE_NOT_TRAIN);

					if (!vehicle)
						return;

					int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
					//cheat_state_text("fRoll-Roll[0] = %f", fRoll[0]);
					g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
					g_RakClient->SendFakeUnoccupiedSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
					g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}
void C_RollCrasher2()
{
	if (cheat_state->crasher.iRollCrasher2)
	{
		static DWORD tick = 150;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 150)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;
			
			//float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };
			float randomroll = random_float(-10000.0f, 10000.0f);
			float fPos[3];
			fPos[0] += 0.4f;
			float spin[3] = { 0,1,0 };
			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					vehicle_info* vehicle =
						GetVehicleInfoStandart(
							VEHICLE_NO_BE_PROTECT |
							VEHICLE_NOT_FRIEND |
							VEHICLE_NOT_OCCUPIED |
							VEHICLE_NOT_CLOSED,
							VEHICLE_NEXT |
							VEHICLE_NOT_MY |
							VEHICLE_ALIVE |
							VEHICLE_NOT_TRAIN);

					if (!vehicle)
						return;

					int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
					g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
					g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));
					stUnoccupiedData picSync;
					memset(&picSync, 0, sizeof(stUnoccupiedData));
					RakNet::BitStream bsUnoccupiedSync;
					picSync.sVehicleID = VehicleID;
					picSync.byteSeatID = 1;
					struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(VehicleID);
					/*picSync.fDirection[0] = sqrt((float)-1);
					picSync.fDirection[1] = sqrt((float)-1);
					picSync.fDirection[2] = sqrt((float)-1);*/
					picSync.fDirection[0] = vinfo->base.matrix[4 * 1 + 0];
					picSync.fDirection[1] = vinfo->base.matrix[4 * 1 + 1];
					picSync.fDirection[2] = vinfo->base.matrix[4 * 1 + 2];
					picSync.fRoll[0] = randomroll;
					picSync.fRoll[1] = randomroll;
					picSync.fRoll[2] = randomroll;
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//					cheat_state_text("Roll Crasher #2 : %0.2f",randomroll);
//#endif
					picSync.fPosition[0] = fPos[0];
					picSync.fPosition[1] = fPos[1];
					picSync.fPosition[2] = fPos[2];
					picSync.fMoveSpeed[0] = vinfo->speed[0];
					picSync.fMoveSpeed[1] = vinfo->speed[1];
					picSync.fMoveSpeed[2] = vinfo->speed[2];
					picSync.fTurnSpeed[0] = spin[0];
					picSync.fTurnSpeed[1] = spin[1];
					picSync.fTurnSpeed[2] = spin[2];
					picSync.fHealth = vinfo->hitpoints;
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsUnoccupiedSync.Write((PCHAR)&picSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				}
			}
			tick = now_tick;
		}
	}
}

void C_DirectionCrasher1()
{
	if (cheat_state->crasher.iDirectionCrasher1)
	{
		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;
		float fDirection[3] = { -50000.0f, -50000.0f, 10000.0f };
		float fPos[3];
		float fRoll[3] = { 1,0,1 };
		fPos[0] += 5.0;
		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NO_BE_PROTECT |
				VEHICLE_NOT_FRIEND |
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;

		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		static DWORD tick = 100;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 100)
		{
			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					//cheat_state_text("fRoll-Roll[0] = %f", fRoll[0]);
					g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
					g_RakClient->SendFuckingTrailerData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, fRoll, fDirection, vehicle->speed);
					g_RakClient->SendFullFakeUnoccupiedFuckingSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fDirection, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
					g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));
				}
			}
			tick = now_tick;
		}
	}
}
void C_DirectionCrasher2()
{
	if (cheat_state->crasher.iDirectionCrasher2)
	{
		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;
		/*float fRandomDirection[3] = { random_float(1000.0f, 10000.0f) };*/
		float fRoll[3] = { 1,0,1 };
		float fPos[3];
		float fDirection[3] = { 9750.0f, 10000.0f, 50010.0f };
		float fTurnSpeed[3] = { sqrt((float)-1), sqrt((float)-1), sqrt((float)-1) };
		fPos[0] += 5.0;
		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NO_BE_PROTECT |
				VEHICLE_NOT_FRIEND |
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;

		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		static DWORD tick = 100;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick >100)
		{
			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					//cheat_state_text("fRoll-Roll[0] = %f", fRoll[0]);
					g_RakClient->SendFuckingTrailerData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, fRoll, fDirection, vehicle->speed);
				
					g_RakClient->SendFullFakeUnoccupiedFuckingSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fDirection, fPos, vehicle->speed, vehicle->hitpoints = 1000, fTurnSpeed, fRoll);
//#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//						cheat_state_text("Direction Crasher #2");
//#endif
					g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
					/*g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));*/
					tick = now_tick;
				}
			}
			tick = now_tick;
		}
	}
}
void GameSoundCrasher()
{
	if (cheat_state->crasher.iGameSoundCrasher)
	{
		static DWORD tick = 150;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 150)
		{
			actor_info* self = actor_info_get(ACTOR_SELF, NULL);
			if (!self)
				return;
			vehicle_info* vehicle =
				GetVehicleInfoForceFlags(
					VEHICLE_NOT_OCCUPIED |
					VEHICLE_NEXT |
					VEHICLE_NOT_MY |
					VEHICLE_ALIVE);
			if (!vehicle)
				return;
			//tick = now_tick;
			float fRoll[3] = { 6,6,6 };
			float fPos[3];
			fPos[1] += 0.5f;
			float fDirection[3] = { 0,0,0 }; // fSoundCrasher'in Z ekseninin değerini 1111.0f'ten, 999.9f'e çektim.
			float fSoundCrasherValue[3] = { 998.6f, 1000.0f, 999.9f };
			//float fCrasherPos[3] = { 19789.0f, 10001.f, 20001.0f };
			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			vect3_copy(&self->base.matrix[12], fPos);
			if (KEY_DOWN(VK_LBUTTON))
			{
				if (self->state == CHEAT_STATE_ACTOR)
				{
					stOnFootData onSync;
					ZeroMemory(&onSync, sizeof(stOnFootData));
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = fPos[2] - 1.0f;
					onSync.fSurfingOffsets[2] = g_Players->pLocalPlayer->onFootData.fSurfingOffsets[2];
					onSync.sSurfingVehicleID = VehicleID;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_PLAYER_SYNC);
					bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					g_RakClient->SendFakeUnoccupiedSyncData(VehicleID, 0, fPos, vehicle->speed, vehicle->hitpoints, fSoundCrasherValue, fRoll);
				}
			}
			tick = now_tick;
		}
	}
}
void C_WeaponCrasher()
{
	if (cheat_state->crasher.iWeaponCrasher)
	{
		static DWORD dwWeaponCrasherMS = 75;
		if (GetTickCount() - dwWeaponCrasherMS > 75)
		{
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));
			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
			onSync.sKeys = 128;
			onSync.byteCurrentWeapon = 40;
			onSync.fMoveSpeed[0] = 0.19f;
			vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12], onSync.fPosition);
			RakNet::BitStream fBit;
			fBit.Write((BYTE)ID_PLAYER_SYNC);
			fBit.Write((PCHAR)&onSync, sizeof(stOnFootData));
			g_RakClient->Send(&fBit);
			dwWeaponCrasherMS = GetTickCount();
		}
	}
}
void Crashers(void)
{
	C_PassengerCrasher(); // MasterZero
	C_HighfRollCrasher(); // Copied MasterZero
	C_RemovePlayerCrasher(); // NIEX -> V2'de paylaşılacak.
	C_TuningCrasher(); // MasterZero -> V2'de paylaşılacak.
	C_InvalidBulletsCrasher1();
	C_InvalidBulletsCrasher2();
	C_InvalidBulletsCrasher3();
	C_InvalidBulletsCrasher4();
	C_RollCrasher1();
	C_RollCrasher2();
	C_DirectionCrasher1();
	C_DirectionCrasher2();
	GameSoundCrasher();
};
#endif