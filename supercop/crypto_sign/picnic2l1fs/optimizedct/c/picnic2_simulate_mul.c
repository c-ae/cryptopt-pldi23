/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#include <assert.h>
#include <string.h>

#include "endian_compat.h"
#include "picnic2_simulate_mul.h"

#if defined(WITH_SSE2)
#define ATTR_TARGET_S128 ATTR_TARGET_SSE2
#else
#define ATTR_TARGET_S128
#endif

static const block_t block_masks[] = {
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
};

static const block_t nl_part_block_masks[] = {
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0x0000000000000000),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
    {{
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
        UINT64_C(0xffffffffffffffff),
    }},
};


/* transpose a 64x64 bit matrix using Eklundh's algorithm
   this variant assumes that the bit with index 0 is the msb of byte 0
   e.g., 01234567 89abcdef ...
 */
static void transpose_64_64_uint64(const uint64_t* in, uint64_t* out) {
  static const uint64_t TRANSPOSE_MASKS64[6] = {
      UINT64_C(0xFFFFFFFF00000000), UINT64_C(0xFFFF0000FFFF0000), UINT64_C(0xFF00FF00FF00FF00),
      UINT64_C(0xF0F0F0F0F0F0F0F0), UINT64_C(0xCCCCCCCCCCCCCCCC), UINT64_C(0xAAAAAAAAAAAAAAAA)};

  uint32_t width = 32, nswaps = 1;
  const uint32_t logn = 6;

  // copy in to out and transpose in-place
  for (uint32_t i = 0; i < 64; i++) {
    out[i] = htobe64(in[i]);
  }

  for (uint32_t i = 0; i < logn; i++) {
    uint64_t mask     = TRANSPOSE_MASKS64[i];
    uint64_t inv_mask = ~mask;

    for (uint32_t j = 0; j < nswaps; j++) {
      for (uint32_t k = 0; k < width; k++) {
        uint32_t i1 = k + 2 * width * j;
        uint32_t i2 = k + width + 2 * width * j;

        uint64_t t1 = out[i1];
        uint64_t t2 = out[i2];

        out[i1] = (t1 & mask) ^ ((t2 & mask) >> width);
        out[i2] = (t2 & inv_mask) ^ ((t1 & inv_mask) << width);
      }
    }
    nswaps *= 2;
    width /= 2;
  }
  for (uint32_t i = 0; i < 64; i++) {
    out[i] = be64toh(out[i]);
  }
}


void transpose_64_64(const uint64_t* in, uint64_t* out) {
  transpose_64_64_uint64(in, out);
}

uint64_t tapesToParityOfWord(randomTape_t* tapes, uint8_t without_last) {
  uint64_t shares;

  if (tapes->pos % 64 == 0) {
    tapes->buffer[0] = 0;
    for (size_t i = 0; i < 63; i++) {
      tapes->buffer[0] ^= ((uint64_t*)tapes->tape[i])[tapes->pos / 64];
    }
    tapes->buffer[1] = tapes->buffer[0];
    tapes->buffer[0] ^= ((uint64_t*)tapes->tape[63])[tapes->pos / 64];
  }

  shares = getBit((uint8_t*)&tapes->buffer[without_last ? 1 : 0], tapes->pos % 64);
  tapes->pos++;
  return shares;
}

uint64_t tapesToWord(randomTape_t* tapes) {
  uint64_t shares;

  if (tapes->pos % 64 == 0) {
    for (size_t i = 0; i < 64; i++) {
      tapes->buffer[i] = ((uint64_t*)tapes->tape[i])[tapes->pos / 64];
    }
    transpose_64_64(tapes->buffer, tapes->buffer);
  }

  shares = tapes->buffer[tapes->pos % 64];
  tapes->pos++;
  return shares;
}

void reconstructShares(uint32_t* output, shares_t* shares) {
  for (size_t i = 0; i < shares->numWords; i++) {
    setBit((uint8_t*)output, i, parity64_uint64(shares->shares[i]));
  }
}

void xor_word_array(uint32_t* out, const uint32_t* in1, const uint32_t* in2, uint32_t length) {
  for (uint32_t i = 0; i < length; i++) {
    out[i] = in1[i] ^ in2[i];
  }
}

/* Get one bit from a byte array */
uint8_t getBit(const uint8_t* array, uint32_t bitNumber) {
  return (array[bitNumber / 8] >> (7 - (bitNumber % 8))) & 0x01;
}

/* Set a specific bit in a byte array to a given value */
void setBit(uint8_t* bytes, uint32_t bitNumber, uint8_t val) {
  bytes[bitNumber / 8] =
      (bytes[bitNumber >> 3] & ~(1 << (7 - (bitNumber % 8)))) | (val << (7 - (bitNumber % 8)));
}

void copyShares(shares_t* dst, shares_t* src) {
  assert(dst->numWords == src->numWords);
  memcpy(dst->shares, src->shares, dst->numWords * sizeof(dst->shares[0]));
}

void mpc_matrix_mul_uint64_128(mzd_local_t* output, const mzd_local_t* vec,
                               const mzd_local_t* matrix, shares_t* mask_shares) {
  const uint32_t rowstride = (128) / (sizeof(word) * 8);
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);

  for (size_t i = 0; i < 128; i++) {
    const uint64_t mask_share = mask_shares->shares[128 - 1 - i];

    for (uint32_t j = 0; j < 128; j += 8) {
      uint8_t matrix_byte  = matrix->w64[(i * rowstride) + (128 - 1 - j) / 64] >> (56 - (j % 64));
      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_local_t tmp;
  mzd_copy_uint64_128(&tmp, vec);
  mzd_mul_v_uint64_128(output, &tmp, matrix);

  copyShares(mask_shares, tmp_mask);
  freeShares(tmp_mask);
}

void mpc_matrix_mul_uint64_192(mzd_local_t* output, const mzd_local_t* vec,
                               const mzd_local_t* matrix, shares_t* mask_shares) {
  const uint32_t rowstride = (256) / (8 * sizeof(word));
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);

  for (size_t i = 0; i < 192; i++) {
    const uint64_t mask_share = mask_shares->shares[192 - 1 - i];

    for (uint32_t j = 0; j < 192; j += 8) {
      uint8_t matrix_byte = matrix->w64[(i * rowstride) + (192 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_local_t tmp;
  mzd_copy_uint64_192(&tmp, vec);
  mzd_mul_v_uint64_192(output, &tmp, matrix);

  copyShares(mask_shares, tmp_mask);
  freeShares(tmp_mask);
}
void mpc_matrix_mul_uint64_256(mzd_local_t* output, const mzd_local_t* vec,
                               const mzd_local_t* matrix, shares_t* mask_shares) {
  const uint32_t rowstride = (256) / (8 * sizeof(word));
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);

  for (size_t i = 0; i < 256; i++) {
    const uint64_t mask_share = mask_shares->shares[256 - 1 - i];

    for (uint32_t j = 0; j < 256; j += 8) {
      uint8_t matrix_byte = matrix->w64[(i * rowstride) + (256 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_local_t tmp;
  mzd_copy_uint64_256(&tmp, vec);
  mzd_mul_v_uint64_256(output, &tmp, matrix);

  copyShares(mask_shares, tmp_mask);
  freeShares(tmp_mask);
}

void mpc_matrix_mul_z_uint64_128(mzd_local_t* state2, const mzd_local_t* state,
                                 shares_t* mask2_shares, const shares_t* mask_shares,
                                 const mzd_local_t* matrix) {
  const uint32_t rowstride = (128) / (8 * sizeof(word));
  memset(mask2_shares->shares, 0, sizeof(uint64_t) * 128);
  for (size_t i = 0; i < 30; i++) {
    uint64_t new_mask_i = 0;
    for (uint32_t j = 0; j < 128; j += 8) {
      uint8_t matrix_byte = matrix->w64[i * rowstride + (128 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      new_mask_i ^= mask_shares->shares[j + 0] & mask1->w64[0];
      new_mask_i ^= mask_shares->shares[j + 1] & mask1->w64[1];
      new_mask_i ^= mask_shares->shares[j + 2] & mask1->w64[2];
      new_mask_i ^= mask_shares->shares[j + 3] & mask1->w64[3];
      new_mask_i ^= mask_shares->shares[j + 4] & mask2->w64[0];
      new_mask_i ^= mask_shares->shares[j + 5] & mask2->w64[1];
      new_mask_i ^= mask_shares->shares[j + 6] & mask2->w64[2];
      new_mask_i ^= mask_shares->shares[j + 7] & mask2->w64[3];
    }
    mask2_shares->shares[30 - 1 - i] = new_mask_i;
  }
  mzd_mul_v_parity_uint64_128_30(state2, state, matrix);
}

void mpc_matrix_mul_z_uint64_192(mzd_local_t* state2, const mzd_local_t* state,
                                 shares_t* mask2_shares, const shares_t* mask_shares,
                                 const mzd_local_t* matrix) {
  const uint32_t rowstride = (256) / (8 * sizeof(word));
  memset(mask2_shares->shares, 0, sizeof(uint64_t) * 192);
  for (size_t i = 0; i < 30; i++) {
    uint64_t new_mask_i = 0;
    for (uint32_t j = 0; j < 192; j += 8) {
      uint8_t matrix_byte = matrix->w64[i * rowstride + (192 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      new_mask_i ^= mask_shares->shares[j + 0] & mask1->w64[0];
      new_mask_i ^= mask_shares->shares[j + 1] & mask1->w64[1];
      new_mask_i ^= mask_shares->shares[j + 2] & mask1->w64[2];
      new_mask_i ^= mask_shares->shares[j + 3] & mask1->w64[3];
      new_mask_i ^= mask_shares->shares[j + 4] & mask2->w64[0];
      new_mask_i ^= mask_shares->shares[j + 5] & mask2->w64[1];
      new_mask_i ^= mask_shares->shares[j + 6] & mask2->w64[2];
      new_mask_i ^= mask_shares->shares[j + 7] & mask2->w64[3];
    }
    mask2_shares->shares[30 - 1 - i] = new_mask_i;
  }
  mzd_mul_v_parity_uint64_192_30(state2, state, matrix);
}

void mpc_matrix_mul_z_uint64_256(mzd_local_t* state2, const mzd_local_t* state,
                                 shares_t* mask2_shares, const shares_t* mask_shares,
                                 const mzd_local_t* matrix) {
  const uint32_t rowstride = (256) / (8 * sizeof(word));
  memset(mask2_shares->shares, 0, sizeof(uint64_t) * 256);
  for (size_t i = 0; i < 30; i++) {
    uint64_t new_mask_i = 0;
    for (uint32_t j = 0; j < 256; j += 8) {
      uint8_t matrix_byte = matrix->w64[i * rowstride + (256 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      new_mask_i ^= mask_shares->shares[j + 0] & mask1->w64[0];
      new_mask_i ^= mask_shares->shares[j + 1] & mask1->w64[1];
      new_mask_i ^= mask_shares->shares[j + 2] & mask1->w64[2];
      new_mask_i ^= mask_shares->shares[j + 3] & mask1->w64[3];
      new_mask_i ^= mask_shares->shares[j + 4] & mask2->w64[0];
      new_mask_i ^= mask_shares->shares[j + 5] & mask2->w64[1];
      new_mask_i ^= mask_shares->shares[j + 6] & mask2->w64[2];
      new_mask_i ^= mask_shares->shares[j + 7] & mask2->w64[3];
    }
    mask2_shares->shares[30 - 1 - i] = new_mask_i;
  }
  mzd_mul_v_parity_uint64_256_30(state2, state, matrix);
}

void mpc_matrix_addmul_r_uint64_128(mzd_local_t* state2, const mzd_local_t* state,
                                    shares_t* mask2_shares, shares_t* mask_shares,
                                    const mzd_local_t* matrix) {
  const uint32_t rowstride = (128) / (8 * sizeof(word));
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);
  copyShares(tmp_mask, mask2_shares);

  for (size_t i = 0; i < 30; i++) {
    const uint64_t mask_share = mask_shares->shares[30 - 1 - i];

    for (uint32_t j = 0; j < 128; j += 8) {
      uint8_t matrix_byte = matrix->w64[(i * rowstride) + (128 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_addmul_v_uint64_30_128(state2, state, matrix);

  copyShares(mask2_shares, tmp_mask);
  freeShares(tmp_mask);
}

void mpc_matrix_addmul_r_uint64_192(mzd_local_t* state2, const mzd_local_t* state,
                                    shares_t* mask2_shares, shares_t* mask_shares,
                                    const mzd_local_t* matrix) {
  const uint32_t rowstride = 256 / (8 * sizeof(word));
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);
  copyShares(tmp_mask, mask2_shares);

  for (size_t i = 0; i < 30; i++) {
    const uint64_t mask_share = mask_shares->shares[30 - 1 - i];

    for (uint32_t j = 0; j < 192; j += 8) {
      uint8_t matrix_byte = matrix->w64[(i * rowstride) + (192 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_addmul_v_uint64_30_192(state2, state, matrix);

  copyShares(mask2_shares, tmp_mask);
  freeShares(tmp_mask);
}

void mpc_matrix_addmul_r_uint64_256(mzd_local_t* state2, const mzd_local_t* state,
                                    shares_t* mask2_shares, shares_t* mask_shares,
                                    const mzd_local_t* matrix) {
  const uint32_t rowstride = (256) / (8 * sizeof(word));
  shares_t* tmp_mask       = allocateShares(mask_shares->numWords);
  copyShares(tmp_mask, mask2_shares);

  for (size_t i = 0; i < 30; i++) {
    const uint64_t mask_share = mask_shares->shares[30 - 1 - i];

    for (uint32_t j = 0; j < 256; j += 8) {
      uint8_t matrix_byte = matrix->w64[(i * rowstride) + (256 - 1 - j) / 64] >> (56 - (j % 64));

      const block_t* mask1 = &block_masks[(matrix_byte >> 4) & 0xF];
      const block_t* mask2 = &block_masks[(matrix_byte >> 0) & 0xF];

      tmp_mask->shares[j + 0] ^= mask_share & mask1->w64[0];
      tmp_mask->shares[j + 1] ^= mask_share & mask1->w64[1];
      tmp_mask->shares[j + 2] ^= mask_share & mask1->w64[2];
      tmp_mask->shares[j + 3] ^= mask_share & mask1->w64[3];
      tmp_mask->shares[j + 4] ^= mask_share & mask2->w64[0];
      tmp_mask->shares[j + 5] ^= mask_share & mask2->w64[1];
      tmp_mask->shares[j + 6] ^= mask_share & mask2->w64[2];
      tmp_mask->shares[j + 7] ^= mask_share & mask2->w64[3];
    }
  }
  mzd_addmul_v_uint64_30_256(state2, state, matrix);

  copyShares(mask2_shares, tmp_mask);
  freeShares(tmp_mask);
}

void mpc_matrix_mul_nl_part_uint64_128(mzd_local_t* nl_part, const mzd_local_t* key,
                                       const mzd_local_t* precomputed_nl_matrix,
                                       const mzd_local_t* precomputed_constant_nl,
                                       shares_t* nl_part_masks, const shares_t* key_masks) {

  const uint32_t rowstride = ((20 * 32 + 255) / 256 * 256) / (8 * sizeof(word));
  for (size_t i = 0; i < 128; i++) {
    const uint64_t key_mask = key_masks->shares[128 - 1 - i];

    for (uint32_t j = 0; j < 20 * 32; j += 8) {
      uint8_t matrix_byte = precomputed_nl_matrix->w64[(i * rowstride) + j / 64] >> (j % 64);

      const block_t* mask1 = &nl_part_block_masks[(matrix_byte >> 0) & 0xF];
      const block_t* mask2 = &nl_part_block_masks[(matrix_byte >> 4) & 0xF];

      nl_part_masks->shares[j + 0] ^= key_mask & mask1->w64[0];
      nl_part_masks->shares[j + 1] ^= key_mask & mask1->w64[1];
      nl_part_masks->shares[j + 2] ^= key_mask & mask1->w64[2];
      nl_part_masks->shares[j + 3] ^= key_mask & mask1->w64[3];
      nl_part_masks->shares[j + 4] ^= key_mask & mask2->w64[0];
      nl_part_masks->shares[j + 5] ^= key_mask & mask2->w64[1];
      nl_part_masks->shares[j + 6] ^= key_mask & mask2->w64[2];
      nl_part_masks->shares[j + 7] ^= key_mask & mask2->w64[3];
    }
  }
  mzd_mul_v_uint64_128_640(nl_part, key, precomputed_nl_matrix);
  mzd_xor_uint64_640(nl_part, nl_part, precomputed_constant_nl);
}

void mpc_matrix_mul_nl_part_uint64_192(mzd_local_t* nl_part, const mzd_local_t* key,
                                       const mzd_local_t* precomputed_nl_matrix,
                                       const mzd_local_t* precomputed_constant_nl,
                                       shares_t* nl_part_masks, const shares_t* key_masks) {

  const uint32_t rowstride = ((30 * 32 + 255) / 256 * 256) / (8 * sizeof(word));
  for (size_t i = 0; i < 192; i++) {
    const uint64_t key_mask = key_masks->shares[192 - 1 - i];

    for (uint32_t j = 0; j < 30 * 32; j += 8) {
      uint8_t matrix_byte = precomputed_nl_matrix->w64[(i * rowstride) + j / 64] >> (j % 64);

      const block_t* mask1 = &nl_part_block_masks[(matrix_byte >> 0) & 0xF];
      const block_t* mask2 = &nl_part_block_masks[(matrix_byte >> 4) & 0xF];

      nl_part_masks->shares[j + 0] ^= key_mask & mask1->w64[0];
      nl_part_masks->shares[j + 1] ^= key_mask & mask1->w64[1];
      nl_part_masks->shares[j + 2] ^= key_mask & mask1->w64[2];
      nl_part_masks->shares[j + 3] ^= key_mask & mask1->w64[3];
      nl_part_masks->shares[j + 4] ^= key_mask & mask2->w64[0];
      nl_part_masks->shares[j + 5] ^= key_mask & mask2->w64[1];
      nl_part_masks->shares[j + 6] ^= key_mask & mask2->w64[2];
      nl_part_masks->shares[j + 7] ^= key_mask & mask2->w64[3];
    }
  }
  mzd_mul_v_uint64_192_960(nl_part, key, precomputed_nl_matrix);
  mzd_xor_uint64_960(nl_part, nl_part, precomputed_constant_nl);
}

void mpc_matrix_mul_nl_part_uint64_256(mzd_local_t* nl_part, const mzd_local_t* key,
                                       const mzd_local_t* precomputed_nl_matrix,
                                       const mzd_local_t* precomputed_constant_nl,
                                       shares_t* nl_part_masks, const shares_t* key_masks) {

  const uint32_t rowstride = ((38 * 32 + 255) / 256 * 256) / (8 * sizeof(word));
  for (size_t i = 0; i < 256; i++) {
    const uint64_t key_mask = key_masks->shares[256 - 1 - i];

    for (uint32_t j = 0; j < 38 * 32; j += 8) {
      uint8_t matrix_byte = precomputed_nl_matrix->w64[(i * rowstride) + j / 64] >> (j % 64);

      const block_t* mask1 = &nl_part_block_masks[(matrix_byte >> 0) & 0xF];
      const block_t* mask2 = &nl_part_block_masks[(matrix_byte >> 4) & 0xF];

      nl_part_masks->shares[j + 0] ^= key_mask & mask1->w64[0];
      nl_part_masks->shares[j + 1] ^= key_mask & mask1->w64[1];
      nl_part_masks->shares[j + 2] ^= key_mask & mask1->w64[2];
      nl_part_masks->shares[j + 3] ^= key_mask & mask1->w64[3];
      nl_part_masks->shares[j + 4] ^= key_mask & mask2->w64[0];
      nl_part_masks->shares[j + 5] ^= key_mask & mask2->w64[1];
      nl_part_masks->shares[j + 6] ^= key_mask & mask2->w64[2];
      nl_part_masks->shares[j + 7] ^= key_mask & mask2->w64[3];
    }
  }
  mzd_mul_v_uint64_256_1216(nl_part, key, precomputed_nl_matrix);
  mzd_xor_uint64_1216(nl_part, nl_part, precomputed_constant_nl);
}

