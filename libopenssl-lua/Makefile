#
# Copyright (C) 2007-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lua-openssl
PKG_VERSION:=0.2.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_REV).tar.bz2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_REV=8cf78fd
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_URL:=https://github.com/zhaozg/lua-openssl.git

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/libopenssl-lua
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Openssl binding for Lua
  URL:=https://github.com/zhaozg/lua-openssl
  DEPENDS:=+libc +lua +libopenssl +librt
endef

define Package/libopenssl-lua/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openssl.so $(1)/usr/lib/lua/openssl.so
endef

$(eval $(call BuildPackage,libopenssl-lua))
