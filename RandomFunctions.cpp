#include "main.h"
void gen_random(char* s, const int len) // 2
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
void generate_random_allchars(char* s, const int len) // 2
{
	static const char alphanum[] =
		"#$/()=?!+-[]"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
void generate_random_new_characters(char* s, const int len)
{
	static const char alphanum[] =
		"!\"·$%&/()=?|@#~€¬<>`+´ç^*¨Ç.,Şş™š▼Í¢-_";
	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
void generate_random_lagger_flooder(char* s, const int len)
{
	static const char alphanum[] =
		"^><$#½";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
int random(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
void GenerateRandom_Only_A_Z_a_z(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}
void GenerateRandom_Only_A_Z(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}
void GenerateRandom_Only_a_z(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}
void GenerateRandom_Only_0_9(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"0123456789";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}
void GenerateRandom_Only_0_1(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"01";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}
void GenerateRandom_Only_Special_Letters(char* str, int iLengthOfRandom)
{
	static const char alphanum[] =
		"$()=_[]@"
		"^><$#*}{";

	for (int i = 0; i < iLengthOfRandom; ++i)
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	str[iLengthOfRandom] = 0;
}