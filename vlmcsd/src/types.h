#ifndef __types_h
#define __types_h

#ifndef __packed
#define __packed  __attribute__((packed))
#endif
#define __inline  __attribute__((always_inline)) inline

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define socket_errno WSAGetLastError()

/* Unknown Winsock error codes */
#define WSAENODEV -1

#else // !__MINGW__
typedef unsigned int    DWORD;
typedef unsigned short  WORD;
typedef unsigned char   BYTE;
typedef short           WCHAR;
typedef int             BOOL;

#define FALSE  0
#define TRUE   1

typedef struct {
	DWORD  Data1;
	WORD   Data2;
	WORD   Data3;
	BYTE   Data4[8];
} __packed GUID;

typedef struct {
	DWORD  dwLowDateTime;
	DWORD  dwHighDateTime;
} __packed FILETIME;

#define IsEqualGUID(a, b)  ( !memcmp(a, b, sizeof(GUID)) )
#define _countof(x)        ( sizeof(x) / sizeof(x[0]) )
#define SOCKET int
#define INVALID_SOCKET -1
#define socket_errno errno

// MAP errno error codes to WSAGetLastError() codes
// Add more if you need them
#define WSAEADDRINUSE EADDRINUSE
#define WSAENODEV ENODEV
#define WSAEADDRNOTAVAIL EADDRNOTAVAIL
#define WSAEACCES EACCES
#define WSAEACCES EACCES
#define WSAEINVAL EINVAL

#endif // __MINGW__
#define INVALID_UID ((uid_t)-1)
#define INVALID_GID ((gid_t)-1)

#endif // __types_h
