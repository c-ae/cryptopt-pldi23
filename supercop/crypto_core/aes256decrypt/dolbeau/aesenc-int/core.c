/*
  core.c version $Date: 2016/04/01 17:05:23 $
  aes256decrypt
  Romain Dolbeau
  Public Domain
*/

#include "crypto_core.h"
#include <immintrin.h>


static inline void aes256ni_setkey_encrypt(const unsigned char* key, __m128i rkeys[15]) {
  __m128i key0 = _mm_loadu_si128((const __m128i *)(key+0));
  __m128i key1 = _mm_loadu_si128((const __m128i *)(key+16));
  __m128i temp0, temp1, temp2, temp4;
  int idx = 0;

  rkeys[idx++] = key0;
  temp0 = key0;
  temp2 = key1;

  /* blockshift-based block by Cedric Bourrasset & Romain Dolbeau */
#define BLOCK1(IMM)                              \
  temp1 = _mm_aeskeygenassist_si128(temp2, IMM); \
  rkeys[idx++] = temp2;                          \
  temp4 = _mm_slli_si128(temp0,4);               \
  temp0 = _mm_xor_si128(temp0,temp4);            \
  temp4 = _mm_slli_si128(temp0,8);               \
  temp0 = _mm_xor_si128(temp0,temp4);            \
  temp1 = _mm_shuffle_epi32(temp1,0xff);         \
  temp0 = _mm_xor_si128(temp0,temp1)

#define BLOCK2(IMM)                              \
  temp1 = _mm_aeskeygenassist_si128(temp0, IMM); \
  rkeys[idx++] = temp0;                          \
  temp4 = _mm_slli_si128(temp2,4);               \
  temp2 = _mm_xor_si128(temp2,temp4);            \
  temp4 = _mm_slli_si128(temp2,8);               \
  temp2 = _mm_xor_si128(temp2,temp4);            \
  temp1 = _mm_shuffle_epi32(temp1,0xaa);         \
  temp2 = _mm_xor_si128(temp2,temp1)
  
  BLOCK1(0x01);
  BLOCK2(0x01);

  BLOCK1(0x02);
  BLOCK2(0x02);

  BLOCK1(0x04);
  BLOCK2(0x04);

  BLOCK1(0x08);
  BLOCK2(0x08);

  BLOCK1(0x10);
  BLOCK2(0x10);

  BLOCK1(0x20);
  BLOCK2(0x20);

  BLOCK1(0x40);
  rkeys[idx++] = temp0;
}

static inline void aes256ni_setkey_decrypt(const unsigned char* key, __m128i rkeys[15]) {
  __m128i tkeys[15];
  int i;
  aes256ni_setkey_encrypt(key, tkeys);
  rkeys[0] = tkeys[14];
#pragma unroll(13)
  for (i = 1 ; i < 14 ; i++) {
    rkeys[i] = _mm_aesimc_si128(tkeys[14-i]);
  }
  rkeys[14] = tkeys[0];
}
static inline void aes256ni_decrypt(const __m128i rkeys[15], const unsigned char *n, unsigned char *out) {
  __m128i nv = _mm_loadu_si128((const __m128i *)n);
  int i;
  __m128i temp = _mm_xor_si128(nv, rkeys[0]);
#pragma unroll(13)
  for (i = 1 ; i < 14 ; i++) {
    temp = _mm_aesdec_si128(temp, rkeys[i]);
  }
  temp = _mm_aesdeclast_si128(temp, rkeys[14]);
  _mm_storeu_si128((__m128i*)(out), temp);
}

int crypto_core(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
)
{
  __m128i rkeys[15];
  aes256ni_setkey_decrypt(k,rkeys);
  aes256ni_decrypt(rkeys, in, out);
  return 0;
}

