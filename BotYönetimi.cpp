#include "main.h" 
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
CBotData* g_BotClient = new CBotData();

void CBotEntity::WriteOnFootSync(stOnFootData* bOnFoot)
{
	RakNet::BitStream bsData;
	bsData.Write((BYTE)ID_PLAYER_SYNC);
	bsData.Write((PCHAR)& bOnFoot, sizeof(stOnFootData));
	g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].pRakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotEntity::WriteAimSync(stAimData* bAimData)
{
	RakNet::BitStream bsData;
	bsData.Write((BYTE)ID_AIM_SYNC);
	bsData.Write((PCHAR)& bAimData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].pRakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotEntity::WriteUnoccupiedSync(stUnoccupiedData* unocData)
{
	RakNet::BitStream bsUnoc;
	bsUnoc.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoc.Write((PCHAR)& unocData, sizeof(stUnoccupiedData));
	g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].pRakClient->Send(&bsUnoc, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotEntity::WriteBulletSync(stBulletData* bulletData)
{
	RakNet::BitStream bsBullet;
	bsBullet.Write((BYTE)ID_BULLET_SYNC);
	bsBullet.Write((PCHAR)& bulletData, sizeof(stBulletData));
	g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].pRakClient->Send(&bsBullet, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotEntity::SendFakeBulletData(uint16_t PlayerID, float Origin[3], float Target[3], float Center[3], uint8_t WeaponID, BYTE type)
{

	stBulletData bulletSync;
	ZeroMemory(&bulletSync, sizeof(stBulletData));
	if (PlayerID == g_Players->sLocalPlayerID)
		return;
	g_BotFuncs->BotSettings.sTargetID = bulletSync.sTargetID;
	//if()
	bulletSync.sTargetID = PlayerID;

	bulletSync.fOrigin[0] = Origin[0];
	bulletSync.fOrigin[1] = Origin[1];
	bulletSync.fOrigin[2] = Origin[2];

	bulletSync.fTarget[0] = Target[0];
	bulletSync.fTarget[1] = Target[1];
	bulletSync.fTarget[2] = Target[2];

	bulletSync.fCenter[0] = Center[0];
	bulletSync.fCenter[1] = Center[1];
	bulletSync.fCenter[2] = Center[2];

	bulletSync.byteWeaponID = WeaponID;

	bulletSync.byteType = type;
	RakNet::BitStream bsSync;
	bsSync.Write((BYTE)ID_BULLET_SYNC);
	bsSync.Write((PCHAR)(&bulletSync), sizeof(stBulletData));
	g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].pRakClient->Send(&bsSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotEntity::SendFakeKick(uint16_t iClientID, uint16_t VehicleID, BOOL bPassenger)
{
	RakNet::BitStream bsSend;
	BYTE bytePassenger = 0;

	if (bPassenger)
		bytePassenger = 1;

	bsSend.Write(VehicleID);
	bsSend.Write(bytePassenger);
	g_BotFuncs->OL_Bot_SendRPC(iClientID, RPC_EnterVehicle, bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, false);
}

#endif