#
# Copyright (C) 2014 nanpuyue <nanpuyue@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libdvbcsa
PKG_VERSION:=1.1.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://download.videolan.org/pub/videolan/libdvbcsa/$(PKG_VERSION)/
#PKG_MD5SUM:=894da0e07a715dd8e44f8b3486093e70

PKG_MAINTAINER:=maz-1 <ohmygod19993@gmail.com>

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libdvbcsa
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=libdvbcsa
  URL:=http://www.videolan.org/developers/libdvbcsa.html
  MENU:=1
endef

define Package/libdvbcsa/description
 libdvbcsa is a free implementation of the DVB Common Scrambling
 Algorithm - DVB/CSA - with encryption and decryption capabilities
endef

CONFIGURE_ARGS += \
	--prefix=/usr 

define Build/Configure
	$(call Build/Configure/Default)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libdvbcsa.{a,so*} $(1)/usr/lib/
endef

define Package/libdvbcsa/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/src/.libs/libdvbcsa.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libdvbcsa))
