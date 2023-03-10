#ifndef params_H
#define params_H

#define p 1013
#define q 7177
#define w 392
#define tau0 3367
#define tau1 73
#define tau2 3143
#define tau3 449
#define I 256

#define ppadsort 1024

#define q18 37 /* round(2^18/q) */
#define q27 18701 /* round(2^27/q) */
#define q31 299217 /* floor(2^31/q) */

#include "crypto_verify_1583.h"
#define crypto_verify_clen crypto_verify_1583

#include "crypto_decode_1013x2393.h"
#define Rounded_bytes crypto_decode_1013x2393_STRBYTES
#define Rounded_decode crypto_decode_1013x2393

#include "crypto_encode_1013x2393round.h"
#define Round_and_encode crypto_encode_1013x2393round

#include "crypto_encode_1013x3.h"
#include "crypto_decode_1013x3.h"
#define Small_bytes crypto_encode_1013x3_STRBYTES
#define Small_encode crypto_encode_1013x3
#define Small_decode crypto_decode_1013x3

#include "crypto_encode_256x16.h"
#include "crypto_decode_256x16.h"
#define Top_bytes crypto_encode_256x16_STRBYTES
#define Top_encode crypto_encode_256x16
#define Top_decode crypto_decode_256x16

#include "crypto_encode_256x2.h"
#include "crypto_decode_256x2.h"
#define Inputs_bytes crypto_encode_256x2_STRBYTES
#define Inputs_encode crypto_encode_256x2
#define Inputs_decode crypto_decode_256x2

#include "crypto_decode_1013xint32.h"
#define crypto_decode_pxint32 crypto_decode_1013xint32

#include "crypto_decode_1013xint16.h"
#define crypto_decode_pxint16 crypto_decode_1013xint16

#include "crypto_encode_1013xint16.h"
#define crypto_encode_pxint16 crypto_encode_1013xint16

#include "crypto_core_multsntrup1013.h"
#define crypto_core_mult crypto_core_multsntrup1013

#endif
