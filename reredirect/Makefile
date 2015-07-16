#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=reredirect
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/reredirect/Default
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=A tool to dynamically redirect outputs of a running program.
  URL:=https://github.com/jerome-pouiller/reredirect
  MAINTAINER:=maz-1
  DEPENDS:=+libc
endef

define Package/reredirect
	$(call Package/reredirect/Default)
endef

define Build/Install
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/reredirect/description
   	A tool to dynamically redirect outputs of a running program
endef

define Package/reredirect/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin/$(PKG_NAME)
endef

$(eval $(call BuildPackage,reredirect))
