//#ifdef _WIN32
//#error Support for native Win32 is incomplete. Currently only cygwin is supported
//#endif

#include <sys/types.h>

#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pwd.h>
#include <grp.h>
#include <syslog.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "rpc.h"
#include "data.h"

#ifndef _WIN32
#define SENDRECV_T(v)  int (*v)(int, BYTE*, int, int)
#else
#define SENDRECV_T(v)  int (WINAPI *v)(int, BYTE*, int, int)
#endif

extern const KmsIdList AppList[4];
extern const struct KMSHostOS { uint16_t Type; uint16_t Build; } HostOS[4];
extern const uint16_t LcidList[158];

char RandomPid[][PID_BUFFER_SIZE] =
{
		"", "", ""
};

BOOL sendrecv(int sock, BYTE *data, int len, int do_send)
{
	int n;
	SENDRECV_T( f ) = do_send
		? (SENDRECV_T()) send
		: (SENDRECV_T()) recv;

	do n = f(sock, data, len, 0);
	while (
			( n < 0 && errno == EINTR ) || ( n > 0 && ( data += n, (len -= n) > 0 ) ));

	return ! len;
}

char *fn_pid = NULL;
char *fn_ini = NULL;
char *defaultport = "1688";
char *fn_log = NULL;
BOOL nodaemon = 0;
BOOL logstdout = 0;
int v6required = 0;
int v4required = 0;
int RandomizationLevel = 1;
SOCKET *SocketList;
int maxsockets = 0;
int numsockets = 0;
int HaveIPv6Stack = 0;
int HaveIPv4Stack = 0;
char *const cIPv4 = "IPv4";
char *const cIPv6 = "IPv6";
char *const fIPv4 = "%s:%s";
char *const fIPv6 = "[%s]:%s";
#ifndef _WIN32
gid_t gid = INVALID_GID;
uid_t uid = INVALID_UID;
#endif

int ip2str(char *result, size_t resultlen, struct sockaddr *sa, socklen_t socklen)
{
	char addr[256], serv[256];
	if (getnameinfo(sa, socklen, addr, sizeof(addr), serv, sizeof(serv), NI_NUMERICHOST | NI_NUMERICSERV)) return FALSE;
	if ((unsigned int)snprintf(result, resultlen, sa->sa_family == AF_INET6 ? fIPv6 : fIPv4, addr, serv) > resultlen) return FALSE;
	return TRUE;
}

void logger(char* text)
{
	FILE *log;
	if (logstdout) log = stdout;
	else
	{
		if (fn_log == NULL) return;

#ifndef _WIN32
		if (!strcmp(fn_log, "syslog"))
		{
			openlog("vlmcsd", LOG_CONS | LOG_PID, LOG_USER);
			syslog(LOG_INFO, "%s", text);
			closelog();
			return;
		}
#endif

		log = fopen(fn_log, "a");
		if ( !log ) return;
	}

	time_t now = time(0);
	char mbstr[100];
	strftime(mbstr, 100, "%Y-%m-%d %X", localtime(&now));
	fprintf(log, "%s: %s", mbstr, text);

	if (!logstdout) fclose(log);
	else fflush(stdout);
}

void Usage(char* argv0)
{
	fprintf(stderr,
			"\nUsage:\n"
			"   %s [ options ]\n\n"
			"Where:\n"
			#ifndef _WIN32
			"  -u <user>		set uid to <user>\n"
			"  -g <group>		set gid to <group>\n"
			#endif
			"  -e			log to stdout\n"
			"  -D			run in foreground\n"
			"  -f			run in foreground and log to stdout\n"
			"  -r			set ePID randomization level (default 1)\n"
			"  -4			use IPv4\n"
			"  -6			use IPv6\n"
			"  -p <file>		write pid to <file>\n"
			"  -i <file>		load KMS ePIDs from <file>\n"
			"  -P <port>		set TCP port for subsequent -L statements (default 1688)\n"
			"  -L <address>[:<port>]	listen on IP address <address> with optional <port>\n"
			#ifndef _WIN32
			"  -l syslog		log to syslog\n"
			#endif
			"  -l <file>		log to <file>\n\n",
			argv0);
}

#ifndef _WIN32
char GetNumericId(gid_t *i, char *c)
{
	char* endptr;
	*i = (gid_t)strtol(c, &endptr, 10);

	if (*endptr)
		fprintf(stderr, "Fatal: setgid/setuid for %s failed.\n", optarg);

	return *endptr;
}
#endif

char GetGid()
{
	#ifndef _WIN32
		struct group *g;

		if ((g = getgrnam(optarg)))
			gid = g->gr_gid;
		else
			return GetNumericId(&gid, optarg);

		return 0;
	#else
		fprintf(stderr, "Warning: -g is not supported on your platform (ignoring).\n");
		return 0;
	#endif
}

char GetUid()
{
#ifndef _WIN32
	struct passwd *u;

	///BUGBUG: Assumes uid_t and gid_t are of same size (shouldn't be a problem)
	if ((u = getpwnam(optarg)))
		uid = u->pw_uid;
	else
		return GetNumericId((gid_t*)&uid, optarg);

	return 0;
#else
	fprintf(stderr, "Warning: -u is not supported on your platform (ignoring).\n");
	return 0;
#endif
}

int ListenOnAddress(struct addrinfo *sa, SOCKET *s, char *szHost, char *szPort)
{
	*s = INVALID_SOCKET;
	*s = socket(sa->ai_family, SOCK_STREAM, 0);

	if (*s == INVALID_SOCKET)
	{
		fprintf(stderr, "Warning: General %s protocol error.\n", sa->ai_family ? cIPv4 : cIPv6);
		return 2;
	}

	BOOL socketOption = TRUE;

	if (sa->ai_family == AF_INET6) setsockopt(*s, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&socketOption, sizeof(socketOption));
	setsockopt(*s, SOL_SOCKET, SO_REUSEADDR, (void*)&socketOption, sizeof(socketOption));

	if (bind(*s, sa->ai_addr, sa->ai_addrlen))
	{
		//fprintf(stderr, "Socket error %u: ", socket_errno); /* for debugging only */

		fprintf(stderr, "Warning: Could not bind to port %s with IP address %s.\n", szPort, szHost);
		close(*s);
		return 2;
	}

	if (listen(*s, SOMAXCONN))
	{
		fprintf(stderr, "Warning: Cannot listen on port %s with IP address %s.\n", szPort, szHost);
		close(*s);
		return 2;
	}

	char buffer[256], ipstr[256];

	if (ip2str(ipstr, sizeof(ipstr), sa->ai_addr, sa->ai_addrlen) &&
	    (unsigned int)snprintf(buffer, sizeof(buffer), "Listening on %s\n", ipstr) <= sizeof(buffer))
	{
		logger(buffer);
	}

	return 0;
}

int AddSocketAddress(char* addr)
{
	SOCKET *s = SocketList + numsockets;

	int rc, result;

	size_t len = strlen(addr) + 1;
	if (len > 256) return FALSE;
	char *addrcopy = alloca(len);
	memcpy(addrcopy, addr, len);

	char *szHost = addrcopy;
	char *szPort = defaultport;

	char *lastcolon = strrchr(addrcopy, ':');
	char *firstcolon = strchr(addrcopy, ':');
	char *closingbracket = strstr(addrcopy, "]:");

	if (*addrcopy == '[' && closingbracket) //IPv6 address with port
	{
		*closingbracket = 0;
		szHost++;
		szPort = closingbracket + 2;
	}
	else if (firstcolon && firstcolon == lastcolon) //IPv4 address with port
	{
		*firstcolon = 0;
		szPort = firstcolon + 1;
	}

	struct addrinfo hints;
	struct addrinfo *saList, *sa;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICHOST;

	if ((rc = getaddrinfo(szHost, szPort, &hints, &saList)))
	{
		fprintf(stderr, "Warning: %s: %s\n", addr, gai_strerror(rc));
		return FALSE;
	}

	for (sa = saList; sa; sa = sa->ai_next)
	{
		// struct sockaddr_in* addr4 = (struct sockaddr_in*)sa->ai_addr;
		// struct sockaddr_in6* addr6 = (struct sockaddr_in6*)sa->ai_addr;

		if (sa->ai_family != AF_INET && sa->ai_family != AF_INET6) continue;

		if (!ListenOnAddress(sa, s, szHost, szPort))
		{
			numsockets++;
			result = TRUE;
		}
	}

	freeaddrinfo(saList);
	return result;
}

SOCKET network_accept_any(SOCKET fds[], unsigned int count, struct sockaddr *addr, socklen_t *addrlen)
{
    fd_set readfds;
    SOCKET maxfd, fd;
    unsigned int i;
    int status;

    FD_ZERO(&readfds);
    maxfd = -1;

    for (i = 0; i < count; i++)
    {
        FD_SET(fds[i], &readfds);
        if (fds[i] > maxfd) maxfd = fds[i];
    }

    status = select(maxfd + 1, &readfds, NULL, NULL, NULL);

    if (status < 0) return INVALID_SOCKET;

    fd = INVALID_SOCKET;

    for (i = 0; i < count; i++)
    {
        if (FD_ISSET(fds[i], &readfds))
        {
            fd = fds[i];
            break;
        }
    }

    if (fd == INVALID_SOCKET)
        return INVALID_SOCKET;
    else
        return accept(fd, addr, addrlen);
}

void CloseAllListeningSockets()
{
	int i;

	for (i = 0; i < numsockets; i++)
		close(SocketList[i]);
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
	nodaemon = 1;
	WSADATA wsadata;
	WSAStartup(0x0202, &wsadata);
#endif

	SOCKET s = INVALID_SOCKET;

	s = socket(AF_INET6, SOCK_STREAM, 0);

	if (s != INVALID_SOCKET)
	{
		HaveIPv6Stack = 1;
		close(s);
		s = INVALID_SOCKET;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);

	if (s != INVALID_SOCKET)
	{
		HaveIPv4Stack = 1;
		close(s);
	}

	int o;
	const static char* const optstring = "u:g:L:p:i:P:l:r:feD46";
	
	for (opterr = 0; ( o = getopt(argc, argv, optstring) ) > 0; ) switch (o)
	{
		case '4':
			if (!HaveIPv4Stack)
			{
				fprintf(stderr, "Fatal: Your system does not support %s.\n", cIPv4);
				return !0;
			}
			v4required = 1;
			break;
		case '6':
			if (!HaveIPv6Stack)
			{
				fprintf(stderr, "Fatal: Your system does not support %s.\n", cIPv6);
				return !0;
			}
			v6required = 1;
			break;
		case 'p':
			fn_pid = optarg;
			break;
		case 'i':
			fn_ini = optarg;
			break;
		case 'l':
			fn_log = optarg;
			break;
		case 'L':
			maxsockets++;
			break;
		case 'f':
			nodaemon = 1;
			logstdout = 1;
			break;
		case 'D':
			nodaemon = 1;
			break;
		case 'e':
			logstdout = 1;
			break;
		case 'r':
			RandomizationLevel = atoi(optarg);
			if (RandomizationLevel < 0 || RandomizationLevel > 2) RandomizationLevel = 1;
			break;
		case 'g':
			if (GetGid()) return !0;
			break;
		case 'u':
			if (GetUid()) return !0;
			break;
		case 'P':
			break;
		default:
			Usage(argv[0]);
			return !0;
	}

	if (optind != argc)
	{
		Usage(argv[0]);
		return !0;
	}

	int allocsockets = maxsockets ? maxsockets : 2;
	SocketList = malloc(allocsockets * sizeof(SOCKET));

#if defined(__BSD__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__OpenBSD__)
	optind = 1;
	optreset = 1; // Makes BSD getopt happy
#else
	optind = 0; // Makes GLIBC getopt happy
#endif

	for (opterr = 0; ( o = getopt(argc, argv, optstring) ) > 0; ) switch (o)
	{
		case 'L':
			AddSocketAddress(optarg);
			break;
		case 'P':
			defaultport = optarg;
			break;
		default:
			break;
	}

	if (!maxsockets)
	{
		if (HaveIPv6Stack && (v6required || !v4required)) AddSocketAddress("::");
		if (HaveIPv4Stack && (v4required || !v6required)) AddSocketAddress("0.0.0.0");
	}

	if (!numsockets)
	{
		fprintf(stderr, "Fatal: Could not listen on any socket.\n");
		return !0;
	}

#ifndef _WIN32
	if ((gid != INVALID_GID && setgid(gid)) || (uid != INVALID_GID && setuid(uid)))
	{
		fprintf(stderr, "Fatal: setgid/setuid for %s failed.\n", optarg);
		return !0;
	}

#endif

	if (RandomizationLevel == 1)
	{
		int i;
		srand((unsigned int)time(NULL));
		int serverType = rand() % _countof(HostOS);
		int16_t lang = LcidList[rand() % _countof(LcidList)];

		for (i = 0; i < _countof(RandomPid); i++)
		{
			GenerateRandomPid(AppList[i].guid, RandomPid[i], serverType, lang);
		}
	}

#ifndef _WIN32 // Windows has no fork or signal handling
	if ( !nodaemon) if (daemon(!0, logstdout))
	{
		fprintf(stderr, "Fatal: Could not daemonize to background.\n");
		return errno;
	}

	{
		struct sigaction sa =
		{
			.sa_handler = SIG_IGN,
			.sa_flags   = SA_NOCLDWAIT
		};

		if ( sigemptyset(&sa.sa_mask) || sigaction(SIGCHLD, &sa, 0) )
			return errno;
	}
#endif

	logger("KMS emulator started successfully\n");

	if (fn_pid)
	{
		FILE *_f = fopen(fn_pid, "w");

		if ( _f ) {
			fprintf(_f, "%u", getpid());
			fclose(_f);
		}
		else
		{
			logger("Warning: Cannot write pid file.\n");
		}
	}

	srand( (int)time(NULL) );

	RpcAssocGroup = rand();

	for (;;)
	{
		socklen_t len;
		struct sockaddr_storage addr;
		SOCKET s_client;

		for (;;) if ( (s_client = network_accept_any(SocketList, numsockets, NULL, NULL)) < 0 )
		{
			if ( errno != EINTR )
				return errno;
		}
		else break;

		RpcAssocGroup++;
		len = sizeof addr;

		if (getsockname(s_client, (struct sockaddr*)&addr, &len) ||
				getnameinfo((struct sockaddr*)&addr, len, NULL, 0, RpcSecondaryAddress, sizeof(RpcSecondaryAddress), NI_NUMERICSERV))
		{
			strcpy(RpcSecondaryAddress, "1688"); // In case of failure use default port (doesn't seem to break activation)
		}

		RpcSecondaryAddressLength = LE16(strlen(RpcSecondaryAddress) + 1);

#ifndef _WIN32
		int pid;
		if ( (pid = fork()) < 0 )
			return errno;

		else if ( pid )
			close(s_client);

		else
#endif
		{
			char ipstr[256], text[256];

			struct timeval to = {
				.tv_sec  = 60,
				.tv_usec = 0
			};

			setsockopt(s_client, SOL_SOCKET, SO_RCVTIMEO, (char*)&to, sizeof(to));
			setsockopt(s_client, SOL_SOCKET, SO_SNDTIMEO, (char*)&to, sizeof(to));
			len = sizeof addr;

			if (getpeername(s_client, (struct sockaddr*)&addr, &len) ||
					!ip2str(ipstr, sizeof(ipstr), (struct sockaddr*)&addr, len))
			{
				*ipstr = 0;
			}

			char *connection_type = addr.ss_family == AF_INET6 ? cIPv6 : cIPv4;
			static char *const cAccepted = "accepted";
			static char *const cClosed = "closed";
			static char *const fIP = "%s connection %s: %s.\n";

			CloseAllListeningSockets();
			sprintf(text, fIP, connection_type, cAccepted, ipstr);
			if (*ipstr) logger(text);
			RpcServer(s_client);
#ifdef _WIN32
			shutdown(s_client, SD_BOTH);
#endif
			close(s_client);

			sprintf(text, fIP, connection_type, cClosed, ipstr);
			if (*ipstr) logger(text);
#ifndef _WIN32
			return 0;
#endif
		}
	}

	unlink(fn_pid);
	CloseAllListeningSockets();
	return 0;
}
