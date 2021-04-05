#include "main.h"

void H_GoDFly(float timeDiff)
{
	if (cheat_state->genel.iGoDFly)
	{

		actor_info *actor = actor_info_get(ACTOR_SELF, NULL);
		if (actor == NULL) return;

		if (cheat_state->actor.fly_on) 
			return;
		if (cheat_state->actor.air_brake) 
			return;
		// v3'te buna bak.
		timeDiff *= 2.0f; // accelerate
		float ang = pGame->GetCamera()->GetCameraRotation();
		static float FlyUPSpeed = 0.0f;
		vect3_zero(actor->spin);
		SetActorZAngle(actor, ang, false);
		actor->vehicle_contact = (struct vehicle_info *)actor;
		GTAfunc_PerformAnimation("SHOP", "SHP_Jump_Land ", -1, 0, 1, 0, 0, 0, 0, 0);
		if (KEY_DOWN(GTA_KEY_D))
		{
			actor->speed[0] += cosf(ang)* set.General.fGodFlySpeed[0] * timeDiff;
			actor->speed[1] -= sinf(ang)* set.General.fGodFlySpeed[0] * timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_A))
		{
			actor->speed[0] -= cosf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
			actor->speed[1] += sinf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_S))
		{
			actor->speed[0] -= sinf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
			actor->speed[1] -= cosf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_W))
		{
			actor->speed[0] += sinf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
			actor->speed[1] += cosf(ang)* set.General.fGodFlySpeed[0] *timeDiff;
		}

		if (KEY_DOWN(GTA_KEY_SPACE))
		{
			actor->speed[2] += set.General.fGodFlySpeed[0] *timeDiff;
			FlyUPSpeed += set.General.fGodFlySpeed[1] *timeDiff;
			actor->base.matrix[4 * 3 + 2] += FlyUPSpeed;
		}
		else
			FlyUPSpeed = 0.0f; // accelerate up

		if (KEY_DOWN(GTA_KEY_LSHIFT))
		{
			actor->speed[2] - 3.5f *timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_X))
		{
			vect3_zero(actor->speed);
		}
	}
}
void H_GoDFlyVehicle(float timeDiff)
{
	if (cheat_state->genel.iGoDFly)
	{
		vehicle_info *vehicle = vehicle_info_get(VEHICLE_SELF, NULL);


		if (vehicle == NULL)
			return;
		if (cheat_state->vehicle.air_brake)
			return;
		timeDiff *= 10.0f; // accelerate

		float ang = pGame->GetCamera()->GetCameraRotation();
		static float FlyUPSpeed = 0.7f;
		vect3_zero(vehicle->spin);
		SetVehicleZAngle(vehicle, ang, false);

		if (KEY_DOWN(GTA_KEY_D))
		{
			vehicle->speed[0] += cosf(ang)*FlyUPSpeed*timeDiff;
			vehicle->speed[1] -= sinf(ang)*FlyUPSpeed*timeDiff;
		}

		if (KEY_DOWN(GTA_KEY_A))
		{
			vehicle->speed[0] -= cosf(ang)*FlyUPSpeed*timeDiff;
			vehicle->speed[1] += sinf(ang)*FlyUPSpeed*timeDiff;
		}

		if (KEY_DOWN(GTA_KEY_S))
		{
			vehicle->speed[0] -= sinf(ang)*FlyUPSpeed*timeDiff;
			vehicle->speed[1] -= cosf(ang)*FlyUPSpeed*timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_W))
		{
			vehicle->speed[0] += sinf(ang)*FlyUPSpeed*timeDiff;
			vehicle->speed[1] += cosf(ang)*FlyUPSpeed*timeDiff;
		}

		if (KEY_DOWN(GTA_KEY_SPACE))
		{
			vehicle->speed[2] += FlyUPSpeed*timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_LSHIFT))
		{
			vehicle->speed[2] -= FlyUPSpeed*timeDiff;
		}
		if (KEY_DOWN(GTA_KEY_X))
		{
			vect3_zero(vehicle->speed);
		}
	}
}

void H_DoNotSendKill()
{
	if (cheat_state->genel.iDo_Not_Send_Kill) 
	{
		struct actor_info *oyuncu = actor_info_get(ACTOR_SELF, NULL);
		if (oyuncu->hitpoints < 30.0f)
		{
			g_RakClient->SendSpawn();
			cheat_state->genel.iDo_Not_Send_Kill = 0;
		}
	}
}
void H_Spawn_at_Death_Position()
{
	if (cheat_state->genel.iSpawnAtDeathPos)
	{
		struct actor_info *pInfo = actor_info_get(ACTOR_SELF, 0);
		static int checkDeath = 0, interior;
		static float fPos[3];
		static DWORD time = GetTickCount();
		if (pInfo != NULL && checkDeath == 0 && ACTOR_IS_DEAD(pInfo))
		{
			vect3_copy(&pInfo->base.matrix[4 * 3], fPos);
			interior = gta_interior_id_get();
			checkDeath = 1;
		}
		if (pInfo != NULL && checkDeath == 1 && !ACTOR_IS_DEAD(pInfo))
		{
			if (GetTickCount() - time >= 2500)
			{
				playerSpawn();
				//g_RakClient->RPC(RPC_Spawn, &bs);
				cheat_teleport(fPos, interior);
				checkDeath = 0;
				time = GetTickCount();
			}
		}
	}
}
/*
	inCar.byteCurrentWeapon = 0;
	inCar.sUpDownKeys = 128;
	inCar.sLeftRightKeys = 128;
	inCar.sKeys = 4;
	//
	inCar.byteCurrentWeapon = 44 + rand() % 2;
	inCar.sUpDownKeys = 128;
	inCar.sLeftRightKeys = 128;
*/
void H_DiscoMode()
{
	if (cheat_state->genel.iDiscoMode)
	{
		static bool pfoot_State = false;
		if (pfoot_State == false)
		{
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));

			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];
			//cheat_state_text("Data0");
			onSync.byteCurrentWeapon = 0;
			onSync.sUpDownKeys = 128;
			onSync.sLeftRightKeys = 128;
			onSync.sKeys = 4;

			RakNet::BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
			for (int i = 0; i < 2; i++)
				g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			
			pfoot_State = true;
			//}
		}
		else
		{
			static DWORD tick = 200;
			DWORD now_tick = GetTickCount();
			if (now_tick - tick > 200)
			{
				//tick = now_tick;

				stOnFootData onSync;
				ZeroMemory(&onSync, sizeof(stOnFootData));

				onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
				onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

				onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
				onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
				onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

				onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
				onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
				onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];
				//cheat_state_text("Data1");
				onSync.byteCurrentWeapon = 44 + rand() % 2;
				onSync.sUpDownKeys = 128;
				onSync.sLeftRightKeys = 128;

				RakNet::BitStream bsData;
				bsData.Write((BYTE)ID_PLAYER_SYNC);
				bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
				for (int i = 0; i < 2; i++)
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				pfoot_State = false;
				tick = now_tick;
			}
		}
	}
}
void H_Pulsator()
{
	if (cheat_state->genel.iCanPulsator)
	{
		struct actor_info *info;

		for (int x = 0; x < 10; x++)
		{
			if ((info = actor_info_get(ACTOR_SELF, ACTOR_ALIVE)) != NULL)
			{
				static bool health_pulse_state;

				if (!health_pulse_state && info->hitpoints <= 1.0f)
					health_pulse_state = 1;

				else if (health_pulse_state && info->hitpoints >= 100.0f)
					health_pulse_state = 0;

				if (health_pulse_state)
					info->hitpoints++;
				else
					info->hitpoints--;
			}
		}
	}
}
void H_CameraMode()
{
	if (cheat_state->genel.iCameraMode)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info	*vinfo = vehicle_info_get(VEHICLE_SELF, 0);

		self->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
		self->fTargetRotation = self->fCurrentRotation;

		if (vinfo == NULL)
		{
			self->base.matrix[4] = sinf(-self->fCurrentRotation);
			self->base.matrix[5] = cosf(-self->fCurrentRotation);
		}
		else
		{
			if (vinfo->passengers[0] == self)
			{
				vinfo->base.matrix[4] = sinf(-self->fCurrentRotation);
				vinfo->base.matrix[5] = cosf(-self->fCurrentRotation);
			}
		}
	}
	return;
}
void H_PlayerDeformer()
{
	if (cheat_state->genel.iPlayerDeformer)
	{
		traceLastFunc("H_PlayerDeformer()");

		if (KEY_DOWN(set.General.key_playerdeformer1))
		{
			GTAfunc_PerformAnimation("PARACHUTE", "PARA_RIP_LOOP_O", -1, 1, 1, 0, 0, 1, 0, 1);
		}
		if (KEY_DOWN(set.General.key_playerdeformer2))
		{
			GTAfunc_PerformAnimation("PARACHUTE", "PARA_RIP_O", -1, 1, 1, 0, 0, 1, 0, 1);
		}
		if (KEY_DOWN(set.General.key_playerdeformer3))
		{
			GTAfunc_PerformAnimation("PARACHUTE", "PARA_STEERL_O", -1, 1, 1, 0, 0, 1, 0, 1);
		}
		if (KEY_DOWN(set.General.key_stop_playerdeformer))
		{
			//GTAfunc_DisembarkInstantly();
			GTAfunc_PerformAnimation("PARACHUTE", "PARA_RIP_LOOP_O", 1, 0, 1, 0, 0, 0, 0, 0);
		}
	}
}
void H_ArmorPulsator()
{
	if (cheat_state->genel.iZirhPulsator)
	{
		struct actor_info *info;

		for (int x = 0; x < 10; x++)
		{
			if ((info = actor_info_get(ACTOR_SELF, ACTOR_ALIVE)) != NULL)
			{
				static bool armor_pulse_state;

				if (!armor_pulse_state && info->armor <= 1.0f)
					armor_pulse_state = 1;

				else if (armor_pulse_state && info->armor >= 100.0f)
					armor_pulse_state = 0;

				if (armor_pulse_state)
					info->armor++;
				else
					info->armor--;
			}
		}
	}
}
void H_NoFall()
{
	if (cheat_state->genel.iNoFall == 1)
	{
		if (g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 0x469 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 0x4B8)
			GTAfunc_DisembarkInstantly();
	}
}
void H_AntiStun()
{
	if (cheat_state->genel.iAntiStun)
	{
		if (g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1087 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1177 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1078 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1073 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1079 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1077 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1081 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1075 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1084 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1083 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1085 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1083 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1086 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1072 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1175 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1076 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1074 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1082 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1173 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1178 ||
			g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1087 || g_Players->pLocalPlayer->onFootData.sCurrentAnimationID == 1078)
			GTAfunc_DisembarkInstantly();
	}
}

void H_WalkThroughWalls()
{
	if (cheat_state->genel.iWalkThroughWalls)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (self == NULL || ACTOR_IS_DEAD(self))
			return;

		if (KEY_DOWN('W'))
		{
			float fPos[2] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY };

			fPos[0] += sinf(-self->fCurrentRotation) * 0.09f;
			fPos[1] += cosf(-self->fCurrentRotation) * 0.09f;
			float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);
			pPedSelf->SetPosition(fPos[0], fPos[1], fGroundZHeight);
		}
	}
	return;
}
void H_SpeedWalk()
{
	if (cheat_state->genel.iSpeedWalk)
	{
		struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (self == NULL || ACTOR_IS_DEAD(self))
			return;
		if (KEY_DOWN('W'))
		{
			float fPos[3] = { pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ };
			fPos[0] += sinf(-self->fCurrentRotation) * set.General.SpeedWalk_X;
			fPos[1] += cosf(-self->fCurrentRotation) * set.General.SpeedWalk_X;
			fPos[2] += 0.02f;
			float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);
			//fPos[2] = fGroundZHeight + 1.0f;
			pPedSelf->SetPosition(fPos[0], fPos[1], fGroundZHeight);
		}
	}
}
void H_AllowCBUG()
{
	static bool bAllowCBug = false;
	if (cheat_state->Silah.iAllowCBUG)
	{
	if (cheat_state->Silah.iAllowTypeFreeze)
		pSecure->memcpy_safe((void*)(g_dwSAMP_Addr + 0x0168E0), "\xC3\x90", 2);
	if (cheat_state->Silah.iAllowTypeAnim)
		pSecure->memcpy_safe((void*)(g_dwSAMP_Addr + 0x016FA0), "\xC3\x90", 2);
	if (cheat_state->Silah.iAllowTypeWeapon)
		pSecure->memcpy_safe((void*)(g_dwSAMP_Addr + 0x015530), "\xC3\x90", 2);
	if (cheat_state->Silah.iAllowTypeText)
		pSecure->memcpy_safe((void*)(g_dwSAMP_Addr + 0x015F40), "\xC3\x90", 2);
		bAllowCBug = true;
	}
	else if (bAllowCBug)
	{
		memcpy_safe((void*)(g_dwSAMP_Addr + 0x0168E0), "\xE9\x49", 2);
		memcpy_safe((void*)(g_dwSAMP_Addr + 0x016FA0), "\x55\x8B", 2);
		memcpy_safe((void*)(g_dwSAMP_Addr + 0x015530), "\xE9\x18", 2);
		memcpy_safe((void*)(g_dwSAMP_Addr + 0x015F40), "\xE9\x2C", 2);
		bAllowCBug = false;
	}
}
void H_CarInvisible()
{
	if (cheat_state->Troll.iCarInvisible)
	{
		static DWORD tick = 150;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 150)
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

			stUnoccupiedData unSync;
			ZeroMemory(&unSync, sizeof(stUnoccupiedData));
			unSync.sVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

			vect3_copy(actor_info_get(ACTOR_SELF, NULL)->base.matrix + 12, unSync.fPosition);

			unSync.fHealth = 1000.0f;
			vect3_zero(unSync.fMoveSpeed);
			vect3_zero(unSync.fTurnSpeed);

			unSync.fDirection[0] = sqrt((float)-1);
			unSync.fDirection[1] = sqrt((float)-1);
			unSync.fDirection[2] = sqrt((float)-1);

			unSync.fRoll[0] = sqrt((float)-1);
			unSync.fRoll[1] = sqrt((float)-1);
			unSync.fRoll[2] = sqrt((float)-1);

			unSync.byteSeatID = NULL;

			RakNet::BitStream bsUnoccupiedSync;
			bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
			bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
			g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		}

	}
}
void Normal_Hileler(void)
{
	H_GoDFly(g_timeDiff);
	H_GoDFlyVehicle(g_timeDiff);
	H_DoNotSendKill();
	H_Spawn_at_Death_Position();
	H_DiscoMode();
	H_Pulsator();
	H_CameraMode();
	H_PlayerDeformer();
	H_ArmorPulsator();
	H_NoFall();
	H_AntiStun();
	H_WalkThroughWalls();
	H_SpeedWalk();
	H_AllowCBUG();
	H_CarInvisible();
}