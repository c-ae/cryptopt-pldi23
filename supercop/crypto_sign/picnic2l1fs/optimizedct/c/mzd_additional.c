/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */


#include "compat.h"
#include "mzd_additional.h"

#if !defined(_MSC_VER)
#include <stdalign.h>
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_MSC_VER) && !defined(static_assert)
#define static_assert _Static_assert
#endif

static_assert(((sizeof(mzd_local_t) + 0x1f) & ~0x1f) == 32, "sizeof mzd_local_t not supported");

static const unsigned int align_bound = 128 / (8 * sizeof(word));

static size_t calculate_rowstride(size_t width) {
  // As soon as we hit the AVX bound, use 32 byte alignment. Otherwise use 16
  // byte alignment for SSE2 and 128 bit vectors.
  if (width > align_bound) {
    return ((width * sizeof(word) + 31) & ~31) / sizeof(word);
  } else {
    return ((width * sizeof(word) + 15) & ~15) / sizeof(word);
  }
}

static size_t calculate_width(size_t c) {
  return (c + sizeof(word) * 8 - 1) / (sizeof(word) * 8);
}

// Notes on the memory layout: mzd_init allocates multiple memory blocks (one
// for mzd_local_t, one for rows and multiple for the buffers). We use one memory
// block for mzd_local_t, rows and the buffer. This improves memory locality and
// requires less calls to malloc.
//
// In mzd_local_init_multiple we do the same, but store n mzd_local_t instances in one
// memory block.

mzd_local_t* mzd_local_init_ex(uint32_t r, uint32_t c, bool clear) {
  const size_t rowstride = calculate_rowstride(calculate_width(c));

  const size_t buffer_size = r * rowstride * sizeof(word);
  const size_t alloc_size  = (buffer_size + 31) & ~31;

  /* We always align mzd_local_ts to 32 bytes. Thus the first row is always
   * aligned to 32 bytes as well. For 128 bit and SSE all other rows are then
   * aligned to 16 bytes. */
  unsigned char* buffer = aligned_alloc(32, alloc_size);
  if (clear) {
    memset(buffer, 0, alloc_size);
  }

  return (mzd_local_t*)buffer;
}

void mzd_local_free(mzd_local_t* v) {
  aligned_free(v);
}

void mzd_local_init_multiple_ex(mzd_local_t** dst, size_t n, uint32_t r, uint32_t c, bool clear) {
  const size_t rowstride = calculate_rowstride(calculate_width(c));

  const size_t buffer_size   = r * rowstride * sizeof(word);
  const size_t size_per_elem = (buffer_size + 31) & ~31;

  unsigned char* full_buffer = aligned_alloc(32, size_per_elem * n);
  if (clear) {
    memset(full_buffer, 0, size_per_elem * n);
  }

  for (size_t s = 0; s < n; ++s, full_buffer += size_per_elem) {
    dst[s] = (mzd_local_t*)full_buffer;
  }
}

void mzd_local_free_multiple(mzd_local_t** vs) {
  if (vs) {
    aligned_free(vs[0]);
  }
}

void mzd_copy_uint64_128(mzd_local_t* dst, mzd_local_t const* src) {
  const block_t* sblock = CONST_BLOCK(src, 0);
  block_t* dblock       = BLOCK(dst, 0);

  for (unsigned int i = 0; i < 2; ++i) {
    dblock->w64[i] = sblock->w64[i];
  }
}

void mzd_copy_uint64_192(mzd_local_t* dst, mzd_local_t const* src) {
  const block_t* sblock = CONST_BLOCK(src, 0);
  block_t* dblock       = BLOCK(dst, 0);

  for (unsigned int i = 0; i < 3; ++i) {
    dblock->w64[i] = sblock->w64[i];
  }
}

void mzd_copy_uint64_256(mzd_local_t* dst, mzd_local_t const* src) {
  const block_t* sblock = CONST_BLOCK(src, 0);
  block_t* dblock       = BLOCK(dst, 0);

  for (unsigned int i = 0; i < 4; ++i) {
    dblock->w64[i] = sblock->w64[i];
  }
}



static void mzd_xor_uint64_block(block_t* rblock, const block_t* fblock, const block_t* sblock,
                                 const unsigned int len) {
  for (unsigned int i = 0; i < len; ++i) {
    rblock->w64[i] = fblock->w64[i] ^ sblock->w64[i];
  }
}

static void mzd_xor_uint64_blocks(block_t* rblock, const block_t* fblock, const block_t* sblock,
                                  const unsigned int len) {
  for (unsigned int i = len; i; --i, ++rblock, ++fblock, ++sblock) {
    mzd_xor_uint64_block(rblock, fblock, sblock, 4);
  }
}

void mzd_xor_uint64_128(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_block(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 2);
}

void mzd_xor_uint64_192(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_block(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 3);
}

void mzd_xor_uint64_256(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_block(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 4);
}

void mzd_xor_uint64_640(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_blocks(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 2);
  mzd_xor_uint64_block(BLOCK(res, 2), CONST_BLOCK(first, 2), CONST_BLOCK(second, 2), 2);
}

void mzd_xor_uint64_960(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_blocks(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 3);
  mzd_xor_uint64_block(BLOCK(res, 3), CONST_BLOCK(first, 3), CONST_BLOCK(second, 3), 3);
}

void mzd_xor_uint64_1216(mzd_local_t* res, mzd_local_t const* first, mzd_local_t const* second) {
  mzd_xor_uint64_blocks(BLOCK(res, 0), CONST_BLOCK(first, 0), CONST_BLOCK(second, 0), 4);
  mzd_xor_uint64_block(BLOCK(res, 4), CONST_BLOCK(first, 4), CONST_BLOCK(second, 4), 3);
}

void mzd_mul_v_parity_uint64_128_30(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* At) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* vblock = CONST_BLOCK(v, 0);

  cblock->w64[0] = 0;

  word res = 0;
  for (unsigned int i = 15; i; --i) {
    const block_t* Ablock = CONST_BLOCK(At, 15 - i);
    const word parity1 =
        parity64_uint64((vblock->w64[0] & Ablock->w64[0]) ^ (vblock->w64[1] & Ablock->w64[1]));
    const word parity2 =
        parity64_uint64((vblock->w64[0] & Ablock->w64[2]) ^ (vblock->w64[1] & Ablock->w64[3]));
    res |= (parity1 | (parity2 << 1)) << (64 - (2 * i));
  }
  cblock->w64[1] = res;
}

void mzd_mul_v_parity_uint64_192_30(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* At) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* vblock = CONST_BLOCK(v, 0);

  for (unsigned int j = 0; j < 2; j++) {
    cblock->w64[j] = 0;
  }

  word res = 0;
  for (unsigned int i = 30; i; --i) {
    const block_t* Ablock = CONST_BLOCK(At, 30 - i);
    const word parity =
        parity64_uint64((vblock->w64[0] & Ablock->w64[0]) ^ (vblock->w64[1] & Ablock->w64[1]) ^
                        (vblock->w64[2] & Ablock->w64[2]));
    res |= parity << (64 - i);
  }
  cblock->w64[2] = res;
}

void mzd_mul_v_parity_uint64_256_30(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* At) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* vblock = CONST_BLOCK(v, 0);

  for (unsigned int j = 0; j < 3; j++) {
    cblock->w64[j] = 0;
  }

  word res = 0;
  for (unsigned int i = 30; i; --i) {
    const block_t* Ablock = CONST_BLOCK(At, 30 - i);
    const word parity =
        parity64_uint64((vblock->w64[0] & Ablock->w64[0]) ^ (vblock->w64[1] & Ablock->w64[1]) ^
                        (vblock->w64[2] & Ablock->w64[2]) ^ (vblock->w64[3] & Ablock->w64[3]));
    res |= parity << (64 - i);
  }
  cblock->w64[3] = res;
}


static void clear_uint64_block(block_t* block, const unsigned int idx) {
  for (unsigned int i = 0; i < idx; ++i) {
    block->w64[i] = 0;
  }
}

static void clear_uint64_blocks(block_t* block, unsigned int len) {
  for (; len; --len, ++block) {
    clear_uint64_block(block, 4);
  }
}

static void mzd_xor_mask_uint64_block(block_t* rblock, const block_t* fblock, const word mask,
                                      const unsigned int idx) {
  for (unsigned int i = 0; i < idx; ++i) {
    rblock->w64[i] ^= fblock->w64[i] & mask;
  }
}

void mzd_addmul_v_uint64_128(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  for (unsigned int w = 2; w; --w, ++vptr) {
    word idx = *vptr;
    for (unsigned int i = sizeof(word) * 8; i; i -= 2, idx >>= 2, Ablock += 1) {
      const uint64_t mask1 = -(idx & 1);
      const uint64_t mask2 = -((idx >> 1) & 1);
      cblock->w64[0] ^= (Ablock->w64[0] & mask1) ^ (Ablock->w64[2] & mask2);
      cblock->w64[1] ^= (Ablock->w64[1] & mask1) ^ (Ablock->w64[3] & mask2);
    }
  }
}

void mzd_mul_v_uint64_128(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  clear_uint64_block(BLOCK(c, 0), 2);
  mzd_addmul_v_uint64_128(c, v, A);
}

void mzd_addmul_v_uint64_192(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  for (unsigned int w = 3; w; --w, ++vptr) {
    word idx = *vptr;
    for (unsigned int i = sizeof(word) * 8; i; --i, idx >>= 1, ++Ablock) {
      const uint64_t mask = -(idx & 1);
      mzd_xor_mask_uint64_block(cblock, Ablock, mask, 3);
    }
  }
}

void mzd_mul_v_uint64_192(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  clear_uint64_block(BLOCK(c, 0), 3);
  mzd_addmul_v_uint64_192(c, v, A);
}

void mzd_addmul_v_uint64_256(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  for (unsigned int w = 4; w; --w, ++vptr) {
    word idx = *vptr;

    for (unsigned int i = sizeof(word) * 8; i; --i, idx >>= 1, ++Ablock) {
      const uint64_t mask = -(idx & 1);
      mzd_xor_mask_uint64_block(cblock, Ablock, mask, 4);
    }
  }
}

void mzd_mul_v_uint64_256(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  clear_uint64_block(BLOCK(c, 0), 4);
  mzd_addmul_v_uint64_256(c, v, A);
}

void mzd_mul_v_uint64_128_640(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  clear_uint64_blocks(BLOCK(c, 0), 2);
  clear_uint64_block(BLOCK(c, 2), 2);

  for (unsigned int w = 2; w; --w, ++vptr) {
    word idx = *vptr;
    for (unsigned int i = sizeof(word) * 8; i; --i, idx >>= 1, ++Ablock) {
      const uint64_t mask = -(idx & 1);
      for (unsigned int j = 0; j < 2; ++j, ++Ablock) {
        mzd_xor_mask_uint64_block(BLOCK(c, j), Ablock, mask, 4);
      }
      mzd_xor_mask_uint64_block(BLOCK(c, 2), Ablock, mask, 2);
    }
  }
}

void mzd_mul_v_uint64_192_960(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  clear_uint64_blocks(BLOCK(c, 0), 3);
  clear_uint64_block(BLOCK(c, 3), 3);

  for (unsigned int w = 3; w; --w, ++vptr) {
    word idx = *vptr;
    for (unsigned int i = sizeof(word) * 8; i; --i, idx >>= 1, ++Ablock) {
      const uint64_t mask = -(idx & 1);
      for (unsigned int j = 0; j < 3; ++j, ++Ablock) {
        mzd_xor_mask_uint64_block(BLOCK(c, j), Ablock, mask, 4);
      }
      mzd_xor_mask_uint64_block(BLOCK(c, 3), Ablock, mask, 3);
    }
  }
}

void mzd_mul_v_uint64_256_1216(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  const word* vptr      = CONST_BLOCK(v, 0)->w64;
  const block_t* Ablock = CONST_BLOCK(A, 0);

  clear_uint64_blocks(BLOCK(c, 0), 4);
  clear_uint64_block(BLOCK(c, 4), 3);

  for (unsigned int w = 4; w; --w, ++vptr) {
    word idx = *vptr;
    for (unsigned int i = sizeof(word) * 8; i; --i, idx >>= 1, ++Ablock) {
      const uint64_t mask = -(idx & 1);
      for (unsigned int j = 0; j < 4; ++j, ++Ablock) {
        mzd_xor_mask_uint64_block(BLOCK(c, j), Ablock, mask, 4);
      }
      mzd_xor_mask_uint64_block(BLOCK(c, 4), Ablock, mask, 3);
    }
  }
}

// specific instances
// bit extract, non-constant time for mask, but mask is public in our calls
static word extract_bits(word in, word mask) {
  word res = 0;
  for (word bb = 1; mask != 0; bb <<= 1, mask &= (mask - 1)) {
    res |= bb & (-((word) !!(in & mask & -mask)));
  }
  return res;
}

static inline void mzd_shuffle_30_idx(mzd_local_t* x, const word mask, unsigned int idx) {
  const word w          = CONST_BLOCK(x, 0)->w64[idx];
  const word a          = extract_bits(w, mask) << 34;
  BLOCK(x, 0)->w64[idx] = a | extract_bits(w, ~mask);
}

void mzd_shuffle_128_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_30_idx(x, mask, 1);
}

void mzd_shuffle_192_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_30_idx(x, mask, 2);
}

void mzd_shuffle_256_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_30_idx(x, mask, 3);
}

// no SIMD
void mzd_addmul_v_uint64_30_128(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);

  word idx = CONST_BLOCK(v, 0)->w64[1] >> 34;
  for (unsigned int i = 15; i; --i, idx >>= 2, ++Ablock) {
    const uint64_t mask1 = -(idx & 1);
    const uint64_t mask2 = -((idx >> 1) & 1);
    for (unsigned int j = 0; j < 2; ++j) {
      cblock->w64[j] ^= (Ablock->w64[j] & mask1) ^ (Ablock->w64[j + 2] & mask2);
    }
  }
}

void mzd_addmul_v_uint64_30_192(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);

  word idx = CONST_BLOCK(v, 0)->w64[2] >> 34;
  for (unsigned int i = 30; i; --i, idx >>= 1, ++Ablock) {
    const uint64_t mask = -(idx & 1);
    mzd_xor_mask_uint64_block(cblock, Ablock, mask, 3);
  }
}

void mzd_addmul_v_uint64_30_256(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);

  word idx = CONST_BLOCK(v, 0)->w64[3] >> 34;
  for (unsigned int i = 30; i; --i, idx >>= 1, ++Ablock) {
    const uint64_t mask = -(idx & 1);
    mzd_xor_mask_uint64_block(cblock, Ablock, mask, 4);
  }
}

#if defined(WITH_SSE2) || defined(WITH_NEON)
ATTR_TARGET_S128
void mzd_addmul_v_s128_30_128(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);
  word idx              = CONST_BLOCK(v, 0)->w64[1] >> 34;

  word128 cval[2] ATTR_ALIGNED(alignof(word128));
  cval[0] = mm128_xor_mask(cblock->w128[0], Ablock[0].w128[0], mm128_compute_mask(idx, 0));
  cval[1] = mm128_and(Ablock[0].w128[1], mm128_compute_mask(idx, 1));
  idx >>= 2;
  Ablock += 1;

  for (unsigned int i = 28; i; i -= 4, idx >>= 4, Ablock += 2) {
    cval[0] = mm128_xor_mask(cval[0], Ablock[0].w128[0], mm128_compute_mask(idx, 0));
    cval[1] = mm128_xor_mask(cval[1], Ablock[0].w128[1], mm128_compute_mask(idx, 1));
    cval[0] = mm128_xor_mask(cval[0], Ablock[1].w128[0], mm128_compute_mask(idx, 2));
    cval[1] = mm128_xor_mask(cval[1], Ablock[1].w128[1], mm128_compute_mask(idx, 3));
  }
  cblock->w128[0] = mm128_xor(cval[0], cval[1]);
}

ATTR_TARGET_S128
static void mzd_addmul_v_s128_30_256_idx(mzd_local_t* c, mzd_local_t const* A, word idx) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);

  word128 cval[4] ATTR_ALIGNED(alignof(word128)) = {cblock->w128[0], cblock->w128[1], mm128_zero,
                                                    mm128_zero};
  for (unsigned int i = 30; i; i -= 2, idx >>= 2, Ablock += 2) {
    mm128_xor_mask_region(&cval[0], Ablock[0].w128, mm128_compute_mask(idx, 0), 2);
    mm128_xor_mask_region(&cval[2], Ablock[1].w128, mm128_compute_mask(idx, 1), 2);
  }
  cblock->w128[0] = mm128_xor(cval[0], cval[2]);
  cblock->w128[1] = mm128_xor(cval[1], cval[3]);
}

ATTR_TARGET_S128
void mzd_addmul_v_s128_30_192(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  mzd_addmul_v_s128_30_256_idx(c, A, CONST_BLOCK(v, 0)->w64[2] >> 34);
}

ATTR_TARGET_S128
void mzd_addmul_v_s128_30_256(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  mzd_addmul_v_s128_30_256_idx(c, A, CONST_BLOCK(v, 0)->w64[3] >> 34);
}

#endif

#if defined(WITH_AVX2)
ATTR_TARGET_AVX2
void mzd_addmul_v_s256_30_128(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* vblock = CONST_BLOCK(v, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);
  word idx              = vblock->w64[1] >> 34;

  word256 cval[2] ATTR_ALIGNED(alignof(word256));
  cval[0] = mm256_xor_mask(_mm256_castsi128_si256(cblock->w128[0]), Ablock[0].w256,
                           mm256_compute_mask_2(idx, 0));
  cval[1] = mm256_and(Ablock[1].w256, mm256_compute_mask_2(idx, 2));
  idx >>= 4;
  Ablock += 2;

  for (unsigned int i = 24; i; i -= 8, idx >>= 8, Ablock += 4) {
    cval[0] = mm256_xor_mask(cval[0], Ablock[0].w256, mm256_compute_mask_2(idx, 0));
    cval[1] = mm256_xor_mask(cval[1], Ablock[1].w256, mm256_compute_mask_2(idx, 2));
    cval[0] = mm256_xor_mask(cval[0], Ablock[2].w256, mm256_compute_mask_2(idx, 4));
    cval[1] = mm256_xor_mask(cval[1], Ablock[3].w256, mm256_compute_mask_2(idx, 6));
  }
  cval[0] = mm256_xor_mask(cval[0], Ablock[0].w256, mm256_compute_mask_2(idx, 0));

  cval[0] = mm256_xor(cval[0], cval[1]);
  cblock->w128[0] =
      mm128_xor(_mm256_extractf128_si256(cval[0], 0), _mm256_extractf128_si256(cval[0], 1));
}

ATTR_TARGET_AVX2
static inline void mzd_addmul_v_s256_30_256_idx(mzd_local_t* c, mzd_local_t const* A, word idx) {
  block_t* cblock       = BLOCK(c, 0);
  const block_t* Ablock = CONST_BLOCK(A, 0);

  word256 cval[2] ATTR_ALIGNED(alignof(word256));
  cval[0] = mm256_xor_mask(cblock->w256, Ablock[0].w256, mm256_compute_mask(idx, 0));
  cval[1] = mm256_and(Ablock[1].w256, mm256_compute_mask(idx, 1));
  idx >>= 2;
  Ablock += 2;

  for (unsigned int i = 28; i; i -= 4, idx >>= 4, Ablock += 4) {
    cval[0] = mm256_xor_mask(cval[0], Ablock[0].w256, mm256_compute_mask(idx, 0));
    cval[1] = mm256_xor_mask(cval[1], Ablock[1].w256, mm256_compute_mask(idx, 1));
    cval[0] = mm256_xor_mask(cval[0], Ablock[2].w256, mm256_compute_mask(idx, 2));
    cval[1] = mm256_xor_mask(cval[1], Ablock[3].w256, mm256_compute_mask(idx, 3));
  }
  cblock->w256 = mm256_xor(cval[0], cval[1]);
}

ATTR_TARGET_AVX2
void mzd_addmul_v_s256_30_192(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  mzd_addmul_v_s256_30_256_idx(c, A, CONST_BLOCK(v, 0)->w64[2] >> 34);
}

ATTR_TARGET_AVX2
void mzd_addmul_v_s256_30_256(mzd_local_t* c, mzd_local_t const* v, mzd_local_t const* A) {
  mzd_addmul_v_s256_30_256_idx(c, A, CONST_BLOCK(v, 0)->w64[3] >> 34);
}

#if !defined(__x86_64__) && !defined(_M_X64)
ATTR_TARGET_AVX2 ATTR_CONST static uint8_t popcount_32(uint32_t value) {
  uint64_t result =
      ((value & 0xfff) * UINT64_C(0x1001001001001) & UINT64_C(0x84210842108421)) % 0x1f;
  result +=
      (((value & 0xfff000) >> 12) * UINT64_C(0x1001001001001) & UINT64_C(0x84210842108421)) % 0x1f;
  result += ((value >> 24) * UINT64_C(0x1001001001001) & UINT64_C(0x84210842108421)) % 0x1f;
  return result;
}

ATTR_TARGET_AVX2 ATTR_CONST static uint64_t _pext_u64(uint64_t a, uint64_t mask) {
  const uint32_t low  = _pext_u32(a, mask);
  const uint32_t high = _pext_u32(a >> 32, mask >> 32);

  return (((uint64_t)high) << popcount_32(mask)) | low;
}
#endif

ATTR_TARGET_AVX2
static inline void mzd_shuffle_pext_30_idx(mzd_local_t* x, const word mask, unsigned int idx) {
  const word w          = CONST_BLOCK(x, 0)->w64[idx];
  const word a          = _pext_u64(w, mask) << 34;
  BLOCK(x, 0)->w64[idx] = a | _pext_u64(w, ~mask);
}

ATTR_TARGET_AVX2
void mzd_shuffle_pext_128_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_pext_30_idx(x, mask, 1);
}

ATTR_TARGET_AVX2
void mzd_shuffle_pext_192_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_pext_30_idx(x, mask, 2);
}

ATTR_TARGET_AVX2
void mzd_shuffle_pext_256_30(mzd_local_t* x, const word mask) {
  mzd_shuffle_pext_30_idx(x, mask, 3);
}
#endif
