/**
 * The CAESAR file proposed for the competition
 * that indicates all the lengths values for the
 * key, the secret message, the public message and
 * the ciphertext
 * 
 * @file api.h
 */
#ifndef __OMD_API_H__
#define __OMD_API_H__

#define CRYPTO_KEYBYTES 16  /**< Key size in bytes                               */
#define CRYPTO_NSECBYTES 0  /**< Secret message number size in bytes             */
#define CRYPTO_NPUBBYTES 12 /**< Public message number size in bytes             */
#define CRYPTO_ABYTES 16    /**< Ciphertext bytes size longer than the plaintext */

#define TAU_BLK_MACRO __attribute__((unused)) static const hashblock taublk = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
#define NONCE_BLK_MACRO hashblock nonce_block = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#endif /* __OMD_API_H__  */
