#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lua-llthreads2
PKG_VERSION:=2.7.2
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/lua-llthreads2/Default
  SUBMENU:=Lua
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=llthreads library rewritten without LuaNativeObjects code generator 
  URL:=https://github.com/moteus/lua-llthreads2/
  MAINTAINER:=maz-1
  DEPENDS:=+lua +libpthread
endef

define Package/lua-llthreads2
	$(call Package/lua-llthreads2/Default)
endef

define Build/Install
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/lua-llthreads2/description
   	llthreads library rewritten without LuaNativeObjects code generator
endef

define Package/lua-llthreads2/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/llthreads.so $(1)/usr/lib/lua/llthreads.so
endef

$(eval $(call BuildPackage,lua-llthreads2))
