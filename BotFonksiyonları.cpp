#include "main.h"
#include "FRakNet/RakClient.h"
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
CBotFuncs *g_BotFuncs = new CBotFuncs();
#define BOT_CRASHER_TYPE_OFF 0 // Off
#define BOT_CRASHER_TYPE_DETONATOR 1 // byteCamMode 45 & byteCurrentWeapon 40 -> Sunucu Spawn isteði gönder RPC_Spawn
#define BOT_CRASHER_TYPE_BULLETS 2 // Invalid Bullets -> High fTurnSpeed -> Aþýrý yüksek deðerlerde fTurnSpeed verisi.
#define BOT_CRASHER_TYPE_POSITION 3 // Passenger Crasher -> High Position -> Aþýrý yüksek deðerlerde fPosition verisi.
#define BOT_CRASHER_TYPE_ROLL 4 // Roll Crasher -> High Roll -> Aþýrý yüksek deðerlerde fRoll verisi.
#define BOT_CRASHER_TYPE_NEGATIVE_BULLETS 5 // Invalid Bullets #2 -> Low fTurnSpeed -> Ciddi anlamda negatif döndürme hýzý
#define BOT_CRASHER_TYPE_TUNING	6 // Tuning Crasher -> Car Modification -> Araç Modifikasyonlarý
#define BOT_CRASHER_TYPE_LOWROLL 7 // Roll Crasher #2 -> Low Roll[Dangerous Exploit] -> Çok Tehlikeli Exploit
//Ba
//#define list_get_entry_data(entry)\
//((void*)((char*)(entry)+sizeof(struct list_entry)))
CBotFuncs::CBotFuncs()
{
	
	memset(&BotClient, 0, sizeof(stBot));
	memset(&BotSettings, 0, sizeof(stBotSettings));
	memset(uiIsBot, 0, sizeof(uiIsBot));
	BotSettings.UpdateSendRate = 5;
	N_Client_to_Add_In_Queue = 5;
	Client_in_Queue = 0;
	BotSettings.fDistanceFollow = -0.8f;
	BotSettings.fDistanceFollowBetweenBots = 0.8f;
	BotSettings.fMultiplierSilent = 9.0f;
	//BotSettings.bCopyHealth = true;
	//BotSettings.bCopyArmor = true;
	BotSettings.bCopyWeapon = true;
	BotSettings.sTargetID = -1;
	BotSettings.uiAttackWeaponID = 27;
	BotSettings.CurrentClientID = 0;
	BotSettings.bUseNearestTarget = true;
	BotSettings.sBotFollowAnimID = 881;
	/*BotSettings.sTwistModeRunDelay = 0;
	BotSettings.byteTwistModeWeaponID = 46;*/
}

void CBotFuncs::OL_Add_Bot_Queue()
{
	traceLastFunc("OL_Add_Bot_Queue()");
	if (BotClient == nullptr || g_SAMP == nullptr || g_Players == nullptr)
		return;

	if (BotSettings.ClientCount != NULL)
	{
		if (!BotClient[BotSettings.ClientCount - 1].bJoined)
		{
			Client_in_Queue++;
		}
		else
		{
			OL_Add_Bot();
		}
	}
	else
	{
		OL_Add_Bot();
	}
}

void CBotFuncs::OL_Delete_Bot()
{
	if (BotClient == nullptr || g_SAMP == nullptr || g_Players == nullptr)
		return;
	if (BotSettings.ClientCount <= 0 || BotSettings.ClientJoined == 0)
	{
		BotSettings.ClientCount = 0;
		BotSettings.ClientJoined = 0;
		BotSettings.CurrentClientID = 0;
		cheat_state_text("All bots are deleted from server.");
		return;
	}//sec bug team
	if (g_BotFuncs->BotSettings.bKickBotsByTimeout)
		BotClient[BotSettings.ClientCount - 1].pRakClient->Disconnect(0);
	else if (g_BotFuncs->BotSettings.bDeleteBotsByKick)
		g_BotEntity->SendFakeKick(BotSettings.ClientCount, 0xFFFF, false);
	else
		BotClient[BotSettings.ClientCount - 1].pRakClient->Disconnect(1);
	RakNetworkFactory::DestroyRakClientInterface(BotClient[BotSettings.ClientCount - 1].pRakClient);
	uiIsBot[BotClient[BotSettings.ClientCount - 1].playerID][0] = 0;
	memset(&BotClient[BotSettings.ClientCount - 1], 0, sizeof(stBot));
	//BotClient[BotSettings.ClientCount - 1].bConnected = 0;
	//BotClient[BotSettings.ClientCount - 1].bJoined = 0;
	//BotClient[BotSettings.ClientCount - 1].pRakClient = 0;
	//BotClient[BotSettings.ClientCount - 1].playerID = 0;
	//BotClient[BotSettings.ClientCount - 1].uiChallenge = 0;
	BotSettings.ClientCount--;
	BotSettings.ClientJoined--;
	BotSettings.CurrentClientID = 0;
}

bool CBotFuncs::OL_Add_Bot_Nick(char *nick)
{
	traceLastFunc("RAKNETB0T_Add_Bot()");
	if (BotClient == nullptr || g_SAMP == nullptr || g_Players == nullptr)
		return false;
	sprintf(BotClient[BotSettings.ClientCount].NickName, nick);

	BotClient[BotSettings.ClientCount].pRakClient =
		RakNetworkFactory::GetRakClientInterface();

	if (BotClient[BotSettings.ClientCount].pRakClient == nullptr)
	{
		cheat_state_text("Project Attack: There is a problem about RakNet Pointer.");
		//Log("Problem With RakNet ptr");
		return false;
	}
	if (!BotClient[BotSettings.ClientCount].pRakClient->Connect(g_SAMP->szIP,
		g_SAMP->ulPort,
		0, 0, 0))
	{
		cheat_state_text("Project Attack: RakClient can not connect to server.");
		//Log("Bot Client can't connect");
		return false;
	}
	cheat_state_text("Connection Request has sent... -> Client ID Number: %d",
		BotSettings.ClientCount);
	BotClient[BotSettings.ClientCount].bConnected = true;
	BotSettings.ClientCount++;
	BotSettings.CurrentClientID = 0;
	return true;
}

bool CBotFuncs::OL_Add_Bot()
{
	traceLastFunc("RAKNETB0T_Add_Bot()");
	if (BotClient == nullptr || g_SAMP == nullptr || g_Players == nullptr)
		return false;
	if (BotSettings.UseFakeBot)
	{
		sprintf(BotClient[BotSettings.ClientCount].NickName, "%s_%d",
			getPlayerName(BotCheats->Target_PlayerID),
			BotSettings.ClientCount);

	}
	else
	{
		/*char *szName = new char[SAMP_MAX_PLAYER_NAME + 1];*/
		*BotClient[BotSettings.ClientCount].NickName = 0; // clear string
	
		if (g_BotFuncs->BotSettings.bUseAdjustableNick)
		{
			//Log("0");
			if (g_BotFuncs->BotSettings.bUseAdjustableTag)
			{
				//Log("1");
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "[%s]", set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName);
				//Log("2");
			}
				strncat(BotClient[BotSettings.ClientCount].NickName, set.Bots.RAKNET_BOT_AdjustableNick, SAMP_MAX_PLAYER_NAME);
			//Log("4");
			if(set.Bots.RAKNET_BOT_use_Random_Numbers == true && set.Bots.RAKNET_BOT_use_Split_For_NickName == true) // Eðer ikiside açýksa.
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s%s%d", BotClient[BotSettings.ClientCount].NickName, set.Bots.RAKNET_BOT_NickName_Split, rand());
			else if (set.Bots.RAKNET_BOT_use_Random_Numbers == true)
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s_%d", BotClient[BotSettings.ClientCount].NickName, rand());
			else if (set.Bots.RAKNET_BOT_use_Bot_Count == true && set.Bots.RAKNET_BOT_use_Split_For_NickName == true)
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s%s%d", BotClient[BotSettings.ClientCount].NickName, set.Bots.RAKNET_BOT_NickName_Split, BotSettings.ClientCount);
			else if(set.Bots.RAKNET_BOT_use_Bot_Count == true)
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s_%d", BotClient[BotSettings.ClientCount].NickName, BotSettings.ClientCount);
		}
		else
		{
			if(set.Bots.RAKNET_BOT_use_Split_For_NickName == true)
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s%s%d", getPlayerName(g_Players->sLocalPlayerID), set.Bots.RAKNET_BOT_NickName_Split, BotSettings.ClientCount);
			else
				snprintf(BotClient[BotSettings.ClientCount].NickName, SAMP_MAX_PLAYER_NAME, "%s_%d", getPlayerName(g_Players->sLocalPlayerID), BotSettings.ClientCount);
		}

		if (set.Bots.RAKNET_BOT_use_Random_Numbers == true)
			set.Bots.RAKNET_BOT_use_Bot_Count = false;
		if (set.Bots.RAKNET_BOT_use_Bot_Count == true)
			set.Bots.RAKNET_BOT_use_Random_Numbers = false;
	}
	BotClient[BotSettings.ClientCount].pRakClient = RakNetworkFactory::GetRakClientInterface();
	if (BotClient[BotSettings.ClientCount].pRakClient == nullptr)
	{
		cheat_state_text("There is a problem about RakNet Pointer.");
		//Log("Problem With RakNet ptr");
		return false;
	}
	if (!BotClient[BotSettings.ClientCount].pRakClient->Connect(g_SAMP->szIP,
		g_SAMP->ulPort,
		0, 0, 0))
	{
		cheat_state_text("Project Attack: B0T RakClient can't connect to server.");
		//Log("Bot Client can't connect");
		return false;
	}
	cheat_state_text("Connection Request has sent... -> Client ID: %d",
		BotSettings.ClientCount);
	BotClient[BotSettings.ClientCount].bConnected = true;
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth = 100.0f;
	BotSettings.ClientCount++;
	BotSettings.CurrentClientID = 0;
	return true;
}

void CBotFuncs::OL_Bot_Process()
{
	traceLastFunc("RAKNETB0T_Process()");
	if (!BotClient)		// || g_SAMP == nullptr || g_Players == nullptr)
		return;
	traceLastFunc("RAKNETB0T_Process() 2");
	//return;
	if (Client_in_Queue >= 1)
	{
		if (BotSettings.ClientCount == NULL)
		{
			Client_in_Queue--;
			OL_Add_Bot();
		}
		else if (BotClient[BotSettings.ClientCount - 1].bJoined)
		{
			Client_in_Queue--;
			OL_Add_Bot();
		}
	}
	uint8_t ClientID = BotSettings.CurrentClientID;
	traceLastFunc("RAKNETB0T_Process() 3");
	if (BotClient[ClientID].bConnected == false
		|| BotClient[ClientID].pRakClient == nullptr)
		return;
	//OL_Bot_ReceiveRPC(&BotClient[ClientID].pRakClient);

	static DWORD dwUpdateTick = GetTickCount();

	if (GetTickCount() - dwUpdateTick >= BotSettings.UpdateSendRate)
	{

		traceLastFunc("RAKNETB0T_Process() 4");
		Packet *packet;
		unsigned char packetID;
		traceLastFunc("RAKNETB0T_Process() 5");
		for (packet = BotClient[ClientID].pRakClient->Receive();
			packet;
			BotClient[ClientID].pRakClient->DeallocatePacket(packet),
			packet = BotClient[ClientID].pRakClient->Receive())
		{
		
			if ((unsigned char)packet->data[0] == ID_TIMESTAMP)
			{
				if (packet->length > sizeof(unsigned char) + sizeof(unsigned int))
					packetID =
					(unsigned char)packet->data[sizeof(unsigned char) +
					sizeof(unsigned int)];
				else
				{
					continue;
				}
				//return;
			}
			else
				packetID = (unsigned char)packet->data[0];
			//cheat_state_text("Packet ID: %d", packetID);
			switch (packetID)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				cheat_state_text("Server closed the connection. Client ID: %d.",
					ClientID);
				Log("Server closed the connection. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_CONNECTION_BANNED:
				cheat_state_text("You are banned from this server. Client ID: %d.",
					ClientID);
				Log("You are banned from this server. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_CONNECTION_ATTEMPT_FAILED:
				cheat_state_text("Connection attempt failed. Client ID: %d.",
					ClientID);
				Log("Connection attempt failed. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				cheat_state_text("Server is Full. Client ID: %d.", ClientID);
				Log("Server Full. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_INVALID_PASSWORD:
				cheat_state_text("Password is wrong. Client ID: %d.",
					ClientID);
				Log("Password is wrong. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_CONNECTION_LOST:
				cheat_state_text("Server lost connection. Client ID: %d.",
					ClientID);
				Log("Server lost connection. Client ID: %d.", ClientID);
				for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
					g_BotFuncs->OL_Delete_Bot();
				goto exit_loop;
				break;
			case ID_AUTH_KEY:
				OL_Packet_Auth_Key(packet, ClientID);
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				OL_Packet_ConnectionAccepted(packet, ClientID);
				break;
			case ID_AIM_SYNC:
				if (BotSettings.bFollow)
					OL_Packet_AimSync(packet, ClientID);
				break;
			case ID_UNOCCUPIED_SYNC:
				if (BotSettings.bFollow || BotSettings.bCopyUnocData)
					OL_Packet_UnoccupiedSync(packet, ClientID);
				break;
			case ID_BULLET_SYNC:
				if (BotSettings.bFollow)
					OL_Packet_BulletSync(packet, ClientID);
				break;
				//case ID_MARKERS_SYNC:
				//      OL_Packet_MarkersSync(packet, ClientID);
				//      break;
				//
			case ID_PLAYER_SYNC:
				OL_Packet_PlayerSync(packet, ClientID);
				break;
			}
		}

		if (g_BotFuncs->BotClient[ClientID].bJoined)
		{
			if (g_BotFuncs->BotSettings.bUseNearestTarget)
				g_BotFuncs->BotSettings.sTargetID = NearestPlayer();

			if (g_BotFuncs->BotSettings.bFollow)
				g_BotFuncs->OL_Bot_Follow();

			if (g_BotFuncs->BotSettings.bShooter)
				g_BotFuncs->OL_Bot_Shooter();



			if (g_BotFuncs->BotSettings.bBotCircle)
				g_BotFuncs->OL_Bot_Circle();

			if (g_BotFuncs->BotSettings.bBotSilent)
				g_BotFuncs->OL_Bot_Silent();

			if (g_BotFuncs->BotSettings.bBotAttacker)
				g_BotFuncs->OL_Bot_Attacker();

			if (g_BotFuncs->BotSettings.bBotElevator || g_BotFuncs->BotSettings.bBotJetpackElevator)
				g_BotFuncs->OL_Bot_Elevator();

			if (g_BotFuncs->BotSettings.bBotSlapper)
				g_BotFuncs->OL_Bot_Slapper();

			if (g_BotFuncs->BotSettings.bBotFuck)
				g_BotFuncs->OL_Bot_Fuck();

			if (g_BotFuncs->BotSettings.bBotSuck)
				g_BotFuncs->Bot_Suck();

			if (g_BotFuncs->BotSettings.bBotPlayerBlocker)
				g_BotFuncs->OL_Bot_PlayerBlocker();

			if (g_BotFuncs->BotSettings.bBotPick)
				g_BotFuncs->OL_Bot_Pick();

			if (g_BotFuncs->BotSettings.bBotFollowAnim)
				g_BotFuncs->OL_Bot_Follow_Anim();

			if (g_BotFuncs->BotSettings.bRemovePlayerCrasher)
				g_BotFuncs->BotRemovePlayerCrasher();

 
			if(g_BotFuncs->BotSettings.bBotKiller)
				g_BotFuncs->BotKiller();

			if (g_BotFuncs->BotSettings.bPMFlooder)
				g_BotFuncs->OL_Bot_PMFlooder(ClientID);
				
			if (g_BotFuncs->BotSettings.bInvalidFPSCrasher)
				g_BotFuncs->BotInvalidFPSCrasher(ClientID);

			if (g_BotFuncs->BotSettings.bDiscoMode)
				g_BotFuncs->BotDiscoMode();

			if (set.Bots.BotCrasherType)
				g_BotFuncs->BotPlayerCrashers(ClientID);

		/*	if (g_BotFuncs->BotSettings.bZombieConnection)
				g_BotEntity->ZombieConnection(ClientID);*/

			if (g_BotFuncs->BotSettings.bRollCrasher)
				g_BotFuncs->BotRollCrasher();

			if (g_BotFuncs->BotSettings.bClassFlooder)
				g_BotFuncs->ClassFlooder();

			if(g_BotFuncs->BotSettings.bTornado)
				g_BotFuncs->Bot_Tornado();

			if (g_BotFuncs->BotSettings.bTornado2)
				g_BotFuncs->Bot_Tornado2();

			if (g_BotFuncs->BotSettings.bChatFlooder)
				g_BotFuncs->OL_Bot_ChatFlooder(ClientID);

			if (g_BotFuncs->BotSettings.bBotSun)
				g_BotFuncs->OL_Bot_Sun();

			if (g_BotFuncs->BotSettings.bStorm)
				g_BotFuncs->OL_Bot_Storm();
		}
		BotSettings.CurrentClientID++; // current bot id what is being processed
		dwUpdateTick = GetTickCount();
	}
exit_loop:;
	if (BotSettings.CurrentClientID >= BotSettings.ClientCount)
	{
		BotSettings.CurrentClientID = 0;
	}

}
void CBotFuncs::OL_Bot_Circle()
{
	float *coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	//float pos[3] = { coord[0] + sinf(-m_fDaireMesafesi) * radius, coord[1] + cosf(-m_fDaireMesafesi) * radius, coord[2] + 1 };
	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	float fPozisyon[3]; 
	struct actor_info* mylocalactor = actor_info_get(ACTOR_SELF, NULL);
	if (g_BotFuncs->BotSettings.bCopyHealth)
		OnFootData.byteHealth = mylocalactor->hitpoints;
	else
		OnFootData.byteHealth = 1;

	if (g_BotFuncs->BotSettings.bCopyArmor)
		OnFootData.byteHealth = mylocalactor->hitpoints;
	else
		OnFootData.byteArmor = 0;
	
	if (KEY_DOWN(VK_LBUTTON))
	{
		OnFootData.sCurrentAnimationID = 301;
		vect3_copy(OnFootData.fPosition, fPozisyon);
		static int x = 0;
		fPozisyon[0] += coord[0] + sinf(19.0f * (float)x) * 25.0f;
		fPozisyon[1] += coord[1] + cosf(19.0f * (float)x) * 25.0f;
		fPozisyon[2] += coord[2] + 3.0f;
		OnFootData.fPosition[0] += fPozisyon[0];
		OnFootData.fPosition[1] += fPozisyon[1];
		OnFootData.fPosition[2] += fPozisyon[2];
		x++;
	}
	else if (KEY_DOWN(VK_RBUTTON))
	{
		//float fPozisyonOne[3]; //
		float fPozisyonDouble[3]; // Bu deðiþken, Ondalýklý sayýlarý saklamak içindir bu sonundaki Double ise, Ýkinci bir daire oluþturmak için.
		//vect3_copy(OnFootData.fPosition, fPozisyonOne);
		vect3_copy(OnFootData.fPosition, fPozisyonDouble);
		static int x2 = 0;
		//fPozisyonOne[0] += sinf(19.0f * (float)x2) * 25.0f;
		//fPozisyonOne[1] += cosf(19.0f * (float)x2) * 25.0f;
		//fPozisyonOne[2] += 35.0f;

		fPozisyonDouble[0] += coord[0] + sinf(35.0f * (float)x2) * 40.0f;
		fPozisyonDouble[1] += coord[1] + cosf(35.0f * (float)x2) * 40.0f;
		fPozisyonDouble[2] += coord[2] + 3.0f;
		
		OnFootData.fPosition[0] += fPozisyonDouble[0];
		OnFootData.fPosition[1] += fPozisyonDouble[1];
		OnFootData.fPosition[2] += fPozisyonDouble[2];
		x2++;
	}
	else
	{
		OnFootData.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
		OnFootData.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
		OnFootData.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2] + 3.0f;
	}
	RakNet::BitStream bsSendData;
	bsSendData.Write((BYTE)ID_PLAYER_SYNC);
	bsSendData.Write((PCHAR)&OnFootData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsSendData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	BotSettings.m_fCircleAngle += 3.1415 / BotSettings.CurrentClientID;//10;
	if (BotSettings.m_fCircleAngle >= 2 * 3.1415) BotSettings.m_fCircleAngle = 0;
}

void OL_Bot_SetHealth(RPCParameters * params)
{
	RakNet::BitStream bsData(params->input, params->numberOfBitsOfData / 8, false);
	bsData.Read(g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].
		fHealth);
}

void OL_Bot_SetArmour(RPCParameters * params)
{
	RakNet::BitStream bsData(params->input, params->numberOfBitsOfData / 8, false);
	bsData.Read(g_BotFuncs->BotClient[g_BotFuncs->BotSettings.CurrentClientID].
		fArmour);
}


void CBotFuncs::OL_Bot_Sun()
{
	float fPos[3], fSpeed[3];
	static float Angle = 0;
	vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12], fPos);
	fPos[2] += 5.0f;
	float AbsSpeed = 50.0f;

	fSpeed[0] = AbsSpeed * cos(Angle);
	fSpeed[1] = AbsSpeed * sin(Angle);

	Angle += DEGTORAD(115);

	OL_Bot_Send_OnFoot(fPos, fSpeed, false);
}
void CBotFuncs::Bot_Invalid_Aim_Z(uint8_t iClientID)
{
	stAimData aimData;
	memset(&aimData, 0, sizeof(stAimData));
	aimData.fAimZ = sqrt((float)-1);
	RakNet::BitStream bsAim;
	bsAim.Write((BYTE)ID_AIM_SYNC);
	bsAim.Write((PCHAR)& aimData, sizeof(stAimData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsAim,
		HIGH_PRIORITY,
		UNRELIABLE_SEQUENCED,
		0);
}
void CBotFuncs::Bot_Shaking_Camera(uint8_t iClientID)
{
	stAimData aimData;
	memset(&aimData, 0, sizeof(stAimData));
	aimData.byteCamMode = 45;
	RakNet::BitStream bsAim;
	bsAim.Write((BYTE)ID_AIM_SYNC);
	bsAim.Write((PCHAR)& aimData, sizeof(stAimData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsAim,
		HIGH_PRIORITY,
		UNRELIABLE_SEQUENCED,
		0);
}
void CBotFuncs::Bot_Suck()
{
	short playerid = BotSettings.sTargetID;
	if (IsPlayerStreamed(playerid)) // if Player is streamed.. so if i can see him.
	{
		stOnFootData onFootData;
		memset(&onFootData, 0, sizeof(stOnFootData));
		onFootData.byteHealth = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
		onFootData.byteArmor = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
		// First of all, Get position!!! - RapidFire
		vect3_copy(&g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], onFootData.fPosition);
		vect3_copy(g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed, onFootData.fMoveSpeed);
		/*GetPlayerQuaternion(playerid, onFootData.fQuaternion);*/
		onFootData.fQuaternion[0] = g_Players->pRemotePlayer[playerid]->pPlayerData->onFootData.fQuaternion[0] + -0.7f;
		onFootData.fPosition[0] += -g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[4] * -0.2f;
		onFootData.fPosition[1] += -g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[5] * -0.2f;
		
		onFootData.fPosition[2] += -g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6] * -0.2f;
		onFootData.fPosition[2] += -g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6] * -0.2f;

		onFootData.fPosition[0] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[4] * -0.2f;
		onFootData.fPosition[1] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[5] * -0.2f;
		onFootData.fPosition[2] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6] * -0.2f;
		onFootData.sCurrentAnimationID = 1666;
		onFootData.sAnimFlags = 4356;
		onFootData.byteSpecialAction = 1;
		onFootData.fMoveSpeed[2] = -0.01f;
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& onFootData, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}

void CBotFuncs::OL_Bot_Fuck()
{
	short playerID = BotSettings.sTargetID;
	//      float fQuaternion[4];
	if (IsPlayerStreamed(playerID))
	{
		stOnFootData OnFoot;
		memset(&OnFoot, 0, sizeof(stOnFootData));
		OnFoot.byteHealth = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
		OnFoot.byteArmor = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
		vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
			OnFoot.fPosition);
		vect3_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed,
			OnFoot.fMoveSpeed);

		GetPlayerQuaternion(playerID, OnFoot.fQuaternion);
		OnFoot.fPosition[0] += -g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[4] * 0.3f;
		OnFoot.fPosition[1] += -g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[5] * 0.3f;

		OnFoot.fPosition[2] += -g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6] * 0.3f;
		OnFoot.fPosition[2] += -g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6] * 0.3f;

		OnFoot.fPosition[0] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[4]
			* 0.3f;

		OnFoot.fPosition[1] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[5]
			* 0.3f;
		OnFoot.fPosition[2] -= (float)BotSettings.CurrentClientID * g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTAEntity->base.matrix[6]
			* 0.3f;
		OnFoot.sCurrentAnimationID = 1666;
		OnFoot.sAnimFlags = 4356;
		OnFoot.byteSpecialAction = 3;
		OnFoot.fMoveSpeed[2] = -0.01f;
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFoot, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}
void CBotFuncs::OL_Bot_PlayerBlocker() // By RapiddddddFire so DarkNeX!! xD
{
	short sPlayerID = BotSettings.sTargetID;
	float fRota;
	if (IsPlayerStreamed(sPlayerID))
	{
		struct actor_info *ainfo = actor_info_get(ACTOR_SELF, NULL);
		stOnFootData onFoot;
		memset(&onFoot, 0, sizeof(stOnFootData));
		onFoot.byteCurrentWeapon = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->onFootData.byteCurrentWeapon;
		onFoot.byteHealth = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->onFootData.byteHealth;
		//cheat_state_text("1");
		vect3_copy(&g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
			onFoot.fPosition);

		vect3_copy(g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed,
			onFoot.fMoveSpeed);
		fRota = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->pSAMP_Actor->pGTAEntity->fCurrentRotation;
		onFoot.fPosition[0] = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->onFootData.fPosition[0]; // X Axis.
		onFoot.fPosition[1] = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->onFootData.fPosition[1];	// Y Axis.
		onFoot.fPosition[2] = g_Players->pRemotePlayer[sPlayerID]->pPlayerData->onFootData.fPosition[2];	// Z Axis.
		/*onFoot.fMoveSpeed[2] = -0.01f;*/

		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)&onFoot, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}
void CBotFuncs::OL_Bot_Follow_Anim()
{
	short playerID = BotSettings.sTargetID;
	if (IsPlayerStreamed(playerID))
	{
		stOnFootData OnFoot;
		memset(&OnFoot, 0, sizeof(stOnFootData));
		OnFoot.byteHealth =
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
		OnFoot.byteArmor =
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
		vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->base.matrix[12], OnFoot.fPosition);
		vect3_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->speed, OnFoot.fMoveSpeed);
		//vect4_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.fQuaternion, OnFoot.fQuaternion);
		GetPlayerQuaternion(playerID, OnFoot.fQuaternion);
		OnFoot.fPosition[0] +=
			-g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[4] * 0.3f;
		OnFoot.fPosition[1] +=
			-g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[5] * 0.3f;
		OnFoot.fPosition[2] +=
			-g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[6] * 0.3f;
		OnFoot.fPosition[0] -=
			(float)BotSettings.CurrentClientID *
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[4] * 0.3f;
		OnFoot.fPosition[1] -=
			(float)BotSettings.CurrentClientID *
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[5] * 0.3f;
		OnFoot.fPosition[2] -=
			(float)BotSettings.CurrentClientID *
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->base.matrix[6] * 0.3f;
		OnFoot.sCurrentAnimationID = BotSettings.sBotFollowAnimID;
		OnFoot.sAnimFlags = 4356;
		OnFoot.byteSpecialAction = 3;
		OnFoot.fMoveSpeed[2] = -0.01f;
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFoot, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}

void CBotFuncs::OL_Bot_Storm()
{
	float fRange = 400.0f;
	float fSpeed = 99.0f;
	stOnFootData OnFoot;
	memset(&OnFoot, 0, sizeof(stOnFootData));
	OnFoot.byteHealth = BotClient[BotSettings.CurrentClientID].fHealth;
	vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.
		matrix[12], OnFoot.fPosition);
	OnFoot.fPosition[0] +=
		(fRange / 2.f) - (float)rand() / (float)(RAND_MAX / fRange);
	OnFoot.fPosition[1] +=
		(fRange / 2.f) - (float)rand() / (float)(RAND_MAX / fRange);
	OnFoot.fMoveSpeed[0] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fMoveSpeed[1] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fMoveSpeed[2] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fQuaternion[0] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[1] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[2] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[3] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.sCurrentAnimationID = rand() % 2000;
	OnFoot.sAnimFlags = 4356;
	RakNet::BitStream bsOnFoot;
	bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFoot.Write((PCHAR)& OnFoot, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void CBotFuncs::OL_Bot_Slapper()
{
	short playerID = BotSettings.sTargetID;
	static int state = 0;
	if (IsPlayerStreamed(playerID))
	{
		stOnFootData OnFoot;
		memset(&OnFoot, 0, sizeof(stOnFootData));
		OnFoot.byteHealth = BotClient[BotSettings.CurrentClientID].fHealth;
		vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->base.matrix[12], OnFoot.fPosition);
		OnFoot.sCurrentAnimationID = 1666;
		OnFoot.sAnimFlags = 4356;
		switch (state)
		{
		case 0:
			//OnFoot.fPosition[0] += -10.0f;
			//OnFoot.fPosition[2] += 0.25f;
			OnFoot.fMoveSpeed[0] = -(10.0f + (rand() % 999) / 100.0f);
			OnFoot.fMoveSpeed[1] = 0;
			OnFoot.fMoveSpeed[2] = 0.25f;
			state++;
			break;
		case 1:
			//OnFoot.fPosition[1] += 10.0f;
			//OnFoot.fPosition[2] += 0.25f;
			OnFoot.fMoveSpeed[0] = 0;
			OnFoot.fMoveSpeed[1] = (10.0f + (rand() % 999) / 100.0f);
			OnFoot.fMoveSpeed[2] = 0.25f;
			state++;
			break;
		case 2:
			//OnFoot.fPosition[0] += -10.0f;
			//OnFoot.fPosition[2] += 0.25f;
			OnFoot.fMoveSpeed[0] = (10.0f + (rand() % 999) / 100.0f);
			OnFoot.fMoveSpeed[1] = 0;
			OnFoot.fMoveSpeed[2] = 0.25f;
			state++;
			break;
		case 3:
			//OnFoot.fPosition[1] += 10.0f;
			//OnFoot.fPosition[2] += 0.25f;
			OnFoot.fMoveSpeed[0] = 0;
			OnFoot.fMoveSpeed[1] = -(10.0f + (rand() % 999) / 100.0f);
			OnFoot.fMoveSpeed[2] = 0.25f;
			state = 0;
			break;
		}
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFoot, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}

void CBotFuncs::OL_Bot_Pick()
{
	render->D3DBox((pPresentParam.BackBufferWidth / 2) - 20.0f,
		(pPresentParam.BackBufferHeight / 2) - 1.0f, 40.0f, 2.0f,
		0xFF00FFFF);
	render->D3DBox((pPresentParam.BackBufferWidth / 2) - 1.0f,
		(pPresentParam.BackBufferHeight / 2) - 20.0f, 2.0f, 40.0f,
		0xFF00FFFF);
	static bool bVehiclePicked = false;
	//static int BotID = 0;
	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	OnFootData.byteHealth =
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
	OnFootData.byteArmor =
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
	OnFootData.sCurrentAnimationID =
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].sCurrentAnimationID;
	OnFootData.byteSpecialAction =
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].byteSpecialAction;
	OnFootData.sAnimFlags = 4356;
	//for fluid work
	OnFootData.fMoveSpeed[2] = -0.01f;

	if (KEY_DOWN(VK_RBUTTON))
	{
		if (g_NewModSa->iAimClientBot == BotSettings.CurrentClientID
			|| bVehiclePicked)
		{
			bVehiclePicked = true;
			vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.
				matrix[12], OnFootData.fPosition);
			OnFootData.fPosition[0] += cam_matrix[4] * 3.0f;
			OnFootData.fPosition[1] += cam_matrix[5] * 3.0f;
			OnFootData.fPosition[2] += cam_matrix[6] * 3.0f;
			vect3_copy(OnFootData.fPosition,
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].
				fLastOnFootPos);

			D3DXQUATERNION Quat;
			D3DXQUATERNION Quat2;
			Quat.w = g_Players->pLocalPlayer->onFootData.fQuaternion[0];
			Quat.x = g_Players->pLocalPlayer->onFootData.fQuaternion[1];
			Quat.y = g_Players->pLocalPlayer->onFootData.fQuaternion[2];
			Quat.z = g_Players->pLocalPlayer->onFootData.fQuaternion[3];
			//
			D3DXVECTOR3 Axis;
			Axis.x = 0;
			Axis.y = 0;
			Axis.z = 1;
			D3DXQuaternionRotationAxis(&Quat2, &Axis, M_PI);
			D3DXQuaternionMultiply(&Quat, &Quat, &Quat2);
			OnFootData.fQuaternion[0] = Quat.w;
			OnFootData.fQuaternion[1] = Quat.x;
			OnFootData.fQuaternion[2] = Quat.y;
			OnFootData.fQuaternion[3] = Quat.z;

			vect4_copy(OnFootData.fQuaternion,
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].
				fLastOnFootQuat);

			RakNet::BitStream bsOnFoot;
			bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
			bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
				Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

			//for fluid work
			BotSettings.CurrentClientID--;
		}
	}
	else
	{
		bVehiclePicked = false;
		vect3_copy(g_BotFuncs->BotClient[BotSettings.CurrentClientID].
			fLastOnFootPos, OnFootData.fPosition);
		vect4_copy(g_BotFuncs->BotClient[BotSettings.CurrentClientID].
			fLastOnFootQuat, OnFootData.fQuaternion);

		//cheat_state_text("%d", OnFootData.sCurrentAnimationID);
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}


}

void CBotFuncs::OL_Bot_Elevator()
{
	short playerID = BotSettings.sTargetID;
	if (IsPlayerStreamed(playerID))
	{
		stOnFootData OnFootData;
		memset(&OnFootData, 0, sizeof(stOnFootData));
		vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->base.matrix[12],
			OnFootData.fPosition);
		//vect3_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->speed, OnFootData.fMoveSpeed);
		OnFootData.fPosition[0] +=
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTA_Ped->speed[0] * 10.97f;
		OnFootData.fPosition[1] +=
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTA_Ped->speed[1] * 10.97f;
		OnFootData.fPosition[2] +=
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTA_Ped->speed[2] * 10.97f;
		OnFootData.fQuaternion[0] = 0.50f;
		OnFootData.fQuaternion[1] = -0.50f;
		OnFootData.fQuaternion[2] = 0.50f;
		OnFootData.fQuaternion[3] = 0.50f;
		OnFootData.fMoveSpeed[0] =
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->speed[0] * 1.5;
		OnFootData.fMoveSpeed[1] =
			g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->
			pGTAEntity->speed[1] * 1.5;
		OnFootData.fMoveSpeed[2] = 10.0f;	//random_float(5.0f, 30.0f);
		OnFootData.fPosition[2] -= (float)(rand() % 70) / 100.0f;
		if (BotSettings.bBotJetpackElevator)
			OnFootData.byteSpecialAction = 2;
		OnFootData.byteHealth =
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
		OnFootData.byteArmor =
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;

		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
}

void CBotFuncs::OL_Bot_Shooter()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		float fPos[3], fSpeed[3];
		bool bFake = BotSettings.UseFakeBot;
	
		float fRandomDistance = 5.5f + (rand() % 1000) / 100;
		if (bFake)
		{
			vect3_copy(g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
				pPlayerData->onFootData.fPosition, fPos);
			fPos[0] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[4] * fRandomDistance;
			fPos[1] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[5] * fRandomDistance;
			fPos[2] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[6] * fRandomDistance;

			fSpeed[0] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[4] * 7.5f;
			fSpeed[1] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[5] * 7.5f;
			fSpeed[2] +=
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				pSAMP_Actor->pGTAEntity->base.matrix[6] * 7.5f;
		
			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake);
		}
		else
		{
 
			static float distance = 4;
			static int counter = 0;
			static float c_angle = 0;
			static float rotate_speed = 23.1234f;
			static bool stillSending = false;
			vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.
				matrix[12], fPos);
			float apos[3];
			apos[0] = (distance * sin(c_angle + ((90 * counter) * PI / 180)));
			apos[1] = /*(distance * sin(c_angle + (90 * counter) * PI / 180))*/0;
			apos[2] = (distance * cos(c_angle + ((90 * counter) * PI / 180)));
			fPos[0] += apos[0];
			fPos[1] += apos[1];
			fPos[2] += apos[2];
			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;
			fPos[0] += fSpeed[0];
			fPos[1] += fSpeed[1];
			fPos[2] += fSpeed[2];
			fPos[2] += 0.5f;
			counter++;
			if (counter >= 4)
			{
				c_angle += rotate_speed * PI / 180;
				counter = 0;

				stillSending = false;
			}
			else
			{
				stillSending = true;
			}
			vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.
				matrix[12], fPos);
			fPos[0] += cam_matrix[4] * fRandomDistance;
			fPos[1] += cam_matrix[5] * fRandomDistance;
			fPos[2] += cam_matrix[6] * fRandomDistance;
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake);

		}
	}

}

void CBotFuncs::OL_Packet_PlayerSync(Packet * packet, uint8_t ClientID)
{
	if (g_BotFuncs->BotSettings.bBotSilent)
	{
		RakNet::BitStream bsOnFootSync((unsigned char *)packet->data, packet->length,
			false);
		unsigned short PlayerID;
		bsOnFootSync.IgnoreBits(8);
		bsOnFootSync.Read(PlayerID);
		if (BotSettings.UseFakeBot)
		{
			if (PlayerID != BotCheats->Target_PlayerID)
				return;
		}
		else
		{
			if (PlayerID != g_Players->sLocalPlayerID)
				return;
		}
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
		bsOnFootSync.ReadNormQuat(OnFootData.fQuaternion[0],
			OnFootData.fQuaternion[1],
			OnFootData.fQuaternion[2],
			OnFootData.fQuaternion[3]);


		BYTE byteHealthArmour;
		BYTE byteHealth, byteArmour;
		BYTE byteArmTemp = 0, byteHlTemp = 0;

		bsOnFootSync.Read(byteHealthArmour);
		byteArmTemp = (byteHealthArmour & 0x0F);
		byteHlTemp = (byteHealthArmour >> 4);

		if (byteArmTemp == 0xF)
			byteArmour = 100;
		else if (byteArmTemp == 0)
			byteArmour = 0;
		else
			byteArmour = byteArmTemp * 7;

		if (byteHlTemp == 0xF)
			byteHealth = 100;
		else if (byteHlTemp == 0)
			byteHealth = 0;
		else
			byteHealth = byteHlTemp * 7;

		OnFootData.byteHealth = byteHealth;
		OnFootData.byteArmor = byteArmour;

		BYTE byteWeaponKey;

		//bsOnFootSync.Read(OnFootData.byteCurrentWeapon);
		bsOnFootSync.Read(byteWeaponKey);
		OnFootData.byteCurrentWeapon = byteWeaponKey & 6;
		OnFootData.sKeys = byteWeaponKey & 2;

		bsOnFootSync.Read(OnFootData.byteSpecialAction);

		bsOnFootSync.ReadVector(OnFootData.fMoveSpeed[0],
			OnFootData.fMoveSpeed[1],
			OnFootData.fMoveSpeed[2]);

		bool bHasSurfInfo;
		bsOnFootSync.Read(bHasSurfInfo);
		if (bHasSurfInfo)
		{
			bsOnFootSync.Read(OnFootData.sSurfingVehicleID);
			bsOnFootSync.Read(OnFootData.fSurfingOffsets[0]);
			bsOnFootSync.Read(OnFootData.fSurfingOffsets[1]);
			bsOnFootSync.Read(OnFootData.fSurfingOffsets[2]);
		}
		else
			OnFootData.sSurfingVehicleID = -1;

		bool bAnimation;
		bsOnFootSync.Read(bAnimation);
		if (bAnimation)
			bsOnFootSync.Read(OnFootData.sCurrentAnimationID);

		vect3_copy(OnFootData.fPosition, BotSettings.fSelfPos);
		vect3_copy(OnFootData.fMoveSpeed, BotSettings.fSelfSpeed);
	}

	//}
	//memcpy(&PlayerInfo[PlayerID].OnFootSync, &OnFootData, sizeof(stOnFootData));
	//PlayerInfo[PlayerID].fPos[0] = PlayerInfo[PlayerID].OnFootSync.fPosition[0];
	//PlayerInfo[PlayerID].fPos[1] = PlayerInfo[PlayerID].OnFootSync.fPosition[1];
	//PlayerInfo[PlayerID].fPos[2] = PlayerInfo[PlayerID].OnFootSync.fPosition[2];
}


void CBotFuncs::OL_Packet_BulletSync(Packet * packet, uint8_t ClientID)
{
	if (BotSettings.bCopyWeapon)
	{
		RakNet::BitStream bsBullet((unsigned char *)packet->data, packet->length,
			false);
		uint16_t playerID;

		bsBullet.IgnoreBits(8);
		bsBullet.Read(playerID);
		if (BotSettings.UseFakeBot)
		{
			if (playerID != BotCheats->Target_PlayerID)
				return;
			stBulletData BulletData;
			memset(&BulletData, 0, sizeof(stBulletData));
			bsBullet.Read((char *)&BulletData, sizeof(stBulletData));
			RakNet::BitStream bsSend;
			bsSend.Write((BYTE)ID_BULLET_SYNC);
			bsSend.Write((char *)&BulletData, sizeof(stBulletData));
			g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
				HIGH_PRIORITY,
				UNRELIABLE_SEQUENCED,
				0);
		}
		else
		{
			if (playerID == g_Players->sLocalPlayerID)
			{
				stBulletData BulletData;
				memset(&BulletData, 0, sizeof(stBulletData));
				bsBullet.Read((char *)&BulletData, sizeof(stBulletData));
				RakNet::BitStream bsSend;
				bsSend.Write((BYTE)ID_BULLET_SYNC);
				bsSend.Write((PCHAR)& BulletData, sizeof(stBulletData));
				g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
					HIGH_PRIORITY,
					UNRELIABLE_SEQUENCED,
					0);
			}
		}
	}
}
void CBotFuncs::OL_Bot_Say(int iBotID, const char *szMessage, ...) // DarkNeX's Code, DarkNeX'in kodu..
{
	if (iBotID > BotSettings.CurrentClientID)
		return;
	va_list ap;
	char string[256];

	va_start(ap, szMessage);
	vsnprintf(string, sizeof(string), szMessage, ap);
	va_end(ap);

	BYTE len = (BYTE)strlen(string);

	RakNet::BitStream Params;

	Params.Write(len); // but here it takes one byte variable, understand? ofc my understand is this; RPC_ServerCommand wants 4 byte, RPC_Chat wants 1 byte 1 byte = byte 4 byte = int - exactly
	Params.Write(string, len);

	g_BotFuncs->OL_Bot_SendRPC(iBotID, RPC_Chat, Params, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false);
}
void CBotFuncs::OL_Packet_AimSync(Packet * packet, uint8_t ClientID)
{
	RakNet::BitStream bsAim((BYTE *)packet->data, packet->length, false);
	uint16_t playerID;

	bsAim.IgnoreBits(8);
	bsAim.Read(playerID);
	if (BotSettings.UseFakeBot)
	{
		if (playerID != BotCheats->Target_PlayerID)
			return;
		stAimData AimData;
		memset(&AimData, 0, sizeof(stAimData));
		bsAim.Read((char *)&AimData, sizeof(stAimData));
		RakNet::BitStream bsSend;
		bsSend.Write((BYTE)ID_AIM_SYNC);
		bsSend.Write((PCHAR)& AimData, sizeof(stAimData));
		g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
			HIGH_PRIORITY,
			UNRELIABLE_SEQUENCED,
			0);
	}
	else
	{
		if (playerID != g_Players->sLocalPlayerID)
			return;
		stAimData AimData;
		memset(&AimData, 0, sizeof(stAimData));
		bsAim.Read((char *)&AimData, sizeof(stAimData));
		RakNet::BitStream bsSend;
		bsSend.Write((BYTE)ID_AIM_SYNC);
		//comment for work total remote
		//bsSend.Write((PCHAR)&g_Players->pLocalPlayer->aimData, sizeof(stAimData));
		bsSend.Write((PCHAR)& AimData, sizeof(stAimData));
		g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
			HIGH_PRIORITY,
			UNRELIABLE_SEQUENCED,
			0);
	}

}
void CBotFuncs::OL_Packet_UnoccupiedSync(Packet* packet, uint8_t ClientID)
{
	RakNet::BitStream bsUnoc((BYTE*)packet->data, packet->length, false);
	uint16_t playerID;

	bsUnoc.IgnoreBits(8);
	bsUnoc.Read(playerID);
	if (BotSettings.UseFakeBot)
	{
		if (playerID != BotCheats->Target_PlayerID)
			return;
		stUnoccupiedData unoccupiedData;
		memset(&unoccupiedData, 0, sizeof(stUnoccupiedData));
		bsUnoc.Read((char*)&unoccupiedData, sizeof(stUnoccupiedData));
		RakNet::BitStream bsSend;
		bsSend.Write((BYTE)ID_AIM_SYNC);
		bsSend.Write((PCHAR)&unoccupiedData, sizeof(stUnoccupiedData));
		g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
			HIGH_PRIORITY,
			UNRELIABLE_SEQUENCED,
			0);
	}
	else
	{
		if (playerID != g_Players->sLocalPlayerID)
			return;
		stUnoccupiedData unoccupiedData;
		memset(&unoccupiedData, 0, sizeof(stUnoccupiedData));
		bsUnoc.Read((char*)&unoccupiedData, sizeof(stUnoccupiedData));
		RakNet::BitStream bsSend;
		bsSend.Write((BYTE)ID_AIM_SYNC);
		bsSend.Write((PCHAR)&unoccupiedData, sizeof(stUnoccupiedData));
		g_BotFuncs->BotClient[ClientID].pRakClient->Send(&bsSend,
			HIGH_PRIORITY,
			UNRELIABLE_SEQUENCED,
			0);
	}
}
void CBotFuncs::OL_Bot_Silent()
{
	static float fPos[3];
	if (vect3_near_zero(fPos))
	{
		vect3_copy(g_Players->pLocalPlayer->onFootData.fPosition, fPos);
	}
	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	vect3_copy(fPos, OnFootData.fPosition);
	OnFootData.byteCurrentWeapon = g_Players->pLocalPlayer->onFootData.byteCurrentWeapon;
	OnFootData.sKeys = 132;
	OnFootData.byteHealth = 100;
	RakNet::BitStream bsOnFoot;
	bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

	stAimData AimData;
	memset(&AimData, 0, sizeof(stAimData));
	AimData.byteCamMode = 65;	//work with all weapon and sniper
	AimData.vecAimf1[0] = 0;
	AimData.vecAimf1[1] = 0;
	AimData.vecAimf1[2] = -0.01f;
	vect3_copy(BotSettings.fSelfPos, AimData.vecAimPos);
	AimData.vecAimPos[0] += BotSettings.fSelfSpeed[0]
		* BotSettings.fMultiplierSilent;
	AimData.vecAimPos[1] += BotSettings.fSelfSpeed[1]
		* BotSettings.fMultiplierSilent;
	AimData.vecAimPos[2] += 1.0f + BotSettings.fSelfSpeed[2]
		* BotSettings.fMultiplierSilent;
	RakNet::BitStream bsAim;
	bsAim.Write((BYTE)ID_AIM_SYNC);
	bsAim.Write((PCHAR)& AimData, sizeof(stAimData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsAim,
		HIGH_PRIORITY,
		UNRELIABLE_SEQUENCED,
		0);

}

void CBotFuncs::OL_Bot_Follow_Passenger(bool bFake)
{
	if (!g_BotFuncs->BotClient[BotSettings.CurrentClientID].bIsInVehicle)
	{
		//for UIF protection

		short sVehicleID;
		RakNet::BitStream bsEnterVehicle;
		if (bFake)
		{
			sVehicleID =
				g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
				inCarData.sVehicleID;
		}
		else
		{
			sVehicleID = g_Players->pLocalPlayer->inCarData.sVehicleID;
		}

		CVehicle *pVehicle =
			pGameInterface->GetPools()->
			GetVehicle((DWORD *)getGTAVehicleFromSAMPVehicleID(sVehicleID));
		if (isBadPtr_GTA_pVehicle(pVehicle))
			return;
		float fPos[3], fNull[3] = { 0, 0, 0 };
		fPos[0] = pVehicle->GetInterface()->Placeable.matrix->vPos.fX;
		fPos[1] = pVehicle->GetInterface()->Placeable.matrix->vPos.fY;
		fPos[2] = pVehicle->GetInterface()->Placeable.matrix->vPos.fZ;
		OL_Bot_Send_OnFoot(fPos, fNull, bFake, sVehicleID, fNull);

		bsEnterVehicle.Write(sVehicleID);
		bsEnterVehicle.Write((BYTE)BotSettings.CurrentClientID + 1);
		g_BotFuncs->OL_Bot_SendRPC(BotSettings.CurrentClientID,
			RPC_EnterVehicle, bsEnterVehicle,
			HIGH_PRIORITY, RELIABLE_SEQUENCED, NULL,
			false);
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].bIsInVehicle = true;

	}
	OL_Bot_Send_Passenger(bFake);
}

void CBotFuncs::OL_Bot_Follow_OnFoot(bool bFake)
{

	if (g_BotFuncs->BotClient[BotSettings.CurrentClientID].bIsInVehicle)
	{
		RakNet::BitStream bsExitVehicle;
		bsExitVehicle.Write(g_BotFuncs->BotClient[BotSettings.CurrentClientID].
			last_vehicleID);
		g_BotFuncs->OL_Bot_SendRPC(BotSettings.CurrentClientID,
			RPC_ExitVehicle, bsExitVehicle,
			HIGH_PRIORITY, RELIABLE_SEQUENCED, NULL,
			false);
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].bIsInVehicle = false;
	}
	float rest = (BotSettings.CurrentClientID + 1) % 2;
	int versor = (rest == 0) ? 1 : -1;
	int versor2 = (rest == 0) ? -1 : 0;
	float fPos[3], fPos2[3], fSpeed[3], fRotation;
	bool bSurf = false;

	if (bFake)
	{
		vect3_copy(g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
			pPlayerData->onFootData.fPosition, fPos);

		vect3_copy(fPos, fPos2);

		vect3_copy(g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
			pPlayerData->onFootData.fMoveSpeed, fSpeed);
		fRotation =
			g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			pSAMP_Actor->pGTAEntity->fCurrentRotation;

		fPos2[0] =
			(BotSettings.fDistanceFollow +
			(BotSettings.CurrentClientID +
				versor2) * BotSettings.fDistanceFollowBetweenBots) *
				(sinf(-fRotation)) +
			((BotSettings.CurrentClientID + 1 +
				versor2) * BotSettings.fDistanceFollowBetweenBots * versor) *
			cosf(fRotation);
		fPos2[1] =
			(BotSettings.fDistanceFollow +
			(BotSettings.CurrentClientID +
				versor2) * BotSettings.fDistanceFollowBetweenBots) *
				(cosf(-fRotation)) +
			((BotSettings.CurrentClientID + 1 +
				versor2) * BotSettings.fDistanceFollowBetweenBots * versor) *
			sinf(fRotation);
		fPos2[2] = 0;

		fPos[0] += fPos2[0];
		fPos[1] += fPos2[1];
		fPos[2] += fPos2[2];

		fSpeed[2] -= 0.01;

		if (g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			onFootData.sSurfingVehicleID != 0)
		{
			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake,
				g_Players->pRemotePlayer[BotCheats->
				Target_PlayerID]->
				pPlayerData->onFootData.sSurfingVehicleID,
				fPos2);
		}
		else
		{
			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake);
			OL_Bot_Send_Aim(true);
		}
	}
	else
	{
		vect3_copy(g_Players->pLocalPlayer->onFootData.fPosition, fPos);

		vect3_copy(fPos, fPos2);

		vect3_copy(g_Players->pLocalPlayer->onFootData.fMoveSpeed, fSpeed);
		
		fRotation = g_Players->pLocalPlayer->pSAMP_Actor->pGTAEntity->fCurrentRotation;

		fPos2[0] =
			(BotSettings.fDistanceFollow +
			(BotSettings.CurrentClientID +
				versor2) * BotSettings.fDistanceFollowBetweenBots) *
				(sinf(-fRotation)) +
			((BotSettings.CurrentClientID + 1 +
				versor2) * BotSettings.fDistanceFollowBetweenBots * versor) *
			cosf(fRotation);
		fPos2[1] =
			(BotSettings.fDistanceFollow + (BotSettings.CurrentClientID + versor2) * BotSettings.fDistanceFollowBetweenBots) * (cosf(-fRotation)) +
			((BotSettings.CurrentClientID + 1 +
				versor2) * BotSettings.fDistanceFollowBetweenBots * versor) *
			sinf(fRotation);
		fPos2[2] = 0;

		fPos[0] += fPos2[0];
		fPos[1] += fPos2[1];
		fPos[2] += fPos2[2];

		fSpeed[2] -= 0.01;
	

		if (g_Players->pLocalPlayer->onFootData.sSurfingVehicleID != 0)
		{

			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake,
				g_Players->pLocalPlayer->onFootData.
				sSurfingVehicleID, fPos2);
		}
		else
		{
			OL_Bot_Send_OnFoot(fPos, fSpeed, bFake);
			OL_Bot_Send_Aim(false);
		}
	}


}

void CBotFuncs::OL_Bot_Attacker()
{
	short playerID = BotSettings.sTargetID;
	if (IsPlayerStreamed(playerID))
	{
		float angle =
			(float)(BotSettings.CurrentClientID +
			1) / (float)(BotSettings.ClientCount);
		float alpha =
			(float)BotSettings.CurrentClientID * (2.0f * M_PI) /
			(float)BotSettings.ClientCount;
		//Log("%d / %d =  %f", BotSettings.CurrentClientID + 1, BotSettings.ClientCount, angle);
		D3DXQUATERNION Quat;
		D3DXVECTOR3 Axis;
		Axis.x = 1;
		Axis.y = 0;
		Axis.z = 0;
		D3DXQuaternionRotationAxis(&Quat, &Axis, (2 * M_PI) - alpha);

		stOnFootData OnFootData;
		memset(&OnFootData, 0, sizeof(stOnFootData));
		vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->base.matrix[12],
			OnFootData.fPosition);
		vect3_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->
			pSAMP_Actor->pGTA_Ped->speed, OnFootData.fMoveSpeed);
		OnFootData.fQuaternion[0] = Quat.x;
		OnFootData.fQuaternion[1] = Quat.y;
		OnFootData.fQuaternion[2] = Quat.z;
		OnFootData.fQuaternion[3] = Quat.w;

		OnFootData.fPosition[1] += cosf(alpha) * 5.0f;
		OnFootData.fPosition[0] += sinf(alpha) * 5.0f;


		OnFootData.byteCurrentWeapon = BotSettings.uiAttackWeaponID;
		OnFootData.sKeys = 4;
		OnFootData.byteSpecialAction = 1; // 3'tü 0 yaptým. // Bullet Senkronizasyonu iþlev görmüyor... tekrar 1 yapýyorum.
		OnFootData.byteHealth = 100;
		OnFootData.fMoveSpeed[2] = -1;
		RakNet::BitStream bsOnFoot;
		bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
		bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
			Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		vect3_copy(OnFootData.fPosition,
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].
			fLastOnFootPos);

		if (g_NewModSa->byteLagComp)
		{
			if (time_get() -
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].
				dwSendBulletTick > MSEC_TO_TIME(500))
			{
				stBulletData BulletData;
				memset(&BulletData, 0, sizeof(stBulletData));
				BulletData.sTargetID = playerID;
				BulletData.byteType = 1;
				BulletData.byteWeaponID = BotSettings.uiAttackWeaponID;
				vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
					pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fOrigin);
				vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
					pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fTarget);
				BulletData.fCenter[2] = 0.5f;
				RakNet::BitStream bsSend;
				bsSend.Write((BYTE)ID_BULLET_SYNC);
				bsSend.Write((PCHAR)& BulletData, sizeof(stBulletData));
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
					Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].
					dwSendBulletTick = time_get();
			}
		}
		else
		{
			stAimData AimData;
			memset(&AimData, 0, sizeof(stAimData));
			AimData.byteCamMode = 65;	//work with all weapon and sniper
			AimData.vecAimf1[0] = 0;
			AimData.vecAimf1[1] = 0;
			AimData.vecAimf1[2] = -0.01f;
			vect3_copy(&g_Players->pRemotePlayer[playerID]->pPlayerData->
				pSAMP_Actor->pGTA_Ped->base.matrix[12],
				AimData.vecAimPos);
			AimData.vecAimPos[0] +=
				g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.
				fMoveSpeed[0] * 10.97f;
			AimData.vecAimPos[1] +=
				g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.
				fMoveSpeed[1] * 10.97f;
			AimData.vecAimPos[2] +=
				1.0f +
				g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.
				fMoveSpeed[2] * 10.97f;
			RakNet::BitStream bsSend;
			bsSend.Write((BYTE)ID_AIM_SYNC);
			bsSend.Write((PCHAR)& AimData, sizeof(stAimData));
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
				Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		}
	}
}
void CBotFuncs::BotRemovePlayerCrasher()
{
	float fPos_[3];
	float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	fPos_[0] = coord[0], fPos_[1] = coord[1], fPos_[2] = coord[2];

	bool static foot_state = false;

	static DWORD tick = 0;

	DWORD now_tick = GetTickCount();

	if (now_tick - tick > 150) // Delay 280'den 150'ye düþürüldü.
	{
		tick = now_tick;

		//static bool normalize = false;

		if (!foot_state)
		{
			stOnFootData footData;
			ZeroMemory(&footData, sizeof(stOnFootData));

			footData.fPosition[0] = coord[0];
			footData.fPosition[1] = coord[1];
			footData.fPosition[2] = coord[2];

			footData.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			footData.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			footData.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

			footData.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			footData.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			RakNet::BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)& footData, sizeof(stOnFootData));
			for (int i = 0; i < 2; i++)
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			foot_state = true;
		}
		else
		{
			RakNet::BitStream bs;
			for (int i = 0; i < 2; i++)
				g_BotFuncs->OL_Bot_SendRPC(BotSettings.CurrentClientID, RPC_Spawn, bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, false);
			foot_state = false;
		}
	}
}
 
void CBotFuncs::BotDiscoMode()
{
	static bool pfoot_State = false;
	if (pfoot_State == false)
	{
		stOnFootData onSync;
		ZeroMemory(&onSync, sizeof(stOnFootData));

		onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
		onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

		onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
		onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
		onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

		onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
		onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
		onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

		onSync.byteCurrentWeapon = 0;
		onSync.sUpDownKeys = 128;
		onSync.sLeftRightKeys = 128;
		onSync.sKeys = 4;

		RakNet::BitStream bsData;
		bsData.Write((BYTE)ID_PLAYER_SYNC);
		bsData.Write((PCHAR)& onSync, sizeof(stOnFootData));
		for (int i = 0; i < 2; i++)
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
		pfoot_State = true;
	}
	else
	{
		static DWORD tick = 200;

		DWORD now_tick = GetTickCount();

		if (now_tick - tick > 100)
		{
			tick = now_tick;

			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));

			onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
			onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;

			onSync.fPosition[0] = g_Players->pLocalPlayer->onFootData.fPosition[0];
			onSync.fPosition[1] = g_Players->pLocalPlayer->onFootData.fPosition[1];
			onSync.fPosition[2] = g_Players->pLocalPlayer->onFootData.fPosition[2];

			onSync.fMoveSpeed[0] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[0];
			onSync.fMoveSpeed[1] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[1];
			onSync.fMoveSpeed[2] = g_Players->pLocalPlayer->onFootData.fMoveSpeed[2];

			onSync.byteCurrentWeapon = 44 + rand() % 2;
			onSync.sUpDownKeys = 128;
			onSync.sLeftRightKeys = 128;

			RakNet::BitStream bsData;
			bsData.Write((BYTE)ID_PLAYER_SYNC);
			bsData.Write((PCHAR)& onSync, sizeof(stOnFootData));
			for (int i = 0; i < 2; i++)
				g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			pfoot_State = false;
		}
	}
}

void CBotFuncs::BotPlayerCrashers(uint16_t uiClientID)
{
	/*
	bool bConnected;
	bool bJoined;
	bool bSpawned;
	*/
	/*if (g_BotFuncs->BotSettings.ClientJoined == NULL)
		return cheat_state_text("Sunucuya bot at...");*/
	/*if(!BotClient[uiClientID].bConnected)
		return cheat_state_text("Sunucuya bot at...");
	if (!BotClient[uiClientID].bSpawned)
		return cheat_state_text("Sunucuya atýlan botlarý spawn et!!");*/
	
	float fPosition[3];
	float fPassengerCrasher[3] = { 9910000000000.0F, 9910000000000.0F, 9910000000000.0F };
	float fRollCrasher[3] = { 9910000000000.0F, 9910000000000.0F, 9910000000000.0F };
	struct actor_info* self = actor_info_get(ACTOR_SELF, NULL);
	vehicle_info* vehicle = GetVehicleInfoStandart(
			VEHICLE_NO_BE_PROTECT |
			VEHICLE_NOT_FRIEND |
			VEHICLE_NOT_OCCUPIED |
			VEHICLE_NOT_CLOSED,
			VEHICLE_CLOSEST |
			VEHICLE_NOT_MY |
			VEHICLE_ALIVE |
			VEHICLE_NOT_TRAIN);
	int iVehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
	float fOrigin[3], fTarget[3], fCenter[3];
	static DWORD tick = 0;
	DWORD now_tick = GetTickCount();
	switch (set.Bots.BotCrasherType)
	{
		case BOT_CRASHER_TYPE_OFF:
		{

		}break;

		case BOT_CRASHER_TYPE_DETONATOR:
		{
			bool static foot_state = false;
			float fPosition[3];
			float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
			fPosition[0] = coord[0], fPosition[1] = coord[1], fPosition[2] = coord[2];
			if (!foot_state)
			{
				stOnFootData onfootSync;
				ZeroMemory(&onfootSync, sizeof(stOnFootData));
				if (now_tick - tick > 150) // Delay 280'den 150'ye düþürüldü.
				{
					tick = now_tick;
					onfootSync.byteArmor = 0;
					onfootSync.byteHealth = 100;
					onfootSync.byteSpecialAction = 3;
					onfootSync.fPosition[0] = fPosition[0];
					onfootSync.fPosition[1] = fPosition[1];
					onfootSync.fPosition[2] = fPosition[2];
					/*cheat_state_text("Detonator Crasher 1");*/
					for (int i = 0; i < 2; i++)
						g_BotEntity->WriteOnFootSync(&onfootSync);
					foot_state = true;
				}
			}
			else
			{
				RakNet::BitStream bs;
				for (int i = 0; i < 2; i++)
					g_BotFuncs->OL_Bot_SendRPC(BotSettings.CurrentClientID, RPC_Spawn, bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, false);
				foot_state = false;
			}
		}break;

		case BOT_CRASHER_TYPE_BULLETS:
		{
			stUnoccupiedData unSync;
			ZeroMemory(&unSync, sizeof(stUnoccupiedData));
			stOnFootData onSync;
			ZeroMemory(&onSync, sizeof(stOnFootData));
			g_BotFuncs->BotSettings.bCopyWeapon = true;
			if (!self)
				return;
			int PlayerID = GetClosestPlayerid(self, GetActorFlag(true, false, false, true, false, false, false, false));
			if (!vehicle)
				return;
			int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
			float fPos[3];
			//BYTE bSeatIDs[2] = { -1, 255 };
			if (now_tick - tick > 250)
			{
				vect3_copy(vehicle->base.matrix + 12, fPos);
				actor_info* deadman = getGTAPedFromSAMPPlayerID(PlayerID);
				if (!deadman)
					return;

				vect3_copy(&self->base.matrix[4 * 3], fOrigin);
				vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
				fCenter[0] = -0.01f;
				fCenter[1] = -0.02f;
				fCenter[2] = 0.04f;
				g_BotFuncs->BotSettings.bCopyWeapon = true;
				int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
				if (cheack_valid_weaponid(WeaponID))
				{
					g_BotEntity->SendFakeBulletData(PlayerID, fOrigin, fTarget, fCenter, WeaponID, BULLET_HIT_TYPE_PLAYER);
					onSync.byteHealth = g_Players->pLocalPlayer->onFootData.byteHealth;
					onSync.byteArmor = g_Players->pLocalPlayer->onFootData.byteArmor;
					onSync.fPosition[0] = fPos[0];
					onSync.fPosition[1] = fPos[1];
					onSync.fPosition[2] = -5.5f;
					onSync.fSurfingOffsets[2] = -5.5f;
					onSync.sSurfingVehicleID = VehicleID;
					g_BotEntity->WriteOnFootSync(&onSync);
					unSync.sVehicleID = VehicleID;
					unSync.fPosition[0] = fPos[0];
					unSync.fPosition[1] = fPos[1];
					unSync.fPosition[2] = -5.5f;
					unSync.fHealth = vehicle->hitpoints;
					unSync.fMoveSpeed[0] = vehicle->speed[0];
					unSync.fMoveSpeed[1] = vehicle->speed[1];
					unSync.fMoveSpeed[2] = vehicle->speed[2];
					unSync.fRoll[0] = 1;
					unSync.fRoll[1] = 1;
					unSync.fRoll[2] = 1;
					unSync.fDirection[0] = 0;
					unSync.fDirection[1] = 1;
					unSync.fDirection[2] = 0;
					unSync.fTurnSpeed[0] = 0x15F90; // 90000.0f deðerine denk geliyor
					unSync.fTurnSpeed[1] = 0x15F90;
					unSync.fTurnSpeed[2] = 0x15F90;
					unSync.byteSeatID = 1;
					RakNet::BitStream bsUnoccupiedSync; // Veriyi tanýmla
					bsUnoccupiedSync.Write((BYTE)ID_UNOCCUPIED_SYNC); // Veriyi oyuna yazdýr.
					bsUnoccupiedSync.Write((PCHAR)& unSync, sizeof(stUnoccupiedData)); // Veriyi oyuna yazdýr.
					g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsUnoccupiedSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0); // Veriyi gönder
					tick = now_tick;
				}
			}
		}break;
		case BOT_CRASHER_TYPE_POSITION: // Passenger Crasher bs
		{
			if (now_tick - tick > 100)
			{
				if (!self)
					return;
				if (!vehicle)
					return;
				vect3_copy(&self->base.matrix[12], fPosition);
				fPosition[0] += 3.0f;
				if (self->state == CHEAT_STATE_ACTOR)
				{
					g_BotClient->SendFakePassengerSyncData(uiClientID, iVehicleID, fPosition, vehicle->hitpoints, g_Players->pLocalPlayer->byteCurrentWeapon, 1, 128);
					g_BotClient->SendExitPlayerVehicle(uiClientID, iVehicleID);
					g_BotClient->SendFakeUnoccupiedSyncData(uiClientID, iVehicleID, 1, fPassengerCrasher, vehicle->speed, vehicle->hitpoints, &vehicle->base.matrix[0], 0);
				}
				tick = now_tick;
			}
		}break;

		case BOT_CRASHER_TYPE_ROLL:
		{
			if (now_tick - tick > 100)
			{
				if (!self)
					return;
				if (!vehicle)
					return;
				vect3_copy(&self->base.matrix[12], fPosition);
				fPosition[0] += 4.0f;
				vect3_copy(&self->base.matrix[12], fPosition);
				vehicle->base.matrix[4 * 1 + 1];
				vehicle->base.matrix[4 * 1 - 1];
				if (self->state == CHEAT_STATE_ACTOR)
				{
					g_BotClient->SendFakeUnoccupiedSyncData(uiClientID, iVehicleID, 1, fPosition, vehicle->speed, vehicle->hitpoints, &vehicle->base.matrix[0], fRollCrasher);
					/*g_BotClient->SendFakePassengerSyncData(BotSettings.CurrentClientID, iVehicleID, fPosition, vehicle->hitpoints, g_Players->pLocalPlayer->byteCurrentWeapon, 1, 128);*/
					g_RakClient->SendEnterPlayerVehicle(iVehicleID, 1);
					g_BotClient->SendExitPlayerVehicle(uiClientID, iVehicleID);
				}
				tick = now_tick;
			}
		}break;

		case BOT_CRASHER_TYPE_NEGATIVE_BULLETS:
		{

		}break;
		
		case BOT_CRASHER_TYPE_TUNING:
		{

		}break;

		case BOT_CRASHER_TYPE_LOWROLL:
		{

		}break;

	}
}

void CBotFuncs::BotKiller(/*uint16_t uiClientID*/)
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, 0);
	DWORD dwFakeBulletTime = 0;
	float fRange = 400.0f;
	float fSpeed = 99.0f;
	stOnFootData OnFoot;
	memset(&OnFoot, 0, sizeof(stOnFootData));
	OnFoot.byteHealth = BotClient[BotSettings.CurrentClientID].fHealth;
	vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.
		matrix[12], OnFoot.fPosition);
	OnFoot.fPosition[0] +=
		(fRange / 2.f) - (float)rand() / (float)(RAND_MAX / fRange);
	OnFoot.fPosition[1] +=
		(fRange / 2.f) - (float)rand() / (float)(RAND_MAX / fRange);
	OnFoot.fMoveSpeed[0] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fMoveSpeed[1] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fMoveSpeed[2] +=
		(fSpeed / 2.f) - (float)rand() / (float)(RAND_MAX / fSpeed);
	OnFoot.fQuaternion[0] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[1] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[2] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.fQuaternion[3] = 1.0f - (float)rand() / (float)(RAND_MAX / 2.0f);
	OnFoot.sCurrentAnimationID = rand() % 2000;
	OnFoot.sAnimFlags = 4356;

	RakNet::BitStream bsOnFoot;
	bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFoot.Write((PCHAR)& OnFoot, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

	for (int x = 0; x < SAMP_MAX_PLAYERS; x++)
	{
		if (IsPlayerStreamed(x))
		{
			struct actor_info* ainfo = getGTAPedFromSAMPPlayerID(x);
			if (ainfo == NULL)
				continue;
			float myPos[3];
			vect3_copy(&self->base.matrix[4 * 3], myPos);
			float playerPos[3];
			vect3_copy(&ainfo->base.matrix[4 * 3], playerPos);
			if (GetTickCount() - 250 > dwFakeBulletTime)
			{
				g_RakClient->SendGiveDamage(x, 0, 4, 3);
				g_RakClient->SendGiveDamage(x, 1833.331542, 4, 3);
				//cheat_state_text("Damage Gönderdi... Oyuncu ID: %d", x);
				dwFakeBulletTime = GetTickCount();
			}
		}
	}
}
void CBotFuncs::OL_Bot_Follow()
{
	if (BotSettings.UseFakeBot)
	{
		if (IsPlayerStreamed(BotCheats->Target_PlayerID))
		{
			switch (g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
				pPlayerData->bytePlayerState)
			{
			case PLAYER_STATE_ONFOOT:
				OL_Bot_Follow_OnFoot(true);
				break;

			case PLAYER_STATE_DRIVER:
				OL_Bot_Follow_Passenger(true);
				break;

			default:
				OL_Bot_Follow_OnFoot(true);
				break;
			}

		}
		else
		{
			cheat_state_text("Player/Enemy is not streamed..");
			return;
		}
	}
	else
	{
		if (g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle)
		{
			OL_Bot_Follow_Passenger(false);
		}
		else
		{
			OL_Bot_Follow_OnFoot(false);
		}

	}

	//vect3_copy(OnFootData.fPosition, pos);
}


void CBotFuncs::OL_Packet_Auth_Key(Packet* packet, uint8_t ClientID)
{
 
	if (g_BotFuncs->BotSettings.bConnectAsNPC)
	{
		char* auth_key = "NPC";
		bool found_key = true;
		if (found_key)
		{
			RakNet::BitStream bsKey;
			BYTE byteAuthKeyLen;

			byteAuthKeyLen = (BYTE)strlen(auth_key);

			bsKey.Write((BYTE)ID_AUTH_KEY);
			bsKey.Write((BYTE)byteAuthKeyLen);
			bsKey.Write(auth_key, byteAuthKeyLen);

			BotClient[ClientID].pRakClient->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE,
				NULL);

		}
	}
	else
	{
		char* auth_key = "";
		bool found_key = false;

		for (int x = 0; x < 1535; x++)
		{
			if (!strcmp(((char*)packet->data + 2), AuthKeyTable[x][0]))
			{
				auth_key = AuthKeyTable[x][1];
				found_key = true;
				break;
			}
		}

		if (found_key)
		{
			RakNet::BitStream bsKey;
			BYTE byteAuthKeyLen;

			byteAuthKeyLen = (BYTE)strlen(auth_key);

			bsKey.Write((BYTE)ID_AUTH_KEY);
			bsKey.Write((BYTE)byteAuthKeyLen);
			bsKey.Write(auth_key, byteAuthKeyLen);

			BotClient[ClientID].pRakClient->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE,
				NULL);

		}
	}

	char* auth_key = "";
	bool found_key = false;

	for (int x = 0; x < 1535; x++)
	{
		if (!strcmp(((char*)packet->data + 2), AuthKeyTable[x][0]))
		{
			auth_key = AuthKeyTable[x][1];
			found_key = true;
			break;
		}
	}
	if (found_key)
	{
		RakNet::BitStream bsKey;
		BYTE byteAuthKeyLen;

		byteAuthKeyLen = (BYTE)strlen(auth_key);

		bsKey.Write((BYTE)ID_AUTH_KEY);
		bsKey.Write((BYTE)byteAuthKeyLen);
		bsKey.Write(auth_key, byteAuthKeyLen);

		BotClient[ClientID].pRakClient->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE,
			NULL);

	}
}

void CBotFuncs::OL_Packet_ConnectionAccepted(Packet* packet, uint8_t ClientID)
{
	cheat_state_text("Connection Accepted for Client ID: %d", ClientID);
	RakNet::BitStream bsSuccAuth((unsigned char*)packet->data, packet->length,
		false);
	bsSuccAuth.IgnoreBits(8);	// ID_CONNECTION_REQUEST_ACCEPTED
	bsSuccAuth.IgnoreBits(32);	// binaryAddress
	bsSuccAuth.IgnoreBits(16);	// port
	bsSuccAuth.Read(BotClient[ClientID].playerID);
	bsSuccAuth.Read(BotClient[ClientID].uiChallenge);

	uiIsBot[BotClient[ClientID].playerID][0] = 1;
	uiIsBot[BotClient[ClientID].playerID][1] = ClientID;

	int iVersion = 4057;		// NETGAME_VERSION;

	char auth_bs[4 * 16] = { 0 };
	char client_version[] = "0.3.7";	// CLIENT_VERSION;
	gen_gpci(auth_bs, 0x3e9);
	/*gen_rand_gpci(auth_bs, 0x3E9);*/
	//BYTE byteNameLen = (BYTE)strlen(BotClient[ClientID].NickName);
	BYTE byteNameLen = (BYTE)strlen(BotClient[ClientID].NickName);
	BYTE byteAuthBSLen = (BYTE)strlen(auth_bs);
	BYTE byteVersionLen = (BYTE)strlen(client_version);
	RakNet::BitStream bsSend;
	unsigned int uiClientChallengeResponse =
		BotClient[ClientID].uiChallenge ^ iVersion;

	bsSend.Write(iVersion);
	bsSend.Write((BYTE)1);	//byteMod

	bsSend.Write(byteNameLen);
	bsSend.Write(BotClient[ClientID].NickName, byteNameLen);

	bsSend.Write(uiClientChallengeResponse);
	bsSend.Write(byteAuthBSLen);
	bsSend.Write(auth_bs, byteAuthBSLen);

	bsSend.Write(byteVersionLen);
	bsSend.Write(client_version, byteVersionLen);
	if (g_BotFuncs->BotSettings.bConnectAsNPC)
		OL_Bot_SendRPC(ClientID, RPC_NPCJoin, bsSend, HIGH_PRIORITY,
			RELIABLE_ORDERED, 0, false);
	else
		OL_Bot_SendRPC(ClientID, RPC_ClientJoin, bsSend, HIGH_PRIORITY,
			RELIABLE_ORDERED, 0, false);
	BotClient[ClientID].bJoined = true;
	BotSettings.ClientJoined++;
}


bool CBotFuncs::OL_Bot_SendRPC(uint8_t ClientID, int iRPCID, RakNet::BitStream Params,
PacketPriority Priority,
PacketReliability Reliability,
char OrderingChannel, bool ShiftTimestamp)
{
	return BotClient[ClientID].pRakClient->RPC(&iRPCID, &Params, Priority, Reliability, OrderingChannel, ShiftTimestamp);
}

void CBotFuncs::OL_Random_Spawn_Bot(uint8_t ClientID)
{

	int ClassID = rand() % (g_SAMP->pSettings->iClassesAvailable - 1);

	RakNet::BitStream bsSpawnRequest;
	bsSpawnRequest.Write(ClassID);
	OL_Bot_SendRPC(ClientID, RPC_RequestClass, bsSpawnRequest, HIGH_PRIORITY,
		RELIABLE, 0, FALSE);

	RakNet::BitStream bsSendRequestSpawn;
	OL_Bot_SendRPC(ClientID, RPC_RequestSpawn, bsSendRequestSpawn,
		HIGH_PRIORITY, RELIABLE, 0, FALSE);
	RakNet::BitStream bsSendSpawn;
	OL_Bot_SendRPC(ClientID, RPC_Spawn, bsSendSpawn, HIGH_PRIORITY, RELIABLE,
		0, FALSE);
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth = 100.0f;
}

void CBotFuncs::OL_Spawn_Bot(uint8_t ClientID)
{
	RakNet::BitStream bsSpawnRequest;
	bsSpawnRequest.Write(g_BotFuncs->BotSettings.ClassID);
	OL_Bot_SendRPC(ClientID, RPC_RequestClass, bsSpawnRequest, HIGH_PRIORITY,
		RELIABLE, 0, FALSE);

	RakNet::BitStream bsSendRequestSpawn;
	OL_Bot_SendRPC(ClientID, RPC_RequestSpawn, bsSendRequestSpawn,
		HIGH_PRIORITY, RELIABLE, 0, FALSE);
	RakNet::BitStream bsSendSpawn;
	OL_Bot_SendRPC(ClientID, RPC_Spawn, bsSendSpawn, HIGH_PRIORITY, RELIABLE,
		0, FALSE);
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth = 100.0f;
}
//void CBotFuncs::OL_Bot_ReceiveRPC(RakClientInterface** pRakClient)
//{
//	int RPC_SetHealth = RPC_SetPlayerHealth;
//	int RPC_SetArmour = RPC_SetPlayerArmour;
//	pRakClient[0]->RegisterAsRemoteProcedureCall(&RPC_SetHealth,
//		OL_Bot_SetHealth);
//	pRakClient[0]->RegisterAsRemoteProcedureCall(&RPC_SetArmour,
//		OL_Bot_SetArmour);
//}

void CBotFuncs::OL_Bot_Send_Aim(bool bCopyFakePlayerVariables)
{
	stAimData aimData;
	memset(&aimData, 0, sizeof(stAimData));
	if (bCopyFakePlayerVariables)
	{
		memcpy(&aimData,
			&g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
			pPlayerData->aimData, sizeof(stAimData));
	}
	else
	{
		memcpy(&aimData, &g_Players->pLocalPlayer->aimData,
			sizeof(stAimData));
	}
	if (g_BotFuncs->BotSettings.bSpinBot)
	{
	
		///*if (!g_BotFuncs->BotSettings.bCopyWeapon)
		//	return cheat_state_text("Go enable Copy Weapon function.");*/
	
		//aimData.fAimZ = 1.45f;
		////cheat_state_text("Aim'in Z Ekseni: %f", aimData.fAimZ);
		//if (g_Players->pLocalPlayer->byteCurrentWeapon == 30 || 31)
		//{
		//	aimData.fAimZ = 1.48f;
		//}
	}
	if (g_BotFuncs->BotSettings.bBotShakingCamera)
	{
		aimData.byteCamMode = 45;
		//cheat_state_text("Aim'in Cam Modu Numarasý: %i", aimData.byteCamMode);
	}
	else if(g_BotFuncs->BotSettings.bBotShakingCamera2)
	{
		aimData.byteCamMode = 34;
	}
	if (g_BotFuncs->BotSettings.bBotInvalidAimZ)
	{
		aimData.fAimZ = sqrt((float)-1);
	}

	if (g_BotFuncs->BotSettings.bRemovePlayerCrasher)
	{
		aimData.byteCamMode = 34; // Aslýnda 45 - Actually 45
	}
 
	if (set.Bots.BotCrasherType == BOT_CRASHER_TYPE_DETONATOR) // Eðer Detonator Crasheri seçtiyse...
	{
		aimData.byteCamMode = 34;
		/*cheat_state_text("Aim Verisi okundu.");*/
	}

	//g_BotFeatures->WriteAimSync(&aimData);
	RakNet::BitStream bsAim;
	bsAim.Write((BYTE)ID_AIM_SYNC);
	bsAim.Write((PCHAR)& aimData, sizeof(stAimData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsAim, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void CBotFuncs::OL_Bot_Send_OnFoot(const float *fPos, const float *fSpeed, bool bFake, uint16_t sSurfingVehicleID, float *fSurfPos)
{

	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	if (bFake)
	{
		memcpy(&OnFootData,
			&g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->onFootData, sizeof(stOnFootData));
	}
	else
	{
		memcpy(&OnFootData, &g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));

	}
	vect3_copy(fPos, OnFootData.fPosition);
	vect3_copy(fSpeed, OnFootData.fMoveSpeed);
	if (BotSettings.bCopyHealth)
	{
		if (OnFootData.byteHealth > 100)
			OnFootData.byteHealth = 100;
	}
	else
	{
		OnFootData.byteHealth = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
	}

	if (!BotSettings.bCopyArmor)
		OnFootData.byteArmor = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
	if (g_BotFuncs->BotSettings.bRandAnim)
	{
		short sRandAnimationID[5] = { 972, 973, 974, 975, 977 };
		OnFootData.sCurrentAnimationID = sRandAnimationID[random(0, sizeof(sRandAnimationID))];
		OnFootData.sAnimFlags = sRandAnimationID[random(0, sizeof(sRandAnimationID))];
		//Log("Bot Random Anim %s -> %i", OnFootData.sCurrentAnimationID, OnFootData.sCurrentAnimationID);
	}
	if (g_BotFuncs->BotSettings.bRandomQuaternions)
	{
		OnFootData.fQuaternion[0] = random_float(-1, 1);
		OnFootData.fQuaternion[1] = random_float(-1, 1);
		//cheat_state_text("QUAT X: %f", OnFootData.fQuaternion[0]);
		OnFootData.fQuaternion[2] = random_float(-1, 1);
		OnFootData.fQuaternion[3] = random_float(-1, 1);
	}
	else if (g_BotFuncs->BotSettings.bUpsideDown)
	{
		OnFootData.fQuaternion[0] = 0;
		OnFootData.fQuaternion[1] = 1;
		OnFootData.fQuaternion[2] = 0;
		OnFootData.fQuaternion[3] = 0;
	}
	else if (g_BotFuncs->BotSettings.bTwistMode)
	{
		static float fRotation = 0.0f;

		OnFootData.fQuaternion[0] = cosf(fRotation);
		OnFootData.fQuaternion[3] = sinf(fRotation);
		if (g_BotFuncs->BotSettings.bCopyWeapon) // Eðer Copy weapon açýksa
			g_BotFuncs->BotSettings.bCopyWeapon = false; //  kapatacak iþte.. sýkýntý çýkmasýný istemiyorum..
		OnFootData.byteCurrentWeapon = 46;

		static DWORD timer = 0;
		if (GetTickCount() - timer > 15)
		{
			fRotation += 1.0f;
			if (fRotation >= 360.0f) fRotation = 0.0f;

			timer = GetTickCount();
		}
		static DWORD timer2 = 0;
		if (GetTickCount() - timer2 > 15)
		{
			OnFootData.sUpDownKeys = 128;
			/*if (g_BotFuncs->BotSettings.byteTwistModeWeaponID == 46)
			{
				OnFootData.sCurrentAnimationID = 0x3C5;
				OnFootData.sAnimFlags = 0x1901;
			}*/
			OnFootData.sCurrentAnimationID = 0x3C5;
			OnFootData.sAnimFlags = 0x1901;
			timer2 = GetTickCount();
		}
	}

	if (g_BotFuncs->BotSettings.bRemovePlayerCrasher)
	{
		OnFootData.sKeys = 128;
		OnFootData.byteCurrentWeapon = 40;
		OnFootData.sUpDownKeys = 128;
		OnFootData.sLeftRightKeys = 128;
	}
 
	if (set.Bots.BotCrasherType == BOT_CRASHER_TYPE_DETONATOR)
	{
		OnFootData.sKeys = 128;
		OnFootData.byteCurrentWeapon = 40;
		OnFootData.sUpDownKeys = 128;
		OnFootData.sLeftRightKeys = 128;
	}
	if (g_BotFuncs->BotSettings.bSpinBot)
	{
		static float fRotation = 0.0f;
		if (/*!g_BotFuncs->BotSettings.bCopyWeapon || */g_Players->pLocalPlayer->byteCurrentWeapon == 0) // Eðer copy weapon açýk deðilse veya benim adamýn elinde silah YOKSA.
		{
			OnFootData.fQuaternion[0] = g_Players->pLocalPlayer->onFootData.fQuaternion[0];
			OnFootData.fQuaternion[3] = g_Players->pLocalPlayer->onFootData.fQuaternion[3];
		}
		else
		{
			OnFootData.fQuaternion[0] = cosf(fRotation);
			OnFootData.fQuaternion[3] = sinf(fRotation);
		}
		
		static DWORD timer = 0;
		if (GetTickCount() - timer > 0) // 95'ten 0'a indirildi.
		{
			fRotation += 1.0f;
			if (fRotation >= 360.0f) fRotation = 0.0f;

			timer = GetTickCount();
		}

		static DWORD timer2 = 0;
		if (GetTickCount() - timer2 > 0) // 250'den 0'a indirildi.
		{
			OnFootData.sUpDownKeys = 128;

			timer2 = GetTickCount();
		}
	}
	if (!BotSettings.bCopyWeapon)
		OnFootData.byteCurrentWeapon = 0;

	if (sSurfingVehicleID != 0)
	{
		vect3_copy(fSurfPos, OnFootData.fSurfingOffsets);
	}

	RakNet::BitStream bsOnFoot;
	bsOnFoot.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFoot.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsOnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	vect3_copy(OnFootData.fPosition,
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].
		fLastOnFootPos);
	vect4_copy(OnFootData.fQuaternion,
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].
		fLastOnFootQuat);
}

void CBotFuncs::OL_Bot_Send_Passenger(bool bFake)
{
	stPassengerData PassengerData;
	memset(&PassengerData, 0, sizeof(stPassengerData));
	if (bFake)
	{
		PassengerData.sVehicleID =
			g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			inCarData.sVehicleID;
		PassengerData.byteSeatID = BotSettings.CurrentClientID + 1;
		PassengerData.byteHealth =
			g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			inCarData.bytePlayerHealth;
		PassengerData.byteArmor =
			g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			inCarData.byteArmor;
		PassengerData.byteCurrentWeapon =
			g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->pPlayerData->
			inCarData.byteCurrentWeapon;
		vect3_copy(g_Players->pRemotePlayer[BotCheats->Target_PlayerID]->
			pPlayerData->inCarData.fPosition, PassengerData.fPosition);
	}
	else
	{
		PassengerData.sVehicleID =
			g_Players->pLocalPlayer->inCarData.sVehicleID;
		PassengerData.byteSeatID = BotSettings.CurrentClientID + 1;
		PassengerData.byteHealth =
			g_Players->pLocalPlayer->inCarData.bytePlayerHealth;
		PassengerData.byteArmor = g_Players->pLocalPlayer->inCarData.byteArmor;
		PassengerData.byteCurrentWeapon =
			g_Players->pLocalPlayer->inCarData.byteCurrentWeapon;
		vect3_copy(g_Players->pLocalPlayer->inCarData.fPosition,
			PassengerData.fPosition);
	}

	if (BotSettings.bCopyHealth)
	{
		if (PassengerData.byteHealth > 100)
			PassengerData.byteHealth = 100;
	}
	else
	{
		PassengerData.byteHealth =
			g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
	}

	if (!BotSettings.bCopyArmor)
		PassengerData.byteArmor =
		g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;

	if (!BotSettings.bCopyWeapon)
		PassengerData.byteCurrentWeapon = 0;


	RakNet::BitStream bsPassenger;
	bsPassenger.Write((BYTE)ID_PASSENGER_SYNC);
	bsPassenger.Write((PCHAR)& PassengerData, sizeof(stPassengerData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->
		Send(&bsPassenger, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

}
void CBotFuncs::OL_Bot_Send_Command(uint8_t uiClientID, const char *szMessage, ...)
{
	va_list ap;
	//char BotYazi[50];

	char string[256];

	va_start(ap, szMessage);
	vsnprintf(string, sizeof(string), szMessage, ap);
	va_end(ap);
	if (string[0] == '/') // Eðer string'in içinde / varsa --- eng: if string is have /
	{
		// this will work just fine 
		// only one thing you have to change is data type of "len" variable
		// BYTE = 1 byte
		// but RPC_ServerCommand takes len in 4 byte format (int)
		// that's why you have to change BYTE len to int len
		int len = strlen(string);
		RakNet::BitStream Params;
		Params.Write(len); // see? now it takes int variable
		Params.Write(string, len);
		g_BotFuncs->OL_Bot_SendRPC(uiClientID, RPC_ServerCommand, Params, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false);
	}
}
 
void CBotFuncs::OL_Bot_PMFlooder(uint8_t uiClientID)
{
	DWORD s = GetTickCount();
	static DWORD l = 0;
	if (s - l > 100)
	{
		switch (set.Bots.botpmfloodertype)
		{
		case 1: // 1
		{
					char GenerateRandomAllChars[47 + 1];
					generate_random_allchars(GenerateRandomAllChars, 47);
					g_BotFuncs->OL_Bot_Send_Command(uiClientID, "/pm %d %s", set.Bots.botpmflooderhedef, GenerateRandomAllChars);
		}
			break;
		case 2: // 2
		{
					char GenerateRandomBinary[47 + 1];
					GenerateRandom_Only_0_1(GenerateRandomBinary, 47);
					g_BotFuncs->OL_Bot_Send_Command(uiClientID, "/pm %d %s", set.Bots.botpmflooderhedef, GenerateRandomBinary);
		}
			break;
		case 3: // 3
		{
					char GenerateOnlyNumbers[47 + 1];
					GenerateRandom_Only_0_9(GenerateOnlyNumbers, 47);
					g_BotFuncs->OL_Bot_Send_Command(uiClientID, "/pm %d %s", set.Bots.botpmflooderhedef, GenerateOnlyNumbers);
		}
			break;
		case 4:
		{
				  g_BotFuncs->OL_Bot_Send_Command(uiClientID, "/pm %d %s", set.Bots.botpmflooderhedef, set.Bots.RAKNET_BOT_PM_Flooder_Text);
		}
			break;
		default:
			break;
		}
	}
}
void CBotFuncs::OL_Bot_ChatFlooder(uint8_t uiClientID)
{

	//char random[set.Bot_Yazi_Hane_Sayisi + 1];
	char random[6 + 1];
	//gen_random(random, 5);
	switch (set.Bots.Bot_ChatFlooder_Text_Type)
	{
	case 1: // Rastgele Yeni karakterler[LAG] yapan cinsten.
	{
		generate_random_new_characters(random, set.Bots.RAKNET_BOT_Flooder_Letter_Length);
		g_BotFuncs->OL_Bot_Say(uiClientID, "-+= %s %s %s =+-", random, set.Bots.RAKNET_BOT_Chat_Text, random);
	}
		break;
	case 2: // Rastgele Binary
	{
		GenerateRandom_Only_0_1(random, set.Bots.RAKNET_BOT_Flooder_Letter_Length);
		g_BotFuncs->OL_Bot_Say(uiClientID, "-+= %s %s %s =+-", random, set.Bots.RAKNET_BOT_Chat_Text, random);
	}
		break;
	case 3: // Rastgele Random sayý 0-9
	{
		GenerateRandom_Only_0_9(random, set.Bots.RAKNET_BOT_Flooder_Letter_Length);
		g_BotFuncs->OL_Bot_Say(uiClientID, "-+= %s %s %s =+-", random, set.Bots.RAKNET_BOT_Chat_Text, random);
	}
		break;
	case 4: // Hepsi.
	{
		generate_random_allchars(random, set.Bots.RAKNET_BOT_Flooder_Letter_Length);
		g_BotFuncs->OL_Bot_Say(uiClientID, "-+= %s %s %s =+-", random, set.Bots.RAKNET_BOT_Chat_Text, random);
	}
		break;
	default:
		break;
	}
}

void CBotFuncs::OL_Send_Death(uint16_t iClientID, uint16_t KillerID, uint16_t WeaponID)
{
	RakNet::BitStream bsSend;
	bsSend.Write(KillerID);
	bsSend.Write(WeaponID);
	g_BotFuncs->OL_Bot_SendRPC(iClientID, RPC_Death, bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, false);
}

void CBotFuncs::BotRollCrasher()
{
	uint16_t iClientID;
	if (set.Bots.iRollCrasherBotID > BotSettings.CurrentClientID) // Eðer oyuna baðlanan bot yoksa veya yüksek id girerse crash yemeyi önlemeye yönelik bir if þartý.
		return cheat_state_text("Wrong Bot ID! Try to do it: ZERO -> 0");
	if (set.Bots.bUseRollCrasherBotID)
		iClientID = set.Bots.iRollCrasherBotID;
	else
		iClientID = BotSettings.CurrentClientID;
	static DWORD tick = 100;
	DWORD now_tick = GetTickCount();
	if (now_tick - tick > 100)
	{
		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;

		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NO_BE_PROTECT |
				VEHICLE_NOT_FRIEND |
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_CLOSEST |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;
		float fPos[3];
		float fRoll[3] = { 9910000000000.0F, 9910000000000.0F, 991000000000.0F };
		fPos[0] += 5.0;
		vect3_copy(&self->base.matrix[12], fPos);
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (self->state == CHEAT_STATE_ACTOR)
			{
				g_BotFuncs->BotClient[iClientID].pBotData->SendFakeUnoccupiedSyncData(iClientID, getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
				g_BotFuncs->BotClient[iClientID].pBotData->SendEnterPlayerVehicle(iClientID, getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
				g_BotFuncs->BotClient[iClientID].pBotData->SendExitPlayerVehicle(iClientID, getSAMPVehicleIDFromGTAVehicle(vehicle));
			}
		}
		tick = now_tick;
	}
}
 
void CBotFuncs::BotInvalidFPSCrasher(uint16_t uiClientID)
{
	static DWORD tick = 25;
	float fRoll[3] = { -5000.0F, -5000.0F, -5000.0F };
	DWORD now_tick = GetTickCount();
	if (now_tick - tick > 25)
	{
		tick = now_tick;

		actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		if (!self)
			return;

		vehicle_info* vehicle =
			GetVehicleInfoStandart(
				VEHICLE_NO_BE_PROTECT |
				VEHICLE_NOT_FRIEND |
				VEHICLE_NOT_OCCUPIED |
				VEHICLE_NOT_CLOSED,
				VEHICLE_CLOSEST |
				VEHICLE_NOT_MY |
				VEHICLE_ALIVE |
				VEHICLE_NOT_TRAIN);

		if (!vehicle)
			return;

		float fPos[3];

		fPos[0] += 5.0;
		vect3_copy(&self->base.matrix[12], fPos);

		int VehicleID = getSAMPVehicleIDFromGTAVehicle(vehicle);
		//int WeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (self->state == CHEAT_STATE_ACTOR)
			{
				
				cheat_state_text("Roll Value X: %f", fRoll[0]);
				g_BotFuncs->BotClient[uiClientID].pBotData->SendFakeUnoccupiedSyncData(uiClientID, getSAMPVehicleIDFromGTAVehicle(vehicle), 1, fPos, vehicle->speed, vehicle->hitpoints = 1000, &vehicle->base.matrix[0], fRoll);
				tick = now_tick;

				/*g_BotFuncs->BotClient[uiClientID].pBotData->SendEnterPlayerVehicle(uiClientID, getSAMPVehicleIDFromGTAVehicle(vehicle), 1);
				tick = now_tick;
				g_BotFuncs->BotClient[uiClientID].pBotData->SendExitPlayerVehicle(uiClientID, getSAMPVehicleIDFromGTAVehicle(vehicle));
				tick = now_tick;
				g_BotFuncs->BotClient[uiClientID].pBotData->SendFakePassengerSyncData(uiClientID,getSAMPVehicleIDFromGTAVehicle(vehicle), fPos, vehicle->hitpoints, g_Players->pLocalPlayer->byteCurrentWeapon, 1, 128);
				tick = now_tick;*/
			}
		}
	}
}

void CBotFuncs::Bot_Tornado()
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, NULL);
	float fPos[3];
	vect3_copy(&self->base.matrix[4 * 3], fPos);

	static int x = 1;

	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	/* Circle */
	fPos[0] += sinf(19.0f * (float)x) * 27;
	fPos[1] += cosf(19.0f * (float)x) * 27;
	fPos[2] += 8 + tanf(19.0f * (float)x) - 6.0f;

	float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
	fSpeed[2] = 2.0f;
	/*OnFootData.byteHealth = R4nd0m(1, 100);*/
	/*OnFootData.byteCurrentWeapon = R4nd0m(0, 46);*/
	OnFootData.byteCurrentWeapon = 0;
	OnFootData.byteHealth = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
	OnFootData.byteArmor = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fArmour;
	OnFootData.fPosition[0] = fPos[0];
	OnFootData.fPosition[1] = fPos[1];
	OnFootData.fPosition[2] = fPos[2];
	OnFootData.fMoveSpeed[0] = fSpeed[0];
	OnFootData.fMoveSpeed[1] = fSpeed[1];
	OnFootData.fMoveSpeed[2] = fSpeed[2];
	//cheat_state_text("WORKS!");
	RakNet::BitStream bsSendData;
	bsSendData.Write((BYTE)ID_PLAYER_SYNC);
	bsSendData.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsSendData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	x++;
}
void CBotFuncs::ClassFlooder()
{
	if (g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient == NULL)
		return;
	int ClassID = rand() % (g_SAMP->pSettings->iClassesAvailable - 1);

	RakNet::BitStream bsSpawnRequest;
	bsSpawnRequest.Write(ClassID);
	OL_Bot_SendRPC(BotSettings.CurrentClientID, RPC_RequestClass, bsSpawnRequest, HIGH_PRIORITY,
		RELIABLE, 0, FALSE);

	RakNet::BitStream bsSendRequestSpawn;
	OL_Bot_SendRPC(BotSettings.CurrentClientID, RPC_RequestSpawn, bsSendRequestSpawn,
		HIGH_PRIORITY, RELIABLE, 0, FALSE);
	RakNet::BitStream bsSendSpawn;
	OL_Bot_SendRPC(BotSettings.CurrentClientID, RPC_Spawn, bsSendSpawn, HIGH_PRIORITY, RELIABLE,
		0, FALSE);
}
void CBotFuncs::Bot_Tornado2()
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, NULL);
	float fPos[3];
	vect3_copy(&self->base.matrix[4 * 3], fPos);

	static int x = 1;
	static int radius_counter = 1;
	static int height_counter = 1;

	if (radius_counter > 70) radius_counter = 1;
	if (height_counter > 100) height_counter = 1;
	stOnFootData OnFootData;
	memset(&OnFootData, 0, sizeof(stOnFootData));
	/* Circle */
	fPos[0] += sinf(19.0f * (float)x) * radius_counter;
	fPos[1] += cosf(19.0f * (float)x) * radius_counter;
	fPos[2] += height_counter;

	float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
	fSpeed[2] = 1.0f;
	/*OnFootData.byteCurrentWeapon = R4nd0m(0, 46);*/
	OnFootData.byteCurrentWeapon = 0;
	OnFootData.byteHealth = g_BotFuncs->BotClient[BotSettings.CurrentClientID].fHealth;
	OnFootData.fPosition[0] = fPos[0];
	OnFootData.fPosition[1] = fPos[1];
	OnFootData.fPosition[2] = fPos[2];
	OnFootData.fMoveSpeed[0] = fSpeed[0];
	OnFootData.fMoveSpeed[1] = fSpeed[1];
	OnFootData.fMoveSpeed[2] = fSpeed[2];
	/*cheat_state_text("WORKS!");*/
	/*OnFootData.byteHealth = R4nd0m(1, 100);*/
	RakNet::BitStream bsSendData;
	bsSendData.Write((BYTE)ID_PLAYER_SYNC);
	bsSendData.Write((PCHAR)& OnFootData, sizeof(stOnFootData));
	g_BotFuncs->BotClient[BotSettings.CurrentClientID].pRakClient->Send(&bsSendData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	x++;
	radius_counter++;
	height_counter++;
}
CBotFuncs::~CBotFuncs()
{
	for (int i = g_BotFuncs->BotSettings.ClientCount; i > 0; i--)
		g_BotFuncs->OL_Delete_Bot();

	delete[] BotClient;

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		delete[] uiIsBot[i];
	delete[] uiIsBot;

	delete g_BotFuncs;

}
#endif