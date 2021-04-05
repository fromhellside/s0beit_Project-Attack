#include "main.h"

#define COMPILE_FOR_SAMP037 1
#define COMPILE_FOR_SAMP03DL 2
#define COMPILE_FOR_SAMP037R4 3


#define COMPILE_SAMP_VERSION COMPILE_FOR_SAMP03DL

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
#define SAMP_VERSION	"SA:MP 0.3.7"
#elif COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037R4
#define SAMP_VERSION	"SA:MP 0.3.7-R4"
#elif COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
#define SAMP_VERSION	"SA:MP 0.3.DL-R1"
#endif

// Compile Type - Derleme Türü : 0.3DL Veya 0.3.7... Sadece Seç...

#if COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037
#pragma message("Proje SA-MP 0.3.7 için çalýþacak þekilde derleniyor...")
#elif COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP03DL
#pragma message("Proje SA-MP 0.3DL için çalýþacak þekilde derleniyor...")
#elif COMPILE_SAMP_VERSION == COMPILE_FOR_SAMP037R4
#pragma message("Proje SA-MP 0.3.7-R4 için çalýþacak þekilde derleniyor...")
#else
#pragma message("Proje için her hangi bir sürüm seçilmedi, þu an bu okuduðun yazý kesinlikle yazmamasý gereken bir yazý!")
#endif