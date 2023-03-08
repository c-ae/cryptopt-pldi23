#define CUBEHASH_ROUNDS 16
#include "crypto_hash.h"
#include "crypto_uint8.h"
#include "crypto_uint16.h"
#include "crypto_uint32.h"

typedef crypto_uint8 crypto_uint1;
typedef crypto_uint8 crypto_uint3;
typedef crypto_uint8 crypto_uint5;
typedef crypto_uint16 crypto_uint9;
typedef crypto_uint16 crypto_uint11;

int crypto_hash(unsigned char *out,const unsigned char *in,unsigned long long inlen)
{
  crypto_uint8 newx00; crypto_uint8 x00[4] = {512 / 8};
  crypto_uint8 newx01; crypto_uint8 x01[4] = {32};
  crypto_uint8 newx02; crypto_uint8 x02[4] = {CUBEHASH_ROUNDS};
  crypto_uint8 newx03; crypto_uint8 x03[4] = {0};
  crypto_uint8 newx04; crypto_uint8 x04[4] = {0};
  crypto_uint8 newx05; crypto_uint8 x05[4] = {0};
  crypto_uint8 newx06; crypto_uint8 x06[4] = {0};
  crypto_uint8 newx07; crypto_uint8 x07[4] = {0};
  crypto_uint8 newx08; crypto_uint8 x08[4] = {0};
  crypto_uint8 newx09; crypto_uint8 x09[4] = {0};
  crypto_uint8 newx0a; crypto_uint8 x0a[4] = {0};
  crypto_uint8 newx0b; crypto_uint8 x0b[4] = {0};
  crypto_uint8 newx0c; crypto_uint8 x0c[4] = {0};
  crypto_uint8 newx0d; crypto_uint8 x0d[4] = {0};
  crypto_uint8 newx0e; crypto_uint8 x0e[4] = {0};
  crypto_uint8 newx0f; crypto_uint8 x0f[4] = {0};
  crypto_uint8 newx10; crypto_uint8 x10[4] = {0};
  crypto_uint8 newx11; crypto_uint8 x11[4] = {0};
  crypto_uint8 newx12; crypto_uint8 x12[4] = {0};
  crypto_uint8 newx13; crypto_uint8 x13[4] = {0};
  crypto_uint8 newx14; crypto_uint8 x14[4] = {0};
  crypto_uint8 newx15; crypto_uint8 x15[4] = {0};
  crypto_uint8 newx16; crypto_uint8 x16[4] = {0};
  crypto_uint8 newx17; crypto_uint8 x17[4] = {0};
  crypto_uint8 newx18; crypto_uint8 x18[4] = {0};
  crypto_uint8 newx19; crypto_uint8 x19[4] = {0};
  crypto_uint8 newx1a; crypto_uint8 x1a[4] = {0};
  crypto_uint8 newx1b; crypto_uint8 x1b[4] = {0};
  crypto_uint8 newx1c; crypto_uint8 x1c[4] = {0};
  crypto_uint8 newx1d; crypto_uint8 x1d[4] = {0};
  crypto_uint8 newx1e; crypto_uint8 x1e[4] = {0};
  crypto_uint8 newx1f; crypto_uint8 x1f[4] = {0};
  crypto_uint11 newq0; crypto_uint11 q0;
  crypto_uint11 newq1; crypto_uint11 q1;
  crypto_uint11 newq2; crypto_uint11 q2;
  crypto_uint11 newq3; crypto_uint11 q3;
  crypto_uint11 newq4; crypto_uint11 q4;
  crypto_uint11 newq5; crypto_uint11 q5;
  crypto_uint11 newq6; crypto_uint11 q6;
  crypto_uint11 newq7; crypto_uint11 q7;
  crypto_uint11 newq8; crypto_uint11 q8;
  crypto_uint11 newq9; crypto_uint11 q9;
  crypto_uint11 newqa; crypto_uint11 qa;
  crypto_uint11 newqb; crypto_uint11 qb;
  crypto_uint11 newqc; crypto_uint11 qc;
  crypto_uint11 newqd; crypto_uint11 qd;
  crypto_uint11 newqe; crypto_uint11 qe;
  crypto_uint11 newqf; crypto_uint11 qf;
  crypto_uint1 keep;
  crypto_uint1 qshift;
  crypto_uint1 newcarry0; crypto_uint1 carry0 = 0;
  crypto_uint1 newcarry1; crypto_uint1 carry1 = 0;
  crypto_uint1 newcarry2; crypto_uint1 carry2 = 0;
  crypto_uint1 newcarry3; crypto_uint1 carry3 = 0;
  crypto_uint1 newcarry4; crypto_uint1 carry4 = 0;
  crypto_uint1 newcarry5; crypto_uint1 carry5 = 0;
  crypto_uint1 newcarry6; crypto_uint1 carry6 = 0;
  crypto_uint1 newcarry7; crypto_uint1 carry7 = 0;
  crypto_uint1 newcarry8; crypto_uint1 carry8 = 0;
  crypto_uint1 newcarry9; crypto_uint1 carry9 = 0;
  crypto_uint1 newcarrya; crypto_uint1 carrya = 0;
  crypto_uint1 newcarryb; crypto_uint1 carryb = 0;
  crypto_uint1 newcarryc; crypto_uint1 carryc = 0;
  crypto_uint1 newcarryd; crypto_uint1 carryd = 0;
  crypto_uint1 newcarrye; crypto_uint1 carrye = 0;
  crypto_uint1 newcarryf; crypto_uint1 carryf = 0;
  crypto_uint9 z0;
  crypto_uint9 z1;
  crypto_uint9 z2;
  crypto_uint9 z3;
  crypto_uint9 z4;
  crypto_uint9 z5;
  crypto_uint9 z6;
  crypto_uint9 z7;
  crypto_uint9 z8;
  crypto_uint9 z9;
  crypto_uint9 za;
  crypto_uint9 zb;
  crypto_uint9 zc;
  crypto_uint9 zd;
  crypto_uint9 ze;
  crypto_uint9 zf;
  crypto_uint9 sum0;
  crypto_uint9 sum1;
  crypto_uint9 sum2;
  crypto_uint9 sum3;
  crypto_uint9 sum4;
  crypto_uint9 sum5;
  crypto_uint9 sum6;
  crypto_uint9 sum7;
  crypto_uint9 sum8;
  crypto_uint9 sum9;
  crypto_uint9 suma;
  crypto_uint9 sumb;
  crypto_uint9 sumc;
  crypto_uint9 sumd;
  crypto_uint9 sume;
  crypto_uint9 sumf;
  crypto_uint8 s0; crypto_uint8 t0;
  crypto_uint8 s1; crypto_uint8 t1;
  crypto_uint8 s2; crypto_uint8 t2;
  crypto_uint8 s3; crypto_uint8 t3;
  crypto_uint8 s4; crypto_uint8 t4;
  crypto_uint8 s5; crypto_uint8 t5;
  crypto_uint8 s6; crypto_uint8 t6;
  crypto_uint8 s7; crypto_uint8 t7;
  crypto_uint8 s8; crypto_uint8 t8;
  crypto_uint8 s9; crypto_uint8 t9;
  crypto_uint8 sa; crypto_uint8 ta;
  crypto_uint8 sb; crypto_uint8 tb;
  crypto_uint8 sc; crypto_uint8 tc;
  crypto_uint8 sd; crypto_uint8 td;
  crypto_uint8 se; crypto_uint8 te;
  crypto_uint8 sf; crypto_uint8 tf;
  crypto_uint3 top0;
  crypto_uint3 top1;
  crypto_uint3 top2;
  crypto_uint3 top3;
  crypto_uint3 top4;
  crypto_uint3 top5;
  crypto_uint3 top6;
  crypto_uint3 top7;
  crypto_uint3 top8;
  crypto_uint3 top9;
  crypto_uint3 topa;
  crypto_uint3 topb;
  crypto_uint3 topc;
  crypto_uint3 topd;
  crypto_uint3 tope;
  crypto_uint3 topf;
  crypto_uint5 mid0;
  crypto_uint5 mid1;
  crypto_uint5 mid2;
  crypto_uint5 mid3;
  crypto_uint5 mid4;
  crypto_uint5 mid5;
  crypto_uint5 mid6;
  crypto_uint5 mid7;
  crypto_uint5 mid8;
  crypto_uint5 mid9;
  crypto_uint5 mida;
  crypto_uint5 midb;
  crypto_uint5 midc;
  crypto_uint5 midd;
  crypto_uint5 mide;
  crypto_uint5 midf;
  crypto_uint3 bot0;
  crypto_uint3 bot1;
  crypto_uint3 bot2;
  crypto_uint3 bot3;
  crypto_uint3 bot4;
  crypto_uint3 bot5;
  crypto_uint3 bot6;
  crypto_uint3 bot7;
  crypto_uint3 bot8;
  crypto_uint3 bot9;
  crypto_uint3 bota;
  crypto_uint3 botb;
  crypto_uint3 botc;
  crypto_uint3 botd;
  crypto_uint3 bote;
  crypto_uint3 botf;
  int i;
  int r;
  int cycle;
  int bigcycle;
  int finalization = 0;
  unsigned char tmp[32];

  r = 16;
  goto morerounds;

  mainloop:

    for (i = 0;i < 4;++i) {
      x00[i] ^= in[i];
      x01[i] ^= in[i + 4];
      x02[i] ^= in[i + 8];
      x03[i] ^= in[i + 12];
      x04[i] ^= in[i + 16];
      x05[i] ^= in[i + 20];
      x06[i] ^= in[i + 24];
      x07[i] ^= in[i + 28];
    }
    in += 32;
    inlen -= 32;
    r = CUBEHASH_ROUNDS;

    morerounds:

    q0 = x08[3] >> 1;
    q1 = x09[3] >> 1;
    q2 = x0a[3] >> 1;
    q3 = x0b[3] >> 1;
    q4 = x0c[3] >> 1;
    q5 = x0d[3] >> 1;
    q6 = x0e[3] >> 1;
    q7 = x0f[3] >> 1;
    q8 = x00[3] >> 1;
    q9 = x01[3] >> 1;
    qa = x02[3] >> 1;
    qb = x03[3] >> 1;
    qc = x04[3] >> 1;
    qd = x05[3] >> 1;
    qe = x06[3] >> 1;
    qf = x07[3] >> 1;

    for (;r > 0;--r) {
      for (bigcycle = 0;bigcycle < 2;++bigcycle) {
        for (cycle = 0;cycle < 4;++cycle) {
	  z0 = x00[cycle];
	  z1 = x01[cycle];
	  z2 = x02[cycle];
	  z3 = x03[cycle];
	  z4 = x04[cycle];
	  z5 = x05[cycle];
	  z6 = x06[cycle];
	  z7 = x07[cycle];
	  z8 = x08[cycle];
	  z9 = x09[cycle];
	  za = x0a[cycle];
	  zb = x0b[cycle];
	  zc = x0c[cycle];
	  zd = x0d[cycle];
	  ze = x0e[cycle];
	  zf = x0f[cycle];
	  sum0 = x10[cycle] + (crypto_uint9) z0 + carry0;
          sum1 = x11[cycle] + (crypto_uint9) z1 + carry1;
          sum2 = x12[cycle] + (crypto_uint9) z2 + carry2;
          sum3 = x13[cycle] + (crypto_uint9) z3 + carry3;
	  sum4 = x14[cycle] + (crypto_uint9) z4 + carry4;
          sum5 = x15[cycle] + (crypto_uint9) z5 + carry5;
          sum6 = x16[cycle] + (crypto_uint9) z6 + carry6;
          sum7 = x17[cycle] + (crypto_uint9) z7 + carry7;
	  sum8 = x18[cycle] + (crypto_uint9) z8 + carry8;
          sum9 = x19[cycle] + (crypto_uint9) z9 + carry9;
          suma = x1a[cycle] + (crypto_uint9) za + carrya;
          sumb = x1b[cycle] + (crypto_uint9) zb + carryb;
	  sumc = x1c[cycle] + (crypto_uint9) zc + carryc;
          sumd = x1d[cycle] + (crypto_uint9) zd + carryd;
          sume = x1e[cycle] + (crypto_uint9) ze + carrye;
          sumf = x1f[cycle] + (crypto_uint9) zf + carryf;
	  s0 = sum0;
	  s1 = sum1;
	  s2 = sum2;
	  s3 = sum3;
	  s4 = sum4;
	  s5 = sum5;
	  s6 = sum6;
	  s7 = sum7;
	  s8 = sum8;
	  s9 = sum9;
	  sa = suma;
	  sb = sumb;
	  sc = sumc;
	  sd = sumd;
	  se = sume;
	  sf = sumf;
	  keep = cycle < 3;
	  newcarry0 = keep & (sum0 >> 8);
	  newcarry1 = keep & (sum1 >> 8);
	  newcarry2 = keep & (sum2 >> 8);
	  newcarry3 = keep & (sum3 >> 8);
	  newcarry4 = keep & (sum4 >> 8);
	  newcarry5 = keep & (sum5 >> 8);
	  newcarry6 = keep & (sum6 >> 8);
	  newcarry7 = keep & (sum7 >> 8);
	  newcarry8 = keep & (sum8 >> 8);
	  newcarry9 = keep & (sum9 >> 8);
	  newcarrya = keep & (suma >> 8);
	  newcarryb = keep & (sumb >> 8);
	  newcarryc = keep & (sumc >> 8);
	  newcarryd = keep & (sumd >> 8);
	  newcarrye = keep & (sume >> 8);
	  newcarryf = keep & (sumf >> 8);
	  t0 = (q0 & 127) | (bigcycle ? (q0 & 128) : (z8 << 7));
	  t1 = (q1 & 127) | (bigcycle ? (q1 & 128) : (z9 << 7));
	  t2 = (q2 & 127) | (bigcycle ? (q2 & 128) : (za << 7));
	  t3 = (q3 & 127) | (bigcycle ? (q3 & 128) : (zb << 7));
	  t4 = (q4 & 127) | (bigcycle ? (q4 & 128) : (zc << 7));
	  t5 = (q5 & 127) | (bigcycle ? (q5 & 128) : (zd << 7));
	  t6 = (q6 & 127) | (bigcycle ? (q6 & 128) : (ze << 7));
	  t7 = (q7 & 127) | (bigcycle ? (q7 & 128) : (zf << 7));
	  t8 = (q8 & 127) | (bigcycle ? (q8 & 128) : (z0 << 7));
	  t9 = (q9 & 127) | (bigcycle ? (q9 & 128) : (z1 << 7));
	  ta = (qa & 127) | (bigcycle ? (qa & 128) : (z2 << 7));
	  tb = (qb & 127) | (bigcycle ? (qb & 128) : (z3 << 7));
	  tc = (qc & 127) | (bigcycle ? (qc & 128) : (z4 << 7));
	  td = (qd & 127) | (bigcycle ? (qd & 128) : (z5 << 7));
	  te = (qe & 127) | (bigcycle ? (qe & 128) : (z6 << 7));
	  tf = (qf & 127) | (bigcycle ? (qf & 128) : (z7 << 7));
	  newx00 = s0 ^ t0;
	  newx01 = s1 ^ t1;
	  newx02 = s2 ^ t2;
	  newx03 = s3 ^ t3;
	  newx04 = s4 ^ t4;
          newx05 = s5 ^ t5;
          newx06 = s6 ^ t6;
          newx07 = s7 ^ t7;
	  newx08 = s8 ^ t8;
          newx09 = s9 ^ t9;
          newx0a = sa ^ ta;
          newx0b = sb ^ tb;
	  newx0c = sc ^ tc;
          newx0d = sd ^ td;
          newx0e = se ^ te;
          newx0f = sf ^ tf;
	  newx10 = bigcycle ? s1 : s2;
	  newx11 = bigcycle ? s0 : s3;
	  newx12 = bigcycle ? s3 : s0;
	  newx13 = bigcycle ? s2 : s1;
	  newx14 = bigcycle ? s5 : s6;
	  newx15 = bigcycle ? s4 : s7;
	  newx16 = bigcycle ? s7 : s4;
	  newx17 = bigcycle ? s6 : s5;
	  newx18 = bigcycle ? s9 : sa;
	  newx19 = bigcycle ? s8 : sb;
	  newx1a = bigcycle ? sb : s8;
	  newx1b = bigcycle ? sa : s9;
	  newx1c = bigcycle ? sd : se;
	  newx1d = bigcycle ? sc : sf;
	  newx1e = bigcycle ? sf : sc;
	  newx1f = bigcycle ? se : sd;
	  top0 = bigcycle ? (z4 >> 5) : (newx04 >> 5);
	  top1 = bigcycle ? (z5 >> 5) : (newx05 >> 5);
	  top2 = bigcycle ? (z6 >> 5) : (newx06 >> 5);
	  top3 = bigcycle ? (z7 >> 5) : (newx07 >> 5);
	  top4 = bigcycle ? (z0 >> 5) : (newx00 >> 5);
	  top5 = bigcycle ? (z1 >> 5) : (newx01 >> 5);
	  top6 = bigcycle ? (z2 >> 5) : (newx02 >> 5);
	  top7 = bigcycle ? (z3 >> 5) : (newx03 >> 5);
	  top8 = bigcycle ? (zc >> 5) : (newx0c >> 5);
	  top9 = bigcycle ? (zd >> 5) : (newx0d >> 5);
	  topa = bigcycle ? (ze >> 5) : (newx0e >> 5);
	  topb = bigcycle ? (zf >> 5) : (newx0f >> 5);
	  topc = bigcycle ? (z8 >> 5) : (newx08 >> 5);
	  topd = bigcycle ? (z9 >> 5) : (newx09 >> 5);
	  tope = bigcycle ? (za >> 5) : (newx0a >> 5);
	  topf = bigcycle ? (zb >> 5) : (newx0b >> 5);
	  qshift = !(bigcycle ^ keep);
	  bot0 = qshift ? (q0 >> 8) : (bigcycle ? ((newx08 & 14) >> 1) : ((z8 & 14) >> 1));
	  bot1 = qshift ? (q1 >> 8) : (bigcycle ? ((newx09 & 14) >> 1) : ((z9 & 14) >> 1));
	  bot2 = qshift ? (q2 >> 8) : (bigcycle ? ((newx0a & 14) >> 1) : ((za & 14) >> 1));
	  bot3 = qshift ? (q3 >> 8) : (bigcycle ? ((newx0b & 14) >> 1) : ((zb & 14) >> 1));
	  bot4 = qshift ? (q4 >> 8) : (bigcycle ? ((newx0c & 14) >> 1) : ((zc & 14) >> 1));
	  bot5 = qshift ? (q5 >> 8) : (bigcycle ? ((newx0d & 14) >> 1) : ((zd & 14) >> 1));
	  bot6 = qshift ? (q6 >> 8) : (bigcycle ? ((newx0e & 14) >> 1) : ((ze & 14) >> 1));
	  bot7 = qshift ? (q7 >> 8) : (bigcycle ? ((newx0f & 14) >> 1) : ((zf & 14) >> 1));
	  bot8 = qshift ? (q8 >> 8) : (bigcycle ? ((newx00 & 14) >> 1) : ((z0 & 14) >> 1));
	  bot9 = qshift ? (q9 >> 8) : (bigcycle ? ((newx01 & 14) >> 1) : ((z1 & 14) >> 1));
	  bota = qshift ? (qa >> 8) : (bigcycle ? ((newx02 & 14) >> 1) : ((z2 & 14) >> 1));
	  botb = qshift ? (qb >> 8) : (bigcycle ? ((newx03 & 14) >> 1) : ((z3 & 14) >> 1));
	  botc = qshift ? (qc >> 8) : (bigcycle ? ((newx04 & 14) >> 1) : ((z4 & 14) >> 1));
	  botd = qshift ? (qd >> 8) : (bigcycle ? ((newx05 & 14) >> 1) : ((z5 & 14) >> 1));
	  bote = qshift ? (qe >> 8) : (bigcycle ? ((newx06 & 14) >> 1) : ((z6 & 14) >> 1));
	  botf = qshift ? (qf >> 8) : (bigcycle ? ((newx07 & 14) >> 1) : ((z7 & 14) >> 1));
	  mid0 = bigcycle ? (keep ? (z4 & 31) : (newx08 >> 4)) : (keep ? (z8 >> 4) : (newx04 & 31));
	  mid1 = bigcycle ? (keep ? (z5 & 31) : (newx09 >> 4)) : (keep ? (z9 >> 4) : (newx05 & 31));
	  mid2 = bigcycle ? (keep ? (z6 & 31) : (newx0a >> 4)) : (keep ? (za >> 4) : (newx06 & 31));
	  mid3 = bigcycle ? (keep ? (z7 & 31) : (newx0b >> 4)) : (keep ? (zb >> 4) : (newx07 & 31));
	  mid4 = bigcycle ? (keep ? (z0 & 31) : (newx0c >> 4)) : (keep ? (zc >> 4) : (newx00 & 31));
	  mid5 = bigcycle ? (keep ? (z1 & 31) : (newx0d >> 4)) : (keep ? (zd >> 4) : (newx01 & 31));
	  mid6 = bigcycle ? (keep ? (z2 & 31) : (newx0e >> 4)) : (keep ? (ze >> 4) : (newx02 & 31));
	  mid7 = bigcycle ? (keep ? (z3 & 31) : (newx0f >> 4)) : (keep ? (zf >> 4) : (newx03 & 31));
	  mid8 = bigcycle ? (keep ? (zc & 31) : (newx00 >> 4)) : (keep ? (z0 >> 4) : (newx0c & 31));
	  mid9 = bigcycle ? (keep ? (zd & 31) : (newx01 >> 4)) : (keep ? (z1 >> 4) : (newx0d & 31));
	  mida = bigcycle ? (keep ? (ze & 31) : (newx02 >> 4)) : (keep ? (z2 >> 4) : (newx0e & 31));
	  midb = bigcycle ? (keep ? (zf & 31) : (newx03 >> 4)) : (keep ? (z3 >> 4) : (newx0f & 31));
	  midc = bigcycle ? (keep ? (z8 & 31) : (newx04 >> 4)) : (keep ? (z4 >> 4) : (newx08 & 31));
	  midd = bigcycle ? (keep ? (z9 & 31) : (newx05 >> 4)) : (keep ? (z5 >> 4) : (newx09 & 31));
	  mide = bigcycle ? (keep ? (za & 31) : (newx06 >> 4)) : (keep ? (z6 >> 4) : (newx0a & 31));
	  midf = bigcycle ? (keep ? (zb & 31) : (newx07 >> 4)) : (keep ? (z7 >> 4) : (newx0b & 31));
	  newq0 = bot0 | (mid0 << 3) | (top0 << 8);
	  newq1 = bot1 | (mid1 << 3) | (top1 << 8);
	  newq2 = bot2 | (mid2 << 3) | (top2 << 8);
	  newq3 = bot3 | (mid3 << 3) | (top3 << 8);
	  newq4 = bot4 | (mid4 << 3) | (top4 << 8);
	  newq5 = bot5 | (mid5 << 3) | (top5 << 8);
	  newq6 = bot6 | (mid6 << 3) | (top6 << 8);
	  newq7 = bot7 | (mid7 << 3) | (top7 << 8);
	  newq8 = bot8 | (mid8 << 3) | (top8 << 8);
	  newq9 = bot9 | (mid9 << 3) | (top9 << 8);
	  newqa = bota | (mida << 3) | (topa << 8);
	  newqb = botb | (midb << 3) | (topb << 8);
	  newqc = botc | (midc << 3) | (topc << 8);
	  newqd = botd | (midd << 3) | (topd << 8);
	  newqe = bote | (mide << 3) | (tope << 8);
	  newqf = botf | (midf << 3) | (topf << 8);

	  x00[cycle] = newx00;
	  x01[cycle] = newx01;
	  x02[cycle] = newx02;
	  x03[cycle] = newx03;
	  x04[cycle] = newx04;
	  x05[cycle] = newx05;
	  x06[cycle] = newx06;
	  x07[cycle] = newx07;
	  x08[cycle] = newx08;
	  x09[cycle] = newx09;
	  x0a[cycle] = newx0a;
	  x0b[cycle] = newx0b;
	  x0c[cycle] = newx0c;
	  x0d[cycle] = newx0d;
	  x0e[cycle] = newx0e;
	  x0f[cycle] = newx0f;
	  x10[cycle] = newx10;
	  x11[cycle] = newx11;
	  x12[cycle] = newx12;
	  x13[cycle] = newx13;
	  x14[cycle] = newx14;
	  x15[cycle] = newx15;
	  x16[cycle] = newx16;
	  x17[cycle] = newx17;
	  x18[cycle] = newx18;
	  x19[cycle] = newx19;
	  x1a[cycle] = newx1a;
	  x1b[cycle] = newx1b;
	  x1c[cycle] = newx1c;
	  x1d[cycle] = newx1d;
	  x1e[cycle] = newx1e;
	  x1f[cycle] = newx1f;
	  q0 = newq0;
	  q1 = newq1;
	  q2 = newq2;
	  q3 = newq3;
	  q4 = newq4;
	  q5 = newq5;
	  q6 = newq6;
	  q7 = newq7;
	  q8 = newq8;
	  q9 = newq9;
	  qa = newqa;
	  qb = newqb;
	  qc = newqc;
	  qd = newqd;
	  qe = newqe;
	  qf = newqf;
	  carry0 = newcarry0;
	  carry1 = newcarry1;
	  carry2 = newcarry2;
	  carry3 = newcarry3;
	  carry4 = newcarry4;
	  carry5 = newcarry5;
	  carry6 = newcarry6;
	  carry7 = newcarry7;
	  carry8 = newcarry8;
	  carry9 = newcarry9;
	  carrya = newcarrya;
	  carryb = newcarryb;
	  carryc = newcarryc;
	  carryd = newcarryd;
	  carrye = newcarrye;
	  carryf = newcarryf;
	}
      }
    }

  if (inlen >= 32) goto mainloop;

  if (finalization == 0) {
    for (i = 0;i < inlen;++i) tmp[i] = in[i];
    tmp[i] = 128;
    for (++i;i < 32;++i) tmp[i] = 0;
    in = tmp;
    inlen = 32;
    finalization = 1;
    goto mainloop;
  }

  if (finalization == 1) {
    x1f[0] ^= 1;
    r = 32;
    finalization = 2;
    goto morerounds;
  }

  for (i = 0;i < 4;++i) {
    out[i] = x00[i];
    out[i + 4] = x01[i];
    out[i + 8] = x02[i];
    out[i + 12] = x03[i];
    out[i + 16] = x04[i];
    out[i + 20] = x05[i];
    out[i + 24] = x06[i];
    out[i + 28] = x07[i];
    out[i + 32] = x08[i];
    out[i + 36] = x09[i];
    out[i + 40] = x0a[i];
    out[i + 44] = x0b[i];
    out[i + 48] = x0c[i];
    out[i + 52] = x0d[i];
    out[i + 56] = x0e[i];
    out[i + 60] = x0f[i];
  }

  return 0;
}
