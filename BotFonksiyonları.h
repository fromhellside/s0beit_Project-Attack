#include "main.h"
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
//extern class CBotFeatures* g_BotFeatures;
extern class CBotFuncs *g_BotFuncs;
extern struct stBotCheats *BotCheats;
struct stBot
{
	RakClientInterface *pRakClient;
	RakPeer* pRakPeer;
	CBotData *pBotData;
	/*CBotFeatures *g_BotFeatures;*/
	char NickName[SAMP_MAX_PLAYER_NAME + 1];
	bool bConnected;
	bool bJoined;
	bool bSpawned;

	bool bIsInVehicle;
	uint16_t last_vehicleID;

	uint16_t playerID;
	unsigned int uiChallenge;

	float fLastOnFootPos[3];
	float fLastOnFootQuat[4];
	short sCurrentAnimationID;
	uint8_t byteSpecialAction;

	DWORD dwSendBulletTick;

	float fHealth;
	float fArmour;
	

	stBot()
	{
		fHealth = 100.0f;
	}
};

struct stBotSettings
{
	//int ClientCount;
	//int CurrentClientID;
	//bool bUIF_DM_Farmer;

	//---- Geliþmiþ Ayarlar - Advanced Settings ----//
	int iBotWeaponID;
	bool bCopyHealth;
	bool bCopyArmor;
	bool bCopyWeapon;
	bool bCopyChat;
	bool bCopyRPC;
	bool bCopyUnocData;
	//bool bDo_Not_Spin; // Mevlanayla ilgili bir ayar bu.
	//---- Geliþmiþ Ayarlar SON - Advanced Settings ----//
	int ClientCount;
	DWORD UpdateSendRate;

	uint8_t CurrentClientID;
	uint8_t ClientJoined;
	bool bRemovePlayerCrasher;
	bool bZombieConnection;
 
	bool bPMFlooder;
	bool bDiscoMode;
	bool bInvalidFPSCrasher;
	bool bBotKiller;

	bool bConnectAsNPC; // R.I.P SA-MP
	bool bRollCrasher; // BOT ROLL!!!!!!!!!!!! - 23.03.2019 20:50
	bool bRandAnim;
	bool bClassFlooder;
	bool bBotSuck;// let's sux players dick xD - RapidFirererererelolol
	bool bTornado;
	bool bTornado2;
	bool bUpsideDown;
	bool bRandomQuaternions; 
	bool bTwistMode;
	bool bSpinBot;

	bool bChatFlooder;

	bool bUseAdjustableNick;
	bool bUseAdjustableTag;

	bool bKickBotsByTimeout; // 12.04.2019 11:11
	bool bDeleteBotsByKick; // 12.04.2019 14:36

	bool bReceiveRPC;
	bool UseFakeBot; // Fake Bot
	int ClassID;
	float fTakenDamage;
	bool bFollow;
	float fDistanceFollow;
	float fDistanceFollowBetweenBots;
	float m_fCircleAngle;
	float fCircleRadius;
	bool bShooter;

	bool bStorm;
	bool bUseNearestTarget;
	bool bBotAttacker;
	short sTargetID;
	uint8_t uiAttackWeaponID;
	bool bBotCircle;
	bool bBotElevator;
	bool bBotJetpackElevator;
	bool bBotPick;
	bool bBotSlapper;
	bool bBotPlayerBlocker; // By me.
	bool bBotFuck;
	bool bBotFollowAnim;
	short sBotFollowAnimID;
	
	bool bBotSun;
	bool bBotInvalidAimZ;
	bool bBotShakingCamera;
	bool bBotShakingCamera2;


	//temp 
	bool bBotSilent;
	float fMultiplierSilent;
	float fSelfPos[3];
	float fSelfSpeed[3];

	short sTwistModeRunDelay; // 0 - 750 ms arasý
	short byteTwistModeWeaponID; // 0 - 46 arasý
	//bool bStorm;
};

class CBotFuncs
{
public:

	CBotFuncs();

	~CBotFuncs();
	uint16_t Client_in_Queue;
	uint16_t N_Client_to_Add_In_Queue;
	uint16_t uiIsBot[SAMP_MAX_PLAYERS][2];

	stBotSettings BotSettings;
	/*uhmm maybe is better
	to use the vector*/
	stBot BotClient[256];
	void OL_Bot_Send_Command(uint8_t uiClientID, const char *szMessage, ...);
	void BotRemovePlayerCrasher();
 
	void OL_Bot_PMFlooder(uint8_t uiClientID); // uiClientID = Bu iþi yapacak olan fake botlarýn ID'si.
	void BotInvalidFPSCrasher(uint16_t uiClientID);
	void BotPlayerCrashers(uint16_t uiClientID);
	void BotDiscoMode();
	void BotKiller();

	void BotRollCrasher();
	void OL_Bot_Say(int iBotID, const char *szMessage, ...);
	
	void Bot_Tornado();
	void Bot_Tornado2();
	void ClassFlooder();

	void OL_Bot_ChatFlooder(uint8_t uiClientID);
	void Bot_Suck();
	void OL_Send_Death(uint16_t iClientID, uint16_t KillerID, uint16_t WeaponID);
	void Bot_Invalid_Aim_Z(uint8_t iClientID);
	void Bot_Shaking_Camera(uint8_t iClientID);

	void OL_Add_Bot_Queue();
	bool OL_Add_Bot();
	bool OL_Add_Bot_Nick(char *nick);
	void OL_Delete_Bot();
	void OL_Spawn_Bot(uint8_t ClientID);
	void OL_Random_Spawn_Bot(uint8_t ClientID);
	//void OL_Bot_Die();
	void OL_Bot_Process();
	//RPC
	bool OL_Bot_SendRPC(uint8_t ClientID, int iRPCID, RakNet::BitStream Params, PacketPriority Priority, PacketReliability Reliability, char OrderingChannel, bool ShiftTimestamp);
	//void OL_Bot_ReceiveRPC(RakClientInterface ** pRakClient);


private:
	//RPC



	void OL_Packet_ConnectionAccepted(Packet *packet, uint8_t ClientID);
	void OL_Packet_Auth_Key(Packet *packet, uint8_t ClientID);
	void OL_Packet_AimSync(Packet *packet, uint8_t ClientID);
	void OL_Packet_UnoccupiedSync(Packet* packet, uint8_t ClientID);
	void OL_Packet_BulletSync(Packet *packet, uint8_t ClientID);
	void OL_Packet_PlayerSync(Packet *packet, uint8_t ClientID);

	void OL_Bot_Follow();
	void OL_Bot_Follow_OnFoot(bool bFake);
	void OL_Bot_Follow_Passenger(bool bFake);
	void OL_Bot_Silent();
	void OL_Bot_Shooter();
	void OL_Bot_Circle();
	void OL_Bot_Attacker();
	void OL_Bot_Elevator();
	void OL_Bot_Slapper();
	void OL_Bot_Fuck();
	void OL_Bot_PlayerBlocker();
	void OL_Bot_Pick();
	void OL_Bot_Follow_Anim();
	void OL_Bot_Sun();
	//void OL_UIF_DM_Farmer();
	//void OL_Bot_Door_Storm();
	void OL_Bot_Storm();

	/*Ýstersen Aim,OnFoot ve Passenger olan þeylere ilave InCar ve Trailer'de yapabilirsin. :/ :((( */
	void OL_Bot_Send_Aim(bool bCopyFakePlayerVariables);
	void OL_Bot_Send_OnFoot(const float *fPos, const float *fSpeed, bool bFake, uint16_t sSurfingVehicleID = 0, float *fSurfPos = nullptr);
	void OL_Bot_Send_Passenger(bool bFake);
	

};

void OL_Bot_SetHealth(RPCParameters *params);
void OL_Bot_SetArmour(RPCParameters *params);
#endif