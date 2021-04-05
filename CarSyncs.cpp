#include "main.h"
#define ID_SYNC_DATA_INCAR 0
#define ID_SYNC_DATA_UNOC 1
#define ID_SYNC_DATA_TRAILER 2
#define ID_SYNC_DATA_PASSENGER 3
#define ID_SYNC_DATA_IN_CAR_RPC 4
void GetStreamedVehicle(static int v)
{
	for (v++; v < SAMP_MAX_VEHICLES; v++)
	{
		if (g_Players->pLocalPlayer->sCurrentVehicleID == v)
		{ continue; }
		if (g_Vehicles->iIsListed[v] != 1)
		{ continue; }
		if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
		{ continue; }
		if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
		{ continue; }
		if ((cheat_state->Arac.bWithoutDriver && g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle->passengers[0] != NULL))
			continue;
		break;
	}

}
void VehicleSynchronization(float fPosition[3], float fMoveSpeed[3], bool bUseMakeZeroHPforCars)
{

	//RakNet::BitStream bsData;
	//RakNet::BitStream bsData4RPC;
	//vehicle_info* vehicle =
	//	GetVehicleInfoStandart(
	//		VEHICLE_NO_BE_PROTECT |
	//		VEHICLE_NOT_FRIEND |
	//		VEHICLE_NOT_OCCUPIED |
	//		VEHICLE_NOT_CLOSED,
	//		VEHICLE_CLOSEST |
	//		VEHICLE_NOT_MY |
	//		VEHICLE_ALIVE |
	//		VEHICLE_NOT_TRAIN);
	//if (!vehicle)
	//	return;
	//int iAracID = getSAMPVehicleIDFromGTAVehicle(vehicle);

	//if (!g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle && !cheat_state->Arac.iCarPosLagger)
	//{
	//	RakNet::BitStream bsData4OnFoot;
	//	bsData4OnFoot.Write((BYTE)ID_PLAYER_SYNC);
	//	bsData4OnFoot.Write((PCHAR)&g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
	//	g_RakClient->Send(&bsData4OnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	//}
	//stInCarData inCar;
	//stUnoccupiedData Unoc;
	//stTrailerData TrailerSync;
	//stPassengerData passenger;
	//switch (set.CarCheats.iCarSyncType)
	//{
	//case ID_SYNC_DATA_INCAR: // InCar
	//{
	//	memset(&inCar, 0, sizeof(stInCarData));
	//	inCar.sVehicleID = iAracID;
	//	if (bUseMakeZeroHPforCars)
	//		inCar.fVehicleHealth = 1.0f;
	//	else
	//		inCar.fVehicleHealth = vehicle->hitpoints;
	//	if (set.CarCheats.Information_About_My_Sync)
	//		cheat_state_text("Information:You are using InCar Sync");
	//	inCar.bytePlayerHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
	//	inCar.byteArmor = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->armor;
	//	inCar.fQuaternion[3] = 1;
	//	vect3_copy(fPosition, inCar.fPosition);
	//	vect3_copy(fMoveSpeed, inCar.fMoveSpeed);
	//	bsData.Write((BYTE)ID_VEHICLE_SYNC);
	//	bsData.Write((PCHAR)&inCar, sizeof(stInCarData));
	//	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	//}
	//break;
	//case ID_SYNC_DATA_UNOC: // %50 By me(RapidFire) Unoccupied
	//{
	//	memset(&Unoc, 0, sizeof(stUnoccupiedData));
	//	Unoc.sVehicleID = iAracID;
	//	if (bUseMakeZeroHPforCars)
	//		Unoc.fHealth = 1.0f;
	//	else
	//		Unoc.fHealth = vehicle->hitpoints;
	//	if (set.CarCheats.Information_About_My_Sync)
	//		cheat_state_text("Information:You are using UnOccupiedSync");
	//	vect3_copy(fPosition, Unoc.fPosition);
	//	vect3_copy(fMoveSpeed, Unoc.fMoveSpeed);
	//	Unoc.byteSeatID = 1;
	//	Unoc.fDirection[1] = 1;
	//	Unoc.fRoll[0] = 1;
	//	Unoc.fHealth = vehicle->hitpoints;//1000.0f;
	//	bsData.Write((BYTE)ID_UNOCCUPIED_SYNC);
	//	bsData.Write((PCHAR)&Unoc, sizeof(stUnoccupiedData));
	//	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	//}
	//break;
	//case ID_SYNC_DATA_TRAILER: // %100 By me(RapidFire) Trailer
	//{
	//	g_RakClient->SendFakeDriverSyncData2(getSAMPVehicleIDFromGTAVehicle(vehicle),
	//		g_Players->pLocalPlayer->inCarData.fPosition,
	//		g_Players->pLocalPlayer->inCarData.fVehicleHealth,
	//		g_Players->pLocalPlayer->inCarData.fMoveSpeed,
	//		g_Players->pLocalPlayer->inCarData.sKeys,
	//		iAracID);
	//	if (set.CarCheats.Information_About_My_Sync)
	//		cheat_state_text("Information:You are using Trailer Sync");
	//	g_RakClient->SendFakeTrailerData(iAracID,
	//		fPosition,
	//		vehicle->hitpoints,
	//		fMoveSpeed);
	//	/*memset(&TrailerSync, 0, sizeof(stTrailerData));
	//	TrailerSync.sTrailerID = iAracID;
	//	if (set.CarCheats.Information_About_My_Sync)
	//	cheat_state_text("Information:You are using Trailer Sync");
	//	vect3_copy(fPosition, TrailerSync.fPosition);
	//	vect3_copy(fMoveSpeed, TrailerSync.fMoveSpeed);
	//	bsData.Write((BYTE)ID_TRAILER_SYNC);
	//	bsData.Write((PCHAR)&TrailerSync, sizeof(stTrailerData));
	//	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);*/
	//}
	//break;
	//case ID_SYNC_DATA_PASSENGER: // Passenger Type
	//{
	//	g_RakClient->SendFakePassengerSyncData(iAracID, fPosition, vehicle->hitpoints = 1000.0f, g_Players->pLocalPlayer->byteCurrentWeapon, 1, 0);
	//	if (set.CarCheats.Information_About_My_Sync)
	//		cheat_state_text("Information:You are using Passenger Sync");
	//}
	//break;
	//case ID_SYNC_DATA_IN_CAR_RPC:
	//{
	//	bsData4RPC.Write(iAracID);
	//	bsData4RPC.Write(0); // Seat ID... Passenger mi driver mý...
	//	g_RakClient->RPC(RPC_EnterVehicle, &bsData4RPC);
	//	memset(&inCar, 0, sizeof(stInCarData));
	//	inCar.sVehicleID = iAracID;
	//	inCar.fVehicleHealth = vehicle->hitpoints;//1000.0f;
	//	inCar.bytePlayerHealth = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->hitpoints;
	//	inCar.byteArmor = g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->armor;
	//	inCar.fQuaternion[3] = 1;
	//	vect3_copy(fPosition, inCar.fPosition);
	//	vect3_copy(fMoveSpeed, inCar.fMoveSpeed);
	//	if (set.CarCheats.Information_About_My_Sync)
	//		cheat_state_text("Information:You are using RPC Sync");
	//	bsData.Write((BYTE)ID_VEHICLE_SYNC);
	//	bsData.Write((PCHAR)&inCar, sizeof(stInCarData));
	//	g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	//	break;
	//}
	//default:
	//	cheat_state_text("Choose an Sync Type."); // Sync seçmezse...
	//	break;
	//}

}
