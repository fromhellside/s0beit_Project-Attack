#include "main.h"

void SH_DoubleGun1(void)
{
	if (cheat_state->Silah.iDoubleGun1 == 1)
	{
		static DWORD time = 0;
		static bool state_of_weapon = false;
		actor_info *actor = actor_info_get(ACTOR_SELF, NULL);
		if (actor->weapon[2].id == 24 && actor->weapon[3].id == 25)
		{
			if (g_Players->pLocalPlayer->onFootData.stSampKeys.keys_secondaryFire__shoot && (g_Players->pLocalPlayer->onFootData.byteCurrentWeapon == 24 ||
				g_Players->pLocalPlayer->onFootData.byteCurrentWeapon == 25))
			{
				if (GetTickCount() - set.WeaponCheats.iDoubleGun1_Delay > time)
				{

					if (state_of_weapon == false)
					{
						pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(2));
						state_of_weapon = true;
						time = GetTickCount();
					}
					else
					{
						if (state_of_weapon == true)
						{
							pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(3));
							state_of_weapon = false;
							time = GetTickCount();
						}
					}
				}
			}
		}
	}
}
void SH_DoubleGun2(void)
{
	if (cheat_state->Silah.iDoubleGun2)
	{
		if (KEY_DOWN(VK_LBUTTON)) // if (KEY_DOWN(0x02) & KEY_DOWN(0x01))
		{
			actor_info *pInfo = actor_info_get(ACTOR_SELF, 0);
			static DWORD time = GetTickCount();
			if (GetTickCount() - time >= set.WeaponCheats.iDoubleGun2_Delay)
			{
				if (ACTOR_IS_DEAD(pInfo)) return;
				static int weapon = 0;
				if (weapon == 0)
				{
					pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(set.WeaponCheats.iDoubleGun2_WeaponSlot1));
					weapon = 1;
					time = GetTickCount();
				}
				else if (weapon == 1)
				{
					pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(set.WeaponCheats.iDoubleGun2_WeaponSlot2));
					weapon = 0;
					time = GetTickCount();
				}
			}
		}
	}
}

void SH_SAim_Draw()
{
	if (!g_Players)
		return;
	if (gta_menu_active())
		return;
	if (cheat_state->Silent.bSilent)
		g_NewModSa->iAimPlayerID = GetAimingPlayer(true);
	//if (g_Players->pLocalPlayer->byteCurrentWeapon != 34)
	//{
	//	g_NewModSa->fViewFinderPosition[0] = (float)pPresentParam.BackBufferWidth * 0.5299999714f;
	//	g_NewModSa->fViewFinderPosition[1] = (float)pPresentParam.BackBufferHeight * 0.4f;
	//}
	//else
	//{
	//	g_NewModSa->fViewFinderPosition[0] = (float)pPresentParam.BackBufferWidth / 2.f;
	//	g_NewModSa->fViewFinderPosition[1] = (float)pPresentParam.BackBufferHeight / 2.f;
	//}
	/*
	if (set.silentAim.bDrawCircle)
	{
		Draw2DCircle((g_NewModSa->fViewFinderPosition[0]) - 20.0f, (g_NewModSa->fViewFinderPosition[1]) - 1.0f, set.silentAim.fCircleRadius, samp_color_get(g_NewModSa->iAimPlayerID));*/
		/*render->D3DBox((g_NewModSa->fViewFinderPosition[0]) - 20.0f, (g_NewModSa->fViewFinderPosition[1]) - 1.0f, 40.0f, 2.0f, D3DCOLOR_ARGB(255, rand() % 255, rand() % 255, rand() % 255));
		render->D3DBox((g_NewModSa->fViewFinderPosition[0]) - 1.0f, (g_NewModSa->fViewFinderPosition[1]) - 20.0f, 2.0f, 40.0f, D3DCOLOR_ARGB(255, rand() % 255, rand() % 255, rand() % 255));*/
		/*if (Color < 250)
			Color += 10;
		else
			Color = 50;*/
	//}
}
void SH_AutoCbug1()
{
	if (cheat_state->Silah.iAutoCbug1)
	{
		actor_info *me = actor_info_get(ACTOR_SELF, NULL);
		if (!me)
			return;
		if (!gta_menu_active() && !cheat_state->_generic.menu && me->state != ACTOR_STATE_DRIVING)
		{
			enum eStep
			{
				C_BUG_STEP_SHOT,
				C_BUG_STEP_SHOT_UP,
				C_BUG_STEP_PRESS_C,
				C_BUG_STEP_C_UP,
				C_BUG_STEP_AIMING,
			};
			static DWORD step = C_BUG_STEP_SHOT;

			int now_rkey_down = (bool)(GetKeyState(VK_RBUTTON) & 0x8000);
			int now_lkey_down = (bool)(GetKeyState(VK_LBUTTON) & 0x8000);
			static int most_rkey_down = true;
			static int most_lkey_down = true;
			bool shooting = false;
			if (((now_lkey_down && most_lkey_down) || !most_lkey_down) &&
				((now_rkey_down && most_rkey_down) || !most_rkey_down))
			{
				shooting = true;
			}
			else
			{
				shooting = false;
				if (!most_rkey_down)
				{
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					most_rkey_down = true;
				}

				if (!most_lkey_down)
				{
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					most_lkey_down = true;
				}

				step = C_BUG_STEP_SHOT;
			}
			if (shooting)
			{
				static DWORD timeout;
				static DWORD tick;

				DWORD now_tick = GetTickCount();


				if (now_tick - tick > timeout)
				{

					tick = now_tick;


					switch (step)
					{
					case C_BUG_STEP_SHOT:
						most_lkey_down = true;

						if (now_lkey_down)
							mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						timeout = 0;
			
						break;
					case C_BUG_STEP_SHOT_UP:
						most_rkey_down = false;
						most_lkey_down = false;
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						timeout = 10;
						break;
					case C_BUG_STEP_PRESS_C:
						timeout = 10;
						keybd_event(GTA_KEY_C, 0, 0, 0);
						break;
					case C_BUG_STEP_C_UP:
						keybd_event(GTA_KEY_C, 0, KEYEVENTF_KEYUP, 0);
						break;
					case C_BUG_STEP_AIMING:
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						most_rkey_down = true;
						timeout = 10;
						break;
					default:
						break;
					}
					if (step++ >= C_BUG_STEP_AIMING)
						step = C_BUG_STEP_SHOT;
				}
			}
		}
	}
}
void SH_AutoCbug2()
{
	if (cheat_state->Silah.iAutoCbug2)
	{
		if (KEY_DOWN(VK_LBUTTON)) // if (KEY_DOWN(0x02) & KEY_DOWN(0x01))
		{
			struct actor_info* pInfo = actor_info_get(ACTOR_SELF, 0);
			static DWORD time = GetTickCount();
			if (GetTickCount() - time >= set.WeaponCheats.AutoCbug2_Delay)
			{
				if (ACTOR_IS_DEAD(pInfo))
					return;
				if (gta_menu_active())
					return;
				if (pInfo->weapon[pInfo->weapon_slot].ammo_clip == 0)
					return;
				//GTAfunc_PerformAnimation("PED", "HIT_WALK", 1, 0, 1, 0, 0, 1, 0, 1);
				GTAfunc_DisembarkInstantly();
				time = GetTickCount();
			}
		}
	}
}
void SH_NoRecoil(void)
{
	static bool no_rec = false;
	if (cheat_state->Silah.iNoRecoil == 1)
	{
		*(float *)0xC8C450 = 5.0; // colts için
		*(float *)0xC8C8B0 = 25.0; // tec9 için
		*(float *)0xC8C5A0 = 2.0; // shootgun için
		*(float *)0xC8C4C0 = 3.0; // pistol silent için
		*(float *)0xC8C840 = 25.0; // m4 için
		*(float *)0xC8C530 = 5.0; // deagle için
		*(float *)0xC8C6F0 = 5.0; // uzi için
		*(float *)0xC8C760 = 5.0; // mp5 için
		*(float *)0xC8C7D0 = 25.0; // ak için
	}
	else
	{
		//orijinal değerler.
		*(float *)0xC8C450 = 1.250000; // Colt45 için 
		*(float *)0xC8C8B0 = 1.100000; // tec9 için
		*(float *)0xC8C5A0 = 1.400000; // Pompalı tüfek, Shotgun için
		*(float *)0xC8C4C0 = 1.500000; // Susturuculu silah için
		*(float *)0xC8C840 = 0.800000; // m4 için
		*(float *)0xC8C530 = 1.250000; // deagle için
		*(float *)0xC8C6F0 = 1.100000; // uzi için
		*(float *)0xC8C760 = 1.200000; // mp5 için
		*(float *)0xC8C7D0 = 0.600000; // ak47 için
	}
}
void SH_NoReloadBug(void)
{
	traceLastFunc("SH_NoReload()");
	if (cheat_state->Silah.iNoReloadBug == 1)
	{
		struct actor_info *pInfo = actor_info_get(ACTOR_SELF, 0);
		if (ACTOR_IS_DEAD(pInfo)) return;
		// Check weapons
		int wID = pInfo->weapon[pInfo->weapon_slot].id;
		if (wID == 22 || wID == 23 || wID == 24 || wID == 26 || wID == 27 || wID == 28 || wID == 29 ||
			wID == 30 || wID == 31 || wID == 32 || wID == 37 || wID == 38 || wID == 41 || wID == 42) {
			int wSlot = pPedSelf->GetCurrentWeaponSlot();
			if (pInfo->weapon[pInfo->weapon_slot].ammo_clip == 1)
			{
				pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(0));
				pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(wSlot));
			}
		}
		else return;
	}
}
void SH_AutoSawn(void)
{
	if (cheat_state->Silah.iAuto2_2)
	{
		static bool state_of_weapon = false;

		actor_info *ped = actor_info_get(ACTOR_SELF, NULL);
		static DWORD timer = 0;

		if (ped->weapon[3].id == 26 && ped->weapon[3].ammo_clip <= 2)
		{
			if (KEY_DOWN(VK_RBUTTON))
				return;

			if (GetTickCount() - 350 > timer)
			{

				if (state_of_weapon == false)
				{
					pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(0));
					state_of_weapon = true;
					timer = GetTickCount();
				}
				else
				{
					if (state_of_weapon == true)
					{
						pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(3));
						state_of_weapon = false;
						timer = GetTickCount();
					}
				}
			}
		}
	}
}
void SH_SawnDeagle(void)
{
	static bool state_of_weapons = false;
	static DWORD timer = 0;
	if (cheat_state->Silah.iSawnDeagle)
	{
		struct actor_info* ped = actor_info_get(ACTOR_SELF, NULL);
		if (ped->weapon[3].id == 26 && ped->weapon[3].ammo_clip <= 2)
		{
			if (KEY_DOWN(VK_RBUTTON))
				return;
			if (GetTickCount() - timer > 250)
			{
				if (state_of_weapons == false && g_Players->pLocalPlayer->byteWeaponInventory[2] == 24)
				{
					pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(2));
					if(ped->weapon[2].id == 24 && ped->weapon[2].ammo_clip < 7)
					state_of_weapons = true;
					timer = GetTickCount();
				}
				else
				{
					if (state_of_weapons == true)
					{
						pPedSelf->SetCurrentWeaponSlot(eWeaponSlot(3));
						state_of_weapons = false;
						timer = GetTickCount();
					}
				}
			}
		}
	}
}

void SH_RapidFire(void)
{
	if (cheat_state->Silah.iRapidFire)
	{
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, ACTOR_ALIVE);
		if (!ainfo)
			return;
		// Eğer hedef varsa, ve benden başka insan varsa etrafta ve yaşıyorsa 
		// "Alive" ve "Not me"
		int iTargetPlayerID = GetClosestPlayerid(ainfo, ACTOR_ALIVE | ACTOR_NOT_ME);

		actor_info* deadman = getGTAPedFromSAMPPlayerID(iTargetPlayerID);
		if (!deadman)
			return;
		//if (cheat_state->state != CHEAT_STATE_ACTOR) // Eğer oyuncu normal yürüyebilmiyorsa çalışma, kullanma oynama işte.
		//	return;
		// İzinli silahlar
		BYTE bAllowedWeapons[] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38 };
		int iWeaponID = g_Players->pLocalPlayer->byteCurrentWeapon;

		static DWORD dwBulletTime = set.WeaponCheats.dwRapidFireDelay;  // Yeni güncelleme, 1.10.2020 -> 100'e düşürdüm delayı
		if (KEY_DOWN(GTA_KEY_SPACE))
		{
			if (bAllowedWeapons[g_Players->pLocalPlayer->byteCurrentWeapon])
			{
				if (GetTickCount() - dwBulletTime >= set.WeaponCheats.dwRapidFireDelay)
				{
					float fOrigin[3], fTarget[3], fCenter[3] = { -0.01f,-0.02f,0.56 - ((rand() % 5) / 100.0f) };
					vect3_copy(&ainfo->base.matrix[4 * 3], fOrigin);
					vect3_copy(&deadman->base.matrix[4 * 3], fTarget);
					if (IsPlayerStreamed(iTargetPlayerID)) // Eğer yakında adam varsa.
					{
						//g_RakClient->SendBulletData();
						BYTE bBodyParts[3] = { 3,4,9 };
						g_RakClient->SendDamage(iTargetPlayerID, fWeaponDamage[iWeaponID], iWeaponID, bBodyParts[rand() % 3]);
						g_RakClient->SendModifiedBulletData(iTargetPlayerID, fOrigin, fTarget, fCenter, iWeaponID, 1);
						if (set.WeaponCheats.bTeleportForRapidFire && deadman->state == CHEAT_STATE_ACTOR)
							pPedSelf->SetPosition(g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->fOnFootPos[0], g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->fOnFootPos[1], g_Players->pRemotePlayer[iTargetPlayerID]->pPlayerData->fOnFootPos[2]);
					}
					dwBulletTime = GetTickCount();
				}
			}
		}
	}
}
void SilahFonksiyonlari(void)
{
	SH_DoubleGun1();
	SH_DoubleGun2();
	SH_SAim_Draw();
	SH_AutoCbug1();
	SH_AutoCbug2();
	SH_NoRecoil();
	SH_NoReloadBug();
	SH_AutoSawn();
	SH_SawnDeagle();
	SH_RapidFire();
}