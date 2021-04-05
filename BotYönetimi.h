#include "main.h"
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
extern class CBotEntity* g_BotEntity;
struct stBotCheats
{

	int Target_PlayerID;
	bool bUseNearestTarget;
	int Target_Passenger_PlayerID;
	bool bUseFriendTarget;

};
class CBotEntity
{
public:
	void WriteOnFootSync(stOnFootData* bOnFoot);
	void WriteAimSync(stAimData* bAimData);
	void WriteUnoccupiedSync(stUnoccupiedData* unocData);
	void WriteBulletSync(stBulletData* bulletData);
	void SendFakeBulletData(uint16_t PlayerID, float Origin[3], float Target[3], float Center[3], uint8_t WeaponID, BYTE type);
	void SendFakeKick(uint16_t iClientID, uint16_t VehicleID, BOOL bPassenger);
private:

};
#endif