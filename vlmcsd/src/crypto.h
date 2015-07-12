#ifndef __crypto_h
#define __crypto_h

#include "main.h"

#define AES_ROUNDS      (10)
#define AES_KEY_BYTES   (16)
#define AES_BLOCK_BYTES (16)
#define AES_KEY_DWORDS  (AES_KEY_BYTES / sizeof(DWORD))

#define ROR32(v, n)  ( (v) << (32 - n) | (v) >> n )

__inline static void XorBlock(const BYTE *const in, const BYTE *out)
{
	UAA64( out, 0 ) ^= UAA64( in, 0 );
	UAA64( out, 1 ) ^= UAA64( in, 1 );
}

void AesCmacV4(BYTE *data, size_t len, BYTE *hash);

extern const BYTE AesKeyV5[];
extern const BYTE AesKeyV6[];

typedef struct {
	DWORD  Key[44];
} AesCtx;

void AesInitKey(AesCtx *Ctx, const BYTE *Key, BOOL IsV6);
void AesEncryptBlock(AesCtx *Ctx, BYTE *block);
void AesDecryptBlock(AesCtx *Ctx, BYTE *block);
void AesEncryptCbc(AesCtx *Ctx, BYTE *iv, BYTE *data, size_t *len);
void AesDecryptCbc(AesCtx *Ctx, BYTE *iv, BYTE *data, size_t len);

#if defined(_CRYPTO_OPENSSL)
#include "crypto_openssl.h"

#elif defined(_CRYPTO_POLARSSL)
#include "crypto_polarssl.h"

#else
#include "crypto_internal.h"

#endif
#endif // __crypto_h
