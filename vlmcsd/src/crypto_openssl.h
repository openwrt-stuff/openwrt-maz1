#ifndef __crypto_openssl_h
#define __crypto_openssl_h

#include <openssl/opensslv.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include "crypto.h"

#define Sha256(d, l, h)  SHA256(d, l, h)
#define Sha256HmacCtx    HMAC_CTX

#if OPENSSL_VERSION_NUMBER >= 0x10000000L

#define Sha256HmacInit(c, k, l)    HMAC_Init_ex(c, k, l, EVP_sha256(), NULL)
#define Sha256HmacUpdate(c, d, l)  HMAC_Update(c, d, l)
#define Sha256HmacFinish(c, h)     HMAC_Final(c, h, NULL)

#else // OPENSSL_VERSION_NUMBER

#define Sha256HmacInit(c, k, l)    ( HMAC_Init_ex(c, k, l, EVP_sha256(), NULL), !0 )
#define Sha256HmacUpdate(c, d, l)  ( HMAC_Update(c, d, l),                      !0 )
#define Sha256HmacFinish(c, h)     ( HMAC_Final(c, h, NULL),                    !0 )

#endif // OPENSSL_VERSION_NUMBER
#endif // __crypto_openssl_h
