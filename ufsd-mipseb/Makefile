#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ufsd

PKG_VERSION:=8.9.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk


define KernelPackage/ufsd
  SUBMENU:=Filesystems
  TITLE:=Paragon ufsd for mipseb
  DEPENDS:=+kmod-nls-base +kmod-nls-utf8 @TARGET_ar71xx
#  DEFAULT:=y if (CONFIG_TARGET_ramips_mt7620n || CONFIG_TARGET_ramips_mt7620a)
  FILES:=$(PKG_BUILD_DIR)/ufsd_wrapper.ko \
$(PKG_BUILD_DIR)/ufsd.ko 
  AUTOLOAD:=$(call AutoLoad,50,ufsd_wrapper ufsd)
endef

define KernelPackage/ufsd/description
Paragon ufsd is a fs driverof ntfs
endef

#define KernelPackage/raeth/config
#	source "$(SOURCE)/config.in"
#endef

SOURCE_DIR:=$(PKG_BUILD_DIR)
export SOURCE_DIR

MAKEOPTS:= -C $(LINUX_DIR) \
                ARCH="$(LINUX_KARCH)" \
                CROSS_COMPILE="$(TARGET_CROSS)" \
                M="$(PKG_BUILD_DIR)" \
		CONFIG_UFSD_FS=m \
		modules

define Build/Prepare
	$(call Build/Prepare/Default)
	echo $(LINUX_DIR)|grep 3.18 && cp -r src-3.18/. $(PKG_BUILD_DIR) || cp -r src-4.1/. $(PKG_BUILD_DIR)
	#$(CP) -r src-4.1/. $(PKG_BUILD_DIR)
	$(CP) obj/libufsd_mips.obj $(PKG_BUILD_DIR)/
endef


define Build/Compile
	$(MAKE) $(MAKEOPTS)
endef

define KernelPackage/ufsd/install
endef



$(eval $(call KernelPackage,ufsd))
