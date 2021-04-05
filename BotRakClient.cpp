#include "main.h"
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
CBotEntity* g_BotEntity = new CBotEntity();
void CBotData::SendEnterPlayerVehicle(uint16_t iClientID, USHORT VehicleID, BYTE seat)
{
	RakNet::BitStream VehicleEnter;

	VehicleEnter.Write(VehicleID);
	VehicleEnter.Write(seat);
	g_BotFuncs->OL_Bot_SendRPC(iClientID, RPC_EnterVehicle, VehicleEnter, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}
void CBotData::SendExitPlayerVehicle(uint16_t iClientID, USHORT VehicleID)
{
	RakNet::BitStream bsSend;
	bsSend.Write(VehicleID);
	g_BotFuncs->OL_Bot_SendRPC(iClientID, RPC_ExitVehicle, bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, 0);
}
void CBotData::SendFakeUnoccupiedSyncData(uint16_t iClientID, uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3])
{
	stUnoccupiedData picSync;
	memset(&picSync, 0, sizeof(stUnoccupiedData));
	RakNet::BitStream bsUnoccupiedSync;
	picSync.sVehicleID = VehicleID;
	picSync.byteSeatID = SeatID;
	struct vehicle_info *vinfo = getGTAVehicleFromSAMPVehicleID(VehicleID);
	picSync.fDirection[0] = vinfo->base.matrix[4 * 1 + 0];
	picSync.fDirection[1] = vinfo->base.matrix[4 * 1 + 1];
	picSync.fDirection[2] = vinfo->base.matrix[4 * 1 + 2];
	picSync.fRoll[0] = roll[0];
	picSync.fRoll[1] = roll[1];
	picSync.fRoll[2] = roll[2];
	picSync.fPosition[0] = Pos[0];
	picSync.fPosition[1] = Pos[1];
	picSync.fPosition[2] = Pos[2];
	picSync.fMoveSpeed[0] = Speed[0];
	picSync.fMoveSpeed[1] = Speed[1];
	picSync.fMoveSpeed[2] = Speed[2];
	picSync.fTurnSpeed[0] = spin[0];
	picSync.fTurnSpeed[1] = spin[1];
	picSync.fTurnSpeed[2] = spin[2];
	picSync.fHealth = Health;
	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&picSync, sizeof(stUnoccupiedData));
	g_BotFuncs->BotClient[iClientID].pRakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void CBotData::SendFakePassengerSyncData(uint16_t iClientID, WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key)
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	stPassengerData PassData;
	ZeroMemory(&PassData, sizeof(stPassengerData));
	RakNet::BitStream bsVehicleSync;
	PassData.sVehicleID = vehicleid;

	PassData.fPosition[0] = fPos[0];
	PassData.fPosition[1] = fPos[1];
	PassData.fPosition[2] = fPos[2];
	PassData.byteCurrentWeapon = WeaponID;
	PassData.sKeys = key;
	PassData.byteSeatID = SeatID;
	PassData.byteHealth = self->hitpoints;
	PassData.byteArmor = self->armor;
	bsVehicleSync.Write((BYTE)ID_PASSENGER_SYNC);
	bsVehicleSync.Write((PCHAR)& PassData, sizeof(stPassengerData));
	g_BotFuncs->BotClient[iClientID].pRakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

int NearestPlayer()
{
	actor_info *self = actor_info_get(ACTOR_SELF, 0);

	float fNearestDistance = -1.0f;
	int iplayerID = -1;

	for (int playerID = 0; playerID < SAMP_MAX_PLAYERS; playerID++)
	{
		if (g_Players->iIsListed[playerID] != 1)
			continue;
		if (g_Players->pRemotePlayer[playerID] == NULL)
			continue;
		if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
			continue;
		if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
			continue;	// not streamed
		if (g_BotFuncs->uiIsBot[playerID][0] == 1)
			continue;
		if (!BotCheats->bUseFriendTarget && g_NewModSa->iArkadasID[playerID])
			continue;
		float fDistance = vect3_dist(&self->base.matrix[12], &g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
		if (fNearestDistance == -1.0f || fDistance < fNearestDistance)
		{
			iplayerID = playerID;
			fNearestDistance = fDistance;
		}
	}

	return iplayerID;
}

#endif