/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */


#include "mpc_lowmc.h"
#include "mzd_additional.h"

#if !defined(_MSC_VER)
#include <stdalign.h>
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "simd.h"

#include "lowmc_255_255_4.h"

#define MPC_LOOP_CONST(function, result, first, second, sc)                                        \
  do {                                                                                             \
    for (unsigned int e = 0; e < (sc); ++e) {                                                      \
      function((result)[e], (first)[e], (second));                                                 \
    }                                                                                              \
  } while (0)

#define MPC_LOOP_SHARED(function, result, first, second, sc)                                       \
  do {                                                                                             \
    for (unsigned int o = 0; o < (sc); ++o) {                                                      \
      function((result)[o], (first)[o], (second)[o]);                                              \
    }                                                                                              \
  } while (0)

#define MPC_LOOP_SHARED_1(function, result, first, sc)                                             \
  do {                                                                                             \
    for (unsigned int o = 0; o < (sc); ++o) {                                                      \
      function((result)[o], (first)[o]);                                                           \
    }                                                                                              \
  } while (0)

#define MPC_LOOP_CONST_C_0(function, result, first, second, sc)                                    \
  function((result)[0], (first)[0], (second))

#define MPC_LOOP_CONST_C_ch(function, result, first, second, sc, c)                                \
  do {                                                                                             \
    if (!(c)) {                                                                                    \
      MPC_LOOP_CONST_C_0(function, result, first, second, sc);                                     \
    } else if ((c) == (sc)) {                                                                      \
      function((result)[(sc)-1], first[(sc)-1], (second));                                         \
    }                                                                                              \
  } while (0)

// clang-format off

/* MPC Sbox implementation for full instances */
#if !defined(NO_UINT64_FALLBACK)

static void mpc_and_uint64_256(mzd_local_t* res, const mzd_local_t* first,
                               const mzd_local_t* second, const mzd_local_t* r, view_t* view,
                               unsigned viewshift) {
  mzd_local_t tmp = {{0}};

  for (unsigned int m = 0; m < SC_PROOF; ++m) {
    const unsigned int j = (m + 1) % SC_PROOF;

    // f[m] & s[m]
    mzd_and_uint64_256(&res[m], &first[m], &second[m]);

    // f[m + 1] & s[m]
    mzd_and_uint64_256(&tmp, &first[j], &second[m]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    // f[m] & s[m + 1]
    mzd_and_uint64_256(&tmp, &first[m], &second[j]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    // ... ^ r[m] ^ r[m + 1]
    mzd_xor_uint64_256(&tmp, &r[m], &r[j]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    if (viewshift) {
      mzd_shift_right_uint64_256(&tmp, &res[m], viewshift);
      mzd_xor_uint64_256(&view->s[m], &view->s[m], &tmp);
    } else {
      // on first call (viewshift == 0), view->t[0..2] == 0
      mzd_copy_uint64_256(&view->s[m], &res[m]);
    }
  }
}

static void mpc_and_verify_uint64_256(mzd_local_t* res, const mzd_local_t* first,
                                      const mzd_local_t* second, const mzd_local_t* r, view_t* view,
                                      const mzd_local_t* mask, unsigned viewshift) {
  mzd_local_t tmp = {{0}};

  for (unsigned int m = 0; m < (SC_VERIFY - 1); ++m) {
    const unsigned int j = m + 1;

    mzd_and_uint64_256(&res[m], &first[m], &second[m]);

    mzd_and_uint64_256(&tmp, &first[j], &second[m]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    mzd_and_uint64_256(&tmp, &first[m], &second[j]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    mzd_xor_uint64_256(&tmp, &r[m], &r[j]);
    mzd_xor_uint64_256(&res[m], &res[m], &tmp);

    if (viewshift) {
      mzd_shift_right_uint64_256(&tmp, &res[m], viewshift);
      mzd_xor_uint64_256(&view->s[m], &view->s[m], &tmp);
    } else {
      // on first call (viewshift == 0), view->s[0] == 0
      mzd_copy_uint64_256(&view->s[m], &res[m]);
    }
  }

  if (viewshift) {
    mzd_shift_left_uint64_256(&tmp, &view->s[SC_VERIFY - 1], viewshift);
    mzd_and_uint64_256(&res[SC_VERIFY - 1], &tmp, mask);
  } else {
    mzd_and_uint64_256(&res[SC_VERIFY - 1], &view->s[SC_VERIFY - 1], mask);
  }
}

#define bitsliced_step_1(sc, AND, ROL, MASK_A, MASK_B, MASK_C)                                     \
  mzd_local_t x2m[sc] = {{{0}}};                                                                   \
  mzd_local_t r0m[sc] = {{{0}}}, r1m[sc] = {{{0}}}, r2m[sc] = {{{0}}};                             \
  mzd_local_t x0s[sc] = {{{0}}}, x1s[sc] = {{{0}}}, r0s[sc] = {{{0}}}, r1s[sc] = {{{0}}};          \
                                                                                                   \
  for (unsigned int m = 0; m < (sc); ++m) {                                                        \
    AND(&x0s[m], &in[m], MASK_A);                                                                  \
    AND(&x1s[m], &in[m], MASK_B);                                                                  \
    AND(&x2m[m], &in[m], MASK_C);                                                                  \
                                                                                                   \
    ROL(&x0s[m], &x0s[m], 2);                                                                      \
    ROL(&x1s[m], &x1s[m], 1);                                                                      \
                                                                                                   \
    AND(&r0m[m], &rvec->s[m], MASK_A);                                                             \
    AND(&r1m[m], &rvec->s[m], MASK_B);                                                             \
    AND(&r2m[m], &rvec->s[m], MASK_C);                                                             \
                                                                                                   \
    ROL(&r0s[m], &r0m[m], 2);                                                                      \
    ROL(&r1s[m], &r1m[m], 1);                                                                      \
  }

#define bitsliced_step_2(sc, XOR, ROR)                                                             \
  for (unsigned int m = 0; m < sc; ++m) {                                                          \
    XOR(&r2m[m], &r2m[m], &x0s[m]);                                                                \
    XOR(&x0s[m], &x0s[m], &x1s[m]);                                                                \
    XOR(&r1m[m], &r1m[m], &x0s[m]);                                                                \
    XOR(&r0m[m], &r0m[m], &x0s[m]);                                                                \
    XOR(&r0m[m], &r0m[m], &x2m[m]);                                                                \
                                                                                                   \
    ROR(&x0s[m], &r2m[m], 2);                                                                      \
    ROR(&x1s[m], &r1m[m], 1);                                                                      \
                                                                                                   \
    XOR(&x0s[m], &x0s[m], &r0m[m]);                                                                \
    XOR(&out[m], &x0s[m], &x1s[m]);                                                                \
  }



static void mpc_sbox_prove_uint64_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                  view_t* view, const rvec_t* rvec) {
  bitsliced_step_1(SC_PROOF, mzd_and_uint64_256, mzd_shift_left_uint64_256, mask_255_255_85_a,
                   mask_255_255_85_b, mask_255_255_85_c);

  // a & b
  mpc_and_uint64_256(r0m, x0s, x1s, r2m, view, 0);
  // b & c
  mpc_and_uint64_256(r2m, x1s, x2m, r1s, view, 1);
  // c & a
  mpc_and_uint64_256(r1m, x0s, x2m, r0s, view, 2);

  bitsliced_step_2(SC_PROOF, mzd_xor_uint64_256, mzd_shift_right_uint64_256);
}

static void mpc_sbox_verify_uint64_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                   view_t* view, const rvec_t* rvec) {
  bitsliced_step_1(SC_VERIFY, mzd_and_uint64_256, mzd_shift_left_uint64_256, mask_255_255_85_a,
                   mask_255_255_85_b, mask_255_255_85_c);

  // a & b
  mpc_and_verify_uint64_256(r0m, x0s, x1s, r2m, view, mask_255_255_85_c, 0);
  // b & c
  mpc_and_verify_uint64_256(r2m, x1s, x2m, r1s, view, mask_255_255_85_c, 1);
  // c & a
  mpc_and_verify_uint64_256(r1m, x0s, x2m, r0s, view, mask_255_255_85_c, 2);

  bitsliced_step_2(SC_VERIFY, mzd_xor_uint64_256, mzd_shift_right_uint64_256);
}
#endif /* NO_UINT_FALLBACK */

#define NROLR(a, b, c)                                                                             \
  do {                                                                                             \
    a[0] = b[0];                                                                                   \
    a[1] = b[1];                                                                                   \
    (void)c;                                                                                       \
  } while (0)

/* requires IN and RVEC to be defined */
#define bitsliced_mm_step_1(sc, type, AND, ROL, MASK_A, MASK_B, MASK_C)                            \
  type r0m[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type r0s[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type r1m[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type r1s[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type r2m[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type x0s[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type x1s[sc] ATTR_ALIGNED(alignof(type));                                                        \
  type x2m[sc] ATTR_ALIGNED(alignof(type));                                                        \
  do {                                                                                             \
    for (unsigned int m = 0; m < (sc); ++m) {                                                      \
      x0s[m] = AND(IN(m), MASK_A);                                                                 \
      x1s[m] = AND(IN(m), MASK_B);                                                                 \
      x2m[m] = AND(IN(m), MASK_C);                                                                 \
                                                                                                   \
      x0s[m] = ROL(x0s[m], 2);                                                                     \
      x1s[m] = ROL(x1s[m], 1);                                                                     \
                                                                                                   \
      r0m[m] = AND(RVEC(m), MASK_A);                                                               \
      r1m[m] = AND(RVEC(m), MASK_B);                                                               \
      r2m[m] = AND(RVEC(m), MASK_C);                                                               \
                                                                                                   \
      r0s[m] = ROL(r0m[m], 2);                                                                     \
      r1s[m] = ROL(r1m[m], 1);                                                                     \
    }                                                                                              \
  } while (0)

#define bitsliced_mm_step_2(sc, XOR, ROR)                                                          \
  do {                                                                                             \
    for (unsigned int m = 0; m < sc; ++m) {                                                        \
      r2m[m] = XOR(r2m[m], x0s[m]);                                                                \
      x0s[m] = XOR(x0s[m], x1s[m]);                                                                \
      r1m[m] = XOR(x0s[m], r1m[m]);                                                                \
      r0m[m] = XOR(x0s[m], r0m[m]);                                                                \
      r0m[m] = XOR(r0m[m], x2m[m]);                                                                \
                                                                                                   \
      x0s[m] = ROR(r2m[m], 2);                                                                     \
      x1s[m] = ROR(r1m[m], 1);                                                                     \
                                                                                                   \
      OUT(m) = XOR(r0m[m], XOR(x0s[m], x1s[m]));                                                   \
    }                                                                                              \
  } while (0)

#define mpc_mm_and_def(AND, XOR, ROR, res, first, second, r, viewshift)                            \
  do {                                                                                             \
    for (unsigned int m = 0; m < SC_PROOF; ++m) {                                                  \
      const unsigned int j = (m + 1) % SC_PROOF;                                                   \
                                                                                                   \
      res[m] = XOR(AND(first[m], second[m]), AND(first[j], second[m]));                            \
      res[m] = XOR(res[m], AND(first[m], second[j]));                                              \
      res[m] = XOR(res[m], XOR(r[m], r[j]));                                                       \
      if (viewshift) {                                                                             \
        VIEW(m) = XOR(ROR(res[m], viewshift), VIEW(m));                                            \
      } else {                                                                                     \
        VIEW(m) = res[m];                                                                          \
      }                                                                                            \
    }                                                                                              \
  } while (0)

#define mpc_mm_and_verify_def(AND, XOR, ROL, ROR, res, first, second, r, MASK, viewshift)          \
  do {                                                                                             \
    for (unsigned int m = 0; m < (SC_VERIFY - 1); ++m) {                                           \
      const unsigned int j = m + 1;                                                                \
                                                                                                   \
      res[m] = XOR(AND(first[m], second[m]), AND(first[j], second[m]));                            \
      res[m] = XOR(res[m], AND(first[m], second[j]));                                              \
      res[m] = XOR(res[m], XOR(r[m], r[j]));                                                       \
      if (viewshift) {                                                                             \
        VIEW(m) = XOR(ROR(res[m], viewshift), VIEW(m));                                            \
      } else {                                                                                     \
        VIEW(m) = res[m];                                                                          \
      }                                                                                            \
    }                                                                                              \
    if (viewshift) {                                                                               \
      res[SC_VERIFY - 1] = AND(ROL(VIEW(SC_VERIFY - 1), viewshift), MASK);                         \
    } else {                                                                                       \
      res[SC_VERIFY - 1] = AND(VIEW(SC_VERIFY - 1), MASK);                                         \
    }                                                                                              \
  } while (0)

#define bitsliced_mm_multiple_step_1(sc, type, size, AND, ROL, MASK_A, MASK_B, MASK_C)             \
  type r0m[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type r0s[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type r1m[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type r1s[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type r2m[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type x0s[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type x1s[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  type x2m[sc][size] ATTR_ALIGNED(alignof(type));                                                  \
  do {                                                                                             \
    for (unsigned int m = 0; m < (sc); ++m) {                                                      \
      AND(x0s[m], IN(m), MASK_A);                                                                  \
      AND(x1s[m], IN(m), MASK_B);                                                                  \
      AND(x2m[m], IN(m), MASK_C);                                                                  \
                                                                                                   \
      ROL(x0s[m], x0s[m], 2);                                                                      \
      ROL(x1s[m], x1s[m], 1);                                                                      \
                                                                                                   \
      AND(r0m[m], RVEC(m), MASK_A);                                                                \
      AND(r1m[m], RVEC(m), MASK_B);                                                                \
      AND(r2m[m], RVEC(m), MASK_C);                                                                \
                                                                                                   \
      ROL(r0s[m], r0m[m], 2);                                                                      \
      ROL(r1s[m], r1m[m], 1);                                                                      \
    }                                                                                              \
  } while (0)

#define bitsliced_mm_multiple_step_2(sc, type, size, XOR, ROR)                                     \
  do {                                                                                             \
    for (unsigned int m = 0; m < sc; ++m) {                                                        \
      XOR(r2m[m], r2m[m], x0s[m]);                                                                 \
      XOR(x0s[m], x0s[m], x1s[m]);                                                                 \
      XOR(r1m[m], x0s[m], r1m[m]);                                                                 \
      XOR(r0m[m], x0s[m], r0m[m]);                                                                 \
      XOR(r0m[m], r0m[m], x2m[m]);                                                                 \
                                                                                                   \
      ROR(x0s[m], r2m[m], 2);                                                                      \
      ROR(x1s[m], r1m[m], 1);                                                                      \
                                                                                                   \
      XOR(x0s[m], x0s[m], x1s[m]);                                                                 \
      XOR(OUT(m), r0m[m], x0s[m]);                                                                 \
    }                                                                                              \
  } while (0)

#define mpc_mm_multiple_and_def(type, size, AND, XOR, ROR, res, first, second, r, viewshift)       \
  do {                                                                                             \
    for (unsigned int m = 0; m < SC_PROOF; ++m) {                                                  \
      const unsigned int j = (m + 1) % SC_PROOF;                                                   \
      type tmp1[size] ATTR_ALIGNED(alignof(type)), tmp2[size] ATTR_ALIGNED(alignof(type));         \
                                                                                                   \
      AND(tmp1, first[m], second[m]);                                                              \
      AND(tmp2, first[j], second[m]);                                                              \
      XOR(res[m], tmp1, tmp2);                                                                     \
      AND(tmp1, first[m], second[j]);                                                              \
      XOR(res[m], res[m], tmp1);                                                                   \
      XOR(tmp2, r[m], r[j]);                                                                       \
      XOR(res[m], res[m], tmp2);                                                                   \
      if (viewshift) {                                                                             \
        ROR(tmp1, res[m], viewshift);                                                              \
        XOR(VIEW(m), tmp1, VIEW(m));                                                               \
      } else {                                                                                     \
        for (unsigned int k = 0; k < size; ++k) {                                                  \
          VIEW(m)[k] = res[m][k];                                                                  \
        }                                                                                          \
      }                                                                                            \
    }                                                                                              \
  } while (0)

#define mpc_mm_multiple_and_verify_def(type, size, AND, XOR, ROL, ROR, res, first, second, r,      \
                                       MASK, viewshift)                                            \
  do {                                                                                             \
    for (unsigned int m = 0; m < (SC_VERIFY - 1); ++m) {                                           \
      const unsigned int j = (m + 1) % SC_PROOF;                                                   \
      type tmp1[size] ATTR_ALIGNED(alignof(type)), tmp2[size] ATTR_ALIGNED(alignof(type));         \
                                                                                                   \
      AND(tmp1, first[m], second[m]);                                                              \
      AND(tmp2, first[j], second[m]);                                                              \
      XOR(res[m], tmp1, tmp2);                                                                     \
      AND(tmp1, first[m], second[j]);                                                              \
      XOR(res[m], res[m], tmp1);                                                                   \
      XOR(tmp2, r[m], r[j]);                                                                       \
      XOR(res[m], res[m], tmp2);                                                                   \
      if (viewshift) {                                                                             \
        ROR(tmp1, res[m], viewshift);                                                              \
        XOR(VIEW(m), tmp1, VIEW(m));                                                               \
      } else {                                                                                     \
        for (unsigned int k = 0; k < size; ++k) {                                                  \
          VIEW(m)[k] = res[m][k];                                                                  \
        }                                                                                          \
      }                                                                                            \
    }                                                                                              \
                                                                                                   \
    if (viewshift) {                                                                               \
      type tmp[size] ATTR_ALIGNED(alignof(type));                                                  \
      ROL(tmp, VIEW(SC_VERIFY - 1), viewshift);                                                    \
      AND(res[SC_VERIFY - 1], tmp, MASK);                                                          \
    } else {                                                                                       \
      AND(res[SC_VERIFY - 1], VIEW(SC_VERIFY - 1), MASK);                                          \
    }                                                                                              \
  } while (0)

#define IN(m) in[m].w128
#define OUT(m) out[m].w128
#define RVEC(m) rvec->s[m].w128
#define VIEW(m) view->s[m].w128

ATTR_TARGET_S128
static inline void mpc_sbox_prove_s128_256(mzd_local_t* out, const mzd_local_t* in, view_t* view,
                                           const rvec_t* rvec, const mzd_local_t* mask_a,
                                           const mzd_local_t* mask_b, const mzd_local_t* mask_c) {
  bitsliced_mm_multiple_step_1(SC_PROOF, word128, 2, mm128_and_256, mm128_shift_left_256,
                               mask_a->w128, mask_b->w128, mask_c->w128);

  // a & b
  mpc_mm_multiple_and_def(word128, 2, mm128_and_256, mm128_xor_256, NROLR, r0m, x0s, x1s, r2m, 0);
  // b & c
  mpc_mm_multiple_and_def(word128, 2, mm128_and_256, mm128_xor_256, mm128_shift_right_256, r2m, x1s,
                          x2m, r1s, 1);
  // c & a
  mpc_mm_multiple_and_def(word128, 2, mm128_and_256, mm128_xor_256, mm128_shift_right_256, r1m, x0s,
                          x2m, r0s, 2);

  bitsliced_mm_multiple_step_2(SC_PROOF, word128, 2, mm128_xor_256, mm128_shift_right_256);
}

ATTR_TARGET_S128
static inline void mpc_sbox_verify_s128_256(mzd_local_t* out, const mzd_local_t* in, view_t* view,
                                            const rvec_t* rvec, const mzd_local_t* mask_a,
                                            const mzd_local_t* mask_b, const mzd_local_t* mask_c) {
  bitsliced_mm_multiple_step_1(SC_VERIFY, word128, 2, mm128_and_256, mm128_shift_left_256,
                               mask_a->w128, mask_b->w128, mask_c->w128);

  // a & b
  mpc_mm_multiple_and_verify_def(word128, 2, mm128_and_256, mm128_xor_256, NROLR, NROLR, r0m, x0s,
                                 x1s, r2m, mask_c->w128, 0);
  // b & c
  mpc_mm_multiple_and_verify_def(word128, 2, mm128_and_256, mm128_xor_256, mm128_shift_left_256,
                                 mm128_shift_right_256, r2m, x1s, x2m, r1s, mask_c->w128, 1);
  // c & a
  mpc_mm_multiple_and_verify_def(word128, 2, mm128_and_256, mm128_xor_256, mm128_shift_left_256,
                                 mm128_shift_right_256, r1m, x0s, x2m, r0s, mask_c->w128, 2);

  bitsliced_mm_multiple_step_2(SC_VERIFY, word128, 2, mm128_xor_256, mm128_shift_right_256);
}



ATTR_TARGET_S128
static void mpc_sbox_prove_s128_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                view_t* view, const rvec_t* rvec) {
  mpc_sbox_prove_s128_256(out, in, view, rvec, mask_255_255_85_a, mask_255_255_85_b,
                          mask_255_255_85_c);
}

ATTR_TARGET_S128
static void mpc_sbox_verify_s128_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                 view_t* view, const rvec_t* rvec) {
  mpc_sbox_verify_s128_256(out, in, view, rvec, mask_255_255_85_a, mask_255_255_85_b,
                           mask_255_255_85_c);
}

#undef IN
#undef OUT
#undef RVEC
#undef VIEW

#define IN(m) in[m].w256
#define OUT(m) out[m].w256
#define RVEC(m) rvec->s[m].w256
#define VIEW(m) view->s[m].w256

ATTR_TARGET_AVX2
static inline void mpc_sbox_prove_s256_256(mzd_local_t* out, const mzd_local_t* in, view_t* view,
                                           const rvec_t* rvec, const word256 mask_a,
                                           const word256 mask_b, const word256 mask_c) {
  bitsliced_mm_step_1(SC_PROOF, word256, mm256_and, mm256_rotate_left, mask_a, mask_b, mask_c);

  // a & b
  mpc_mm_and_def(mm256_and, mm256_xor, mm256_rotate_right, r0m, x0s, x1s, r2m, 0);
  // b & c
  mpc_mm_and_def(mm256_and, mm256_xor, mm256_rotate_right, r2m, x1s, x2m, r1s, 1);
  // c & a
  mpc_mm_and_def(mm256_and, mm256_xor, mm256_rotate_right, r1m, x0s, x2m, r0s, 2);

  bitsliced_mm_step_2(SC_PROOF, mm256_xor, mm256_rotate_right);
}

ATTR_TARGET_AVX2
static void mpc_sbox_verify_s256_256(mzd_local_t* out, const mzd_local_t* in, view_t* view,
                                     const rvec_t* rvec, const word256 mask_a, const word256 mask_b,
                                     const word256 mask_c) {
  bitsliced_mm_step_1(SC_VERIFY, word256, mm256_and, mm256_rotate_left, mask_a, mask_b, mask_c);

  // a & b
  mpc_mm_and_verify_def(mm256_and, mm256_xor, mm256_rotate_left, mm256_rotate_right, r0m, x0s, x1s,
                        r2m, mask_c, 0);
  // b & c
  mpc_mm_and_verify_def(mm256_and, mm256_xor, mm256_rotate_left, mm256_rotate_right, r2m, x1s, x2m,
                        r1s, mask_c, 1);
  // c & a
  mpc_mm_and_verify_def(mm256_and, mm256_xor, mm256_rotate_left, mm256_rotate_right, r1m, x0s, x2m,
                        r0s, mask_c, 2);

  bitsliced_mm_step_2(SC_VERIFY, mm256_xor, mm256_rotate_right);
}



ATTR_TARGET_AVX2
static void mpc_sbox_prove_s256_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                view_t* view, const rvec_t* rvec) {
  mpc_sbox_prove_s256_256(out, in, view, rvec, mask_255_255_85_a->w256, mask_255_255_85_b->w256,
                          mask_255_255_85_c->w256);
}

ATTR_TARGET_AVX2
static void mpc_sbox_verify_s256_lowmc_255_255_4(mzd_local_t* out, const mzd_local_t* in,
                                                 view_t* view, const rvec_t* rvec) {
  mpc_sbox_verify_s256_256(out, in, view, rvec, mask_255_255_85_a->w256, mask_255_255_85_b->w256,
                           mask_255_255_85_c->w256);
}

/* TODO: get rid of the copies */
#define SBOX(sbox, y, x, views, rvec, n, shares, shares2)                                          \
  {                                                                                                \
    mzd_local_t tmp[shares];                                                                       \
    for (unsigned int count = 0; count < shares; ++count) {                                        \
      memcpy(tmp[count].w64, CONST_BLOCK(x[count], 0)->w64, sizeof(mzd_local_t));                  \
    }                                                                                              \
    sbox(tmp, tmp, views, rvec);                                                                   \
    for (unsigned int count = 0; count < shares; ++count) {                                        \
      memcpy(BLOCK(y[count], 0)->w64, tmp[count].w64, sizeof(mzd_local_t));                        \
    }                                                                                              \
  }                                                                                                \
  while (0)

#define SBOX_uint64(sbox, y, x, views, rvec, n, shares, shares2)                                   \
  do {                                                                                             \
    uint64_t in[shares];                                                                           \
    for (unsigned int count = 0; count < shares; ++count) {                                        \
      in[count] = CONST_BLOCK(x[count], 0)->w64[(n) / (sizeof(word) * 8) - 1];                     \
    }                                                                                              \
    sbox(in, views, rvec->t);                                                                      \
    for (unsigned int count = 0; count < shares2; ++count) {                                       \
      memcpy(BLOCK(y[count], 0)->w64, CONST_BLOCK(x[count], 0)->w64,                               \
             ((n) / (sizeof(word) * 8) - 1) * sizeof(word));                                       \
      BLOCK(y[count], 0)->w64[(n) / (sizeof(word) * 8) - 1] = in[count];                           \
    }                                                                                              \
  } while (0)

#if !defined(NO_UINT64_FALLBACK)
#define IMPL uint64

// uint64 based implementation
#include "lowmc_128_128_20_fns_uint64.h"
#include "mpc_lowmc.c.i"

#include "lowmc_129_129_4_fns_uint64.h"
#include "mpc_lowmc.c.i"

#include "lowmc_192_192_30_fns_uint64.h"
#include "mpc_lowmc.c.i"

#include "lowmc_192_192_4_fns_uint64.h"
#include "mpc_lowmc.c.i"

#include "lowmc_256_256_38_fns_uint64.h"
#include "mpc_lowmc.c.i"

#include "lowmc_255_255_4_fns_uint64.h"
#include "mpc_lowmc.c.i"
#endif

#define FN_ATTR ATTR_TARGET_S128
#undef IMPL
#define IMPL s128

// L1 using SSE2/NEON
#include "lowmc_128_128_20_fns_s128.h"
#include "mpc_lowmc.c.i"

#include "lowmc_129_129_4_fns_s128.h"
#include "mpc_lowmc.c.i"

// L3 using SSE2/NEON
#include "lowmc_192_192_30_fns_s128.h"
#include "mpc_lowmc.c.i"

#include "lowmc_192_192_4_fns_s128.h"
#include "mpc_lowmc.c.i"

// L5 using SSE2/NEON
#include "lowmc_256_256_38_fns_s128.h"
#include "mpc_lowmc.c.i"

#include "lowmc_255_255_4_fns_s128.h"
#include "mpc_lowmc.c.i"

#undef FN_ATTR

#define FN_ATTR ATTR_TARGET_AVX2
#undef IMPL
#define IMPL s256

// L1 using AVX2
#include "lowmc_128_128_20_fns_s256.h"
#include "mpc_lowmc.c.i"

#include "lowmc_129_129_4_fns_s256.h"
#include "mpc_lowmc.c.i"

// L3 using AVX2
#include "lowmc_192_192_30_fns_s256.h"
#include "mpc_lowmc.c.i"

#include "lowmc_192_192_4_fns_s256.h"
#include "mpc_lowmc.c.i"

// L5 using AVX2
#include "lowmc_256_256_38_fns_s256.h"
#include "mpc_lowmc.c.i"

#include "lowmc_255_255_4_fns_s256.h"
#include "mpc_lowmc.c.i"

#undef FN_ATTR

zkbpp_lowmc_implementation_f get_zkbpp_lowmc_implementation(const lowmc_parameters_t* lowmc) {
  const uint32_t lowmc_id = LOWMC_GET_ID(lowmc);
  /* AVX2 enabled instances */
  if (CPU_SUPPORTS_AVX2) {
    switch (lowmc_id) {
      /* Instances with partial Sbox layer */
      /* Instances with full Sbox layer */
    case LOWMC_ID(255, 85):
      return mpc_lowmc_prove_s256_lowmc_255_255_4;
    }
  }

  /* SSE2/NEON enabled instances */
  if (CPU_SUPPORTS_SSE2 || CPU_SUPPORTS_NEON) {
    switch (lowmc_id) {
      /* Instances with partial Sbox layer */
      /* Instances with full Sbox layer */
    case LOWMC_ID(255, 85):
      return mpc_lowmc_prove_s128_lowmc_255_255_4;
    }
  }

#if !defined(NO_UINT64_FALLBACK)
  /* uint64_t implementations */
  switch (lowmc_id) {
    /* Instances with partial Sbox layer */
    /* Instances with full Sbox layer */
  case LOWMC_ID(255, 85):
    return mpc_lowmc_prove_uint64_lowmc_255_255_4;
  }
#endif

  UNREACHABLE;
  return NULL;
}

zkbpp_lowmc_verify_implementation_f
get_zkbpp_lowmc_verify_implementation(const lowmc_parameters_t* lowmc) {
  const uint32_t lowmc_id = LOWMC_GET_ID(lowmc);
  /* AVX2 enabled instances */
  if (CPU_SUPPORTS_AVX2) {
    switch (lowmc_id) {
      /* Instances with partial Sbox layer */
      /* Instances with full Sbox layer */
    case LOWMC_ID(255, 85):
      return mpc_lowmc_verify_s256_lowmc_255_255_4;
    }
  }

  /* SSE2/NEON enabled instances */
  if (CPU_SUPPORTS_SSE2 || CPU_SUPPORTS_NEON) {
    switch (lowmc_id) {
      /* Instances with partial Sbox layer */
      /* Instances with full Sbox layer */
    case LOWMC_ID(255, 85):
      return mpc_lowmc_verify_s128_lowmc_255_255_4;
    }
  }

#if !defined(NO_UINT64_FALLBACK)
  /* uint64_t implementations */
  switch (lowmc_id) {
    /* Instances with partial Sbox layer */
    /* Instances with full Sbox layer */
  case LOWMC_ID(255, 85):
    return mpc_lowmc_verify_uint64_lowmc_255_255_4;
  }
#endif

  UNREACHABLE;
  return NULL;
}

#if !defined(NO_UINT64_FALLBACK)
static void mzd_share_uint64_128(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                                 const mzd_local_t* v3) {
  mzd_xor_uint64_128(r, v1, v2);
  mzd_xor_uint64_128(r, r, v3);
}

static void mzd_share_uint64_192(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                                 const mzd_local_t* v3) {
  mzd_xor_uint64_192(r, v1, v2);
  mzd_xor_uint64_192(r, r, v3);
}

static void mzd_share_uint64_256(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                                 const mzd_local_t* v3) {
  mzd_xor_uint64_256(r, v1, v2);
  mzd_xor_uint64_256(r, r, v3);
}
#endif

ATTR_TARGET_S128
static void mzd_share_s128_128(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                               const mzd_local_t* v3) {
  mzd_xor_s128_128(r, v1, v2);
  mzd_xor_s128_128(r, r, v3);
}

ATTR_TARGET_S128
static void mzd_share_s128_256(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                               const mzd_local_t* v3) {
  mzd_xor_s128_256(r, v1, v2);
  mzd_xor_s128_256(r, r, v3);
}

ATTR_TARGET_AVX2
static void mzd_share_s256_128(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                               const mzd_local_t* v3) {
  mzd_xor_s256_128(r, v1, v2);
  mzd_xor_s256_128(r, r, v3);
}

ATTR_TARGET_AVX2
static void mzd_share_s256_256(mzd_local_t* r, const mzd_local_t* v1, const mzd_local_t* v2,
                               const mzd_local_t* v3) {
  mzd_xor_s256_256(r, v1, v2);
  mzd_xor_s256_256(r, r, v3);
}

zkbpp_share_implementation_f get_zkbpp_share_implentation(const lowmc_parameters_t* lowmc) {
  if (CPU_SUPPORTS_AVX2) {
    if (lowmc->n <= 128) {
      return mzd_share_s256_128;
    } else {
      return mzd_share_s256_256;
    }
  }
  if (CPU_SUPPORTS_SSE2 || CPU_SUPPORTS_NEON) {
    if (lowmc->n <= 128) {
      return mzd_share_s128_128;
    } else {
      return mzd_share_s128_256;
    }
  }

#if !defined(NO_UINT64_FALLBACK)
  if (lowmc->n <= 128) {
    return mzd_share_uint64_128;
  } else if (lowmc->n <= 192) {
    return mzd_share_uint64_192;
  } else {
    return mzd_share_uint64_256;
  }
#endif
}
