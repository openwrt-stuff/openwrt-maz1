EXTRA_CFLAGS += -include $(src)/fs_conf.h
EXTRA_CFLAGS += -DNDEBUG -g0
EXTRA_CFLAGS += -DUFSD_DEVICE=ufsd -DUFSD_USE_ASM_DIV64
EXTRA_CFLAGS += -DUFSD_DISABLE_UGM -DUFSD_CHECK_BDI -Wno-unused-local-typedefs -Wno-implicit-function-declaration

MODULE_NAME := ufsd
MODULE_OBJECTS := ufsdvfs.o vfsdebug.o fool.o libufsd_$(ARCH).obj

## obj-$(CONFIG_UFSD_FS) += $(MODULE_NAME).o

$(MODULE_NAME)-y := $(MODULE_OBJECTS)

obj-m := $(MODULE_NAME).o ufsd_wrapper.o