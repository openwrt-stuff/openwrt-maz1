#ifndef __data_h
#define __data_h

#include "types.h"
//
// REQUEST... types are actually fixed size
// RESPONSE... size may vary, defined here is max possible size
//

#define MAX_RESPONSE_SIZE 384
#define PID_BUFFER_SIZE 64
#define MAX_REQUEST_SIZE sizeof(REQUEST_V6)

typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	DWORD IsClientVM;
	DWORD LicenseStatus;
	DWORD GraceTime;
	GUID AppId;
	GUID SkuId;
	GUID KmsId;
	GUID ClientMachineId;
	DWORD MinimumClients;
	FILETIME TimeStamp;
	BYTE Reserved1[16];
	WCHAR WorkstationName[64];
} __packed REQUEST;

typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	DWORD KmsPIDLen;
	WCHAR KmsPID[PID_BUFFER_SIZE];
	GUID ClientMachineId;
	FILETIME TimeStamp;
	DWORD ActivatedMachines;
	DWORD ActivationInterval;
	DWORD RenewalInterval;
} __packed RESPONSE;

#ifdef _DEBUG
typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	DWORD KmsPIDLen;
	WCHAR KmsPID[49]; 		// Set this to the ePID length you want to debug
	GUID ClientMachineId;
	FILETIME TimeStamp;
	DWORD ActivatedMachines;
	DWORD ActivationInterval;
	DWORD RenewalInterval;
} __packed RESPONSE_DEBUG;
#endif


typedef struct {
	REQUEST RequestBase;
	BYTE Hash[16];
} __packed REQUEST_V4;

typedef struct {
	RESPONSE ResponseBase;
	BYTE Hash[16];
} __packed RESPONSE_V4;


typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	BYTE Salt[16];
	REQUEST RequestBase;
	BYTE Pad[4];
} __packed REQUEST_V5;

typedef REQUEST_V5 REQUEST_V6;

typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	BYTE Salt[16];
	RESPONSE ResponseBase;
	BYTE Rand[16];
	BYTE Hash[32];
	BYTE HwId[8];
	BYTE XorSalts[16];
	BYTE Hmac[16];
	//BYTE Pad[10];
} __packed RESPONSE_V6;

#ifdef _DEBUG
typedef struct {
	WORD MinorVer;
	WORD MajorVer;
	BYTE Salt[16];
	RESPONSE_DEBUG ResponseBase;
	BYTE Rand[16];
	BYTE Hash[32];
	BYTE Unknown[8];
	BYTE XorSalts[16];
	BYTE Hmac[16];
	BYTE Pad[16];
} __packed RESPONSE_V6_DEBUG;
#endif

#endif // __data_h
