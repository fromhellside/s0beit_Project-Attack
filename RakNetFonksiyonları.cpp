#include "main.h"

void RF_FakeKick()
{
	if (cheat_state->RakNet.iFakeKick)
	{
	//	addMessageToChatWindow("You are kicked from server By Fake Kick function.");
		if (g_RakClient) g_RakClient->SendEnterVehicleNotification(0xFFFF, 0);
	}
}
void RF_FakeLeave()
{
	if (cheat_state->RakNet.iFakeLeave)
	{
		//addMessageToChatWindow("You have disconnected from server by Fake Leave function.");
		disconnect(500);
	}
}
void RF_FakeTimeout()
{
	if (cheat_state->RakNet.iFakeTimeout)
	{
		//addMessageToChatWindow("You have disconnected from server by Fake Timeout function.");
		disconnect(0);
	}
}
void RN_Fonksiyonlari(void)
{
	RF_FakeKick();
	RF_FakeLeave();
	RF_FakeTimeout();
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	ZeroPingExploit();
#endif
}