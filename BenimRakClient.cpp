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

MyRakClient *g_RakClient = NULL;

#define RAKNET_MTU_SIZE			 576
MyRakClient::MyRakClient(void *pRakClientInterface)
{
	pRakClient = (MyRakClientInterface *)pRakClientInterface;
}

bool MyRakClient::RPC(int rpcId, RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if ( !pRakClient )
		return false;

	return pRakClient->RPC(&rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp );
}

bool MyRakClient::Send(RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if ( !pRakClient )
		return false;

	return pRakClient->Send( bitStream, priority, reliability, orderingChannel );
}

// misc functions
void MyRakClient::SendDeath(uint16_t killerId, uint8_t reason)
{
	RakNet::BitStream bsDeath;

	bsDeath.Write( reason );
	bsDeath.Write( killerId );
	g_RakClient->RPC( RPC_Death, &bsDeath );
}

void MyRakClient::SendGiveDamage(int iPlayerID, float fDamage, int iWeaponID, int iBodyPart)
{
	RakNet::BitStream bsGiveDamage;

	bsGiveDamage.Write<bool>(false);
	bsGiveDamage.Write<WORD>(iPlayerID);
	bsGiveDamage.Write<float>(fDamage);
	bsGiveDamage.Write<int>(iWeaponID);
	bsGiveDamage.Write<int>(iBodyPart);
	g_RakClient->RPC(RPC_GiveTakeDamage, &bsGiveDamage);
}
void MyRakClient::SendGivenDamage(bool giveTake, int playerID, float fDamage, int iWeaponID, int iBodyPart)
{
	RakNet::BitStream bsDamage;
	bsDamage.Write<bool>(giveTake);
	bsDamage.Write<WORD>(playerID);
	bsDamage.Write<float>(fDamage);
	bsDamage.Write<int>(iWeaponID);
	bsDamage.Write<int>(iBodyPart);
	g_RakClient->RPC(RPC_GiveTakeDamage, &bsDamage);
}

void MyRakClient::SendEnterPlayerVehicle(USHORT VehicleID, BYTE seat)
{
	RakNet::BitStream VehicleEnter;

	VehicleEnter.Write(VehicleID);
	VehicleEnter.Write(seat);
	g_RakClient->RPC(RPC_EnterVehicle, &VehicleEnter, HIGH_PRIORITY, RELIABLE_ORDERED, 0, 0);
}

void MyRakClient::SendPickUp(int pickupId)
{
	RakNet::BitStream bsPickup;

	bsPickup.Write( pickupId );
	
	RPC( RPC_PickedUpPickup, &bsPickup );
}

void MyRakClient::RequestClass(int classId)
{
	RakNet::BitStream bsClass;

	bsClass.Write( classId );
	g_RakClient->RPC( RPC_RequestClass, &bsClass );
}

void MyRakClient::SendSCMEvent(int vehicleID, int eventId, int param1, int param2)
{
	RakNet::BitStream bsScmEvent;

	bsScmEvent.Write ( vehicleID );
	bsScmEvent.Write ( param1 );
	bsScmEvent.Write ( param2 );
	bsScmEvent.Write ( eventId );

	RPC( RPC_SCMEvent, &bsScmEvent );
}

void MyRakClient::SendSpawn(void)
{
	RakNet::BitStream bsSpawn;

	g_RakClient->RPC( RPC_RequestSpawn, &bsSpawn );
	g_RakClient->RPC( RPC_Spawn, &bsSpawn );
}

void MyRakClient::SendFakeDriverFullSyncData(stInCarData *picSync, int iUseCarPos)
{
	if (picSync == NULL)
		return;

	RakNet::BitStream bsVehicleSync;

	if (iUseCarPos)
	{
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[picSync->sVehicleID]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

		if (!vinfo)
			return;

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

		picSync->fPosition[0] = fPos[0];
		picSync->fPosition[1] = fPos[1];
		picSync->fPosition[2] = fPos[2];
	}

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)picSync, sizeof(stInCarData));

	g_RakClient->Send(&bsVehicleSync);
}

void MyRakClient::SendModifiedBulletData(uint16_t targetID, float fOrigin[3], float fTarget[3], float fCenter[3], BYTE bWeapID, BYTE bTypeOfHit)
{
	stBulletData bulletSync;
	ZeroMemory(&bulletSync, sizeof(stBulletData));

	bulletSync.sTargetID = targetID;

	bulletSync.fOrigin[0] = fOrigin[0];
	bulletSync.fOrigin[1] = fOrigin[1];
	bulletSync.fOrigin[2] = fOrigin[2];

	bulletSync.fTarget[0] = fTarget[0];
	bulletSync.fTarget[1] = fTarget[1];
	bulletSync.fTarget[2] = fTarget[2];

	bulletSync.fCenter[0] = fCenter[0];
	bulletSync.fCenter[1] = fCenter[1];
	bulletSync.fCenter[2] = fCenter[2];

	bulletSync.byteWeaponID = bWeapID;

	bulletSync.byteType = bTypeOfHit;

	RakNet::BitStream bsSync;
	bsSync.Write((BYTE)ID_BULLET_SYNC);
	bsSync.Write((PCHAR)(&bulletSync), sizeof(stBulletData));
	g_RakClient->Send(&bsSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakeBulletData(uint16_t PlayerID, float Origin[3], float Target[3], float  Center[3], uint8_t WeaponID, BYTE type)
{

	stBulletData bulletSync;
	ZeroMemory(&bulletSync, sizeof(stBulletData));

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
	g_RakClient->Send(&bsSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakePassengerSyncData(WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
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
	bsVehicleSync.Write((PCHAR)&PassData, sizeof(stPassengerData));
	g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendUnoccupiedSyncData(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], int SeatID, float fRoll[3])
{
	stUnoccupiedData unSync;
	ZeroMemory(&unSync, sizeof(stUnoccupiedData));
	unSync.sVehicleID = vehicleid;

	unSync.fPosition[0] = fPos[0];
	unSync.fPosition[1] = fPos[1];
	unSync.fPosition[2] = fPos[2];

	unSync.fHealth = HealthCar;
	unSync.fMoveSpeed[0] = Speed[0];
	unSync.fMoveSpeed[1] = Speed[1];
	unSync.fMoveSpeed[2] = Speed[2];

	unSync.fRoll[0] = fRoll[0];
	unSync.fRoll[1] = fRoll[1];
	unSync.fRoll[2] = fRoll[2];

	unSync.fDirection[0] = 0;
	unSync.fDirection[1] = 1;
	unSync.fDirection[2] = 0;

	unSync.fTurnSpeed[0] = 0;
	unSync.fTurnSpeed[1] = 0;
	unSync.fTurnSpeed[2] = 0;

	unSync.byteSeatID = SeatID;
	RakNet::BitStream bsUnoccupiedSync;
	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
	g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendExitPlayerVehicle(USHORT VehicleID)
{
	RakNet::BitStream bsSend;
	bsSend.Write(VehicleID);
	g_RakClient->RPC(RPC_ExitVehicle, &bsSend);
}
void MyRakClient::SendFakeUnoccupiedSyncData(uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3])
{
	stUnoccupiedData picSync;
	memset(&picSync, 0, sizeof(stUnoccupiedData));
	RakNet::BitStream bsUnoccupiedSync;
	picSync.sVehicleID = VehicleID;
	picSync.byteSeatID = SeatID;
	struct vehicle_info *vinfo = getGTAVehicleFromSAMPVehicleID(VehicleID);
	/*picSync.fDirection[0] = sqrt((float)-1);
	picSync.fDirection[1] = sqrt((float)-1);
	picSync.fDirection[2] = sqrt((float)-1);*/
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
	g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::sendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp)
{
	BYTE respLen = (BYTE)strlen(szInputResp);
	RakNet::BitStream bsSend;
	bsSend.Write(wDialogID);
	bsSend.Write(bButtonID);
	bsSend.Write(wListBoxItem);
	bsSend.Write(respLen);
	bsSend.Write(szInputResp, respLen);
	g_RakClient->RPC(RPC_DialogResponse, &bsSend);
}
void MyRakClient::SendLagToServer() // N3X Projesindeki exploit'in kaynak kodu. La Pirula Projesinde var. La Pirula Project
{
	static int	players = 0, vehicles = 0, pickups = 0, menus = 0, textdraws = 0, dialogs = 0, classes = 0;
	RakNet::BitStream	bsPlayers, bsVehicles, bsPickups, bsMenus, bsTextDraws;

	bsPlayers.Write(players);
	bsVehicles.Write(vehicles);
	bsPickups.Write(pickups);
	bsMenus.Write(menus);
	bsTextDraws.Write(textdraws);

	g_RakClient->RPC(RPC_ClickPlayer, &bsPlayers, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RPC(RPC_EnterVehicle, &bsVehicles, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RPC(RPC_ExitVehicle, &bsVehicles, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RPC(RPC_PickedUpPickup, &bsPickups, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RequestClass(classes);
	g_RakClient->SendSpawn();
	g_RakClient->sendDialogResponse(dialogs, 1, 1, "");
	g_RakClient->RPC(RPC_MenuSelect, &bsMenus, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RPC(RPC_MenuQuit, &bsMenus, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);
	g_RakClient->RPC(RPC_ClickTextDraw, &bsTextDraws, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, false);

	players++;
	vehicles++;
	pickups++;
	menus++;
	textdraws++;
	dialogs++;
	classes++;

	if (players >= SAMP_MAX_PLAYERS) players = 0;
	if (vehicles >= SAMP_MAX_VEHICLES) vehicles = 0;
	if (pickups >= SAMP_MAX_PICKUPS) pickups = 0;
	if (menus >= SAMP_MAX_MENUS) menus = 0;
	if (textdraws >= SAMP_MAX_TEXTDRAWS) textdraws = 0;
	if (dialogs >= SAMP_MAX_DIALOGS) dialogs = 0;
	if (classes >= SAMP_MAX_SKINS) classes = 0;
}

void MyRakClient::SendFakeDriverSyncData(int iSAMPVehicleID, float fVehiclePos[3],float fVehicleHealth, float fMoveSpeed[3])
{
	stInCarData InCarData;
	RakNet::BitStream bsInCarData;

	struct actor_info *pSelfActor = actor_info_get(ACTOR_SELF, 0);

	InCarData.sVehicleID = iSAMPVehicleID;
	InCarData.fMoveSpeed[0] = fMoveSpeed[0];
	InCarData.fMoveSpeed[1] = fMoveSpeed[1];
	InCarData.fMoveSpeed[2] = fMoveSpeed[2];
	InCarData.fPosition[0] = fVehiclePos[0];
	InCarData.fPosition[1] = fVehiclePos[1];
	InCarData.fPosition[2] = fVehiclePos[2];
	InCarData.fVehicleHealth = fVehicleHealth;
	InCarData.bytePlayerHealth = (BYTE)pSelfActor->hitpoints;
	InCarData.byteArmor = (BYTE)pSelfActor->armor;

	if (cheat_state->state == CHEAT_STATE_VEHICLE)
		InCarData.byteCurrentWeapon = g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;

	else if (cheat_state->state == CHEAT_STATE_ACTOR)
		InCarData.byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;

	else InCarData.byteCurrentWeapon = 0;

	bsInCarData.Write((BYTE)ID_VEHICLE_SYNC);
	bsInCarData.Write((PCHAR)&InCarData, sizeof(stInCarData));

	g_RakClient->Send(&bsInCarData, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakeUnoccupiedFullSyncData(stUnoccupiedData *punocSync)
{
	if (punocSync == NULL)
		return;

	RakNet::BitStream bsUnocSync;

	bsUnocSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnocSync.Write((PCHAR)punocSync, sizeof(stUnoccupiedData));

	g_RakClient->Send(&bsUnocSync);
}
void MyRakClient::SendBulletData()
{
	RakNet::BitStream bsBulletdata;
	stBulletData bulletSync;
	ZeroMemory(&bulletSync, sizeof(stBulletData));

	bsBulletdata.Write((BYTE)ID_BULLET_SYNC);
	bsBulletdata.Write((PCHAR)&bulletSync, sizeof(stBulletData));

	g_RakClient->Send(&bsBulletdata, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendEnterVehicleNotification(uint16_t VehicleID, BOOL bPassenger)
{
	RakNet::BitStream bsSend;
	BYTE bytePassenger = 0;

	if (bPassenger)
		bytePassenger = 1;

	bsSend.Write(VehicleID);
	bsSend.Write(bytePassenger);

	g_RakClient->RPC(RPC_EnterVehicle, &bsSend);
}

void MyRakClient::NotifyVehicleDeath(int VehicleID)
{
	RakNet::BitStream bsDeath;
	bsDeath.Write(VehicleID);
	g_RakClient->RPC(RPC_VehicleDestroyed, &bsDeath);
}
void MyRakClient::SendFuckingTrailerData(WORD wTrailerID, float fPosition[3], float fRoll[3], float fDirection[3], float fMoveSpeed[3])
{
    stTrailerData TRSenk;
    ZeroMemory(&TRSenk, sizeof(stTrailerData));
    TRSenk.sTrailerID = wTrailerID;

    TRSenk.fPosition[0] = fPosition[0];
    TRSenk.fPosition[1] = fPosition[1];
    TRSenk.fPosition[2] = fPosition[2];

	TRSenk.fMoveSpeed[0] = fMoveSpeed[0];
	TRSenk.fMoveSpeed[1] = fMoveSpeed[1];
	TRSenk.fMoveSpeed[2] = fMoveSpeed[2];

	TRSenk.fRoll[0] = fRoll[0];
	TRSenk.fRoll[1] = fRoll[1];
	TRSenk.fRoll[2] = fRoll[2];
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
    TRSenk.fDirection[0] = fDirection[0];
    TRSenk.fDirection[1] = fDirection[1];
    TRSenk.fDirection[2] = fDirection[2];
#endif
    RakNet::BitStream bsTrailerVeri;
    bsTrailerVeri.Write((BYTE)ID_TRAILER_SYNC);
    bsTrailerVeri.Write((PCHAR)(&TRSenk), sizeof(stTrailerData));
    g_RakClient->Send(&bsTrailerVeri, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
/* RapidFire is always best */

void MyRakClient::SendFakeOnfootSyncData2(float fPos[3], float fSpeed[3], float Health, float Armor, int AnimFlags, int AnimationID, float Quaternion[4], int sKeys)
{
	stOnFootData onSync;
	ZeroMemory(&onSync, sizeof(stOnFootData));

	onSync.byteHealth = Health;
	onSync.byteArmor = Armor;

	onSync.fPosition[0] = fPos[0];
	onSync.fPosition[1] = fPos[1];
	onSync.fPosition[2] = fPos[2];

	onSync.fMoveSpeed[0] = fSpeed[0];
	onSync.fMoveSpeed[1] = fSpeed[1];
	onSync.fMoveSpeed[2] = fSpeed[2];

	onSync.fQuaternion[0] = Quaternion[0];
	onSync.fQuaternion[1] = Quaternion[1];
	onSync.fQuaternion[2] = Quaternion[2];
	onSync.fQuaternion[3] = Quaternion[3];

	onSync.sAnimFlags = AnimFlags;
	onSync.sCurrentAnimationID = AnimationID;

	onSync.sKeys = sKeys;

	RakNet::BitStream bsData;
	bsData.Write((BYTE)ID_PLAYER_SYNC);
	bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakeOnfootSyncData(float fPos[3], float fSpeed[3], float Health, float Armor, int AnimFlags, int AnimationID, float Quaternion[4])
{
	stOnFootData onSync;
	ZeroMemory(&onSync, sizeof(stOnFootData));

	onSync.byteHealth = Health;
	onSync.byteArmor = Armor;

	onSync.fPosition[0] = fPos[0];
	onSync.fPosition[1] = fPos[1];
	onSync.fPosition[2] = fPos[2];

	onSync.fMoveSpeed[0] = fSpeed[0];
	onSync.fMoveSpeed[1] = fSpeed[1];
	onSync.fMoveSpeed[2] = fSpeed[2];

	onSync.fQuaternion[0] = Quaternion[0];
	onSync.fQuaternion[1] = Quaternion[1];
	onSync.fQuaternion[2] = Quaternion[2];
	onSync.fQuaternion[3] = Quaternion[3];

	onSync.sAnimFlags = AnimFlags;
	onSync.sCurrentAnimationID = AnimationID;

	RakNet::BitStream bsData;
	bsData.Write((BYTE)ID_PLAYER_SYNC);
	bsData.Write((PCHAR)&onSync, sizeof(stOnFootData));
	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakeOnfootFullSyncData(struct stOnFootData *pofSync)
{
	if (pofSync == NULL)
		return;

	RakNet::BitStream bsOnfootSync;
	bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
	bsOnfootSync.Write((PCHAR)pofSync, sizeof(stOnFootData));
	g_RakClient->Send(&bsOnfootSync);
}
void MyRakClient::SendDamage(uint16_t uiPlayerID, float fDamageAmountToSend, int iWeaponID, int iBodyPart)
{
	RakNet::BitStream bsSendDamage;
	bsSendDamage.Write(false); // I will "send" the damage... not "take"... I will create a different function to "take" damage...
	bsSendDamage.Write(uiPlayerID); // Send the damage, but send the damage to who? -> Player!
	bsSendDamage.Write(fDamageAmountToSend); // Send the damage to player, but how much?!?! -> fDamageAmount!
	bsSendDamage.Write(iWeaponID);
	bsSendDamage.Write(iBodyPart);
	g_RakClient->RPC(RPC_GiveTakeDamage, &bsSendDamage, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, FALSE);
}
void MyRakClient::SendFakeBulletFullSyncData(stBulletData *pBulletSync)
{
	if (pBulletSync == NULL)
		return;

	RakNet::BitStream bsBulletSync;
	bsBulletSync.Write((BYTE)ID_BULLET_SYNC);
	bsBulletSync.Write((PCHAR)pBulletSync, sizeof(stBulletData));
	g_RakClient->Send(&bsBulletSync);
}

void MyRakClient::SyncFakeEnterVehicle(WORD vehicleid, int  passid)
{
	RakNet::BitStream bs;
	bs.Write(vehicleid);
	bs.Write(passid);
	g_RakClient->RPC(RPC_EnterVehicle, &bs);
}
void MyRakClient::SendFakeDriverSyncData2(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], WORD key, WORD trailer)
{
	struct actor_info *self = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
	stInCarData InCarData;
	ZeroMemory(&InCarData, sizeof(stInCarData));
	RakNet::BitStream bsVehicleSync;
	InCarData.sVehicleID = vehicleid;

	InCarData.fPosition[0] = fPos[0];
	InCarData.fPosition[1] = fPos[1];
	InCarData.fPosition[2] = fPos[2];

	InCarData.fVehicleHealth = HealthCar;

	InCarData.fMoveSpeed[0] = Speed[0];
	InCarData.fMoveSpeed[1] = Speed[1];
	InCarData.fMoveSpeed[2] = Speed[2];

	InCarData.sKeys = key;
	InCarData.bytePlayerHealth = self->hitpoints;
	InCarData.byteArmor = self->armor;

	InCarData.sTrailerID = trailer;

	bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
	bsVehicleSync.Write((PCHAR)&InCarData, sizeof(stInCarData));
	g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void MyRakClient::SendUnoccupiedSyncData(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], int SeatID)
{
	stUnoccupiedData unSync;
	ZeroMemory(&unSync, sizeof(stUnoccupiedData));
	unSync.sVehicleID = vehicleid;

	unSync.fPosition[0] = fPos[0];
	unSync.fPosition[1] = fPos[1];
	unSync.fPosition[2] = fPos[2];


	unSync.fMoveSpeed[0] = Speed[0];
	unSync.fMoveSpeed[1] = Speed[1];
	unSync.fMoveSpeed[2] = Speed[2];

	unSync.fRoll[0] = 1;
	unSync.fRoll[1] = 0;
	unSync.fRoll[2] = 0;

	unSync.fDirection[0] = 0;
	unSync.fDirection[1] = 1;
	unSync.fDirection[2] = 0;

	unSync.fTurnSpeed[0] = 0;
	unSync.fTurnSpeed[1] = 0;
	unSync.fTurnSpeed[2] = 0;
	unSync.byteSeatID = SeatID;	
	unSync.fHealth = HealthCar;
	RakNet::BitStream bsUnoccupiedSync;
	bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC);
	bsUnoccupiedSync.Write((PCHAR)&unSync, sizeof(stUnoccupiedData));
	g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendFakeTrailerData(WORD vehicleid, float fpos[3], float HealthCar, float Speed[3])
{

	stTrailerData trailer_sync;
	ZeroMemory(&trailer_sync, sizeof(stTrailerData));
	trailer_sync.sTrailerID = vehicleid;
	vect3_copy(fpos, trailer_sync.fPosition);
	vect3_copy(Speed, trailer_sync.fMoveSpeed);
	RakNet::BitStream bsPackettrailer;
	bsPackettrailer.Write((BYTE)ID_TRAILER_SYNC);
	bsPackettrailer.Write((PCHAR)(&trailer_sync), sizeof(trailer_sync));
	g_RakClient->Send(&bsPackettrailer, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::GivePlayerWeapon(uint16_t playerid, BYTE weaponid, WORD ammo)
{
	RakNet::BitStream bsData;
	bsData.Write(playerid);
	bsData.Write(weaponid);
	bsData.Write(ammo);
	g_RakClient->RPC(RPC_GivePlayerWeapon, &bsData, HIGH_PRIORITY, RELIABLE, 0, 0);
}


//void MyRakClient::SendFuckingTrailerData(WORD wTrailerID, float fPosition[3], float fRoll[3], float fDirection[3], float fMoveSpeed[3])
//{
//	stTrailerData TRSenk;
//	ZeroMemory(&TRSenk, sizeof(stTrailerData));
//	TRSenk.sTrailerID = wTrailerID;
//
//	TRSenk.fPosition[0] = fPosition[0];
//	TRSenk.fPosition[1] = fPosition[1];
//	TRSenk.fPosition[2] = fPosition[2];
//
//	TRSenk.fRoll[0] = fRoll[0];
//	TRSenk.fRoll[1] = fRoll[1];
//	TRSenk.fRoll[2] = fRoll[2];
//
//	/*TRSenk.fDirection[0] = fDirection[0];
//	TRSenk.fDirection[1] = fDirection[1];
//	TRSenk.fDirection[2] = fDirection[2]*/;
//
//	TRSenk.fMoveSpeed[0] = fMoveSpeed[0];
//	TRSenk.fMoveSpeed[1] = fMoveSpeed[1];
//	TRSenk.fMoveSpeed[2] = fMoveSpeed[2];
//
//	RakNet::BitStream bsTrailerVeri;
//	bsTrailerVeri.Write((BYTE)ID_TRAILER_SYNC);
//	bsTrailerVeri.Write((PCHAR)(&TRSenk), sizeof(stTrailerData));
//	g_RakClient->Send(&bsTrailerVeri, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
//}

void MyRakClient::SendFakeNewOnfootSyncData(float fPos[3], float fSpeed[3], float Health, float Armor)
{
	stOnFootData onSync;
	ZeroMemory(&onSync, sizeof(stOnFootData));

	onSync.byteHealth = Health;
	onSync.byteArmor = Armor;

	onSync.fPosition[0] = fPos[0];
	onSync.fPosition[1] = fPos[1];
	onSync.fPosition[2] = fPos[2];

	onSync.fMoveSpeed[0] = fSpeed[0];
	onSync.fMoveSpeed[1] = fSpeed[1];
	onSync.fMoveSpeed[2] = fSpeed[2];

	RakNet::BitStream bsData;
	bsData.Write((BYTE)ID_PLAYER_SYNC);
	bsData.Write((PCHAR)& onSync, sizeof(stOnFootData));
	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void MyRakClient::SendFullFakeUnoccupiedFuckingSyncData(uint16_t VehicleID, uint8_t SeatID, float fDirection[3], float Pos[3], float Speed[3], float Health, float spin[3], float roll[3])
{
	stUnoccupiedData picSync;
	memset(&picSync, 0, sizeof(stUnoccupiedData));
	RakNet::BitStream bsUnoccupiedSync;
	picSync.sVehicleID = VehicleID;
	picSync.byteSeatID = SeatID;
	struct vehicle_info* vinfo = getGTAVehicleFromSAMPVehicleID(VehicleID);
	picSync.fDirection[0] = fDirection[0];
	picSync.fDirection[1] = fDirection[1];
	picSync.fDirection[2] = fDirection[2];
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
	g_RakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MyRakClient::SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires)
{
	RakNet::BitStream bsDamageVehicle;
	bsDamageVehicle.Write(vehicleID);
	bsDamageVehicle.Write(panel);//(panel);  //<3
	bsDamageVehicle.Write(door);//(door);
	bsDamageVehicle.Write(lights);//(lights);
	bsDamageVehicle.Write(tires);//tires
	g_RakClient->RPC(RPC_DamageVehicle, &bsDamageVehicle, HIGH_PRIORITY, RELIABLE, 0, 0);
}