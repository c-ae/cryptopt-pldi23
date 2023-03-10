/**
 * @file parameters.h
 * @brief Parameters of the HQC_KEM IND-CCA2 scheme
 */

#include "api.h"
#include "vector.h"

#ifndef HQC_PARAMETERS_H
#define HQC_PARAMETERS_H

#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/

/*
  #define PARAM_N                             	Define the parameter n of the scheme
  #define PARAM_N1                            	Define the parameter n1 of the scheme (length of BCH code)
  #define PARAM_N2                            	Define the parameter n2 of the scheme (length of the repetition code)
  #define PARAM_N1N2                          	Define the parameter n1 * n2 of the scheme (length of the tensor code)
  #define PARAM_OMEGA                         	Define the parameter omega of the scheme
  #define PARAM_OMEGA_E                       	Define the parameter omega_e of the scheme
  #define PARAM_OMEGA_R                       	Define the parameter omega_r of the scheme
  #define PARAM_SECURITY                      	Define the security level corresponding to the chosen parameters
  #define PARAM_DFR_EXP                       	Define the decryption failure rate corresponding to the chosen parameters

  #define SECRET_KEY_BYTES                    	Define the size of the secret key in bytes
  #define PUBLIC_KEY_BYTES                    	Define the size of the public key in bytes
  #define SHARED_SECRET_BYTES                 	Define the size of the shared secret in bytes
  #define CIPHERTEXT_BYTES                    	Define the size of the ciphertext in bytes

  #define UTILS_REJECTION_THRESHOLD           	Define the rejection threshold used to generate given weight vectors (see vector_set_random_fixed_weight function)
  #define VEC_N_SIZE_BYTES                    	Define the size of the array used to store a PARAM_N sized vector in bytes
  #define VEC_K_SIZE_BYTES                    	Define the size of the array used to store a PARAM_K sized vector in bytes
  #define VEC_N1_SIZE_BYTES                   	Define the size of the array used to store a PARAM_N1 sized vector in bytes
  #define VEC_N1N2_SIZE_BYTES                 	Define the size of the array used to store a PARAM_N1N2 sized vector in bytes

  #define VEC_N_SIZE_64                       	Define the size of the array used to store a PARAM_N sized vector in 64 bits
  #define VEC_K_SIZE_64                       	Define the size of the array used to store a PARAM_K sized vector in 64 bits
  #define VEC_N1_SIZE_64                      	Define the size of the array used to store a PARAM_N1 sized vector in 64 bits
  #define VEC_N1N2_SIZE_64                    	Define the size of the array used to store a PARAM_N1N2 sized vector in 64 bits

  #define VEC_N_256_SIZE_64                   	Define the size of the array of 64 bits elements used to store an array of size PARAM_N considered as elements of 256 bits
  #define VEC_N1N2_256_SIZE_64                	Define the size of the array of 64 bits elements used to store an array of size PARAM_N1N2 considered as elements of 256 bits

  #define PARAM_T                             	Define a threshold for decoding repetition code word (PARAM_T = (PARAM_N2 - 1) / 2)

  #define PARAM_DELTA                         	Define the parameter delta of the scheme (correcting capacity of the BCH code)
  #define PARAM_M                             	Define a positive integer
  #define PARAM_GF_POLY                       	Generator polynomial of galois field GF(2^PARAM_M), represented in hexadecimial form
  #define PARAM_GF_MUL_ORDER                  	Define the size of the multiplicative group of GF(2^PARAM_M),  i.e 2^PARAM_M -1
  #define PARAM_K                             	Define the size of the information bits of the BCH code
  #define PARAM_G                             	Define the size of the generator polynomial of BCH code
  #define PARAM_FFT                           	The additive FFT takes a 2^PARAM_FFT polynomial as input
                                              	We use the FFT to compute the roots of sigma, whose degree if PARAM_DELTA=60
                                              	The smallest power of 2 greater than 60+1 is 64=2^6
  #define PARAM_BCH_POLY                      	Generator polynomial of the BCH code

  #define RED_MASK                            	A mask fot the higher bits of a vector
  #define SHA512_BYTES                        	Define the size of SHA512 output in bytes
  #define SEED_BYTES                          	Define the size of the seed in bytes
  #define SEEDEXPANDER_MAX_LENGTH             	Define the seed expander max length
*/

#define PARAM_N                             	45197
#define PARAM_N1                            	766
#define PARAM_N2                            	59
#define PARAM_N1N2                          	45194
#define PARAM_OMEGA                         	101
#define PARAM_OMEGA_E                       	117
#define PARAM_OMEGA_R                       	117
#define PARAM_SECURITY                      	192
#define PARAM_DFR_EXP                       	192

#define SECRET_KEY_BYTES                    	CRYPTO_SECRETKEYBYTES
#define PUBLIC_KEY_BYTES                    	CRYPTO_PUBLICKEYBYTES
#define SHARED_SECRET_BYTES                 	CRYPTO_BYTES
#define CIPHERTEXT_BYTES                    	CRYPTO_CIPHERTEXTBYTES

#define UTILS_REJECTION_THRESHOLD           	16768087
#define VEC_K_SIZE_BYTES                    	CEIL_DIVIDE(PARAM_K, 8)
#define VEC_N_SIZE_BYTES                    	CEIL_DIVIDE(PARAM_N, 8)
#define VEC_N1_SIZE_BYTES                   	CEIL_DIVIDE(PARAM_N1, 8)
#define VEC_N1N2_SIZE_BYTES                 	CEIL_DIVIDE(PARAM_N1N2, 8)

#define VEC_N_SIZE_64                       	CEIL_DIVIDE(PARAM_N, 64)
#define VEC_K_SIZE_64                       	CEIL_DIVIDE(PARAM_K, 64)
#define VEC_N1_SIZE_64                      	CEIL_DIVIDE(PARAM_N1, 64)
#define VEC_N1N2_SIZE_64                    	CEIL_DIVIDE(PARAM_N1N2, 64)

#define PARAM_N_MULT                        	48768
#define VEC_N_256_SIZE_64                   	(CEIL_DIVIDE(PARAM_N_MULT, 256) << 2)
#define VEC_N1N2_256_SIZE_64                	(CEIL_DIVIDE(PARAM_N1N2, 256) << 2)

#define PARAM_T                             	29

#define PARAM_DELTA                         	57
#define PARAM_M                             	10
#define PARAM_GF_POLY                       	0x409
#define PARAM_GF_MUL_ORDER                  	1023
#define PARAM_K                             	256
#define PARAM_G                             	511
#define PARAM_FFT                           	6
#define PARAM_FFT_T                         	7
#define PARAM_BCH_POLY { \
        1,1,0,0,0,0,1,0,0,1,1,0,1,1,0,1,0,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1, \
        1,1,0,1,1,1,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0, \
        0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,0,0,0, \
        1,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0, \
        0,1,1,0,1,0,1,1,0,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,1,1,1,0, \
        1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,1,0,0,0,0,1,0, \
        0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,0,0,1,0,1, \
        1,1,1,1,1,0,1,0,1,0,1,1,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0, \
        1,0,0,0,1,0,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1, \
        1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,0,0,1,1,1,1,1,0,1,0,1, \
        0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1, \
        1,0,1,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1, \
        0,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,1,1,0,1,1,0,0,1,0,1, \
        1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1 \
      };

#define RED_MASK                            	0x0000000000001fffUL
#define SHA512_BYTES                        	64
#define SEED_BYTES                          	40
#define SEEDEXPANDER_MAX_LENGTH             	4294967295

#endif
