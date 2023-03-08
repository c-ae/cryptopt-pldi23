/* Autogenerated: 'src/ExtractionOCaml/bedrock2_unsaturated_solinas' --lang bedrock2 --static --no-wide-int --widen-carry --widen-bytes --split-multiret --no-select --no-field-element-typedefs poly1305 64 3 '2^130 - 5' carry_mul carry_square carry add sub opp selectznz to_bytes from_bytes relax */
/* curve description: poly1305 */
/* machine_wordsize = 64 (from "64") */
/* requested operations: carry_mul, carry_square, carry, add, sub, opp, selectznz, to_bytes, from_bytes, relax */
/* n = 3 (from "3") */
/* s-c = 2^130 - [(1, 5)] (from "2^130 - 5") */
/* tight_bounds_multiplier = 1 (from "") */
/*  */
/* Computed values: */
/*   carry_chain = [0, 1, 2, 0, 1] */
/*   eval z = z[0] + (z[1] << 44) + (z[2] << 87) */
/*   bytes_eval z = z[0] + (z[1] << 8) + (z[2] << 16) + (z[3] << 24) + (z[4] << 32) + (z[5] << 40) + (z[6] << 48) + (z[7] << 56) + (z[8] << 64) + (z[9] << 72) + (z[10] << 80) + (z[11] << 88) + (z[12] << 96) + (z[13] << 104) + (z[14] << 112) + (z[15] << 120) + (z[16] << 128) */
/*   balance = [0x1ffffffffff6, 0xffffffffffe, 0xffffffffffe] */

#include <stdint.h>
#include <string.h>
#include <assert.h>

static __attribute__((constructor)) void _br2_preconditions(void) {
  static_assert(~(intptr_t)0 == -(intptr_t)1, "two's complement");
  assert(((void)"two's complement", ~(intptr_t)0 == -(intptr_t)1));
  assert(((void)"little-endian", 1 == *(unsigned char *)&(const uintptr_t){1}));
  assert(((void)"little-endian", 1 == *(unsigned char *)&(const intptr_t){1}));
}

// We use memcpy to work around -fstrict-aliasing.
// A plain memcpy is enough on clang 10, but not on gcc 10, which fails
// to infer the bounds on an integer loaded by memcpy.
// Adding a range mask after memcpy in turn makes slower code in clang.
// Loading individual bytes, shifting them together, and or-ing is fast
// on clang and sometimes on GCC, but other times GCC inlines individual
// byte operations without reconstructing wider accesses.
// The little-endian idiom below seems fast in gcc 9+ and clang 10.
static inline  __attribute__((always_inline, unused))
uintptr_t _br2_load(uintptr_t a, uintptr_t sz) {
  switch (sz) {
  case 1: { uint8_t  r = 0; memcpy(&r, (void*)a, 1); return r; }
  case 2: { uint16_t r = 0; memcpy(&r, (void*)a, 2); return r; }
  case 4: { uint32_t r = 0; memcpy(&r, (void*)a, 4); return r; }
  case 8: { uint64_t r = 0; memcpy(&r, (void*)a, 8); return r; }
  default: __builtin_unreachable();
  }
}

static inline __attribute__((always_inline, unused))
void _br2_store(uintptr_t a, uintptr_t v, uintptr_t sz) {
  memcpy((void*)a, &v, sz);
}

static inline __attribute__((always_inline, unused))
uintptr_t _br2_mulhuu(uintptr_t a, uintptr_t b) {
  #if (UINTPTR_MAX == (UINTMAX_C(1)<<31) - 1 + (UINTMAX_C(1)<<31))
	  return ((uint64_t)a * b) >> 32;
  #elif (UINTPTR_MAX == (UINTMAX_C(1)<<63) - 1 + (UINTMAX_C(1)<<63))
    return ((unsigned __int128)a * b) >> 64;
  #else
    #error "32-bit or 64-bit uintptr_t required"
  #endif
}

static inline __attribute__((always_inline, unused))
uintptr_t _br2_divu(uintptr_t a, uintptr_t b) {
  if (!b) return -1;
  return a/b;
}

static inline __attribute__((always_inline, unused))
uintptr_t _br2_remu(uintptr_t a, uintptr_t b) {
  if (!b) return a;
  return a%b;
}

static inline __attribute__((always_inline, unused))
uintptr_t _br2_shamt(uintptr_t a) {
  return a&(sizeof(uintptr_t)*8-1);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 *   in1: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 */
static
void internal_fiat_poly1305_carry_mul(uintptr_t out0, uintptr_t in0, uintptr_t in1) {
  uintptr_t x2, x1, x5, x4, x0, x3, x8, x10, x25, x11, x26, x9, x24, x22, x29, x23, x30, x27, x31, x28, x12, x14, x35, x15, x36, x13, x34, x18, x39, x19, x40, x37, x6, x16, x43, x17, x44, x7, x42, x20, x47, x21, x48, x45, x46, x32, x51, x49, x52, x50, x38, x53, x56, x41, x57, x55, x58, x33, x60, x61, x62, x54, x64, x65, x59, x63, x66, x67, x68, x69, x70;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  x3 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x4 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x5 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x6 = (x2)*((x5)*((uintptr_t)(UINTMAX_C(5))));
  x7 = _br2_mulhuu((x2), ((x5)*((uintptr_t)(UINTMAX_C(5)))));
  x8 = (x2)*((x4)*((uintptr_t)(UINTMAX_C(10))));
  x9 = _br2_mulhuu((x2), ((x4)*((uintptr_t)(UINTMAX_C(10)))));
  x10 = (x1)*((x5)*((uintptr_t)(UINTMAX_C(10))));
  x11 = _br2_mulhuu((x1), ((x5)*((uintptr_t)(UINTMAX_C(10)))));
  x12 = (x2)*(x3);
  x13 = _br2_mulhuu((x2), (x3));
  x14 = (x1)*((x4)*((uintptr_t)(UINTMAX_C(2))));
  x15 = _br2_mulhuu((x1), ((x4)*((uintptr_t)(UINTMAX_C(2)))));
  x16 = (x1)*(x3);
  x17 = _br2_mulhuu((x1), (x3));
  x18 = (x0)*(x5);
  x19 = _br2_mulhuu((x0), (x5));
  x20 = (x0)*(x4);
  x21 = _br2_mulhuu((x0), (x4));
  x22 = (x0)*(x3);
  x23 = _br2_mulhuu((x0), (x3));
  x24 = (x10)+(x8);
  x25 = (uintptr_t)((x24)<(x10));
  x26 = (x25)+(x11);
  x27 = (x26)+(x9);
  x28 = (x22)+(x24);
  x29 = (uintptr_t)((x28)<(x22));
  x30 = (x29)+(x23);
  x31 = (x30)+(x27);
  x32 = ((x28)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))))|((x31)<<_br2_shamt((uintptr_t)(UINTMAX_C(20))));
  x33 = (x28)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x34 = (x14)+(x12);
  x35 = (uintptr_t)((x34)<(x14));
  x36 = (x35)+(x15);
  x37 = (x36)+(x13);
  x38 = (x18)+(x34);
  x39 = (uintptr_t)((x38)<(x18));
  x40 = (x39)+(x19);
  x41 = (x40)+(x37);
  x42 = (x16)+(x6);
  x43 = (uintptr_t)((x42)<(x16));
  x44 = (x43)+(x17);
  x45 = (x44)+(x7);
  x46 = (x20)+(x42);
  x47 = (uintptr_t)((x46)<(x20));
  x48 = (x47)+(x21);
  x49 = (x48)+(x45);
  x50 = (x32)+(x46);
  x51 = (uintptr_t)((x50)<(x32));
  x52 = (x51)+(x49);
  x53 = ((x50)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))|((x52)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))));
  x54 = (x50)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x55 = (x53)+(x38);
  x56 = (uintptr_t)((x55)<(x53));
  x57 = (x56)+(x41);
  x58 = ((x55)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))|((x57)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))));
  x59 = (x55)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x60 = (x58)*((uintptr_t)(UINTMAX_C(5)));
  x61 = (x33)+(x60);
  x62 = (x61)>>_br2_shamt((uintptr_t)(UINTMAX_C(44)));
  x63 = (x61)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x64 = (x62)+(x54);
  x65 = (x64)>>_br2_shamt((uintptr_t)(UINTMAX_C(43)));
  x66 = (x64)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x67 = (x65)+(x59);
  x68 = x63;
  x69 = x66;
  x70 = x67;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x68, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x69, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x70, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_carry_mul(uint64_t out1[3], const uint64_t arg1[3], const uint64_t arg2[3]) {
  internal_fiat_poly1305_carry_mul((uintptr_t)out1, (uintptr_t)arg1, (uintptr_t)arg2);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 */
static
void internal_fiat_poly1305_carry_square(uintptr_t out0, uintptr_t in0) {
  uintptr_t x2, x3, x4, x1, x5, x6, x0, x9, x17, x20, x18, x21, x10, x22, x19, x11, x13, x26, x14, x27, x12, x7, x15, x30, x16, x31, x8, x29, x23, x34, x32, x35, x33, x25, x36, x39, x28, x40, x38, x41, x24, x43, x44, x45, x37, x47, x48, x42, x46, x49, x50, x51, x52, x53;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x3 = (x2)*((uintptr_t)(UINTMAX_C(5)));
  x4 = (x3)*((uintptr_t)(UINTMAX_C(2)));
  x5 = (x2)*((uintptr_t)(UINTMAX_C(2)));
  x6 = (x1)*((uintptr_t)(UINTMAX_C(2)));
  x7 = (x2)*(x3);
  x8 = _br2_mulhuu((x2), (x3));
  x9 = (x1)*((x4)*((uintptr_t)(UINTMAX_C(2))));
  x10 = _br2_mulhuu((x1), ((x4)*((uintptr_t)(UINTMAX_C(2)))));
  x11 = (x1)*((x1)*((uintptr_t)(UINTMAX_C(2))));
  x12 = _br2_mulhuu((x1), ((x1)*((uintptr_t)(UINTMAX_C(2)))));
  x13 = (x0)*(x5);
  x14 = _br2_mulhuu((x0), (x5));
  x15 = (x0)*(x6);
  x16 = _br2_mulhuu((x0), (x6));
  x17 = (x0)*(x0);
  x18 = _br2_mulhuu((x0), (x0));
  x19 = (x17)+(x9);
  x20 = (uintptr_t)((x19)<(x17));
  x21 = (x20)+(x18);
  x22 = (x21)+(x10);
  x23 = ((x19)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))))|((x22)<<_br2_shamt((uintptr_t)(UINTMAX_C(20))));
  x24 = (x19)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x25 = (x13)+(x11);
  x26 = (uintptr_t)((x25)<(x13));
  x27 = (x26)+(x14);
  x28 = (x27)+(x12);
  x29 = (x15)+(x7);
  x30 = (uintptr_t)((x29)<(x15));
  x31 = (x30)+(x16);
  x32 = (x31)+(x8);
  x33 = (x23)+(x29);
  x34 = (uintptr_t)((x33)<(x23));
  x35 = (x34)+(x32);
  x36 = ((x33)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))|((x35)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))));
  x37 = (x33)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x38 = (x36)+(x25);
  x39 = (uintptr_t)((x38)<(x36));
  x40 = (x39)+(x28);
  x41 = ((x38)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))|((x40)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))));
  x42 = (x38)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x43 = (x41)*((uintptr_t)(UINTMAX_C(5)));
  x44 = (x24)+(x43);
  x45 = (x44)>>_br2_shamt((uintptr_t)(UINTMAX_C(44)));
  x46 = (x44)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x47 = (x45)+(x37);
  x48 = (x47)>>_br2_shamt((uintptr_t)(UINTMAX_C(43)));
  x49 = (x47)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x50 = (x48)+(x42);
  x51 = x46;
  x52 = x49;
  x53 = x50;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x51, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x52, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x53, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_carry_square(uint64_t out1[3], const uint64_t arg1[3]) {
  internal_fiat_poly1305_carry_square((uintptr_t)out1, (uintptr_t)arg1);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 */
static
void internal_fiat_poly1305_carry(uintptr_t out0, uintptr_t in0) {
  uintptr_t x0, x1, x2, x3, x4, x6, x7, x5, x8, x9, x10, x11, x12, x13;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x3 = x0;
  x4 = ((x3)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))))+(x1);
  x5 = ((x4)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))+(x2);
  x6 = ((x3)&((uintptr_t)(UINTMAX_C(17592186044415))))+(((x5)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))*((uintptr_t)(UINTMAX_C(5))));
  x7 = ((x6)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))))+((x4)&((uintptr_t)(UINTMAX_C(8796093022207))));
  x8 = (x6)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x9 = (x7)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x10 = ((x7)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))+((x5)&((uintptr_t)(UINTMAX_C(8796093022207))));
  x11 = x8;
  x12 = x9;
  x13 = x10;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x11, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x12, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x13, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_carry(uint64_t out1[3], const uint64_t arg1[3]) {
  internal_fiat_poly1305_carry((uintptr_t)out1, (uintptr_t)arg1);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 *   in1: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 */
static
void internal_fiat_poly1305_add(uintptr_t out0, uintptr_t in0, uintptr_t in1) {
  uintptr_t x0, x3, x1, x4, x2, x5, x6, x7, x8, x9, x10, x11;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  x3 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x4 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x5 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x6 = (x0)+(x3);
  x7 = (x1)+(x4);
  x8 = (x2)+(x5);
  x9 = x6;
  x10 = x7;
  x11 = x8;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x9, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x10, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x11, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_add(uint64_t out1[3], const uint64_t arg1[3], const uint64_t arg2[3]) {
  internal_fiat_poly1305_add((uintptr_t)out1, (uintptr_t)arg1, (uintptr_t)arg2);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 *   in1: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 */
static
void internal_fiat_poly1305_sub(uintptr_t out0, uintptr_t in0, uintptr_t in1) {
  uintptr_t x0, x3, x1, x4, x2, x5, x6, x7, x8, x9, x10, x11;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  x3 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x4 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x5 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x6 = (((uintptr_t)(UINTMAX_C(35184372088822)))+(x0))-(x3);
  x7 = (((uintptr_t)(UINTMAX_C(17592186044414)))+(x1))-(x4);
  x8 = (((uintptr_t)(UINTMAX_C(17592186044414)))+(x2))-(x5);
  x9 = x6;
  x10 = x7;
  x11 = x8;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x9, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x10, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x11, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_sub(uint64_t out1[3], const uint64_t arg1[3], const uint64_t arg2[3]) {
  internal_fiat_poly1305_sub((uintptr_t)out1, (uintptr_t)arg1, (uintptr_t)arg2);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 */
static
void internal_fiat_poly1305_opp(uintptr_t out0, uintptr_t in0) {
  uintptr_t x0, x1, x2, x3, x4, x5, x6, x7, x8;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x3 = ((uintptr_t)(UINTMAX_C(35184372088822)))-(x0);
  x4 = ((uintptr_t)(UINTMAX_C(17592186044414)))-(x1);
  x5 = ((uintptr_t)(UINTMAX_C(17592186044414)))-(x2);
  x6 = x3;
  x7 = x4;
  x8 = x5;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x6, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x7, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x8, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_opp(uint64_t out1[3], const uint64_t arg1[3]) {
  internal_fiat_poly1305_opp((uintptr_t)out1, (uintptr_t)arg1);
}


/*
 * Input Bounds:
 *   in0: [0x0 ~> 0x1]
 *   in1: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 *   in2: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff], [0x0 ~> 0xffffffffffffffff]]
 */
static
void internal_fiat_poly1305_selectznz(uintptr_t out0, uintptr_t in0, uintptr_t in1, uintptr_t in2) {
  uintptr_t x3, x6, x0, x7, x4, x9, x1, x10, x5, x12, x2, x13, x8, x11, x14, x15, x16, x17;
  /*skip*/
  x0 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in1)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  x3 = _br2_load((in2)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x4 = _br2_load((in2)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x5 = _br2_load((in2)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x6 = ((uintptr_t)(UINTMAX_C(-1)))+((uintptr_t)((in0)==((uintptr_t)(UINTMAX_C(0)))));
  x7 = (x6)^((uintptr_t)(UINTMAX_C(18446744073709551615)));
  x8 = ((x3)&(x6))|((x0)&(x7));
  x9 = ((uintptr_t)(UINTMAX_C(-1)))+((uintptr_t)((in0)==((uintptr_t)(UINTMAX_C(0)))));
  x10 = (x9)^((uintptr_t)(UINTMAX_C(18446744073709551615)));
  x11 = ((x4)&(x9))|((x1)&(x10));
  x12 = ((uintptr_t)(UINTMAX_C(-1)))+((uintptr_t)((in0)==((uintptr_t)(UINTMAX_C(0)))));
  x13 = (x12)^((uintptr_t)(UINTMAX_C(18446744073709551615)));
  x14 = ((x5)&(x12))|((x2)&(x13));
  x15 = x8;
  x16 = x11;
  x17 = x14;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x15, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x16, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x17, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_selectznz(uint64_t out1[3], uint8_t arg1, const uint64_t arg2[3], const uint64_t arg3[3]) {
  internal_fiat_poly1305_selectznz((uintptr_t)out1, (uintptr_t)arg1, (uintptr_t)arg2, (uintptr_t)arg3);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x3]]
 */
static
void internal_fiat_poly1305_to_bytes(uintptr_t out0, uintptr_t in0) {
  uintptr_t x0, x4, x3, x1, x6, x7, x8, x10, x11, x9, x2, x13, x14, x15, x17, x18, x16, x20, x5, x22, x23, x25, x12, x26, x27, x29, x28, x30, x32, x19, x33, x21, x34, x35, x31, x24, x39, x41, x43, x45, x37, x47, x48, x50, x52, x54, x56, x36, x58, x59, x61, x63, x65, x67, x69, x38, x40, x42, x44, x46, x49, x51, x53, x55, x57, x60, x62, x64, x66, x68, x70, x71, x72, x73, x74, x75, x76, x77, x78, x79, x80, x81, x82, x83, x84, x85, x86, x87, x88;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x3 = (x0)-((uintptr_t)(UINTMAX_C(17592186044411)));
  x4 = (uintptr_t)((x0)<(x3));
  x5 = (x3)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x6 = ((x4)<<_br2_shamt((uintptr_t)(UINTMAX_C(20))))-((x3)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))));
  x7 = (x1)-((uintptr_t)(UINTMAX_C(8796093022207)));
  x8 = (uintptr_t)((x1)<(x7));
  x9 = (x7)-(x6);
  x10 = (uintptr_t)((x7)<(x9));
  x11 = (x8)+(x10);
  x12 = (x9)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x13 = ((x11)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))))-((x9)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))));
  x14 = (x2)-((uintptr_t)(UINTMAX_C(8796093022207)));
  x15 = (uintptr_t)((x2)<(x14));
  x16 = (x14)-(x13);
  x17 = (uintptr_t)((x14)<(x16));
  x18 = (x15)+(x17);
  x19 = (x16)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x20 = ((x18)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))))-((x16)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))));
  x21 = ((uintptr_t)(UINTMAX_C(-1)))+((uintptr_t)((x20)==((uintptr_t)(UINTMAX_C(0)))));
  x22 = (x5)+((x21)&((uintptr_t)(UINTMAX_C(17592186044411))));
  x23 = (uintptr_t)((x22)<(x5));
  x24 = (x22)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x25 = ((x22)>>_br2_shamt((uintptr_t)(UINTMAX_C(44))))+((x23)<<_br2_shamt((uintptr_t)(UINTMAX_C(20))));
  x26 = (x25)+(x12);
  x27 = (uintptr_t)((x26)<(x12));
  x28 = (x26)+((x21)&((uintptr_t)(UINTMAX_C(8796093022207))));
  x29 = (uintptr_t)((x28)<((x21)&((uintptr_t)(UINTMAX_C(8796093022207)))));
  x30 = (x27)+(x29);
  x31 = (x28)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x32 = ((x28)>>_br2_shamt((uintptr_t)(UINTMAX_C(43))))+((x30)<<_br2_shamt((uintptr_t)(UINTMAX_C(21))));
  x33 = (x32)+(x19);
  x34 = (x33)+((x21)&((uintptr_t)(UINTMAX_C(8796093022207))));
  x35 = (x34)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x36 = (x35)<<_br2_shamt((uintptr_t)(UINTMAX_C(7)));
  x37 = (x31)<<_br2_shamt((uintptr_t)(UINTMAX_C(4)));
  x38 = (x24)&((uintptr_t)(UINTMAX_C(255)));
  x39 = (x24)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x40 = (x39)&((uintptr_t)(UINTMAX_C(255)));
  x41 = (x39)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x42 = (x41)&((uintptr_t)(UINTMAX_C(255)));
  x43 = (x41)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x44 = (x43)&((uintptr_t)(UINTMAX_C(255)));
  x45 = (x43)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x46 = (x45)&((uintptr_t)(UINTMAX_C(255)));
  x47 = (x45)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x48 = (x37)+(x47);
  x49 = (x48)&((uintptr_t)(UINTMAX_C(255)));
  x50 = (x48)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x51 = (x50)&((uintptr_t)(UINTMAX_C(255)));
  x52 = (x50)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x53 = (x52)&((uintptr_t)(UINTMAX_C(255)));
  x54 = (x52)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x55 = (x54)&((uintptr_t)(UINTMAX_C(255)));
  x56 = (x54)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x57 = (x56)&((uintptr_t)(UINTMAX_C(255)));
  x58 = (x56)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x59 = (x36)+(x58);
  x60 = (x59)&((uintptr_t)(UINTMAX_C(255)));
  x61 = (x59)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x62 = (x61)&((uintptr_t)(UINTMAX_C(255)));
  x63 = (x61)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x64 = (x63)&((uintptr_t)(UINTMAX_C(255)));
  x65 = (x63)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x66 = (x65)&((uintptr_t)(UINTMAX_C(255)));
  x67 = (x65)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x68 = (x67)&((uintptr_t)(UINTMAX_C(255)));
  x69 = (x67)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x70 = (x69)&((uintptr_t)(UINTMAX_C(255)));
  x71 = (x69)>>_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x72 = x38;
  x73 = x40;
  x74 = x42;
  x75 = x44;
  x76 = x46;
  x77 = x49;
  x78 = x51;
  x79 = x53;
  x80 = x55;
  x81 = x57;
  x82 = x60;
  x83 = x62;
  x84 = x64;
  x85 = x66;
  x86 = x68;
  x87 = x70;
  x88 = x71;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x72, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(1))), x73, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(2))), x74, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(3))), x75, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(4))), x76, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(5))), x77, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(6))), x78, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(7))), x79, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x80, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(9))), x81, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(10))), x82, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(11))), x83, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(12))), x84, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(13))), x85, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(14))), x86, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(15))), x87, 1);
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x88, 1);
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_to_bytes(uint8_t out1[17], const uint64_t arg1[3]) {
  internal_fiat_poly1305_to_bytes((uintptr_t)out1, (uintptr_t)arg1);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0xff], [0x0 ~> 0x3]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 */
static
void internal_fiat_poly1305_from_bytes(uintptr_t out0, uintptr_t in0) {
  uintptr_t x16, x15, x14, x13, x12, x11, x10, x9, x8, x7, x6, x5, x4, x3, x2, x1, x0, x32, x33, x31, x34, x30, x35, x29, x36, x28, x37, x38, x27, x40, x26, x41, x25, x42, x24, x43, x23, x44, x45, x22, x47, x21, x48, x20, x49, x19, x50, x18, x51, x17, x52, x39, x46, x53, x54, x55, x56;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), 1);
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(1))), 1);
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(2))), 1);
  x3 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(3))), 1);
  x4 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(4))), 1);
  x5 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(5))), 1);
  x6 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(6))), 1);
  x7 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(7))), 1);
  x8 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), 1);
  x9 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(9))), 1);
  x10 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(10))), 1);
  x11 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(11))), 1);
  x12 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(12))), 1);
  x13 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(13))), 1);
  x14 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(14))), 1);
  x15 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(15))), 1);
  x16 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), 1);
  /*skip*/
  /*skip*/
  x17 = (x16)<<_br2_shamt((uintptr_t)(UINTMAX_C(41)));
  x18 = (x15)<<_br2_shamt((uintptr_t)(UINTMAX_C(33)));
  x19 = (x14)<<_br2_shamt((uintptr_t)(UINTMAX_C(25)));
  x20 = (x13)<<_br2_shamt((uintptr_t)(UINTMAX_C(17)));
  x21 = (x12)<<_br2_shamt((uintptr_t)(UINTMAX_C(9)));
  x22 = (x11)*((uintptr_t)(UINTMAX_C(2)));
  x23 = (x10)<<_br2_shamt((uintptr_t)(UINTMAX_C(36)));
  x24 = (x9)<<_br2_shamt((uintptr_t)(UINTMAX_C(28)));
  x25 = (x8)<<_br2_shamt((uintptr_t)(UINTMAX_C(20)));
  x26 = (x7)<<_br2_shamt((uintptr_t)(UINTMAX_C(12)));
  x27 = (x6)<<_br2_shamt((uintptr_t)(UINTMAX_C(4)));
  x28 = (x5)<<_br2_shamt((uintptr_t)(UINTMAX_C(40)));
  x29 = (x4)<<_br2_shamt((uintptr_t)(UINTMAX_C(32)));
  x30 = (x3)<<_br2_shamt((uintptr_t)(UINTMAX_C(24)));
  x31 = (x2)<<_br2_shamt((uintptr_t)(UINTMAX_C(16)));
  x32 = (x1)<<_br2_shamt((uintptr_t)(UINTMAX_C(8)));
  x33 = x0;
  x34 = (x32)+(x33);
  x35 = (x31)+(x34);
  x36 = (x30)+(x35);
  x37 = (x29)+(x36);
  x38 = (x28)+(x37);
  x39 = (x38)&((uintptr_t)(UINTMAX_C(17592186044415)));
  x40 = (x38)>>_br2_shamt((uintptr_t)(UINTMAX_C(44)));
  x41 = (x27)+(x40);
  x42 = (x26)+(x41);
  x43 = (x25)+(x42);
  x44 = (x24)+(x43);
  x45 = (x23)+(x44);
  x46 = (x45)&((uintptr_t)(UINTMAX_C(8796093022207)));
  x47 = (x45)>>_br2_shamt((uintptr_t)(UINTMAX_C(43)));
  x48 = (x22)+(x47);
  x49 = (x21)+(x48);
  x50 = (x20)+(x49);
  x51 = (x19)+(x50);
  x52 = (x18)+(x51);
  x53 = (x17)+(x52);
  x54 = x39;
  x55 = x46;
  x56 = x53;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x54, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x55, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x56, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_from_bytes(uint64_t out1[3], const uint8_t arg1[17]) {
  internal_fiat_poly1305_from_bytes((uintptr_t)out1, (uintptr_t)arg1);
}


/*
 * Input Bounds:
 *   in0: [[0x0 ~> 0x100000000000], [0x0 ~> 0x80000000000], [0x0 ~> 0x80000000000]]
 * Output Bounds:
 *   out0: [[0x0 ~> 0x300000000000], [0x0 ~> 0x180000000000], [0x0 ~> 0x180000000000]]
 */
static
void internal_fiat_poly1305_relax(uintptr_t out0, uintptr_t in0) {
  uintptr_t x0, x1, x2, x3, x4, x5, x6, x7, x8;
  x0 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(0))), sizeof(uintptr_t));
  x1 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(8))), sizeof(uintptr_t));
  x2 = _br2_load((in0)+((uintptr_t)(UINTMAX_C(16))), sizeof(uintptr_t));
  /*skip*/
  /*skip*/
  x3 = x0;
  x4 = x1;
  x5 = x2;
  x6 = x3;
  x7 = x4;
  x8 = x5;
  /*skip*/
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(0))), x6, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(8))), x7, sizeof(uintptr_t));
  _br2_store((out0)+((uintptr_t)(UINTMAX_C(16))), x8, sizeof(uintptr_t));
  /*skip*/
  return;
}

/* NOTE: The following wrapper function is not covered by Coq proofs */
static void fiat_poly1305_relax(uint64_t out1[3], const uint64_t arg1[3]) {
  internal_fiat_poly1305_relax((uintptr_t)out1, (uintptr_t)arg1);
}
