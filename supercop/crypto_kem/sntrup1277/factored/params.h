#ifndef params_H
#define params_H

#define p 1277
#define q 7879
#define w 492

#define ppadsort 1280

#include "crypto_verify_1847.h"
#define crypto_verify_clen crypto_verify_1847

#include "crypto_encode_1277x7879.h"
#include "crypto_decode_1277x7879.h"
#define Rq_bytes crypto_encode_1277x7879_STRBYTES
#define Rq_encode crypto_encode_1277x7879
#define Rq_decode crypto_decode_1277x7879

#include "crypto_decode_1277x2627.h"
#define Rounded_bytes crypto_decode_1277x2627_STRBYTES
#define Rounded_decode crypto_decode_1277x2627

#include "crypto_encode_1277x2627round.h"
#define Round_and_encode crypto_encode_1277x2627round

#include "crypto_encode_1277x3.h"
#include "crypto_decode_1277x3.h"
#define Small_bytes crypto_encode_1277x3_STRBYTES
#define Small_encode crypto_encode_1277x3
#define Small_decode crypto_decode_1277x3

#include "crypto_encode_1277xfreeze3.h"
#define crypto_encode_pxfreeze3 crypto_encode_1277xfreeze3

#include "crypto_decode_1277xint32.h"
#define crypto_decode_pxint32 crypto_decode_1277xint32

#include "crypto_decode_1277xint16.h"
#define crypto_decode_pxint16 crypto_decode_1277xint16

#include "crypto_encode_1277xint16.h"
#define crypto_encode_pxint16 crypto_encode_1277xint16

#include "crypto_core_wforcesntrup1277.h"
#define crypto_core_wforce crypto_core_wforcesntrup1277

#include "crypto_core_scale3sntrup1277.h"
#define crypto_core_scale3 crypto_core_scale3sntrup1277

#include "crypto_core_invsntrup1277.h"
#define crypto_core_inv crypto_core_invsntrup1277

#include "crypto_core_inv3sntrup1277.h"
#define crypto_core_inv3 crypto_core_inv3sntrup1277

#include "crypto_core_mult3sntrup1277.h"
#define crypto_core_mult3 crypto_core_mult3sntrup1277

#include "crypto_core_multsntrup1277.h"
#define crypto_core_mult crypto_core_multsntrup1277

#endif
