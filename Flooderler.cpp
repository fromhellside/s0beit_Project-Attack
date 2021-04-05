#include "main.h"
#include "math_stuff.h"
#define ID_FLOODER_TYPE_ONLY_CHARACTERS 1
#define ID_FLOODER_TYPE_ONLY_BIG_LETTERS 2
#define ID_FLOODER_TYPE_ONLY_SMALL_LETTERS 3
#define ID_FLOODER_TYPE_ONLY_NUMBERS 4
#define ID_FLOODER_TYPE_BINARY 5
#define ID_FLOODER_TYPE_SPECIAL_CHARACTERS 6

void CF_ProjeFlooderi()
{
	if (cheat_state->Flooderler.iRandomFlooder)
	{
		DWORD s = GetTickCount();
		static DWORD l = 0;
		char randomleft[9 + 1];
		char randomright[9 + 1];
		if (s - l > set.ChatHacks.Project_Spammer1_Run_Delay)
		{
			switch (set.ChatHacks.bSpammer1_Random_Texts_Random_Type)
			{
				case ID_FLOODER_TYPE_ONLY_CHARACTERS:
				{
					GenerateRandom_Only_A_Z_a_z(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_A_Z_a_z(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if(set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s",set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				case ID_FLOODER_TYPE_ONLY_BIG_LETTERS:
				{
					GenerateRandom_Only_A_Z(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_A_Z(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if (set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s", set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				case ID_FLOODER_TYPE_ONLY_SMALL_LETTERS:
				{
					GenerateRandom_Only_a_z(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_a_z(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if (set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s", set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				case ID_FLOODER_TYPE_ONLY_NUMBERS:
				{
					GenerateRandom_Only_0_9(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_0_9(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if (set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s", set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				case ID_FLOODER_TYPE_BINARY:
				{
					GenerateRandom_Only_0_1(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_0_1(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if (set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s", set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				case ID_FLOODER_TYPE_SPECIAL_CHARACTERS:
				{
					GenerateRandom_Only_Special_Letters(randomleft, set.ChatHacks.sSpammer1_Left_Random_Text_Lenght);
					GenerateRandom_Only_Special_Letters(randomright, set.ChatHacks.sSpammer1_Right_Random_Text_Lenght);
					if (set.ChatHacks.bUseSpammer1_Left_Random_Texts)
						say("%s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text);
					else if (set.ChatHacks.bUseSpammer1_Right_Random_Texts)
						say("%s -+= %s", set.ChatHacks.Project_Spammer1_Text, randomright);
					if (set.ChatHacks.bUseSpammer1_Both_Random_Texts)
					{
						set.ChatHacks.bUseSpammer1_Left_Random_Texts = false;
						set.ChatHacks.bUseSpammer1_Right_Random_Texts = false;
						say("%s -+= %s -+= %s", randomleft, set.ChatHacks.Project_Spammer1_Text, randomright);
					}
				}
				break;
				/*default:
					cheat_state_text("Bilinmeyen spammer türü.");*/
				break;
			}
			l = GetTickCount();
		}
	}
	
}

void CF_PMFlooder()
{
	if (cheat_state->Flooderler.iPMCrashFlooder)
	{
		DWORD s = GetTickCount();
		static DWORD l = 0; 
		char gen_binarychars[91+1];
		if (set.ChatHacks.iPMLagFloodID == g_Players->sLocalPlayerID)
#if COMPILE_TYPE == COMPILE_TYPE_ENGLISH
			return cheat_state_text("You can't flood yourself.");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_LOW_LEVEL_VERSION
		if (set.ChatHacks.iPMLagger_Run_Delay < 100)
			return cheat_state_text("Gecikme 100'den düþük, hile çalýþmayacak.");
#elif COMPILE_TYPE == COMPILE_TYPE_TURKISH_HIGH_LEVEL_VERSION
		if (set.ChatHacks.iPMLagger_Run_Delay < 70)
			return cheat_state_text("Gecikme 70'ten düþük, hile çalýþmayacak.");
#endif
		if (s - l > set.ChatHacks.iPMLagger_Run_Delay)
		{ 
			generate_random_new_characters(gen_binarychars, set.ChatHacks.iPMLaggerText_Lenght);
			KomutYaz("/%s %i %s", set.ChatHacks.iPMLagFloodCommandText, set.ChatHacks.iPMLagFloodID, gen_binarychars);
			l = GetTickCount();
		}
	}
}
void CF_MatrixSpammer()
{
	if (cheat_state->Flooderler.iMatrixSpammer)
	{
		DWORD s = GetTickCount();
		static DWORD l = 0;
		if (s - l > set.ChatHacks.iMatrixSpammer_Run_Delay)
		{
			say("%d  %d  %d  %d  %d  %d  %d  %d  %d  %d",
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000),
				random(100, 25000)
				);
			l = GetTickCount();
		}
	}
}
void ChatFlooderleri(void)
{
	CF_ProjeFlooderi();
	CF_PMFlooder();
	CF_MatrixSpammer();
}
