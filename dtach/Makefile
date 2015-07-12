#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dtach
PKG_VERSION:=0.8
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/dtach
PKG_MD5SUM:=ec5999f3b6bb67da19754fcb2e5221f3
PKG_MAINTAINER:=maz-1 <ohmygod19993 at gmail dot com>
PKG_LICENSE:=GPL

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dtach/Default
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=A program that emulates the detach feature of screen
  URL:=http://dtach.sourceforge.net/
  MAINTAINER:=maz-1
  DEPENDS:=+libc
endef

define Package/dtach
	$(call Package/dtach/Default)
endef

define Build/Install
endef

define Package/dtach/description
  A program that emulates the detach feature of screen
endef

define Package/dtach/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin/dtach
endef

$(eval $(call BuildPackage,dtach))
