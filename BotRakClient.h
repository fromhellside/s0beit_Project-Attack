#include "main.h"
int NearestPlayer();

extern class CBotData *g_BotClient;
class CBotData
{
public: // Eriþilen kýsým.
	void SendFakeUnoccupiedSyncData(uint16_t iClientID,uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3]);
	void SendExitPlayerVehicle(uint16_t iClientID,USHORT VehicleID);
	void SendEnterPlayerVehicle(uint16_t iClientID, USHORT VehicleID, BYTE seat);
	void SendFakePassengerSyncData(uint16_t iClientID, WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key);
private: // Eriþilemeyen kýsým.

};