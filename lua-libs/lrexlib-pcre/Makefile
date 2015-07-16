#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lrexlib-pcre
PKG_VERSION:=2.7.2
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/lrexlib-pcre/Default
  SUBMENU:=Lua
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=PCRE Library for Lua 5.1
  URL:=https://github.com/LuaDist/lrexlib-pcre
  MAINTAINER:=maz-1
  DEPENDS:=+lua +libpcre
endef

define Package/lrexlib-pcre
	$(call Package/lrexlib-pcre/Default)
endef

define Build/Install
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/lrexlib-pcre/description
   	PCRE Library for Lua 5.1
endef

define Package/lrexlib-pcre/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rex_pcre.so $(1)/usr/lib/lua/rex_pcre.so
endef

$(eval $(call BuildPackage,lrexlib-pcre))
