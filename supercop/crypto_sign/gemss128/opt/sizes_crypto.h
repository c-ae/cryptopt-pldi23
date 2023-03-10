#ifndef _SIZES_CRYPTO_H
#define _SIZES_CRYPTO_H


#include "choice_crypto.h"



/************************ SIZES ************************/

/* Theoretical sizes in bits */
/* Pratical sizes in bytes */


/* Sizes with the inner mode */
#if HFE
    #include "sizes_HFE.h"
    /** Theoretical in bits size of the public key (inner mode). */
    #define SIZE_PK_THEORETICAL_INNER SIZE_PK_THEORETICAL_HFE
    /** Theoretical in bits size of the secret key (inner mode). */
    #define SIZE_SK_THEORETICAL_INNER SIZE_SK_THEORETICAL_HFE
    /** Theoretical in bits size of the signature (inner mode). */
    #define SIZE_SIGN_THEORETICAL_INNER SIZE_SIGN_THEORETICAL_HFE

    /** Pratical size in bytes of the public key (inner mode). */
    #define SIZE_PK_INNER SIZE_PK_HFE
    /** Pratical size in bytes of the secret key (inner mode). */
    #define SIZE_SK_INNER SIZE_SK_HFE
    /** Pratical size in bytes of the signature (inner mode). */
    #define SIZE_SIGN_INNER SIZE_SIGN_HFE
#endif



#if InnerMode
    /** Theoretical size in bits of the public key. */
    #define SIZE_PK_THEORETICAL SIZE_PK_THEORETICAL_INNER
    /** Theoretical size in bits of the secret key. */
    #define SIZE_SK_THEORETICAL SIZE_SK_THEORETICAL_INNER
    /** Theoretical size in bits of the signature. */
    #define SIZE_SIGN_THEORETICAL SIZE_SIGN_THEORETICAL_INNER

    /** Pratical size in bytes of the public key. */
    #define SIZE_PK SIZE_PK_INNER
    /** Pratical size in bytes of the secret key. */
    #define SIZE_SK SIZE_SK_INNER
    /** Pratical size in bytes of the signature. */
    #define SIZE_SIGN SIZE_SIGN_INNER
#endif





#endif
