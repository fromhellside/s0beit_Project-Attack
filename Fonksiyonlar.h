/* 
	RapidFire's Attack Project / RapidFire'nin Attack Projesi
*/


#include "main.h"
#include "AraçHileleri.h"
#define ACTOR_INVEHICLE			4
#define ACTOR_ONFOOT			8
#define ACTOR_NOT_ME			16
#define ACTOR_NOT_IN_MY_CAR		32
#define ACTOR_NOT_AFK			64
#define ACTOR_NO_PROTECT		128
#define ACTOR_NOT_ATTACH		256
#define ACTOR_NOT_FRIEND		512
#define ACTOR_NO_SELF_COLOR		1024
#define ACTOR_NO_SELF_SKIN		2048
#define ACTOR_NO_SELF_TEAM		4096
#define OL_COLOR1(a) D3DCOLOR_ARGB(a, 0, 50, 50)
#define OL_COLOR1_2(a) D3DCOLOR_ARGB(a, 0, 60, 70)
#define OL_COLOR2(a) D3DCOLOR_ARGB(a, 0, 255, 255)
#define OL_COLOR3(a) D3DCOLOR_ARGB(a, 255, 255, 255)
#define OL_COLOR4(a) D3DCOLOR_ARGB(a, 23, 23, 23)
#define OL_COLOR5(a) D3DCOLOR_ARGB(a, 255, 255, 0)
#define OL_COLOR6(a) D3DCOLOR_ARGB(a, 34, 34, 0)
#define OL_COLOR7(a) D3DCOLOR_ARGB(a, 255, 0, 0)
#define OL_RED(a) D3DCOLOR_ARGB(a, 255, 0, 0)
#define OL_GREEN(a) D3DCOLOR_ARGB(a, 0, 255, 0)
#define MOD_SA_GROUP_COLOR1(a) D3DCOLOR_ARGB(a, 30, 30, 30)
#define MOD_SA_GROUP_COLOR2(a) D3DCOLOR_ARGB(a, 50, 50, 50)

#define						crosshair_x_normal 31
#define						crosshair_y_normal -77
#define						PI 3.141
#define CAMERA_X *(float*)0xB6F258
#define CAMERA_Y *(float*)0xB6F248


vehicle_info *GetVehicleInfoStandart(DWORD using_config_flags, DWORD force_add_flags);
vehicle_info *GetVehicleInfoForceFlags(DWORD flags);
byte GetPlayerAlpha(int playerid);
void SetColorAlpha(D3DCOLOR & color, byte alpha);
bool ValidVehicle(int VehicleID);
bool IsVehicleStreamed(uint16_t vehicleID);
int iGetAimingVehicle();
bool ActorIsVehicleDriver(actor_info * actor, vehicle_info * vehicle);
bool GetPlayerQuaternion(uint16_t playerID, float* fQuaternion);
std::vector<int> NearPlayers(int my_playerid, float distance, bool check_streamed);
std::vector<int> NearVehicles(int my_playerid, float distance, bool check_streamed);
//---- Full RakNet için yazýlan tanýmlamalarýn baþý ----//
#define NETCODE_CONNCOOKIELULZ 0x6969
#define RAKSAMP_CLIENT 1

//---- Full RakNet için yazýlan tanýmlamalarýn sonu ----//

//---- SobFoX'tan alýnan kaynaklar ----//
struct point3D
{
	float x, y, z;
	point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float radius2() { return x * x + y * y + z * z; }
	float radius() { return sqrt(x * x + y * y + z * z); }
};
struct Quaternion
{
	float x, y, z, w;
	float radius2() { return x * x + y * y + z * z + w * w; }
	float radius() { return sqrt(x * x + y * y + z * z + w * w); }
	point3D R;
};
void qEULER(point3D Rotation, Quaternion &q);

Quaternion qRotate(float rx, float ry, float rz);

float Get_Deg(float x, float y, float add);

point3D VAIM(float myPoint[3], float enemyPoint[3]);
//---- SobFoX'tan alýnan kaynaklarýn sonu ----//
void SetActorZAngle(actor_info *actor, float ang, bool Invert);

int GetClosestPlayerid(actor_info *player, int flugs);
int cheack_valid_weaponid(int weaponid);

int GetActorFlag(bool alive, bool incar, bool onfoot, bool ignore_myself, bool not_in_my_car, bool not_afk, bool no_attach, bool not_friend);

int R4nd0m(int min, int max);
unsigned int r4nDs(unsigned int from, unsigned int to);
float r4ndom_fl0at(float low, float high);
void ran_start(int seed);
float random_float(float a, float b);
double double_random(double a, double b);
void ran_array(unsigned int aa[], unsigned int n);
int rand0m(int min, int max);

bool ValidPlayer(int PlayerID);
bool IsPlayerStreamed(uint16_t playerID);

int GetAimingPlayer(bool bFromWhenPress);


int gen_gpci(char buf[64], unsigned long factor);
void BIG_NUM_MUL(unsigned long in[5], unsigned long out[6], unsigned long factor);

class tVector
{
public:

	float X, Y, Z;

	tVector()	{ this->X = 0.0f; this->Y = 0.0f; this->Z = 0.0f; };
	tVector(float a_float_X, float a_float_Y, float a_float_Z)	{ this->X = a_float_X; this->Y = a_float_Y; this->Z = a_float_Z; };

	tVector& operator= (const tVector& a_Vector) { this->X = a_Vector.X; this->Y = a_Vector.Y; this->Z = a_Vector.Z; return *this; }

	tVector operator+ (const tVector& a_Vector) const { return tVector(this->X + a_Vector.X, this->Y + a_Vector.Y, this->Z + a_Vector.Z); }
	tVector& operator+= (const tVector& a_Vector) { this->X += a_Vector.X; this->Y += a_Vector.Y; this->Z += a_Vector.Z; return *this; };

	tVector operator- (const tVector& a_Vector) const { return tVector(this->X - a_Vector.X, this->Y - a_Vector.Y, this->Z - a_Vector.Z); }
	tVector& operator-= (const tVector& a_Vector) { this->X -= a_Vector.X; this->Y -= a_Vector.Y; this->Z -= a_Vector.Z; return *this; };

	tVector operator* (const tVector& a_Vector) const { return tVector(this->X * a_Vector.X, this->Y * a_Vector.Y, this->Z * a_Vector.Z); }
	tVector& operator*= (const tVector& a_Vector) { this->X *= a_Vector.X; this->Y *= a_Vector.Y; this->Z *= a_Vector.Z; return *this; };

	tVector operator/ (const tVector& a_Vector) const { return tVector(this->X / a_Vector.X, this->Y / a_Vector.Y, this->Z / a_Vector.Z); }
	tVector& operator/= (const tVector& a_Vector) { this->X /= a_Vector.X; this->Y /= a_Vector.Y; this->Z /= a_Vector.Z; return *this; };

	tVector operator/ (const float a_Value) const { return tVector(this->X / a_Value, this->Y / a_Value, this->Z / a_Value); }
	tVector& operator/= (const float a_Value) { this->X /= a_Value; this->Y /= a_Value; this->Z /= a_Value; return *this; };

	float GetLength(void)
	{
		return sqrt(X * X + Y * Y + Z * Z);
	};

	float GetDistanceFrom(tVector* a_Vector)
	{
		return tVector(X - a_Vector->X, Y - a_Vector->Y, Z - a_Vector->Z).GetLength();
	}
};
struct stNewModSa
{
	/*  Sunucu Adminleri için deðiþkenler */
	
	bool bOyuncuAdmin[SAMP_MAX_PLAYERS];
	int iAdminlerID[SAMP_MAX_PLAYERS];

	/*  Sunucu Adminleri için deðiþkenler */

	/* Sunucudaki Arkadaþlarýmýz için deðiþkenler */
	
	bool bOyuncuArkadas[SAMP_MAX_PLAYERS];
	int iArkadasID[SAMP_MAX_PLAYERS];

	/* Sunucudaki Arkadaþlarýmýz için deðiþkenler */
	//Aim
	int iAimPlayerID;
	float fPosAimPlayerID[2];
	int iAimVehicleID;
	int iAimClientBot;

	//server
	BYTE byteLagComp;

	//screen
	float fViewFinderPosition[2];

	float fDesertEagleHitChance;
	float fM4HitChance;
	//thread
	//bool bThread;
};

struct stEnemyStats
{
	//this for calculate the effective speed and something like a ping
	int iPlayerOnFootTick[2];
	float fPlayerPos[2][3];
};

enum LastTick
{
	LAST,
	SECOND_LAST
};

struct stMenuSettings
{
	bool				bPosInitalized;
	float				fMenuPos[2];
	int					iRowHeight;
	int					iMenuHeight;
	int					iLogoHeight;
};

extern struct stMenuSettings MenuSettings;
extern struct stEnemyStats EnemyStats[SAMP_MAX_PLAYERS];

extern float fWeaponDamage[55];
extern float fWeaponRange[39];

extern float fWeaponRangeNew[39];
extern float fWeaponDamageNew[55];

void MatrixToQuaternion(VECTOR* right, VECTOR* up, VECTOR* at, float &quaterW, float &quaterX, float &quaterY, float &quaterZ);
float MagnetForce(float pos, float radius, float power, float mass);
void OL_CalculateLagPosition(int playerID, float fPos[3]);
void OL_CalculateSpeed(int playerID, float fSpeed[3]);
void KomutYaz(const char *szMessage, ...);
void sendPacket(RakNet::BitStream *bsParams);
void SetVehicleZAngle(vehicle_info *vehicle, float ang, bool Invert);
void MatrixToQuaternion2(tVector* right, tVector* up, tVector* at, float &quaterW, float &quaterX, float &quaterY, float &quaterZ);
float GetDistance(D3DXVECTOR3 target);
/* N3X's Features - N3X'in Fonksiyonlarý / Özellikleri. */
int FindNearestSAMPPlayer(bool bCheckIfIsPlayerDead, float fDistance);
int FindNearestSAMPPlayer(bool bCheckIfIsPlayerDead, float fPos[3]);
void BulletsHitAt(float self_pos[3], float target_pos[3], stAimData *aimData, float radius);
struct actor_info *FindNearestGTAPed(bool bCheckIfIsPlayerDead);
void TeleportPlayer(int iPlayerID, float fPos[3]);
void GetLocalBulletSyncData(stBulletData *bulletSync);

void calc_crosshair_xy(); // Muhtemelen NieXrlaM tarafýndan yapýldý.
int NextPlayer(const int iplayerID, const int increase);
float GetDistance3D(float* first_operand, float* two_operand);
DWORD rainbow();
bool IsPlayerConnected(uint16_t playerID);
bool IsPlayerConnectedTEST(uint16_t playerID);