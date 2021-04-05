#include "main.h"
extern struct gui *menu_titlebar_background;
extern struct gui *menu_background;
extern struct gui *menu_selected_item_bar;
extern struct gui *menu_selected_item_text;

extern struct gui *gta_hp_bar;
extern struct gui *gta_money_hud;

TwBar *twBar_MainMenu;
TwBar *twBar_GeneralCheats;
TwBar *twBar_CarCheats;
TwBar *twBar_FloodCheats;
TwBar *twBar_AimFuncs;
TwBar *twBar_TrollFuncs;
TwBar *twBar_FakeKill;
TwBar *twBar_RakNetCheats;
TwBar* twBar_weaponCheats;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
TwBar *twBar_Bots;
#endif
TwBar *twBar_Interface;

void runNewMenu()
{
	if (KEY_PRESSED(set.ATB_key))
	{
		if (gta_menu_active()) return;
		if (g_SAMP != NULL) if (g_Scoreboard->iIsEnabled) return;

		cheat_state->_generic.bShowRapidManager ^= 1;
		if (cheat_state->_generic.bShowRapidManager)
			toggleATBCursor(true);
		else
			toggleATBCursor(false);
	}
}
DWORD dwLastUpdate_MenuPopulator;
void menuPopulator()
{
	if (dwLastUpdate_MenuPopulator < (GetTickCount() - 200))
	{
		dwLastUpdate_MenuPopulator = GetTickCount();
	}
}
DWORD menuUpdateHook_origfunc = 0x50B8F0;
void _declspec(naked) menuUpdateHook()
{
	_asm call menuUpdateHook_origfunc
	_asm pushad
	menuPopulator();
	_asm popad
	_asm retn
}
void TW_CALL newcheatsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_GeneralCheats))
		TwMaximizeBar(twBar_GeneralCheats);
	else
		TwMinimizeBar(twBar_GeneralCheats);
}
void TW_CALL carcheatsMenuLinker(void*)
{
	if (TwIsBarMinimized(twBar_CarCheats))
		TwMaximizeBar(twBar_CarCheats);
	else
		TwMinimizeBar(twBar_CarCheats);
}

void TW_CALL newAimFuncsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_AimFuncs))
		TwMaximizeBar(twBar_AimFuncs);
	else
		TwMinimizeBar(twBar_AimFuncs);
}
void TW_CALL newWeaponFuncsLinker(void*)
{
	if (TwIsBarMinimized(twBar_weaponCheats))
		TwMaximizeBar(twBar_weaponCheats);
	else
		TwMinimizeBar(twBar_weaponCheats);
}
void TW_CALL newTrollFuncMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_TrollFuncs))
		TwMaximizeBar(twBar_TrollFuncs);
	else
		TwMinimizeBar(twBar_TrollFuncs);
}
void TW_CALL floodcheatsMenuLinker(void*)
{
	if (TwIsBarMinimized(twBar_FloodCheats))
		TwMaximizeBar(twBar_FloodCheats);
	else
		TwMinimizeBar(twBar_FloodCheats);
}
void TW_CALL newFakeKillMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_FakeKill))
		TwMaximizeBar(twBar_FakeKill);
	else
		TwMinimizeBar(twBar_FakeKill);
}
void TW_CALL rakNetFunctionsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_RakNetCheats))
		TwMaximizeBar(twBar_RakNetCheats);
	else
		TwMinimizeBar(twBar_RakNetCheats);
}

//void TW_CALL newPacketLoggerMenuLinker(void*)
//{
//	if (TwIsBarMinimized(twBar_PacketLoggers))
//		TwMaximizeBar(twBar_PacketLoggers);
//	else
//		TwMinimizeBar(twBar_PacketLoggers);
//}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
void TW_CALL botsMenuLinker(void *)
{
	if (TwIsBarMinimized(twBar_Bots))
		TwMaximizeBar(twBar_Bots);
	else
		TwMinimizeBar(twBar_Bots);
}
#endif

void TW_CALL interfaceMenu_GetInterfaceColor(void *value, void *clientData)
{
	int iColorID = (int)clientData;

	switch (iColorID)
	{
	case 1:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_titlebar_background->alpha, menu_titlebar_background->red, menu_titlebar_background->green, menu_titlebar_background->blue);
		break;

	case 2:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_background->alpha, menu_background->red, menu_background->green, menu_background->blue);
		break;

	case 3:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_selected_item_bar->alpha, menu_selected_item_bar->red, menu_selected_item_bar->green, menu_selected_item_bar->blue);
		break;

	case 4:
		*(DWORD*)value = D3DCOLOR_ARGB(menu_selected_item_text->alpha, menu_selected_item_text->red, menu_selected_item_text->green, menu_selected_item_text->blue);
		break;

	case 5:
		*(DWORD*)value = D3DCOLOR_ARGB(gta_hp_bar->alpha, gta_hp_bar->red, gta_hp_bar->green, gta_hp_bar->blue);
		break;

	case 6:
		*(DWORD*)value = D3DCOLOR_ARGB(gta_money_hud->alpha, gta_money_hud->red, gta_money_hud->green, gta_money_hud->blue);
		break;

	case 7:
		*(DWORD*)value = sampGetRadarColor(1); // sampGetRadarColor
		break;

	case 8:
		*(DWORD*)value = sampGetRadarColor(2);
		break;

	case 9:
		*(DWORD*)value = sampGetRadarColor(3);
		break;
	}
}
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
void TW_CALL botsMenu_addBot(void *)
{
	g_BotFuncs->OL_Add_Bot();
}
void TW_CALL botsMenu_delBot(void *)
{
	g_BotFuncs->OL_Delete_Bot();
}
void TW_CALL botsaySomething(void*)
{
	g_BotFuncs->OL_Bot_Say(set.Bots.iBotID_for_Message, set.Bots.BotMessage);
}
void TW_CALL botsMenu_SpawnAll(void*)
{
	for (int i = g_BotFuncs->BotSettings.ClientCount - 1; i >= 0; i--)
		g_BotFuncs->OL_Spawn_Bot(i);
}
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
//void TW_CALL zombieConnection(void*)
//{
//	g_BotClient->ZombieConnection(BotSet);
//}
#endif
#endif
void TW_CALL AreYouRageCheater(void*)
{
	set.silentAim.iHitChanceValue = 100;
	cheat_state->Silah.iSpinBotType = ID_SPINTYPE_DOWN;
	set.aimCheatsSettings.iSyncSpinBotTypes = ID_SPINTYPE_DOWN;
	set.silentAim.bFriendFilter = true;
	set.silentAim.bAFKFilter = true;
	set.silentAim.bAliveFilter = true;
	set.silentAim.bVisibleFilter = false;
	//addMessageToChatWindow("Projenin Aimbot Faktörleri Rage olacak þekilde ayarlandý, Ýyi eðlenceler!{00FF00} %s", getPlayerName(g_Players->sLocalPlayerID));
}
void TW_CALL killAll(void*)
{
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			g_RakClient->SendDamage(i, 0, 4, 3);
			g_RakClient->SendDamage(i, 1833.331542, 4, 3);
		}
	}
}
void TW_CALL AreYouLegitCheater(void*)
{ 
	set.silentAim.iHitChanceValue = random(15,50);
	set.silentAim.bFriendFilter = true;
	set.silentAim.bAFKFilter = true;
	set.silentAim.bAliveFilter = true;
	set.silentAim.bVisibleFilter = true;
	//addMessageToChatWindow("Projenin Aimbot Faktörleri Legit olacak þekilde ayarlandý, Ýyi eðlenceler,{00FF00} %s", getPlayerName(g_Players->sLocalPlayerID));
}
void TW_CALL skyCrasher(void*)
{
	RakNet::BitStream CrashServer;
	CrashServer.Write((uint8_t)200); // 207 crash
	CrashServer.Write((uint16_t)NAN);
	g_RakClient->Send(&CrashServer, SYSTEM_PRIORITY, UNRELIABLE, 0);
}
void TW_CALL fkick(void*)
{
	if (g_RakClient) g_RakClient->SendEnterVehicleNotification(0xFFFF, 0);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn. \n Not: Kick/Ban sebebiyle çýkýþ yaptýn.");
}
void TW_CALL fleave(void*)
{
	disconnect(500);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn.");
}
void TW_CALL ftimeout(void*)
{
	disconnect(0);
	//addMessageToChatWindow("Sunucudan baþarýyla çýkýþ yaptýn. \n Not: Timeout/Crash sebebiyle çýkýþ yaptýn.");
}
void TW_CALL weaponMenu_GiveWeaponWithAmmo(void*)
{
	pPedSelf->GiveWeapon((eWeaponType)set.WeaponCheats.GiveWeapon_WeaponID, set.WeaponCheats.GiveWeapon_Ammo_Amount);
}
void TW_CALL reconnect(void*)
{
	if (GetTickCount() - set.rejoin_delay > cheat_state->_generic.rejoinTick)
	{
		restartGame();
		disconnect(500);
	//	cheat_state_text("Sunucuya tekrar baðlanýlýyor...");
		cheat_state->_generic.rejoinTick = GetTickCount();
	}
}
void TW_CALL silahVerNedir(void*)
{
	/*addMessageToChatWindow("Silah hilesi bazý oyun sunucularda ban sebebi olabilir. \n Lütfen, 'Silah hilesi Geçirme' yöntemlerinden birini kullanmayý düþünün.");*/
	addMessageToChatWindow("Silah hilesi bazý oyun sunucularda ban sebebi olabilir.");
}
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
void TW_CALL silahSwitchNedir(void*)
{
	addMessageToChatWindow("Silah Switch hilesi, bazý silahlar arasýnda geçiþ yaparak daha hýzlý \n ateþ etmeni saðlayan bir hiledir.");
	addMessageToChatWindow("Silah Slotlarý: \n 0-)Yumruk 1-)Ateþ edilemeyen silahlar. \n 2-)Tabancalar \n 3-)Pompalý Tüfekler");
	Sleep(100);
	addMessageToChatWindow("4-)Hafif taramalýlar. \n 5-)AK-47 & M4 \n 6-)Cuntgun & Sniper");
}
void TW_CALL silentAimNedir(void*)
{
	addMessageToChatWindow("Silent Aim isabet þansý: Silent Aimbot kullanýrken her ateþ ettiðin merminin isabet olmamasýdýr.");
	addMessageToChatWindow("Not: {00FF00}Adminlerin ve sunucu anti hilesinin fark etmesini önlemek için yapýldý.");
	addMessageToChatWindow("Legit için 15-40 Arasýnda bir deðer seçin.");
	addMessageToChatWindow("Full Rage için 100 {00FF00}kullanabilirsiniz.");
}
/*
		Filtreler ve ne iþe yaradýklarý:
		Mesafe Filtresi: Mevcut silahýnýn uzaðýnda atýþ yapmaný saðlar.
		Takým Filtresi: Sunucu içerisinde bir birliðe veya ekibe girdiðin zaman, aimbot, ekip arkadaþlarýna niþan almaz.
		Renk Filtresi: Ayný isim renginde olduðun arkadaþlarýna, aimbot niþan almaz.
		Skin Filtresi: Seninle ayný skin olan arkadaþlarýna aimbot niþan almaz.
		Görünen Hedef Filtresi: Görebildiðin oyuncuya niþan alýrsýn sadece, duvar arkasýndakilere alamazsýn!
		AFK Filtresi: Aimbot, AFK olan oyunculara niþan almaz.
		Ölü Filtresi: Aimbot, Yerde yatan ölülere niþan almaz.
		NPC Filtresi: Þimdilik kalsýn.
		Admin Filtresi: Þimdilik kalsýn.
		Arkadaþ Filtresi: Þimdilik Kalsýn.
*/
void TW_CALL silentAimAyarlariNedir(void*)
{
	addMessageToChatWindow("Silent Aim Filtreleri:");
	addMessageToChatWindow("Mesafe: Þuanki silahýnýn mevcut mesafesinden uzaðýnda atýþ yapmaný saðlar.");
	addMessageToChatWindow("Takým: Sunucu içerisinde bir birliðe veya ekibe girdiðin zaman, aimbot, ekip arkadaþlarýna niþan almaz.");
	Sleep(10); 
	addMessageToChatWindow("Renk: Ayný isim renginde olduðun oyunculara, aimbot niþan almaz.");
	addMessageToChatWindow("Skin: Ayný skin olduðun oyunculara, aimbot niþan almaz.");
	Sleep(10);
	addMessageToChatWindow("Görünen Hedef: Görebildiðin oyuncuya niþan alýrsýn sadece, duvar arkasýndakilere alamazsýn.");
	addMessageToChatWindow("AFK Filtresi: Aimbot, AFK olan oyunculara niþan almaz. \n Ölü Filtresi:Aimbot, Yerde yatan ölülere niþan almaz.");
	addMessageToChatWindow("Dost: Görüþ hileleri kategorisindeki, 'Dostlar listesi' açýkken çalýþýr. | Dostlara niþan almaz.");
	addMessageToChatWindow("Admin: Görüþ hileleri kategorisindeki, 'Admin listesi' açýkken çalýþýr. | Adminlere niþan almaz.");
	//addMessageToChatWindow("NPC Filtresi:");
}
void TW_CALL aracKontrolNedir(void*)
{
	addMessageToChatWindow("{FF0000}Araç Kontrol, bazý sunucularda fixlenmiþ olabilir.");
	addMessageToChatWindow("{00FF00}Çalýþmasý için araç içinde olman gerek ve hedefin araçta olmasý gerek.");
}
void TW_CALL aracLagBilgi(void*)
{
	addMessageToChatWindow("Bu faktör geliþtirici bilgisi gerektiriyor, otomatik ayarlarý kullanmayý göz önünde bulundurun.");
	addMessageToChatWindow("Sunucudaki, yakýnýndaki araçlarý iç içe toplar ve FPS düþürür.");
}
void TW_CALL dostEkle(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteFriendID) || g_Players->iIsListed[set.friendFilters.iAddDeleteFriendID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");
	outputFile.open(filename, std::fstream::out | std::fstream::app);

	if (g_Players->pRemotePlayer[set.friendFilters.iAddDeleteFriendID]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[set.friendFilters.iAddDeleteFriendID]->strPlayerName.c_str(); //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close();
	addMessageToChatWindow("%s[ID:%d] isimli oyuncu {00FF00}Arkadaþlar listesine eklendi.", nick.c_str(), set.friendFilters.iAddDeleteFriendID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}
void TW_CALL adminEkle(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteAdminID) || g_Players->iIsListed[set.friendFilters.iAddDeleteAdminID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	std::ofstream outputFile;
	char filename[512];
	std::string nick;
	std::string del;
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");
	outputFile.open(filename, std::fstream::out | std::fstream::app);
	if (g_Players->pRemotePlayer[set.friendFilters.iAddDeleteAdminID]->strPlayerName.c_str()) // Default : if (g_Players->pRemotePlayer[playerid]->iNameAllocated <= 0xF)
	{
		nick = g_Players->pRemotePlayer[set.friendFilters.iAddDeleteAdminID]->strPlayerName; //  Default : nick = g_Players->pRemotePlayer[playerid]->szPlayerName;
	}
	outputFile << nick << "\n";
	outputFile.close(); // close it.
	addMessageToChatWindow("%s [ID:%d] isimli oyuncu {00FF00}Adminler listesine eklendi. ", nick.c_str(), set.friendFilters.iAddDeleteAdminID);
}
void TW_CALL adminSil(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteAdminID) || g_Players->iIsListed[set.friendFilters.iAddDeleteAdminID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	char filename[512];
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "AdminListesi.ini");

	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	// That should be it. Let's test. wait

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(set.friendFilters.iAddDeleteAdminID)))
			continue;

		nicklist.push_back(nick);
	}

	inputFile.close();

	std::ofstream outputFile; // good song xd xD
	outputFile.open(filename, std::ios::trunc);

	for (int i = 0; i < (int)nicklist.size(); i++)
	{
		nick = nicklist[i];
		outputFile << nick << "\n";
	}

	outputFile.close();
	addMessageToChatWindow("%s [ID:%d] isimli oyuncu Adminler Listesinden {FF0000}SÝLÝNDÝ.", getPlayerName(set.friendFilters.iAddDeleteAdminID), set.friendFilters.iAddDeleteAdminID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}
void TW_CALL dostSil(void*)
{
	if (isBadSAMPPlayerID(set.friendFilters.iAddDeleteFriendID) || g_Players->iIsListed[set.friendFilters.iAddDeleteFriendID] != 1)
		return addMessageToChatWindow("Oyuncu ID'si Hatalý.");

	char filename[512];
	snprintf(filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, "DostListesi.ini");

	std::vector<std::string> nicklist;
	std::ifstream inputFile; // ERROR -> Redefiniton!! good xd
	std::string nick;

	inputFile.open(filename);
	while (inputFile >> nick)
	{
		if (!strcmp(nick.c_str(), getPlayerName(set.friendFilters.iAddDeleteFriendID)))
			continue;

		nicklist.push_back(nick);
	}

	inputFile.close();

	std::ofstream outputFile; // good song xd xD
	outputFile.open(filename, std::ios::trunc);

	for (int i = 0; i < (int)nicklist.size(); i++)
	{
		nick = nicklist[i];
		outputFile << nick << "\n";
	}

	outputFile.close();
	addMessageToChatWindow("%s [ID: %d] Nick nameli oyuncu {00FF00} Arkadaþlar listesinden SÝLÝNDÝ.", getPlayerName(set.friendFilters.iAddDeleteFriendID), set.friendFilters.iAddDeleteFriendID);
	/* Eðer girilen nick listede varsa listeden silsin o nicki. */
}
void TW_CALL carlagAyarYap(void*)
{
	set.CarCheats.CarLagger_Coords[0] = 7.5f;
	set.CarCheats.CarLagger_Coords[1] = 2.0f;
	addMessageToChatWindow("{00FF00}Ayarlama iþlemi tamamlandý.");
}
void TW_CALL aracRenkBilgi(void*)
{
	addMessageToChatWindow("{FF0000}Gecikme sürelerini arttýrsanýz, aracýn renkleri daha yavaþ deðiþir.");
	addMessageToChatWindow("{00FF00}Not:1000MS = 1 Saniyedir.");
}
void TW_CALL xPosNedir(void*)
{
	addMessageToChatWindow("{FF0000}Eðer Admin veya Dost listesi aktif hale getirildiðinde düzgün bir þekilde");
	addMessageToChatWindow("Görüntülenmiyorsa, Ayarlarý deðiþtirmeyi deneyin. | {FF0000}Aksi takdirde deðiþtirmeyin.");
}
void TW_CALL ipucuver(void*)
{
	int x = random(0, 7);
	/*addMessageToChatWindow("Gecikme sürelerini arttýrsanýz, hileler daha yavaþ çalýþýr.");
	addMessageToChatWindow("Yarýçap deðerlerini arttýrýrsanýz, hileler daha hýzlý ve çaplý çalýþýr.");
	addMessageToChatWindow("Ýpucu: Eðer bir hilenin iþlevini arttýrmak istiyorsan, yarýçap ve hýz deðerlerini arttýrabilirsin!");
	addMessageToChatWindow("Ýpucu: Eðer bir hilenin fark edilme olasýlýðýný düþürmek istiyorsan, gecikme süresini arttýr.");*/
	switch (x)
	{
		case 1:
		{
			addMessageToChatWindow("Tüyo #1:Gecikme sürelerini arttýrsanýz, hileler daha yavaþ çalýþýr.");
		}break;
		case 2:
		{
			addMessageToChatWindow("Tüyo #2:Yarýçap deðerlerini arttýrýrsanýz, hileler daha hýzlý ve çaplý çalýþýr.");
		}break;
		case 3:
		{
			addMessageToChatWindow("Tüyo #3:Eðer bir hilenin fark edilme olasýlýðýný düþürmek istiyorsan, gecikme süresini arttýr.");
		}break;
		case 4:
		{
			addMessageToChatWindow("Tüyo #4:Gökkuþaðý yazýlarýn hýzýný 'Genel Hile Ayarlarý' menüsünden ayarlayabilirsin.");
		}break;
		case 5:
		{
			addMessageToChatWindow("Tüyo #5:Eðer bir hilenin iþlevini arttýrmak istiyorsan, yarýçap ve hýz deðerlerini arttýrabilirsin.");
		}break;
		case 6:
		{
			addMessageToChatWindow("Tüyo #7:Eðer SilentAimi düzgün ayarlamakta sýkýntý yaþýyorsan, \n Legit Ayarlar veya Rage Ayarlar butonlarýmýzý kullanabilirsin.");
		}break;
		default:
		{
			addMessageToChatWindow("Gecikme sürelerini arttýrsanýz, hileler daha yavaþ çalýþýr.");
			addMessageToChatWindow("Yarýçap deðerlerini arttýrýrsanýz, hileler daha hýzlý ve çaplý çalýþýr.");
			addMessageToChatWindow("Ýpucu: Eðer bir hilenin iþlevini arttýrmak istiyorsan, yarýçap ve hýz deðerlerini arttýrabilirsin.");
			addMessageToChatWindow("Ýpucu: Eðer bir hilenin fark edilme olasýlýðýný düþürmek istiyorsan, gecikme süresini arttýr.");
		}break;
	}
	//addMessageToChatWindow("Gecikme sürelerini arttýrsanýz, hileler daha yavaþ çalýþýr.");
	//addMessageToChatWindow("Yarýçap deðerlerini arttýrýrsanýz, hileler daha hýzlý ve çaplý çalýþýr.");
	//addMessageToChatWindow("Ýpucu: Eðer bir hilenin iþlevini arttýrmak istiyorsan, yarýçap ve hýz deðerlerini arttýrabilirsin!");
	//addMessageToChatWindow("Ýpucu: Eðer bir hilenin fark edilme olasýlýðýný düþürmek istiyorsan, gecikme süresini arttýr.");
}
#endif

void TW_CALL interfaceMenu_SetInterfaceColor(const void *value, void *clientData)
{
	int iColorID = (int)clientData;
	DWORD dwColor = *(DWORD*)value;

	BYTE byteA, byteR, byteG, byteB;

	byteA = dwColor >> 24; byteR = (dwColor >> 16) & 0xFF;
	byteG = (dwColor >> 8) & 0xFF; byteB = dwColor & 0xFF;

	if (iColorID == 1)
	{
		menu_titlebar_background->alpha = byteA; menu_titlebar_background->red = byteR;
		menu_titlebar_background->green = byteG; menu_titlebar_background->blue = byteB;
	}
	else if (iColorID == 2)
	{
		menu_background->alpha = byteA; menu_background->red = byteR;
		menu_background->green = byteG; menu_background->blue = byteB;
	}
	else if (iColorID == 3)
	{
		menu_selected_item_bar->alpha = byteA; menu_selected_item_bar->red = byteR;
		menu_selected_item_bar->green = byteG; menu_selected_item_bar->blue = byteB;
	}
	else if (iColorID == 4)
	{
		menu_selected_item_text->alpha = byteA; menu_selected_item_text->red = byteR;
		menu_selected_item_text->green = byteG; menu_selected_item_text->blue = byteB;
	}
	else if (iColorID == 5)
	{
		gta_hp_bar->alpha = byteA; gta_hp_bar->red = byteR;
		gta_hp_bar->green = byteG; gta_hp_bar->blue = byteB;
	}
	else if (iColorID == 6)
	{
		gta_money_hud->alpha = byteA; gta_money_hud->red = byteR;
		gta_money_hud->green = byteG; gta_money_hud->blue = byteB;
	}

	else if (iColorID == 7)
		sampSetRadarColor(1, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	else if (iColorID == 8)
		sampSetRadarColor(2, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	else if (iColorID == 9)
		sampSetRadarColor(3, byteA | (byteB << 8) | (byteG << 16) | (byteR << 24));

	if (iColorID == 5 || iColorID == 6)
		UpdateHUDColors(); // UpdateHUDColors
}

void initializeBarsMenu()
{
	if (memcmp_safe((uint8_t *)0x53EB0D, hex_to_bin("E8DECDFCFF"), 5))
	{
		CDetour api;
		if (api.Create((uint8_t *)((uint32_t)0x53EB0D), (uint8_t *)menuUpdateHook, DETOUR_TYPE_CALL_FUNC, 5) == 0)
			Log("Failed to hook menuUpdateHook.");
	}
	else
		Log("Failed to hook menuUpdateHook (memcmp)");

	TwDefine(" TW_HELP visible=false iconified=true ");
	TwDefine(" GLOBAL fontstyle=fixed ");
	TwDefine(" GLOBAL fontsize=3 ");
	char menuParameters[512];
 
	int iMainMenuPosX = pPresentParam.BackBufferWidth / 2 - 400 / 2;
	int iMainMenuPosY = pPresentParam.BackBufferHeight - 275;
	//int iMainMenuPosY = pPresentParam.BackBufferHeight / 2;

	/*sprintf(menuParameters, " Main_Menu label='~ Project Attack v2.3 Delays/Cheatz ~' color='238 130 238' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", iMainMenuPosX, iMainMenuPosY);*/
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH

#if COMPILE_RINA_RP_CLANS == COMPILE_FOR_WILLSON
	sprintf(menuParameters, " Main_Menu label=' %s ' color='255 0 0' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", M0D_VERSION,iMainMenuPosX, iMainMenuPosY);
#else
	sprintf(menuParameters, " Main_Menu label=` %s ` color='0 0 0' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ",M0D_VERSION,iMainMenuPosX, iMainMenuPosY);
#endif
	TwDefine(menuParameters);
	
	TwAddSeparator(twBar_MainMenu, NULL, NULL);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Cheat_Settings", newcheatsMenuLinker, NULL, " label='Hile Ayarlari' ");

	sprintf(menuParameters, " Cheat_Settings label='Hile Ayarlari' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);
	
	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (445 / 2) - 175;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 175;

	TwAddButton(twBar_MainMenu, "Car_Hacks", carcheatsMenuLinker, NULL, " label='Araç Hileleri: Ayarlar' ");

	sprintf(menuParameters, " Car_Hacks label='Araç Hileleri: Ayarlar' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (125 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Aim_Funcs", newAimFuncsMenuLinker, NULL, " label='Aimbot Ayarlari' ");

	sprintf(menuParameters, " Aim_Funcs label='Aimbot Ayarlari' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (250 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (350 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Weapon_Funcs", newWeaponFuncsLinker, NULL, " label='Silah Hileleri' ");

	sprintf(menuParameters, " Weapon_Funcs label='Silah Hileleri' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Troll_Cheats", newTrollFuncMenuLinker, NULL, " label='Troll Hileler Ayarlar' ");

	sprintf(menuParameters, " Troll_Cheats label='Troll Hileler: Ayarlar' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ",iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Flood_Hacks", floodcheatsMenuLinker, NULL, " label='Chat Flood Ayarlari' ");

	sprintf(menuParameters, " Flood_Hacks label='Chat Flood Ayarlari' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;


	//TwAddButton(twBar_MainMenu, "Fake_Kill", newFakeKillMenuLinker, NULL, " label='Fake Kill Settings' ");

	//sprintf(menuParameters, " Fake_Kill label='~ Fake Kill Settings ~' color='255 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	//TwDefine(menuParameters);

	//iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	//iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "RakNet_Funcs", rakNetFunctionsMenuLinker, NULL, " label='RakNet' ");

	sprintf(menuParameters, " RakNet_Funcs label='RakNet' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
	TwAddButton(twBar_MainMenu, "Bot_Options", botsMenuLinker, NULL, " label='#RakNetBOT Fonksiyonlari' ");

	sprintf(menuParameters, " Bot_Options label='=> RakNet Bot Fonksiyonlari <=' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
#endif

#else

	sprintf(menuParameters, " Main_Menu label='~ Project Attack v4 ~' color='192 255 192' position='%d %d' size='405 235' fontsize='4' iconpos='topright' iconmargin='8 24' valueswidth=150 ", rand() % 255, rand() % 255, rand() % 255, iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	TwAddSeparator(twBar_MainMenu, NULL, NULL);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 150;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 150;

	TwAddButton(twBar_MainMenu, "Cheat_Settings", newcheatsMenuLinker, NULL, " label='Cheats' ");

	sprintf(menuParameters, " Cheat_Settings label='~ Cheats ~' color='192 255 192' position='%d %d' size='405 235' fontsize='6' ", rand() % 255, rand() % 255, rand() % 255, iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Car_Hacks", carcheatsMenuLinker, NULL, " label='Car Cheats' ");

	sprintf(menuParameters, " Car_Hacks label='~ Car Cheats ~' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Aim_Funcs", newAimFuncsMenuLinker, NULL, " label='Aim Funcs/Settings' ");

	sprintf(menuParameters, " Aim_Funcs label='~ Aim Funcs/Settings ~' color='0 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Weapon_Funcs", newWeaponFuncsLinker, NULL, " label='Weapon Cheats' ");

	sprintf(menuParameters, " Weapon_Funcs label='~ Weapon Cheats ~' color='135 206 235' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Troll_Cheats", newTrollFuncMenuLinker, NULL, " label='Troll Funcs/Settings' ");

	sprintf(menuParameters, " Troll_Cheats label='~ Troll Funcs/Settings ~' color='0 0 0' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "Flood_Hacks", floodcheatsMenuLinker, NULL, " label='Chat Operations Settings' ");

	sprintf(menuParameters, " Flood_Hacks label='~ Chat Operations Settings ~' color='34 156 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;


	TwAddButton(twBar_MainMenu, "Fake_Kill", newFakeKillMenuLinker, NULL, " label='Fake Kill Settings' ");

	sprintf(menuParameters, " Fake_Kill label='~ Fake Kill Settings ~' color='255 255 255' position='%d %d' size='405 235' fontsize='6' ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 125;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 125;

	TwAddButton(twBar_MainMenu, "RakNet_Funcs", rakNetFunctionsMenuLinker, NULL, " label='RakNet Settings' ");

	sprintf(menuParameters, " RakNet_Funcs label='~ RakNet Settings ~' color='0 0 55' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
	TwAddButton(twBar_MainMenu, "Bot_Options", botsMenuLinker, NULL, " label='RakNet Bot Functions/Settings' ");

	sprintf(menuParameters, " Bot_Options label='~ RakNet Bot Functions/Settings ~' color='0 0 0' position='%d %d' size='405 235' fontsize='4' alpha=255 alpha='255'  ", iMainMenuPosX, iMainMenuPosY);
	TwDefine(menuParameters);

	iMainMenuPosX = (pPresentParam.BackBufferWidth / 2) - (405 / 2) - 25;
	iMainMenuPosY = (pPresentParam.BackBufferHeight / 2) - (235 / 2) - 25;
#endif

#endif

	//TwAddButton(twBar_GeneralCheats, "Hile ipuclari", ipucuver, NULL, " label='Hile Tüyolari' ");
#if COMPILE_TYPE != COMPILE_TYPE_ENGLISH
	TwType ActorFlyType = TwDefineEnum("FlyType", NULL, 0);
	TwAddVarRW(twBar_GeneralCheats, "Player Fly Type", ActorFlyType, &set.General.Actor_Fly_Type, " label='Uçma Hilesi Türü:' enum='1 { Yüzerek Uçma }, 2 { Düz Uçma }, 3 { Bisiklet Sürer Gibi Uçma } ' ");
	TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi yazi", TW_TYPE_CSSTRING(sizeof(set.D3DFeatures.friendtext)), &set.D3DFeatures.friendtext, " label='Dost Etiketinde Görünecek Yazi:' min=1 max=25 group='Görsel Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "rainbowhudtitle", TW_TYPE_BOOLCPP, &set.D3DFeatures.Use_Rainbow_Title_for_NewHUD, "label='Rainbow Baslik:HUD' group='Görsel Ayarlar' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Görsel Ayarlar' ");
	TwAddButton(twBar_GeneralCheats, "X Pos Nedir", xPosNedir, NULL, "label='Koordinatlar:Bilgilendirme' group='Görsel Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "Friend List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForFriendList, " label='Dost Listesi:X Koordinatlari' min=-200.0f max=300.0 group='Görsel Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "Admin List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForAdminList, " label='Admin Listesi:X Koordinatlari' min=-200.0f max=300.0 group='Görsel Ayarlar' ");
	TwDefine(" 'Cheat_Settings'/'Görsel Ayarlar' opened=false ");

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwType CrasherType = TwDefineEnum("CrasherType", NULL, 0);
	TwAddVarRW(twBar_GeneralCheats, "IBC fOnFootZPos", TW_TYPE_FLOAT, &set.invalidBullets.fOnFootPosZ, " label='Invalid Bullets Crasherler: OnFoot Z Koordinati[-5.5 Kullanma!]' min=-6.0 max=15.0 group='Crasher Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "IBCs: Delay", TW_TYPE_INT32, &set.invalidBullets.dwDelayOfInvalidBullets, " label='Invalid Bullets Crasherler: Gecikme Süreleri' step=25 min=50 max=500 group='Crasher Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "Send Give Damage", TW_TYPE_BOOLCPP, &set.invalidBullets.bSendGiveDamage, " label='Bypass Invalid Bullets Crasher | RPC_GiveTakeDamage' group='Crasher Ayarlari' ");
	TwDefine(" 'Cheat_Settings'/'Crasher Ayarlari' opened=false ");

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	
	TwDefine(" 'Cheat_Settings'/'RapidFire: Özel Taraf' opened=false ");
#endif
	TwAddVarRW(twBar_GeneralCheats, "IBC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher1, " label='Invalid Bullets Crasher #1' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher2, " label='Invalid Bullets Crasher #2' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #3", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher3, " label='Invalid Bullets Crasher #3' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "IBC #4", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher4, " label='Invalid Bullets Crasher #4' group='Developer Crasherleri' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "RC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher1, " label='Roll Crasher #1' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "RC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher2, " label='Roll Crasher #2' group='Developer Crasherleri' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "DC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher1, " label='Direction Crasher #1' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "DC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher2, " label='Direction Crasher #2' group='Developer Crasherleri' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Game Sound Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iGameSoundCrasher, " label='Game Sound Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Enter Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iEnterPlayerCrasher, " label='Enter Vehicle Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Remove Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicRemovePlayerCrasher, " label='Detonator Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Tuning Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicTuningCrasher, " label='Tuning Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Pass Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicPassengerCrasher, " label='Pass Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Test crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iCrashertest, " label='Test Crasher' group='Developer Crasherleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Weapon crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iWeaponCrasher, " label='Weapon Crasher' group='Developer Crasherleri' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
	TwDefine(" 'Cheat_Settings'/'Developer Crasherleri' opened=false ");
	

	TwAddVarRW(twBar_GeneralCheats, "Aim Log", TW_TYPE_BOOLCPP, &cheat_state->developerPanel.bLogAimData, " label='Log AimData' group='Developer Paneli' ");
	TwAddVarRW(twBar_GeneralCheats, "SilentAim", TW_TYPE_BOOLCPP, &cheat_state->Korumalar.iAntiSilentAim, " label='Anti Silent Aim & WallShot' group='Developer Paneli' ");
	TwAddVarRW(twBar_GeneralCheats, "Hileci Listesi", TW_TYPE_BOOLCPP, &cheat_state->PrivateControlPanel.bEnablePanel, " label='Proje Kullanicilarini Gör' group='Developer Paneli' ");
	TwDefine(" 'Cheat_Settings'/'Developer Paneli' opened=false ");
#endif

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION ||  COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION

	TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon, " label='Bypass Yöntemi #1' group='Silah Atlatma Yöntemleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon2, " label='Bypass Yöntemi #2' group='Silah Atlatma Yöntemleri' ");
	TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #3", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon3, " label='Bypass Yöntemi #3' group='Silah Atlatma Yöntemleri' ");
	TwDefine(" 'Cheat_Settings'/'Silah Atlatma Yöntemleri' opened=false ");
#endif

	//set.rainbowdelay
	
	TwAddVarRW(twBar_GeneralCheats, "afk", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreAFKs, "label='AFK Filtresi' group='Genel Hile Filtreleri' ");
	TwAddVarRW(twBar_GeneralCheats, "dead", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreDEADs, "label='Ölü Filtresi' group='Genel Hile Filtreleri' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwAddVarRW(twBar_GeneralCheats, "Color", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameColor, "label='Renk Filtresi' group='Genel Hile Filtreleri' ");
	TwAddVarRW(twBar_GeneralCheats, "skin", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameSkinID, "label='Skin Filtresi' group='Genel Hile Filtreleri' ");
	TwAddVarRW(twBar_GeneralCheats, "team", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameTeam, "label='Takim Filtresi' group='Genel Hile Filtreleri' ");
	TwAddVarRW(twBar_GeneralCheats, "friend", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreMyFriends, "label='Dost Filtresi' group='Genel Hile Filtreleri' ");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwAddVarRW(twBar_GeneralCheats, "project user", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreProjectUsers, "label='Proje Kullanicilari Filtresi' group='Genel Hile Filtreleri' ");
#endif
	TwDefine(" 'Cheat_Settings'/'Genel Hile Filtreleri' opened=false ");
	//if(set.infover)
	addMessageToChatWindow("Gecikme sürelerini arttýrsanýz, hileler daha yavaþ çalýþýr.");
	addMessageToChatWindow("Ýpucu: Eðer bir hilenin fark edilme olasýlýðýný düþürmek istiyorsan, gecikme süresini arttýr.");
	//addMessageToChatWindow("Bu mesajý devre dýþý býrakmak istiyorsanýz, Bilgilendirme menüsüne göz atýn.");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwAddVarRW(twBar_GeneralCheats, "RapidFire: Delay", TW_TYPE_INT32, &set.WeaponCheats.dwRapidFireDelay, " label='RapidFire:Gecikme Süresi' min=70 max=2500 group='Genel Hile Ayarlari' ");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
	TwAddVarRW(twBar_GeneralCheats, "RapidFire: Delay", TW_TYPE_INT32, &set.WeaponCheats.dwRapidFireDelay, " label='RapidFire:Gecikme Süresi' min=100 max=2500 group='Genel Hile Ayarlari' ");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
	TwAddVarRW(twBar_GeneralCheats, "RapidFire: Delay", TW_TYPE_INT32, &set.WeaponCheats.dwRapidFireDelay, " label='RapidFire:Gecikme Süresi' min=120 max=2500 group='Genel Hile Ayarlari' ");
#endif
	TwAddVarRW(twBar_GeneralCheats, "Rainbow Kullan", TW_TYPE_BOOLCPP, &set.bUseRainbowColors, " label='Rainbow Kullan' group='Genel Hile Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "Rainbow Delay", TW_TYPE_FLOAT, &set.rainbowdelay, " label='Rainbow: Gecikme Süresi' min=0.100 max=1000.0 group='Genel Hile Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "MapRun Speed", TW_TYPE_FLOAT, &set.General.MapRun_Speed, " label='Harita-Hiz: HIZ' min=0.5 max=10.0 group='Genel Hile Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "Unsynch Radius", TW_TYPE_INT32, &set.Unsynch_Radius, " label='Fake Troller:Çap' min=20 max=500 group='Genel Hile Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "Speed Walk", TW_TYPE_FLOAT, &set.General.SpeedWalk_X, " label='Hiz Hilesi:HIZ' step=0.1 min=0.1 max=1.0 group='Genel Hile Ayarlari' ");

	TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi", TW_TYPE_BOOLCPP, &set.D3DFeatures.bDrawFriendTag, " label='Dost Etiketi' group='Genel Hile Ayarlari' ");
	TwAddVarRW(twBar_GeneralCheats, "Rapid Fire:Teleport sistemi", TW_TYPE_BOOLCPP, &set.WeaponCheats.bTeleportForRapidFire, " label='Rapid Fire: Teleport Sistemi' group='Genel Hile Ayarlari' ");
	TwDefine(" 'Cheat_Settings'/'Genel Hile Ayarlari' opened=false ");

	TwAddVarRW(twBar_GeneralCheats, "God Fly: X", TW_TYPE_FLOAT, &set.General.fGodFlySpeed[0], " label='Uçma: HIZ' step=0.1 min=0.1 max=5.0 group='Uçma Hilesi: Ayarlar' ");
	//TwAddVarRW(twBar_GeneralCheats, "God Fly: Y", TW_TYPE_FLOAT, &set.General.fGodFlySpeed[1], " label='God Fly: Y Hizi' step=0.1 min=0.1 max=4.0 group='God Fly Settings' ");
	TwDefine(" 'Cheat_Settings'/'Uçma Hilesi: Ayarlar' opened=false ");

	TwAddVarRW(twBar_GeneralCheats, "Double Gun #1 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun1_Delay, " label='Çifte Silah: #1 Gecikme Süresi' min=250 max=2000 group='Deagle/Shotgun: Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_Delay, " label='Çifte Silah: #2 Gecikme Süresi' min=250 max=2000 group='Deagle/Shotgun: Ayarlar' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Deagle/Shotgun: Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #1", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot1, " label='Çifte Silah #2: Birincil Silah Slotu' min=0 max=6 group='Deagle/Shotgun: Ayarlar' ");
	TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #2", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot2, " label='Çifte Silah #2: Ikincil Silah Slotu' min=0 max=6 group='Deagle/Shotgun: Ayarlar' ");
	TwAddButton(twBar_GeneralCheats, "Bu nedir?", silahSwitchNedir, NULL, "label='Bu Hile Nedir?' group='Deagle/Shotgun: Ayarlar' ");
	TwDefine(" 'Cheat_Settings'/'Deagle/Shotgun: Ayarlar' opened=false ");

	TwType gWeapon = TwDefineEnum("gWeapon", NULL, 0);
	TwAddButton(twBar_GeneralCheats, "Bu nedir - silah?", silahVerNedir, NULL, "label='Önemli | Bilgi için Tikla' group='Silah ver' ");
	TwAddVarRW(twBar_GeneralCheats, "Weapon Name:", gWeapon, &set.WeaponCheats.GiveWeapon_WeaponID, " label='Silah ismi:' enum='0 {Yumruk}, 1 {Musta}, 2 {Golf Sopasi}, 3 {Jop}, 4 {Bicak}, 5 {Bat}, 6 {Kürek}, 7 {Bilardo Sopasi}, 8 {Katana}, 9 {Testere}, 10 {Dildo #1}, 11 {Dildo #2}, 12 {Vibratör #1}, 13 {Vibratör #2}, 14 {Çiçek}, 15 {Cane}, 16 {Bomba}, 17 {Gaz Bombasi}, 18 {Molotof}, 22 {Colt45}, 23 {Susturuculu Colt45}, 24 {Deagle}, 25 {Shotgun}, 26 {Sawn Off Shotgun}, 27 {Combat Shotgun}, 28 {Uzi}, 29 {MP5}, 30 {AK47}, 31 {M4}, 32 {TEC9}, 33 {Cuntgun}, 34 {Sniper}, 35 {Roket}, 36 {Isi Duyarli Roket}, 37 {Alev Püskürtücü}, 38 {Minigun}' group='Silah ver' ");
	TwAddVarRW(twBar_GeneralCheats, "Weapon Ammo:", TW_TYPE_INT32, &set.WeaponCheats.GiveWeapon_Ammo_Amount, " label='Silah Mermi Miktari:' step=100 min=1 max=10000 group='Silah ver' ");
	TwAddButton(twBar_GeneralCheats, "Get Gun", weaponMenu_GiveWeaponWithAmmo, NULL, " label='Seçili Silahi ver' group='Silah ver' ");
	TwDefine(" 'Cheat_Settings'/'Silah ver' opened=false ");


	TwAddVarRW(twBar_GeneralCheats, "Admin Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddDeleteAdminID, " label=`Admin ID'si:` step=1 min=1 max=1000 group='Admin Ekle/Kaldir' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Ekle", adminEkle, NULL, " label=`Seçili ID'yi Admin Ekle` group='Admin Ekle/Kaldir' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Admin Ekle/Kaldir' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Sil", adminSil, NULL, " label=`Seçili ID'yi Adminlerden Sil` group='Admin Ekle/Kaldir' ");
	TwDefine(" 'Cheat_Settings'/'Admin Ekle/Kaldir' opened=false ");

	TwAddVarRW(twBar_GeneralCheats, "Dost Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddDeleteFriendID, " label=`Dost ID'si:` step=1 min=1 max=1000 group='Dost Ekle/Kaldir' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Dost Ekle", dostEkle, NULL, " label=`Seçili ID'yi Dost Ekle` group='Dost Ekle/Kaldir' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Dost Ekle/Kaldir' ");
	TwAddButton(twBar_GeneralCheats, "Seçili ID Dosttan Sil", dostSil, NULL, " label=`Seçili ID'yi Dostlardan Sil` group='Dost Ekle/Kaldir' ");
	TwDefine(" 'Cheat_Settings'/'Dost Ekle/Kaldir' opened=true ");

	//TwAddVarRW(twBar_GeneralCheats, "Admin Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddFriendID, " label=`Admin ID'si:` step=1 min=1 max=1000 group='Admin Ekle/Kaldir' ");
	//TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Ekle", adminEkle, NULL, " label=`Seçili ID'yi Admin Ekle` group='Admin Ekle/Kaldir' ");
	//TwAddSeparator(twBar_GeneralCheats, NULL, "group='Admin Ekle/Kaldir' ");
	//TwAddVarRW(twBar_GeneralCheats, "Admin Sil ID", TW_TYPE_INT32, &set.friendFilters.iDeleteFriendID, " label=`Seçili ID'yi Dostlardan Sil:` step=1 min=1 max=1000 group='Admin Ekle/Kaldir' ");
	//TwAddButton(twBar_GeneralCheats, "Seçili ID Admin Sil", adminSil, NULL, " label=`Seçili ID'yi Adminlerden Sil` group='Admin Ekle/Kaldir' ");
	//TwDefine(" 'Cheat_Settings'/'Admin Ekle/Kaldir' opened=false ");

	//TwAddVarRW(twBar_GeneralCheats, "Dost Ekle ID", TW_TYPE_INT32, &set.friendFilters.iAddFriendID, " label=`Dost ID'si:` step=1 min=1 max=1000 group='Dost Ekle/Kaldir' ");
	//TwAddButton(twBar_GeneralCheats, "Seçili ID Dost Ekle", dostEkle, NULL, " label=`Seçili ID'yi Dost Ekle` group='Dost Ekle/Kaldir' ");
	//TwAddSeparator(twBar_GeneralCheats, NULL, "group='Dost Ekle/Kaldir' ");
	//TwAddVarRW(twBar_GeneralCheats, "Dost Sil ID", TW_TYPE_INT32, &set.friendFilters.iDeleteFriendID, " label=`Dostlardan Sil:` step=1 min=1 max=1000 group='Dost Ekle/Kaldir' ");
	//TwAddButton(twBar_GeneralCheats, "Seçili ID Dosttan Sil", dostSil, NULL, " label=`Seçili ID'yi Dostlardan Sil` group='Dost Ekle/Kaldir' ");
	//TwDefine(" 'Cheat_Settings'/'Dost Ekle/Kaldir' opened=true ");


	/*TwAddVarRW(twBar_GeneralCheats, "1", TW_TYPE_FLOAT, &set.D3DFeatures.playerTagYStuff[0], " label='Y Stuff #1' step=1.0 min=-20.00 max=50.00 group='Debug Faktörü' ");
	TwAddVarRW(twBar_GeneralCheats, "2", TW_TYPE_FLOAT, &set.D3DFeatures.playerTagYStuff[1], " label='Y Stuff #2' step=1.0 min=-20.00 max=50.00 group='Debug Faktörü' ");
	TwAddVarRW(twBar_GeneralCheats, "3", TW_TYPE_FLOAT, &set.D3DFeatures.playerTagYStuffX[0], " label='XY Stuff #1' step=1.0 min=-20.00 max=50.00 group='Debug Faktörü' ");
	TwAddVarRW(twBar_GeneralCheats, "4", TW_TYPE_FLOAT, &set.D3DFeatures.playerTagYStuffX[1], " label='XY Stuff #2' step=1.0 min=-20.00 max=50.00 group='Debug Faktörü' ");
	TwAddSeparator(twBar_GeneralCheats, NULL, "group='Debug Faktörü' ");*/


	TwAddVarRW(twBar_GeneralCheats, "Unsynch senkronize", TW_TYPE_BOOLCPP, &set.See_How_UnSynch_Works, "label='Fake Trolleyici: Pozisyonu Gör' group='Senkronizasyon Ayarlari' ");
	TwDefine(" 'Cheat_Settings'/'Senkronizasyon Ayarlari' opened=false ");


	TwAddButton(twBar_CarCheats, "Bu nedir - araç?", aracKontrolNedir, NULL, "label='Önemli | Bilgi için Tikla'  group='Araç Uzaktan Kontrol: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Remote Control", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarRemoteControl, " label='Araç Uzaktan Kontrol: Aktiflestir' group='Araç Uzaktan Kontrol: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Remote Control With Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_with_driver, " label='Araç Uzaktan Kontrol: Sürücülü Mod' group='Araç Uzaktan Kontrol: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Remote Control Without Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_without_driver, " label='Araç Uzaktan Kontrol: Sürücüsüz Mod' group='Araç Uzaktan Kontrol: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Araç Uzaktan Kontrol: Ayarlar' opened=false ");
	
	TwAddButton(twBar_CarCheats, "Araç Koordinat", aracLagBilgi, NULL, "label='Araç Lag: Bilgi' group='Araç Lag Koordinatlari' ");
	TwAddButton(twBar_CarCheats, "Ayar yap", carlagAyarYap, NULL, "label='Kullanimini Bilmiyorsan bu butona bas' group='Araç Lag Koordinatlari' ");
	TwAddVarRW(twBar_CarCheats, "Car Lag X Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[0], " label='Araç Lag: X+ Koordinatlari' min=-10 max=150  group='Araç Lag Koordinatlari' ");
	TwAddVarRW(twBar_CarCheats, "Car Lag Y Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[1], " label='Araç Lag: Y+ Koordinatlari' min=-10 max=150  group='Araç Lag Koordinatlari' ");
	TwAddVarRW(twBar_CarCheats, "Car Lag Z Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[2], " label='Araç Lag: Z+ Koordinatlari' min=-15 max=50   group='Araç Lag Koordinatlari' ");
	TwDefine(" 'Car_Hacks'/'Araç Lag Koordinatlari' opened=false ");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELPER_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION

	TwAddVarRW(twBar_CarCheats, "Car Sun Angle", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Angle, " label='Araç Günesi: Derece' step=10.0 min=0.0 max=180.00 group='Araç Günesi: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Z Height", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Z_Position_Height, " label='Araç Günesi: Z+ Yüksekligi' step=10.0 min=0.0 max=100.00 group='Araç Günesi: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Abs Speed", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Abs_Speed, " label='Araç Günesi: HIZ' step=10.0 min=0.0 max=100.00 group='Araç Günesi: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Sun Degree To Radian Value", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Degree_To_Radian_Value, " label='Car Günesi: Radyan Derece' step=10.0 min=5.0 max=200.00 group='Araç Günesi: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Araç Günesi: Ayarlar' opened=false ");
	
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Z Height", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Z_Height, " label='Araç Dairesi #2:Rastgele Z Yüksekligi Kullan' group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Minimum_Value, " label='Araç Dairesi #2:Rastgele Z Minimum Deger:' step=6.0 min=7.0 max=50.00 group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Maximum_Value, " label='Araç Dairesi #2:Rastgele Z Maksimum Deger:' step=6.0 min=7.0 max=50.00 group='Araç Dairesi #2: Ayarlar' ");
	TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Radius", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Radius, " label='Araç Dairesi #2:Rastgele Yariçap Kullan' group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Minimum_Value, " label='Araç Dairesi #2:Yariçap Minimum Deger:' step=6.0 min=7.0 max=90.00 group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Maximum_Value, " label='Araç Dairesi #2:Yariçap Maksimum Deger:' step=6.0 min=7.0 max=90.00 group='Araç Dairesi #2: Ayarlar' ");
	TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Radius", TW_TYPE_FLOAT, &set.CarCheats.CarCircle3_Radius, " label='[SABiT DEGER]Araç Dairesi #2:Yariçap' step=6.0 min=7.0 max=150.00 group='Araç Dairesi #2: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Circle #2: Z Height", TW_TYPE_FLOAT, &set.CarCheats.CarCircle_Z_Height, " label='[SABiT DEGER]Araç Dairesi #2:Z Yüksekligi' step=6.0 min=2.0 max=70.00 group='Araç Dairesi #2: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Araç Dairesi #2: Ayarlar' opened=false ");

	/*TwAddVarRW(twBar_CarCheats, "Car Fucker #3: X Min Random Value", TW_TYPE_INT32, &set.CarCheats.iCarFucker_RandomMinMaxValueForX_Axis[0], " label='Araç Trolleyici #3:X Ekseni Minimum Deger:' step=10 min=15 max=350 group='Araç Silkeyici #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Fucker #3: X Max Random Value", TW_TYPE_INT32, &set.CarCheats.iCarFucker_RandomMinMaxValueForX_Axis[1], " label='Araç Trolleyici #3:X Ekseni Maksimum Deger:' step=10 min=15 max=350 group='Araç Silkeyici #3: Ayarlar' ");
	TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Silkeyici #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Fucker #3: Y Min Random Value", TW_TYPE_INT32, &set.CarCheats.iCarFucker_RandomMinMaxValueForY_Axis[0], " label='Araç Trolleyici #3:Y Ekseni Minimum Deger:' step=10 min=15 max=350 group='Araç Silkeyici #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Fucker #3: Y Max Random Value", TW_TYPE_INT32, &set.CarCheats.iCarFucker_RandomMinMaxValueForY_Axis[1], " label='Araç Trolleyici #3:Y Ekseni Maksimum Deger:' step=10 min=15 max=350 group='Araç Silkeyici #3: Ayarlar' ");
	TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Silkeyici #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Fucker #3: Z Height", TW_TYPE_FLOAT, &set.CarCheats.fCarFucker_Z_Height, " label='Araç Trolleyici #3: Rastgele Z Yüksekligi:' step=6.0 min=4.0 max=70.0 group='Araç Silkeyici #3: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Araç Silkeyici #3: Ayarlar' opened=false ");*/

	TwAddVarRW(twBar_CarCheats, "Car Floating #3:X Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[0], " label='Yüzen Araçlar #3:X Ekseni Minimum Deger:' step=10 min=15 max=350 group='Yüzen Araçlar #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Floating #3:Y Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[1], " label='Yüzen Araçlar #3:Y Ekseni Minimum Deger:' step=10 min=15 max=350 group='Yüzen Araçlar #3: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Car Floating #3:Z Height", TW_TYPE_FLOAT, &set.CarCheats.fCarFloating3_Z_Height, " label='Yüzen Araçlar #3:Z Yüksekligi:' step=6.0 min=3.0 max=70.00 group='Yüzen Araçlar #3: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Yüzen Araçlar #3: Ayarlar' opened=false ");
#endif

	TwAddButton(twBar_CarCheats, "Bu nedir? - araç renk", aracRenkBilgi, NULL, "label='Araç Renkleri: Kullanim Bilgisi' group='Araç Renkleri #1-#4: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #1 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar1_Delay, " label='Araç Renkleri #1: Gecikme Süresi' step=100 min=100 max=4500 group='Araç Renkleri #1-#4: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #2 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar2_Delay, " label='Araç Renkleri #2: Gecikme Süresi' step=100 min=100 max=4500 group='Araç Renkleri #1-#4: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #3 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar3_Delay, " label='Araç Renkleri #3: Gecikme Süresi' step=100 min=100 max=4500 group='Araç Renkleri #1-#4: Ayarlar' ");
	TwAddVarRW(twBar_CarCheats, "Crazy Car #4 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar4_Delay, " label='Araç Renkleri #4: Gecikme Süresi' step=100 min=100 max=4500 group='Araç Renkleri #1-#4: Ayarlar' ");
	TwDefine(" 'Car_Hacks'/'Araç Renkleri #1-#4: Ayarlar' opened=false ");
	//TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Renkleri #1-#4: Ayarlar' ");

	/*
		Added Delay settings for Crazy Car #1, #2, #3, #4.
		iTroll Places is changed.. It is on F2 menu -> Troll Cheats menu anymore.
	*/

	/*
	<- Aim Functions & Aim Fonksiyonlarý ->
	*/
	TwAddButton(twBar_AimFuncs, "Rage Hacking", AreYouRageCheater, NULL, " label='Rage Ayarlar için TIKLA!' ");
	TwAddButton(twBar_AimFuncs, "Legit Hacking", AreYouLegitCheater, NULL, " label='Legit Ayarlar için TIKLA!' ");
	TwType AimBotType = TwDefineEnum("AimBotType", NULL, 0); 
	TwAddVarRW(twBar_AimFuncs, "AimBot Lock To:", AimBotType, &set.AutoAimPozisyon, " label='Skin Aimbot: Nereye Nisan Alsin?' enum='0 {Kapali: Kafaya}, 1 {Karin Bölgesi #1}, 2 {Karin Bölgesi #2}, 3 {Bel #1}, 4 {Üst Gövde}, 5 {Boyun}, 6 {Right Upper Torso}, 8 {Omuz}' ");
	
	TwAddVarRW(twBar_AimFuncs, "SilentAim", TW_TYPE_BOOLCPP, &cheat_state->Silent.bSilent, " label='Silent Aim: Aç' ");
	TwAddVarRW(twBar_AimFuncs, "Shoot Through Walls", TW_TYPE_BOOLCPP, &cheat_state->Silah.iShooting_Through_Walls, " label='Wall Shot: Aç' ");
	TwAddVarRW(twBar_AimFuncs, "Shoot Through Walls | Fix BETA", TW_TYPE_BOOLCPP, &cheat_state->Silah.iShooting_Through_WallsBypass, " label='Wall Shot Bypass | BETA' ");
	//TwAddVarRW(twBar_AimFuncs, "Bypass AC", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassAimAntiCheat, " label='Silent Aim: Anti Cheat Bypass #1' ");
	TwAddSeparator(twBar_AimFuncs, NULL, NULL);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Hit Chance", TW_TYPE_INT32, &set.silentAim.iHitChanceValue, " label='SilentAim:Isabet Derecesi' min=5 max=100 group='Silent Aim:Legit Ayarlar' ");
	TwAddButton(twBar_AimFuncs, "Bu nedir?", silentAimNedir, NULL, "label='Bu Hile Nedir?' group='Silent Aim:Legit Ayarlar' ");
	TwDefine(" 'Aim_Funcs'/'Silent Aim:Legit Ayarlar' opened=false ");

	TwType targetType = TwDefineEnum("targetType", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Hedef Çizim Türü", targetType, &set.silentAim.targetType, " label='Silent Aim: Hedef Çizim Türü' enum='0 { Yazi }, 1 { Yok }' group='SilentAim Ayarlar:Hedef Bilgisi #1' ");
	//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Circle Radius", TW_TYPE_FLOAT, &set.silentAim.fCircleRadius, " label='SilentAim:Daire Büyüklügü' min=5.0 max=500.0 group='SilentAim Ayarlar:Hedef Bilgisi #1' ");
	TwDefine(" 'Aim_Funcs'/'SilentAim Ayarlar:Hedef Bilgisi #1' opened=true ");

	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Draw Target Bones", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBones, " label='SilentAim:Hedef iskeleti' group='SilentAim Ayarlar:Hedef Bilgisi #2' ");
	TwType colorType1 = TwDefineEnum("ColorType1", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Hedef Çizimi", colorType1, &set.silentAim.iDrawBoneColor, " label='Hedef iskeleti:Renk' enum='0 { Oyuncunun Rengini Kullan }, 1 { Kirmizi Renk }, 2 { Yesil Renk }, 3 { Mavi Renk }, 4 { Siyah Renk }, 5 { Beyaz Renk }, 6 { Altin Rengi }, 7 { Gümüs Renk }, 8 { Gece Mavisi Rengi }, 9 { Su Rengi }, 10 { Kestane Rengi }, 11 { Rainbow Kullan }' group='SilentAim Ayarlar:Hedef Bilgisi #2' ");
	TwDefine(" 'Aim_Funcs'/'SilentAim Ayarlar:Hedef Bilgisi #2' opened=true ");

	//TwAddSeparator(twBar_AimFuncs, NULL, "group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
	TwType colorType2 = TwDefineEnum("ColorType2", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: ESP: Aç ", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBox, " label='SilentAim:Hedef ESP' group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: ESP Renk", colorType2, &set.silentAim.iDrawBoxColor, " label='Hedef ESP:Renk' enum='0 { Oyuncunun Rengini Kullan }, 1 { Kirmizi Renk }, 2 { Yesil Renk }, 3 { Mavi Renk }, 4 { Siyah Renk }, 5 { Beyaz Renk }, 6 { Altin Rengi }, 7 { Gümüs Renk }, 8 { Gece Mavisi Rengi }, 9 { Su Rengi }, 10 { Kestane Rengi }, 11 { Rainbow Kullan }' group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
	TwDefine(" 'Aim_Funcs'/'SilentAim Ayarlar:Hedef Bilgisi #3' opened=true ");

	/*
		Filtreler ve ne iþe yaradýklarý:
		Mesafe Filtresi: Mevcut silahýnýn uzaðýnda atýþ yapmaný saðlar.
		Takým Filtresi: Sunucu içerisinde bir birliðe veya ekibe girdiðin zaman, aimbot, ekip arkadaþlarýna niþan almaz.
		Renk Filtresi: Ayný isim renginde olduðun arkadaþlarýna, aimbot niþan almaz.
		Skin Filtresi: Seninle ayný skin olan arkadaþlarýna aimbot niþan almaz.
		Görünen Hedef Filtresi: Görebildiðin oyuncuya niþan alýrsýn sadece, duvar arkasýndakilere alamazsýn!
		AFK Filtresi: Aimbot, AFK olan oyunculara niþan almaz.
		Ölü Filtresi: Aimbot, Yerde yatan ölülere niþan almaz.
		NPC Filtresi: Þimdilik kalsýn.
		Admin Filtresi: Þimdilik kalsýn.
		Arkadaþ Filtresi: Þimdilik Kalsýn.
	*/
	TwAddButton(twBar_AimFuncs, "Bu ayarlar nedir?", silentAimAyarlariNedir, NULL, "label='Bu Filtreler Nelerdir?' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Out Of Range", TW_TYPE_BOOLCPP, &set.silentAim.bOutOfRange, " label='SilentAim: Mesafe Filtresi' group='Silent Aim: Filtreler' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Same Team Filter", TW_TYPE_BOOLCPP, &set.silentAim.bTeamFilter, " label='SilentAim: Takim Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Nick Name Color Filter", TW_TYPE_BOOLCPP, &set.silentAim.bColorFilter, " label='SilentAim: Renk Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Skin Filter", TW_TYPE_BOOLCPP, &set.silentAim.bSkinFilter, " label='SilentAim: Skin Filtresi' group='Silent Aim: Filtreler' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Visible Target Filter", TW_TYPE_BOOLCPP, &set.silentAim.bVisibleFilter, " label='SilentAim: Görünen Hedef Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> AFK Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAFKFilter, " label='SilentAim: AFK Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Alive Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAliveFilter, " label='SilentAim: Ölü Filtresi' group='Silent Aim: Filtreler' ");
	TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filtreler' ");
	// NPC Filtresine gerek yok...
	//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore NPCs Filter", TW_TYPE_BOOLCPP, &cheat_state->Silah.iSAim_IgnoreNPCs, " label='SilentAim: NPC Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Admins[IN ADMINS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAdminFilter, " label='SilentAim: Admin Filtresi' group='Silent Aim: Filtreler' ");
	TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Friends[IN FRIENDS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bFriendFilter, " label='SilentAim: Dost Filtresi' group='Silent Aim: Filtreler' ");
	TwDefine(" 'Aim_Funcs'/'Silent Aim: Filtreler' opened=true ");
	
	TwType spinType = TwDefineEnum("spinSettings", NULL, 0);
	TwAddVarRW(twBar_AimFuncs, "SpinBot Type", spinType, &cheat_state->Silah.iSpinBotType, " label='Spinbot Türü:' enum='0 { KAPALI }, 1 { Yere Bak }, 2 { Havaya Bak }, 3 { Random Bak }' group='Spinbot Ayarlari' ");
	TwDefine(" 'Aim_Funcs'/'Spinbot Ayarlari' opened=false ");

	TwAddVarRW(twBar_AimFuncs, "SyncSpinBot", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.iSyncSpinBotTypes, " label='SpinBot:Senkronize Et' group='Aim Senkronizasyonlari' ");
	TwAddVarRW(twBar_AimFuncs, "InvalidAimZ:Sync", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.bSyncInvalidAimZPed, " label='Aim Z:Senkronize Et' group='Aim Senkronizasyonlari' ");
	TwDefine(" 'Aim_Funcs'/'Aim Senkronizasyonlari' opened=false ");
	
	TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon, " label='Silah Hilesi Atlatma Yöntemi #1' group='Silah Hilesi Atlatma Yöntemleri' ");
	TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon2, " label='Silah Hilesi Atlatma Yöntemi #2' group='Silah Hilesi Atlatma Yöntemleri' ");
	TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #3", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon3, " label='Silah Hilesi Atlatma Yöntemi #3' group='Silah Hilesi Atlatma Yöntemleri' ");
	TwDefine(" 'Weapon_Funcs'/'Silah Hilesi Atlatma Yöntemleri' opened=true ");
	TwAddSeparator(twBar_weaponCheats, NULL, "");
	TwAddVarRW(twBar_weaponCheats, "RapidFire", TW_TYPE_BOOLCPP, &cheat_state->Silah.iRapidFire, " label='Süper Tarama | Rapid Fire' ");
	TwAddVarRW(twBar_weaponCheats, "RTD", TW_TYPE_BOOLCPP, &cheat_state->Silah.iReturnTheDamage, " label='Hasar Döndürücü' ");
	TwAddVarRW(twBar_weaponCheats, "No Reload", TW_TYPE_BOOLCPP, &cheat_state->Silah.iNoReloadBug, " label='Sinirsiz Mermi' ");
	TwAddVarRW(twBar_weaponCheats, "Oto 2-2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAuto2_2, " label='Otomatik 2-2' ");
	TwAddVarRW(twBar_weaponCheats, "No Recoil", TW_TYPE_BOOLCPP, &cheat_state->Silah.iNoRecoil, " label='Silah Geri Tepmesini Kapat | No Recoil' ");
	TwAddSeparator(twBar_weaponCheats, NULL, NULL);
	TwAddVarRW(twBar_weaponCheats, "Oto C bug #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAutoCbug1, " label='Oto C-Bug #1' group='Oto C Bug' ");
	TwAddVarRW(twBar_weaponCheats, "Oto C bug #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAutoCbug2, " label='Oto C-Bug #2' group='Oto C Bug' ");
	TwDefine(" 'Weapon_Funcs'/'Oto C Bug' opened=true ");
	TwAddVarRW(twBar_weaponCheats, "Çifte Silah #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDoubleGun1, " label='Çifte Silah #1' group='Çifte Silah' ");
	TwAddVarRW(twBar_weaponCheats, "Çifte Silah #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDoubleGun2, " label='Çifte Silah #2' group='Çifte Silah' ");
	TwAddVarRW(twBar_weaponCheats, "Silah Hasar Katlayici", TW_TYPE_INT32, &set.WeaponCheats.Weapon_Damage, " label='Silah Hasar Katlayici:' min=0 max=30");
	/*TwAddVarRW(twBar_weaponCheats, "iAllowCBUG", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAllowCBUG, " label='CBUG Bypass: Aktif Et' group='Oto C Bug | Bypass' ");
	TwAddVarRW(twBar_weaponCheats, "iAllowTypeAnim", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAllowTypeAnim, " label='CBUG Bypass | Animasyon' group='Oto C Bug | Bypass' ");
	TwAddVarRW(twBar_weaponCheats, "iAllowTypeFreeze", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAllowTypeFreeze, " label='CBUG Bypass | Dondurma' group='Oto C Bug | Bypass' ");
	TwAddVarRW(twBar_weaponCheats, "iAllowTypeText", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAllowTypeText, " label='CBUG Bypass | Yazi' group='Oto C Bug | Bypass' ");
	TwAddVarRW(twBar_weaponCheats, "iAllowTypeWeapon", TW_TYPE_BOOLCPP, &cheat_state->Silah.iAllowTypeWeapon, " label='CBUG Bypass | Silah' group='Oto C Bug | Bypass' ");
	TwDefine(" 'Weapon_Funcs'/'Oto C Bug | Bypass' opened=true ");*/
	TwDefine(" 'Weapon_Funcs'/'Çifte Silah' opened=true ");
	//DETECTOR_PROJECTVERSION_ID
	TwType iTrollType = TwDefineEnum("iTrollType", NULL, 0); // cheat_state->Troll.iInvisible5
	TwAddVarRW(twBar_TrollFuncs, "iTroll Type", iTrollType, &cheat_state->Troll.iTroll, " label='iTroll Türü:' enum='0 { iTroll KAPALI }, 1 { Yerin Altina Sok }, 2 { Hiz Ver }, 3 { Patlat Ve Uçur #1 }, 4 { Patlat ve Uçur #2 }, 5 { 360 Derece Döndür }, 6 { Ters Çevir }, 7 { Patlat }, 8 { Çekiciye Teleport Et }, 9 { Ziplat }, 10 { Haritanin Ortasina Teleport Et }, 11 { Denize Teleport Et }, 12 { Durdur }, 13 { Çukura Teleport Et }, 14 { HP Ayarla }, 15 { Rastgele HP Ayarla }, 16 { Rastgele Eksen Degeri }, 17 { Rastgele Koordinat }, 18 { Hileli Z Koordinati + Patlama }, 19 { Arabadan At }' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);

	TwAddVarRW(twBar_TrollFuncs, "iTroll: HP degeri", TW_TYPE_FLOAT, &set.itrollSettings.fSetHP, " label='iTroll:Araç HPsini Ayarla' min=1.0 max=1000.0 group='iTroll:Ayarlar' ");
	TwDefine(" 'Troll_Cheats'/'iTroll:Ayarlar' opened=false ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #14", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible14, " label='Pass/Drive-By Modu' ");
	TwAddVarRW(twBar_TrollFuncs, "Invisible Bike", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisibleBike, " label='Görünmez Bisiklet' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	//TwAddVarRW(twBar_TrollFuncs, "Invisible Cars", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarInvisible, " label='Görünmezlik[Araç]' ");
	TwAddVarRW(twBar_TrollFuncs, "Delete Cars #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars, " label='Araç Silici #1' ");
	TwAddVarRW(twBar_TrollFuncs, "Delete Cars #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars2, " label='Araç Silici #2' ");
	TwAddVarRW(twBar_TrollFuncs, "Vehicle Deformer", TW_TYPE_BOOLCPP, &cheat_state->Arac.iVehicleDeformer, " label='Araç Deformasyonu' ");
	TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCircleTroll, " label='Daire Troll: Aç' group='Daire Troll' ");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Target ID", TW_TYPE_INT32, &set.TrollCheats.CircleTrollTargetID, " label='Daire Troll: Hedef Oyuncu ID' min=0 max=1000 group='Daire Troll' ");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Spin Speed", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Spin_Speed, " label='Daire Troll: Dönme HIZI' min=0 max=100 group='Daire Troll' ");
	TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Circle Radius", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Circle_Radius, " label='Daire Troll: Daire Yariçap' min=1 max=100 group='Daire Troll' ");
	TwDefine(" 'Troll_Cheats'/'Daire Troll' opened=false ");
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerCopier, " label='Koordinat Kopyalayici:Aç' group='Oyuncu Koordinat Kopyalayici:Ayarlari' ");
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Target ID", TW_TYPE_INT32, &set.TrollCheats.iPlayerCopier_TargetID, " label='Koordinat Kopyalayici:Hedef Oyuncu ID' min=0 max=1000 group='Oyuncu Koordinat Kopyalayici:Ayarlari' ");
	TwAddVarRW(twBar_TrollFuncs, "Player Copier: Sync Player Copier", TW_TYPE_BOOLCPP, &set.TrollCheats.bSyncPlayerCopier, " label='Koordinat Kopyalayici:Senkronize' group='Oyuncu Koordinat Kopyalayici:Ayarlari' ");
	TwDefine(" 'Troll_Cheats'/'Oyuncu Koordinat Kopyalayici:Ayarlari' opened=false ");


	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible1, " label='Görünmezlik #1' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible2, " label='Görünmezlik #2' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible3, " label='Görünmezlik #3' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible4, " label='Görünmezlik #4' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible5, " label='Görünmezlik #5' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible6, " label='Görünmezlik #6' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible7, " label='Görünmezlik #7' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #8", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible8, " label='Görünmezlik #8' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #9", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible9, " label='Görünmezlik #9' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #10", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible10, " label='Görünmezlik #10' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #11", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible11, " label='Görünmezlik #11' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #12", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible12, " label='Görünmezlik #12' group='Görünmezlikler' ");
	TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #13", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible13, " label='Görünmezlik #13' group='Görünmezlikler' ");
	
	//TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #15", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible15, " label='Görünmezlik #15' group='Görünmezlikler' ");
	TwDefine(" 'Troll_Cheats'/'Görünmezlikler' opened=true ");

	TwAddVarRW(twBar_TrollFuncs, "Slapper #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerFucker, " label='Slapper #1' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iHeadWalkSlapper, " label='Slapper #2' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iQuaSlapper, " label='Slapper #3' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iSpeedKicker, " label='Slapper #4' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iActorShooter, " label='Detected | Slapper #5' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iElevator, " label='Detected | Slapper #6' group='Slapperler' ");
	TwAddVarRW(twBar_TrollFuncs, "Slapper #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iJetpackElevator, " label='Detected | Slapper #7' group='Slapperler' ");

	TwDefine(" 'Troll_Cheats'/'Slapperler' opened=false ");

	TwAddVarRW(twBar_TrollFuncs, "Undetected Invisible[En Düsük Random Deger]", TW_TYPE_FLOAT, &set.TrollCheats.fUDInvisibleMinValue, " label='Görünmezlik #5[En Düsük Rastgele Deger]' min=2.9 max=5.9 group='Invisible #5:Ayarlar' ");
	TwAddVarRW(twBar_TrollFuncs, "Undetected Invisible[En Yüksek Random Deger]", TW_TYPE_FLOAT, &set.TrollCheats.fUDInvisibleMaxValue, " label='Görünmezlik #5[En Yüksek Rastgele Deger]' min=6.0 max=13.5 group='Invisible #5:Ayarlar' ");
	//TwAddSeparator(twBar_TrollFuncs, NULL, "group='Görünmezlik Hilelerinin Ayarlari' ");
	TwDefine(" 'Troll_Cheats'/'Invisible #5:Ayarlar' opened=false ");
	// Flooder faktörleri...
	TwAddVarRW(twBar_FloodCheats, "Spammer #1 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer1_Text)), &set.ChatHacks.Project_Spammer1_Text, " label='Flooder #1: Yazi' group='Spam: Yazi Ayarlari' ");
	//TwAddVarRW(twBar_FloodCheats, "Spammer #2 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer2_Text)), &set.ChatHacks.Project_Spammer2_Text, " label='Flooder #2 Text' group='Flooder Text Settings' ");
	TwDefine(" 'Flood_Hacks'/'Spam: Yazi Ayarlari' opened=false ");

	TwAddVarRW(twBar_FloodCheats, "Spammer #1 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer1_Run_Delay, " label='Flooder #1: Gecikme Süresi' min=50 max=10000 group='Spam: Zamanlama Ayarlari' ");
	//TwAddVarRW(twBar_FloodCheats, "Spammer #2 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer2_Run_Delay, " label='Flooder #2 -> Run Delay' min=50 max=10000 group='Flooder Delay/Run Settings' ");
	TwDefine(" 'Flood_Hacks'/'Spam: Zamanlama Ayarlari' opened=false ");

	TwType FlooderType = TwDefineEnum("FlooderType", NULL, 0);
	TwAddVarRW(twBar_FloodCheats, "Random Texts Flooder Type:", FlooderType, &set.ChatHacks.bSpammer1_Random_Texts_Random_Type, " label='Flooder #1: Üretici Türü' enum='1 { Sadece: A-Z & a-z }, 2 { Sadece: A-Z }, 3 { Sadece: a-z }, 4 { Sadece: 0-9 }, 5 { Sadece: 0 & 1 }, 6 { Sadece Özel Karakterler }' group='Spam: Türler ve Ayarlar' ");
	TwAddSeparator(twBar_FloodCheats, NULL, "group='Spam: Türler ve Ayarlar' ");
	TwAddVarRW(twBar_FloodCheats, "Use Left Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Left_Random_Texts, "label='Flooder #1: Sol taraftan üret' group='Spam: Türler ve Ayarlar' ");
	TwAddVarRW(twBar_FloodCheats, "Use Right Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Right_Random_Texts, "label='Flooder #1: Sag taraftan üret' group='Spam: Türler ve Ayarlar' ");
	TwAddVarRW(twBar_FloodCheats, "Use Both Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Both_Random_Texts, "label='Flooder #1: Sol & Sag için üret' group='Spam: Türler ve Ayarlar' ");
	TwAddSeparator(twBar_FloodCheats, NULL, "group='Spam: Türler ve Ayarlar' ");
	TwAddVarRW(twBar_FloodCheats, "Left Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Left_Random_Text_Lenght, " label='Flooder #1: Sol Yazi Uzunlugu' min=1 max=9 group='Spam: Türler ve Ayarlar' ");
	TwAddVarRW(twBar_FloodCheats, "Right Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Right_Random_Text_Lenght, " label='Flooder #1: Sag Yazi Uzunlugu' min=1 max=9 group='Spam: Türler ve Ayarlar' ");
	TwDefine(" 'Flood_Hacks'/'Spam: Türler ve Ayarlar' opened=false ");

	
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Target ID", TW_TYPE_INT32, &set.ChatHacks.iPMLagFloodID, " label='PM Spamlayici:Hedef Oyuncu ID' min=0 max=1000 group='PM Spam:Ayarlar' ");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Delay", TW_TYPE_INT32, &set.ChatHacks.iPMLagger_Run_Delay, " label='PM Spamlayici:Gecikme Süresi' min=100 max=10000 group='PM Spam:Ayarlar' ");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Delay", TW_TYPE_INT32, &set.ChatHacks.iPMLagger_Run_Delay, " label='PM Spamlayici:Gecikme Süresi' min=70 max=10000 group='PM Spam:Ayarlar' ");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION ||COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Delay", TW_TYPE_INT32, &set.ChatHacks.iPMLagger_Run_Delay, " label='PM Spamlayici:Gecikme Süresi' min=10 max=10000 group='PM Spam:Ayarlar' ");
#endif
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION ||COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Lenght", TW_TYPE_INT32, &set.ChatHacks.iPMLaggerText_Lenght, " label='PM Spamlayici:Yazi Uzunlugu' min=1 max=90 group='PM Spam:Ayarlar' ");
#else
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: Lenght", TW_TYPE_INT32, &set.ChatHacks.iPMLaggerText_Lenght, " label='PM Spamlayici:Yazi Uzunlugu' min=1 max=49 group='PM Spam:Ayarlar' ");
#endif
	TwAddVarRW(twBar_FloodCheats, "PM Flooder: CMD Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.iPMLagFloodCommandText)), &set.ChatHacks.iPMLagFloodCommandText, " label='Sunucunun Özel Mesaj Yollama Komutu Nedir?' min=1 max=6 group='PM Spam:Ayarlar' ");
	TwDefine(" 'Flood_Hacks'/'PM Spam:Ayarlar' opened=false ");

	/*TwType ClientSurumu = TwDefineEnum("ClientVer", NULL, 0);
	TwAddVarRW(twBar_RakNetCheats, "ClientVer", ClientSurumu, &set.ConnectionCheats.iFakeVersion, "label='Fake Client Version:' enum='0 { 0.3.7 -> OFF}, 1 { 0.3.7-R2 }, 2 { 0.3.7-R3 }, 3 { 0.3.7-R4 }' ");*/
#if COMPILE_RINA_RP_CLANS == COMPILE_FOR_WILLSON
	TwAddButton(twBar_RakNetCheats, "Knife Hack Uyari Mesaji", killAllUyari, NULL, " label='Knife Hack | Önce buna TIKLA' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #1", killAll, NULL, " label='Knife Hack #1' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #2", killAll2, NULL, " label='Knife Hack #2' ");
#endif
	///TwAddVarRW(twBar_RakNetCheats, "Knife Hack #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iKillAll, "label='Kill All | Knife Hack' ");
	TwAddButton(twBar_RakNetCheats, "Reconnect", reconnect, NULL, " label='Sunucuya Tekrar Baglan' group='Baglanti Fonksiyonlari' ");
	TwAddButton(twBar_RakNetCheats, "Fake Leave", fleave, NULL, " label='Sunucudan Cikis Yap' group='Baglanti Fonksiyonlari' ");
	TwAddButton(twBar_RakNetCheats, "Fake Timeout", ftimeout, NULL, " label='Sunucudan Cikis Yap[Crash]' group='Baglanti Fonksiyonlari' ");
	TwAddButton(twBar_RakNetCheats, "Fake Kick/Ban", fkick, NULL, " label='Sunucudan Cikis Yap[Kick/Ban]' group='Baglanti Fonksiyonlari' ");
	TwAddVarRW(twBar_RakNetCheats, "NPC Connection Info", TW_TYPE_BOOLCPP, &set.NPC_Connection_Checker, "label='NPC Bilgisi' group='Baglanti Fonksiyonlari' ");
	TwDefine(" 'RakNet_Funcs'/'Baglanti Fonksiyonlari' opened=false ");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	TwAddVarRW(twBar_RakNetCheats, "Connect As NPC", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iConnectAsNPC, "label='Connect As NPC' group='Exploitler' ");
	//TwAddVarRW(twBar_RakNetCheats, "Connect As Zombie", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iConnectAsZombie, "label='Connect As Zombie' group='Exploitler' ");
	TwAddVarRW(twBar_RakNetCheats, "Zero ping exploit", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iZeroPingExploit, "label='Zero Ping Exploit' group='Exploitler' ");
	TwAddButton(twBar_RakNetCheats, "Sky Crasher", skyCrasher, NULL, " label='Sky Crasher' group='Exploitler' ");
	TwAddButton(twBar_RakNetCheats, "Knife Hack #2", killAll2, NULL, " label='Kill All' group='Exploitler' ");
	TwDefine(" 'RakNet_Funcs'/'Exploitler' opened=false ");

#endif
	
	
	TwAddVarRW(twBar_RakNetCheats, "Use Fake GPCI", TW_TYPE_BOOLCPP, &set.bUse_Fake_GPCI, "label='Fake GPCI ID kullan' group='GPCI Ayarlari' ");
	TwAddVarRW(twBar_RakNetCheats, "Information about fake gpci", TW_TYPE_BOOLCPP, &set.Information_About_My_Fake_GPCI, "label='GPCI Hakkinda bilgi ver' group='GPCI Ayarlari' ");
	TwAddVarRW(twBar_RakNetCheats, "GPCI Info", TW_TYPE_BOOLCPP, &set.raknetSettings.bGPCI_info, "label='Yeni GPCI Bilgisini gör' group='GPCI Ayarlari' ");
	TwDefine(" 'RakNet_Funcs'/'GPCI Ayarlari' opened=true ");
	
	TwAddVarRW(twBar_RakNetCheats, "Aim", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingAimData, "label='Sunucuya Aim Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	TwAddVarRW(twBar_RakNetCheats, "Bullet", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingBulletData, "label='Sunucuya Bullet Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	TwAddVarRW(twBar_RakNetCheats, "Passenger", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPassengerData, "label='Sunucuya Passenger Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");

	TwAddVarRW(twBar_RakNetCheats, "Player", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPlayerData, "label='Sunucuya OnFoot Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	TwAddVarRW(twBar_RakNetCheats, "Trailer", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingTrailerData, "label='Sunucuya Trailer Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	//TwAddVarRW(twBar_RakNetCheats, "Unoccupied", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingUnoccupiedData, "label='Disable Sending Unoccupied Data' group='Disable Sending Some Data Packets' ");
	TwAddVarRW(twBar_RakNetCheats, "Vehicle", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingVehicleData, "label='Sunucuya Vehicle Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	TwAddVarRW(twBar_RakNetCheats, "Weapon", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingWeaponUpdateData, "label='Sunucuya Weapon Data Göndermeyi Kapat' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
	//TwAddVarRW(twBar_RakNetCheats, "Spec", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSpectatorSyncData, "label='Disable Sending Spectator Sync Data' group='Disable Sending Some Data Packets' ");
	TwDefine(" 'RakNet_Funcs'/'Sunucuya Gönderilen Paketler:Aç/Kapat' opened=false ");

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037 && COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	if (g_BotFuncs)
	{
		TwAddButton(twBar_Bots, "Add bot", botsMenu_addBot, NULL, " label='Add Bot' ");
		TwAddButton(twBar_Bots, "Delete bot", botsMenu_delBot, NULL, " label='Delete Bot' ");
		TwAddButton(twBar_Bots, "Spawn ALL b0Tz", botsMenu_SpawnAll, NULL, " label='Spawn All Bots' ");
		TwAddVarRW(twBar_Bots, "Bot Class Flooder", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bClassFlooder, "label='[Shitty-Servers]Bot Class Flooder' ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Use Fake Bot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.UseFakeBot, " label='Use Fake Bot' group='Fake Bot Settings' ");
		TwAddVarRW(twBar_Bots, "Fake Bot ID", TW_TYPE_INT32, &BotCheats->Target_PlayerID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
		TwDefine(" 'Bot_Options'/'Fake Bot Settings' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Rand0m quats", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandomQuaternions, " label='Bot Rand Quats' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot TwistMode", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTwistMode, " label='Bot Twist Mode' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot Upside Down", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUpsideDown, " label='Bot Head Walk' group='Bot OnFoot Functions' ");
		TwAddVarRW(twBar_Bots, "Bot Random Animations", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandAnim, " label='Bot Random Animations' group='Bot OnFoot Functions'  ");
		TwDefine(" 'Bot_Options'/'Bot OnFoot Functions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Tornado #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado, " label='Bot Tornado #1' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Tornado #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado2, " label='Bot Tornado #2' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Circle", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotCircle, "	label='Bot Circle' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Sun", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSun, " label='Bot Sun' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Shooter", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bShooter, " label='Bot Shooter' group='Bot OnFoot Actions'  ");
		TwAddVarRW(twBar_Bots, "Bot Storm", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bStorm, " label='Bot Storm' group='Bot OnFoot Actions'  ");
		TwDefine(" 'Bot_Options'/'Bot OnFoot Actions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Player Blocker", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotPlayerBlocker, " label='Bot Player Blocker' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Slapper", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSlapper, " label='Bot Player Slapper' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotElevator, " label='Bot Player Elevator' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Jetpack Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotJetpackElevator, " label='Bot Player Jetpack Elevator' group='Bot Troll Actions' ");
		TwAddVarRW(twBar_Bots, "Bot Player Fuck", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotFuck, " label='Bot Player Fucker' group='Bot Troll Actions' ");
		TwDefine(" 'Bot_Options'/'Bot Troll Actions' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot SpinBot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bSpinBot, " label='Bot SpinBot' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot SilentAim", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSilent, " label='Bot Silent' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot ShakingCamera #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera, " label='Bot Derp Cam #1' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot ShakingCamera #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera2, " label='Bot Derp Cam #2' group='Bot Aim Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Invalid Aim Z", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotInvalidAimZ, " label='Bot Invalid Aim Z' group='Bot Aim Funcs' ");
		TwDefine(" 'Bot_Options'/'Bot Aim Funcs' opened=false ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Remove Player Crasher!", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRemovePlayerCrasher, " label='Bot Remove Player Crasher' group='Bot Player Crashers' ");
		TwAddVarRW(twBar_Bots, "Bot Roll Crasher", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRollCrasher, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
		TwDefine(" 'Bot_Options'/'Bot Player Crashers' opened=false ");


		/*TwAddVarRW(twBar_Bots, "Bot Roll Crasher: Use Bot ID", TW_TYPE_BOOLCPP, &set.Bots.bUseRollCrasherBotID, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
		TwAddVarRW(twBar_Bots, "Bot Roll CRASHERZ: Bot ID", TW_TYPE_INT32, &set.Bots.bUseRollCrasherBotID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
		TwDefine(" 'Bot_Options'/'Bot Player Crashers Settings' opened=false ");*/
		/*

		*/
		//////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////// which ver? CP health, etcc v1.5
		TwAddVarRW(twBar_Bots, "CP Health", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyHealth, " label='Copy My Health Value' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Armor", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyArmor, " label='Copy My Armor Value' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Weapon", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyWeapon, " label='Copy My Weapon ID' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP Words", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyChat, " label='Copy My Words' group='Bot Copy Settings' ");
		TwAddVarRW(twBar_Bots, "CP RPCs", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyRPC, " label='Copy RPCs[Commands/Die]' group='Bot Copy Settings' ");
		TwDefine(" 'Bot_Options'/'Bot Copy Settings' opened=false ");
		//TwAddVarRW(twBar_Bots, "CP Anim ID", TW_TYPE_INT16, &g_BotFuncs->BotSettings.sBotFollowAnimID, " label='Bot Follow Me Animation ID' min=0 max=885 group='Bot Copy Settings' ");
		////////////////////////////////////////////////////////////////////
		//
		////////////////////////////////////////////////////////////////////
		TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Use Adjustable Nick for bots? ");
		TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Use Adjustable Tag for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Use Adjustable Split for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Use Bot Count method for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Use Random numbers for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");

		TwAddVarRW(twBar_Bots, "Update Send Rate", TW_TYPE_INT32, &g_BotFuncs->BotSettings.UpdateSendRate, " label='Bots: Update Send Rate' step=1 min=1 max=50 group='Bot Settings' ");
		TwDefine(" 'Bot_Options'/'Bot Settings' opened=false ");
		/* Bu gece 22.10.2019 -> 21:07 Aþaðýdaki yazýyý yorum satýrý yapmamýn sebebi milletin sik kafalý olmasýndan bir boku okuma alýþkanlýðý olmamasýndan dolayý... */

		/*TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Do you want to use Adjustable Nick for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Do you want to use Adjustable Tag for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Do you want to use Adjustable Split for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Do you want to use Bot Count method for bots?' ");
		TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Do you want to use Random numbers for bots?' ");
		TwAddSeparator(twBar_Bots, NULL, NULL);
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
		TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");*/

		TwType BotYaziTuru = TwDefineEnum("BotText", NULL, 0);
		TwAddVarRW(twBar_Bots, "Bot Flooder Type", BotYaziTuru, &set.Bots.Bot_ChatFlooder_Text_Type, " label='RAKNET Bot Chat Flood Type:' enum='1 {Use New Characters}, 2 {Only Binary Nums[0 & 1]}, 3{Only Numbers[0 & 9]}, 4 {Full Random}' group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot chat flood", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bChatFlooder, " label='Bot Chat Flood' group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Chat Flooder Letter length", TW_TYPE_INT32, &set.Bots.RAKNET_BOT_Flooder_Letter_Length, " label='Bot Chat Flooder Character/Letter Length' min=0 max=9 group='Bot Chat Funcs' ");
		TwAddVarRW(twBar_Bots, "Bot Flooder Text", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Chat_Text)), &set.Bots.RAKNET_BOT_Chat_Text, " label='Bot Flooder Text:' group='Bot Chat Funcs' ");
		TwDefine(" 'Bot_Options'/'Bot Chat Funcs' opened=false ");

	}
#endif

#else
		TwType ActorFlyType = TwDefineEnum("FlyType", NULL, 0);
		TwAddVarRW(twBar_GeneralCheats, "Player Fly Type", ActorFlyType, &set.General.Actor_Fly_Type, " label='Actor Fly Type:' enum='1 { Swiming }, 2 { Boss Fly }, 3 { Bike } ' ");
		TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi yazi", TW_TYPE_CSSTRING(sizeof(set.D3DFeatures.friendtext)), &set.D3DFeatures.friendtext, " label='Friend Text' min=1 max=25 group='Visual Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "rainbowhudtitle", TW_TYPE_BOOLCPP, &set.D3DFeatures.Use_Rainbow_Title_for_NewHUD, "label='Rainbow HUD' group='Visual Settings' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Visual Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Friend List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForFriendList, " label='Friend List:X Coords' min=-200.0f max=300.0 group='Visual Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Admin List X Pos", TW_TYPE_FLOAT, &set.D3DFeatures.fXPosFixForAdminList, " label='Admin List:X Coords' min=-200.0f max=300.0 group='Visual Settings' ");
		TwDefine(" 'Cheat_Settings'/'Visual Settings' opened=false ");

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		TwType CrasherType = TwDefineEnum("CrasherType", NULL, 0);
		TwAddVarRW(twBar_GeneralCheats, "IBC fOnFootZPos", TW_TYPE_FLOAT, &set.invalidBullets.fOnFootPosZ, " label='Invalid Bullets Crasherler: OnFoot Z Koordinati[-5.5 Kullanma!]' min=-6.0 max=15.0 group='Crasher Ayarlari' ");
		TwAddVarRW(twBar_GeneralCheats, "IBCs: Delay", TW_TYPE_INT32, &set.invalidBullets.dwDelayOfInvalidBullets, " label='Invalid Bullets Crasherler: Gecikme Süreleri' step=25 min=50 max=500 group='Crasher Ayarlari' ");
		TwAddVarRW(twBar_GeneralCheats, "Send Give Damage", TW_TYPE_BOOLCPP, &set.invalidBullets.bSendGiveDamage, " label='Bypass Invalid Bullets Crasher | RPC_GiveTakeDamage' group='Crasher Ayarlari' ");
		TwDefine(" 'Cheat_Settings'/'Crasher Ayarlari' opened=false ");

		TwAddVarRW(twBar_GeneralCheats, "IBC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher1, " label='Invalid Bullets Crasher #1' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "IBC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher2, " label='Invalid Bullets Crasher #2' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "IBC #3", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher3, " label='Invalid Bullets Crasher #3' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "IBC #4", TW_TYPE_BOOLCPP, &cheat_state->crasher.iInvalidBulletsCrasher4, " label='Invalid Bullets Crasher #4' group='Developer Crasherleri' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "RC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher1, " label='Roll Crasher #1' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "RC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iRollCrasher2, " label='Roll Crasher #2' group='Developer Crasherleri' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "DC #1", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher1, " label='Direction Crasher #1' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "DC #2", TW_TYPE_BOOLCPP, &cheat_state->crasher.iDirectionCrasher2, " label='Direction Crasher #2' group='Developer Crasherleri' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Game Sound Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iGameSoundCrasher, " label='Game Sound Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Enter Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iEnterPlayerCrasher, " label='Enter Vehicle Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Remove Player Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicRemovePlayerCrasher, " label='Detonator Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Tuning Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicTuningCrasher, " label='Tuning Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Pass Crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iPublicPassengerCrasher, " label='Pass Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Test crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iCrashertest, " label='Test Crasher' group='Developer Crasherleri' ");
		TwAddVarRW(twBar_GeneralCheats, "Weapon crasher", TW_TYPE_BOOLCPP, &cheat_state->crasher.iWeaponCrasher, " label='Weapon Crasher' group='Developer Crasherleri' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Developer Crasherleri' ");
		TwDefine(" 'Cheat_Settings'/'Developer Crasherleri' opened=false ");


		TwAddVarRW(twBar_GeneralCheats, "Aim Log", TW_TYPE_BOOLCPP, &cheat_state->developerPanel.bLogAimData, " label='Log AimData' group='Developer Paneli' ");
		TwAddVarRW(twBar_GeneralCheats, "SilentAim", TW_TYPE_BOOLCPP, &cheat_state->Korumalar.iAntiSilentAim, " label='Anti Silent Aim & WallShot' group='Developer Paneli' ");
		TwAddVarRW(twBar_GeneralCheats, "Hileci Listesi", TW_TYPE_BOOLCPP, &cheat_state->PrivateControlPanel.bEnablePanel, " label='Proje Kullanicilarini Gör' group='Developer Paneli' ");
		TwDefine(" 'Cheat_Settings'/'Developer Paneli' opened=false ");
#endif

		TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon, " label='Bypass Weapon Cheat #1' group='Bypass Weapon Cheats' ");
		TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon2, " label='Bypass Weapon Cheat #2' group='Bypass Weapon Cheats' ");
		TwAddVarRW(twBar_GeneralCheats, "Weapon Cheat #3", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon3, " label='Bypass Weapon Cheat #3' group='Bypass Weapon Cheats' ");
		TwDefine(" 'Cheat_Settings'/'Bypass Weapon Cheats' opened=false ");

		//set.rainbowdelay

		TwAddVarRW(twBar_GeneralCheats, "afk", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreAFKs, "label='AFK Filter' group='General Cheat Filters' ");
		TwAddVarRW(twBar_GeneralCheats, "dead", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreDEADs, "label='Dead Filter' group='General Cheat Filters ");
		TwAddSeparator(twBar_AimFuncs, NULL, NULL);
		TwAddVarRW(twBar_GeneralCheats, "Color", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameColor, "label='Color Filter' group='General Cheat Filters' ");
		TwAddVarRW(twBar_GeneralCheats, "skin", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameSkinID, "label='Skin Filter' group='General Cheat Filters' ");
		TwAddVarRW(twBar_GeneralCheats, "team", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreSameTeam, "label='Team Filter' group='General Cheat Filters' ");
		TwAddVarRW(twBar_GeneralCheats, "friend", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreMyFriends, "label='Friend Filter' group='General Cheat Filters' ");
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		TwAddVarRW(twBar_GeneralCheats, "project user", TW_TYPE_BOOLCPP, &cheat_state->filters.bIgnoreProjectUsers, "label='Proje Kullanicilari Filtresi' group='General Cheat Filters' ");
#endif
		TwDefine(" 'Cheat_Settings'/'General Cheat Filters' opened=false ");

		TwAddVarRW(twBar_GeneralCheats, "RapidFire: Delay", TW_TYPE_INT32, &set.WeaponCheats.dwRapidFireDelay, " label='RapidFire: Delay' min=70 max=2500 group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Rainbow Kullan", TW_TYPE_BOOLCPP, &set.bUseRainbowColors, " label='Use Rainbow' group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Rainbow Delay", TW_TYPE_FLOAT, &set.rainbowdelay, " label='Rainbow: Delay' min=0.100 max=1000.0 group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "MapRun Speed", TW_TYPE_FLOAT, &set.General.MapRun_Speed, " label='MapRun Speed' min=0.5 max=10.0 group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Unsynch Radius", TW_TYPE_INT32, &set.Unsynch_Radius, " label='Unsynch:Radius' min=20 max=500 group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Speed Walk", TW_TYPE_FLOAT, &set.General.SpeedWalk_X, " label='Speed Walk: X' step=0.1 min=0.1 max=1.0 group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Unsynch senkronize", TW_TYPE_BOOLCPP, &set.See_How_UnSynch_Works, "label='Fake Trolleyici: Pozisyonu Gör' group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Dost Etiketi", TW_TYPE_BOOLCPP, &set.D3DFeatures.bDrawFriendTag, " label='Friend Tag' group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Rapid Fire:Teleport sistemi", TW_TYPE_BOOLCPP, &set.WeaponCheats.bTeleportForRapidFire, " label='Rapid Fire: Teleport Func' group='General Cheat Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "God Fly: X", TW_TYPE_FLOAT, &set.General.fGodFlySpeed[0], " label='Uçma: HIZ' step=0.1 min=0.1 max=5.0 group='General Cheat Settings' ");
		//TwAddVarRW(twBar_GeneralCheats, "God Fly: Y", TW_TYPE_FLOAT, &set.General.fGodFlySpeed[1], " label='God Fly: Y Hizi' step=0.1 min=0.1 max=4.0 group='God Fly Settings' ");
		TwDefine(" 'Cheat_Settings'/'General Cheat Settings' opened=false ");

		TwAddVarRW(twBar_GeneralCheats, "Double Gun #1 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun1_Delay, " label='Double Gun #1 Delay' min=250 max=2000 group='Deagle/Shotgun: Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Delay", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_Delay, " label='Double Gun #2 Delay' min=250 max=2000 group='Deagle/Shotgun: Settings' ");
		TwAddSeparator(twBar_GeneralCheats, NULL, "group='Deagle/Shotgun: Ayarlar' ");
		TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #1", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot1, " label='Double Gun #2 Weapon Slot #1' min=0 max=6 group='Deagle/Shotgun: Settings' ");
		TwAddVarRW(twBar_GeneralCheats, "Double Gun #2 Weapon Slot #2", TW_TYPE_INT32, &set.WeaponCheats.iDoubleGun2_WeaponSlot2, " label='Double Gun #2 Weapon Slot #2' min=0 max=6 group='Deagle/Shotgun: Settings' ");
		TwDefine(" 'Cheat_Settings'/'Deagle/Shotgun: Settings' opened=false ");

		TwType gWeapon = TwDefineEnum("gWeapon", NULL, 0);
		TwAddVarRW(twBar_GeneralCheats, "Weapon Name:", gWeapon, &set.WeaponCheats.GiveWeapon_WeaponID, " label='Weapon Name:' enum='0 {Yumruk}, 1 {Musta}, 2 {Golf Sopasi}, 3 {Jop}, 4 {Bicak}, 5 {Bat}, 6 {Kürek}, 7 {Bilardo Sopasi}, 8 {Katana}, 9 {Testere}, 10 {Dildo #1}, 11 {Dildo #2}, 12 {Vibratör #1}, 13 {Vibratör #2}, 14 {Çiçek}, 15 {Cane}, 16 {Bomba}, 17 {Gaz Bombasi}, 18 {Molotof}, 22 {Colt45}, 23 {Susturuculu Colt45}, 24 {Deagle}, 25 {Shotgun}, 26 {Sawn Off Shotgun}, 27 {Combat Shotgun}, 28 {Uzi}, 29 {MP5}, 30 {AK47}, 31 {M4}, 32 {TEC9}, 33 {Cuntgun}, 34 {Sniper}, 35 {Roket}, 36 {Isi Duyarli Roket}, 37 {Alev Püskürtücü}, 38 {Minigun}' group='Give Weapon' ");
		TwAddVarRW(twBar_GeneralCheats, "Weapon Ammo:", TW_TYPE_INT32, &set.WeaponCheats.GiveWeapon_Ammo_Amount, " label='Weapon Ammo:' step=100 min=1 max=10000 group='Give Weapon' ");
		TwAddButton(twBar_GeneralCheats, "Get Gun", weaponMenu_GiveWeaponWithAmmo, NULL, " label='Get Gun' group='Give Weapon' ");
		TwDefine(" 'Cheat_Settings'/'Give Weapon' opened=false ");
	
		TwAddVarRW(twBar_CarCheats, "Car Remote Control", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarRemoteControl, " label='Car Remote Control' group='Car Remote Control' ");
		TwAddVarRW(twBar_CarCheats, "Car Remote Control With Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_with_driver, " label='Car Remote Control: Driver Mod' group='Car Remote Control' ");
		TwAddVarRW(twBar_CarCheats, "Car Remote Control Without Driver", TW_TYPE_BOOLCPP, &set.CarCheats.car_remote_control_without_driver, " label='Car Remote Control: Non-Drive Mod' group='Car Remote Control' ");
		TwDefine(" 'Car_Hacks'/'Car Remote Control' opened=false ");

		TwAddVarRW(twBar_CarCheats, "Car Lag X Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[0], " label='Car Lag X Axis' min=-10 max=150  group='Car Lagger' ");
		TwAddVarRW(twBar_CarCheats, "Car Lag Y Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[1], " label='Car Lag Y Axis' min=-10 max=150  group='Car Lagger' ");
		TwAddVarRW(twBar_CarCheats, "Car Lag Z Axis", TW_TYPE_INT32, &set.CarCheats.CarLagger_Coords[2], " label='Car Lag Z Axis' min=-15 max=50   group='Car Lagger' ");
		TwDefine(" 'Car_Hacks'/'Car Lagger' opened=false ");

		TwAddVarRW(twBar_CarCheats, "Car Sun Angle", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Angle, " label='Car Sun Angle' step=10.0 min=0.0 max=180.00 group='Car Sun' ");
		TwAddVarRW(twBar_CarCheats, "Car Sun Z Height", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Z_Position_Height, " label='Car Sun Z Height step=10.0 min=0.0 max=100.00 group='Car Sun' ");
		TwAddVarRW(twBar_CarCheats, "Car Sun Abs Speed", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Abs_Speed, " label='Car Sun Abs Speed' step=10.0 min=0.0 max=100.00 group='Car Sun' ");
		TwAddVarRW(twBar_CarCheats, "Car Sun Degree To Radian Value", TW_TYPE_FLOAT, &set.CarCheats.Car_Sun_Degree_To_Radian_Value, " label='Car Sun Degree To Radian Value' step=10.0 min=5.0 max=200.00 group='Car Sun' ");
		TwDefine(" 'Car_Hacks'/'Car Sun' opened=false ");

		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Z Height", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Z_Height, " label='Car Circle #2: Use Random Z Height' group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Minimum_Value, " label='Car Circle #2: Minimum Random Value' step=6.0 min=7.0 max=50.00 group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Z_Height_Maximum_Value, " label='Car Circle #2: Maximum Random Value' step=6.0 min=7.0 max=50.00 group='Car Circle #2: Settings' ");
		TwAddSeparator(twBar_CarCheats, NULL, "group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Use Random Radius", TW_TYPE_BOOLCPP, &set.CarCheats.bCarCircle_Use_Random_Radius, " label='Car Circle #2: Use Random Radius' group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Minimum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Minimum_Value, " label='Car Circle #2: Minimum Random Value for Radius' step=6.0 min=7.0 max=90.00 group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Maximum Random Value for Radius", TW_TYPE_FLOAT, &set.CarCheats.fCarCircle_Random_Radius_Maximum_Value, " label='Car Circle #2: Maximum Random Value for Radius' step=6.0 min=7.0 max=90.00 group='Car Circle #2: Settings' ");
		TwAddSeparator(twBar_CarCheats, NULL, "group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Radius", TW_TYPE_FLOAT, &set.CarCheats.CarCircle3_Radius, " label='Car Circle #2: Radius' step=6.0 min=7.0 max=150.00 group='Car Circle #2: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Circle #2: Z Height", TW_TYPE_FLOAT, &set.CarCheats.CarCircle_Z_Height, " label='Car Circle #2: Z Height' step=6.0 min=2.0 max=70.00 group='Car Circle #2: Settings' ");
		TwDefine(" 'Car_Hacks'/'Car Circle #2: Settings' opened=false ");

		TwAddVarRW(twBar_CarCheats, "Car Floating #3:X Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[0], " label='Car Floating #3:X Max Random Value' step=10 min=15 max=350 group='Car Floating #3: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Floating #3:Y Max Random Value", TW_TYPE_INT32, &set.CarCheats.fCarFloating3_Random_Value[1], " label='Car Floating #3:Y Max Random Valu' step=10 min=15 max=350 group='Car Floating #3: Settings' ");
		TwAddVarRW(twBar_CarCheats, "Car Floating #3:Z Height", TW_TYPE_FLOAT, &set.CarCheats.fCarFloating3_Z_Height, " label='Car Floating #3:Z Height' step=6.0 min=3.0 max=70.00 group='Car Floating #3: Settings' ");
		TwDefine(" 'Car_Hacks'/'Car Floating #3: Settings' opened=false ");

		TwAddVarRW(twBar_CarCheats, "Crazy Car #1 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar1_Delay, " label='Crazy Car #1 Delay' step=100 min=100 max=4500 group='Crazy Car Settings' ");
		TwAddVarRW(twBar_CarCheats, "Crazy Car #2 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar2_Delay, " label='Crazy Car #2 Delay' step=100 min=100 max=4500 group='Crazy Car Settings' ");
		TwAddVarRW(twBar_CarCheats, "Crazy Car #3 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar3_Delay, " label='Crazy Car #3 Delay' step=100 min=100 max=4500 group='Crazy Car Settings' ");
		TwAddVarRW(twBar_CarCheats, "Crazy Car #4 Delay", TW_TYPE_INT32, &set.CarCheats.iCrazyCar4_Delay, " label='Crazy Car #4 Delay' step=100 min=100 max=4500 group='Crazy Car Settings' ");
		TwDefine(" 'Car_Hacks'/'Crazy Car Settings' opened=false ");
		//TwAddSeparator(twBar_CarCheats, NULL, "group='Araç Renkleri #1-#4: Ayarlar' ");

		/*
			Added Delay settings for Crazy Car #1, #2, #3, #4.
			iTroll Places is changed.. It is on F2 menu -> Troll Cheats menu anymore.
		*/

		/*
		<- Aim Functions & Aim Fonksiyonlarý ->
		*/
		TwAddButton(twBar_AimFuncs, "Rage Hacking", AreYouRageCheater, NULL, " label='Click here for Rage' ");
		TwAddButton(twBar_AimFuncs, "Legit Hacking", AreYouLegitCheater, NULL, " label='Click here for Legit' ");
		TwType AimBotType = TwDefineEnum("AimBotType", NULL, 0);
		TwAddVarRW(twBar_AimFuncs, "AimBot Lock To:", AimBotType, &set.AutoAimPozisyon, " label='AimBot Lock To:' enum='0 {Head}, 1 {Spine #1}, 2 {Spine #2}, 3 {Spine #3}, 4 {Üst Gövde}, 5 {neck}, 6 {Right Upper Torso}, 8 {Body}' ");

		TwAddVarRW(twBar_AimFuncs, "SilentAim", TW_TYPE_BOOLCPP, &cheat_state->Silent.bSilent, " label='Silent Aim' ");
		TwAddVarRW(twBar_AimFuncs, "Shoot Through Walls", TW_TYPE_BOOLCPP, &cheat_state->Silah.iShooting_Through_Walls, " label='Shoot Through Walls' ");
		TwAddVarRW(twBar_AimFuncs, "Shoot Through Walls | Fix BETA", TW_TYPE_BOOLCPP, &cheat_state->Silah.iShooting_Through_WallsBypass, " label='Shoot Through Walls | Fix BETA' ");
		//TwAddVarRW(twBar_AimFuncs, "Bypass AC", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassAimAntiCheat, " label='Silent Aim: Anti Cheat Bypass #1' ");
		TwAddSeparator(twBar_AimFuncs, NULL, NULL);
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Hit Chance", TW_TYPE_INT32, &set.silentAim.iHitChanceValue, " label='SilentAim Setting -> Hit Chance' min=5 max=100 group='Silent Aim:Legit Settings' ");
		TwDefine(" 'Aim_Funcs'/'Silent Aim:Legit Settings' opened=false ");

		TwType targetType = TwDefineEnum("targetType", NULL, 0);
		TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Hedef Çizim Türü", targetType, &set.silentAim.targetType, " label='Silent Aim: Text Type' enum='0 { Text }, 1 { Nothing }' group='SilentAim: Target Info #1' ");
		//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Circle Radius", TW_TYPE_FLOAT, &set.silentAim.fCircleRadius, " label='SilentAim:Daire Büyüklügü' min=5.0 max=500.0 group='SilentAim Ayarlar:Hedef Bilgisi #1' ");
		TwDefine(" 'Aim_Funcs'/'SilentAim: Target Info #1' opened=true ");

		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Draw Target Bones", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBones, " label='SilentAim Setting -> Draw Target Bones' group='SilentAim: Target Info #2' ");
		TwType colorType1 = TwDefineEnum("ColorType1", NULL, 0);
		TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: Hedef Çizimi", colorType1, &set.silentAim.iDrawBoneColor, " label='Hedef iskeleti:Renk' enum='0 { Oyuncunun Rengini Kullan }, 1 { Kirmizi Renk }, 2 { Yesil Renk }, 3 { Mavi Renk }, 4 { Siyah Renk }, 5 { Beyaz Renk }, 6 { Altin Rengi }, 7 { Gümüs Renk }, 8 { Gece Mavisi Rengi }, 9 { Su Rengi }, 10 { Kestane Rengi }, 11 { Rainbow Kullan }' group='SilentAim: Target Info #2' ");
		TwDefine(" 'Aim_Funcs'/'SilentAim: Target Info #2' opened=true ");

		//TwAddSeparator(twBar_AimFuncs, NULL, "group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
		TwType colorType2 = TwDefineEnum("ColorType2", NULL, 0);
		TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: ESP: Aç ", TW_TYPE_BOOLCPP, &cheat_state->Silah.iDrawTargetBox, " label='SilentAim:ESP' group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Ayarlar: ESP Renk", colorType2, &set.silentAim.iDrawBoxColor, " label='ESP:Color' enum='0 { Oyuncunun Rengini Kullan }, 1 { Kirmizi Renk }, 2 { Yesil Renk }, 3 { Mavi Renk }, 4 { Siyah Renk }, 5 { Beyaz Renk }, 6 { Altin Rengi }, 7 { Gümüs Renk }, 8 { Gece Mavisi Rengi }, 9 { Su Rengi }, 10 { Kestane Rengi }, 11 { Rainbow Kullan }' group='SilentAim Ayarlar:Hedef Bilgisi #3' ");
		TwDefine(" 'Aim_Funcs'/'SilentAim: Target Info #3' opened=true ");

		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Out Of Range", TW_TYPE_BOOLCPP, &set.silentAim.bOutOfRange, " label='SilentAim: Out Of Range Filter' group='Silent Aim: Filter' ");
		TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Same Team Filter", TW_TYPE_BOOLCPP, &set.silentAim.bTeamFilter, " label='SilentAim: team Filter' group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Nick Name Color Filter", TW_TYPE_BOOLCPP, &set.silentAim.bColorFilter, " label='SilentAim: color Filter' group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Skin Filter", TW_TYPE_BOOLCPP, &set.silentAim.bSkinFilter, " label='SilentAim: Skin Filter' group='Silent Aim: Filter' ");
		TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Visible Target Filter", TW_TYPE_BOOLCPP, &set.silentAim.bVisibleFilter, " label='SilentAim: visible Filter' group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> AFK Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAFKFilter, " label='SilentAim: AFK Filter' group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Alive Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAliveFilter, " label='SilentAim: Dead Filter' group='Silent Aim: Filter' ");
		TwAddSeparator(twBar_AimFuncs, NULL, " group='Silent Aim: Filter' ");
		// NPC Filtresine gerek yok...
		//TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore NPCs Filter", TW_TYPE_BOOLCPP, &cheat_state->Silah.iSAim_IgnoreNPCs, " label='SilentAim: NPC Filtresi' group='Silent Aim: Filtreler' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Admins[IN ADMINS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bAdminFilter, " label='SilentAim: Admin Filter' group='Silent Aim: Filter' ");
		TwAddVarRW(twBar_AimFuncs, "SilentAim Setting -> Ignore Friends[IN FRIENDS LIST] Filter", TW_TYPE_BOOLCPP, &set.silentAim.bFriendFilter, " label='SilentAim: Friend Filter' group='Silent Aim: Filter' ");
		TwDefine(" 'Aim_Funcs'/'Silent Aim: Filter' opened=true ");

		TwType spinType = TwDefineEnum("spinSettings", NULL, 0);
		TwAddVarRW(twBar_AimFuncs, "SpinBot Type", spinType, &cheat_state->Silah.iSpinBotType, " label='Spinbot Type:' enum='0 { KAPALI }, 1 { UP }, 2 { Down }, 3 { Random }' group='Spinbot' ");
		TwDefine(" 'Aim_Funcs'/'Spinbot' opened=false ");

		TwAddVarRW(twBar_AimFuncs, "SyncSpinBot", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.iSyncSpinBotTypes, " label='SpinBot:Sync' ");
		TwAddVarRW(twBar_AimFuncs, "InvalidAimZ:Sync", TW_TYPE_BOOLCPP, &set.aimCheatsSettings.bSyncInvalidAimZPed, " label='Aim Z:Sync' ");

		TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #1", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon, " label='Bypass Weapon Cheat #1' group='Silah Hilesi Atlatma Yöntemleri' ");
		TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon2, " label='Bypass Weapon Cheat #2' group='Silah Hilesi Atlatma Yöntemleri' ");
		TwAddVarRW(twBar_weaponCheats, "Silah Hilesi Atlatma Yöntemi #3", TW_TYPE_BOOLCPP, &cheat_state->Silah.iBypassWeapon3, " label='Bypass Weapon Cheat #3' group='Silah Hilesi Atlatma Yöntemleri' ");
		TwDefine(" 'Weapon_Funcs'/'Silah Hilesi Atlatma Yöntemleri' opened=true ");
		TwAddSeparator(twBar_weaponCheats, NULL, "");
		TwType iTrollType = TwDefineEnum("iTrollType", NULL, 0); // cheat_state->Troll.iInvisible5
		TwAddVarRW(twBar_TrollFuncs, "iTroll Type", iTrollType, &cheat_state->Troll.iTroll, " label='iTroll Türü:' enum='0 { iTroll KAPALI }, 1 { iTroll #1 }, 2 { iTroll #2 }, 3 { iTroll #3 }, 4 { iTroll #4 }, 5 { iTroll #5 }, 6 { iTroll #6 }, 7 { iTroll #7 }, 8 { iTroll #8 }, 9 { iTroll #9 }, 10 { iTroll #10 }, 11 { iTroll #11 }, 12 { iTroll #12 }, 13 { iTroll #13 }, 14 { iTroll #14 }, 15 { iTroll #15 }, 16 { iTroll #16 }, 17 { iTroll #17 }, 18 { iTroll #18 }, 19 { iTroll #19 }' ");
		TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
		TwAddVarRW(twBar_TrollFuncs, "iTroll: HP degeri", TW_TYPE_FLOAT, &set.itrollSettings.fSetHP, " label='iTroll:Set HP ' min=1.0 max=1000.0 group='iTroll' ");
		TwAddVarRW(twBar_TrollFuncs, "Görünmezlik #14", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible14, " label='Pass/Drive-By Mode | GodMode' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible Bike", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisibleBike, " label='Invisible Bike' ");
		TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
		//TwAddVarRW(twBar_TrollFuncs, "Invisible Cars", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCarInvisible, " label='Görünmezlik[Araç]' ");
		TwAddVarRW(twBar_TrollFuncs, "Delete Cars #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars, " label='Car Deleter #1' ");
		TwAddVarRW(twBar_TrollFuncs, "Delete Cars #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iRemoveCars2, " label='Car Deleter #2' ");
		TwAddVarRW(twBar_TrollFuncs, "Vehicle Deformer", TW_TYPE_BOOLCPP, &cheat_state->Arac.iVehicleDeformer, " label='Car Deformation' ");
		TwAddSeparator(twBar_TrollFuncs, NULL, NULL);
		TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iCircleTroll, " label='Circle Troll: Enable' group='Circle Troll' ");
		TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Target ID", TW_TYPE_INT32, &set.TrollCheats.CircleTrollTargetID, " label='Circle Troll: Target ID' min=0 max=1000 group='Circle Troll' ");
		TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Spin Speed", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Spin_Speed, " label='Circle Troll: Spin Speed' min=0 max=100 group='Circle Troll' ");
		TwAddVarRW(twBar_TrollFuncs, "Circle Troll: Circle Radius", TW_TYPE_INT32, &set.TrollCheats.CircleTroll_Circle_Radius, " label='Circle Troll: Circle Radius' min=1 max=100 group='Circle Troll' ");
		TwDefine(" 'Troll_Cheats'/'Circle Troll' opened=false ");
		TwAddVarRW(twBar_TrollFuncs, "Player Copier: Enable", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerCopier, " label='Player Copier: Enable' group='Player Copier' ");
		TwAddVarRW(twBar_TrollFuncs, "Player Copier: Target ID", TW_TYPE_INT32, &set.TrollCheats.iPlayerCopier_TargetID, " label='Player Copier: Target ID' min=0 max=1000 group='Player Copier' ");
		TwAddVarRW(twBar_TrollFuncs, "Player Copier: Sync Player Copier", TW_TYPE_BOOLCPP, &set.TrollCheats.bSyncPlayerCopier, " label='Player Copier: Sync Player Copier' group='Player Copier' ");
		TwDefine(" 'Troll_Cheats'/'Player Copier' opened=false ");


		TwAddVarRW(twBar_TrollFuncs, "Invisible #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible1, " label='Invisible #1' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible2, " label='Invisible #2' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible3, " label='Invisible #3' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible4, " label='Invisible #4' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible5, " label='Invisible #5' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible6, " label='Invisible #6' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible7, " label='Invisible #7' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #8", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible8, " label='Invisible #8' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #9", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible9, " label='Invisible #9' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #10", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible10, " label='Invisible #10' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #11", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible11, " label='Invisible #11' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #12", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible12, " label='Invisible #12' group='Invisible Funcs' ");
		TwAddVarRW(twBar_TrollFuncs, "Invisible #13", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible13, " label='Invisible #13' group='Invisible Funcs' ");
		//TwAddVarRW(twBar_TrollFuncs, "Invisible #15", TW_TYPE_BOOLCPP, &cheat_state->Troll.iInvisible15, " label='Invisible #15' group='Invisibleler' ");
		TwDefine(" 'Troll_Cheats'/'Invisible Funcs' opened=true ");

		TwAddVarRW(twBar_TrollFuncs, "Slapper #1", TW_TYPE_BOOLCPP, &cheat_state->Troll.iPlayerFucker, " label='Slapper #1' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #2", TW_TYPE_BOOLCPP, &cheat_state->Troll.iHeadWalkSlapper, " label='Slapper #2' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #3", TW_TYPE_BOOLCPP, &cheat_state->Troll.iQuaSlapper, " label='Slapper #3' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #4", TW_TYPE_BOOLCPP, &cheat_state->Troll.iSpeedKicker, " label='Slapper #4' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #5", TW_TYPE_BOOLCPP, &cheat_state->Troll.iActorShooter, " label='Detected | Slapper #5' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #6", TW_TYPE_BOOLCPP, &cheat_state->Troll.iElevator, " label='Detected | Slapper #6' group='Slappers' ");
		TwAddVarRW(twBar_TrollFuncs, "Slapper #7", TW_TYPE_BOOLCPP, &cheat_state->Troll.iJetpackElevator, " label='Detected | Slapper #7' group='Slappers' ");
		TwDefine(" 'Troll_Cheats'/'Slappers' opened=false ");

		TwAddVarRW(twBar_TrollFuncs, "Undetected Invisible[En Düsük Random Deger]", TW_TYPE_FLOAT, &set.TrollCheats.fUDInvisibleMinValue, " label='Undetected Invisible min' min=2.9 max=5.9 group='Invisible #5:Ayarlar' ");
		TwAddVarRW(twBar_TrollFuncs, "Undetected Invisible[En Yüksek Random Deger]", TW_TYPE_FLOAT, &set.TrollCheats.fUDInvisibleMaxValue, " label='Undetected Invisible max' min=6.0 max=13.5 group='Invisible #5:Ayarlar' ");
		//TwAddSeparator(twBar_TrollFuncs, NULL, "group='Görünmezlik Hilelerinin Ayarlari' ");
		TwDefine(" 'Troll_Cheats'/'Invisible #5:Ayarlar' opened=false ");
		// Flooder faktörleri...
		TwAddVarRW(twBar_FloodCheats, "Spammer #1 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer1_Text)), &set.ChatHacks.Project_Spammer1_Text, " label='Flooder #1: Text' group='Spam: text' ");
		//TwAddVarRW(twBar_FloodCheats, "Spammer #2 Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.Project_Spammer2_Text)), &set.ChatHacks.Project_Spammer2_Text, " label='Flooder #2 Text' group='Flooder Text Settings' ");
		TwDefine(" 'Flood_Hacks'/'Spam: text' opened=false ");

		TwAddVarRW(twBar_FloodCheats, "Spammer #1 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer1_Run_Delay, " label='Flooder #1: Gecikme Süresi' min=50 max=10000 group='Spam: Zamanlama Ayarlari' ");
		//TwAddVarRW(twBar_FloodCheats, "Spammer #2 -> Run Delay", TW_TYPE_INT32, &set.ChatHacks.Project_Spammer2_Run_Delay, " label='Flooder #2 -> Run Delay' min=50 max=10000 group='Flooder Delay/Run Settings' ");
		TwDefine(" 'Flood_Hacks'/'Spam: Zamanlama Ayarlari' opened=false ");

		TwType FlooderType = TwDefineEnum("FlooderType", NULL, 0);
		TwAddVarRW(twBar_FloodCheats, "Random Texts Flooder Type:", FlooderType, &set.ChatHacks.bSpammer1_Random_Texts_Random_Type, " label='Flooder #1: Üretici Türü' enum='1 { Sadece: A-Z & a-z }, 2 { Sadece: A-Z }, 3 { Sadece: a-z }, 4 { Sadece: 0-9 }, 5 { Sadece: 0 & 1 }, 6 { Sadece Özel Karakterler }' group='Spammer' ");
		TwAddSeparator(twBar_FloodCheats, NULL, "group='Spammer' ");
		TwAddVarRW(twBar_FloodCheats, "Use Left Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Left_Random_Texts, "label='Use Left Random Texts for Flooder #1' group='Spammer' ");
		TwAddVarRW(twBar_FloodCheats, "Use Right Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Right_Random_Texts, "label='Use Right Random Texts for Flooder #1' group='Spammer' ");
		TwAddVarRW(twBar_FloodCheats, "Use Both Random Texts for Flooder #1", TW_TYPE_BOOLCPP, &set.ChatHacks.bUseSpammer1_Both_Random_Texts, "label='Use Both Random Texts for Flooder #1' group='Spammer' ");
		TwAddSeparator(twBar_FloodCheats, NULL, "group='Spammer' ");
		TwAddVarRW(twBar_FloodCheats, "Left Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Left_Random_Text_Lenght, " label='Left Random Text Lenght for Flooder #1' min=1 max=9 group='Spammer' ");
		TwAddVarRW(twBar_FloodCheats, "Right Random Text Lenght for Flooder #1", TW_TYPE_INT32, &set.ChatHacks.sSpammer1_Right_Random_Text_Lenght, " label='Right Random Text Lenght for Flooder #1' min=1 max=9 group='Spammer' ");
		TwDefine(" 'Flood_Hacks'/'Spammer' opened=false ");


		TwAddVarRW(twBar_FloodCheats, "PM Flooder: Target ID", TW_TYPE_INT32, &set.ChatHacks.iPMLagFloodID, " label='PM Flooder: Target ID' min=0 max=1000 group='PM Spam:Cheats' ");
		TwAddVarRW(twBar_FloodCheats, "PM Flooder: Lenght", TW_TYPE_INT32, &set.ChatHacks.iPMLaggerText_Lenght, " label='PM Flooder: Lenght' min=1 max=49 group='PM Spam:Cheats' ");
		TwAddVarRW(twBar_FloodCheats, "PM Flooder: CMD Text", TW_TYPE_CSSTRING(sizeof(set.ChatHacks.iPMLagFloodCommandText)), &set.ChatHacks.iPMLagFloodCommandText, " label='PM Flooder: CMD Text' min=1 max=6 group='PM Spam:Cheats' ");
		TwDefine(" 'Flood_Hacks'/'PM Spam:Cheats' opened=false ");

		/*TwType ClientSurumu = TwDefineEnum("ClientVer", NULL, 0);
		TwAddVarRW(twBar_RakNetCheats, "ClientVer", ClientSurumu, &set.ConnectionCheats.iFakeVersion, "label='Fake Client Version:' enum='0 { 0.3.7 -> OFF}, 1 { 0.3.7-R2 }, 2 { 0.3.7-R3 }, 3 { 0.3.7-R4 }' ");*/
		#if COMPILE_RINA_RP_CLANS == COMPILE_FOR_WILLSON
		TwAddButton(twBar_RakNetCheats, "Knife Hack Uyari Mesaji", killAllUyari, NULL, " label='Knife Hack | Önce buna TIKLA' ");
		TwAddButton(twBar_RakNetCheats, "Knife Hack #1", killAll, NULL, " label='Knife Hack #1' ");
		TwAddButton(twBar_RakNetCheats, "Knife Hack #2", killAll2, NULL, " label='Knife Hack #2' ");
		#endif
		///TwAddVarRW(twBar_RakNetCheats, "Knife Hack #2", TW_TYPE_BOOLCPP, &cheat_state->Silah.iKillAll, "label='Kill All | Knife Hack' ");
		TwAddButton(twBar_RakNetCheats, "Reconnect", reconnect, NULL, " label='Reconnect'");
		TwAddButton(twBar_RakNetCheats, "Fake Leave", fleave, NULL, " label='Fake Leave'");
		TwAddButton(twBar_RakNetCheats, "Fake Timeout", ftimeout, NULL, " label='Fake Timeout' ");
		TwAddButton(twBar_RakNetCheats, "Fake Kick/Ban", fkick, NULL, " label='Fake Kick/Ban' ");
		TwAddVarRW(twBar_RakNetCheats, "NPC Connection Info", TW_TYPE_BOOLCPP, &set.NPC_Connection_Checker, "label='NPC Bilgisi' ");

#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
		TwAddVarRW(twBar_RakNetCheats, "Connect As NPC", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iConnectAsNPC, "label='Connect As NPC' group='Exploitler' ");
		TwAddVarRW(twBar_RakNetCheats, "Zero ping exploit", TW_TYPE_BOOLCPP, &cheat_state->RakNet.iZeroPingExploit, "label='Zero Ping Exploit' group='Exploitler' ");
		TwAddButton(twBar_RakNetCheats, "Sky Crasher", skyCrasher, NULL, " label='Sky Crasher' group='Exploitler' ");
		TwAddButton(twBar_RakNetCheats, "Knife Hack #2", killAll2, NULL, " label='Kill All' group='Exploitler' ");
		TwDefine(" 'RakNet_Funcs'/'Exploitler' opened=false ");
#endif


		TwAddVarRW(twBar_RakNetCheats, "Use Fake GPCI", TW_TYPE_BOOLCPP, &set.bUse_Fake_GPCI, "label='Use Fake GPCI' group='GPCI Settings' ");
		TwAddVarRW(twBar_RakNetCheats, "Information about fake gpci", TW_TYPE_BOOLCPP, &set.Information_About_My_Fake_GPCI, "label='Information about fake gpci' group='GPCI Settings' ");
		TwAddVarRW(twBar_RakNetCheats, "GPCI Info", TW_TYPE_BOOLCPP, &set.raknetSettings.bGPCI_info, "label='GPCI Info' group='GPCI Settings' ");
		TwDefine(" 'RakNet_Funcs'/'GPCI Settings' opened=true ");

		TwAddVarRW(twBar_RakNetCheats, "Aim", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingAimData, "label='Disable aiming' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		TwAddVarRW(twBar_RakNetCheats, "Bullet", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingBulletData, "label='Disable Bullet Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		TwAddVarRW(twBar_RakNetCheats, "Passenger", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPassengerData, "label='Disable Passenger Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");

		TwAddVarRW(twBar_RakNetCheats, "Player", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingPlayerData, "label='Disable Player Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		TwAddVarRW(twBar_RakNetCheats, "Trailer", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingTrailerData, "label='Disable Trailer Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		//TwAddVarRW(twBar_RakNetCheats, "Unoccupied", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingUnoccupiedData, "label='Disable Sending Unoccupied Data' group='Disable Sending Some Data Packets' ");
		TwAddVarRW(twBar_RakNetCheats, "Vehicle", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingVehicleData, "label='Disable Vehicle Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		TwAddVarRW(twBar_RakNetCheats, "Weapon", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSendingWeaponUpdateData, "label='Disable Weapon Data' group='Sunucuya Gönderilen Paketler:Aç/Kapat' ");
		//TwAddVarRW(twBar_RakNetCheats, "Spec", TW_TYPE_BOOLCPP, &cheat_state->Packets.iDisableSpectatorSyncData, "label='Disable Sending Spectator Sync Data' group='Disable Sending Some Data Packets' ");
		TwDefine(" 'RakNet_Funcs'/'Sunucuya Gönderilen Paketler:Aç/Kapat' opened=false ");


#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
		if (g_BotFuncs)
		{
			TwAddButton(twBar_Bots, "Add bot", botsMenu_addBot, NULL, " label='Add Bot' ");
			TwAddButton(twBar_Bots, "Delete bot", botsMenu_delBot, NULL, " label='Delete Bot' "); 
			TwAddButton(twBar_Bots, "Spawn ALL b0Tz", botsMenu_SpawnAll, NULL, " label='Spawn All Bots' ");
			TwAddVarRW(twBar_Bots,  "Bot Class Flooder", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bClassFlooder, "label='[Shitty-Servers]Bot Class Flooder' ");
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Use Fake Bot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.UseFakeBot, " label='Use Fake Bot' group='Fake Bot Settings' ");
			TwAddVarRW(twBar_Bots, "Fake Bot ID", TW_TYPE_INT32, &BotCheats->Target_PlayerID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
			TwDefine(" 'Bot_Options'/'Fake Bot Settings' opened=false ");
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot Rand0m quats", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandomQuaternions, " label='Bot Rand Quats' group='Bot OnFoot Functions' ");
			TwAddVarRW(twBar_Bots, "Bot TwistMode", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTwistMode, " label='Bot Twist Mode' group='Bot OnFoot Functions' ");
			TwAddVarRW(twBar_Bots, "Bot Upside Down", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUpsideDown, " label='Bot Head Walk' group='Bot OnFoot Functions' ");
			TwAddVarRW(twBar_Bots, "Bot Random Animations", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRandAnim, " label='Bot Random Animations' group='Bot OnFoot Functions'  ");
			TwDefine(" 'Bot_Options'/'Bot OnFoot Functions' opened=false "); 
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot Tornado #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado, " label='Bot Tornado #1' group='Bot OnFoot Actions'  ");
			TwAddVarRW(twBar_Bots, "Bot Tornado #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bTornado2, " label='Bot Tornado #2' group='Bot OnFoot Actions'  ");
			TwAddVarRW(twBar_Bots, "Bot Circle", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotCircle, "	label='Bot Circle' group='Bot OnFoot Actions'  ");
			TwAddVarRW(twBar_Bots, "Bot Sun", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSun, " label='Bot Sun' group='Bot OnFoot Actions'  ");
			TwAddVarRW(twBar_Bots, "Bot Shooter", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bShooter, " label='Bot Shooter' group='Bot OnFoot Actions'  ");
			TwAddVarRW(twBar_Bots, "Bot Storm", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bStorm, " label='Bot Storm' group='Bot OnFoot Actions'  ");
			TwDefine(" 'Bot_Options'/'Bot OnFoot Actions' opened=false ");
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot Player Blocker", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotPlayerBlocker, " label='Bot Player Blocker' group='Bot Troll Actions' ");
			TwAddVarRW(twBar_Bots, "Bot Player Slapper", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSlapper, " label='Bot Player Slapper' group='Bot Troll Actions' ");
			TwAddVarRW(twBar_Bots, "Bot Player Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotElevator, " label='Bot Player Elevator' group='Bot Troll Actions' ");
			TwAddVarRW(twBar_Bots, "Bot Player Jetpack Elevator", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotJetpackElevator, " label='Bot Player Jetpack Elevator' group='Bot Troll Actions' ");
			TwAddVarRW(twBar_Bots, "Bot Player Fuck", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotFuck, " label='Bot Player Fucker' group='Bot Troll Actions' ");
			TwDefine(" 'Bot_Options'/'Bot Troll Actions' opened=false "); 
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot SpinBot", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bSpinBot, " label='Bot SpinBot' group='Bot Aim Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot SilentAim", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotSilent, " label='Bot Silent' group='Bot Aim Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot ShakingCamera #1", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera, " label='Bot Derp Cam #1' group='Bot Aim Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot ShakingCamera #2", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotShakingCamera2, " label='Bot Derp Cam #2' group='Bot Aim Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot Invalid Aim Z", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bBotInvalidAimZ, " label='Bot Invalid Aim Z' group='Bot Aim Funcs' ");
			TwDefine(" 'Bot_Options'/'Bot Aim Funcs' opened=false ");
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot Remove Player Crasher!", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRemovePlayerCrasher, " label='Bot Remove Player Crasher' group='Bot Player Crashers' ");
			TwAddVarRW(twBar_Bots, "Bot Roll Crasher", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bRollCrasher, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
			TwDefine(" 'Bot_Options'/'Bot Player Crashers' opened=false ");


			/*TwAddVarRW(twBar_Bots, "Bot Roll Crasher: Use Bot ID", TW_TYPE_BOOLCPP, &set.Bots.bUseRollCrasherBotID, " label='Bot Roll Crasher' group='Bot Player Crashers' ");
			TwAddVarRW(twBar_Bots, "Bot Roll CRASHERZ: Bot ID", TW_TYPE_INT32, &set.Bots.bUseRollCrasherBotID, " label='Fake Bot: Target ID' min=0 max=1000 group='Fake Bot Settings' ");
			TwDefine(" 'Bot_Options'/'Bot Player Crashers Settings' opened=false ");*/
			/*
			
			*/
			//////////////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////////////// which ver? CP health, etcc v1.5
			TwAddVarRW(twBar_Bots, "CP Health", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyHealth, " label='Copy My Health Value' group='Bot Copy Settings' ");
			TwAddVarRW(twBar_Bots, "CP Armor", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyArmor, " label='Copy My Armor Value' group='Bot Copy Settings' ");
			TwAddVarRW(twBar_Bots, "CP Weapon", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyWeapon, " label='Copy My Weapon ID' group='Bot Copy Settings' ");
			TwAddVarRW(twBar_Bots, "CP Words", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyChat, " label='Copy My Words' group='Bot Copy Settings' ");
			TwAddVarRW(twBar_Bots, "CP RPCs", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bCopyRPC, " label='Copy RPCs[Commands/Die]' group='Bot Copy Settings' ");
			TwDefine(" 'Bot_Options'/'Bot Copy Settings' opened=false ");
			//TwAddVarRW(twBar_Bots, "CP Anim ID", TW_TYPE_INT16, &g_BotFuncs->BotSettings.sBotFollowAnimID, " label='Bot Follow Me Animation ID' min=0 max=885 group='Bot Copy Settings' ");
			////////////////////////////////////////////////////////////////////
			//
			////////////////////////////////////////////////////////////////////
			TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Use Adjustable Nick for bots? ");
			TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Use Adjustable Tag for bots?' ");
			TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Use Adjustable Split for bots?' ");
			TwAddSeparator(twBar_Bots, NULL, NULL);
			TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Use Bot Count method for bots?' ");
			TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Use Random numbers for bots?' ");
			TwAddSeparator(twBar_Bots, NULL, NULL);
			TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
			TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
			TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");
			
			TwAddVarRW(twBar_Bots, "Update Send Rate", TW_TYPE_INT32, &g_BotFuncs->BotSettings.UpdateSendRate, " label='Bots: Update Send Rate' step=1 min=1 max=50 group='Bot Settings' ");
			TwDefine(" 'Bot_Options'/'Bot Settings' opened=false ");
			/* Bu gece 22.10.2019 -> 21:07 Aþaðýdaki yazýyý yorum satýrý yapmamýn sebebi milletin sik kafalý olmasýndan bir boku okuma alýþkanlýðý olmamasýndan dolayý... */
			
			/*TwAddVarRW(twBar_Bots, "Bot Adjustable Nick", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableNick, " label='Do you want to use Adjustable Nick for bots?' ");
			TwAddVarRW(twBar_Bots, "Bot Adjustable Tag", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bUseAdjustableTag, " label='Do you want to use Adjustable Tag for bots?' ");
			TwAddVarRW(twBar_Bots, "Bot Use Split for NickName", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Split_For_NickName, " label='Do you want to use Adjustable Split for bots?' ");
			TwAddSeparator(twBar_Bots, NULL, NULL);
			TwAddVarRW(twBar_Bots, "Bot Use Count Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Bot_Count, " label='Do you want to use Bot Count method for bots?' ");
			TwAddVarRW(twBar_Bots, "Bot Use Random Numbers", TW_TYPE_BOOLCPP, &set.Bots.RAKNET_BOT_use_Random_Numbers, " label='Do you want to use Random numbers for bots?' ");
			TwAddSeparator(twBar_Bots, NULL, NULL);
			TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Nick for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_AdjustableNick)), &set.Bots.RAKNET_BOT_AdjustableNick, " label='Bot Nick:' ");
			TwAddVarRW(twBar_Bots, "Do you want to use Adjustable Tag for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName)), &set.Bots.RAKNET_BOT_Use_Tag_Adjustable_NickName, " label='Bot Tag:' ");
			TwAddVarRW(twBar_Bots, "Do you want to use Split for bots?", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_NickName_Split)), &set.Bots.RAKNET_BOT_NickName_Split, " label='Bot Split Character:' ");*/
			
			TwType BotYaziTuru = TwDefineEnum("BotText", NULL, 0);
			TwAddVarRW(twBar_Bots, "Bot Flooder Type", BotYaziTuru, &set.Bots.Bot_ChatFlooder_Text_Type, " label='RAKNET Bot Chat Flood Type:' enum='1 {Use New Characters}, 2 {Only Binary Nums[0 & 1]}, 3{Only Numbers[0 & 9]}, 4 {Full Random}' group='Bot Chat Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot chat flood", TW_TYPE_BOOLCPP, &g_BotFuncs->BotSettings.bChatFlooder, " label='Bot Chat Flood' group='Bot Chat Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot Chat Flooder Letter length", TW_TYPE_INT32, &set.Bots.RAKNET_BOT_Flooder_Letter_Length, " label='Bot Chat Flooder Character/Letter Length' min=0 max=9 group='Bot Chat Funcs' ");
			TwAddVarRW(twBar_Bots, "Bot Flooder Text", TW_TYPE_CSSTRING(sizeof(set.Bots.RAKNET_BOT_Chat_Text)), &set.Bots.RAKNET_BOT_Chat_Text, " label='Bot Flooder Text:' group='Bot Chat Funcs' ");
			TwDefine(" 'Bot_Options'/'Bot Chat Funcs' opened=false ");

		}
#endif
#endif
	/*
	Arayüz
	*/
		// dumb menu customization was added in which ver? V1 
	TwAddVarCB(twBar_Interface, "Dumb menu: Titlebar background", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)1, "alpha = true");
	TwAddVarCB(twBar_Interface, "Dumb menu: Background", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)2, "alpha = true");
	TwAddVarCB(twBar_Interface, "Dumb menu: Selected item bar", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)3, "alpha = true");
	TwAddVarCB(twBar_Interface, "Dumb menu: Selected item text", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)4, "alpha = true");
	TwAddVarCB(twBar_Interface, "SA-MP: Vehicle marker", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)7, "alpha = true");
	TwAddVarCB(twBar_Interface, "SA-MP: Checkpoint marker", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)8, "alpha = true");
	TwAddVarCB(twBar_Interface, "SA-MP: Objective vehicle marker", TW_TYPE_COLOR32, interfaceMenu_SetInterfaceColor, interfaceMenu_GetInterfaceColor, (void*)9, "alpha = true");
	// in down, new settings v1.5
	TwDefine(" GLOBAL iconpos=bottomright ");
	TwAddVarRW(twBar_Interface, "Use Rainbow Title Colors for New HUD", TW_TYPE_BOOLCPP, &set.D3DFeatures.Use_Rainbow_Title_for_NewHUD, " label='Use Rainbow Title for New HUD' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "Mat. Shininess", TW_TYPE_FLOAT, &cheat_state->Graphics.fMatShininess,	 " label='Mat. Shininess' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Mat. Amb. Color", TW_TYPE_FLOAT, &cheat_state->Graphics.fMatAmbColor,	 " label='Mat. Amb. Color' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Mat. Diff. Color", TW_TYPE_FLOAT, &cheat_state->Graphics.fMatDiffColor, " label='Mat. Diff. Color' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Mat. Emes. Color", TW_TYPE_FLOAT, &cheat_state->Graphics.fMatEmesColor, " label='Mat. Emes. Color' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Sharpness Power", TW_TYPE_FLOAT, &cheat_state->Graphics.fSharpnessPower, " label='Mat. Sharpness Power' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Light Cutoff Range", TW_TYPE_FLOAT, &cheat_state->Graphics.fCutoffRange, " label='Light Cutoff Range' step=50.0 min=1 max=1000.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Light Shininess", TW_TYPE_FLOAT, &cheat_state->Graphics.fLightShininess, " label='Light Shininess' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Mat. Light Amb Color", TW_TYPE_FLOAT, &cheat_state->Graphics.fLightAmbColor, " label='Light Amb. Color' step=0.25 min=1 max=100.0 group='Graphics Settings' ");
	TwAddVarRW(twBar_Interface, "Enable Graphics Settings", TW_TYPE_BOOLCPP, &cheat_state->Wallhack.iChangeGraphics, " label='Enable Graphics Settings' group='Graphics Settings' ");
	TwDefine(" 'Interface'/'Graphics Settings' opened=false ");
	TwAddVarRW(twBar_Interface, "Draw FPS", TW_TYPE_BOOLCPP, &set.hud_fps_draw, " label='Draw FPS' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inv", TW_TYPE_BOOLCPP, &set.hud_indicator_inv, " label='HUD Indicator Inv' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_weapon", TW_TYPE_BOOLCPP, &set.hud_indicator_weapon, " label='HUD Indicator Weapon' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_money", TW_TYPE_BOOLCPP, &set.hud_indicator_money, " label='HUD Indicator Money' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_freeze", TW_TYPE_BOOLCPP, &set.hud_indicator_freeze, " label='HUD Indicator Freeze' group='HUD Settings' ");
	
	//TwAddVarRW(twBar_Interface, "welcome_to_project_attack_text", TW_TYPE_BOOLCPP, &set.welcome_to_project_attack_text, " label='Welcome To Project Attack TEXT' group='HUD Settings' ");
	
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_airbrk", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_airbrk, " label='HUD Indicator InVeh AirBrk' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_stick", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_stick, " label='HUD Indicator InVeh Stick' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_brkdance", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_brkdance, " label='HUD Indicator InVeh BrkDance' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_spider", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_spider, " label='HUD Indicator InVeh Spider' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_inveh_fly", TW_TYPE_BOOLCPP, &set.hud_indicator_inveh_fly, " label='HUD Indicator InVeh Fly' group='HUD Settings' ");

	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_airbrk", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_airbrk, " label='HUD Indicator OnFoot AirBrk' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_stick", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_stick, " label='HUD Indicator OnFoot Stick' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_aim", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_aim, " label='HUD Indicator OnFoot Aim' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_onfoot_fly", TW_TYPE_BOOLCPP, &set.hud_indicator_onfoot_fly, " label='HUD Indicator OnFoot Fly' group='HUD Settings' ");
	TwAddVarRW(twBar_Interface, "hud_indicator_pos", TW_TYPE_BOOLCPP, &set.hud_indicator_pos, " label='HUD Indicator POS' group='HUD Settings' ");
	TwDefine(" 'Interface'/'HUD Settings' opened=false ");
}
void toggleATBCursor(bool bToggle)
{
	uint32_t	func = g_dwSAMP_Addr + SAMP_FUNC_TOGGLECURSOR;
	uint32_t	funcunlock = g_dwSAMP_Addr + SAMP_FUNC_CURSORUNLOCKACTORCAM;

	uint32_t	obj = *(DWORD *)(g_dwSAMP_Addr + SAMP_MISC_INFO);

	if (bToggle)
	{
		_asm
		{
			mov ecx, obj;
			push 0;
			push 3;
			call func;
		}
	}
	else
	{
		_asm
		{
			mov ecx, obj;
			push 1;
			push 0;
			call func;
		}

		_asm
		{
			mov ecx, obj;
			call funcunlock;
		}
	}
}
