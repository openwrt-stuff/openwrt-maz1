#ifndef __main_h
#define __main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define __T(x)    #x
#define  _T(x) __T(x)

extern char *fn_pid;
extern char *fn_ini;
extern char *fn_log;

#include "types.h"
#include "endian.h"

BOOL sendrecv(int, BYTE *, int, int);
void logger(char* text);

#define _recv(s, d, l)  sendrecv(s, (BYTE *)d, l,  0)
#define _send(s, d, l)  sendrecv(s, (BYTE *)d, l, !0)

#ifndef SA_NOCLDWAIT    // required for Cygwin
#define SA_NOCLDWAIT 0
#endif

#endif // __main_h
