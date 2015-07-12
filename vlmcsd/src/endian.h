#ifndef __endian_h
#define __endian_h

//
// Unaligned access
//
#define __UNALIGNED(t, p)  ( ((struct __packed { t val[0]; } *)(p))->val )

#define UAA64(p, i)  __UNALIGNED(unsigned long long, p)[(i)]
#define UAA32(p, i)  __UNALIGNED(unsigned int,       p)[(i)]
#define UAA16(p, i)  __UNALIGNED(unsigned short,     p)[(i)]

#define UA64(p)  UAA64(p, 0)
#define UA32(p)  UAA32(p, 0)
#define UA16(p)  UAA16(p, 0)

//
// Byteorder
//
#if defined(__linux__) || defined(__GLIBC__)

#include <endian.h>
#include <byteswap.h>

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__OpenBSD__)

#include <sys/types.h>
#include <sys/endian.h>

#define __BYTE_ORDER     _BYTE_ORDER
#define __LITTLE_ENDIAN  _LITTLE_ENDIAN
#define __BIG_ENDIAN     _BIG_ENDIAN

#ifdef __OpenBSD__

#define bswap_16  swap16
#define bswap_32  swap32
#define bswap_64  swap64

#else // !__OpenBSD__

#define bswap_16  bswap16
#define bswap_32  bswap32
#define bswap_64  bswap64

#endif // __OpenBSD__

#elif defined(__APPLE__)

#include <sys/types.h>
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>

#define __BYTE_ORDER     _BYTE_ORDER
#define __LITTLE_ENDIAN  _LITTLE_ENDIAN
#define __BIG_ENDIAN     _BIG_ENDIAN

#define bswap_16 OSSwapInt16
#define bswap_32 OSSwapInt32
#define bswap_64 OSSwapInt64

#elif defined(__CYGWIN__)

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __BYTE_ORDER __LITTLE_ENDIAN
#include <byteswap.h>

#endif



#if defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && defined(__LITTLE_ENDIAN)  \
	&& defined(bswap_16) && defined(bswap_32) && defined(bswap_64)

#if __BYTE_ORDER == __LITTLE_ENDIAN

#define __BE16(x)  bswap_16(x)
#define __LE16(x)  (x)
#define __BE32(x)  bswap_32(x)
#define __LE32(x)  (x)
#define __BE64(x)  bswap_64(x)
#define __LE64(x)  (x)

#else // __BYTE_ORDER == __BIG_ENDIAN

#define __BE16(x)  (x)
#define __LE16(x)  bswap_16(x)
#define __BE32(x)  (x)
#define __LE32(x)  bswap_32(x)
#define __BE64(x)  (x)
#define __LE64(x)  bswap_64(x)

#endif // __BYTE_ORDER

#define PUT_UAA64BE(p, v, i)  ( UAA64(p, i) = __BE64(v) )
#define PUT_UAA32BE(p, v, i)  ( UAA32(p, i) = __BE32(v) )
#define PUT_UAA16BE(p, v, i)  ( UAA16(p, i) = __BE16(v) )

#define PUT_UAA64LE(p, v, i)  ( UAA64(p, i) = __LE64(v) )
#define PUT_UAA32LE(p, v, i)  ( UAA32(p, i) = __LE32(v) )
#define PUT_UAA16LE(p, v, i)  ( UAA16(p, i) = __LE16(v) )

#define GET_UAA64BE(p, i)  __BE64(UAA64(p, i))
#define GET_UAA32BE(p, i)  __BE32(UAA32(p, i))
#define GET_UAA16BE(p, i)  __BE16(UAA16(p, i))

#define GET_UAA64LE(p, i)  __LE64(UAA64(p, i))
#define GET_UAA32LE(p, i)  __LE32(UAA32(p, i))
#define GET_UAA16LE(p, i)  __LE16(UAA16(p, i))

#define BE16(x)  __BE16(x)
#define LE16(x)  __LE16(x)
#define BE32(x)  __BE32(x)
#define LE32(x)  __LE32(x)
#define BE64(x)  __BE64(x)
#define LE64(x)  __LE64(x)

#else // ! defined(__BYTE_ORDER)

extern inline void PUT_UAA64BE(void *p, unsigned long long v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned long long *)p)[i];
	_p[ 0 ] = v >> 56;
	_p[ 1 ] = v >> 48;
	_p[ 2 ] = v >> 40;
	_p[ 3 ] = v >> 32;
	_p[ 4 ] = v >> 24;
	_p[ 5 ] = v >> 16;
	_p[ 6 ] = v >> 8;
	_p[ 7 ] = v;
}

extern inline void PUT_UAA32BE(void *p, unsigned int v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned int *)p)[i];
	_p[ 0 ] = v >> 24;
	_p[ 1 ] = v >> 16;
	_p[ 2 ] = v >> 8;
	_p[ 3 ] = v;
}

extern inline void PUT_UAA16BE(void *p, unsigned short v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned short *)p)[i];
	_p[ 0 ] = v >> 8;
	_p[ 1 ] = v;
}


extern inline void PUT_UAA64LE(void *p, unsigned long long v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned long long *)p)[i];
	_p[ 0 ] = v;
	_p[ 1 ] = v >> 8;
	_p[ 2 ] = v >> 16;
	_p[ 3 ] = v >> 24;
	_p[ 4 ] = v >> 32;
	_p[ 5 ] = v >> 40;
	_p[ 6 ] = v >> 48;
	_p[ 7 ] = v >> 56;
}

extern inline void PUT_UAA32LE(void *p, unsigned int v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned int *)p)[i];
	_p[ 0 ] = v;
	_p[ 1 ] = v >> 8;
	_p[ 2 ] = v >> 16;
	_p[ 3 ] = v >> 24;
}

extern inline void PUT_UAA16LE(void *p, unsigned short v, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned short *)p)[i];
	_p[ 0 ] = v;
	_p[ 1 ] = v >> 8;
}


extern inline unsigned long long GET_UAA64BE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned long long *)p)[i];
	return
		(unsigned long long)_p[ 0 ] << 56 |
		(unsigned long long)_p[ 1 ] << 48 |
		(unsigned long long)_p[ 2 ] << 40 |
		(unsigned long long)_p[ 3 ] << 32 |
		(unsigned long long)_p[ 4 ] << 24 |
		(unsigned long long)_p[ 5 ] << 16 |
		(unsigned long long)_p[ 6 ] << 8  |
		(unsigned long long)_p[ 7 ];

}

extern inline unsigned int GET_UAA32BE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned int *)p)[i];
	return
		(unsigned int)_p[ 0 ] << 24 |
		(unsigned int)_p[ 1 ] << 16 |
		(unsigned int)_p[ 2 ] << 8  |
		(unsigned int)_p[ 3 ];
}

extern inline unsigned short GET_UAA16BE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned short *)p)[i];
	return
		(unsigned short)_p[ 0 ] << 8 |
		(unsigned short)_p[ 1 ];
}


extern inline unsigned long long GET_UAA64LE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned long long *)p)[i];
	return
		(unsigned long long)_p[ 0 ] |
		(unsigned long long)_p[ 1 ] << 8  |
		(unsigned long long)_p[ 2 ] << 16 |
		(unsigned long long)_p[ 3 ] << 24 |
		(unsigned long long)_p[ 4 ] << 32 |
		(unsigned long long)_p[ 5 ] << 40 |
		(unsigned long long)_p[ 6 ] << 48 |
		(unsigned long long)_p[ 7 ] << 56;

}

extern inline unsigned int GET_UAA32LE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned int *)p)[i];
	return
		(unsigned int)_p[ 0 ] |
		(unsigned int)_p[ 1 ] << 8  |
		(unsigned int)_p[ 2 ] << 16 |
		(unsigned int)_p[ 3 ] << 24;
}

extern inline unsigned short GET_UAA16LE(void *p, unsigned int i)
{
	unsigned char *_p = (unsigned char *)&((unsigned short *)p)[i];
	return
		(unsigned short)_p[ 0 ] |
		(unsigned short)_p[ 1 ] << 8;
}


extern inline unsigned short BE16(unsigned short x)
{
	return GET_UAA16BE(&x, 0);
}

extern inline unsigned short LE16(unsigned short x)
{
	return GET_UAA16LE(&x, 0);
}

extern inline unsigned int BE32(unsigned int x)
{
	return GET_UAA32BE(&x, 0);
}

extern inline unsigned int LE32(unsigned int x)
{
	return GET_UAA32LE(&x, 0);
}

extern inline unsigned long long BE64(unsigned long long x)
{
	return GET_UAA64BE(&x, 0);
}

extern inline unsigned long long LE64(unsigned long long x)
{
	return GET_UAA64LE(&x, 0);
}

#endif // defined(__BYTE_ORDER)


#define PUT_UA64BE(p, v)  PUT_UAA64BE(p, v, 0)
#define PUT_UA32BE(p, v)  PUT_UAA32BE(p, v, 0)
#define PUT_UA16BE(p, v)  PUT_UAA16BE(p, v, 0)

#define PUT_UA64LE(p, v)  PUT_UAA64LE(p, v, 0)
#define PUT_UA32LE(p, v)  PUT_UAA32LE(p, v, 0)
#define PUT_UA16LE(p, v)  PUT_UAA16LE(p, v, 0)

#define GET_UA64BE(p)  GET_UAA64BE(p, 0)
#define GET_UA32BE(p)  GET_UAA32BE(p, 0)
#define GET_UA16BE(p)  GET_UAA16BE(p, 0)

#define GET_UA64LE(p)  GET_UAA64LE(p, 0)
#define GET_UA32LE(p)  GET_UAA32LE(p, 0)
#define GET_UA16LE(p)  GET_UAA16LE(p, 0)

#endif // __endian_h
