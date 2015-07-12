#ifndef __rpc_h
#define __rpc_h

#include "main.h"

typedef struct {
	BYTE   VersionMajor;
	BYTE   VersionMinor;
	BYTE   PacketType;
	BYTE   PacketFlags;
	DWORD  DataRepresentation;
	WORD   FragLength;
	WORD   AuthLength;
	DWORD  CallId;
} __packed RPC_HEADER;


typedef struct {
	// RPC_HEADER  hdr;
	WORD   MaxXmitFrag;
	WORD   MaxRecvFrag;
	DWORD  AssocGroup;
	DWORD  NumCtxItems;
	struct {
		WORD   ContextId;
		WORD   NumTransItems;
		GUID   InterfaceUUID;
		WORD   InterfaceVerMajor;
		WORD   InterfaceVerMinor;
		GUID   TransferSyntax;
		DWORD  SyntaxVersion;
	} CtxItems[0];
} __packed RPC_BIND_REQUEST;

typedef struct {
	// RPC_HEADER  hdr;
	WORD   MaxXmitFrag;
	WORD   MaxRecvFrag;
	DWORD  AssocGroup;
	WORD   SecondaryAddressLength;
	BYTE   SecondaryAddress[6];
	DWORD  NumResults;
	struct {
		WORD   AckResult;
		WORD   AckReason;
		GUID   TransferSyntax;
		DWORD  SyntaxVersion;
	} Results[0];
} __packed RPC_BIND_RESPONSE;


typedef struct {
	// RPC_HEADER  hdr;
	DWORD  AllocHint;
	WORD   ContextId;
	WORD   Opnum;
	struct {
		DWORD  DataLength;
		DWORD  DataSizeIs;
	} Ndr;
	BYTE   Data[0];
} __packed RPC_REQUEST;

typedef struct {
	// RPC_HEADER  hdr;
	DWORD  AllocHint;
	WORD   ContextId;
	BYTE   CancelCount;
	BYTE   Pad1;
	struct {
		DWORD  DataLength;
		DWORD  DataSizeIs1;
		DWORD  DataSizeIs2;
	} Ndr;
	BYTE   Data[0];
} __packed RPC_RESPONSE;

typedef struct
{
	GUID guid;
	char* name;
	char* pid;
} KmsIdList;

#define RPC_PT_REQUEST   0
#define RPC_PT_RESPONSE  2
#define RPC_PT_BIND_REQ  11
#define RPC_PT_BIND_ACK  12

#define RPC_PF_FIRST  1
#define RPC_PF_LAST   2

extern DWORD RpcAssocGroup;
extern WORD  RpcSecondaryAddressLength;
extern char  RpcSecondaryAddress[ sizeof(((RPC_BIND_RESPONSE *)0)->SecondaryAddress) ];
extern BOOL RandomizationLevel;

void RpcServer(int);
void GenerateRandomPid(GUID guid, char* szPid, int serverType, int16_t lang);
char* itoc(char* c, int i, int digits);

#endif // __rpc_h
