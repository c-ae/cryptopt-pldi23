#ifndef PARAMS_H
#define PARAMS_H


#define NEWHOPECMPCT_N 768

#if  (NEWHOPECMPCT_N == 512 || NEWHOPECMPCT_N == 1024)
#define NEWHOPECMPCT_Q    3329
#define NEWHOPECMPCT_QINV 62209   /* inverse_mod(p,2^16) */
#elif (NEWHOPECMPCT_N == 768)
#define NEWHOPECMPCT_Q    3457
#define NEWHOPECMPCT_QINV 12929   /* inverse_mod(p,2^16) */
#endif

#define NEWHOPECMPCT_K    2       /* used in noise sampling */

#define NEWHOPECMPCT_NTT_LENGTH 128

#if   (NEWHOPECMPCT_N == 512)
#define NEWHOPECMPCT_NTT_POLY 4
#define NEWHOPECMPCT_POLYCOMPRESSEDBITS  3
#elif (NEWHOPECMPCT_N == 768)
#define NEWHOPECMPCT_NTT_POLY 6
#define NEWHOPECMPCT_POLYCOMPRESSEDBITS  4
#elif (NEWHOPECMPCT_N == 1024)
#define NEWHOPECMPCT_NTT_POLY 8
#define NEWHOPECMPCT_POLYCOMPRESSEDBITS  4
#endif

#define NEWHOPECMPCT_SYMBYTES 32   /* size of shared key, seeds/coins, and hashes */

#define NEWHOPECMPCT_POLYBYTES            ((3*NEWHOPECMPCT_N)/2)
#define NEWHOPECMPCT_POLYCOMPRESSEDBYTES  ((NEWHOPECMPCT_POLYCOMPRESSEDBITS*NEWHOPECMPCT_N)/8)

#define NEWHOPECMPCT_CPAPKE_PUBLICKEYBYTES  (NEWHOPECMPCT_POLYBYTES + NEWHOPECMPCT_SYMBYTES)
#define NEWHOPECMPCT_CPAPKE_SECRETKEYBYTES  (NEWHOPECMPCT_POLYBYTES)
#define NEWHOPECMPCT_CPAPKE_CIPHERTEXTBYTES (NEWHOPECMPCT_POLYBYTES + NEWHOPECMPCT_POLYCOMPRESSEDBYTES)

#define NEWHOPECMPCT_CPAKEM_PUBLICKEYBYTES NEWHOPECMPCT_CPAPKE_PUBLICKEYBYTES
#define NEWHOPECMPCT_CPAKEM_SECRETKEYBYTES NEWHOPECMPCT_CPAPKE_SECRETKEYBYTES
#define NEWHOPECMPCT_CPAKEM_CIPHERTEXTBYTES NEWHOPECMPCT_CPAPKE_CIPHERTEXTBYTES

#define NEWHOPECMPCT_CCAKEM_PUBLICKEYBYTES NEWHOPECMPCT_CPAPKE_PUBLICKEYBYTES
#define NEWHOPECMPCT_CCAKEM_SECRETKEYBYTES (NEWHOPECMPCT_CPAPKE_SECRETKEYBYTES + NEWHOPECMPCT_CPAPKE_PUBLICKEYBYTES + 2*NEWHOPECMPCT_SYMBYTES)
#define NEWHOPECMPCT_CCAKEM_CIPHERTEXTBYTES (NEWHOPECMPCT_CPAPKE_CIPHERTEXTBYTES + NEWHOPECMPCT_SYMBYTES)  /* Second part is for Targhi-Unruh */

#endif
