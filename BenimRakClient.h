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
#include "FRakNet\RakNetStatistics.h"
#include "FRakNet\PacketPriority.h"
#include "FRakNet\BitStream.h"
#include "FRakNet\RakClient.h"
#define RAKNET_MAX_PACKET	256

extern class MyRakClient *g_RakClient;

#pragma pack(push, 1)

struct Pack3t
{
	PlayerID playerId;
	unsigned int length;
	unsigned int bitSize;
	unsigned char* data;
	bool deleteData;
	PlayerIndex playerIndex;
};

struct RPCN0de
{
	uint8_t uniqueIdentifier;
	void(*staticFunctionPointer) (RPCParameters *rpcParms);
};

#pragma pack(pop)

class MyRakClientInterface
{
public:
	virtual ~MyRakClientInterface() {};
	virtual bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel = 0);
	virtual void InitializeSecurity(const char *privKeyP, const char *privKeyQ);
	virtual void SetPassword(const char *_password);
	virtual bool HasPassword(void) const;
	virtual bool Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	virtual bool Send(RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	virtual Packet* Receive(void);
	virtual void DeallocatePacket(Packet *packet);
	virtual void PingServer(void);
	virtual void PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections);
	virtual int GetAveragePing(void);
	virtual int GetLastPing(void) const;
	virtual int GetLowestPing(void) const;
	virtual int GetPlayerPing(const PlayerID playerId);
	virtual void StartOccasionalPing(void);
	virtual void StopOccasionalPing(void);
	virtual bool IsConnected(void) const;
	virtual unsigned int GetSynchronizedRandomInteger(void) const;
	virtual bool GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer);
	virtual bool DeleteCompressionLayer(bool inputLayer);
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms));
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer);
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID);
	virtual bool RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
	virtual bool RPC(int* uniqueID, RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
	virtual bool RPC_(int* uniqueID, RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID);
	virtual void SetTrackFrequencyTable(bool b);
	virtual bool GetSendFrequencyTable(unsigned int outputFrequencyTable[256]);
	virtual float GetCompressionRatio(void) const;
	virtual float GetDecompressionRatio(void) const;
	virtual void AttachPlugin(void *messageHandler);
	virtual void DetachPlugin(void *messageHandler);
	virtual RakNet::BitStream * GetStaticServerData(void);
	virtual void SetStaticServerData(const char *data, const int length);
	virtual RakNet::BitStream * GetStaticClientData(const PlayerID playerId);
	virtual void SetStaticClientData(const PlayerID playerId, const char *data, const int length);
	virtual void SendStaticClientDataToServer(void);
	virtual PlayerID GetServerID(void) const;
	virtual PlayerID GetPlayerID(void) const;
	virtual PlayerID GetInternalID(void) const;
	virtual const char* PlayerIDToDottedIP(const PlayerID playerId) const;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead);
	virtual void SetRouterInterface(void *routerInterface);
	virtual void RemoveRouterInterface(void *routerInterface);
	virtual void SetTimeoutTime(RakNetTime timeMS);
	virtual bool SetMTUSize(int size);
	virtual int GetMTUSize(void) const;
	virtual void AllowConnectionResponseIPMigration(bool allow);
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength);
	virtual RakNetStatisticsStruct * const GetStatistics(void);
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
	virtual bool IsNetworkSimulatorActive(void);
	virtual PlayerIndex GetPlayerIndex(void);
};

enum NetPatchType
{
	INCOMING_RPC,
	OUTCOMING_RPC,
	INCOMING_PACKET,
	OUTCOMING_PACKET,
};

struct stNetPatch
{
	const char *name;
	int hotkey;
	bool enabled;
	byte id;
	NetPatchType type;
};
typedef unsigned short PLAYERID;
class MyRakClient
{
public:
	MyRakClient(void *pRakClientInterface);
	bool RPC(int rpcId, RakNet::BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, char orderingChannel = 0, bool shiftTimestamp = false);
	bool Send(RakNet::BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = UNRELIABLE_SEQUENCED, char orderingChannel = 0);
	void SendDeath(uint16_t killerId, uint8_t reason);
	void SendGivenDamage(bool giveTake, int playerID, float fDamage, int iWeaponID, int iBodyPart);
	void RequestClass(int classId);
	void SendSCMEvent(int vehicleID, int eventId, int param1, int param2);
	void SendSpawn(void);
	void SendPickUp(int pickupId);

	//
	//						Bu yorum satýrýndan sonrasý bizim eklediðimiz fonksiyonlardýr.
	//
	
	void SendFakeDriverFullSyncData(struct stInCarData *picSync, int iUseCarPos);
	void SendFakeBulletData(uint16_t PlayerID, float Origin[3], float Target[3], float  Center[3], uint8_t WeaponID, BYTE type);
	void SendFakePassengerSyncData(WORD vehicleid, float fPos[3], float HealthCar, uint8_t WeaponID, int SeatID, WORD key);
	void SendUnoccupiedSyncData(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], int SeatID, float fRoll[3]);
	void SendFakeDriverSyncData(int iSAMPVehicleID, float fVehiclePos[3], float fVehicleHealth, float fMoveSpeed[3]);
	void SendLagToServer();
	void sendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp);
	void SendFakeUnoccupiedFullSyncData(struct stUnoccupiedData *punocSync);
	void SendBulletData();
	void SendEnterVehicleNotification(uint16_t VehicleID, BOOL bPassenger);
	void NotifyVehicleDeath(int VehicleID);
	void SendFakeOnfootFullSyncData(struct stOnFootData *pofSync);
	void SendFuckingTrailerData(WORD wTrailerID, float fPosition[3], float fRoll[3], float fDirection[3], float fMoveSpeed[3]);
	void SendGiveDamage(int iPlayerID, float fDamage, int iWeaponID, int iBodyPart);
	void SendFakeBulletFullSyncData(struct stBulletData *pBulletSync);
	void SendDamage(uint16_t uiPlayerID, float fDamageAmountToSend, int iWeaponID, int iBodyPart);
	//void SendFuckingTrailerData(WORD wTrailerID, float fPosition[3], float fRoll[3], float fDirection[3], float fMoveSpeed[3]);
	//void SendPlayerDamage(PLAYERID PlayerID, float fAmountDam, int iWeaponID, BYTE BodyPart);
	void SendFakeOnfootSyncData(float fPos[3], float fSpeed[3], float Health, float Armor, int AnimFlags, int AnimationID, float Quaternion[4]);
	void SendFakeUnoccupiedSyncData(uint16_t VehicleID, uint8_t SeatID, float Pos[3], float Speed[3], float Health, float spin[3], float roll[3]);
	void SendExitPlayerVehicle(USHORT VehicleID);
	void SendEnterPlayerVehicle(USHORT VehicleID, BYTE seat);
	/* Senkronizasyonlar için */
	void SendModifiedBulletData(uint16_t targetID, float fOrigin[3], float fTarget[3], float fCenter[3], BYTE bWeapID, BYTE bTypeOfHit);
	void SendUnoccupiedSyncData(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], int SeatID);
	void SendFakeTrailerData(WORD vehicleid, float fpos[3], float HealthCar, float Speed[3]);
	void SyncFakeEnterVehicle(WORD vehicleid, int  passid);
	void SendFakeDriverSyncData2(WORD vehicleid, float fPos[3], float HealthCar, float Speed[3], WORD key, WORD trailer);
	void GivePlayerWeapon(uint16_t playerid, BYTE weaponid, WORD ammo);
	void SendFakeNewOnfootSyncData(float fPos[3], float fSpeed[3], float Health, float Armor);
	void SendFullFakeUnoccupiedFuckingSyncData(uint16_t VehicleID, uint8_t SeatID, float fDirection[3], float Pos[3], float Speed[3], float Health, float spin[3], float roll[3]);
	void SendDamageVehicle(WORD vehicleID, DWORD panel, DWORD door, BYTE lights, BYTE tires);
	void SendFakeOnfootSyncData2(float fPos[3], float fSpeed[3], float Health, float Armor, int AnimFlags, int AnimationID, float Quaternion[4], int sKeys);
	MyRakClientInterface *GetInterface(void) { return pRakClient; };

private:
	MyRakClientInterface *pRakClient;
};