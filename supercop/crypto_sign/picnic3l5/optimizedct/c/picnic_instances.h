/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifndef PICNIC_INSTANCES_H
#define PICNIC_INSTANCES_H

#include "lowmc.h"
#include "picnic3_simulate.h"
#include "picnic.h"

#define SALT_SIZE 32

/* max digest and seed size */
#define MAX_DIGEST_SIZE 64
#define MAX_SEED_SIZE 32

typedef struct picnic_instance_t {
  const lowmc_parameters_t lowmc;
  const uint16_t num_rounds;       // T
  const uint8_t digest_size;       // bytes
  const uint8_t seed_size;         // bytes
  const uint8_t input_output_size; // bytes
  const uint8_t view_size;         // bytes
  const uint8_t num_opened_rounds; // u (KKW only)
  const uint8_t num_MPC_parties;   // N (KKW only)
} picnic_instance_t;

ATTR_PURE const picnic_instance_t* picnic_instance_get(picnic_params_t param);

ATTR_CONST static inline bool picnic_instance_is_unruh(picnic_params_t param) {
  return param == Picnic_L1_UR || param == Picnic_L3_UR || param == Picnic_L5_UR;
}

PICNIC_EXPORT size_t PICNIC_CALLING_CONVENTION picnic_get_lowmc_block_size(picnic_params_t param);

/* Prefix values for domain separation */
static const uint8_t HASH_PREFIX_0 = 0;
static const uint8_t HASH_PREFIX_1 = 1;
static const uint8_t HASH_PREFIX_2 = 2;
static const uint8_t HASH_PREFIX_3 = 3;
static const uint8_t HASH_PREFIX_4 = 4;
static const uint8_t HASH_PREFIX_5 = 5;

#endif
