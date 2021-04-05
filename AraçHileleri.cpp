#include "main.h"
void AF_MultiCarShooter()
{
	if (cheat_state->Arac.iCarShooter)
	{
		struct actor_info *oyuncubilgisi = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info *aracbilgisi = vehicle_info_get(VEHICLE_SELF, 0);
		float fPos[3]; // Pozisyonlar.. dizi ile tanýmlý 0-1-2 pozisyonlarý. 3 dahil mi bilmiyorum. - RapidFire
		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 225)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				/*if (g_Vehicles->iIsListed[v] == NULL)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL)
					continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL)
					continue;*/
				GetStreamedVehicle(v);
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
					continue;
				static float Angle = 5; // Angle bildiðim kadarýyla mesafeydi türkçesi ama yanýlýyor da olabilirim - RapidFire
				float AbsSpeed = 20.0f; // Deðiþken adý
					float fSpeed[3]; // float hýz, ondalýklý hýz dizi ile tanýmlý 0-1-2 dediðim gibi.. 3 dahil mi bilmiyorum. - RapidFire
				if (KEY_DOWN(VK_LBUTTON))
				{

					vect3_copy(&oyuncubilgisi->base.matrix[4 * 3], fPos); // Veri kopyalamasý
					
					fPos[2] += 4.0f; // Z Pos + 4.0f;

					fSpeed[0] = AbsSpeed * cos(Angle);
					fSpeed[1] = AbsSpeed * sin(Angle);

					Angle += DEGTORAD(30); // 115'den 45 yaptým.
					/*if (set.MakeZeroHPforCars == true)
						VehicleSynchronization(fPos, fSpeed, true);
					else
						VehicleSynchronization(fPos, fSpeed, false);*/
					if (set.MakeZeroHPforCars)
					{
						g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
						g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
					}
					else
					{
						g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
						g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
					}
					
					cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
					vinfo->speed[0] = fSpeed[0];
					vinfo->speed[1] = fSpeed[1];
				}
				time = GetTickCount();
			}
		}
	}
}
void AF_MultiCarShooter2()
{
	if (cheat_state->Arac.iCarShooter2)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, NULL);
		static int v = 0;
		static int x = 0;
		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON))
		{
			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);
			fPos[0] += sinf(18.51f * (float)x) * 15.0f; // ilk deðer:45 // ikinci 25.0f yeni -> 6.0f;
			fPos[1] += cosf(71.45f * (float)x) * 15.0f; // ilk 35 // ikinci = 29.0f // yeni 6.0 
			fPos[2] += 0.5f; // Z coord, already know that. / Z Koordinatlarý, bunu zaten biliyoruz.
			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 2.0f;
			fSpeed[1] = cam_matrix[5] * 3.0f;
			fSpeed[2] = cam_matrix[6] * 4.0f;
			fPos[0] += fSpeed[0];
			fPos[1] += fSpeed[1];
			fPos[2] += fSpeed[2];
			if (set.MakeZeroHPforCars)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			}
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];
			x--;
			if (x < -1) x = 0;
			v++;
		}

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}
void AF_DoubleCarCircle()
{
	static int iGecikme = GetTickCount();
	if (cheat_state->Arac.iCarCircle)
	{
		struct actor_info *kendim = actor_info_get(ACTOR_SELF, NULL); // NULL, 0 anlamýna gelmektedir.
		static int v = 0;
		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON) && GetTickCount() >= iGecikme)
		{
			float fPozisyon[3];
			vect3_copy(&kendim->base.matrix[4 * 3], fPozisyon);
			static int x = 0;
			fPozisyon[0] += sinf(19.0f * (float)x) * 25.0f;
			fPozisyon[1] += cosf(19.0f * (float)x) * 25.0f;
			fPozisyon[2] += 35.0f;
			x++;
			float fSpeed[3] = { 0.0f, 0.0f, 0.0f }; // float Hýz dizisi, C++ Programlama dilinde, Diziler her zaman ama HER ZAMAN 0'dan baþlar. ve Sonuncu sayý dahil deðildir. Bilgi : RapidFire
			stInCarData AracSenk;
			memset(&AracSenk, 0, sizeof(stInCarData));
			AracSenk.sVehicleID = iSAMPVehicleID;
			AracSenk.fPosition[0] = fPozisyon[0];
			AracSenk.fPosition[1] = fPozisyon[1];
			AracSenk.fPosition[2] = fPozisyon[2];
			AracSenk.fVehicleHealth = vinfo->hitpoints;
			AracSenk.fMoveSpeed[0] = fSpeed[0];
			AracSenk.fMoveSpeed[1] = fSpeed[1];
			AracSenk.fMoveSpeed[2] = fSpeed[2];
			AracSenk.sKeys = 0;
			cheat_vehicle_teleport(vinfo, fPozisyon, gta_interior_id_get());
			vect3_zero(vinfo->speed);
			//if (set.MakeZeroHPforCars == true)
			//	VehicleSynchronization(fPozisyon, fSpeed, true);
			//else
			//	VehicleSynchronization(fPozisyon, fSpeed, false);
			if (set.MakeZeroHPforCars)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyon, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyon, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, fSpeed);
			}
			
			v++;

		find_another_car:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
			iGecikme = GetTickCount();
		}
		if (KEY_DOWN(VK_RBUTTON) && GetTickCount() >= iGecikme)
		{
			struct actor_info *kendim = actor_info_get(ACTOR_SELF, NULL); // NULL, 0 anlamýna gelmektedir.
			static int v = 0;
			if (g_Vehicles->iIsListed[v] != 1)
				goto find_another_car_for_double_circle;
			GetStreamedVehicle(v);
			int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
			struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

			int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
			if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
			{
				v++;
				goto find_another_car_for_double_circle;
			}

			float fPozisyonOne[3]; //
			float fPozisyonDouble[3]; // Bu deðiþken, Ondalýklý sayýlarý saklamak içindir bu sonundaki Double ise, Ýkinci bir daire oluþturmak için.
			vect3_copy(&kendim->base.matrix[4 * 3], fPozisyonOne);
			vect3_copy(&kendim->base.matrix[4 * 3], fPozisyonDouble);
			static int x2 = 0;
			fPozisyonOne[0] += sinf(19.0f * (float)x2) * 25.0f;
			fPozisyonOne[1] += cosf(19.0f * (float)x2) * 25.0f;
			fPozisyonOne[2] += 35.0f;

			fPozisyonDouble[0] = fPozisyonOne[0] + sinf(19.0f * (float)x2) * 25.0f;
			fPozisyonDouble[1] = fPozisyonOne[1] + cosf(19.0f * (float)x2) * 25.0f;
			fPozisyonDouble[2] += fPozisyonOne[2];// + 35.0f;
			x2++;
			float fSpeed[3] = { 0.0f, 0.0f, 0.0f }; // float Hýz dizisi, C++ Programlama dilinde, Diziler her zaman ama HER ZAMAN 0'dan baþlar. ve Sonuncu sayý dahil deðildir. Bilgi : RapidFire
			stInCarData AracSenk;
			memset(&AracSenk, 0, sizeof(stInCarData));
			AracSenk.sVehicleID = iSAMPVehicleID;
			AracSenk.fPosition[0] = fPozisyonDouble[0];
			AracSenk.fPosition[1] = fPozisyonDouble[1];
			AracSenk.fPosition[2] = fPozisyonDouble[2];
			AracSenk.fVehicleHealth = vinfo->hitpoints;
			AracSenk.fMoveSpeed[0] = fSpeed[0];
			AracSenk.fMoveSpeed[1] = fSpeed[1];
			AracSenk.fMoveSpeed[2] = fSpeed[2];
			AracSenk.sKeys = 0;
			cheat_vehicle_teleport(vinfo, fPozisyonDouble, gta_interior_id_get());
			vect3_zero(vinfo->speed);
			if (set.MakeZeroHPforCars)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyonDouble, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyonDouble, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyonDouble, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyonDouble, vinfo->hitpoints, fSpeed);
			}
			//g_RakClient->SendFakeDriverFullSyncData(&AracSenk, 0);
			v++;

		find_another_car_for_double_circle:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
			iGecikme = GetTickCount();
		}
	}
}
void AF_MultiCarFollows()
{
	traceLastFunc("AF_MultiCarFollows()");

	if (cheat_state->Arac.iCarFollows)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON))
		{

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			// 1st version
			fPos[0] += (sinf(-self->fCurrentRotation) * 25.0f) + (-150 + rand() % 450);
			fPos[1] += (cosf(-self->fCurrentRotation) * 25.0f) + (-150 + rand() % 450);
			fPos[2] += 15.0f;

			float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vect3_zero(vinfo->speed);
		/*	if (set.MakeZeroHPforCars == true)
				VehicleSynchronization(fPos, fSpeed, true);
			else
				VehicleSynchronization(fPos, fSpeed, false);*/
			if (set.MakeZeroHPforCars)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			}

			v++;

		find_another_car:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
		}
	}
}
void AF_MultiCarFollows2()
{
	if (cheat_state->Arac.iCarFollows2)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON))
		{

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			// 1st version
			fPos[0] += (sinf(-self->fCurrentRotation) * 5.0f) + (-20 + rand() % 40);
			fPos[1] += (cosf(-self->fCurrentRotation) * 5.0f) + (-20 + rand() % 40);
			fPos[2] += 5.0f;

			float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

			stInCarData vehSync;
			memset(&vehSync, 0, sizeof(stInCarData));

			vehSync.sVehicleID = iSAMPVehicleID;
			vehSync.fPosition[0] = fPos[0];
			vehSync.fPosition[1] = fPos[1];
			vehSync.fPosition[2] = fPos[2];
			vehSync.fVehicleHealth = vinfo->hitpoints;
			vehSync.fMoveSpeed[0] = fSpeed[0];
			vehSync.fMoveSpeed[1] = fSpeed[1];
			vehSync.fMoveSpeed[2] = fSpeed[2];
			vehSync.sKeys = 0;
			vehSync.byteArmor = 0.0f;
			if (set.MakeZeroHPforCars)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			}
			//g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vect3_zero(vinfo->speed);

			v++;

		find_another_car:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
		}
	}
}
void AF_CarSmoking()
{
	if (cheat_state->Arac.iCarSmoking == 1)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);
		
		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 250.0f, vinfo->speed);
		vinfo->hitpoints = 250.0f;
		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			vinfo->hitpoints = 250.0f;
			cheat_state->Arac.iCarSmoking = 0;
		}
	}
}
void AF_CrazyCar1() // All Colors / Bütün Renkler
{
	static DWORD Delay = set.CarCheats.iCrazyCar1_Delay;
	if (cheat_state->Arac.CrazyCar1)
	{
		if (vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE) == NULL)
			return;
		if (GetTickCount() - set.CarCheats.iCrazyCar1_Delay > Delay)
		{
			vehicle_setColor0(vehicle_info_get(VEHICLE_SELF, 0), rand() % 255);
			vehicle_setColor1(vehicle_info_get(VEHICLE_SELF, 0), rand() % 255);
			Delay = GetTickCount();
		}
	}
}

void AF_CrazyCar2() // Sadece Jantlar
{
	static DWORD Delay = set.CarCheats.iCrazyCar2_Delay;
	if (cheat_state->Arac.CrazyCar2 && cheat_state->state == CHEAT_STATE_VEHICLE)
	{
		if (vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE) == NULL)
			return;
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, NULL);
		int Wheels_v[] = { 1025, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098 }; // 17
		static int i = 0;
		if (GetTickCount() - set.CarCheats.iCrazyCar2_Delay > Delay)
		{
			if (vinfo->passengers[0] == self)
			{
				sendSCMEvent(2, g_Players->pLocalPlayer->sCurrentVehicleID, Wheels_v[i], Wheels_v[i]);
				vehicle_addUpgrade(vinfo, Wheels_v[i]);
			}
			else
			{
				int vehID = g_Players->pLocalPlayer->passengerData.sVehicleID;
				struct vehicle_info	*vtemp = getGTAVehicleFromSAMPVehicleID(vehID);

				sendSCMEvent(2, vehID, Wheels_v[i], Wheels_v[i]);
				vehicle_addUpgrade(vtemp, Wheels_v[i]);
			}
			i++;
			if (i >= 17) i = 0;
			Delay = GetTickCount();
		}
	}
}
void AF_CrazyCar3() // Sadece Paintjoblar
{
	if (cheat_state->Arac.CrazyCar3 == 1)
	{
		if (vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE) == NULL)
			return;
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);
		static DWORD		Delay = set.CarCheats.iCrazyCar3_Delay;
		struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, NULL);
		int paintJobs[] = { 0, 1, 2, 4 }; // 4
		static int i = 0;

		if (GetTickCount() - set.CarCheats.iCrazyCar3_Delay > Delay)
		{
			if (vinfo->passengers[0] == self)
			{
				vehicle_setPaintJob(vinfo, paintJobs[i]);
			}
			else
			{
				int vehID = g_Players->pLocalPlayer->passengerData.sVehicleID;
				struct vehicle_info	*vtemp = getGTAVehicleFromSAMPVehicleID(vehID);

				sendSCMEvent(1, vehID, paintJobs[i], paintJobs[i]);
				vehicle_setPaintJob(vtemp, paintJobs[i]);
			}

			i++;
			if (i >= 4) i = 0;

			Delay = GetTickCount();
		}
	}
}
void AF_CrazyCar4() // Sadece Siyah ve Beyaz
{
	if (cheat_state->Arac.CrazyCar4)
	{

		if (vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE) == NULL) return;
		static DWORD Delay = set.CarCheats.iCrazyCar4_Delay;
		if (GetTickCount() - set.CarCheats.iCrazyCar4_Delay > Delay)
		{
			vehicle_setColor0(vehicle_info_get(VEHICLE_SELF, 0), rand() % 2);
			vehicle_setColor1(vehicle_info_get(VEHICLE_SELF, 0), rand() % 2);
			Delay = GetTickCount();
		}
	}
}
void AF_CarPick()
{
	//OLCheats->bIsVehCheatActive = true;
	static bool bVehCheatActive = true;
	if (cheat_state->Arac.CarPick)
	{
		/*render->D3DBox((pPresentParam.BackBufferWidth / 2) - 20.0f, (pPresentParam.BackBufferHeight / 2) - 1.0f, 40.0f, 2.0f, 0xFF00FFFF);
		render->D3DBox((pPresentParam.BackBufferWidth / 2) - 1.0f, (pPresentParam.BackBufferHeight / 2) - 20.0f, 2.0f, 40.0f, 0xFF00FFFF);*/
		static bool bVehiclePicked = false;
		static int vehicleID = 0;

		if (KEY_DOWN(VK_RBUTTON))
		{
			if (!bVehiclePicked)
			{
				int tempVehicleID = iGetAimingVehicle();
				if (IsVehicleStreamed(tempVehicleID))
				{
					vehicleID = tempVehicleID;
					bVehiclePicked = true;
				}
			}
			else
			{
				if (IsVehicleStreamed(vehicleID))
				{
					if (!g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->pedFlags.bInVehicle)
					{
						RakNet::BitStream bsData4OnFoot;
						bsData4OnFoot.Write((BYTE)ID_PLAYER_SYNC);
						bsData4OnFoot.Write((PCHAR)&g_Players->pLocalPlayer->onFootData, sizeof(stOnFootData));
						g_RakClient->Send(&bsData4OnFoot, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					}
					vehicle_info *vinfo = getGTAVehicleFromSAMPVehicleID(vehicleID);
					float fPos[3];
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						fPos);
					fPos[0] += cam_matrix[4] * 5.0f;
					fPos[1] += cam_matrix[5] * 5.0f;
					fPos[2] += cam_matrix[6] * 5.0f;
					float fSpeed[3] = { 0, 0, -0.1f };
					stUnoccupiedData UnoccupiedData;
					memset(&UnoccupiedData, 0, sizeof(stUnoccupiedData));
					UnoccupiedData.sVehicleID = vehicleID;
					UnoccupiedData.fHealth = vinfo->hitpoints;
					UnoccupiedData.byteSeatID = 1;
					vect3_copy(fPos, UnoccupiedData.fPosition);
					vect3_copy(fSpeed, UnoccupiedData.fMoveSpeed);
					vect3_copy(vinfo->spin, UnoccupiedData.fTurnSpeed);
					vect3_copy(&vinfo->base.matrixStruct->right.X, UnoccupiedData.fRoll);
					vect3_copy(&vinfo->base.matrixStruct->up.X, UnoccupiedData.fDirection);
					UnoccupiedData.fHealth = vinfo->hitpoints;//1000.0f;
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsData.Write((PCHAR)&UnoccupiedData, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);

					cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
					vect3_copy(fSpeed, vinfo->speed);
				}
			}
		}
		else
		{
			bVehiclePicked = false;
		}
	}
}
void AF_CarColorize()
{
	if (cheat_state->Arac.CarColorize)
	{
		static DWORD time = GetTickCount();
		float fPos[3];
		if (GetTickCount() - time >= 275) // 250
		{
			//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* info = vehicle_info_get(car_id, 0);
					stInCarData sync;
					RakNet::BitStream bsVehicleSync;
					memset(&sync, 0, sizeof(stInCarData));
					sync.sVehicleID = v;
					sync.fVehicleHealth = info->hitpoints;
					sync.fMoveSpeed[0] = info->speed[0];
					sync.fMoveSpeed[1] = info->speed[1];
					sync.fMoveSpeed[2] = info->speed[2];
					//sync.bytePlayerHealth = self->hitpoints;
					//sync.byteCurrentWeapon = self->armor;
					vect3_copy(&info->base.matrix[12], fPos);
					sync.fPosition[0] = fPos[0];
					sync.fPosition[1] = fPos[1];
					sync.fPosition[2] = fPos[2];
					bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
					g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					//g_RakClient->SendFakeDriverSyncData(v, fPos, info->hitpoints, info->speed);
					int new_color = rand() % 255, new_color2 = rand() % 255;
					vehicle_setColor0(info, new_color);
					vehicle_setColor1(info, new_color2);
					sendSCMEvent(3, v, new_color, new_color2);
				}
			}
			time = GetTickCount();
		}
	}
}
void AF_BlackWhiteCars()
{
	if (cheat_state->Arac.BlackWhiteCars == 1)
	{
		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 250) // 250
		{
			//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* info = vehicle_info_get(car_id, 0);
					stInCarData sync;
					RakNet::BitStream bsVehicleSync;
					memset(&sync, 0, sizeof(stInCarData));
					sync.sVehicleID = v;
					sync.fVehicleHealth = info->hitpoints;
					sync.fMoveSpeed[0] = info->speed[0];
					sync.fMoveSpeed[1] = info->speed[1];
					sync.fMoveSpeed[2] = info->speed[2];
					//sync.bytePlayerHealth = self->hitpoints;
					//sync.byteCurrentWeapon = self->armor;
					vect3_copy(&info->base.matrix[12], sync.fPosition);
					bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
					g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					vehicle_setColor0(info, rand() % 2);
					vehicle_setColor1(info, rand() % 2);
					sendSCMEvent(3, v, rand() % 2, rand() % 2);
				}
			}
			time = GetTickCount();
		}
	}
}
void AF_RemoveCars()
{
	if (cheat_state->Arac.RemoveCars)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3] = { sqrt((float)-1), sqrt((float)-1), sqrt((float)-1) };

		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
		g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			cheat_state->Arac.RemoveCars = 0;
		}
	}
}
void AF_DeleteCars()
{
	if (cheat_state->Arac.DeleteCars)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;

		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, VEHICLE_EMPTY);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		float fPos1[3];
		stUnoccupiedData unocSync;
		memset(&unocSync, 0, sizeof(stUnoccupiedData));
		unocSync.sVehicleID = iSAMPVehicleID;
		vect3_copy(fPos1, &unocSync.fPosition[0]);
		vect3_copy(unocSync.fRoll, &vinfo->base.matrixStruct->right.X);
		vect3_copy(unocSync.fDirection, &vinfo->base.matrixStruct->up.X);
		vect3_copy(unocSync.fTurnSpeed, &vinfo->spin[0]);
		vect3_copy(unocSync.fMoveSpeed, &vinfo->speed[0]);
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos1);
		fPos1[2] += 1.0f;

		g_RakClient->SendFakeUnoccupiedFullSyncData(&unocSync);

		cheat_vehicle_teleport(vinfo, fPos1, gta_interior_id_get());

		float fPos[3] = { sqrt((float)-1), sqrt((float)-1), sqrt((float)-1) };

		vect3_copy(fPos, &unocSync.fPosition[0]);

		g_RakClient->SendFakeUnoccupiedFullSyncData(&unocSync);
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			cheat_state->Arac.DeleteCars = 0;
		}
	}
}
void AF_PinkCars()
{
	if (cheat_state->Arac.PinkCars)
	{
		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 275) // 250
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (IsVehicleStreamed(v))
				{

					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* info = vehicle_info_get(car_id, 0);
					stInCarData sync;
					RakNet::BitStream bsVehicleSync;
					memset(&sync, 0, sizeof(stInCarData));
					sync.sVehicleID = v;
					sync.fVehicleHealth = info->hitpoints;
					sync.fMoveSpeed[0] = info->speed[0];
					sync.fMoveSpeed[1] = info->speed[1];
					sync.fMoveSpeed[2] = info->speed[2];
					//sync.bytePlayerHealth = self->hitpoints;
					//sync.byteCurrentWeapon = self->armor;
					vect3_copy(&info->base.matrix[12], sync.fPosition);
					bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
					g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					int new_color = 5, new_color2 = 5; // SA-MP'ta Araç Renk ID'larýna baktým ve 5 numara Pink(Pembe) anlamýna geliyor. Pink Cars kodlayasým geldi xD
					vehicle_setColor0(info, 5);
					vehicle_setColor1(info, 5);
					sendSCMEvent(3, v, 5, 5);
				}
			}
			time = GetTickCount();
		}
	}
}
void AF_CarCircle()
{
	if (cheat_state->Arac.iCarCircle)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPozisyon[3];
		vect3_copy(&self->base.matrix[4 * 3], fPozisyon);
		static int x = 0;

		// Special Thanks to DarkNeX for circle, DarkNeX'e bu daire için özel teþekkürler.
		fPozisyon[0] += sinf(19.0f * (float)x) * 35.0f;
		fPozisyon[1] += cosf(19.0f * (float)x) * 35.0f;
		fPozisyon[2] += 12.5f; // Orijinal deðer: 10.0f.
		x++;
		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));
		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPozisyon[0];
		vehSync.fPosition[1] = fPozisyon[1];
		vehSync.fPosition[2] = fPozisyon[2];
	if (set.MakeZeroHPforCars == true)
		vehSync.fVehicleHealth = 1.0f;
	else
		vehSync.fVehicleHealth = vinfo->hitpoints;
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;
		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, vinfo->speed);
		g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, vinfo->speed);
		/*g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);*/
		
		cheat_vehicle_teleport(vinfo, fPozisyon, gta_interior_id_get());
		vect3_zero(vinfo->speed);

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
		//time = GetTickCount();
	}
}
void AF_ExAttacker(void)
{
	traceLastFunc("AF_ExAttacker()");
	if (cheat_state->Arac.iExAttacker)
	{
		//struct actor_info	*self = actor_info_get(actor_find_nearest(ACTOR_ALIVE), -1);
		struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_ALIVE, -1);
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;
		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;
		static DWORD time = GetTickCount();
		
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (GetTickCount() - time >= 175)
				{
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
					int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
					if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
						continue;
					float fPos[3];
					vect3_copy(&nearest->base.matrix[4 * 3], fPos);
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos,1.0f, vinfo->speed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
					cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				}
				time = GetTickCount();
			}
			
		}
	}
}
void AF_CarShooter()
{
	if (cheat_state->Arac.iCarShooter)
	{
		traceLastFunc("AF_CarShooter()");
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;
		static int x = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if (KEY_DOWN(VK_LBUTTON))
		{
			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);
			fPos[0] += cam_matrix[4] * (6.0f + x);
			fPos[1] += cam_matrix[5] * (6.0f + x);
			fPos[2] += cam_matrix[6] * (2.0f + x);
			float fSpeed[3];
			fSpeed[0] = cam_matrix[4] * 7.5f;
			fSpeed[1] = cam_matrix[5] * 7.5f;
			fSpeed[2] = cam_matrix[6] * 7.5f;

		/*	if (set.MakeZeroHPforCars == true)
				VehicleSynchronization(fPos, fSpeed, true);
			else
				VehicleSynchronization(fPos, fSpeed, false);*/
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];
			x--;
			if (x < -1) x = 0;

			v++;
		}

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarFucker()
{
	//traceLastFunc("carfucker()");
	if (cheat_state->Arac.iCarFucker)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		fPos[0] += -50 + rand() % 100;
		fPos[1] += -50 + rand() % 100;
		fPos[2] += 20.0f;
		float fSpeed[3];
		fSpeed[0] = sinf(fPos[0]) * 5;
		fSpeed[1] = cosf(fPos[1]) * 5;
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}
void AF_CarFollowTroll()
{
	//traceLastFunc("followtroller()");
	if (cheat_state->Arac.iCarFollowTroll)
	{
		//struct actor_info    *self = actor_info_get(actor_find_nearest(ACTOR_ALIVE), -1);

		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 250)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				/*if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;*/
				GetStreamedVehicle(v);
				//if ((self = actor_info_get(ACTOR_SELF, 0)) == NULL) continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&nearest->base.matrix[4 * 3], fPos);

				fPos[0] += -50 + rand() % 70;
				//fPos[1] += -50 + rand() % 70;
				//fPos[2] += 20.0f;

				float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]) * 5;
				fSpeed[1] = cosf(fPos[1]) * 5;
				if (set.MakeZeroHPforCars == true)
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
				}
				else
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
				}
					/*	if (set.MakeZeroHPforCars == true)
					VehicleSynchronization(fPos, fSpeed, true);
				else
					VehicleSynchronization(fPos, fSpeed, false);*/
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				vinfo->speed[0] = fSpeed[0];
				vinfo->speed[1] = fSpeed[1];
			}
			time = GetTickCount();
		}
	}
}

void AF_ZFollowTroll()
{
	//traceLastFunc("zfollow()");
	if (cheat_state->Arac.iCarZTroll == 1)
	{
		//struct actor_info    *self = actor_info_get(actor_find_nearest(ACTOR_ALIVE), -1);
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 200)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
			/*	if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;*/
				GetStreamedVehicle(v);
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&nearest->base.matrix[4 * 3], fPos);

				fPos[2] += -50 + rand() % 100;
				if (set.MakeZeroHPforCars == true)
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
				}
				else
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
				}
				/*if (set.MakeZeroHPforCars == true)
					VehicleSynchronization(fPos, vinfo->speed, true);
				else
					VehicleSynchronization(fPos, vinfo->speed, false);*/
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			}
			time = GetTickCount();
		}
	}
}

void AF_UnnamedTroll()
{
	//traceLastFunc("unnamedtroll()");
	if (cheat_state->Arac.iCarUnnamedTroll)
	{
		int					nearest_id = actor_find_nearest(ACTOR_ALIVE);
		struct actor_info	*nearest;

		if (nearest_id == -1) return;
		if ((nearest = actor_info_get(nearest_id, ACTOR_ALIVE)) == NULL) return;

		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 225)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				/*if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;*/
				GetStreamedVehicle(v);
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				float fPos[3];
				vect3_copy(&nearest->base.matrix[4 * 3], fPos);

				//fPos[2] += -50 + rand() % 100;
				fPos[2] += rand() % 10;

				float fSpeed[3];
				fSpeed[0] = sinf(fPos[0]) * 5;
				fSpeed[1] = cosf(fPos[1]) * 5;
				if (set.MakeZeroHPforCars == true)
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				}
				else
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
				}
				/*if (set.MakeZeroHPforCars == true)
					VehicleSynchronization(fPos, fSpeed, true);
				else
					VehicleSynchronization(fPos, fSpeed, false);*/
				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				vinfo->speed[0] = fSpeed[0];
				vinfo->speed[1] = fSpeed[1];
			}
			time = GetTickCount();
		}
	}
}

void AF_ExplodeCars()
{
	//traceLastFunc("cheat_handle_explodecars()");

	if (cheat_state->Arac.iExplodeCars == 1)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

		//VehicleSynchronization(fPos, vinfo->speed, false);
		g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 0.0f, vinfo->speed);
		vinfo->hitpoints = 0.0f;

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			cheat_state->Arac.iExplodeCars = 0;
		}
	}
}

void AF_HopCars()
{
	//traceLastFunc("cheat_handle_hopcars()");

	if (cheat_state->Arac.iHopCars)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&vinfo->base.matrix[4 * 3], fPos);

		float fSpeed[3] = { vinfo->speed[0], vinfo->speed[1], 1.0f };
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
	/*	if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			cheat_state->Arac.iHopCars = 0;
		}
	}
}

void AF_RespawnCars()
{
	//traceLastFunc("cheat_handle_respawncars()");

	if (cheat_state->Arac.iRespawnCars == 1)
	{
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		g_RakClient->NotifyVehicleDeath(iSAMPVehicleID);

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
		{
			v = 0;
			cheat_state->Arac.iRespawnCars = 0;
		}
	}
}

void AF_CarsFloating()
{
	//traceLastFunc("cheat_handle_carsfloating()");

	if (cheat_state->Arac.iCarFloating)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 1st version
		fPos[0] += -15 + rand() % 35;
		fPos[1] += -15 + rand() % 35;
		fPos[2] += 8.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 1.75f };

		float fQuaternion = -180.0f;

		stInCarData vehSync;
		memset(&vehSync, 0, sizeof(stInCarData));

		vehSync.sVehicleID = iSAMPVehicleID;
		vehSync.fPosition[0] = fPos[0];
		vehSync.fPosition[1] = fPos[1];
		vehSync.fPosition[2] = fPos[2];
		vehSync.fMoveSpeed[0] = fSpeed[0];
		vehSync.fMoveSpeed[1] = fSpeed[1];
		vehSync.fMoveSpeed[2] = fSpeed[2];
		vehSync.sKeys = 0;
		if (set.MakeZeroHPforCars == true)
		{
			vehSync.fVehicleHealth = 1.0f;
		}
		else
			vehSync.fVehicleHealth = 1000.0f;
		vehSync.bytePlayerHealth = self->hitpoints;
		vehSync.byteArmor = self->armor;
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsFloating2()
{
	//traceLastFunc("cheat_handle_carsfloating2()");

	if (cheat_state->Arac.iCarFloating2)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		// 2nd version
		fPos[0] += -15 + rand() % 30;
		fPos[1] += -15 + rand() % 30;
		fPos[2] += 20.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.3f };

		//stInCarData vehSync;
		//memset(&vehSync, 0, sizeof(stInCarData));

		//vehSync.sVehicleID = iSAMPVehicleID;
		//vehSync.fPosition[0] = fPos[0];
		//vehSync.fPosition[1] = fPos[1];
		//vehSync.fPosition[2] = fPos[2];
		//vehSync.fVehicleHealth = vinfo->hitpoints;
		//vehSync.fMoveSpeed[0] = fSpeed[0];
		//vehSync.fMoveSpeed[1] = fSpeed[1];
		//vehSync.fMoveSpeed[2] = fSpeed[2];
		//vehSync.sKeys = 0;
		//if (set.MakeZeroHPforCars == true)
		//	vehSync.fVehicleHealth = 1.0f;
		//else
		//	vehSync.fVehicleHealth = 1000.0f;

		//vehSync.bytePlayerHealth = self->hitpoints;
		//vehSync.byteArmor = self->armor;

		//g_RakClient->SendFakeDriverFullSyncData(&vehSync, 0);
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsTornado()
{
	traceLastFunc("AF_CarsTornado()");

	if (cheat_state->Arac.iCarsTornado == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		static int x = 1;
		fPos[0] += sinf(19.0f * (float)x) * 27;
		fPos[1] += cosf(19.0f * (float)x) * 27;
		fPos[2] += 8.0f+ tanf(19.0f * (float)x) - 6.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 2.0f;
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		x++;
		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsMagnet()
{
	//traceLastFunc("cheat_handle_carsmagnet()");

	if (cheat_state->Arac.iCarsMagnet)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float mPos[3], cPos[3];
		vect3_copy(&self->base.matrix[4 * 3], mPos);
		vect3_copy(&vinfo->base.matrix[4 * 3], cPos);

		float x = (mPos[0] - cPos[0]);
		float y = (mPos[1] - cPos[1]);
		float z = (mPos[2] - cPos[2]);

		float radius = sqrt(x * x + y * y + z * z);
		float power = 20 * 1000;

		float force_x = MagnetForce(x, radius, power, vinfo->mass);
		float force_y = MagnetForce(y, radius, power, vinfo->mass);
		float force_z = MagnetForce(z, radius, power, vinfo->mass);

		vinfo->speed[0] = force_x;
		vinfo->speed[1] = force_y;
		vinfo->speed[2] = force_z;

		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, cPos, 1.0f, vinfo->speed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, cPos, 1.0f, vinfo->speed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, cPos, vinfo->hitpoints, vinfo->speed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, cPos, vinfo->hitpoints, vinfo->speed);
		}
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(cPos, vinfo->speed, true);
		else
			VehicleSynchronization(cPos, vinfo->speed, false);*/
		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsFucker2()
{
	//traceLastFunc("cheat_handle_carsfucker()");

	if (cheat_state->Arac.iCarsFucker2)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		/*fPos[0] += rand0m(-30.0f, 30.0f);
		fPos[1] += rand0m(-30.0f, 30.0f);
		fPos[2] += 30.0f + rand0m(0, 45);*/
		fPos[0] += -50 + rand() % 100;
		fPos[1] += -50 + rand() % 100;
		fPos[2] += 30.0f;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[0] = sinf(fPos[0]) * 1.3f;
		fSpeed[1] = cosf(fPos[1]) * 1.3f;
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsLine()
{
	//traceLastFunc("cheat_handle_carline()");

	if (cheat_state->Arac.iCarsLine)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		static int x = 1;

		/* Line */
		fPos[0] += sinf(-self->fCurrentRotation * (float)x) * 100;
		fPos[1] += cosf(-self->fCurrentRotation * (float)x) * 100;
		fPos[2] += 5;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 0.0f;
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		x++;
		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarsTower()
{
	//traceLastFunc("cheat_handle_cartower()");

	if (cheat_state->Arac.iCarsTower == 1)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		fPos[2] += 5;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 2.0f;
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_FallingCars()
{
	//traceLastFunc("cheat_handle_fallingcars()");

	if (cheat_state->Arac.iFallingCars)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		fPos[0] += R4nd0m(-20, 20);
		fPos[1] += R4nd0m(-20, 20);
		fPos[2] += 20 + R4nd0m(0, 15);

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 20.0f;
		//if (set.MakeZeroHPforCars == true)
		//	VehicleSynchronization(fPos, fSpeed, true);
		//else
		//	VehicleSynchronization(fPos, fSpeed, false);
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_FlyingCars()
{
	//traceLastFunc("cheat_handle_flyingcars()");

	static int once = 1;
	static int state[SAMP_MAX_VEHICLES];

	if (cheat_state->Arac.iFlyingCars)
	{
		if (once == 1)
			once = 0;

		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;
		static float fPos[SAMP_MAX_VEHICLES][3];

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if (state[v] == 0)
		{
			vect3_copy(&vinfo->base.matrix[4 * 3], fPos[v]);
			fPos[v][2] += 15.0f;

			state[v] = 1;
		}

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 20.0f;
	/*	if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos[v], fSpeed, true);
		else
			VehicleSynchronization(fPos[v], fSpeed, false);*/
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos[v], 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos[v], 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos[v], vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos[v], vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos[v], gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
	else
	{
		if (once == 0)
		{
			for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
				state[i] = 0;

			once = 1;
		}
	}
}

void AF_ShakingCars()
{
	//traceLastFunc("cheat_handle_shakingcarscars()");

	static int once = 1;
	static int state[SAMP_MAX_VEHICLES];

	if (cheat_state->Arac.iShakingCars)
	{
		if (once == 1)
			once = 0;

		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;
		static float fPos[SAMP_MAX_VEHICLES][3];

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		if (state[v] == 0)
		{
			vect3_copy(&vinfo->base.matrix[4 * 3], fPos[v]);

			float fGroundZHeight = pGame->GetWorld()->FindGroundZForPosition(fPos[v][0], fPos[v][1]);

			fPos[v][2] = fGroundZHeight + 2.0f;

			state[v] = 1;
		}

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = -20;
		/*if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos[v], fSpeed, true);
		else
			VehicleSynchronization(fPos[v], fSpeed, false);*/

		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos[v], 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos[v], 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos[v], vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos[v], vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos[v], gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
	else
	{
		if (once == 0)
		{
			for (int i = 0; i < SAMP_MAX_VEHICLES; i++)
				state[i] = 0;

			once = 1;
		}
	}
}

void AF_CarsTornado2()
{
	//traceLastFunc("cheat_handle_carstornado2()");

	if (cheat_state->Arac.iCarsTornado2)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);
		
		static int x = 1;
		static int radius_counter = 1;
		static int height_counter = 1;

		if (radius_counter > 70) radius_counter = 1;
		if (height_counter > 100) height_counter = 1;

		/* Circle */
		fPos[0] += sinf(19.0f * (float)x) * radius_counter;
		fPos[1] += cosf(19.0f * (float)x) * radius_counter;
		fPos[2] += height_counter;

		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[2] = 1.0f;
		//if (set.MakeZeroHPforCars == true)
		//	VehicleSynchronization(fPos, fSpeed, true);
		//else
		//	VehicleSynchronization(fPos, fSpeed, false);
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[2] = fSpeed[2];

		x++;
		radius_counter++;
		height_counter++;

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void H_VehicleFlooder(struct vehicle_info* vinfo, float time_diff)
{
	traceLastFunc("H_VehicleFlooder()");
	if (cheat_state->Arac.iCarFlooder == 1)
	{
		static int state = 1;
		if (state == 0)
		{
			for (int i = 0; i < 6; i++)
				vinfo->door_damage_status[i] = 4;

			vinfo->car_bumper_status = 3;
			vinfo->car_bumper_status_front = 3;
			vinfo->car_bumper_status_rear = 3;
			vinfo->car_windshield_status = 3;
			vinfo->car_status_left = 3;
			vinfo->car_status_right = 3;
			state = 1;
		}
		else
		{
			//GTAfunc_RepairVehicle(vinfo);

			CVehicle* pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD*)vinfo);

			if (pVehicle)
				pVehicle->Fix();

			state = 0;
		}
	}
	return;
}
	
void AF_CarWheelize()
{
	if (cheat_state->Arac.iCarWheelize)
	{
		static DWORD time = GetTickCount();
		int Wheels_v[] = { 1025, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1096, 1097, 1098 }; // 17
		for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
		{
			if (GetTickCount() - time >= 275) // 250
			{
				//struct actor_info *self = actor_info_get(-1, ACTOR_ALIVE);
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* info = vehicle_info_get(car_id, 0);
					RakNet::BitStream bsVehicleSync;
					stInCarData sync;
					memset(&sync, 0, sizeof(stInCarData));
					sync.sVehicleID = v;
					vect3_copy(&info->base.matrix[12], sync.fPosition);
					sync.fMoveSpeed[0] = info->speed[0];
					sync.fMoveSpeed[1] = info->speed[1];
					sync.fMoveSpeed[2] = info->speed[2];
					sync.fVehicleHealth = info->hitpoints;
					static int i = 0;
					struct vehicle_info* vtemp = getGTAVehicleFromSAMPVehicleID(v);
					sendSCMEvent(2, v, Wheels_v[i], Wheels_v[i]);
					i++;
					if (i >= 17) i = 0;
					vehicle_addUpgrade(vtemp, Wheels_v[i]);
					bsVehicleSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsVehicleSync.Write((PCHAR)&sync, sizeof(stInCarData));
					g_RakClient->Send(&bsVehicleSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
				}
				time = GetTickCount();
			}
		}
	}
}
void AF_CarSun()
{
	if (cheat_state->Arac.iCarSun)
	{
		struct actor_info *oyuncubilgisi = actor_info_get(ACTOR_SELF, 0);
		struct vehicle_info *aracbilgisi = vehicle_info_get(VEHICLE_SELF, 0);
		float fPos[3]; // Pozisyonlar.. dizi ile tanýmlý 0-1-2 pozisyonlarý. 3 dahil mi bilmiyorum. - RapidFire
		static DWORD time = GetTickCount();
		if (GetTickCount() - time >= 225)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				/*if (g_Vehicles->iIsListed[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v] == NULL) continue;
				if (g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL) continue;*/
				GetStreamedVehicle(v);
				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info *vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID) continue;

				vect3_copy(&oyuncubilgisi->base.matrix[4 * 3], fPos); // Veri kopyalamasý
				static float Angle = set.CarCheats.Car_Sun_Angle; // Angle bildiðim kadarýyla mesafeydi türkçesi ama yanýlýyor da olabilirim - RapidFire
				fPos[2] += set.CarCheats.Car_Sun_Z_Position_Height;
				float AbsSpeed = set.CarCheats.Car_Sun_Abs_Speed; // Deðiþken adý
				float fSpeed[3]; // float hýz, ondalýklý hýz dizi ile tanýmlý 0-1-2 dediðim gibi.. 3 dahil mi bilmiyorum. - RapidFire

				/*fSpeed[0] = sinf(fPos[0]); ///// ESKÝ DEÐÝÞKEN DEÐERLERÝ
				fSpeed[1] = cosf(fPos[1]);*/ ///// ESKÝ DEÐÝÞKEN DEÐERLERÝ

				fSpeed[0] = AbsSpeed * cos(Angle);
				fSpeed[1] = AbsSpeed * sin(Angle);

				Angle += DEGTORAD(set.CarCheats.Car_Sun_Degree_To_Radian_Value); // 115'den 45 yaptým.
				/*if(set.MakeZeroHPforCars == true)
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, vinfo->speed);
				else
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);
				if (set.MakeZeroHPforCars == true)
					VehicleSynchronization(fPos, fSpeed, true);
				else
					VehicleSynchronization(fPos, fSpeed, false);*/
				if (set.MakeZeroHPforCars == true)
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				}
				else
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
					g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
				}

				cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				vinfo->speed[0] = fSpeed[0];
				vinfo->speed[1] = fSpeed[1];
			}
			time = GetTickCount();
		}
	}
}
void AF_CarPosLagger() // Hata veren ne varsa sil gitsin.
{
	if (cheat_state->Arac.iCarPosLagger)
	{
		struct vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, NULL);
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, NULL);
		static DWORD time = GetTickCount();
		float fPos[3];
		float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
	
		if (GetTickCount() - time >= 150)
		{
			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
					float fSpeed[3] = { 0, 0, -0.01f };
					int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

					if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
						continue;
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						fPos);
					fPos[0] = coord[0] + set.CarCheats.CarLagger_Coords[0];
					fPos[1] = coord[1] + set.CarCheats.CarLagger_Coords[1];
					fPos[2] = coord[2] + set.CarCheats.CarLagger_Coords[2];
					stUnoccupiedData unocSync;
					ZeroMemory(&unocSync, sizeof(stUnoccupiedData));
					unocSync.sVehicleID = v;
					unocSync.fPosition[0] = fPos[0];
					unocSync.fPosition[1] = fPos[1];
					unocSync.fPosition[2] = fPos[2];
					unocSync.fMoveSpeed[0] = fSpeed[0];
					unocSync.fMoveSpeed[1] = fSpeed[1];
					unocSync.fMoveSpeed[2] = fSpeed[2];
					unocSync.fRoll[0] = 1.0f;
					unocSync.fRoll[1] = 1.0f;
					unocSync.fRoll[2] = 1.0f;
					unocSync.fDirection[0] = 1.0f;
					unocSync.fDirection[1] = 1.0f;
					unocSync.fDirection[2] = 1.0f;
					unocSync.fTurnSpeed[0] = vinfo->spin[0];
					unocSync.fTurnSpeed[1] = vinfo->spin[1];
					unocSync.fTurnSpeed[2] = vinfo->spin[2];
					unocSync.fHealth = vinfo->hitpoints;
					RakNet::BitStream bsUnocSync;
					bsUnocSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsUnocSync.Write((PCHAR)&unocSync, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsUnocSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					//stInCarData inCarVerisi;
					//memset(&inCarVerisi, 0, sizeof(stInCarData));
					//inCarVerisi.sVehicleID = v; // For döngüsü.. v  = vehicle araç
					//inCarVerisi.bytePlayerHealth = ainfo->hitpoints; // Benim oyuncunun can deðerini kullan..
					//inCarVerisi.fPosition[0] = fPos_[0];
					//inCarVerisi.fPosition[1] = fPos_[1];
					//inCarVerisi.fPosition[2] = fPos_[2];
					//vect3_copy(fSpeed, vinfo->speed);
					//inCarVerisi.fVehicleHealth = vinfo->hitpoints; // Aracýn caný..
	/*				RakNet::BitStream bsInCarSync;
					bsInCarSync.Write((BYTE)ID_VEHICLE_SYNC);
					bsInCarSync.Write((PCHAR)&inCarVerisi, sizeof(stInCarData));
					g_RakClient->Send(&bsInCarSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);*/
					cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
				}
			}
			time = GetTickCount();
		}
	}
}
void AF_SpinningCars()
{
	/*if (cheat_state->Arac.iSpinningCars)
	{
		static int x = 0;
		float fSpeed[3];
		struct vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, NULL);
		struct actor_info* ainfo = actor_info_get(ACTOR_SELF, NULL);
		float fPos[3];
		float* coord = (cheat_state->state == CHEAT_STATE_VEHICLE) ? cheat_state->vehicle.coords : cheat_state->actor.coords;
		float fSpinSpeed[3] = { random_float(1.0f, 4.0f),random_float(1.0f, 4.0f), random_float(1.0f, 4.0f) };
		static DWORD dwTick = 150;
		for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
		{
			if (GetTickCount() - dwTick > 150)
			{
				if (IsVehicleStreamed(v))
				{
					int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
					struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);
					int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

					if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
						continue;
					vect3_copy(&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
						fPos);
					stUnoccupiedData Unoc;
					memset(&Unoc, 0, sizeof(stUnoccupiedData));
					Unoc.sVehicleID = v;
					fPos[0] += cosf(1.1f) + rand() % 18;
					fPos[1] += sinf(1.1f) + rand() % 7;
					fPos[2] += random_float(2.0f,8.0f);
					Unoc.fPosition[0] = fPos[0];
					Unoc.fPosition[1] = fPos[1];
					Unoc.fPosition[2] = fPos[2];
					Unoc.fMoveSpeed[0] = vinfo->speed[0];
					Unoc.fMoveSpeed[1] = vinfo->speed[1];
					Unoc.fMoveSpeed[2] = vinfo->speed[2];
					Unoc.fTurnSpeed[0] = fSpinSpeed[0];
					Unoc.fTurnSpeed[1] = fSpinSpeed[1];
					Unoc.fTurnSpeed[2] = fSpinSpeed[2];
					RakNet::BitStream bsData;
					bsData.Write((BYTE)ID_UNOCCUPIED_SYNC);
					bsData.Write((PCHAR)&Unoc, sizeof(stUnoccupiedData));
					g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
					cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
					vect3_zero(vinfo->speed);
					v++;
				find_another_car:
					for (v; v < SAMP_MAX_VEHICLES; v++)
					{
						if (g_Vehicles->iIsListed[v] == 1)
							break;
					}
					if (v >= SAMP_MAX_VEHICLES)
						v = 0;
				}
				dwTick = GetTickCount();
			}
		}
	}*/
}
void AF_CarCircle2()
{
	if (cheat_state->Arac.iCarCircle2)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;
		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
			static int x = 0;
			float fPozisyon[3];
			static DWORD time = GetTickCount();
			float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
			vect3_copy(&self->base.matrix[4 * 3], fPozisyon);

			if (set.CarCheats.bCarCircle_Use_Random_Radius == true)
			{
				fPozisyon[0] += sinf(19.0f * (float)x) * random(set.CarCheats.fCarCircle_Random_Radius_Minimum_Value, set.CarCheats.fCarCircle_Random_Radius_Maximum_Value);
				fPozisyon[1] += cosf(19.0f * (float)x) * random(set.CarCheats.fCarCircle_Random_Radius_Minimum_Value, set.CarCheats.fCarCircle_Random_Radius_Maximum_Value);
			}
			else
			{
				fPozisyon[0] += sinf(19.0f * (float)x) * set.CarCheats.CarCircle3_Radius;
				fPozisyon[1] += cosf(19.0f * (float)x) * set.CarCheats.CarCircle3_Radius;
			}
			/* Random Z Height */
			if (set.CarCheats.bCarCircle_Use_Random_Z_Height == true) 
				fPozisyon[2] += random(set.CarCheats.fCarCircle_Random_Z_Height_Minimum_Value, set.CarCheats.fCarCircle_Random_Z_Height_Maximum_Value);
			else
				fPozisyon[2] += set.CarCheats.CarCircle_Z_Height;

			x++;
		
		/*	if (set.MakeZeroHPforCars == true)
				VehicleSynchronization(fPozisyon, fSpeed, true);
			else
				VehicleSynchronization(fPozisyon, fSpeed, false);*/
			if (set.MakeZeroHPforCars == true)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyon, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyon, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPozisyon, vinfo->hitpoints, fSpeed);
			}
			cheat_vehicle_teleport(vinfo, fPozisyon, gta_interior_id_get());
			vect3_zero(vinfo->speed);

			v++;

		find_another_car:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
	}
}
void AF_CarsFucker3()
{
	if (cheat_state->Arac.iCarsFucker3)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);
		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}

		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);

		fPos[0] += random(-18.0f, 33.0f);
		fPos[1] += random(-30.0f, 25.0f);
		fPos[2] += 6.5f;
		
		float fSpeed[3] = { 0.0f, 0.0f, 0.0f };
		fSpeed[0] = sinf(fPos[0]) * 1.3f;
		fSpeed[1] = cosf(fPos[1]) * 1.3f;
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
	/*	if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}

void AF_CarFollows3()
{
	if (cheat_state->Arac.iCarFollows3)
	{
		struct actor_info	*self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info	*vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON))
		{

			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);

			// 3rd version
			fPos[0] += (sinf(-self->fCurrentRotation) * 2.0f) + (-10 + rand() % 25);
			fPos[1] += (cosf(-self->fCurrentRotation) * 4.0f) + (-40 + rand() % 20);
			fPos[2] += 4.0f;

			float fSpeed[3] = { 0.0f, 0.0f, 0.0f };

		/*	if (set.MakeZeroHPforCars == true)
				VehicleSynchronization(fPos, fSpeed, true);
			else
				VehicleSynchronization(fPos, fSpeed, false);*/
			if (set.MakeZeroHPforCars == true)
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
				g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			}
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());
			vect3_zero(vinfo->speed);

			v++;

		find_another_car:
			for (v; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] == 1)
					break;
			}

			if (v >= SAMP_MAX_VEHICLES)
				v = 0;
		}
	}
}

void AF_CarsFloating3()
{
	if (cheat_state->Arac.iCarFloating3)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		static int v = 0;

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		GetStreamedVehicle(v);
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		float fPos[3];
		vect3_copy(&self->base.matrix[4 * 3], fPos);
		// 3rd version
		fPos[0] += -15 + rand() % set.CarCheats.fCarFloating3_Random_Value[0]; // X Position -> max random value
		fPos[1] += -15 + rand() % set.CarCheats.fCarFloating3_Random_Value[1]; // Y Position -> max random value
		fPos[2] += set.CarCheats.fCarFloating3_Z_Height;// Z Height...

		float fSpeed[3] = { 0.0f, 0.0f, 1.75f };

		float fQuaternion = -180.0f; // 

	/*	if (set.MakeZeroHPforCars == true)
			VehicleSynchronization(fPos, fSpeed, true);
		else
			VehicleSynchronization(fPos, fSpeed, false);*/
		if (set.MakeZeroHPforCars == true)
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, 1.0f, fSpeed);
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
			g_RakClient->SendFakeTrailerData(iSAMPVehicleID, fPos, vinfo->hitpoints, fSpeed);
		}
		cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

		vinfo->speed[0] = fSpeed[0];
		vinfo->speed[1] = fSpeed[1];
		vinfo->speed[2] = fSpeed[2];

		v++;

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
}
void AF_CarShooter4()
{
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	if (cheat_state->Arac.iCarShooter4)
	{
		static float fDistance = 19;
		static int iCounter = 3;
		static float f_CAngle = 4;
		static float rotate_speed = 23.1234f;
		static bool stillSending = false;
		static int v = 0;
		static int x = 0;
		struct actor_info* self = actor_info_get(ACTOR_SELF, NULL);

		if (g_Vehicles->iIsListed[v] != 1)
			goto find_another_car;
		int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
		struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

		int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
		if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			v++;
			goto find_another_car;
		}
		if (KEY_DOWN(VK_LBUTTON) || stillSending)
		{
			stInCarData inCar;
			memset(&inCar, 0, sizeof(stInCarData));
			stTrailerData trailerData;
			memset(&trailerData, 0, sizeof(stTrailerData));
			float fPos[3];
			vect3_copy(&self->base.matrix[4 * 3], fPos);
			float apos[3];
			/* Eðer ondalýk sayý deðiþkeni olan fDistance deðiþkenini
				sinüs'e parametre olarak verilen
				f_CAngle deðerini 90 ile toplayýp
				iCounter ile çarpýp çýkan sonucu
				M_PI ile çarpýp 180'e bölersen...
				Ýstediðine ulaþabilirsin.
			*/
			apos[0] = (fDistance * sinf(f_CAngle + ((90 * iCounter) * M_PI / 180)));
			apos[1] = 0;//(fDistance * sin(f_CAngle + (90 * iCounter) * M_PI / 180));//0;
			apos[2] = (fDistance * cosf(f_CAngle + ((90 * iCounter) * M_PI / 180)));
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
			fPos[2] += 0.2f;
			inCar.sVehicleID = iSAMPVehicleID;
			inCar.fPosition[0] = fPos[0];
			inCar.fPosition[1] = fPos[1];
			inCar.fPosition[2] = fPos[2];
			inCar.fMoveSpeed[0] = fSpeed[0];
			inCar.fMoveSpeed[1] = fSpeed[1];
			inCar.fMoveSpeed[2] = fSpeed[2];
			inCar.fVehicleHealth = vinfo->hitpoints;
			inCar.sTrailerID = iSAMPVehicleID;
			RakNet::BitStream bsData;
			bsData.Write((BYTE)ID_VEHICLE_SYNC);
			bsData.Write((PCHAR)&inCar, sizeof(stInCarData));
			g_RakClient->Send(&bsData, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			cheat_vehicle_teleport(vinfo, fPos, gta_interior_id_get());

			trailerData.sTrailerID = iSAMPVehicleID;
			vect3_copy(inCar.fPosition, trailerData.fPosition);
			vect3_copy(inCar.fMoveSpeed, trailerData.fMoveSpeed);
			RakNet::BitStream bsPackettrailer;
			bsPackettrailer.Write((BYTE)ID_TRAILER_SYNC);
			bsPackettrailer.Write((PCHAR)(&trailerData), sizeof(stTrailerData));
			g_RakClient->Send(&bsPackettrailer, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			vinfo->speed[0] = fSpeed[0];
			vinfo->speed[1] = fSpeed[1];
			vinfo->speed[2] = fSpeed[2];
			iCounter++;
			if (iCounter >= 4)
			{
				f_CAngle += rotate_speed * M_PI / 180;
				iCounter = 0;

				stillSending = false;
			}
			else
			{
				stillSending = true;
			}

			//x--;
			//if (x < -1) x = 0;

			v++;
		}

	find_another_car:
		for (v; v < SAMP_MAX_VEHICLES; v++)
		{
			if (g_Vehicles->iIsListed[v] == 1)
				break;
		}

		if (v >= SAMP_MAX_VEHICLES)
			v = 0;
	}
#endif
}
void AracFonksiyonlari(void)
{
	AF_MultiCarShooter();
	AF_MultiCarShooter2();
	AF_DoubleCarCircle();
	AF_MultiCarFollows();
	AF_CarSmoking();
	AF_CrazyCar1();
	AF_CrazyCar2();
	AF_CrazyCar3();
	AF_CrazyCar4();
	AF_CarPick();
	AF_CarColorize();
	AF_BlackWhiteCars();
	AF_RemoveCars();
	AF_DeleteCars();
	AF_PinkCars();
	AF_MultiCarFollows2();
	AF_CarCircle();
	AF_ExAttacker();
	AF_CarShooter();
	AF_CarFucker();
	AF_CarFollowTroll();
	AF_ZFollowTroll();
	AF_UnnamedTroll();
	AF_ExplodeCars();
	AF_HopCars();
	AF_RespawnCars();
	AF_CarsFloating();
	AF_CarsFloating2();
	AF_CarsTornado();
	AF_CarsMagnet();
	AF_CarsFucker2();
	AF_CarsLine();
	AF_ShakingCars();
	AF_CarsTower();
	AF_FlyingCars();
	AF_FallingCars();
	AF_CarsTornado2();
	AF_CarWheelize();
	AF_CarSun();
	AF_CarPosLagger();
	AF_SpinningCars();
	AF_CarCircle2(); // V3
	AF_CarsFucker3(); // V3
	AF_CarFollows3(); // V3
	AF_CarsFloating3(); // V3
	AF_CarShooter4();
}