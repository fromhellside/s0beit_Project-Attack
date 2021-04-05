#include "main.h"
#include "math_stuff.h"

void TH_PlayerShooter(stInCarData *AracVerisi)
{
	if (!g_SAMP)
		return;
	if (cheat_state->_generic.cheat_panic_enabled)
		return;
	if (!cheat_state->Troll.iPlayerShooter)
		return;
	if (!KEY_DOWN(VK_LBUTTON))
		return;
	if (cheat_state->state != CHEAT_STATE_VEHICLE)
		return;
	int iTargetPlayerID = cheat_state->Troll.iPlayerShooterHedef;
	if (!ValidPlayer(iTargetPlayerID))
		return;
	if (getPlayerState(iTargetPlayerID) != PLAYER_STATE_DRIVER)
		return;
	uint16_t sTargetVehicleID = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.sVehicleID;
	if (!ValidVehicle(sTargetVehicleID))
		return;
	AracVerisi->sVehicleID = sTargetVehicleID;
	AracVerisi->fVehicleHealth = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fVehicleHealth;
	AracVerisi->byteCurrentWeapon = g_Players->pLocalPlayer->byteCurrentWeapon;
	vect3_copy(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fPosition, AracVerisi->fPosition);
	vect3_copy(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fMoveSpeed, AracVerisi->fMoveSpeed);
	if (cheat_state->Troll.iPlayerShooter)
	{
		float fSpeed[3]; // X,Y,Z Hýz dizisi.
		fSpeed[0] = random_float(0.19282, 0.83711);
		fSpeed[1] = random_float(0.19282, 0.83711);
		fSpeed[2] = random_float(0.2f, 0.4f);
		g_RakClient->SendEnterPlayerVehicle(sTargetVehicleID, 0);
		AracVerisi->fMoveSpeed[0] = fSpeed[0];
		AracVerisi->fMoveSpeed[1] = fSpeed[1];
		AracVerisi->fMoveSpeed[2] = fSpeed[2];
		
		//g_RakClient->SendUnoccupiedSyncData(sTargetVehicleID, AracVerisi->fPosition, AracVerisi->fVehicleHealth, fSpeed, 1);
		g_RakClient->SendFakeTrailerData(sTargetVehicleID, AracVerisi->fPosition, AracVerisi->fVehicleHealth, AracVerisi->fMoveSpeed);
		g_RakClient->SendUnoccupiedSyncData(sTargetVehicleID, AracVerisi->fPosition, AracVerisi->fVehicleHealth, AracVerisi->fMoveSpeed, 1);
		g_RakClient->SendExitPlayerVehicle(sTargetVehicleID);
	}
}
void TH_PlayerShooterTargetFinder()
{
	if (cheat_state->Troll.iPlayerShooter)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		if (!g_SAMP)
			return;

		if (cheat_state->state != CHEAT_STATE_VEHICLE)
		{
			cheat_state->Troll.iPlayerShooter = 0;
			cheat_state->Troll.iPlayerShooterHedef = 0xFFFF;
			return;
		}

		int iClosestVehicleGTAID = vehicle_find_nearest(VEHICLE_ALIVE + VEHICLE_NOTBURNING + VEHICLE_OCCUPIED);
		struct vehicle_info* pClosestVehicle = vehicle_info_get(iClosestVehicleGTAID, 0);
		unsigned short usClosestVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(pClosestVehicle);

		if (ValidVehicle(usClosestVehicleSAMPID))
		{
			struct actor_info* target = g_Vehicles->pGTA_Vehicle[usClosestVehicleSAMPID]->passengers[0];
			if (target != NULL && target != self)
			{
				int HedefOyuncuID = getSAMPPlayerIDFromGTAPed(target);
				if (ValidPlayer(HedefOyuncuID))
				{
					cheat_state->Troll.iPlayerShooterHedef = HedefOyuncuID;
					return;
				}
			}
		}
		cheat_state->Troll.iPlayerShooterHedef = 0xFFFF;
	}
}

void TH_iTrollFeatures(stInCarData* pInCarData)
{
	if (!g_SAMP)
		return;

	if (cheat_state->_generic.cheat_panic_enabled)
		return;

	if (!cheat_state->Troll.iTroll)
		return;

	if (!KEY_DOWN(VK_LBUTTON))
		return;

	if (cheat_state->state != CHEAT_STATE_VEHICLE)
		return;

	int iTargetPlayerID = cheat_state->Troll.iTrollTargetID;

	if (!ValidPlayer(iTargetPlayerID))
		return;

	if (getPlayerState(iTargetPlayerID) != PLAYER_STATE_DRIVER)
		return;

	uint16_t sTargetVehicleID = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.sVehicleID;

	if (!ValidVehicle(sTargetVehicleID))
		return;
	
	stTrailerData trailerData;
	ZeroMemory(&trailerData, sizeof(stTrailerData));
	pInCarData->sVehicleID = sTargetVehicleID;
	pInCarData->fVehicleHealth = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fVehicleHealth;
	pInCarData->byteCurrentWeapon = g_Players->pLocalPlayer->byteCurrentWeapon;
	vect4_copy(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fQuaternion, pInCarData->fQuaternion);
	vect3_copy(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fPosition, pInCarData->fPosition);
	vect3_copy(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->inCarData.fMoveSpeed, pInCarData->fMoveSpeed);
	g_RakClient->SendFakeTrailerData(pInCarData->sTrailerID, pInCarData->fPosition, NULL, pInCarData->fMoveSpeed);
	switch (cheat_state->Troll.iTroll)
	{
	case 1:
	{
		struct actor_info* ainfo = getGTAPedFromSAMPPlayerID(iTargetPlayerID);

		if (ainfo != NULL)
		{
			CPed* pPed = pGameInterface->GetPools()->GetPed((DWORD*)ainfo);
			float fGroundZHeight = pGame->GetWorld()->FindGroundZFor3DPosition(pPed->GetPosition());
			pInCarData->fPosition[2] = fGroundZHeight - 0.25f;
			pInCarData->fQuaternion[0] = 0.707107;
			pInCarData->fQuaternion[1] = -0.707107;
			pInCarData->fQuaternion[2] = 0;
			pInCarData->fQuaternion[3] = 0;
		}
		break;
	}

	case 2:
	{
		struct actor_info* ainfo = getGTAPedFromSAMPPlayerID(iTargetPlayerID);

		if (ainfo != NULL)
		{
			g_RakClient->SendEnterPlayerVehicle(sTargetVehicleID, 0);
			float fSpeed[2] = { sinf(-ainfo->fCurrentRotation) * 2,cosf(-ainfo->fCurrentRotation) * 2 };
			pInCarData->fMoveSpeed[0] = fSpeed[0];
			pInCarData->fMoveSpeed[1] = fSpeed[1];
			g_RakClient->SendUnoccupiedSyncData(sTargetVehicleID, pInCarData->fPosition, pInCarData->fVehicleHealth, pInCarData->fMoveSpeed, 0);
		}
		break; 
	}

	case 3: 
	{
		float* coords = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;

		pInCarData->fVehicleHealth = 1.0f;
		pInCarData->fPosition[0] = coords[0] + random_float(20, 25);
		pInCarData->fPosition[1] = coords[1] + random_float(20, 25);
		pInCarData->fPosition[2] = coords[2] + random_float(10, 15);
		pInCarData->fMoveSpeed[2] = -(random_float(4, 10));
		break;
	}

	case 4:
	{
		pInCarData->fVehicleHealth = 0.0f;
		pInCarData->fMoveSpeed[0] = random_float(0, 2);
		pInCarData->fMoveSpeed[1] = random_float(0, 2);
		pInCarData->fMoveSpeed[2] = random_float(4, 10);
		break;
	}

	case 5: 
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			tVector right, up, at;
			float fRight[3], fUp[3];
			vect3_copy(&vinfo->base.matrix[4 * 0], fRight);
			vect3_copy(&vinfo->base.matrix[4 * 1], fUp);
			vect3_invert(fRight, fRight);
			vect3_invert(fUp, fUp);
			right.X = fRight[0];
			right.Y = fRight[1];
			right.Z = fRight[2];
			up.X = fUp[0];
			up.Y = fUp[1];
			up.Z = fUp[2];
			at.X = vinfo->base.matrixStruct->at.X;
			at.Y = vinfo->base.matrixStruct->at.Y;
			at.Z = vinfo->base.matrixStruct->at.Z;
			MatrixToQuaternion2(&right, &up, &at, pInCarData->fQuaternion[0], pInCarData->fQuaternion[1], pInCarData->fQuaternion[2], pInCarData->fQuaternion[3]);
			vect3_invert(pInCarData->fMoveSpeed, pInCarData->fMoveSpeed);
		}
		break;
	}
	case 6:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			pInCarData->fQuaternion[0] = 0;
			pInCarData->fQuaternion[1] = 1;
			pInCarData->fQuaternion[2] = 0;
			pInCarData->fQuaternion[3] = 0;
		}
		break;
	}
	case 7: 
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			pInCarData->fVehicleHealth = 1.0f;
		}
		break;
	}
	case 8: 
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			pInCarData->fPosition[0] = -1569.4526f;
			pInCarData->fPosition[1] = 98.3293f;
			pInCarData->fPosition[2] = 20.0894f;
		}
		break;
	}
	case 9:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float fSpeed[3] = { vinfo->speed[0], vinfo->speed[1], 1.0f };
			vinfo->speed[2] = fSpeed[2];
			pInCarData->fMoveSpeed[0] = fSpeed[0];
			pInCarData->fMoveSpeed[1] = fSpeed[1];
			pInCarData->fMoveSpeed[2] = fSpeed[2];
		}
		break;
	}
	case 10:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float pos[3] = { 7.14f, 35.22f, 3.11f };
			float Speed[3] = {};
			pInCarData->fPosition[0] = pos[0];
			pInCarData->fPosition[1] = pos[1];
			pInCarData->fPosition[2] = pos[2];
		}
		break;
	}
	case 11:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float pos[3] = { 3609.00f, 971.37f, 27.31f };
			pInCarData->fPosition[0] = pos[0];
			pInCarData->fPosition[1] = pos[1];
			pInCarData->fPosition[2] = pos[2];
		}
		break;
	}
	case 12: 
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float Speed[3] = { 0,0,0 };
			pInCarData->fMoveSpeed[0] = Speed[0];
			pInCarData->fMoveSpeed[1] = Speed[1];
			pInCarData->fMoveSpeed[2] = Speed[2];
		}
		break;
	}
	case 13:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float pos[3] = { -2048.06f, 251.36f, 31.97f };
			pInCarData->fPosition[0] = pos[0];
			pInCarData->fPosition[1] = pos[1];
			pInCarData->fPosition[2] = pos[2];
		}
		break;
	}
	case 14: 
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			pInCarData->fVehicleHealth = set.itrollSettings.fSetHP;
		}
		break;
	}
	case 15:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float fDeger = random_float(1.0f, 1000.0f);
			pInCarData->fVehicleHealth = fDeger;
		}
		break;
	}
	case 16:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL) 
		{
			pInCarData->fQuaternion[0] = random_float(-0.0f,1.0f);
			pInCarData->fQuaternion[1] = random_float(-0.0f, 1.0f);
			pInCarData->fQuaternion[2] = random_float(-0.0f, 1.0f);
			pInCarData->fQuaternion[3] = random_float(-0.0f, 1.0f);
		}
		break;
	}
	case 17:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			float pos[3] = { random_float(-2000.0f,5000.0f), random_float(-2000.0f,5000.0f), random_float(-100.0f,100.0f) };
			pInCarData->fPosition[0] = pos[0];
			pInCarData->fPosition[1] = pos[1];
			pInCarData->fPosition[2] = pos[2];
		}
		break;
	}
	case 18:
	{
		struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(sTargetVehicleID);
		if (vinfo != NULL)
		{
			pInCarData->fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			pInCarData->fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			pInCarData->fPosition[2] += 500.0f;
			pInCarData->fVehicleHealth = 1.0f;
		}
		break;
	}
	}
}

void TH_iTrollFeaturesTargetFinder()
{
	if (cheat_state->Troll.iTroll)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		if (!g_SAMP)
			return;

		if (cheat_state->state != CHEAT_STATE_VEHICLE)
		{
			cheat_state->Troll.iTroll = 0;
			cheat_state->Troll.iTrollTargetID = 0xFFFF;
			return;
		}

		int iClosestVehicleGTAID = vehicle_find_nearest(VEHICLE_ALIVE + VEHICLE_NOTBURNING + VEHICLE_OCCUPIED);
		struct vehicle_info* pClosestVehicle = vehicle_info_get(iClosestVehicleGTAID, 0);
		unsigned short usClosestVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle(pClosestVehicle);

		if (ValidVehicle(usClosestVehicleSAMPID))
		{
			struct actor_info* target = g_Vehicles->pGTA_Vehicle[usClosestVehicleSAMPID]->passengers[0];

			if (target != NULL && target != self)
			{
				int HedefOyuncuID = getSAMPPlayerIDFromGTAPed(target);

				if (ValidPlayer(HedefOyuncuID))
				{
					cheat_state->Troll.iTrollTargetID = HedefOyuncuID;
					return;
				}
			}
		}
		cheat_state->Troll.iTrollTargetID = 0xFFFF;
	}
}

void TH_Elevator()
{
	if (cheat_state->Troll.iElevator)
	{
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (!ainfo)
			return;
		int iTargetPlayerID = GetClosestPlayerid(ainfo, ACTOR_ALIVE | ACTOR_NOT_ME);
		actor_info* deadman = getGTAPedFromSAMPPlayerID(iTargetPlayerID);
		if (!deadman)
			return;
		static DWORD dwTickMS = 100;
		if (GetTickCount() - dwTickMS > 100)
		{
			if (IsPlayerStreamed(iTargetPlayerID))
			{
				stOnFootData OnFoot;
				memcpy(&OnFoot, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				vect3_copy(&g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], OnFoot.fPosition);
				OnFoot.fPosition[0] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[0]
					* 10.97f;
				OnFoot.fPosition[1] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[1]
					* 10.97f;
				OnFoot.fPosition[2] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[2]
					* 10.97f;
				OnFoot.fQuaternion[0] = 0.50f;
				OnFoot.fQuaternion[1] = -0.50f;
				OnFoot.fQuaternion[2] = 0.50f;
				OnFoot.fQuaternion[3] = 0.50f;
				OnFoot.fMoveSpeed[0] = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTAEntity->speed[0] * 1.5f;
				OnFoot.fMoveSpeed[1] = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTAEntity->speed[1] * 1.5f;
				OnFoot.fMoveSpeed[2] = 10.0f;
				RakNet::BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFoot, sizeof(stOnFootData));
				g_RakClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			}
			dwTickMS = GetTickCount();
		}
	}
}
void TH_Jetpack_Elevator()
{
	if (cheat_state->Troll.iJetpackElevator)
	{
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (!ainfo)
			return;
		int iTargetPlayerID = GetClosestPlayerid(ainfo, ACTOR_ALIVE | ACTOR_NOT_ME);
		actor_info* deadman = getGTAPedFromSAMPPlayerID(iTargetPlayerID);
		if (!deadman)
			return;
		static DWORD dwTickMS = 100;
		if (GetTickCount() - dwTickMS > 100)
		{
			if (IsPlayerStreamed(iTargetPlayerID))
			{
				stOnFootData OnFoot;
				memcpy(&OnFoot, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
				vect3_copy(&g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], OnFoot.fPosition);
				OnFoot.fPosition[0] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[0]
					* 10.97f;
				OnFoot.fPosition[1] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[1]
					* 10.97f;
				OnFoot.fPosition[2] += g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed[2]
					* 10.97f;
				OnFoot.byteSpecialAction = 2;
				OnFoot.fQuaternion[0] = 0.50f;
				OnFoot.fQuaternion[1] = -0.50f;
				OnFoot.fQuaternion[2] = 0.50f;
				OnFoot.fQuaternion[3] = 0.50f;
				OnFoot.fMoveSpeed[0] = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTAEntity->speed[0] * 1.5f;
				OnFoot.fMoveSpeed[1] = g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->pSAMP_Actor->pGTAEntity->speed[1] * 1.5f;
				OnFoot.fMoveSpeed[2] = 10.0f;
				RakNet::BitStream bsOnFoot;
				bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
				bsOnFoot.Write((PCHAR)&OnFoot, sizeof(stOnFootData));
				g_RakClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			}
			dwTickMS = GetTickCount();
		}
	}
}
void TH_VehicleTrollCar(struct vehicle_info *vinfo, float time_diff)
{
	static int		once = 1;
	static float	fLastHitpoints;
	if (cheat_state->Troll.iTrollCar2)
	{
		struct vehicle_info	*vtemp;
		for (vtemp = vinfo; vtemp != NULL; vtemp = vtemp->trailer)
		{
			if (vtemp == NULL)
				return;
			if (once == 1)
			{
				fLastHitpoints = vtemp->hitpoints;
				vtemp->hitpoints = 1.0f;
				once = 0;
			}
			vtemp->m_nVehicleFlags.bCanBeDamaged = false;
			vtemp->flags &= ~2;
			if (!set.trailer_support)
				break;
		}
	}
	else
	{
		if (once == 0)
		{
			struct vehicle_info	*vtemp;
			for (vtemp = vinfo; vtemp != NULL; vtemp = vtemp->trailer)
			{
				if (vtemp == NULL)
					return;
				vtemp->hitpoints = fLastHitpoints;
				vtemp->m_nVehicleFlags.bCanBeDamaged = true;
				if (!set.trailer_support)
					break;
			}
			once = 1;
		}
	}

}
void TH_CircleTroll()
{
	if (cheat_state->Troll.iCircleTroll)
	{
		struct actor_info *minfo = actor_info_get(ACTOR_SELF, NULL);
		int iPlayerID;
		if (set.TrollCheats.CircleTrollTargetID == g_Players->sLocalPlayerID) 
			return;
		if (set.TrollCheats.CircleTrollTargetID > INVALID)
			iPlayerID = set.TrollCheats.CircleTrollTargetID;
		actor_info *actor = getGTAPedFromSAMPPlayerID(iPlayerID);
		stRemotePlayer *pPlayer = g_SAMP->pPools->pPlayer->pRemotePlayer[iPlayerID];

		if (!actor)
			return;
		if (!minfo)
			return;

		static DWORD ticktak = 0;
		DWORD not_tick_tak = GetTickCount();
		if (not_tick_tak - ticktak > set.TrollCheats.CircleTroll_Spin_Speed)
		{
			ticktak = not_tick_tak;
			if (IsPlayerStreamed(iPlayerID))
			{
				vect3_copy(&actor->fCurrentRotation, &minfo->fCurrentRotation);
				float fCircle = set.TrollCheats.CircleTroll_Circle_Radius;
				float fPos[3];
				vect3_copy(&actor->base.matrix[4 * 3], fPos);
				static int x = 0;
				fPos[0] += fCircle * sin(180 * x / 3.1415);
				fPos[1] += fCircle * cos(180 * x / 3.1415);
				x++;
				cheat_actor_teleport(minfo, fPos, gta_interior_id_get());
			}
		}
	}
}
void TH_CarRemoteControl()
{
	if (cheat_state->Troll.iCarRemoteControl)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, 0);

		if (vinfo != NULL)
		{
			if (set.CarCheats.car_remote_control_with_driver && !set.CarCheats.car_remote_control_without_driver)
			{
				
				int iPlayerID = FindNearestSAMPPlayer(false, &self->base.matrix[4 * 3]);
				struct actor_info* ainfo = getGTAPedFromSAMPPlayerID(iPlayerID);

				if (ainfo == NULL || ainfo->vehicle == NULL || ainfo == self || ainfo->vehicle == vinfo
					|| getPlayerSAMPVehicleID(iPlayerID) == NULL || getPlayerSAMPVehicleID(iPlayerID) == g_Players->pLocalPlayer->sCurrentVehicleID
					|| getPlayerState(iPlayerID) != PLAYER_STATE_DRIVER && getPlayerState(iPlayerID) != PLAYER_STATE_PASSENGER)
					return;

				struct vehicle_info* vtemp = ainfo->vehicle;
				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vtemp);

				float fPos[3];
				vect3_copy(&vtemp->base.matrix[4 * 3], fPos);

				stInCarData vehSync;
				memset(&vehSync, 0, sizeof(stInCarData));

				vehSync.sVehicleID = iSAMPVehicleID;
				vehSync.fPosition[0] = fPos[0];
				vehSync.fPosition[1] = fPos[1];
		
				vehSync.fPosition[2] = vinfo->base.matrix[4 * 3 + 2];
				vehSync.fVehicleHealth = vtemp->hitpoints;
				vehSync.fMoveSpeed[0] = vinfo->speed[0];
				vehSync.fMoveSpeed[1] = vinfo->speed[1];
				vehSync.fMoveSpeed[2] = vinfo->speed[2];
				vehSync.fQuaternion[0] = g_Players->pLocalPlayer->inCarData.fQuaternion[0];
				vehSync.fQuaternion[1] = g_Players->pLocalPlayer->inCarData.fQuaternion[1];
				vehSync.fQuaternion[2] = g_Players->pLocalPlayer->inCarData.fQuaternion[2];
				vehSync.fQuaternion[3] = g_Players->pLocalPlayer->inCarData.fQuaternion[3];
				vehSync.bytePlayerHealth = self->hitpoints;
				vehSync.byteArmor = self->armor;
				vehSync.sLeftRightKeys = g_Players->pLocalPlayer->inCarData.sLeftRightKeys;
				vehSync.sUpDownKeys = g_Players->pLocalPlayer->inCarData.sUpDownKeys;
				vehSync.sKeys = g_Players->pLocalPlayer->inCarData.sKeys;

				g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
				vtemp->speed[0] = vinfo->speed[0];
				vtemp->speed[1] = vinfo->speed[1];
				vtemp->speed[2] = vinfo->speed[2];
			}
			else if (!set.CarCheats.car_remote_control_with_driver && set.CarCheats.car_remote_control_without_driver)
			{
				static int	carUsed[SAMP_MAX_VEHICLES];
				static int	nearestCar = 0;

				static bool	carFound = false;

				if (carFound == false)
				{
					float fPos[3];
					vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

					float fSmallestDistance = -1.0f;

					for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
					{
						if (g_Vehicles->iIsListed[v] != 1)
							continue;

						int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
						struct vehicle_info* vtemp = vehicle_info_get(car_id, 0);

						if (vtemp == NULL || vtemp == vinfo)
							continue;

						if (carUsed[v] == 1)
							continue;

						int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vtemp);
						if (iSAMPVehicleID <= 0 || iSAMPVehicleID >= SAMP_MAX_VEHICLES || iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
							continue;

						float car_pos[3];
						vect3_copy(&vtemp->base.matrix[4 * 3], car_pos);

						float fDistance = vect3_dist(car_pos, fPos);

						if (fSmallestDistance == -1.0f)
						{
							fSmallestDistance = fDistance;

							nearestCar = v;
						}

						if (fDistance < fSmallestDistance)
						{
							fSmallestDistance = fDistance;

							nearestCar = v;
						}
					}

					if (nearestCar == 0)
					{
						for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
							carUsed[i] = 0;

						return;
					}

					carFound = true;
				}

				if (carFound == true)
				{
					if (nearestCar <= 0 || nearestCar >= SAMP_MAX_VEHICLES || nearestCar == g_Players->pLocalPlayer->sCurrentVehicleID)
					{
						nearestCar = 0;
						carFound = false;
						return;
					}

					struct vehicle_info* vtemp = getGTAVehicleFromSAMPVehicleID(nearestCar);
					if (vtemp == NULL || vtemp == vinfo)
					{
						nearestCar = 0;
						carFound = false;
						return;
					}

					carUsed[nearestCar] = 1;

					float fPos[3];
					vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

					fPos[1] += 8.0f;

					float fQuaternion[4];

					if (vinfo->passengers[0] != self)
					{
						int iPlayerID = getSAMPPlayerIDFromGTAPed(vinfo->passengers[0]);
						if (iPlayerID == -1)
						{
							fQuaternion[0] = vinfo->base.matrix[3];
							fQuaternion[1] = vinfo->base.matrix[6];
							fQuaternion[2] = vinfo->base.matrix[5];
							fQuaternion[3] = vinfo->base.matrix[4];
						}
						else
						{
							fQuaternion[0] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[0];
							fQuaternion[1] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[1];
							fQuaternion[2] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[2];
							fQuaternion[3] = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fQuaternion[3];
						}
					}
					else
					{
						fQuaternion[0] = g_Players->pLocalPlayer->inCarData.fQuaternion[0];
						fQuaternion[1] = g_Players->pLocalPlayer->inCarData.fQuaternion[1];
						fQuaternion[2] = g_Players->pLocalPlayer->inCarData.fQuaternion[2];
						fQuaternion[3] = g_Players->pLocalPlayer->inCarData.fQuaternion[3];
					}

					stInCarData vehSync;
					memset(&vehSync, 0, sizeof(stInCarData));

					vehSync.sVehicleID = nearestCar;
					vehSync.fPosition[0] = fPos[0];
					vehSync.fPosition[1] = fPos[1];
					vehSync.fPosition[2] = fPos[2];
					vehSync.fVehicleHealth = vtemp->hitpoints;
					vehSync.fMoveSpeed[0] = vinfo->speed[0];
					vehSync.fMoveSpeed[1] = vinfo->speed[1];
					vehSync.fMoveSpeed[2] = vinfo->speed[2];
					vehSync.fQuaternion[0] = fQuaternion[0];
					vehSync.fQuaternion[1] = fQuaternion[1];
					vehSync.fQuaternion[2] = fQuaternion[2];
					vehSync.fQuaternion[3] = fQuaternion[3];
					vehSync.bytePlayerHealth = self->hitpoints;
					vehSync.byteArmor = self->armor;
					vehSync.sLeftRightKeys = g_Players->pLocalPlayer->inCarData.sLeftRightKeys;
					vehSync.sUpDownKeys = g_Players->pLocalPlayer->inCarData.sUpDownKeys;
					vehSync.sKeys = g_Players->pLocalPlayer->inCarData.sKeys;
					vehSync.byteLandingGearState = g_Players->pLocalPlayer->inCarData.byteLandingGearState;
					vehSync.byteSiren = g_Players->pLocalPlayer->inCarData.byteSiren;
					vehSync.byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

					g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
					//cheat_vehicle_teleport( vtemp, fPos, gta_interior_id_get() );
					vtemp->speed[0] = vinfo->speed[0];
					vtemp->speed[1] = vinfo->speed[1];
					vtemp->speed[2] = vinfo->speed[2];
					vtemp->base.matrix[0] = vinfo->base.matrix[0];
					vtemp->base.matrix[1] = vinfo->base.matrix[1];
					vtemp->base.matrix[2] = vinfo->base.matrix[2];
					vtemp->base.matrix[3] = vinfo->base.matrix[3];
					vtemp->base.matrix[4] = vinfo->base.matrix[4];
					vtemp->base.matrix[5] = vinfo->base.matrix[5];
					vtemp->base.matrix[6] = vinfo->base.matrix[6];
					vtemp->base.matrix[7] = vinfo->base.matrix[7];
					vtemp->base.matrix[8] = vinfo->base.matrix[8];
					vtemp->base.matrix[9] = vinfo->base.matrix[9];
					vtemp->base.matrix[10] = vinfo->base.matrix[10];
					vtemp->base.matrix[11] = vinfo->base.matrix[11];
					vtemp->base.matrix[12] = vinfo->base.matrix[12];
					vtemp->base.matrix[13] = fPos[1];
					vtemp->base.matrix[14] = vinfo->base.matrix[14];
					vtemp->base.matrix[15] = vinfo->base.matrix[15];
					//matrix_copy( vinfo->base.matrix, vtemp->base.matrix );
				}
			}
		}
		else
		{
			//addMessageToChatWindow("Bir aracýn içinde olman gerek.");
			cheat_state->Troll.iCarRemoteControl = 0;
			return;
		}
	}
	return;
}

void TH_InvisibleSpec()
{
	if (cheat_state->Troll.iInvisible4)
	{
		stSpectatorData specSync;
		ZeroMemory(&specSync, sizeof(stSpectatorData));
		if (g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle)
		{
			for (short x = 0; x < 3; x++)
				specSync.fPosition[x] = g_Players->pLocalPlayer->inCarData.fPosition[x];
		}
		else
		{
			for (short x = 0; x < 3; x++)
				specSync.fPosition[x] = g_Players->pLocalPlayer->onFootData.fPosition[x];
		}
		RakNet::BitStream bsSpec;
		bsSpec.Write((BYTE)ID_SPECTATOR_SYNC);
		bsSpec.Write((PCHAR)&specSync, sizeof(stSpectatorData));
		g_RakClient->Send(&bsSpec, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}

void TH_InvisibleBike()
{
	static DWORD dwInvisibleTick = GetTickCount();
	static int times = 0;
	if (cheat_state->Troll.iInvisibleBike)
	{
		bool wrong_way = false;
		if (g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle)
		{
			int vehicleID = g_Players->pLocalPlayer->inCarData.sVehicleID;
			vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, 0);
			if (!vinfo)
				return;
			if (vinfo->vehicle_type == VEHICLE_TYPE_BIKE)
			{
				if (GetTickCount() - dwInvisibleTick >= 1000)
				{
					stOnFootData OnFootData;
					memset(&OnFootData, 0, sizeof(stOnFootData));
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],OnFootData.fPosition);
					OnFootData.byteArmor = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->armor;
					OnFootData.byteHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
					RakNet::BitStream bsOnFoot;
					bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
					bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
					g_RakClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					//for uif protection
					RakNet::BitStream bsEnterVehicle;
					bsEnterVehicle.Write(vehicleID);
					bsEnterVehicle.Write(0);
					g_RakClient->RPC(RPC_EnterVehicle, &bsEnterVehicle);
					dwInvisibleTick = GetTickCount();
					times++;
				}
			}
			else
			{
				wrong_way = true;
			}
		}
		else
		{
			wrong_way = true;
		}
		if (wrong_way)
		{
			//char* error_message = "Motor veya bisiklet sürüyor olman gerek";
			//cheat_state_text(error_message);
		}
	}
}
void TH_Invisible7()
{
	if (cheat_state->Troll.iInvisible7)
	{
		RakNet::BitStream bsData;
		stSpectatorData InvisHack;
		memset(&InvisHack, 0, sizeof(stSpectatorData));
		//bEditFootSync = true;
		vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12], InvisHack.fPosition);
		InvisHack.sLeftRightKeys = 0;
		InvisHack.sUpDownKeys = 0;
		InvisHack.sKeys = 0;
		bsData.Reset();
		bsData.Write((BYTE)ID_SPECTATOR_SYNC);
		bsData.Write((PCHAR)&InvisHack, sizeof(stSpectatorData));
		g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}
void TH_Invisible9()
{
	if (cheat_state->Troll.iInvisible9)
	{
		static DWORD dwInvisPosSendRate = 3250;
		if (GetTickCount() - dwInvisPosSendRate > 3250)
		{
			stOnFootData OnFootData;
			memset(&OnFootData, 0, sizeof(stOnFootData));
			float fPos[3];
			vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12], fPos);
			OnFootData.fPosition[0] = fPos[0];
			OnFootData.fPosition[1] = fPos[1];
			OnFootData.fPosition[2] = fPos[2];
			OnFootData.byteArmor = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->armor;
			OnFootData.byteHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
			RakNet::BitStream bsOnFoot;
			bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
			bsOnFoot.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
			g_RakClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			dwInvisPosSendRate = GetTickCount();
		}
	}
}
void TH_VehicleDeformer()
{
	if (cheat_state->Arac.iVehicleDeformer)
	{
		actor_info* ainfo = actor_info_get(ACTOR_SELF, NULL);
		if (!ainfo)
			return;

		vehicle_info* vehicle =
			GetVehicleInfoForceFlags(
				VEHICLE_NEXT |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE
			);
		if (!vehicle)
			return;

		float fPos[3];
		vect3_copy(&ainfo->base.matrix[4 * 3], fPos);


		fPos[0] += sinf(-ainfo->fCurrentRotation) * 15.0f;
		fPos[1] += cosf(-ainfo->fCurrentRotation) * 15.0f;

		float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);

		fPos[2] = fGroundZHeight;

		stUnoccupiedData unSync;
		RakNet::BitStream bsUnoccupiedSync;
		ZeroMemory(&unSync, sizeof(stUnoccupiedData));

		unSync.sVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);

		vect3_copy(fPos, unSync.fPosition);

		unSync.fRoll[0] = 100; // size x   100
		unSync.fRoll[1] = 100; // size y	100
		unSync.fRoll[2] = 100; // size z	100

		vect3_zero(unSync.fMoveSpeed);
		vect3_zero(unSync.fTurnSpeed);

		vect3_copy(unSync.fRoll, &vehicle->base.matrixStruct->right.X);
		unSync.fDirection[0] = 100; // 100
		unSync.fDirection[1] = 100; // 100b2
		unSync.fDirection[2] = -2; //-2.0f
		vect3_copy(unSync.fDirection, &vehicle->base.matrixStruct->up.X);
		unSync.fHealth = 1000.0f;
		bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
		bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
		g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		cheat_vehicle_teleport(vehicle, fPos, gta_interior_id_get());
		vehicle->hitpoints = 1000.0f;
	}
}
void TH_RemoveCars()
{
	if (cheat_state->Troll.iRemoveCars)
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
		float fPos[3] = { 10000.0f, 10000.0f ,0 };
		static DWORD tick = 100;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 100)
		{
			g_RakClient->SendUnoccupiedSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, vehicle->hitpoints, vehicle->speed, 0);
			tick = now_tick;
		}
	}
}
void TH_RemoveCars2()
{
	if (cheat_state->Troll.iRemoveCars2)
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
		float fPos[3] = { 10000.0f, 10000.0f ,0 };
		static DWORD tick = 100;
		DWORD now_tick = GetTickCount();
		if (now_tick - tick > 100)
		{
			g_RakClient->SendEnterPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle), 0);
			g_RakClient->SendUnoccupiedSyncData(getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, vehicle->hitpoints, vehicle->speed, 0);
			g_RakClient->SendExitPlayerVehicle(getSAMPVehicleIDFromGTAVehicle(vehicle));
			tick = now_tick;
		}
	}
}
void TH_Hileler(void)
{
	TH_PlayerShooterTargetFinder();
	TH_iTrollFeaturesTargetFinder();
	TH_Elevator();
	TH_Jetpack_Elevator();
	TH_CircleTroll();
	TH_CarRemoteControl();
	TH_InvisibleSpec();
	TH_InvisibleBike();
	TH_Invisible7();
	TH_Invisible9();
	TH_VehicleDeformer();
	TH_RemoveCars();
	TH_RemoveCars2();
}