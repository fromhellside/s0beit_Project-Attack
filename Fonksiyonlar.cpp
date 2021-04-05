#include "main.h"
#define INVALID -1

#define RAKNET_CLIENT_VERSION "0.3.7"
#define ran_arr_next() (*ran_arr_ptr>=0? *ran_arr_ptr++: ran_arr_cycle())
#define KK 100                     /* the int lag */
#define LL  37                     /* the short lag */
#define MM (1L<<30)                 /* the modulus */
#define mod_diff(x,y) (((x)-(y))&(MM-1)) 
#define QUALITY 1009
unsigned int ran_arr_buf[QUALITY];
#define TT  70   /* guaranteed separation between streams */
#define is_odd(x)  ((x)&1)          /* units bit of x */
unsigned int ran_arr_cycle();
unsigned int ran_x[KK];
unsigned int ran_arr_dummy = -1, ran_arr_started = -1;
unsigned int* ran_arr_ptr = &ran_arr_dummy;
unsigned int ran_arr_cycle();


unsigned int ran_arr_cycle()
{
	if (ran_arr_ptr == &ran_arr_dummy)
		ran_start(314159L); /* the user forgot to initialize */
	ran_array(ran_arr_buf, QUALITY);
	ran_arr_buf[KK] = -1;
	ran_arr_ptr = ran_arr_buf + 1;
	return ran_arr_buf[0];
}
void ran_array(unsigned int aa[], unsigned int n)
{
	register int i, j;
	for (j = 0; j < KK; ++j) aa[j] = ran_x[j] + r4nDs(1, 100000);
	for (; j < n; ++j) aa[j] = mod_diff(aa[j - KK], aa[j - LL]);
	for (i = 0; i < LL; i++, j++) ran_x[i] = mod_diff(aa[j - KK], aa[j - LL]);
	for (; i < KK; i++, j++) ran_x[i] = mod_diff(aa[j - KK], ran_x[i - LL]);
}

void ran_start(int seed)
{
	register int t, j;
	unsigned int x[KK + KK - 1];              /* the preparation buffer */
	register int ss = (seed + 2) & (MM - 2);
	for (j = 0; j < KK; j++) {
		x[j] = ss;                      /* bootstrap the buffer */
		ss <<= 1; if (ss >= MM) ss -= MM - 2; /* cyclic shift 29 bits */
	}
	x[1]++;              /* make x[1] (and only x[1]) odd */
	for (ss = seed & (MM - 1), t = TT - 1; t;) {
		for (j = KK - 1; j > 0; j--) x[j + j] = x[j], x[j + j - 1] = 0; /* "square" */
		for (j = KK + KK - 2; j >= KK; j--)
			x[j - (KK - LL)] = mod_diff(x[j - (KK - LL)], x[j]),
			x[j - KK] = mod_diff(x[j - KK], x[j]);
		if (is_odd(ss)) {              /* "multiply by z" */
			for (j = KK; j > 0; j--)  x[j] = x[j - 1];
			x[0] = x[KK];            /* shift the buffer cyclically */
			x[LL] = mod_diff(x[LL], x[KK]);
		}
		if (ss) ss >>= 1; else t--;
	}
	for (j = 0; j < LL; j++) ran_x[j + KK - LL] = x[j];
	for (; j < KK; j++) ran_x[j - LL] = x[j];
	for (j = 0; j < 10; j++) ran_array(x, KK + KK - 1); /* warm things up */
	ran_arr_ptr = &ran_arr_started;
}
float r4ndom_fl0at(float low, float high)
{
	return low + (float)(r4nDs(0, 0xFFFFFF)) / ((float)(0xFFFFFF) / (high - low));
}
double double_random(double a, double b)
{
	return a + (b - a) * rand() / (RAND_MAX + 1);
}
float random_float(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
int rand0m(int min, int max)
{
	if (min == max)
		return min;

	return min + ran_arr_cycle() % (max - min);
}
int R4nd0m(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
unsigned int r4nDs(unsigned int from, unsigned int to)
{
	if (from == 0 && to == 0)
		return 0;
	if (from == to)
		return from;
	return (ran_arr_cycle() % (to - from)) + from;
}
std::vector<int> NearPlayers(int my_playerid, float distance, bool check_streamed)
{
	std::vector<int> _Players;
	for (int playerID = 0; playerID < SAMP_MAX_PLAYERS; playerID++)
	{
		if (playerID != my_playerid)
		{
			if (!g_Players->iIsListed[playerID])
				continue;

			if (g_Players->pRemotePlayer[playerID]->iIsNPC)
				continue;

			float fPos[3];

			getPlayerPos(playerID, fPos);

			float fDistance = vect3_dist(g_Players->pLocalPlayer->onFootData.fPosition, fPos);

			if (fDistance <= distance)
			{
				_Players.push_back(playerID);
			}
		}
	}
	return _Players;
}
std::vector<int> NearVehicles(int my_playerid, float distance, bool check_streamed)
{
	std::vector<int> Vehicles;
	for (int i = 0; i < MAX_VEHICLES; i++)
	{
		if (!g_Vehicles)
			break;
		if (!g_Vehicles->iIsListed[i])
			continue;
		if (g_Vehicles->pSAMP_Vehicle[i] == NULL)
			continue;
		if (g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle == NULL)
			continue;

		if (g_Vehicles->pGTA_Vehicle[i])
		{
			float fPos[3];
			vect3_copy(&g_Vehicles->pGTA_Vehicle[i]->base.matrix[4 * 3], fPos);

			float fDistance = vect3_dist(g_Players->pLocalPlayer->onFootData.fPosition, fPos);

			if (fDistance <= distance)
			{
				Vehicles.push_back(i);
			}
		}
	}
	return Vehicles;
}
//---- SobFoX'tan alýnan kaynaklarýn baþý ----//
void qEULER(point3D Rotation, Quaternion& q)
{
	if (q.x == 0.0f && q.y == 0.0f && q.z == 0.0f && q.w == 0.0f)
		q.w = 1.0f;

	point3D T3(q.R.x - Rotation.x, q.R.y - Rotation.y, q.R.z - Rotation.z);
	Quaternion TQ = { 0.0f, 0.0f, 0.0f, 0.0f, Rotation };

	float angle;
	float sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;

	angle = T3.x * 0.5f * PI / 180.0f;
	sinPitch = sin(angle);
	cosPitch = cos(angle);

	angle = T3.y * 0.5f * PI / 180.0f;
	sinRoll = sin(angle);
	cosRoll = cos(angle);

	angle = T3.z * 0.5f * PI / 180.0f;
	sinYaw = sin(angle);
	cosYaw = cos(angle);

	float cosRollXcosPitch = cosRoll * cosPitch;
	float sinRollXsinPitch = sinRoll * sinPitch;
	float cosRollXsinPitch = cosRoll * sinPitch;
	float sinRollXcosPitch = sinRoll * cosPitch;

	TQ.w = (cosRollXcosPitch * cosYaw - sinRollXsinPitch * sinYaw);
	TQ.x = (cosRollXcosPitch * sinYaw + sinRollXsinPitch * cosYaw);
	TQ.y = (sinRollXcosPitch * cosYaw + cosRollXsinPitch * sinYaw);
	TQ.z = (cosRollXsinPitch * cosYaw - sinRollXcosPitch * sinYaw);

	float n = 1.0f / TQ.radius();

	TQ.x *= n;
	TQ.y *= n;
	TQ.z *= n;
	TQ.w *= n;

	float x = q.x * TQ.w + q.y * TQ.z - q.z * TQ.y + q.w * TQ.x;
	float y = -q.x * TQ.z + q.y * TQ.w + q.z * TQ.x + q.w * TQ.y;
	float z = q.x * TQ.y - q.y * TQ.x + q.z * TQ.w + q.w * TQ.z;

	TQ.w = -q.x * TQ.x - q.y * TQ.y - q.z * TQ.z + q.w * TQ.w;
	TQ.x = x;
	TQ.y = y;
	TQ.z = z;

	q = TQ;
}

Quaternion qRotate(float rx, float ry, float rz)
{
	rx = PI - (rx + PI);

	Quaternion q = { 0.0f, 0.0f, 0.0f, 1.0f };
	point3D R(0.0f, 0.0f, 0.0f);

	R.x = rx * 180.0f / PI;
	qEULER(R, q);

	R.y = ry * 180.0f / PI;
	qEULER(R, q);

	R.z = rz * 180.0f / PI;
	qEULER(R, q);

	return q;
}
float Get_Deg(float x, float y, float add)
{
	float deg = 0;
	if (y < 0)
		deg += atan(x / y) * 180 / PI + 180;
	else
		deg += atan(x / y) * 180 / PI;
	deg += add;
	if (deg < 0)
		deg += 360;
	if (deg > 360)
		deg -= 360;
	return deg;
}

point3D VAIM(float myPoint[3], float enemyPoint[3])
{
	point3D ret;
	float pos[3];
	pos[0] = myPoint[0] - enemyPoint[0];
	pos[1] = myPoint[1] - enemyPoint[1];
	pos[2] = myPoint[2] - enemyPoint[2];
	if (pos[0] >= 0)
		ret.x = atan(pos[1] / pos[0]) + PI;
	else
		ret.x = atan(pos[1] / pos[0]);
	if (ret.x > PI * 2)
		ret.x = 0;
	else if (ret.x < -PI * 2)
		ret.x = 0;
	ret.y = atan(pos[2] / sqrt(pos[0] * pos[0] + pos[1] * pos[1]));
	return ret;
}
//---- SobFoX'tan alýnan kaynaklarýn sonu ----//

bool ValidPlayer(int PlayerID)
{
	if (g_Players == NULL)
		return 0;

	if (PlayerID < 0 || PlayerID > SAMP_MAX_PLAYERS)
		return 0;

	if (PlayerID == g_Players->sLocalPlayerID)
		return 0;

	if (g_Players->iIsListed[PlayerID] != 1)
		return 0;

	return 1;
}

bool ActorIsVehicleDriver(actor_info* actor, vehicle_info* vehicle)
{
	if (!actor || !vehicle)
		return 0;

	if (actor->state != ACTOR_STATE_DRIVING)
		return 0;

	if (!actor->vehicle)
		return 0;

	if (actor->vehicle != vehicle)
		return 0;

	if (vehicle->passengers[0] != actor)
		return 0;

	return true;
}
int GetClosestPlayerid(actor_info* player, int flugs)
{
	//traceLastFunc("int GetClosestPlayerid(actor_info *player, int flugs)");
	int minID = INVALID;
	double minDist = 0.0f;

	for (int id = NULL; id < SAMP_MAX_PLAYERS; id++)
	{
		actor_info* actor = getGTAPedFromSAMPPlayerID(id);
		if (actor == NULL)
			continue;

		if ((flugs & ACTOR_ALIVE) && actor->hitpoints <= 0.0f)
			continue;


		if ((flugs & ACTOR_NOT_ME) && actor == player)
			continue;

		if ((flugs & ACTOR_INVEHICLE) &&
			//actor->state != ACTOR_STATE_DRIVING
			g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState != PLAYER_STATE_DRIVER
			&& g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState != PLAYER_STATE_PASSENGER)
			continue;

		if ((flugs & ACTOR_ONFOOT) &&
			g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState != PLAYER_STATE_ONFOOT)
			continue;


		if ((flugs & ACTOR_NOT_AFK) && g_Players->pRemotePlayer[id]->pPlayerData->iAFKState == 2)
			continue;


		if (flugs & ACTOR_NOT_ATTACH)
		{
			vehicle_info* myveh = (VEHICLE_SELF, NULL);
			//g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_ONFOOT // control fix
			if (myveh && g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_ONFOOT &&
				getSAMPVehicleIDFromGTAVehicle(myveh) == g_Players->pRemotePlayer[id]->pPlayerData->onFootData.sSurfingVehicleID)
				continue;
		}

		if (flugs & ACTOR_NOT_IN_MY_CAR)
		{
			vehicle_info* myveh = vehicle_info_get(VEHICLE_SELF, NULL);
			if (player->state == ACTOR_STATE_DRIVING &&
				(g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER ||
					g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER) && myveh && myveh == actor->vehicle)
				continue;
		}

		double dist = 0;

		dist = vect3_dist(&actor->base.matrix[4 * 3], &player->base.matrix[4 * 3]);


		//if (!dist) return INVALID;

		if (minID == INVALID)
		{
			minID = id;
			minDist = dist;
		}
		else
		{
			if (dist < minDist)
			{
				minID = id;
				minDist = dist;
			}
		}

	}
	return minID;
}

int cheack_valid_weaponid(int weaponid)
{
	if (weaponid == 0 || weaponid == 1 || weaponid == 2
		|| weaponid == 3 || weaponid == 4 || weaponid == 5
		|| weaponid == 6 || weaponid == 7 || weaponid == 8
		|| weaponid == 9 || weaponid == 10 || weaponid == 11
		|| weaponid == 12 || weaponid == 13 || weaponid == 14
		|| weaponid == 15 || weaponid == 16 || weaponid == 17
		|| weaponid == 18 || weaponid == 35 || weaponid == 36
		|| weaponid == 37 || weaponid == 39 || weaponid == 40
		|| weaponid == 41 || weaponid == 42 || weaponid == 43
		|| weaponid == 44 || weaponid == 45 || weaponid == 46)
	{
		return 0;
	}
}

DWORD rainbow()
{

	static float x = 0, y = 0;
	static float r = 0, g = 0, b = 0;

	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	}
	else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	}
	else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	}
	else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	}
	else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	}
	else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}
	// ini set.rainbowdelay
	x += set.rainbowdelay;//SECOND: 0.450f First:0.0100f; //
	if (x >= 255.0f)
		x = 0.0f;

	y += set.rainbowdelay;//0.0100f; //increase this value to switch colors faster
	if (y > 1530.0f)
		y = 0.0f;


	return D3DCOLOR_ARGB(255, (int)r, (int)g, (int)b);
}


vehicle_info* GetVehicleInfoStandart(DWORD using_config_flags, DWORD force_add_flags)
{
	DWORD result_flags = force_add_flags;


	if (using_config_flags & VEHICLE_NO_BE_PROTECT)
		result_flags |= VEHICLE_NO_BE_PROTECT;

	if (using_config_flags & VEHICLE_NOT_FRIEND)
		result_flags |= VEHICLE_NOT_FRIEND;

	if (using_config_flags & VEHICLE_NOT_CLOSED)
		result_flags |= VEHICLE_NOT_CLOSED;


	return GetVehicleInfoForceFlags(result_flags);
}
vehicle_info* GetVehicleInfoForceFlags(DWORD flags)
{
	traceLastFunc("GetVehicleInfo()");

	actor_info* actor = actor_info_get(ACTOR_SELF, NULL);

	if (!actor)
		return NULL;


	vehicle_info* ret = NULL;

	bool nullid = (flags & VEHICLE_NEXT) != 0;


	static WORD NextVehID;
search_againt:

	for (int id = (nullid) ? NextVehID : NULL; id < SAMP_MAX_VEHICLES; id++)
	{
		vehicle_info* vehicle = getGTAVehicleFromSAMPVehicleID(id);

		if (vehicle == NULL)
			continue;

		if ((flags & VEHICLE_ALIVE) && (vehicle->hitpoints < 100.0f))
			continue;

		if ((flags & VEHICLE_NOT_MY) && (vehicle_info_get(VEHICLE_SELF, NULL) == vehicle))
			continue;

		if ((flags & VEHICLE_NOT_OCCUPIED) && vehicle->passengers && *vehicle->passengers)
			continue;


		if (flags & VEHICLE_NO_BE_PROTECT)
		{
			actor_info* driver = vehicle->passengers[0];
			if (driver && driver->state == ACTOR_STATE_DRIVING)
			{
				int id = getSAMPPlayerIDFromGTAPed(driver);

			}
		}

		if (flags & VEHICLE_FOR_FLY)
		{
			const vehicle_entry* model = gta_vehicle_get_by_id(vehicle->base.model_alt_id);
			if (!model)
				continue;

			switch (model->class_id)
			{
			case VEHICLE_CLASS_HELI:
			case VEHICLE_CLASS_AIRPLANE:
			case VEHICLE_CLASS_BOAT:
			case VEHICLE_CLASS_MINI:
			case VEHICLE_CLASS_TRAILER:
				continue;
			default:
				break;
			}
		}


		if (flags & VEHICLE_NOT_BOATS)
		{
			const vehicle_entry* model = gta_vehicle_get_by_id(vehicle->base.model_alt_id);
			if (!model)
				continue;

			if (model->class_id == VEHICLE_CLASS_BOAT)
				continue;
		}

		if (flags & VEHICLE_NOT_TRAIN)
		{
			switch (vehicle->base.model_alt_id)
			{
			case 449:
			case 537:
			case 538:
			case 569:
			case 570:
			case 590:
				continue;
			}
		}

		if (flags & VEHICLE_NOT_FRIEND)
		{
			actor_info* driver = vehicle->passengers[0];
			if (driver && driver->state == ACTOR_STATE_DRIVING)
			{
				int id = getSAMPPlayerIDFromGTAPed(driver);

				continue;
			}
		}



		if (flags & VEHICLE_CARS_ONLY)
		{
			eClientVehicleType vehicleType = GetVehicleType(vehicle->base.model_alt_id);
			if (vehicleType != CLIENTVEHICLE_CAR)
				continue;
		}



		if (flags & VEHICLE_PLANES_ONLY)
		{
			if (vehicle->base.model_alt_id != 513)
				continue;
		}


		if (flags & VEHICLE_CLOSEST)
		{
			if (ret == NULL)
			{
				ret = vehicle;
				continue;
			}
			else if (vect3_dist(&actor->base.matrix[12], &vehicle->base.matrix[12]) < vect3_dist(&actor->base.matrix[12], &ret->base.matrix[12]))
				ret = vehicle;
		}
		else
		{
			if (flags & VEHICLE_NEXT)
				NextVehID = id + 1;


			traceLastFunc("GetVehicleInfo()");
			return vehicle;
		}
	}


	if (nullid)
	{
		nullid = false;
		goto search_againt;
	}


	traceLastFunc("GetVehicleInfo()");
	return ret;
}
int GetActorFlag(bool alive, bool incar, bool onfoot, bool ignore_myself, bool not_in_my_car, bool not_afk, bool no_attach, bool not_friend)
{
	int flag = 0;


	if (alive)
		flag |= ACTOR_ALIVE;

	if (incar)
		flag |= ACTOR_INVEHICLE;

	if (onfoot)
		flag |= ACTOR_ONFOOT;

	if (ignore_myself)
		flag |= ACTOR_NOT_ME;

	if (not_in_my_car)
		flag |= ACTOR_NOT_IN_MY_CAR;

	if (not_afk)
		flag |= ACTOR_NOT_AFK;

	if (no_attach)
		flag |= ACTOR_NOT_ATTACH;

	if (not_friend)
		flag |= ACTOR_NOT_FRIEND;

	return flag;
}

void SetActorZAngle(actor_info* actor, float ang, bool Invert)
{
	actor->fCurrentRotation = -ang;

	actor->base.matrix[4 * 0 + 0] = cosf(ang) * ((Invert) ? -1 : 1);
	actor->base.matrix[4 * 0 + 1] = -sinf(ang) * ((Invert) ? -1 : 1);
	actor->base.matrix[4 * 0 + 2] = 0.0f;
	actor->base.matrix[4 * 1 + 0] = sinf(ang);
	actor->base.matrix[4 * 1 + 1] = cosf(ang);
	actor->base.matrix[4 * 1 + 2] = 0.0f;
}
bool ValidVehicle(int VehicleID)
{
	if (g_Vehicles->iIsListed[VehicleID] != 1)
		return 0;

	if (g_Vehicles->pSAMP_Vehicle[VehicleID] == NULL)
		return 0;

	if (g_Vehicles->pSAMP_Vehicle[VehicleID]->pGTA_Vehicle == NULL)
		return 0;

	return 1;
}

void BIG_NUM_MUL(unsigned long in[5], unsigned long out[6], unsigned long factor)
{
	unsigned long src[5] = { 0 };
	for (int i = 0; i < 5; i++)
		src[i] = ((in[4 - i] >> 24) | ((in[4 - i] << 8) & 0x00FF0000) | ((in[4 - i] >> 8) & 0x0000FF00) | (in[4 - i] << 24));

	unsigned long long tmp = 0;

	tmp = unsigned long long(src[0]) * unsigned long long(factor);
	out[0] = tmp & 0xFFFFFFFF;
	out[1] = tmp >> 32;
	tmp = unsigned long long(src[1]) * unsigned long long(factor) + unsigned long long(out[1]);
	out[1] = tmp & 0xFFFFFFFF;
	out[2] = tmp >> 32;
	tmp = unsigned long long(src[2]) * unsigned long long(factor) + unsigned long long(out[2]);
	out[2] = tmp & 0xFFFFFFFF;
	out[3] = tmp >> 32;
	tmp = unsigned long long(src[3]) * unsigned long long(factor) + unsigned long long(out[3]);
	out[3] = tmp & 0xFFFFFFFF;
	out[4] = tmp >> 32;
	tmp = unsigned long long(src[4]) * unsigned long long(factor) + unsigned long long(out[4]);
	out[4] = tmp & 0xFFFFFFFF;
	out[5] = tmp >> 32;

	for (int i = 0; i < 12; i++)
	{
		unsigned char temp = ((unsigned char*)out)[i];
		((unsigned char*)out)[i] = ((unsigned char*)out)[23 - i];
		((unsigned char*)out)[23 - i] = temp;
	}
}
int gen_gpci(char buf[64], unsigned long factor) /* by bartekdvd */
{
	unsigned char out[6 * 4] = { 0 };

	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < 6 * 4; ++i)
		out[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	out[6 * 4] = 0;

	BIG_NUM_MUL((unsigned long*)out, (unsigned long*)out, factor);

	unsigned int notzero = 0;
	buf[0] = '0'; buf[1] = '\0';

	if (factor == 0) return 1;

	int pos = 0;
	for (int i = 0; i < 24; i++)
	{
		unsigned char tmp = out[i] >> 4;
		unsigned char tmp2 = out[i] & 0x0F;

		if (notzero || tmp)
		{
			buf[pos++] = (char)((tmp > 9) ? (tmp + 55) : (tmp + 48));
			if (!notzero) notzero = 1;
		}

		if (notzero || tmp2)
		{
			buf[pos++] = (char)((tmp2 > 9) ? (tmp2 + 55) : (tmp2 + 48));
			if (!notzero) notzero = 1;
		}
	}
	buf[pos] = 0;

	return pos;
}

void SetQuaMatrix(_MATRIX4X4* matrix, Quaternion* quaternion)
{
	MatrixToQuaternion(&matrix->right, &matrix->up, &matrix->at, quaternion->w, quaternion->x, quaternion->y, quaternion->z);
}

void MatrixToQuaternion(VECTOR* right, VECTOR* up, VECTOR* at, float& quaterW, float& quaterX, float& quaterY, float& quaterZ) // IDA POWA !
{
	long double v13; // st7@1
	long double v14; // st7@3
	long double v15; // st5@5
	float v16; // st6@5
	float v17; // st7@5
	long double v18; // st6@7
	int result = 0; // eax@17
	float v20; // ST28_8@17
	float v21; // ST10_8@17
	float v22; // st7@17
	float v23; // [sp+10h] [bp-20h]@7
	float v24; // [sp+18h] [bp-18h]@9
	float v25; // [sp+20h] [bp-10h]@3

	v13 = right->X + up->Y + at->Z + 1.0f;
	if (v13 < 0.0f)
		v13 = 0.0f;
	v25 = (float)sqrt(v13) * 0.5f;
	v14 = right->X + 1.0 - up->Y - at->Z;
	if (v14 < 0.0f)
		v14 = 0.0f;
	v17 = (float)sqrt(v14) * 0.5f;
	v16 = 1.0f - right->X;
	v15 = up->Y + v16 - at->Z;
	if (v15 < 0.0f)
		v15 = 0.0f;
	v23 = (float)sqrt(v15) * 0.5f;
	v18 = v16 - up->Y + at->Z;
	if (v18 < 0.0f)
		v18 = 0.0f;
	v24 = (float)sqrt(v18) * 0.5f;
	if (v25 < 0.0f)
		v25 = 0.0f;
	if (v17 < 0.0f)
		v17 = 0.0f;
	if (v23 < 0.0f)
		v23 = 0.0f;
	if (v24 < 0.0f)
		v24 = 0.0f;
	v20 = (float)_copysign(v17, at->Y - up->Z);
	v21 = (float)_copysign(v23, right->Z - at->X);
	v22 = (float)_copysign(v24, up->X - right->Y);
	quaterW = v25;
	quaterX = v20;
	quaterY = v21;
	quaterZ = v22;
}
bool IsPlayerConnected(uint16_t playerID)
{
	if (playerID == g_Players->sLocalPlayerID)
		return false;
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	return true;
}
bool IsPlayerConnectedTEST(uint16_t playerID)
{
	if (playerID == g_Players->sLocalPlayerID)
		return false;
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
		return false;
	return true;
}
bool IsPlayerStreamed(uint16_t playerID) // This is mine, it's a nice one. ~ RapidFire
{
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
		return false;
	if (cheat_state->filters.bIgnoreAFKs && g_Players->pRemotePlayer[playerID]->pPlayerData->iAFKState == 2)
		return false;
	if (cheat_state->filters.bIgnoreDEADs && g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->hitpoints == 0)
		return false;
	if (cheat_state->filters.bIgnoreSameColor && samp_color_get(playerID) == samp_color_get(g_Players->sLocalPlayerID))
		return false;
	if (cheat_state->filters.bIgnoreSameSkinID && g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.model_alt_id == g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.model_alt_id)
		return false;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
	if (cheat_state->filters.bIgnoreSameTeam && g_Players->pLocalPlayer->byteTeamID2 == g_Players->pRemotePlayer[playerID]->pPlayerData->byteTeamID)
#else
	if (cheat_state->filters.bIgnoreSameTeam && g_Players->pLocalPlayer->byteTeamID == g_Players->pRemotePlayer[playerID]->pPlayerData->byteTeamID)
#endif
		return false;
#if COMPILE_TYPE == COMPILE_TYPE_TURKISH_THELIFE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_HELLSIDE_VERSION || COMPILE_TYPE == COMPILE_TYPE_TURKISH_RAPIDFIRE_VERSION
	if (cheat_state->filters.bIgnoreProjectUsers)
	{
	if (cheat_state->PrivateControlPanel.ControlProjectUser[playerID].have_projectattack)
		return false;
	}
#endif
	if (cheat_state->filters.bIgnoreMyFriends && g_NewModSa->bOyuncuArkadas[playerID])
		return false;
	return true;
}
//bool IsPlayerStreamed(uint16_t playerID)
//{
//	if (g_Players == NULL)
//		return false;
//	if (g_Players->iIsListed[playerID] != 1)
//		return false;
//	if (g_Players->pRemotePlayer[playerID] == NULL)
//		return false;
//	if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
//		return false;
//	if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
//		return false;
//	return true;
//}

/*
Lenard bugün saat 11:34
Silent aimde hedefteki kiþiyi kutucuða alma fonksiyonunun renkleri parlaklýðý arttýrýlabilir

huso bugün saat 11:34
kýsa yolla kutu içerisindeki adamý dost ekleyebiliriz

azimabi bugün saat 11:36
AFK þeyi yanýp sönmesin sürekli kýrmýzý beyaz duruyo göz alýo

RapidFire bugün saat 11:36
Bahsettiðin þey, çizgi kalýnlýðý ve tonlamasý mý?

Lenard bugün saat 11:37
evet

dezwend bugün saat 12:03
reconnect function gelebilir


benberk bugün saat 12:45
Çoðu ayarda ini üzerinden config olmasý gerekiyor.
Bunun ilk baþýnda silent var, her oyuna girdiðimde silenti ayarlamaktan
çok ini dosyasýna bir kez yapýp ikinciye yapmamýza gerek kalmasýn.

RapidFire bugün saat 12:48
Dost, ölü hedef, afk, renk, skin, takým, admin filtrelerinden mi bahsediyorsun?

benberk bugün saat 12:50
Evet

*/


int GetAimingPlayer(bool bFromWhenPress)
{
	static int NearestCenterPlayerID = -1;
	float fNearestDistanceScreen = -1;
	float DistPlayerScreen[2];
	if ((!g_Players->pLocalPlayer->onFootData.stSampKeys.keys_primaryFire && bFromWhenPress)
		|| cheat_state->state != CHEAT_STATE_ACTOR
		|| g_NewModSa->iAimPlayerID == -1)
	{
		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (i == g_Players->sLocalPlayerID)
				continue;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
				if (g_BotFuncs->uiIsBot[i][0] == 1)
					continue;
#endif

			actor_info* player = getGTAPedFromSAMPPlayerID(i);
			if (!player)
				continue;

			CPed* pPed = pGameInterface->GetPools()->GetPed((DWORD*)player);
			if (!pPed)
				continue;

			CVector pSpinePos;
			D3DXVECTOR3 player_pos, player_pos_on_screen;
			pPed->GetBonePosition(BONE_SPINE1, &pSpinePos);

			player_pos.x = CVecToD3DXVEC(pSpinePos).x;
			player_pos.y = CVecToD3DXVEC(pSpinePos).y;
			player_pos.z = CVecToD3DXVEC(pSpinePos).z;
			CalcScreenCoors(&player_pos, &player_pos_on_screen);

			if (player_pos_on_screen.z < 1.f)
				continue;


			DistPlayerScreen[0] = abs((g_NewModSa->fViewFinderPosition[0]) - (player_pos_on_screen.x));
			DistPlayerScreen[1] = abs((g_NewModSa->fViewFinderPosition[1]) - (player_pos_on_screen.y));

			float fCurrentDistanceScreen = sqrtf((DistPlayerScreen[0] * DistPlayerScreen[0]) + (DistPlayerScreen[1] * DistPlayerScreen[1]));

			float fDistanceFromEnemy = vect3_dist(&g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
				&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);

			if (!set.silentAim.bOutOfRange)
			{
				if (fDistanceFromEnemy > fWeaponRange[g_Players->pLocalPlayer->byteCurrentWeapon])
					continue;
			}
			
			if (fNearestDistanceScreen == -1)
			{
				fNearestDistanceScreen = fCurrentDistanceScreen;
			}

			bool IsPlayerAfk = g_Players->pRemotePlayer[i]->pPlayerData->iAFKState == 2;

			// get the camera
			CCamera* pCamera = pGame->GetCamera();

			// grab the active cam
			CCamSAInterface* pCam = (CCamSAInterface*)((CCamSA*)pCamera->GetCam(pCamera->GetActiveCam()))->GetInterface();
			CVector src = pCam->Source;

			bool IsPlayerVisible = pGame->GetWorld()->IsLineOfSightClear(&src, &pSpinePos, true, false, false, true, true, false, false);

			if (fCurrentDistanceScreen <= fNearestDistanceScreen)
			{
				fNearestDistanceScreen = fCurrentDistanceScreen;
				if (cheat_state->Silent.bSilent)
				{
					if (!(g_NewModSa->bOyuncuArkadas[i] && set.silentAim.bFriendFilter)
						&& !(g_NewModSa->bOyuncuAdmin[i] && set.silentAim.bAdminFilter)
						&& !(set.silentAim.bTeamFilter && (g_Players->pRemotePlayer[i]->pPlayerData->byteTeamID == g_Players->pLocalPlayer->byteTeamID2))
						&& !(set.silentAim.bColorFilter && (samp_color_get(i) == samp_color_get(g_Players->sLocalPlayerID)))
						&& !(set.silentAim.bSkinFilter && (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.model_alt_id == g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.model_alt_id))
						&& !(set.silentAim.bAFKFilter && IsPlayerAfk)
						&& !((set.silentAim.bVisibleFilter && !cheat_state->Silah.iShooting_Through_Walls) && !IsPlayerVisible)
						&& !(set.silentAim.bAliveFilter && g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->hitpoints == 0))
					{
						NearestCenterPlayerID = i;
						g_NewModSa->fPosAimPlayerID[0] = player_pos_on_screen.x;
						g_NewModSa->fPosAimPlayerID[1] = player_pos_on_screen.y;
					}
					else
						continue;
				}
				else
				{
					NearestCenterPlayerID = i;
					g_NewModSa->fPosAimPlayerID[0] = player_pos_on_screen.x;
					g_NewModSa->fPosAimPlayerID[1] = player_pos_on_screen.y;
				}
			}
		}
	}
	else
	{
		if (g_NewModSa->iAimPlayerID != INVALID)
		{
			if (IsPlayerStreamed(g_NewModSa->iAimPlayerID))
			{
				actor_info* player = getGTAPedFromSAMPPlayerID(g_NewModSa->iAimPlayerID);
				if (!player)
					return -1;

				CPed* pPed = pGameInterface->GetPools()->GetPed((DWORD*)player);
				if (!pPed)
					return -1;

				//CVector pos = *pPed->GetPosition();
				CVector pSpinePos;
				D3DXVECTOR3 player_pos, player_pos_on_screen;
				pPed->GetBonePosition(BONE_SPINE1, &pSpinePos);
				player_pos.x = CVecToD3DXVEC(pSpinePos).x;
				player_pos.y = CVecToD3DXVEC(pSpinePos).y;
				player_pos.z = CVecToD3DXVEC(pSpinePos).z;
				CalcScreenCoors(&player_pos, &player_pos_on_screen);

				if (player_pos_on_screen.z < 1.f)
					return -1;
				float fDistanceFromEnemy = vect3_dist(&g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					&g_Players->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12]);
				/*if (cheat_state->Silah.iSAim_Alive)
				{
					if (ACTOR_IS_DEAD(player) || g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->hitpoints == 0)
						return -1;
				}*/
				if (!set.silentAim.bOutOfRange)
				{
					if (fDistanceFromEnemy > fWeaponRange[g_Players->pLocalPlayer->byteCurrentWeapon])
						return -1;
				}
				if (set.silentAim.bVisibleFilter)
				{
					// get the camera
					CCamera* pCamera = pGame->GetCamera();
					// grab the active cam
					CCamSAInterface* pCam = (CCamSAInterface*)((CCamSA*)pCamera->GetCam(pCamera->GetActiveCam()))->GetInterface();
					CVector src = pCam->Source;
					bool IsPlayerVisible = pGame->GetWorld()->IsLineOfSightClear(&src, &pSpinePos, true, false, false, true, true, false, false);
					if (!IsPlayerVisible)
						return -1;
				}
				g_NewModSa->fPosAimPlayerID[0] = player_pos_on_screen.x;
				g_NewModSa->fPosAimPlayerID[1] = player_pos_on_screen.y;
			}
		}
	}
	if (cheat_state->Silent.bSilent)
	{
		if (g_NewModSa->iAimPlayerID != -1)
		{
			if (IsPlayerStreamed(g_NewModSa->iAimPlayerID))
			{
				float fTargetPos[3];
				vect3_copy(&g_Players->pRemotePlayer[g_NewModSa->iAimPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12], fTargetPos);
				if (g_Players->pLocalPlayer->byteCurrentWeapon != 34)
				{
					g_NewModSa->fViewFinderPosition[0] = (float)pPresentParam.BackBufferWidth * 0.5299999714f;
					g_NewModSa->fViewFinderPosition[1] = (float)pPresentParam.BackBufferHeight * 0.4f;
				}
				else
				{
					g_NewModSa->fViewFinderPosition[0] = (float)pPresentParam.BackBufferWidth / 2.f;
					g_NewModSa->fViewFinderPosition[1] = (float)pPresentParam.BackBufferHeight / 2.f;
				}
//#define TARGET_TYPE_BOX 0
//#define TARGET_TYPE_CIRCLE 1
//#define TARGET_TYPE_TEXT 2
//#define TARGET_TYPE_NONE 3
//				switch (set.silentAim.targetType)
//				{
//				case TARGET_TYPE_BOX:
//					render->D3DBoxBorder(player_pos_on_screen.x, player_pos_on_screen.y, 10.0f, 10.0f, D3DCOLOR_XRGB(255, 255, 0), D3DCOLOR_ARGB(255, 255, 0, 0));
//					break;
//				case TARGET_TYPE_CIRCLE:
//					Draw2DCircle(player_pos_on_screen.x, player_pos_on_screen.y, set.silentAim.fCircleRadius, samp_color_get(g_NewModSa->iAimPlayerID));
//					break;
//				case TARGET_TYPE_TEXT:
//					Render3DTextLabel("Hedef Oyuncu", fTargetPos, samp_color_get(g_NewModSa->iAimPlayerID));
//					break;
//				case TARGET_TYPE_NONE:
//					break;
//				}
#define TARGET_TYPE_TEXT 0
#define TARGET_TYPE_NONE 1
				switch (set.silentAim.targetType)
				{
				case TARGET_TYPE_TEXT:
					Render3DTextLabel("Hedef Oyuncu", fTargetPos, samp_color_get(g_NewModSa->iAimPlayerID));
					break;
				case TARGET_TYPE_NONE:
					break;
				}
			}
		}
	}
	return NearestCenterPlayerID;
}

void OL_CalculateLagPosition(int playerID, float fPos[3])
{
	//traceLastFunc("OL_CalculateLagPosition");
	//static DWORD dwUpdateScoreboardTick = GetTickCount() + 3000;
	int iPlayerTickRate = EnemyStats[playerID].iPlayerOnFootTick[LastTick::LAST] - EnemyStats[playerID].iPlayerOnFootTick[LastTick::SECOND_LAST];
	int iServerTickRate = *(DWORD*)(g_dwSAMP_Addr + SAMP_ONFOOTSENDRATE);
	int iTickGap = abs(iServerTickRate - iPlayerTickRate);
	float fInitialSpeed[3];
	OL_CalculateSpeed(playerID, fInitialSpeed);

	vect3_copy(EnemyStats[playerID].fPlayerPos[LastTick::LAST], fPos);
	int iDLocalTick = GetTickCount() - EnemyStats[playerID].iPlayerOnFootTick[LastTick::LAST];

	updateScoreboardData();

	// 1.4 is the ratio of ping from samp browser, and ping from scoreboard
	int iPing = (g_Players->iLocalPlayerPing + g_Players->pRemotePlayer[playerID]->iPing) / 1.4f;

	fPos[0] += fInitialSpeed[0] * (float)(iTickGap + iDLocalTick + iPing);
	fPos[1] += fInitialSpeed[1] * (float)(iTickGap + iDLocalTick + iPing);
	fPos[2] += fInitialSpeed[2] * (float)(iTickGap + iDLocalTick + iPing);

	D3DXVECTOR3 vPos, vPosScreen;
	vPos.x = fPos[0];
	vPos.y = fPos[1];
	vPos.z = fPos[2];
	CalcScreenCoors(&vPos, &vPosScreen);
}

void OL_CalculateSpeed(int playerID, float fSpeed[3])
{
	int iServerTickRate = *(DWORD*)(g_dwSAMP_Addr + SAMP_ONFOOTSENDRATE);
	float fDPos[3];
	fDPos[0] = EnemyStats[playerID].fPlayerPos[LastTick::LAST][0] - EnemyStats[playerID].fPlayerPos[LastTick::SECOND_LAST][0];
	fDPos[1] = EnemyStats[playerID].fPlayerPos[LastTick::LAST][1] - EnemyStats[playerID].fPlayerPos[LastTick::SECOND_LAST][1];
	fDPos[2] = EnemyStats[playerID].fPlayerPos[LastTick::LAST][2] - EnemyStats[playerID].fPlayerPos[LastTick::SECOND_LAST][2];

	fSpeed[0] = fDPos[0] / (float)iServerTickRate;
	fSpeed[1] = fDPos[1] / (float)iServerTickRate;
	fSpeed[2] = fDPos[2] / (float)iServerTickRate;

	//cheat_state_text("%d %f, %f", playerID, fDPos[0], fSpeed[0]);

}



float fWeaponDamage[55] =
{
	1.0, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	0.0, // 21
	8.25, // 22 - Colt 45
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
	49.5,//3.3, // 25 - Shotgun
	49.5,//3.3, // 26 - Sawed-off
	39.6,//4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.9, // 30 - AK47
	9.9, // 31 - M4
	6.6, // 32 - Tec9
	24.75, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
	9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0 // 54 - Splat
};

// from https://github.com/oscar-broman/samp-weapon-config/blob/master/weapon-config.inc
float fWeaponRange[39] = {
	0.0, // 0 - Fist
	0.0, // 1 - Brass knuckles
	0.0, // 2 - Golf club
	0.0, // 3 - Nitestick
	0.0, // 4 - Knife
	0.0, // 5 - Bat
	0.0, // 6 - Shovel
	0.0, // 7 - Pool cue
	0.0, // 8 - Katana
	0.0, // 9 - Chainsaw
	0.0, // 10 - Dildo
	0.0, // 11 - Dildo 2
	0.0, // 12 - Vibrator
	0.0, // 13 - Vibrator 2
	0.0, // 14 - Flowers
	0.0, // 15 - Cane
	0.0, // 16 - Grenade
	0.0, // 17 - Teargas
	0.0, // 18 - Molotov
	90.0, // 19 - Vehicle M4 (custom)
	75.0, // 20 - Vehicle minigun (custom)
	0.0, // 21
	35.0, // 22 - Colt 45
	35.0, // 23 - Silenced
	35.0, // 24 - Deagle
	40.0, // 25 - Shotgun
	35.0, // 26 - Sawed-off
	40.0, // 27 - Spas
	35.0, // 28 - UZI
	45.0, // 29 - MP5
	70.0, // 30 - AK47
	90.0, // 31 - M4
	35.0, // 32 - Tec9
	100.0, // 33 - Cuntgun
	320.0, // 34 - Sniper
	0.0, // 35 - Rocket launcher
	0.0, // 36 - Heatseeker
	0.0, // 37 - Flamethrower
	75.0  // 38 - Minigun
};

struct stEnemyStats EnemyStats[SAMP_MAX_PLAYERS];
byte GetPlayerAlpha(int playerid)
{

	actor_info* my_actor = actor_info_get(ACTOR_SELF, NULL);
	actor_info* player_info = getGTAPedFromSAMPPlayerID(playerid);


	int alpha = 0xFF;

	if (player_info)
	{
		float dist = vect3_dist(&my_actor->base.matrix[12], &player_info->base.matrix[12]);


		const float min_dist = 10.0f;
		const float max_dist = 600.0f; // Ýþin özünde 300.0f

		const int min_alpha = 0x40;
		const int max_alpha = 0x255;

		if (dist < min_dist)
			dist = min_dist;

		if (dist > max_dist)
			dist = max_dist;

		alpha = 255.0f * (1 - (dist - min_dist) / max_dist);


		if (alpha < min_alpha)
			alpha = min_alpha;

		if (alpha > max_alpha)
			alpha = max_alpha;

		if (g_Players->pRemotePlayer[playerid]->pPlayerData->iAFKState == 2)
			alpha /= 2;

		return alpha;

	}
	else
		return alpha / 4;
}
void SetColorAlpha(D3DCOLOR& color, byte alpha)
{
	//D3DCOLOR dw_alpha = alpha;
	color <<= 8; //0xAARRGGBB
	color >>= 8;
	color += alpha << 3 * 8;
	//AddMessageToGoCChat("alpha: %2i color 0x%p", dw_alpha, color);

}
bool IsVehicleStreamed(uint16_t vehicleID)
{
	//if (g_Players->pLocalPlayer->sCurrentVehicleID == OLCheats->iVehicleID) { continue; }
	if (g_Vehicles->iIsListed[vehicleID] != 1)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID] == NULL)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID]->pGTA_Vehicle == NULL)
		return false;
	return true;
}

void SetVehicleZAngle(vehicle_info* vehicle, float ang, bool Invert)
{
	int invert_car = (Invert) ? -1 : 1;
	vehicle->base.matrix[4 * 0 + 0] = invert_car * cosf(ang);
	vehicle->base.matrix[4 * 0 + 1] = invert_car * (-1) * sinf(ang);
	vehicle->base.matrix[4 * 0 + 2] = 0.0f;
	vehicle->base.matrix[4 * 1 + 0] = sinf(ang);
	vehicle->base.matrix[4 * 1 + 1] = cosf(ang);
	vehicle->base.matrix[4 * 1 + 2] = 0.0f;
}

void KomutYaz(const char* szMessage, ...)
{
	va_list ap;
	char BotYazi[50];

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
		/* - DarkNeX */
		int len = strlen(string);

		RakNet::BitStream Params;

		Params.Write(len); // see? now it takes int variable
		Params.Write(string, len);

		g_RakClient->RPC(RPC_ServerCommand, &Params, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false);
	}
}
int iGetAimingVehicle()
{
	static int NearestCenterVehicleID = -1;
	float NearestDistance = -1;
	float DistPlayerScreen[2];
	D3DXVECTOR3 vehicle_pos, vehicle_pos_on_screen;
	CVehicle* pVehicle = NULL;
	CVector vecVehiclepos;
	for (int vehicleID = 0; vehicleID <= SAMP_MAX_VEHICLES; vehicleID++)
	{
		if (g_Vehicles->iIsListed[vehicleID] != 1)
			continue;
		if (g_Vehicles->pSAMP_Vehicle[vehicleID] == NULL)
			continue;
		if (g_Vehicles->pSAMP_Vehicle[vehicleID]->pGTA_Vehicle == NULL)
			continue;


		pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD*)g_Vehicles->pSAMP_Vehicle[vehicleID]->pGTA_Vehicle);
		if (isBadPtr_GTA_pVehicle(pVehicle))
			continue;

		vecVehiclepos = pVehicle->GetInterface()->Placeable.matrix->vPos;
		vehicle_pos.x = vecVehiclepos.fX;
		vehicle_pos.y = vecVehiclepos.fY;
		vehicle_pos.z = vecVehiclepos.fZ;
		CalcScreenCoors(&vehicle_pos, &vehicle_pos_on_screen);

		if (vehicle_pos_on_screen.z < 1.f)
			continue;
		vecVehiclepos.fX = vehicle_pos_on_screen.x;
		vecVehiclepos.fY = vehicle_pos_on_screen.y;

		if (vehicleID != g_Players->pLocalPlayer->sCurrentVehicleID)
		{
			DistPlayerScreen[0] = abs((g_NewModSa->fViewFinderPosition[0]) - (vehicle_pos_on_screen.x));
			DistPlayerScreen[1] = abs((g_NewModSa->fViewFinderPosition[1]) - (vehicle_pos_on_screen.y));
			float CurrentDistance = sqrtf((DistPlayerScreen[0] * DistPlayerScreen[0]) + (DistPlayerScreen[1] * DistPlayerScreen[1]));

			if (NearestDistance == -1)
			{
				NearestDistance = CurrentDistance;
			}

			if (CurrentDistance <= NearestDistance)
			{
				NearestDistance = CurrentDistance;
				NearestCenterVehicleID = vehicleID;
			}
		}
	}
	return NearestCenterVehicleID;
}
void sendPacket(RakNet::BitStream* bsParams)
{
	g_RakClient->Send(bsParams, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}
void MatrixToQuaternion2(tVector* right, tVector* up, tVector* at, float& quaterW, float& quaterX, float& quaterY, float& quaterZ) // IDA POWA !
{
	long double v13; // st7@1
	long double v14; // st7@3
	long double v15; // st5@5
	float v16; // st6@5
	float v17; // st7@5
	long double v18; // st6@7
	int result = 0; // eax@17
	float v20; // ST28_8@17
	float v21; // ST10_8@17
	float v22; // st7@17
	float v23; // [sp+10h] [bp-20h]@7
	float v24; // [sp+18h] [bp-18h]@9
	float v25; // [sp+20h] [bp-10h]@3

	v13 = right->X + up->Y + at->Z + 1.0f;
	if (v13 < 0.0f)
		v13 = 0.0f;
	v25 = (float)sqrt(v13) * 0.5f;
	v14 = right->X + 1.0 - up->Y - at->Z;
	if (v14 < 0.0f)
		v14 = 0.0f;
	v17 = (float)sqrt(v14) * 0.5f;
	v16 = 1.0f - right->X;
	v15 = up->Y + v16 - at->Z;
	if (v15 < 0.0f)
		v15 = 0.0f;
	v23 = (float)sqrt(v15) * 0.5f;
	v18 = v16 - up->Y + at->Z;
	if (v18 < 0.0f)
		v18 = 0.0f;
	v24 = (float)sqrt(v18) * 0.5f;
	if (v25 < 0.0f)
		v25 = 0.0f;
	if (v17 < 0.0f)
		v17 = 0.0f;
	if (v23 < 0.0f)
		v23 = 0.0f;
	if (v24 < 0.0f)
		v24 = 0.0f;
	v20 = (float)_copysign(v17, at->Y - up->Z);
	v21 = (float)_copysign(v23, right->Z - at->X);
	v22 = (float)_copysign(v24, up->X - right->Y);
	quaterW = v25;
	quaterX = v20;
	quaterY = v21;
	quaterZ = v22;
}
float MagnetForce(float pos, float radius, float power, float mass)
{
	/*if ( radius < 20.0f )
	{
	radius = pow(radius, 0.8f);
	radius *= 20.0f;
	}

	return ((pos * power) / mass) / radius;*/
	return (pos / radius) * (power / 1700.0f);
}

int FindNearestSAMPPlayer(bool bCheckIfIsPlayerDead, float fDistance)
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (g_Players->iIsListed[i] != 1)
			continue;
		if (g_Players->pRemotePlayer[i] == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			continue;

		struct actor_info* ainfo = g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if (vect3_dist(&ainfo->base.matrix[4 * 3], &self->base.matrix[4 * 3]) > fDistance)
			continue;

		if (bCheckIfIsPlayerDead)
		{
			if (ACTOR_IS_DEAD(ainfo))
				continue;
		}

		return i;
	}

	return NULL;
}

int FindNearestSAMPPlayer(bool bCheckIfIsPlayerDead, float fPos[3])
{
	struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

	float mPos[3];
	vect3_copy(&self->base.matrix[4 * 3], mPos);

	int iPlayerID = 0;
	float fSmallestDistance = -1.0f;

	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (g_Players->iIsListed[i] != 1)
			continue;
		if (g_Players->pRemotePlayer[i] == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			continue;

		struct actor_info* ainfo = g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if (ainfo == NULL)
			continue;

		if (bCheckIfIsPlayerDead)
		{
			if (ACTOR_IS_DEAD(ainfo))
				continue;
		}

		float pPos[3];
		vect3_copy(&ainfo->base.matrix[4 * 3], pPos);

		float fDistance = vect3_dist(pPos, fPos);

		if (fSmallestDistance == -1.0f)
		{
			fSmallestDistance = fDistance;

			iPlayerID = i;
		}

		if (fDistance < fSmallestDistance)
		{
			fSmallestDistance = fDistance;

			iPlayerID = i;
		}
	}

	if (iPlayerID <= 0 || iPlayerID >= SAMP_MAX_PLAYERS || g_Players->iIsListed[iPlayerID] != 1)
		return NULL;

	return iPlayerID;
}
void BulletsHitAt(float self_pos[3], float target_pos[3], stAimData* aimData, float radius)
{
	D3DXVECTOR3 poss, poss2, screenposs;
	static int crosshair_x_mm;
	static int crosshair_y_mm;
	screenposs.x = (float)((pPresentParam.BackBufferWidth / 2) + crosshair_x_mm * ((float)pPresentParam.BackBufferWidth / 1920.f));
	screenposs.y = (float)((pPresentParam.BackBufferHeight / 2) + crosshair_y_mm * ((float)pPresentParam.BackBufferHeight / 1080.f));
	screenposs.z = 10.0f;

	CalcWorldCoors(&screenposs, &poss);

	screenposs.x = (float)(pPresentParam.BackBufferWidth / 2);
	screenposs.y = (float)(pPresentParam.BackBufferHeight / 2);
	screenposs.z = 10.0f;

	CalcWorldCoors(&screenposs, &poss2);

	float ffpos1[3], ffpos2[3], ffpos3[3];

	ffpos1[0] = poss.x;
	ffpos1[1] = poss.y;
	ffpos1[2] = poss.z;

	ffpos2[0] = poss2.x;
	ffpos2[1] = poss2.y;
	ffpos2[2] = poss2.z;

	vect3_copy((float*)0xB6F338, ffpos3);

	point3D ffp3d1 = VAIM(ffpos1, ffpos3);
	point3D ffp3d2 = VAIM(ffpos2, ffpos3);

	float xcross = ffp3d2.x - ffp3d1.x;
	float ycross = ffp3d2.y - ffp3d1.y;
	//
	float degx = Get_Deg(target_pos[0] - self_pos[0], target_pos[1] - self_pos[1], 90.0f);
	float newVirtualPos[3];

	newVirtualPos[0] = target_pos[0] + sin(degx * PI / 180.0f) * radius;
	newVirtualPos[1] = target_pos[1] + cos(degx * PI / 180.0f) * radius;
	newVirtualPos[2] = target_pos[2];

	degx = Get_Deg(target_pos[0] - newVirtualPos[0], target_pos[1] - newVirtualPos[1], 0.0f);

	float rx = target_pos[0] - newVirtualPos[0];
	float ry = target_pos[1] - newVirtualPos[1];

	aimData->vecAimPos[0] = newVirtualPos[0] - sin(degx * PI / 180.0f) * radius;
	aimData->vecAimPos[1] = newVirtualPos[1] - cos(degx * PI / 180.0f) * radius;
	aimData->vecAimPos[2] = newVirtualPos[2];

	aimData->vecAimf1[0] = sin(degx * PI / 180.0f + xcross);
	aimData->vecAimf1[1] = cos(degx * PI / 180.0f + xcross);
	aimData->vecAimf1[2] = sin(ycross);
}

static int crosshair_x_mm;
static int crosshair_y_mm;
void calc_crosshair_xy()
{
	static long		timer = 0;
	static DWORD	addr = 0;

	if (clock() - timer > 1000)
	{
		addr = (DWORD)dll_baseptr_get("DINPUT8.dll");
		timer = clock();
	}

	if (!addr)
		return;

	struct actor_info* self = actor_info_get(ACTOR_SELF, 0);
	if (self == NULL)
		return;

	if ((self->weapon_model == 358 || self->weapon_model == 359
		|| self->weapon_model == 360 || self->weapon_model == 367
		|| self->weapon_model == 368 || self->weapon_model == 369) && *(DWORD*)(addr + 0x2C1CD) != 0)
	{
		//maxrad *= 3;
		crosshair_x_mm = 0;
		crosshair_y_mm = 0;
	}
	else
	{
		crosshair_x_mm = crosshair_x_normal;
		crosshair_y_mm = crosshair_y_normal;
	}
}

void GetLocalBulletSyncData(stBulletData* bulletSync)
{
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.byteType = bulletSync->byteType;
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.sTargetID = bulletSync->sTargetID;

	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fCenter[0] = bulletSync->fCenter[0];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fCenter[1] = bulletSync->fCenter[1];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fCenter[2] = bulletSync->fCenter[2];

	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fOrigin[0] = bulletSync->fOrigin[0];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fOrigin[1] = bulletSync->fOrigin[1];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fOrigin[2] = bulletSync->fOrigin[2];

	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fTarget[0] = bulletSync->fTarget[0];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fTarget[1] = bulletSync->fTarget[1];
	g_PlayerInfo[g_Players->sLocalPlayerID].bulletData.fTarget[2] = bulletSync->fTarget[2];
}

struct actor_info* FindNearestGTAPed(bool bCheckIfIsPlayerDead)
{
	int nearest_id = actor_find_nearest(ACTOR_ALIVE);

	if (nearest_id == -1)
		return NULL;

	struct actor_info* ainfo = actor_info_get(nearest_id, ACTOR_ALIVE);

	if (ainfo == NULL)
		return NULL;

	if (bCheckIfIsPlayerDead)
	{
		if (ACTOR_IS_DEAD(ainfo))
			return NULL;
	}

	return ainfo;
}
void TeleportPlayer(int iPlayerID, float fPos[3])
{
	if (g_SAMP == NULL || g_Players == NULL)
		return;
	if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS || g_Players->iIsListed[iPlayerID] != 1) // including local player ID
		return;
	if (g_Players->pRemotePlayer[iPlayerID] == NULL || g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL
		|| g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
		return;

	struct actor_info* ainfo = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
	if (ainfo == NULL)
		return;

	if (ainfo->vehicle == NULL)
	{
		struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

		static bool carFound = false;

		static int nearestCar = 0;

		if (carFound == false)
		{
			float fSmallestDistance = -1.0f;

			for (int v = 0; v < SAMP_MAX_VEHICLES; v++)
			{
				if (g_Vehicles->iIsListed[v] != 1)
					continue;

				int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[v]) - (DWORD)pool_vehicle->start) / 2584;
				struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

				int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);
				if (iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
					continue;

				/*if ( vinfo->passengers[0] != NULL )
					continue;

				if ( vinfo->hitpoints == 0.0f )
					continue;*/

				float cPos[3];
				vect3_copy(&vinfo->base.matrix[4 * 3], cPos);

				float mPos[3];
				vect3_copy(&self->base.matrix[4 * 3], mPos);

				float fDistance = vect3_dist(cPos, mPos);

				if (fSmallestDistance == -1.0f)
				{
					fSmallestDistance = fDistance;

					nearestCar = v;
				}

				if (fDistance < fSmallestDistance)
				{
					fSmallestDistance = fDistance;

					nearestCar = v;
				}
			}

			if (nearestCar == 0 && g_Players->pLocalPlayer->sCurrentVehicleID == 0)
				return;
			if (nearestCar == 0 && g_Players->pLocalPlayer->sCurrentVehicleID != 0)
			{
				struct vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, 0);
				if (vinfo == NULL)
					return;

				nearestCar = g_Players->pLocalPlayer->sCurrentVehicleID;

				float self_pos[3];
				vect3_copy(&self->base.matrix[4 * 3], self_pos);

				self_pos[0] += sinf(-self->fCurrentRotation) * 5.0f;
				self_pos[1] += cosf(-self->fCurrentRotation) * 5.0f;

				GTAfunc_RemoveActorFromCarAndPutAt(self_pos);
			}

			carFound = true;
		}
		else
		{
			if (nearestCar <= 0 || nearestCar >= SAMP_MAX_VEHICLES || g_Players->iIsListed[nearestCar] != 1
				|| nearestCar == g_Players->pLocalPlayer->sCurrentVehicleID)
			{
				carFound = false;
				return;
			}

			int car_id = (int)(((DWORD)g_Vehicles->pGTA_Vehicle[nearestCar]) - (DWORD)pool_vehicle->start) / 2584;
			struct vehicle_info* vinfo = vehicle_info_get(car_id, 0);

			int iSAMPVehicleID = getSAMPVehicleIDFromGTAVehicle(vinfo);

			static int state = 0;
			if (state == 0)
			{
				float pPos[3];

				static bool gotPos = false;

				if (gotPos == false)
				{
					vect3_copy(&ainfo->base.matrix[4 * 3], pPos);
					pPos[2] -= 2.0f;

					gotPos = true;
				}

				static long timer = 0;
				if (clock() - timer > 750)
				{
					pPos[2] += 0.5f;

					timer = 0;
				}

				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, pPos, vinfo->hitpoints, vinfo->speed);

				if (g_PlayerInfo[getSAMPPlayerIDFromGTAPed(ainfo)].onFootData.sSurfingVehicleID == iSAMPVehicleID)
				{
					gotPos = false;
					state = 1;
				}
			}
			else
			{
				static long timer = 0;
				if (clock() - timer > 250)
				{
					g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vinfo->hitpoints, vinfo->speed);

					nearestCar = 0;
					carFound = false;
					state = 0;

					timer = clock();
				}
			}
		}
	}
	else
	{
		struct vehicle_info* vtemp = ainfo->vehicle;
		int iSAMPVehicleID = getPlayerSAMPVehicleID(iPlayerID);

		if (vtemp == NULL || iSAMPVehicleID <= 0 || iSAMPVehicleID >= SAMP_MAX_VEHICLES)
			return;

		struct vehicle_info* vinfo = vehicle_info_get(VEHICLE_SELF, 0);

		if (vinfo != NULL)
		{
			if (vtemp == vinfo || iSAMPVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
			{
				struct actor_info* self = actor_info_get(ACTOR_SELF, 0);

				float self_pos[3];
				vect3_copy(&self->base.matrix[4 * 3], self_pos);

				self_pos[0] += sinf(-self->fCurrentRotation) * 5.0f;
				self_pos[1] += cosf(-self->fCurrentRotation) * 5.0f;

				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vtemp->hitpoints, vtemp->speed);

				static long timer = 0;
				if (clock() - timer > 40)
				{
					GTAfunc_RemoveActorFromCarAndPutAt(self_pos);

					timer = clock();
				}
			}
			else
			{
				g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vtemp->hitpoints, vtemp->speed);
			}
		}
		else
		{
			g_RakClient->SendFakeDriverSyncData(iSAMPVehicleID, fPos, vtemp->hitpoints, vtemp->speed);
		}
	}
}

float GetDistance(D3DXVECTOR3 target)
{
	actor_info* playerR = actor_info_get(ACTOR_SELF, NULL);

	CPed* pPedSelf = pGameInterface->GetPools()->GetPed((DWORD*)playerR);

	D3DXVECTOR3 player(pPedSelf->GetPosition()->fX, pPedSelf->GetPosition()->fY, pPedSelf->GetPosition()->fZ);
	return sqrt((player.x - target.x) * (player.x - target.x) + (player.y - target.y) * (player.y - target.y) + (player.z - target.z) * (player.z - target.z));
}
bool GetPlayerQuaternion(uint16_t playerID, float* fQuaternion)
{

	switch (g_Players->pRemotePlayer[playerID]->pPlayerData->bytePlayerState)
	{
	case PLAYER_STATE_DRIVER:
		vect4_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->inCarData.fQuaternion, fQuaternion);
		return true;
		break;
	default:
		vect4_copy(g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.fQuaternion, fQuaternion);
		return true;
		break;
	}
}
int NextPlayer(const int iplayerID, const int increase)
{
	if (increase == -1)
	{
		for (int playerID = iplayerID - 1; playerID >= 0; playerID--)
		{
			if (g_Players->iIsListed[playerID] != 1)
				continue;
			if (g_Players->pRemotePlayer[playerID] == NULL)
				continue;
			if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
				continue;
			if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
				continue;	// not streamed
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
			if (g_BotFuncs->uiIsBot[playerID][0] == 1)
				continue;
			if (!BotCheats->bUseFriendTarget && g_NewModSa->bOyuncuArkadas[playerID])
				continue;
#endif
			return playerID;
		}
	}
	else
	{
		for (int playerID = iplayerID + 1; playerID < SAMP_MAX_PLAYERS; playerID++)
		{
			if (g_Players->iIsListed[playerID] != 1)
				continue;
			if (g_Players->pRemotePlayer[playerID] == NULL)
				continue;
			if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
				continue;
			if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
				continue;	// not streamed
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
			if (g_BotFuncs->uiIsBot[playerID][0] == 1)
				continue;
			if (!BotCheats->bUseFriendTarget && g_NewModSa->bOyuncuArkadas[playerID])
				continue;
#endif
			return playerID;
		}
	}

	return iplayerID;
}
float GetDistance3D(float* first_operand, float* two_operand)
{
	return sqrt((two_operand[0] - first_operand[0]) * (two_operand[0] - first_operand[0])
		+ (two_operand[1] - first_operand[1]) * (two_operand[1] - first_operand[1])
		+ (two_operand[2] - first_operand[2]) * (two_operand[2] - first_operand[2]));
}
