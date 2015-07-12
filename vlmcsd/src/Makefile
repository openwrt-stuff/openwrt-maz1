################################################################################

PROGRAM_NAME = vlmcsd

PID_FILE = /var/run/$(PROGRAM_NAME).pid
INI_FILE = /etc/$(PROGRAM_NAME).ini

# crypto library to use for standard algos, could save ~1-2kb ;)
# can be either 'openssl', 'polarssl' or anything other for internal impl
CRYPTO ?= internal

################################################################################

CC ?= gcc

BASECFLAGS  = -Os -s
BASECFLAGS += -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections 

SRC = crypto.c rpc.c main.c

ifeq ($(CRYPTO), openssl)
	BASECFLAGS += -D_CRYPTO_OPENSSL -lcrypto

else ifeq ($(CRYPTO), polarssl)
	BASECFLAGS += -D_CRYPTO_POLARSSL -lpolarssl

else
	BASECFLAGS += -D_CRYPTO_INTERNAL
	SRC += crypto_internal.c
endif


$(PROGRAM_NAME): $(SRC)
	$(CC) -o $@ $(SRC) $(BASECFLAGS) $(CFLAGS)

all: $(PROGRAM_NAME)

clean:
	-rm -f *.o $(PROGRAM_NAME)
