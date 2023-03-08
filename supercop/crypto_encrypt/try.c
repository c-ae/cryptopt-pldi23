/*
 * crypto_encrypt/try.c version 20200810
 * D. J. Bernstein
 * Public domain.
 * Auto-generated by trygen.py; do not edit.
 */

#include "crypto_encrypt.h"
#include "try.h"
#include "randombytes.h"

const char *primitiveimplementation = crypto_encrypt_IMPLEMENTATION;

#define TUNE_BYTES 1536
#ifdef SMALL
#define MAXTEST_BYTES 128
#else
#define MAXTEST_BYTES 4096
#endif
#ifdef TIMECOP
#define LOOPS TIMECOP_LOOPS
#else
#ifdef SMALL
#define LOOPS 8
#else
#define LOOPS 64
#endif
#endif

static unsigned char *p;
static unsigned char *s;
static unsigned char *m;
static unsigned char *c;
static unsigned char *t;
static unsigned char *p2;
static unsigned char *s2;
static unsigned char *m2;
static unsigned char *c2;
static unsigned char *t2;
#define plen crypto_encrypt_PUBLICKEYBYTES
#define slen crypto_encrypt_SECRETKEYBYTES
unsigned long long mlen;
unsigned long long clen;
unsigned long long tlen;

void preallocate(void)
{
#ifdef RAND_R_PRNG_NOT_SEEDED
  RAND_status();
#endif
}

void allocate(void)
{
  unsigned long long alloclen = 0;
  if (alloclen < TUNE_BYTES) alloclen = TUNE_BYTES;
  if (alloclen < MAXTEST_BYTES + crypto_encrypt_BYTES) alloclen = MAXTEST_BYTES + crypto_encrypt_BYTES;
  if (alloclen < crypto_encrypt_PUBLICKEYBYTES) alloclen = crypto_encrypt_PUBLICKEYBYTES;
  if (alloclen < crypto_encrypt_SECRETKEYBYTES) alloclen = crypto_encrypt_SECRETKEYBYTES;
  p = alignedcalloc(alloclen);
  s = alignedcalloc(alloclen);
  m = alignedcalloc(alloclen);
  c = alignedcalloc(alloclen);
  t = alignedcalloc(alloclen);
  p2 = alignedcalloc(alloclen);
  s2 = alignedcalloc(alloclen);
  m2 = alignedcalloc(alloclen);
  c2 = alignedcalloc(alloclen);
  t2 = alignedcalloc(alloclen);
}

void unalign(void)
{
  ++p;
  ++s;
  ++m;
  ++c;
  ++t;
  ++p2;
  ++s2;
  ++m2;
  ++c2;
  ++t2;
}

void realign(void)
{
  --p;
  --s;
  --m;
  --c;
  --t;
  --p2;
  --s2;
  --m2;
  --c2;
  --t2;
}

void predoit(void)
{
  crypto_encrypt_keypair(p,s);
  unpoison(p,crypto_encrypt_PUBLICKEYBYTES);
  mlen = TUNE_BYTES;
  clen = 0;
  randombytes(m,mlen);
}

void doit(void)
{
  crypto_encrypt(c,&clen,m,mlen,p);
  unpoison(c,clen);
  crypto_encrypt_open(t,&tlen,c,clen,s);
}

void test(void)
{
  unsigned long long loop;
  int result;
  
  for (loop = 0;loop < LOOPS;++loop) {
    mlen = myrandom() % (MAXTEST_BYTES + 1);
    
    output_prepare(p2,p,plen);
    output_prepare(s2,s,slen);
    result = crypto_encrypt_keypair(p,s);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt_keypair returns nonzero");
    unpoison(p,plen);
    unpoison(s,slen);
    checksum(p,plen);
    checksum(s,slen);
    output_compare(p2,p,plen,"crypto_encrypt_keypair");
    output_compare(s2,s,slen,"crypto_encrypt_keypair");
    
    clen = mlen + crypto_encrypt_BYTES;
    output_prepare(c2,c,clen);
    input_prepare(m2,m,mlen);
    memcpy(p2,p,plen);
    double_canary(p2,p,plen);
    poison(m,mlen);
    unpoison(p,plen);
    result = crypto_encrypt(c,&clen,m,mlen,p);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt returns nonzero");
    unpoison(c,clen);
    unpoison(m,mlen);
    unpoison(p,plen);
    if (clen < mlen) fail("crypto_encrypt returns smaller output than input");
    if (clen > mlen + crypto_encrypt_BYTES) fail("crypto_encrypt returns more than crypto_encrypt_BYTES extra bytes");
    checksum(c,clen);
    output_compare(c2,c,clen,"crypto_encrypt");
    input_compare(m2,m,mlen,"crypto_encrypt");
    input_compare(p2,p,plen,"crypto_encrypt");
    
    tlen = clen;
    output_prepare(t2,t,tlen);
    memcpy(c2,c,clen);
    double_canary(c2,c,clen);
    memcpy(s2,s,slen);
    double_canary(s2,s,slen);
    unpoison(c,clen);
    poison(s,slen);
    result = crypto_encrypt_open(t,&tlen,c,clen,s);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt_open returns nonzero");
    unpoison(t,tlen);
    unpoison(c,clen);
    unpoison(s,slen);
    if (tlen != mlen) fail("crypto_encrypt_open does not match mlen");
    if (memcmp(t,m,mlen) != 0) fail("crypto_encrypt_open does not match m");
    checksum(t,tlen);
    output_compare(t2,t,clen,"crypto_encrypt_open");
    input_compare(c2,c,clen,"crypto_encrypt_open");
    input_compare(s2,s,slen,"crypto_encrypt_open");
    
    double_canary(t2,t,tlen);
    double_canary(c2,c,clen);
    double_canary(s2,s,slen);
    unpoison(c2,clen);
    poison(s2,slen);
    result = crypto_encrypt_open(t2,&tlen,c2,clen,s2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt_open returns nonzero");
    unpoison(t2,tlen);
    unpoison(c2,clen);
    unpoison(s2,slen);
    if (memcmp(t2,t,tlen) != 0) fail("crypto_encrypt_open is nondeterministic");
    
    double_canary(t2,t,tlen);
    double_canary(c2,c,clen);
    double_canary(s2,s,slen);
    unpoison(c2,clen);
    poison(s,slen);
    result = crypto_encrypt_open(c2,&tlen,c2,clen,s);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt_open with c=t overlap returns nonzero");
    unpoison(c2,tlen);
    unpoison(s,slen);
    if (memcmp(c2,t,tlen) != 0) fail("crypto_encrypt_open does not handle c=t overlap");
    memcpy(c2,c,clen);
    unpoison(c,clen);
    poison(s2,slen);
    result = crypto_encrypt_open(s2,&tlen,c,clen,s2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_encrypt_open with s=t overlap returns nonzero");
    unpoison(s2,tlen);
    unpoison(c,clen);
    if (memcmp(s2,t,tlen) != 0) fail("crypto_encrypt_open does not handle s=t overlap");
    memcpy(s2,s,slen);
  }
#include "test-more.inc"
}
