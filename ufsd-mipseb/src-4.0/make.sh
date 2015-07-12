#!/bin/sh
ROOTDIR=/build/360c301
STAGING_DIR=$ROOTDIR/staging_dir
PATH1=`echo $ROOTDIR/staging_dir/toolchain-mips_34kc_gcc-*-linaro_uClibc-*/bin`
KSDIR=`echo $ROOTDIR/build_dir/target-mips_34kc_uClibc-*/linux-ar71xx_generic/linux-3.*/`
HOST=192.168.1.1
echo =================
echo add path $PATH1
echo ksdir is $KSDIR
echo copy to host: $HOST
echo =================

export PATH=$PATH1:$PATH
export STAGING_DIR

make -C $KSDIR CROSS_COMPILE=mips-openwrt-linux-uclibc- ARCH=mips M=$ROOTDIR/build_dir/ufsd1 $*
if [ "$?" = 0 -a -e ufsd.ko ] ; then
	scp ufsd.ko root@$HOST:/root/
fi

## generate config.h
## ./configure --host=mips-openwrt-linux-1 --target=mips-openwrt-linux-1 \
##	--with-ks-dir=/build/maindev/build_dir/target-mips_34kc_uClibc-0.9.33.2/linux-ar71xx_generic/linux-3.10.49/ \
##  --with-kb-dir=/build/maindev/build_dir/target-mips_34kc_uClibc-0.9.33.2/linux-ar71xx_generic/linux-3.10.49/ 

## how to make libufsd_mips.bin
##  1. copy it from ufsd.ko mips big endian version.
##  2. strip .modinfo
##  3. shiftname libufsd_mips.o  init_module cleanup_module __this_module
##  4. set a list of func to weak.
##  5. change .gnu.linkonce.this_module to something like .Hnu.linkonCE.This_module
##  6. done!
