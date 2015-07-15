#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-lib-lrexlib-pcre
PKG_VERSION:=2.7.2
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-lib-lrexlib-pcre/Default
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=6. Libraries
  TITLE:=PCRE Library for Lua 5.1
  URL:=https://github.com/LuaDist/lrexlib-pcre
  MAINTAINER:=maz-1
  DEPENDS:=+luci +libpcre
endef

define Package/luci-lib-lrexlib-pcre
	$(call Package/luci-lib-lrexlib-pcre/Default)
endef

define Build/Install
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/luci-lib-lrexlib-pcre/description
   	PCRE Library for Lua 5.1
endef

define Package/luci-lib-lrexlib-pcre/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rex_pcre.so $(1)/usr/lib/lua/rex_pcre.so
endef

$(eval $(call BuildPackage,luci-lib-lrexlib-pcre))
