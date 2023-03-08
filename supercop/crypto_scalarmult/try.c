/*
 * crypto_scalarmult/try.c version 20200810
 * D. J. Bernstein
 * Public domain.
 * Auto-generated by trygen.py; do not edit.
 */

#include "crypto_scalarmult.h"
#include "try.h"
#include "randombytes.h"

const char *primitiveimplementation = crypto_scalarmult_IMPLEMENTATION;

#ifdef TIMECOP
#define LOOPS TIMECOP_LOOPS
#else
#ifdef SMALL
#define LOOPS 64
#else
#define LOOPS 512
#endif
#endif

static unsigned char *a;
static unsigned char *b;
static unsigned char *c;
static unsigned char *d;
static unsigned char *e;
static unsigned char *f;
static unsigned char *a2;
static unsigned char *b2;
static unsigned char *c2;
static unsigned char *d2;
static unsigned char *e2;
static unsigned char *f2;
#define alen crypto_scalarmult_SCALARBYTES
#define blen crypto_scalarmult_SCALARBYTES
#define clen crypto_scalarmult_BYTES
#define dlen crypto_scalarmult_BYTES
#define elen crypto_scalarmult_BYTES
#define flen crypto_scalarmult_BYTES

void preallocate(void)
{
}

void allocate(void)
{
  unsigned long long alloclen = 0;
  if (alloclen < crypto_scalarmult_SCALARBYTES) alloclen = crypto_scalarmult_SCALARBYTES;
  if (alloclen < crypto_scalarmult_SCALARBYTES) alloclen = crypto_scalarmult_SCALARBYTES;
  if (alloclen < crypto_scalarmult_BYTES) alloclen = crypto_scalarmult_BYTES;
  if (alloclen < crypto_scalarmult_BYTES) alloclen = crypto_scalarmult_BYTES;
  if (alloclen < crypto_scalarmult_BYTES) alloclen = crypto_scalarmult_BYTES;
  if (alloclen < crypto_scalarmult_BYTES) alloclen = crypto_scalarmult_BYTES;
  a = alignedcalloc(alloclen);
  b = alignedcalloc(alloclen);
  c = alignedcalloc(alloclen);
  d = alignedcalloc(alloclen);
  e = alignedcalloc(alloclen);
  f = alignedcalloc(alloclen);
  a2 = alignedcalloc(alloclen);
  b2 = alignedcalloc(alloclen);
  c2 = alignedcalloc(alloclen);
  d2 = alignedcalloc(alloclen);
  e2 = alignedcalloc(alloclen);
  f2 = alignedcalloc(alloclen);
}

void unalign(void)
{
  ++a;
  ++b;
  ++c;
  ++d;
  ++e;
  ++f;
  ++a2;
  ++b2;
  ++c2;
  ++d2;
  ++e2;
  ++f2;
}

void realign(void)
{
  --a;
  --b;
  --c;
  --d;
  --e;
  --f;
  --a2;
  --b2;
  --c2;
  --d2;
  --e2;
  --f2;
}

void predoit(void)
{
  randombytes(a,alen);
  randombytes(b,blen);
}

void doit(void)
{
  crypto_scalarmult_base(c,a);
  crypto_scalarmult_base(d,b);
  crypto_scalarmult(e,a,d);
  crypto_scalarmult(f,b,c);
}

void test(void)
{
  unsigned long long loop;
  int result;
  
  for (loop = 0;loop < LOOPS;++loop) {
    
    output_prepare(c2,c,clen);
    input_prepare(a2,a,alen);
    poison(a,alen);
    result = crypto_scalarmult_base(c,a);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base returns nonzero");
    unpoison(c,clen);
    unpoison(a,alen);
    checksum(c,clen);
    output_compare(c2,c,clen,"crypto_scalarmult_base");
    input_compare(a2,a,alen,"crypto_scalarmult_base");
    
    double_canary(c2,c,clen);
    double_canary(a2,a,alen);
    poison(a2,alen);
    result = crypto_scalarmult_base(c2,a2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base returns nonzero");
    unpoison(c2,clen);
    unpoison(a2,alen);
    if (memcmp(c2,c,clen) != 0) fail("crypto_scalarmult_base is nondeterministic");
    
    double_canary(c2,c,clen);
    double_canary(a2,a,alen);
    poison(a2,alen);
    result = crypto_scalarmult_base(a2,a2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base with a=c overlap returns nonzero");
    unpoison(a2,clen);
    if (memcmp(a2,c,clen) != 0) fail("crypto_scalarmult_base does not handle a=c overlap");
    memcpy(a2,a,alen);
    
    output_prepare(d2,d,dlen);
    input_prepare(b2,b,blen);
    poison(b,blen);
    result = crypto_scalarmult_base(d,b);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base returns nonzero");
    unpoison(d,dlen);
    unpoison(b,blen);
    checksum(d,dlen);
    output_compare(d2,d,dlen,"crypto_scalarmult_base");
    input_compare(b2,b,blen,"crypto_scalarmult_base");
    
    double_canary(d2,d,dlen);
    double_canary(b2,b,blen);
    poison(b2,blen);
    result = crypto_scalarmult_base(d2,b2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base returns nonzero");
    unpoison(d2,dlen);
    unpoison(b2,blen);
    if (memcmp(d2,d,dlen) != 0) fail("crypto_scalarmult_base is nondeterministic");
    
    double_canary(d2,d,dlen);
    double_canary(b2,b,blen);
    poison(b2,blen);
    result = crypto_scalarmult_base(b2,b2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult_base with b=d overlap returns nonzero");
    unpoison(b2,dlen);
    if (memcmp(b2,d,dlen) != 0) fail("crypto_scalarmult_base does not handle b=d overlap");
    memcpy(b2,b,blen);
    
    output_prepare(e2,e,elen);
    memcpy(a2,a,alen);
    double_canary(a2,a,alen);
    memcpy(d2,d,dlen);
    double_canary(d2,d,dlen);
    poison(a,alen);
    poison(d,dlen);
    result = crypto_scalarmult(e,a,d);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult returns nonzero");
    unpoison(e,elen);
    unpoison(a,alen);
    unpoison(d,dlen);
    checksum(e,elen);
    output_compare(e2,e,elen,"crypto_scalarmult");
    input_compare(a2,a,alen,"crypto_scalarmult");
    input_compare(d2,d,dlen,"crypto_scalarmult");
    
    double_canary(e2,e,elen);
    double_canary(a2,a,alen);
    double_canary(d2,d,dlen);
    poison(a2,alen);
    poison(d2,dlen);
    result = crypto_scalarmult(e2,a2,d2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult returns nonzero");
    unpoison(e2,elen);
    unpoison(a2,alen);
    unpoison(d2,dlen);
    if (memcmp(e2,e,elen) != 0) fail("crypto_scalarmult is nondeterministic");
    
    double_canary(e2,e,elen);
    double_canary(a2,a,alen);
    double_canary(d2,d,dlen);
    poison(a2,alen);
    poison(d,dlen);
    result = crypto_scalarmult(a2,a2,d);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult with a=e overlap returns nonzero");
    unpoison(a2,elen);
    unpoison(d,dlen);
    if (memcmp(a2,e,elen) != 0) fail("crypto_scalarmult does not handle a=e overlap");
    memcpy(a2,a,alen);
    poison(a,alen);
    poison(d2,dlen);
    result = crypto_scalarmult(d2,a,d2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult with d=e overlap returns nonzero");
    unpoison(d2,elen);
    unpoison(a,alen);
    if (memcmp(d2,e,elen) != 0) fail("crypto_scalarmult does not handle d=e overlap");
    memcpy(d2,d,dlen);
    
    output_prepare(f2,f,flen);
    memcpy(b2,b,blen);
    double_canary(b2,b,blen);
    memcpy(c2,c,clen);
    double_canary(c2,c,clen);
    poison(b,blen);
    poison(c,clen);
    result = crypto_scalarmult(f,b,c);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult returns nonzero");
    unpoison(f,flen);
    unpoison(b,blen);
    unpoison(c,clen);
    checksum(f,flen);
    output_compare(f2,f,flen,"crypto_scalarmult");
    input_compare(b2,b,blen,"crypto_scalarmult");
    input_compare(c2,c,clen,"crypto_scalarmult");
    
    double_canary(f2,f,flen);
    double_canary(b2,b,blen);
    double_canary(c2,c,clen);
    poison(b2,blen);
    poison(c2,clen);
    result = crypto_scalarmult(f2,b2,c2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult returns nonzero");
    unpoison(f2,flen);
    unpoison(b2,blen);
    unpoison(c2,clen);
    if (memcmp(f2,f,flen) != 0) fail("crypto_scalarmult is nondeterministic");
    
    double_canary(f2,f,flen);
    double_canary(b2,b,blen);
    double_canary(c2,c,clen);
    poison(b2,blen);
    poison(c,clen);
    result = crypto_scalarmult(b2,b2,c);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult with b=f overlap returns nonzero");
    unpoison(b2,flen);
    unpoison(c,clen);
    if (memcmp(b2,f,flen) != 0) fail("crypto_scalarmult does not handle b=f overlap");
    memcpy(b2,b,blen);
    poison(b,blen);
    poison(c2,clen);
    result = crypto_scalarmult(c2,b,c2);
    unpoison(&result,sizeof result);
    if (result != 0) fail("crypto_scalarmult with c=f overlap returns nonzero");
    unpoison(c2,flen);
    unpoison(b,blen);
    if (memcmp(c2,f,flen) != 0) fail("crypto_scalarmult does not handle c=f overlap");
    memcpy(c2,c,clen);
    
    if (memcmp(f,e,elen) != 0) fail("crypto_scalarmult not associative");
  }
#include "test-more.inc"
}