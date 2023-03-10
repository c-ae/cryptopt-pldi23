/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */


#include "picnic_instances.h"

// Prefix values for domain separation
const uint8_t HASH_PREFIX_0 = 0;
const uint8_t HASH_PREFIX_1 = 1;
const uint8_t HASH_PREFIX_2 = 2;
const uint8_t HASH_PREFIX_3 = 3;
const uint8_t HASH_PREFIX_4 = 4;
const uint8_t HASH_PREFIX_5 = 5;

// instance handling

// L1, L3, and L5 LowMC instances
#define LOWMC_L1_OR_NULL NULL
#include "lowmc_192_192_30.h"
#define LOWMC_L3_OR_NULL &lowmc_192_192_30
#define LOWMC_L5_OR_NULL NULL

#define ENABLE_ZKBPP(x) NULL

#define ENABLE_KKW(x) x

#define NULL_FNS                                                                                   \
  { NULL, NULL, NULL }

static picnic_instance_t instances[PARAMETER_SET_MAX_INDEX] = {
    {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PARAMETER_SET_INVALID, TRANSFORM_FS, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L1_OR_NULL), 32, 16, 219, 219, 3, 16, 16, 75, 30, 55, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic_L1_FS, Picnic_L1_FS, TRANSFORM_FS, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L1_OR_NULL), 32, 16, 219, 219, 3, 16, 16, 75, 30, 55, 91, 107,
     PICNIC_SIGNATURE_SIZE_Picnic_L1_UR, Picnic_L1_UR, TRANSFORM_UR, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L3_OR_NULL), 48, 24, 329, 329, 3, 24, 24, 113, 30, 83, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic_L3_FS, Picnic_L3_FS, TRANSFORM_FS, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L3_OR_NULL), 48, 24, 329, 329, 3, 24, 24, 113, 30, 83, 137, 161,
     PICNIC_SIGNATURE_SIZE_Picnic_L3_UR, Picnic_L3_UR, TRANSFORM_UR, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L5_OR_NULL), 64, 32, 438, 438, 3, 32, 32, 143, 30, 110, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic_L5_FS, Picnic_L5_FS, TRANSFORM_FS, NULL_FNS},
    {ENABLE_ZKBPP(LOWMC_L5_OR_NULL), 64, 32, 438, 438, 3, 32, 32, 143, 30, 110, 175, 207,
     PICNIC_SIGNATURE_SIZE_Picnic_L5_UR, Picnic_L5_UR, TRANSFORM_UR, NULL_FNS},
    // Picnic2 params
    {ENABLE_KKW(LOWMC_L1_OR_NULL), 32, 16, 343, 27, 64, 16, 16, 75, 30, 55, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic2_L1_FS, Picnic2_L1_FS, TRANSFORM_FS, NULL_FNS},
    {ENABLE_KKW(LOWMC_L3_OR_NULL), 48, 24, 570, 39, 64, 24, 24, 113, 30, 83, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic2_L3_FS, Picnic2_L3_FS, TRANSFORM_FS, NULL_FNS},
    {ENABLE_KKW(LOWMC_L5_OR_NULL), 64, 32, 803, 50, 64, 32, 32, 143, 30, 110, 0, 0,
     PICNIC_SIGNATURE_SIZE_Picnic2_L5_FS, Picnic2_L5_FS, TRANSFORM_FS, NULL_FNS},
};
static bool instance_initialized[PARAMETER_SET_MAX_INDEX];

static bool create_instance(picnic_instance_t* pp) {
  if (!pp->lowmc) {
    return false;
  }

  pp->impls.lowmc                 = lowmc_get_implementation(pp->lowmc);
  pp->impls.lowmc_aux             = lowmc_compute_aux_get_implementation(pp->lowmc);
  pp->impls.lowmc_simulate_online = lowmc_simulate_online_get_implementation(pp->lowmc);

  return true;
}

const picnic_instance_t* picnic_instance_get(picnic_params_t param) {
  if (param <= PARAMETER_SET_INVALID || param >= PARAMETER_SET_MAX_INDEX) {
    return NULL;
  }

  if (!instance_initialized[param]) {
    if (!create_instance(&instances[param])) {
      return NULL;
    }
    instance_initialized[param] = true;
  }

  return &instances[param];
}
