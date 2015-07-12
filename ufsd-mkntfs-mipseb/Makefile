#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ufsd-mkntfs
PKG_VERSION:=8.9.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/ufsd-mkntfs
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  DEPENDS:=+kmod-ufsd @TARGET_ar71xx
  TITLE:=mkntfs from paragon ufsd
endef

define Package/ufsd-mkntfs/description
mkntfs from paragon ufsd
endef

define Build/Compile
endef

define Package/ufsd-mkntfs/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) ./files/mkntfs $(1)/usr/sbin/mkntfs
	cd $(1)/usr/sbin
	chmod +x $(1)/usr/sbin/mkntfs
	ln -s mkntfs $(1)/usr/sbin/mkfs.ntfs
	ln -s mkntfs $(1)/usr/sbin/mkfs.ufsd
endef

$(eval $(call BuildPackage,ufsd-mkntfs))



















