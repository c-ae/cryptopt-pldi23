/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifndef SIMD_H
#define SIMD_H


#include "macros.h"

#if defined(_MSC_VER)
#include <immintrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON)
#include <arm_neon.h>
#endif

#include "cpu.h"

#if defined(__x86_64__) || defined(_M_X64)
#endif

#if defined(__aarch64__)
#define NO_UINT64_FALLBACK
#endif

#if defined(_MSC_VER)
#define restrict __restrict
#endif

#define ATTR_TARGET_S128

#define ATTR_TARGET_S256


#define apply_region(name, type, op, attributes)                                                   \
  static inline void attributes name(type* restrict dst, type const* restrict src,                 \
                                     unsigned int count) {                                         \
    for (unsigned int i = count; i; --i, ++dst, ++src) {                                           \
      *dst = op(*dst, *src);                                                                       \
    }                                                                                              \
  }

#define apply_mask(name, type, op, opmask, attributes)                                             \
  static inline type attributes name(const type lhs, const type rhs, const type mask) {            \
    return op(lhs, opmask(rhs, mask));                                                             \
  }

#define apply_mask_region(name, type, op, opmask, attributes)                                      \
  static inline void attributes name(type* restrict dst, type const* restrict src,                 \
                                     type const mask, unsigned int count) {                        \
    for (unsigned int i = count; i; --i, ++dst, ++src) {                                           \
      *dst = op(*dst, opmask(*src, mask));                                                         \
    }                                                                                              \
  }

#define apply_array(name, type, op, count, attributes)                                             \
  static inline void attributes name(type dst[count], type const lhs[count],                       \
                                     type const rhs[count]) {                                      \
    type* d       = dst;                                                                           \
    const type* l = lhs;                                                                           \
    const type* r = rhs;                                                                           \
    for (unsigned int i = count; i; --i, ++d, ++l, ++r) {                                          \
      *d = op(*l, *r);                                                                             \
    }                                                                                              \
  }



typedef uint64x2_t word128;

#define mm128_zero vmovq_n_u64(0)
#define mm128_load(s) vld1q_u64(s)
#define mm128_store(d, s) vst1q_u64(d, s)
#define mm128_xor(l, r) veorq_u64((l), (r))
#define mm128_and(l, r) vandq_u64((l), (r))
/* !l & r, requires l to be an immediate */
#define mm128_nand(l, r) vbicq_u64((r), (l))
#define mm128_broadcast_u64(x) vdupq_n_u64((x))
/* bit shifts up to 63 bits */
#define mm128_sl_u64(x, s) vshlq_n_u64((x), (s))
#define mm128_sr_u64(x, s) vshrq_n_u64((x), (s))

// clang-format off
apply_region(mm128_xor_region, word128, mm128_xor, FN_ATTRIBUTES_NEON)
apply_mask_region(mm128_xor_mask_region, word128, mm128_xor, mm128_and, FN_ATTRIBUTES_NEON)
apply_mask(mm128_xor_mask, word128, mm128_xor, mm128_and, FN_ATTRIBUTES_NEON_CONST)
apply_array(mm128_xor_256, word128, mm128_xor, 2, FN_ATTRIBUTES_NEON)
apply_array(mm128_and_256, word128, mm128_and, 2, FN_ATTRIBUTES_NEON)
// clang-format on

/* shift left by 64 to 127 bits */
#define mm128_shift_left_64_127(data, count)                                                       \
  mm128_sl_u64(vextq_u64(mm128_zero, data, 1), count - 64)
/* shift right by 64 to 127 bits */
#define mm128_shift_right_64_127(data, count)                                                      \
  mm128_sr_u64(vextq_u64(data, mm128_zero, 1), count - 64)

#define mm128_shift_left(data, count)                                                              \
  vorrq_u64(mm128_sl_u64(data, count), mm128_sr_u64(vextq_u64(mm128_zero, data, 1), 64 - count))

#define mm128_shift_right(data, count)                                                             \
  vorrq_u64(mm128_sr_u64(data, count), mm128_sl_u64(vextq_u64(data, mm128_zero, 1), 64 - count))

#define mm128_rotate_left(data, count)                                                             \
  vorrq_u64(mm128_shift_left(data, count), mm128_shift_right_64_127(data, 128 - count))

#define mm128_rotate_right(data, count)                                                            \
  vorrq_u64(mm128_shift_right(data, count), mm128_shift_left_64_127(data, 128 - count))

#define mm128_shift_left_256(res, data, count)                                                     \
  do {                                                                                             \
    res[1] = vorrq_u64(mm128_shift_left(data[1], count),                                           \
                       mm128_shift_right_64_127(data[0], 128 - count));                            \
    res[0] = mm128_shift_left(data[0], count);                                                     \
  } while (0)

#define mm128_shift_right_256(res, data, count)                                                    \
  do {                                                                                             \
    res[0] = vorrq_u64(mm128_shift_right(data[0], count),                                          \
                       mm128_shift_left_64_127(data[1], 128 - count));                             \
    res[1] = mm128_shift_right(data[1], count);                                                    \
  } while (0)

#define mm128_rotate_left_256(res, data, count)                                                    \
  do {                                                                                             \
    const word128 carry = mm128_shift_right_64_127(data[1], 128 - count);                          \
                                                                                                   \
    res[1] = vorrq_u64(mm128_shift_left(data[1], count),                                           \
                       mm128_shift_right_64_127(data[0], 128 - count));                            \
    res[0] = vorrq_u64(mm128_shift_left(data[0], count), carry);                                   \
  } while (0)

#define mm128_rotate_right_256(res, data, count)                                                   \
  do {                                                                                             \
    const word128 carry = mm128_shift_left_64_127(data[0], 128 - count);                           \
                                                                                                   \
    res[0] = vorrq_u64(mm128_shift_right(data[0], count),                                          \
                       mm128_shift_left_64_127(data[1], 128 - count));                             \
    res[1] = vorrq_u64(mm128_shift_right(data[1], count), carry);                                  \
  } while (0)

#if defined(_MSC_VER)
#undef restrict
#endif

#undef apply_region
#undef apply_mask_region
#undef apply_array
#undef BUILTIN_CPU_SUPPORTED

#endif
