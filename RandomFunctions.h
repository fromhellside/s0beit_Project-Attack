#include "main.h"
void	gen_random(char* s, const int len);
void	generate_random_allchars(char* s, const int len);
void	generate_random_new_characters(char* s, const int len);
void	generate_random_lagger_flooder(char* s, const int len);
int		random(int min, int max);

void	GenerateRandom_Only_A_Z_a_z(char* str, int iLengthOfRandom); // Sadece A-Z, a-z
void	GenerateRandom_Only_A_Z(char* str, int iLengthOfRandom); // Sadece A-Z
void	GenerateRandom_Only_a_z(char* str, int iLengthOfRandom); // Sadece a-z
void	GenerateRandom_Only_0_9(char* str, int iLengthOfRandom); // Sadece 0-9
void	GenerateRandom_Only_0_1(char* str, int iLengthOfRandom); // Sadece 0-1
void	GenerateRandom_Only_Special_Letters(char* s, int iLengthOfRandom); // Sadece Özel karakterler.