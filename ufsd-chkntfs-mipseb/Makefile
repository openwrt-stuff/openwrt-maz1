#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ufsd-chkntfs
PKG_VERSION:=8.9.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/ufsd-chkntfs
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  DEPENDS:=+kmod-ufsd @TARGET_ar71xx
  TITLE:=chkntfs from paragon ufsd
endef

define Package/ufsd-chkntfs/description
chkntfs from paragon ufsd
endef

define Build/Compile
endef

define Package/ufsd-chkntfs/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) ./files/chkntfs $(1)/usr/sbin/chkntfs
	cd $(1)/usr/sbin
	chmod +x $(1)/usr/sbin/chkntfs
	ln -s chkntfs $(1)/usr/sbin/fsck.ntfs
	ln -s chkntfs $(1)/usr/sbin/fsck.ufsd
endef

$(eval $(call BuildPackage,ufsd-chkntfs))



















