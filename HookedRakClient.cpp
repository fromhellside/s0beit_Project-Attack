/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "main.h"
#include "FRakNet\RakClient.h"
#include "FRakNet\PacketPriority.h"
BYTE GetPacketID(Packet *p)
{
	if (p == 0) return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		assert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
		return (unsigned char)p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
	{
		return (unsigned char)p->data[0];
	}
}
bool hkRakClientInterface::RPC(int* uniqueID, RakNet::BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	traceLastFunc("HookedRakClientInterface::RPC(RakNet::BitStream)");
	if (uniqueID != nullptr)
	{

		if (*uniqueID == RPC_ClientJoin)
		{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
			addMessageToChatWindow("{00FF00}Welcome to Project Attack, %s", getPlayerName(g_Players->sLocalPlayerID));
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
			addMessageToChatWindow(M0D_VERSION": Hoşgeldin, %s", getPlayerName(g_Players->sLocalPlayerID));
			//addMessageToChatWindow("Cheating Family Discord Server: https://discord.gg/xMdM2Qebsf");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
			addMessageToChatWindow("{00FF00}Project Attack v4'e | Geliştirici 'TheLife' sürümüne hoşgeldin:%s", getPlayerName(g_Players->sLocalPlayerID));
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
			addMessageToChatWindow("{00FF00}Project Attack v4'e | Geliştirici 'HellSide' sürümüne hoşgeldin:%s", getPlayerName(g_Players->sLocalPlayerID));
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
			addMessageToChatWindow("{00FF00}Project Attack v6 | Geliştirici 'RapidFire' sürümüne hoşgeldin:%s", getPlayerName(g_Players->sLocalPlayerID));
#endif
		}
		
		if (*uniqueID == RPC_Death && cheat_state->genel.iFastRespawn)
		{
			g_RakClient->GetInterface()->RPC(uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp);
			struct actor_info* info;
			if ((info = actor_info_get(ACTOR_SELF, ACTOR_ALIVE)) != NULL)
				info->hitpoints = 100.0f;
			return 1;
		}
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		if (cheat_state->RakNet.iConnectAsNPC)
		{
			if (*uniqueID == RPC_ClientJoin)
			{
				int change_type = RPC_NPCJoin;
				return g_RakClient->GetInterface()->RPC(&change_type, parameters, priority, reliability, orderingChannel, shiftTimestamp);
			}
		}
#endif
		if (set.bUse_Fake_GPCI)
		{
			if (*uniqueID == RPC_ClientJoin)
			{
				unsigned int uiClientChallengeResponse;
				int iVersion;
				BYTE byteMod;
				BYTE byteNameLen;
				char szNickName[32];

				parameters->Read(iVersion);
				parameters->Read(byteMod);
				parameters->Read(byteNameLen);
				parameters->Read(szNickName, byteNameLen);
				parameters->Read(uiClientChallengeResponse);

				parameters->Reset();
				char auth_bs[4 * 16];
				gen_gpci(auth_bs, 0x3e9);
				BYTE byteAuthBSLen;
				byteAuthBSLen = (BYTE)strlen(auth_bs);
				if (set.Information_About_My_Fake_GPCI)
				{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					addMessageToChatWindow("{00FF00}Project Attack v3 has been loaded.");
					if (set.raknetSettings.bGPCI_info)
						addMessageToChatWindow("GPCI Changer status: ON | Your new GPCI ID: %s", auth_bs);
					else
						addMessageToChatWindow("GPCI Changer status : ON | GPCI Changed.");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
					addMessageToChatWindow("HellSide's Project Attack v3 başarıyla yüklendi!");
					if (set.raknetSettings.bGPCI_info)
						addMessageToChatWindow("GPCI Değiştirici aktif, GPCI ID'in: %s", auth_bs);
					else
						addMessageToChatWindow("GPCI Değiştirici aktif, GPCI ID'in,{00FF00}değiştirildi.");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
					addMessageToChatWindow(M0D_VERSION " | Türkçe sürüme hoşgeldin, %s", getPlayerName(g_Players->sLocalPlayerID));
					addMessageToChatWindow("Cheating Family Discord Server:{00FF00} discord.gg/ZTn7DVN33W");
					if (set.raknetSettings.bGPCI_info)
						addMessageToChatWindow("GPCI Değiştirici aktif, GPCI ID'in: \n {00FF00}%s", auth_bs);
					else
						addMessageToChatWindow("GPCI Değiştirici aktif, GPCI ID'in {00FF00}değiştirildi.");
#endif
				}
				parameters->Write(iVersion);
				parameters->Write(byteMod);
				parameters->Write(byteNameLen);
				parameters->Write(szNickName, byteNameLen);

				parameters->Write(uiClientChallengeResponse);
				parameters->Write(byteAuthBSLen);
				parameters->Write(auth_bs, byteAuthBSLen);
				char szClientVer[] = CLIENT_VERSION;
				const BYTE iClientVerLen = (sizeof(szClientVer) - 1);
				parameters->Write(iClientVerLen);
				parameters->Write(szClientVer, iClientVerLen);
			}
		}

	}
	if (!OnSendRPC(*uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp))
		return false;

	return g_RakClient->GetInterface()->RPC(uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp);
}
	

bool hkRakClientInterface::Send(RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	traceLastFunc("HookedRakClientInterface::Send(BitStream)");
	BYTE packetId;
	bitStream->Read(packetId);
	if (packetId == ID_BULLET_SYNC && cheat_state->Packets.iDisableSendingBulletData)  
		return 1;
	if (packetId == ID_PLAYER_SYNC && cheat_state->Troll.iInvisible9)
		return 1;
	if (packetId == ID_PLAYER_SYNC && cheat_state->Troll.iInvisible4)
		return 1;
	if (packetId == ID_PLAYER_SYNC && cheat_state->Packets.iDisableSendingPlayerData)
		return 1;
	if (packetId == ID_VEHICLE_SYNC && cheat_state->Silah.iBypassWeapon2)
		return 1;
	if (packetId == ID_UNOCCUPIED_SYNC && cheat_state->Packets.iDisableSendingUnoccupiedData)
		return 1;
	if (packetId == ID_TRAILER_SYNC && cheat_state->Packets.iDisableSendingTrailerData)
		return 1;
	if (packetId == ID_PASSENGER_SYNC && cheat_state->Packets.iDisableSendingPassengerData)
		return 1;
	if (packetId == ID_SPECTATOR_SYNC && cheat_state->Packets.iDisableSpectatorSyncData) 
		return 1;
	if (packetId == ID_AIM_SYNC && cheat_state->Packets.iDisableSendingAimData)
		return 1;
	if (packetId == ID_WEAPONS_UPDATE && cheat_state->Packets.iDisableSendingWeaponUpdateData) 
		return 1;
	if (packetId == ID_BULLET_SYNC && cheat_state->Packets.iDisableSendingBulletData)
		return 1;
	if (packetId == ID_VEHICLE_SYNC && cheat_state->Packets.iDisableSendingVehicleData)
		return 1;
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION  || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	if (cheat_state->RakNet.iConnectAsNPC)
	{
		if (packetId == ID_AUTH_KEY)
		{
			char* auth_key = "NPC";
			RakNet::BitStream bsKey;
			BYTE byteAuthKeyLen;
			byteAuthKeyLen = (BYTE)strlen(auth_key);
			bsKey.Write((BYTE)ID_AUTH_KEY);
			bsKey.Write((BYTE)byteAuthKeyLen);
			bsKey.Write(auth_key, byteAuthKeyLen);
			g_RakClient->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE, NULL);
		}
	}
#endif
	if (packetId == ID_PASSENGER_SYNC)
	{
		stPassengerData passData;
		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&passData, sizeof(stPassengerData));
		if (cheat_state->Troll.iInvisible14)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			passData.sVehicleID = nearestCar;
			passData.byteSeatID = -1;
			bitStream->Reset();
			bitStream->Write((BYTE)ID_PASSENGER_SYNC);
			bitStream->Write((PCHAR)&passData, sizeof(stPassengerData));
		}
		if (cheat_state->Silah.iBypassWeapon3)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			passData.sVehicleID = nearestCar;
			passData.fPosition[0] = g_Players->pLocalPlayer->passengerData.fPosition[0];
			passData.fPosition[1] = g_Players->pLocalPlayer->passengerData.fPosition[1];
			passData.fPosition[2] = g_Players->pLocalPlayer->passengerData.fPosition[2];
			passData.byteCurrentWeapon = 0;
			bitStream->Reset();
			bitStream->Write((BYTE)ID_PASSENGER_SYNC);
			bitStream->Write((PCHAR)&passData, sizeof(stPassengerData));
		}
	
	}
	if (packetId == ID_VEHICLE_SYNC) //  PacketEnumeration::ID_VEHICLE_SYNC
	{
		stInCarData OutgoingInCarData;
		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingInCarData, sizeof(stInCarData));
		if (cheat_state->genel.iRandomQuaternions)
		{
			OutgoingInCarData.fQuaternion[0] = random_float(-1, 1);
			OutgoingInCarData.fQuaternion[1] = random_float(-1, 1);
			OutgoingInCarData.fQuaternion[2] = random_float(-1, 1);
			OutgoingInCarData.fQuaternion[3] = random_float(-1, 1);
		}
		else if (cheat_state->genel.iUpsideDown)
		{
			OutgoingInCarData.fQuaternion[0] = 0;
			OutgoingInCarData.fQuaternion[1] = 1;
			OutgoingInCarData.fQuaternion[2] = 0;
			OutgoingInCarData.fQuaternion[3] = 0;
		}
		if (cheat_state->Troll.iTroll != 0 && cheat_state->state == CHEAT_STATE_VEHICLE && KEY_DOWN(VK_LBUTTON))
		{
			TH_iTrollFeatures(&OutgoingInCarData);
		}
		else
		{
			if (cheat_state->Troll.iInvisible1)
			{ 
				OutgoingInCarData.fPosition[2] -= -4.5f; // Proje kullanıcısını görülmeyecek kadar yukarı da görünmez yap.
			}
			else if (cheat_state->Troll.iInvisible2)
				OutgoingInCarData.fPosition[2] -= 7.0f; // Proje kullanıcısını yerin altına göndererek görünmez yap.
			else if (cheat_state->Troll.iInvisible5)
			{
				OutgoingInCarData.fPosition[2] -= random_float(set.TrollCheats.fUDInvisibleMinValue, set.TrollCheats.fUDInvisibleMaxValue);
				OutgoingInCarData.fMoveSpeed[1] += random_float(-0.4f, 0.2f);
			}
		}

		if (cheat_state->Silah.iBypassWeapon)
		{
			OutgoingInCarData.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			OutgoingInCarData.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			OutgoingInCarData.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			OutgoingInCarData.byteCurrentWeapon = 0;
		}
		if (cheat_state->Silah.iBypassWeapon2)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			OutgoingInCarData.sVehicleID = nearestCar;
			OutgoingInCarData.fPosition[0] = g_Players->pLocalPlayer->inCarData.fPosition[0];
			OutgoingInCarData.fPosition[1] = g_Players->pLocalPlayer->inCarData.fPosition[1];
			OutgoingInCarData.fPosition[2] = g_Players->pLocalPlayer->inCarData.fPosition[2];
			OutgoingInCarData.byteCurrentWeapon = 0;
		}

		if (cheat_state->Troll.iInvisible5)
		{
			OutgoingInCarData.fPosition[2] -= random_float(-1.6f, -4.2f);
			OutgoingInCarData.fMoveSpeed[0] += random_float(-0.6f, 0.4f);
		}
		if (cheat_state->Troll.iSpeedKicker)
		{
			float fSpeed[3];
			fSpeed[0] = random_float(0.19282, 0.83711);
			fSpeed[1] = random_float(0.19282, 0.83711);
			fSpeed[2] = random_float(0.2f, 0.4f);
			OutgoingInCarData.fMoveSpeed[0] += fSpeed[0];
			OutgoingInCarData.fMoveSpeed[1] += fSpeed[1];
			OutgoingInCarData.fMoveSpeed[2] += fSpeed[2];
			
		}

		if (cheat_state->Troll.iPlayerShooter != 0 && cheat_state->state == CHEAT_STATE_VEHICLE && KEY_DOWN(VK_LBUTTON))
		{
			TH_PlayerShooter(&OutgoingInCarData);
		}
		if (cheat_state->Troll.iPlayerCopier)
		{
			if (IsPlayerStreamed(set.TrollCheats.iPlayerCopier_TargetID))
			{
				OutgoingInCarData.fPosition[0] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->inCarData.fPosition[0];
				OutgoingInCarData.fPosition[1] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->inCarData.fPosition[1];
				OutgoingInCarData.fPosition[2] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->inCarData.fPosition[2];
			}
		}
		if (cheat_state->Troll.iActorShooter)
		{
			OutgoingInCarData.fMoveSpeed[0] = cam_matrix[4] * 5.0f;
			OutgoingInCarData.fMoveSpeed[1] = cam_matrix[5] * 5.0f;
			OutgoingInCarData.fMoveSpeed[2] = cam_matrix[6] * 5.0f;
		}
		if (cheat_state->Troll.iInvisible10)
		{
			OutgoingInCarData.fPosition[2] -= NAN;
		}
		if (cheat_state->Troll.iInvisible11)
		{
			OutgoingInCarData.fPosition[2] += NAN; 
		}
		if (cheat_state->Troll.iPlayerFucker)
		{
			
			float fSpeed[3] = { random_float(0.10000,0.89700),random_float(0.20000,0.79666),random_float(0.1,0.5f) };
			OutgoingInCarData.fMoveSpeed[0] += fSpeed[0];
			OutgoingInCarData.fMoveSpeed[1] += fSpeed[1];
			OutgoingInCarData.fMoveSpeed[2] += fSpeed[2];
		}
		bitStream->Reset();
		bitStream->Write((BYTE)ID_VEHICLE_SYNC);
		bitStream->Write((PCHAR)&OutgoingInCarData, sizeof(stInCarData));
	}

	if (packetId == ID_AIM_SYNC)
	{
		stAimData OutgoingAimVeri;
		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingAimVeri, sizeof(stAimData));

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		if (cheat_state->crasher.iWeaponCrasher)
			OutgoingAimVeri.byteCamMode = 34;
#endif
			// OverLight'tan alıntı..
		if (cheat_state->Silent.bSilent)
		{
			if (g_NewModSa->iAimPlayerID == INVALID)
				return true;
	
			if (!IsPlayerStreamed(g_NewModSa->iAimPlayerID)
				|| /* of course*/ (g_Players->pLocalPlayer->onFootData.byteCurrentWeapon == 40))
				return true;

			if (g_NewModSa->byteLagComp)
			{
				if (cheat_state->Silah.iShooting_Through_Walls)
				{
					float fTargetPos[3];
					OutgoingAimVeri.byteCamMode = 55;
					if (cheat_state->Silah.iShooting_Through_WallsBypass)
					{
						OutgoingAimVeri.vecAimf1[0] = g_Players->pLocalPlayer->aimData.vecAimf1[0];
						OutgoingAimVeri.vecAimf1[1] = g_Players->pLocalPlayer->aimData.vecAimf1[1];
						OutgoingAimVeri.vecAimf1[2] = g_Players->pLocalPlayer->aimData.vecAimf1[2] + 0.25f;
					}
					else
					{
						OutgoingAimVeri.vecAimf1[0] = 0;
						OutgoingAimVeri.vecAimf1[1] = 0;
						OutgoingAimVeri.vecAimf1[2] = -0.01f;
					}
					vect3_copy(&g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						OutgoingAimVeri.vecAimPos);
					g_RakClient->SendDamage(g_NewModSa->iAimPlayerID, fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_Players->pLocalPlayer->byteCurrentWeapon, 3);
				}
				else
				{
					//lagcomp off -> LagShot
					OutgoingAimVeri.byteCamMode = 65; //Bütün silahlar ile çalış..
					if (!IsPlayerStreamed(g_NewModSa->iAimPlayerID))
						return true;
					float fEnemyPos[3], fSelfPos[3];
					OL_CalculateLagPosition(g_NewModSa->iAimPlayerID, fEnemyPos);
					vect3_copy(&g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						fEnemyPos);
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						fSelfPos);
					OutgoingAimVeri.vecAimf1[0] = 0;
					OutgoingAimVeri.vecAimf1[1] = 0;//((fEnemyPos[2] - 3.5f) > fSelfPos[2]) ? 1.0f : 0.f;
					OutgoingAimVeri.vecAimf1[2] = ((fEnemyPos[2] - 3.5f) > fSelfPos[2]) ? 1.0f : -0.01f;//-0.01f;
					vect3_copy(&g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						OutgoingAimVeri.vecAimPos);
					OL_CalculateLagPosition(g_NewModSa->iAimPlayerID, OutgoingAimVeri.vecAimPos);
				}
			}
		}
	/*	if (cheat_state->crasher.iPublicRemovePlayerCrasher)
			OutgoingAimVeri.byteCamMode = 34;*/

		if (cheat_state->genel.iInvalidAimZ)
			OutgoingAimVeri.fAimZ = sqrt((float)-1); // Dipnot: bunu fixlemek istiyorsan if(aimData.fAimZ != aimData.fAimZ)
		if (cheat_state->genel.iShakingCamera)
			OutgoingAimVeri.byteCamMode = 45;
		else if (cheat_state->genel.iShakingCamera2)
			OutgoingAimVeri.byteCamMode = 34;

#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
		switch (cheat_state->Silah.iSpinBotType)
		{
			case ID_SPINTYPE_DOWN:
			{
				OutgoingAimVeri.fAimZ = 1.45f;
			}break;
			case ID_SPINTYPE_UP:
			{
				OutgoingAimVeri.fAimZ = -0.89f;
			}break;
			case ID_SPINTYPE_RANDOM:
			{
				OutgoingAimVeri.fAimZ = random_float(-0.89f, 1.45f);
			}break;
			default:
				cheat_state->Silah.iSpinBotType = 0;
			break;
		}
#endif
		bitStream->Reset();
		bitStream->Write((BYTE)ID_AIM_SYNC);
		bitStream->Write((PCHAR)&OutgoingAimVeri, sizeof(stAimData));
	}

	if (packetId == PacketEnumeration::ID_PLAYER_SYNC)
	{
		stOnFootData OutgoingOnFootveri;
		bitStream->ResetReadPointer();
		bitStream->Read(packetId);
		bitStream->Read((PCHAR)&OutgoingOnFootveri, sizeof(stOnFootData));
	
		if (cheat_state->genel.iGhostMode)
			OutgoingOnFootveri.byteSpecialAction = 3;
		if (cheat_state->Troll.iActorShooter)
		{
			OutgoingOnFootveri.fMoveSpeed[0] = cam_matrix[4] * 5.0f;
			OutgoingOnFootveri.fMoveSpeed[1] = cam_matrix[5] * 5.0f;
			OutgoingOnFootveri.fMoveSpeed[2] = cam_matrix[6] * 5.0f;
		}
		if (cheat_state->Troll.iInvisible6)
		{
			OutgoingOnFootveri.sCurrentAnimationID = 402;
			OutgoingOnFootveri.sAnimFlags = 6148;
		}
		if (cheat_state->Troll.iSpeedKicker)
		{
			float fSpeed[3];
			fSpeed[0] = random_float(0.19282, 0.83711);
			fSpeed[1] = random_float(0.19282, 0.83711);
			fSpeed[2] = random_float(0.2f, 0.4f);
			OutgoingOnFootveri.fMoveSpeed[0] += fSpeed[0];
			OutgoingOnFootveri.fMoveSpeed[1] += fSpeed[1];
			OutgoingOnFootveri.fMoveSpeed[2] += fSpeed[2];
		}
	
		if (cheat_state->Troll.iInvisible8)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			float fSurfType[2] = { -100.0f, -100.0f };
			OutgoingOnFootveri.sSurfingVehicleID = nearestCar;
			OutgoingOnFootveri.fSurfingOffsets[0] = random_float(1.00000f, 1.10000f);
			OutgoingOnFootveri.fSurfingOffsets[1] = random_float(1.00000f, 1.10000f);
			OutgoingOnFootveri.fSurfingOffsets[2] = fSurfType[rand() % 2];
		}
		if (cheat_state->Troll.iInvisible13)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			OutgoingOnFootveri.sSurfingVehicleID = nearestCar;
			OutgoingOnFootveri.fSurfingOffsets[0] = -99991;
			OutgoingOnFootveri.fSurfingOffsets[1] = -99991;
			OutgoingOnFootveri.fSurfingOffsets[2] = -99991;
		}
		if (cheat_state->Troll.iInvisible12)
		{
			int	nearestCar = 0;
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
				nearestCar = getSAMPVehicleIDFromGTAVehicle(vinfo);
			}
			OutgoingOnFootveri.sSurfingVehicleID = nearestCar;
			OutgoingOnFootveri.fSurfingOffsets[0] = random_float(1.00000f, 1.10000f);
			OutgoingOnFootveri.fSurfingOffsets[1] = random_float(1.00000f, 1.10000f);
			OutgoingOnFootveri.fSurfingOffsets[2] = -100.0f;
		}
		if (cheat_state->Troll.iPlayerCopier)
		{
			if (set.TrollCheats.iPlayerCopier_TargetID == g_Players->sLocalPlayerID)
				return false;
			if (IsPlayerStreamed(set.TrollCheats.iPlayerCopier_TargetID))
			{
				OutgoingOnFootveri.fPosition[0] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->onFootData.fPosition[0];
				OutgoingOnFootveri.fPosition[1] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->onFootData.fPosition[1];
				OutgoingOnFootveri.fPosition[2] = g_Players->pRemotePlayer[set.TrollCheats.iPlayerCopier_TargetID]->pPlayerData->onFootData.fPosition[2];
			}
			if (set.TrollCheats.bSyncPlayerCopier == true)
				pPedSelf->SetPosition(OutgoingOnFootveri.fPosition[0], OutgoingOnFootveri.fPosition[1], OutgoingOnFootveri.fPosition[2]);
		}
		if (cheat_state->Troll.iInvisible1)
		{
			OutgoingOnFootveri.fPosition[2] += 100.0f; // v1,v1.5,v2 sürümlerinde += 999.0f'ti ama sunucular fixlemiş.
			OutgoingOnFootveri.byteSpecialAction = 0;
		}
		if (cheat_state->Troll.iInvisible10)
		{
			OutgoingOnFootveri.fPosition[2] -= NAN; 
		}
		if (cheat_state->Troll.iInvisible11)
		{
			OutgoingOnFootveri.fPosition[2] += NAN;
		}
		if (cheat_state->Troll.iQuaSlapper)
		{
			float fSpeed[3];
			fSpeed[0] = random_float(0.19282, 0.83711);
			fSpeed[1] = random_float(0.19282, 0.83711);
			fSpeed[2] = random_float(0.2f, 0.4f);
			OutgoingOnFootveri.fMoveSpeed[0] += fSpeed[0];
			OutgoingOnFootveri.fMoveSpeed[1] += fSpeed[1];
			OutgoingOnFootveri.fMoveSpeed[2] += fSpeed[2];
			OutgoingOnFootveri.fQuaternion[0] = random_float(-1, 1);
			OutgoingOnFootveri.fQuaternion[1] = random_float(-1, 1);
			OutgoingOnFootveri.fQuaternion[2] = random_float(-1, 1);
			OutgoingOnFootveri.fQuaternion[3] = random_float(-1, 1);
		}
		if (cheat_state->Troll.iHeadWalkSlapper)
		{
			float fSpeed[3];
			fSpeed[0] = random_float(0.19282, 0.83711);
			fSpeed[1] = random_float(0.19282, 0.83711);
			fSpeed[2] = random_float(0.2f, 0.4f);
			OutgoingOnFootveri.fMoveSpeed[0] += fSpeed[0];
			OutgoingOnFootveri.fMoveSpeed[1] += fSpeed[1];
			OutgoingOnFootveri.fMoveSpeed[2] += fSpeed[2];
			OutgoingOnFootveri.fQuaternion[0] = 0;
			OutgoingOnFootveri.fQuaternion[1] = 1;
			OutgoingOnFootveri.fQuaternion[2] = 0;
			OutgoingOnFootveri.fQuaternion[3] = 0;
		}
		else if (cheat_state->Troll.iInvisible2)
		{
			OutgoingOnFootveri.fPosition[2] -= 5.0f; // Sunucuların görünmezlik denetlemesine karşı değer düşürüldü. 
			// Orijinal değer : 15.0f;
		}
		else if (cheat_state->Troll.iInvisible5) // Yeni nesil görünmezlik, private bir tane..
		{
			OutgoingOnFootveri.fPosition[2] -= random_float(set.TrollCheats.fUDInvisibleMinValue, set.TrollCheats.fUDInvisibleMaxValue);
			OutgoingOnFootveri.fMoveSpeed[1] += random_float(0.1, 0.2f);
		}

		vehicle_info* vehicle_for_silent_invis = GetVehicleInfoStandart(VEHICLE_ALIVE | VEHICLE_NOT_TRAIN, VEHICLE_CLOSEST);
		int vehicle_id = getSAMPVehicleIDFromGTAVehicle(vehicle_for_silent_invis);
		static bool silent_used;
		if (cheat_state->Troll.iInvisible3)
		{
			if (g_Vehicles->iIsListed[vehicle_id] != 1)
			{
				OutgoingOnFootveri.fPosition[2] = -5.0f;//35.0f'ten -5.0f'e çekmeyi düşün.
			}
			else
			{
				OutgoingOnFootveri.sSurfingVehicleID = vehicle_id;

				if (OutgoingOnFootveri.stSampKeys.keys_aim && OutgoingOnFootveri.stSampKeys.keys_secondaryFire__shoot)
				{
					OutgoingOnFootveri.fSurfingOffsets[2] = -35.0f;
					vect3_zero(OutgoingOnFootveri.fMoveSpeed);
				}
				else
				{
					OutgoingOnFootveri.sSurfingVehicleID = vehicle_id;
					OutgoingOnFootveri.fSurfingOffsets[2] = sqrt((float)-1);
				}
			}
			silent_used = true;
		}
		else
		{
			if (silent_used)
			{
				vect3_zero(OutgoingOnFootveri.fSurfingOffsets);
				OutgoingOnFootveri.sSurfingVehicleID = vehicle_id;
				silent_used = false;
			}
		}
		if (cheat_state->Silah.iBypassWeapon)
		{
			OutgoingOnFootveri.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			OutgoingOnFootveri.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			OutgoingOnFootveri.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];
			OutgoingOnFootveri.byteCurrentWeapon = 0;
		}
		if (cheat_state->Troll.iUnSynch)
		{
			float fPos[3];
			actor_info* self = actor_info_get(ACTOR_SELF, 0);

			vect3_copy(&self->base.matrix[4 * 3], fPos);

			static float prev_pos[2];
			do
			{
				fPos[0] += (float)R4nd0m(-set.Unsynch_Radius, set.Unsynch_Radius);
				fPos[1] += (float)R4nd0m(-set.Unsynch_Radius, set.Unsynch_Radius);

			} while (prev_pos[0] == fPos[0] || prev_pos[1] == fPos[1]);

			prev_pos[0] = fPos[0];
			prev_pos[1] = fPos[1];

			float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[0], fPos[1]);

			fPos[2] = fGroundZHeight + 1.0f;

			OutgoingOnFootveri.fPosition[0] = fPos[0];
			OutgoingOnFootveri.fPosition[1] = fPos[1];
			OutgoingOnFootveri.fPosition[2] = fPos[2];
			if (set.See_How_UnSynch_Works)
				pPedSelf->SetPosition(prev_pos[0], prev_pos[1], fPos[2]);

		}
		if (cheat_state->Troll.iInvisible9)
		{
			OutgoingOnFootveri.byteCurrentWeapon = g_Players->pLocalPlayer->byteCurrentWeapon;
		}
		if (cheat_state->genel.iTwistMode)
		{
			static float fRotation = 0.0f;
			OutgoingOnFootveri.fQuaternion[0] = cosf(fRotation);
			OutgoingOnFootveri.fQuaternion[3] = sinf(fRotation);
			OutgoingOnFootveri.byteCurrentWeapon = 46;
			static DWORD timer = 0;
			if (GetTickCount() - timer > 0)
			{
				fRotation += 1.0f;
				if (fRotation >= 360.0f) fRotation = 0.0f;
				timer = GetTickCount();
			}
			static DWORD timer2 = 0;
			if (GetTickCount() - timer2 > 0)
			{
				OutgoingOnFootveri.sUpDownKeys = 128;
				OutgoingOnFootveri.sCurrentAnimationID = 0x3C5;
				OutgoingOnFootveri.sAnimFlags = 0x1901;
				timer2 = GetTickCount();
			}
		}
		if (cheat_state->genel.iTwistMode2)
		{
			static float fRotation = 0.0f;
			OutgoingOnFootveri.fQuaternion[0] = cosf(fRotation);
			OutgoingOnFootveri.fQuaternion[3] = sinf(fRotation);
			OutgoingOnFootveri.byteCurrentWeapon = g_Players->pLocalPlayer->byteCurrentWeapon;
			static DWORD timer = 0;
			if (GetTickCount() - timer > 0)
			{
				fRotation += 1.0f;
				if (fRotation >= 360.0f) fRotation = 0.0f;

				timer = GetTickCount();
			}
			static DWORD timer2 = 0;
			if (GetTickCount() - timer2 > 0)
			{
				OutgoingOnFootveri.sUpDownKeys = 128;
			
				timer2 = GetTickCount();
			}
		}
		/*
			---- Bu.. Random Quaternions & Upside Down'u fixleyen anti hilenin fixi.
			---- Bizdeki fix, detect etmeden geçirmek.
			---- Alttaki İngilizce yazıyı her şeyi açıklıyor ama.. Yine de bende açıklamak istiyorum.
			---- Y Ekseninin Dördeyini denetleyerek yürüyor.
			Name: OnPlayerTurnUpsideDown
			Type: Gameplay hack
			Description: This modification alters player rotation quaternions, making the user look upside down to other players.
			Detection Method: This include converts the player rotation quaternions to Euler Angles (y axis) and checks if it's above 85.0 or below -85.0, values which you won't get legitely. This method will also detect parkour mods or any other modification that turns the player upside down.
			Callback: OnAntiCheatTurnUpsideDown(playerid, Float:angle)
			Author: Jelly23
		*/
		if (cheat_state->genel.iRandomQuaternions)
		{
				OutgoingOnFootveri.fQuaternion[0] = random_float(-1, 1);
			if(cheat_state->genel.iRandomQuaternionsFix) // Fix!!!! 
				OutgoingOnFootveri.fQuaternion[1] = random_float(-0.84f, 0.84f);
			else
				OutgoingOnFootveri.fQuaternion[1] = random_float(-1, 1);
				OutgoingOnFootveri.fQuaternion[2] = random_float(-1, 1);
				OutgoingOnFootveri.fQuaternion[3] = random_float(-1, 1);
		}
		else if (cheat_state->genel.iUpsideDown)
		{
			OutgoingOnFootveri.fQuaternion[0] = 0;
			if(cheat_state->genel.iRandomQuaternionsFix)
				OutgoingOnFootveri.fQuaternion[1] = 0.84f;
			else
				OutgoingOnFootveri.fQuaternion[1] = 1;
				OutgoingOnFootveri.fQuaternion[2] = 0;
				OutgoingOnFootveri.fQuaternion[3] = 0;
		}
	
		if (cheat_state->Silah.iSpinBotType)
		{
			static float fRotation = 0.0f;
			if (g_Players->pLocalPlayer->byteCurrentWeapon == 0)  // Eğer elimde her hangi bir silah yoksa mevlana gibi dönmeyi bıraksın.
				return true; // false'tan true.
			OutgoingOnFootveri.fQuaternion[0] = cosf(fRotation);
			OutgoingOnFootveri.fQuaternion[3] = sinf(fRotation);
			static DWORD timer = 0;
			if (GetTickCount() - timer > 0) // 95'ten 0'a indirildi.
			{
				fRotation += 1.0f;
				if (fRotation >= 360.0f) fRotation = 0.0f;

				timer = GetTickCount();
			}
		}

		bitStream->Reset();

		bitStream->Write((BYTE)ID_PLAYER_SYNC);
		bitStream->Write((PCHAR)&OutgoingOnFootveri, sizeof(stOnFootData));
	}

	if (packetId == ID_BULLET_SYNC)
	{
		traceLastFunc("ID_BULLET_SYNC");
		stBulletData OutgoingBulletData;
		bitStream->Read((PCHAR)&OutgoingBulletData, sizeof(stBulletData));
		if (set.WeaponCheats.Weapon_Damage > 0)
		{
			for (int iHasar = 0; iHasar < set.WeaponCheats.Weapon_Damage; iHasar++)
			{
				g_RakClient->SendDamage(OutgoingBulletData.sTargetID, fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_Players->pLocalPlayer->byteCurrentWeapon, 3);
				g_RakClient->Send(bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			}
		}
		if (cheat_state->Silent.bSilent)
		{
			if (cheat_state->Silent.bSilent)
			{
				if (g_NewModSa->iAimPlayerID == INVALID)
					return true;
				if (!IsPlayerStreamed(g_NewModSa->iAimPlayerID))
					return true;
				float TargetPos[3], Spread[3];

				switch (g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->bytePlayerState)
				{
				case PLAYER_STATE_ONFOOT:
					for (short x = 0; x < 3; x++)
						TargetPos[x] = g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->fOnFootPos[x];
					break;
				case PLAYER_STATE_DRIVER:
					for (short x = 0; x < 3; x++)
						TargetPos[x] = g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->inCarData.fPosition[x];
					break;
				case PLAYER_STATE_PASSENGER:
					for (short x = 0; x < 3; x++)
						TargetPos[x] = g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->passengerData.fPosition[x];
					break;
				}
				int BodyPart = CalculateSpreadOffset(g_NewModSa->iAimPlayerID, TargetPos, Spread);

				actor_info* player = getGTAPedFromSAMPPlayerID(g_NewModSa->iAimPlayerID);
				CPed* pPed = pGameInterface->GetPools()->GetPed((DWORD*)player);
				CVector fBonePos;
				pPed->GetBonePosition((eBone)cheat_state->Silent.iSilentBone, &fBonePos);

				OutgoingBulletData.byteType = BULLET_HIT_TYPE_PLAYER;

				OutgoingBulletData.fTarget[0] = fBonePos.fX;
				OutgoingBulletData.fTarget[1] = fBonePos.fY;
				OutgoingBulletData.fTarget[2] = fBonePos.fZ;

				OutgoingBulletData.fCenter[0] = Spread[0];
				OutgoingBulletData.fCenter[1] = Spread[1];
				OutgoingBulletData.fCenter[2] = Spread[2];

				OutgoingBulletData.sTargetID = g_NewModSa->iAimPlayerID;
				uint8_t chance = rand() % 100 + 1; // Oranı 0 ile 100 arası RANDOM sayı ürettir.
				if (chance < set.silentAim.iHitChanceValue)
				{
					if (g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->hitpoints != 0)
					{
						bitStream->Reset();
						bitStream->Write((BYTE)ID_BULLET_SYNC);
						bitStream->Write((PCHAR)& OutgoingBulletData, sizeof(stBulletData));
						g_RakClient->Send(bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
						g_RakClient->SendGiveDamage(g_NewModSa->iAimPlayerID, CalculateDamage(), g_Players->pLocalPlayer->byteCurrentWeapon, BodyPart);
						return false;
					}
				}
			}
		}
		bitStream->Reset();
		bitStream->Write((BYTE)ID_BULLET_SYNC);
		bitStream->Write((PCHAR)&OutgoingBulletData, sizeof(stBulletData));
	}

	return g_RakClient->GetInterface()->Send(bitStream, priority, reliability, orderingChannel);
}

Packet* hkRakClientInterface::Receive(void)
{
	traceLastFunc("HookedRakClientInterface::Receive");

	Packet* p = g_RakClient->GetInterface()->Receive();
	BYTE GelenPaketID = GetPacketID(p);
	unsigned short OyuncuID;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH || COMPILE_TYPE != COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
	if (GelenPaketID == PacketEnumeration::ID_TRAILER_SYNC)
	{
		RakNet::BitStream bsTrailerSync((unsigned char*)p->data, p->length, false);
		stTrailerData trailerSync;
		bsTrailerSync.IgnoreBits(8);
		bsTrailerSync.Read(OyuncuID);
		bsTrailerSync.Read((PCHAR)&trailerSync, sizeof(stTrailerData));
		bsTrailerSync.Read(trailerSync.sTrailerID);

		bsTrailerSync.Read(trailerSync.fPosition[0]);
		bsTrailerSync.Read(trailerSync.fPosition[1]);
		bsTrailerSync.Read(trailerSync.fPosition[2]);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
		bsTrailerSync.ReadNormQuat(trailerSync.fQuaternion[0],
			trailerSync.fQuaternion[1],
			trailerSync.fQuaternion[2],
			trailerSync.fQuaternion[3]);
#endif

		bsTrailerSync.Read(trailerSync.fMoveSpeed[0]);
		bsTrailerSync.Read(trailerSync.fMoveSpeed[1]);
		bsTrailerSync.Read(trailerSync.fMoveSpeed[2]);

		bsTrailerSync.Read(trailerSync.fRoll[0]);
		bsTrailerSync.Read(trailerSync.fRoll[1]);
		bsTrailerSync.Read(trailerSync.fRoll[2]);
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
		bsTrailerSync.Read(trailerSync.fDirection[0]);
		bsTrailerSync.Read(trailerSync.fDirection[1]);
		bsTrailerSync.Read(trailerSync.fDirection[2]);
#endif
	
		bool pTrailerDeSync = false;
		if (cheat_state->AntiTrailer.iAntifPositionCrasher)
		{
			if (vect3_length(trailerSync.fPosition) >= 5000.0f || vect3_length(trailerSync.fPosition) <= -5.0f)
			{
				pTrailerDeSync = true;
				cheat_state_text("[Anti Trailer Crasher]ID:%i %s isimli oyuncu Trailer Crasher kullanıyor!", OyuncuID, getPlayerName(OyuncuID));
			}
		}
		if (cheat_state->AntiTrailer.iAntifSpinCrasher)
		{
			if (vect3_length(trailerSync.fRoll) >= 5000.0f || vect3_length(trailerSync.fRoll) <= -5.0f)
			{
				pTrailerDeSync = true;
				cheat_state_text("[Anti Trailer Crasher]ID:%i %s isimli oyuncu Trailer Crasher kullanıyor!", OyuncuID, getPlayerName(OyuncuID));
			}
		}
		if (cheat_state->AntiTrailer.iAntifSpeedCrasher)
		{
			if (vect3_length(trailerSync.fMoveSpeed) >= 1000.0f || vect3_length(trailerSync.fMoveSpeed) <= -5.0f)
			{
				pTrailerDeSync = true;
				cheat_state_text("[Anti Trailer Crasher]ID:%i %s isimli oyuncu Trailer Crasher kullanıyor!", OyuncuID, getPlayerName(OyuncuID));
			}
		}
		if (pTrailerDeSync)
		{
			p->data[0] = 255;
		}
	}
#endif
	if (GelenPaketID == PacketEnumeration::ID_VEHICLE_SYNC)
	{
		traceLastFunc("Receive ID_VEHICLE_SYNC");
		RakNet::BitStream bsAraciciVeri((unsigned char*)p->data, p->length, false);
		stInCarData AracVeri;
		bsAraciciVeri.IgnoreBits(8);
		bsAraciciVeri.Read(OyuncuID);
		bsAraciciVeri.Read((PCHAR)&AracVeri, sizeof(stInCarData));

		bsAraciciVeri.Read(AracVeri.sVehicleID);

		bsAraciciVeri.Read(AracVeri.sLeftRightKeys);
		bsAraciciVeri.Read(AracVeri.sUpDownKeys);
		bsAraciciVeri.Read(AracVeri.sKeys);

		bsAraciciVeri.ReadNormQuat(
			AracVeri.fQuaternion[0],
			AracVeri.fQuaternion[1],
			AracVeri.fQuaternion[2],
			AracVeri.fQuaternion[3]);

		bsAraciciVeri.Read(AracVeri.fPosition[0]);
		bsAraciciVeri.Read(AracVeri.fPosition[1]);
		bsAraciciVeri.Read(AracVeri.fPosition[2]);

		bsAraciciVeri.Read(AracVeri.fMoveSpeed[0]);
		bsAraciciVeri.Read(AracVeri.fMoveSpeed[1]);
		bsAraciciVeri.Read(AracVeri.fMoveSpeed[2]);

		WORD wTempVehicleHealth;
		bsAraciciVeri.Read(wTempVehicleHealth);
		AracVeri.fVehicleHealth = (float)wTempVehicleHealth;
		bool pVehicleDesync = false;
		if (cheat_state->Korumalar.iAntiCarTroll == 1)
		{
			actor_info* me_actor = actor_info_get(ACTOR_SELF, NULL);
			vehicle_info* vehicle = g_SAMP->pPools->pVehicle->pGTA_Vehicle[AracVeri.sVehicleID];
			if (me_actor && vehicle)
			{
				if (ActorIsVehicleDriver(me_actor, vehicle))
				{
					pVehicleDesync = true;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
					cheat_state_text("[Anti Troll]ID:%i %s isimli oyuncu aracını trollemeyi denedi.", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[Warning] ID: %i -> %s is using Vehicle Troll functions.", D3DCOLOR_ARGB(191, 255, 0, 0), OyuncuID, getPlayerName(OyuncuID));
#endif
				}
			}
		}

		if (cheat_state->Korumalar.iAntiVehicleComponentsCrasher == 1)
		{
			if (vect3_length(AracVeri.fPosition) > 10000.0f)
			{
				pVehicleDesync = true;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
				cheat_state_text("[Anti Crasher]ID:%i %s isimli oyuncu Vehicle Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
#else
				cheat_state_text("[Warning] ID: %i -> %s is using Vehicle Crashers.", D3DCOLOR_ARGB(191, 255, 0, 0), OyuncuID, getPlayerName(OyuncuID));
#endif
			}
		}
		if (pVehicleDesync)
		{
			p->data[0] = 255;
		}
	}
	if (GelenPaketID == PacketEnumeration::ID_AIM_SYNC)
	{
		RakNet::BitStream bsAimSync((unsigned char*)p->data, p->length, false);
		stAimData aimData;
		bsAimSync.IgnoreBits(8);
		bsAimSync.Read(OyuncuID);
		bsAimSync.Read((PCHAR)&aimData, sizeof(stAimData));
		bool pAimDataDesync = false;
		bsAimSync.Read(aimData.byteCamMode);
		bsAimSync.Read(aimData.fAimZ);
		//----//
		bsAimSync.Read(aimData.vecAimPos[0]);
		bsAimSync.Read(aimData.vecAimPos[1]);
		bsAimSync.Read(aimData.vecAimPos[2]);
		//----//
		bsAimSync.Read(aimData.vecAimf1[0]);
		bsAimSync.Read(aimData.vecAimf1[1]);
		bsAimSync.Read(aimData.vecAimf1[2]);

		stAimData* aimSyncData = (stAimData*)&p->data[3];
		uint16_t	playerId = *(uint16_t*)&p->data[1];
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		OnRecieveControlPanelHook(playerId, (stAimBEData*)aimSyncData);
#endif
		if (cheat_state->Korumalar.iAntiShakingCamera)
		{
			if (aimSyncData->byteCamMode == 34 || aimSyncData->byteCamMode == 45)
			{
				aimSyncData->byteCamMode = 0;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
				cheat_state_text("[Anti Shaking Camera]ID:%i %s is using Shaking Camera",playerId, getPlayerName(playerId));
#else
				cheat_state_text("[Oyun Koruması]ID:%i %s isimli oyuncu ekran titretici kullanıyor.", playerId, getPlayerName(playerId));
#endif
				
			}
		}

		if (cheat_state->Korumalar.iAntiInvalidAimZ) // Anti Invalid Aim Z!!!!!!!!!! XD
		{
			if (aimSyncData->fAimZ != aimSyncData->fAimZ) 
			{
				pAimDataDesync = true;
				aimData.fAimZ = 0.0f;
				aimSyncData->fAimZ = 0.0f;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
				cheat_state_text("[Anti Invalid Aim Z]ID:%i %s is using Invalid Aim Z.", playerId, getPlayerName(playerId));
#else
				cheat_state_text("[Oyun Koruması]ID:%i %s isimli oyuncu ekran titretici kullanıyor.", playerId, getPlayerName(playerId));
#endif
			}
		}
		if (pAimDataDesync)
		{
			p->data[0] = 255;
		}
	}
	if (GelenPaketID == PacketEnumeration::ID_BULLET_SYNC)
	{
		RakNet::BitStream bsBulletData((unsigned char*)p->data, p->length, false);
		stBulletData BulletData;
		bsBulletData.IgnoreBits(8);
		bsBulletData.Read(OyuncuID);
		bsBulletData.Read((PCHAR)&BulletData, sizeof(stBulletData));
	
		if (cheat_state->Silah.iReturnTheDamage)
		{
			RakNet::BitStream bsBulletSync((unsigned char*)p->data, p->length, false);

			stBulletData BulletData;
			unsigned short PlayerID;
			bsBulletSync.IgnoreBits(8);
			bsBulletSync.Read(PlayerID);
			bsBulletSync.Read((PCHAR)&BulletData, sizeof(stBulletData));
			if (BulletData.sTargetID == g_Players->sLocalPlayerID)
			{

				BulletData.sTargetID = PlayerID;
				BulletData.byteWeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fOrigin);
				if (set.WeaponCheats.Weapon_Damage > 0)//1
				{
					for (short x = 0; x < set.WeaponCheats.Weapon_Damage; x++)
					{
						if (set.WeaponCheats.Weapon_Damage >= 3)
						{
							static DWORD dwWeaponDamageSendRate = 100;
							if (GetTickCount() - dwWeaponDamageSendRate > 100)
							{
								RakNet::BitStream bsBullet;
								bsBullet.Write((BYTE)ID_BULLET_SYNC);
								bsBullet.Write((PCHAR)&BulletData, sizeof(stBulletData));
								g_RakClient->Send(&bsBullet, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
								g_RakClient->SendDamage(PlayerID, fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_Players->pLocalPlayer->byteCurrentWeapon, 3);
								dwWeaponDamageSendRate = GetTickCount();
							}
						}
						else
						{
							RakNet::BitStream bsBullet;
							bsBullet.Write((BYTE)ID_BULLET_SYNC);
							bsBullet.Write((PCHAR)&BulletData, sizeof(stBulletData));
							g_RakClient->Send(&bsBullet, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
							g_RakClient->SendDamage(PlayerID, fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_Players->pLocalPlayer->byteCurrentWeapon, 3);
						}
					}
				}
				else
				{
					RakNet::BitStream bsBullet;
					bsBullet.Write((BYTE)ID_BULLET_SYNC);
					bsBullet.Write((PCHAR)&BulletData, sizeof(stBulletData));
					g_RakClient->Send(&bsBullet, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					g_RakClient->SendDamage(PlayerID, fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_Players->pLocalPlayer->byteCurrentWeapon, 3);
				}
			}
		}
		bool pBulletDataDesync = false;
		if (cheat_state->Korumalar.iAntiBulletCrasher)
		{

			float fPos[3] = {};

			getPlayerPos(OyuncuID, fPos);

			if (g_Players->pRemotePlayer[OyuncuID]->pPlayerData->onFootData.fPosition[2] < -100.0f)
				fPos[2] = g_Players->pRemotePlayer[OyuncuID]->pPlayerData->onFootData.fPosition[2];

			if (BulletData.byteType)
			{

				float vect3_null[3] = {};

				float dist = vect3_dist(BulletData.fTarget, fPos);

				if (dist >= 300.0f)
					pBulletDataDesync = true;

			}

			if (vect3_dist(fPos, BulletData.fOrigin) >= 300.0f)
				pBulletDataDesync = true;


			if (BulletData.byteWeaponID > 46 || BulletData.byteWeaponID < 0)
				pBulletDataDesync = true;
		}

		if (pBulletDataDesync)
		{
			p->data[0] = 255;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
			cheat_state_text("[Anti Crasher]ID: %i -> %s Bullet Crasher kullanıyor.",OyuncuID, getPlayerName(OyuncuID));
#else
			cheat_state_text("[-!-]Warning[-!-] ID: %i -> %s is using Bullet Crasher",OyuncuID, getPlayerName(OyuncuID));
#endif
		}
		else
		{
			if (getPlayerState(OyuncuID))
			{
				float fPos[3];
				vect3_copy(g_Players->pRemotePlayer[OyuncuID]->pPlayerData->onFootData.fPosition, fPos);

				if (!_finite(fPos[2]))
				{
					p->data[0] = 255;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
					cheat_state_text("[Anti Crasher]ID: %i -> %s Bullet Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[-!-]Warning[-!-] ID: %i -> %s is using Bullet Crasher", OyuncuID, getPlayerName(OyuncuID));
#endif
				}
			}
		}
	}
	if (GelenPaketID == PacketEnumeration::ID_PLAYER_SYNC)
	{
		unsigned short OyuncuID;
		traceLastFunc("Receive ID_PLAYER_SYNC");
		RakNet::BitStream bsOyuncuVerisi((unsigned char*)p->data, p->length, false);
		stOnFootData onFootVeri;
		bsOyuncuVerisi.IgnoreBits(8);
		bsOyuncuVerisi.Read(OyuncuID); 
		memset(&onFootVeri, 0, sizeof(onFootVeri));
		bool bHasLR, bHasUD;
		bool bHasSurfInfo, bAnimation;
		// LEFT/RIGHT KEYS
		bsOyuncuVerisi.Read(bHasLR);
		if (bHasLR) bsOyuncuVerisi.Read(onFootVeri.sLeftRightKeys);

		// UP/DOWN KEYS
		bsOyuncuVerisi.Read(bHasUD);
		if (bHasUD) bsOyuncuVerisi.Read(onFootVeri.sUpDownKeys);

		// GENERAL KEYS
		bsOyuncuVerisi.Read(onFootVeri.sKeys);

		// VECTOR POS
		bsOyuncuVerisi.Read(onFootVeri.fPosition[0]);
		bsOyuncuVerisi.Read(onFootVeri.fPosition[1]);
		bsOyuncuVerisi.Read(onFootVeri.fPosition[2]);

		// ROTATION
		bsOyuncuVerisi.ReadNormQuat(
			onFootVeri.fQuaternion[0],
			onFootVeri.fQuaternion[1],
			onFootVeri.fQuaternion[2],
			onFootVeri.fQuaternion[3]);
		// HEALTH/ARMOUR (COMPRESSED INTO 1 BYTE)
		BYTE byteHealthArmour;
		BYTE byteHealth, byteArmour;
		BYTE byteArmTemp = 0, byteHlTemp = 0;

		bsOyuncuVerisi.Read(byteHealthArmour);
		byteArmTemp = (byteHealthArmour & 0x0F);
		byteHlTemp = (byteHealthArmour >> 4);

		if (byteArmTemp == 0xF) byteArmour = 100;
		else if (byteArmTemp == 0) byteArmour = 0;
		else byteArmour = byteArmTemp * 7;

		if (byteHlTemp == 0xF) byteHealth = 100;
		else if (byteHlTemp == 0) byteHealth = 0;
		else byteHealth = byteHlTemp * 7;

		onFootVeri.byteHealth = byteHealth;
		onFootVeri.byteArmor = byteArmour;

		// CURRENT WEAPON
		int weaponOffset = bsOyuncuVerisi.GetReadOffset();
		bsOyuncuVerisi.Read(onFootVeri.byteCurrentWeapon);

		// Special Action
		bsOyuncuVerisi.Read(onFootVeri.byteSpecialAction);

		// READ MOVESPEED VECTORS
		bsOyuncuVerisi.ReadVector(
			onFootVeri.fMoveSpeed[0],
			onFootVeri.fMoveSpeed[1],
			onFootVeri.fMoveSpeed[2]);

		bsOyuncuVerisi.Read(bHasSurfInfo);
		if (bHasSurfInfo)
		{
			//bsOyuncuVerisi.Read(onFootVeri.wSurfInfo);
			bsOyuncuVerisi.Read(onFootVeri.fSurfingOffsets[0]);
			bsOyuncuVerisi.Read(onFootVeri.fSurfingOffsets[1]);
			bsOyuncuVerisi.Read(onFootVeri.fSurfingOffsets[2]);
		}
		else
			//onFootVeri.wSurfInfo = -1;

			bsOyuncuVerisi.Read(bAnimation);
		if (bAnimation)
		{
			bsOyuncuVerisi.Read(onFootVeri.sCurrentAnimationID);
			bsOyuncuVerisi.Read(onFootVeri.sAnimFlags);
		}

		bool pPlayerVeri = false;
		if (cheat_state->Silent.bSilent)
		{
			RakNet::BitStream bsOnFootSync((unsigned char*)p->data, p->length, false);
			unsigned short PlayerID;
			bsOnFootSync.IgnoreBits(8);
			bsOnFootSync.Read(PlayerID);

			EnemyStats[PlayerID].iPlayerOnFootTick[LastTick::SECOND_LAST] = EnemyStats[PlayerID].iPlayerOnFootTick[LastTick::LAST];
			EnemyStats[PlayerID].iPlayerOnFootTick[LastTick::LAST] = GetTickCount();

			stOnFootData OnFootData;
			memset(&OnFootData, 0, sizeof(stOnFootData));

			bool bLR, bUD;
			bsOnFootSync.Read(bLR);
			if (bLR)
				bsOnFootSync.Read(OnFootData.sLeftRightKeys);
			bsOnFootSync.Read(bUD);
			if (bUD)
				bsOnFootSync.Read(OnFootData.sUpDownKeys);
			bsOnFootSync.Read(OnFootData.sKeys);
			bsOnFootSync.Read(OnFootData.fPosition[0]);
			bsOnFootSync.Read(OnFootData.fPosition[1]);
			bsOnFootSync.Read(OnFootData.fPosition[2]);
			vect3_copy(EnemyStats[PlayerID].fPlayerPos[LastTick::LAST], EnemyStats[PlayerID].fPlayerPos[LastTick::SECOND_LAST]);
			vect3_copy(OnFootData.fPosition, EnemyStats[PlayerID].fPlayerPos[LastTick::LAST]);
		}
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
			if (cheat_state->Korumalar.iAntiDiscoMode)
			{
				if (onFootVeri.byteCurrentWeapon == 44 || onFootVeri.byteCurrentWeapon == 45)
				{
					pPlayerVeri = true;
					bsOyuncuVerisi.SetReadOffset(weaponOffset);
					onFootVeri.byteCurrentWeapon = 0;
					cheat_state_text("[UYARI]ID: %i %s Disco Mode kullanıyor!", OyuncuID, getPlayerName(OyuncuID));
				}
			}
#endif
			if (pPlayerVeri)
			{
				p->data[0] = 255;
				//onFootVeri.byteCurrentWeapon = 0;
			}
		}
		if (GelenPaketID == PacketEnumeration::ID_UNOCCUPIED_SYNC)
		{
			RakNet::BitStream bsUnoData((unsigned char*)p->data, p->length, false);
			stUnoccupiedData UnoData;
			bsUnoData.IgnoreBits(8);
			bsUnoData.Read(OyuncuID);
			bsUnoData.Read((PCHAR)&UnoData, sizeof(stUnoccupiedData));
			bsUnoData.Read(UnoData.sVehicleID);
			/* Passenger Crasher'i fixlemek için. */
			bsUnoData.Read(UnoData.fPosition[0]);
			bsUnoData.Read(UnoData.fPosition[1]);
			bsUnoData.Read(UnoData.fPosition[2]);

			bsUnoData.Read(UnoData.fMoveSpeed[0]);
			bsUnoData.Read(UnoData.fMoveSpeed[1]);
			bsUnoData.Read(UnoData.fMoveSpeed[2]);

			bsUnoData.Read(UnoData.fTurnSpeed[0]);
			bsUnoData.Read(UnoData.fTurnSpeed[1]);
			bsUnoData.Read(UnoData.fTurnSpeed[2]);
			bsUnoData.Read(UnoData.fRoll[0]);
			bsUnoData.Read(UnoData.fRoll[1]);
			bsUnoData.Read(UnoData.fRoll[2]);

			bsUnoData.Read(UnoData.byteSeatID);
			bsUnoData.Read(UnoData.fDirection[0]);
			bsUnoData.Read(UnoData.fDirection[1]);
			bsUnoData.Read(UnoData.fDirection[2]);
			
			bool pUnoccupData = false;
			if (cheat_state->Korumalar.iAntiPassengerCrasher)
			{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
				if (vect3_length(UnoData.fPosition) > 10000.0f || vect3_length(UnoData.fPosition) <= -5000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
				if (vect3_length(UnoData.fPosition) > 20000.0f || vect3_length(UnoData.fPosition) <= -20000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
				if (vect3_length(UnoData.fPosition) > 10000.0f || vect3_length(UnoData.fPosition) <= -10000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION
				if (vect3_length(UnoData.fPosition) > 10000.0f || vect3_length(UnoData.fPosition) <= -5000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
				if (vect3_length(UnoData.fPosition) > 20000.0f || vect3_length(UnoData.fPosition) <= -10000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
				if (vect3_length(UnoData.fPosition) > 10000.0f || vect3_length(UnoData.fPosition) <= -5000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
				if (vect3_length(UnoData.fPosition) > 10000.0f || vect3_length(UnoData.fPosition) <= -5000.0f)
#endif
				{
					pUnoccupData = true;
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					cheat_state_text("[Warning] ID: %i -> %s is using Pass Crasher!", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[Anti-Crasher]ID:%i %s isimli oyuncu Passenger Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
					
#endif

				}
			}

			if (cheat_state->Korumalar.iAntiRollCrasher)// Anti High Roll Crasher!
			{

#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
					if (vect3_length(UnoData.fRoll) >= 1000.0f || vect3_length(UnoData.fRoll) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
					if (vect3_length(UnoData.fRoll) >= 20000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
					if (vect3_length(UnoData.fRoll) >= 1000.0f || vect3_length(UnoData.fRoll) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION
				if (vect3_length(UnoData.fRoll) >= 1000.0f || vect3_length(UnoData.fRoll) <= -1.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
					if (vect3_length(UnoData.fRoll) >= 10000.0f || vect3_length(UnoData.fRoll) <= -1.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
					if (vect3_length(UnoData.fRoll) >= 10000.0f || vect3_length(UnoData.fRoll) <= -1.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
					if (vect3_length(UnoData.fRoll) >= 1000.0f || vect3_length(UnoData.fRoll) <= -1.0f)
#endif
				{
					pUnoccupData = true;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
					cheat_state_text("[Anti-Crasher]ID:%i %s isimli oyuncu Roll Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[Warning]ID: %i -> %s is using Roll Crasher!", OyuncuID, getPlayerName(OyuncuID));
#endif
				}
			}
			if (cheat_state->Korumalar.iAntiDirectionCrasher)
			{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
				if (vect3_length(UnoData.fDirection) >= 1000.0f || vect3_length(UnoData.fDirection) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
				if (vect3_length(UnoData.fDirection) >= 20000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
				if (vect3_length(UnoData.fDirection) >= 1000.0f || vect3_length(UnoData.fDirection) <= -5000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION
				if (vect3_length(UnoData.fDirection) >= 1000.0f || vect3_length(UnoData.fDirection) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
				if (vect3_length(UnoData.fDirection) >= 10000.0f || vect3_length(UnoData.fDirection) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
				if (vect3_length(UnoData.fDirection) >= 1000.0f || vect3_length(UnoData.fDirection) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
				if (vect3_length(UnoData.fDirection) >= 1000.0f || vect3_length(UnoData.fDirection) <= -1000.0f)
#endif
				{
					pUnoccupData = true;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
					cheat_state_text("[Anti-Crasher]ID:%i -> %s isimli oyuncu Direction Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[-!-][Warning] ID: %i -> %s is using Direction Crasher!!!", OyuncuID, getPlayerName(OyuncuID));
#endif
				}
			}
			if (cheat_state->Korumalar.iAntiInvalidBulletsCrasher) // Anti Invalid RapidFire Crasher!
			{
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
				if (vect3_length(UnoData.fTurnSpeed) >= 1000.0f || vect3_length(UnoData.fTurnSpeed) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 10000.0f || vect3_length(UnoData.fTurnSpeed) <= -10000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 5000.0f || vect3_length(UnoData.fTurnSpeed) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 1000.0f || vect3_length(UnoData.fTurnSpeed) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 10000.0f || vect3_length(UnoData.fTurnSpeed) <= -10000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 1000.0f || vect3_length(UnoData.fTurnSpeed) <= -1000.0f)
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
				if (vect3_length(UnoData.fTurnSpeed) >= 1000.0f || vect3_length(UnoData.fTurnSpeed) <= -1000.0f)
#endif
				{
					pUnoccupData = true;
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
					cheat_state_text("[Anti-Crasher]ID:%i -> %s isimli oyuncu Invalid Bullets Crasher kullanıyor.", OyuncuID, getPlayerName(OyuncuID));
#else
					cheat_state_text("[-!-][Warning] ID: %i -> %s is using Direction Crasher!!!", OyuncuID, getPlayerName(OyuncuID));
#endif
				}
			}
			if (pUnoccupData)
			{
				p->data[0] = 255;
			}
		}
		while (p != nullptr) //// OLDDD
		{
			if (OnReceivePacket(p))
				break;
			g_RakClient->GetInterface()->DeallocatePacket(p);
			p = g_RakClient->GetInterface()->Receive();
		}
		return p;
	
}

bool hkRakClientInterface::Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer)
{
	traceLastFunc("HookedRakClientInterface::Connect");

	return g_RakClient->GetInterface()->Connect(host, serverPort, clientPort, depreciated, threadSleepTimer);
}

void hkRakClientInterface::Disconnect(unsigned int blockDuration, unsigned char orderingChannel)
{
	traceLastFunc("HookedRakClientInterface::Disconnect");

	g_RakClient->GetInterface()->Disconnect(blockDuration, orderingChannel);
}

void hkRakClientInterface::InitializeSecurity(const char *privKeyP, const char *privKeyQ)
{
	traceLastFunc("HookedRakClientInterface::InitializeSecurity");

	g_RakClient->GetInterface()->InitializeSecurity(privKeyP, privKeyQ);
}

void hkRakClientInterface::SetPassword(const char *_password)
{
	traceLastFunc("HookedRakClientInterface::SetPassword");

	g_RakClient->GetInterface()->SetPassword(_password);
}

bool hkRakClientInterface::HasPassword(void) const
{
	traceLastFunc("HookedRakClientInterface::HasPassword");

	return g_RakClient->GetInterface()->HasPassword();
}

bool hkRakClientInterface::Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	traceLastFunc("HookedRakClientInterface::Send");

	return g_RakClient->GetInterface()->Send(data, length, priority, reliability, orderingChannel);
}

void hkRakClientInterface::DeallocatePacket(Packet *packet)
{
	traceLastFunc("HookedRakClientInterface::DeallocatePacket");
	//if (set.ConnectionCheats.bQuitFromGameWhenGotBanned)
	//{
	//	if (GetPacketID(packet) == ID_CONNECTION_BANNED)
	//	{
	//		Log("You're banned from server, quiting from game!"); // Ban yediğin sunucuda duranda ne bileyim ya :D
	//		exit(0);
	//	}
	//}
	//if (set.Use_Auto_Reconnect)
	//{
	//	if (GetPacketID(packet) == ID_CONNECTION_LOST || GetPacketID(packet) == ID_DISCONNECTION_NOTIFICATION)
	//	{
	//		/*static DWORD dwDelay = 0;
	//		if (GetTickCount() - dwDelay > set.ConnectionCheats.dwReconnectDelay)
	//		{*/
	//			/*cheat_state_text("Auto Reconnect is working.");*/
	//			disconnect(0);
	//			g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
	//	/*		dwDelay = GetTickCount();
	//		}*/
	//	}
	//}
	g_RakClient->GetInterface()->DeallocatePacket(packet);
}

void hkRakClientInterface::PingServer(void)
{
	traceLastFunc("HookedRakClientInterface::PingServer");

	g_RakClient->GetInterface()->PingServer();
}

void hkRakClientInterface::PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections)
{
	traceLastFunc("HookedRakClientInterface::PingServer");

	g_RakClient->GetInterface()->PingServer(host, serverPort, clientPort, onlyReplyOnAcceptingConnections);
}

int hkRakClientInterface::GetAveragePing(void)
{
	traceLastFunc("HookedRakClientInterface::GetAveragePing");

	return g_RakClient->GetInterface()->GetAveragePing();
}

int hkRakClientInterface::GetLastPing(void) const
{
	traceLastFunc("HookedRakClientInterface::GetLastPing");

	return g_RakClient->GetInterface()->GetLastPing();
}

int hkRakClientInterface::GetLowestPing(void) const
{
	traceLastFunc("HookedRakClientInterface::GetLowestPing");

	return g_RakClient->GetInterface()->GetLowestPing();
}

int hkRakClientInterface::GetPlayerPing(const PlayerID playerId)
{
	traceLastFunc("HookedRakClientInterface::GetPlayerPing");

	return g_RakClient->GetInterface()->GetPlayerPing(playerId);
}

void hkRakClientInterface::StartOccasionalPing(void)
{
	traceLastFunc("HookedRakClientInterface::StartOccasionalPing");

	g_RakClient->GetInterface()->StartOccasionalPing();
}

void hkRakClientInterface::StopOccasionalPing(void)
{
	traceLastFunc("HookedRakClientInterface::StopOccasionalPing");

	g_RakClient->GetInterface()->StopOccasionalPing();
}

bool hkRakClientInterface::IsConnected(void) const
{
	traceLastFunc("HookedRakClientInterface::IsConnected");

	return g_RakClient->GetInterface()->IsConnected();
}

unsigned int hkRakClientInterface::GetSynchronizedRandomInteger(void) const
{
	traceLastFunc("HookedRakClientInterface::GetSynchronizedRandomInteger");

	return g_RakClient->GetInterface()->GetSynchronizedRandomInteger();
}

bool hkRakClientInterface::GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer)
{
	traceLastFunc("HookedRakClientInterface::GenerateCompressionLayer");

	return g_RakClient->GetInterface()->GenerateCompressionLayer(inputFrequencyTable, inputLayer);
}

bool hkRakClientInterface::DeleteCompressionLayer(bool inputLayer)
{
	traceLastFunc("HookedRakClientInterface::DeleteCompressionLayer");

	return g_RakClient->GetInterface()->DeleteCompressionLayer(inputLayer);
}

void hkRakClientInterface::RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms))
{
	traceLastFunc("HookedRakClientInterface::RegisterAsRemoteProcedureCall");

	g_RakClient->GetInterface()->RegisterAsRemoteProcedureCall(uniqueID, functionPointer);
}

void hkRakClientInterface::RegisterClassMemberRPC(int* uniqueID, void *functionPointer)
{
	traceLastFunc("HookedRakClientInterface::RegisterClassMemberRPC");

	g_RakClient->GetInterface()->RegisterClassMemberRPC(uniqueID, functionPointer);
}

void hkRakClientInterface::UnregisterAsRemoteProcedureCall(int* uniqueID)
{
	traceLastFunc("HookedRakClientInterface::UnregisterAsRemoteProcedureCall");

	g_RakClient->GetInterface()->UnregisterAsRemoteProcedureCall(uniqueID);
}

bool hkRakClientInterface::RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	traceLastFunc("HookedRakClientInterface::RPC");

	return g_RakClient->GetInterface()->RPC(uniqueID, data, bitLength, priority, reliability, orderingChannel, shiftTimestamp);
}

void hkRakClientInterface::SetTrackFrequencyTable(bool b)
{
	traceLastFunc("HookedRakClientInterface::SetTrackFrequencyTable");

	g_RakClient->GetInterface()->SetTrackFrequencyTable(b);
}

bool hkRakClientInterface::GetSendFrequencyTable(unsigned int outputFrequencyTable[256])
{
	traceLastFunc("HookedRakClientInterface::GetSendFrequencyTable");

	return g_RakClient->GetInterface()->GetSendFrequencyTable(outputFrequencyTable);
}

float hkRakClientInterface::GetCompressionRatio(void) const
{
	traceLastFunc("HookedRakClientInterface::GetCompressionRatio");

	return g_RakClient->GetInterface()->GetCompressionRatio();
}

float hkRakClientInterface::GetDecompressionRatio(void) const
{
	traceLastFunc("HookedRakClientInterface::GetDecompressionRatio");

	return g_RakClient->GetInterface()->GetDecompressionRatio();
}

void hkRakClientInterface::AttachPlugin(void *messageHandler)
{
	traceLastFunc("HookedRakClientInterface::AttachPlugin");

	g_RakClient->GetInterface()->AttachPlugin(messageHandler);
}

void hkRakClientInterface::DetachPlugin(void *messageHandler)
{
	traceLastFunc("HookedRakClientInterface::DetachPlugin");

	g_RakClient->GetInterface()->DetachPlugin(messageHandler);
}

RakNet::BitStream * hkRakClientInterface::GetStaticServerData(void)
{
	traceLastFunc("HookedRakClientInterface::GetStaticServerData");

	return g_RakClient->GetInterface()->GetStaticServerData();
}

void hkRakClientInterface::SetStaticServerData(const char *data, const int length)
{
	traceLastFunc("HookedRakClientInterface::SetStaticServerData");

	g_RakClient->GetInterface()->SetStaticServerData(data, length);
}

RakNet::BitStream * hkRakClientInterface::GetStaticClientData(const PlayerID playerId)
{
	traceLastFunc("HookedRakClientInterface::GetStaticClientData");

	return g_RakClient->GetInterface()->GetStaticClientData(playerId);
}

void hkRakClientInterface::SetStaticClientData(const PlayerID playerId, const char *data, const int length)
{
	traceLastFunc("HookedRakClientInterface::SetStaticClientData");

	g_RakClient->GetInterface()->SetStaticClientData(playerId, data, length);
}

void hkRakClientInterface::SendStaticClientDataToServer(void)
{
	traceLastFunc("HookedRakClientInterface::SendStaticClientDataToServer");

	g_RakClient->GetInterface()->SendStaticClientDataToServer();
}

PlayerID hkRakClientInterface::GetServerID(void) const
{
	traceLastFunc("HookedRakClientInterface::GetServerID");

	return g_RakClient->GetInterface()->GetServerID();
}

PlayerID hkRakClientInterface::GetPlayerID(void) const
{
	traceLastFunc("HookedRakClientInterface::GetPlayerID");

	return g_RakClient->GetInterface()->GetPlayerID();
}

PlayerID hkRakClientInterface::GetInternalID(void) const
{
	traceLastFunc("HookedRakClientInterface::GetInternalID");

	return g_RakClient->GetInterface()->GetInternalID();
}

const char* hkRakClientInterface::PlayerIDToDottedIP(const PlayerID playerId) const
{
	traceLastFunc("HookedRakClientInterface::PlayerIDToDottedIP");

	return g_RakClient->GetInterface()->PlayerIDToDottedIP(playerId);
}

void hkRakClientInterface::PushBackPacket(Packet *packet, bool pushAtHead)
{
	traceLastFunc("HookedRakClientInterface::PushBackPacket");

	g_RakClient->GetInterface()->PushBackPacket(packet, pushAtHead);
}

void hkRakClientInterface::SetRouterInterface(void *routerInterface)
{
	traceLastFunc("HookedRakClientInterface::SetRouterInterface");

	g_RakClient->GetInterface()->SetRouterInterface(routerInterface);
}
void hkRakClientInterface::RemoveRouterInterface(void *routerInterface)
{
	traceLastFunc("HookedRakClientInterface::RemoveRouterInterface");

	g_RakClient->GetInterface()->RemoveRouterInterface(routerInterface);
}

void hkRakClientInterface::SetTimeoutTime(RakNetTime timeMS)
{
	traceLastFunc("HookedRakClientInterface::SetTimeoutTime");

	g_RakClient->GetInterface()->SetTimeoutTime(timeMS);
}

bool hkRakClientInterface::SetMTUSize(int size)
{
	traceLastFunc("HookedRakClientInterface::SetMTUSize");

	return g_RakClient->GetInterface()->SetMTUSize(size);
}

int hkRakClientInterface::GetMTUSize(void) const
{
	traceLastFunc("HookedRakClientInterface::GetMTUSize");

	return g_RakClient->GetInterface()->GetMTUSize();
}

void hkRakClientInterface::AllowConnectionResponseIPMigration(bool allow)
{
	traceLastFunc("HookedRakClientInterface::AllowConnectionResponseIPMigration");

	g_RakClient->GetInterface()->AllowConnectionResponseIPMigration(allow);
}

void hkRakClientInterface::AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength)
{
	traceLastFunc("HookedRakClientInterface::AdvertiseSystem");

	g_RakClient->GetInterface()->AdvertiseSystem(host, remotePort, data, dataLength);
}

RakNetStatisticsStruct* const hkRakClientInterface::GetStatistics(void)
{
	traceLastFunc("HookedRakClientInterface::GetStatistics");

	return g_RakClient->GetInterface()->GetStatistics();
}

void hkRakClientInterface::ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	traceLastFunc("HookedRakClientInterface::ApplyNetworkSimulator");

	g_RakClient->GetInterface()->ApplyNetworkSimulator(maxSendBPS, minExtraPing, extraPingVariance);
}

bool hkRakClientInterface::IsNetworkSimulatorActive(void)
{
	traceLastFunc("HookedRakClientInterface::IsNetworkSimulatorActive");

	return g_RakClient->GetInterface()->IsNetworkSimulatorActive();
}

PlayerIndex hkRakClientInterface::GetPlayerIndex(void)
{
	traceLastFunc("HookedRakClientInterface::GetPlayerIndex");

	return g_RakClient->GetInterface()->GetPlayerIndex();
}

bool hkRakClientInterface::RPC_(int* uniqueID, RakNet::BitStream* bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID)
{
	traceLastFunc("HookedRakClientInterface::RPC_");

	return g_RakClient->GetInterface()->RPC_(uniqueID, bitStream, priority, reliability, orderingChannel, shiftTimestamp, networkID);
}