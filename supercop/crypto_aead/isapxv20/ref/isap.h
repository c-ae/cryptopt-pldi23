#define DEBUG 0
#define ISAP128
#define KECCAKP400

#ifndef ISAP_H
#define ISAP_H

#ifdef ISAP128

/******************************************************************************/
/*                               Isap-128                                     */
/******************************************************************************/

#ifdef KECCAKP400

/**************************************/
/*        Isap-128 & KeccakP400       */
/**************************************/

// Rate in bits
#define ISAP_rH 144
#define ISAP_rB 1

// Number of rounds
#define ISAP_sH 20
#define ISAP_sB 12
#define ISAP_sE 12
#define ISAP_sK 12

// State size in bytes
#define ISAP_STATE_SZ 50

#elif defined(ASCON)

/**************************************/
/*          Isap-128 & Ascon          */
/**************************************/

// Rate in bytes
#define ISAP_rH 64
#define ISAP_rB 1

// Number of rounds
#define ISAP_sH 12
#define ISAP_sB 12
#define ISAP_sE 12
#define ISAP_sK 12

// State size in bytes
#define ISAP_STATE_SZ 40

#endif // ASCON

#elif defined(ISAP128A)

/******************************************************************************/
/*                               Isap-128a                                    */
/******************************************************************************/

#ifdef KECCAKP400

/**************************************/
/*       Isap-128a & KeccakP400       */
/**************************************/

// Rate in bits
#define ISAP_rH 144
#define ISAP_rB 1

// Number of rounds
#define ISAP_sH 16
#define ISAP_sB 1
#define ISAP_sE 8
#define ISAP_sK 8

// State size in bytes
#define ISAP_STATE_SZ 50

#elif defined(ASCON)

/**************************************/
/*         Isap-128a & Ascon          */
/**************************************/

// Rate in bits
#define ISAP_rH 64
#define ISAP_rB 1

// Number of rounds
#define ISAP_sH 12
#define ISAP_sB 1
#define ISAP_sE 6
#define ISAP_sK 12

// State size in bytes
#define ISAP_STATE_SZ 40

#endif // ASCON

#endif // ISAP128A

/******************************************************************************/
/*                                Generic                                     */
/******************************************************************************/

// Size of rate in bytes
#define ISAP_rH_SZ ((ISAP_rH+7)/8)

// Size of zero truncated IV in bytes
#define ISAP_IV_SZ 8

// Size of tag in bytes
#define ISAP_TAG_SZ 16

// Security level
#define ISAP_K 128

void isap_mac(
	const unsigned char *k,
	const unsigned char *npub,
	const unsigned char *ad, const unsigned long long adlen,
	const unsigned char *c, const unsigned long long clen,
	unsigned char *tag
);

void isap_rk(
	const unsigned char *k,
	const unsigned char *iv,
	const unsigned char *in,
	const unsigned long long inlen,
	unsigned char *out,
	const unsigned long long outlen
);

void isap_enc(
	const unsigned char *k,
	const unsigned char *npub,
	const unsigned char *m, const unsigned long long mlen,
	unsigned char *c
);

#endif
