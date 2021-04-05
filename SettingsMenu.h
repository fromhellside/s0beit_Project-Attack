#include "main.h"

extern TwBar* twBar_MainMenu;
extern TwBar* twBar_GeneralCheats;
extern TwBar* twBar_CarCheats;
extern TwBar* twBar_FloodCheats;
extern TwBar* twBar_AimFuncs;
extern TwBar* twBar_TrollFuncs;
extern TwBar* twBar_FakeKill;
extern TwBar* twBar_Aimbot;
extern TwBar* twBar_RakNetCheats;
extern TwBar* twBar_weaponCheats;
#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
extern TwBar* twBar_Bots;
#endif
extern TwBar* twBar_Interface;

void runNewMenu();
void initializeBarsMenu();
DWORD WINAPI threadMenuUpdate(PVOID);
void toggleATBCursor(bool bToggle);
