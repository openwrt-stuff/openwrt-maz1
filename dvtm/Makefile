#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dvtm
PKG_VERSION:=0.14
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.brain-dump.org/projects/dvtm/
PKG_MD5SUM:=44ec5176b1996fdffd97cabe9a35ea0c
PKG_MAINTAINER:=maz-1 <ohmygod19993 at gmail dot com>
PKG_LICENSE:=ISC

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dvtm/Default
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Tiling window management for the console.
  URL:=http://www.brain-dump.org/projects/dvtm/
  MAINTAINER:=maz-1
  DEPENDS:=+libc +libncursesw
endef

define Package/dvtm
	$(call Package/dvtm/Default)
endef

define Package/dvtm/description
  Tiling window management for the console.
endef

define Package/dvtm/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin/dvtm
endef

$(eval $(call BuildPackage,dvtm))
