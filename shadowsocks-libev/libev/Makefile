#
# Copyright (C) 2009-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libev
PKG_VERSION:=4.20
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://dist.schmorp.de/$(PKG_NAME)/
PKG_MD5SUM:=285072f72d776500b7fb064b35e5f4d9

PKG_FIXUP:=libtool autoreconf
PKG_USE_MIPS16:=0
PKG_INSTALL:=1

PKG_MAINTAINER:=maz1 <ohmygod19993 at gamil dot com>
PKG_LICENSE:=GPL

include $(INCLUDE_DIR)/package.mk

define Package/libev
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=A full-featured and high-performance event loop
  URL:=http://software.schmorp.de/pkg/libev.html
  MAINTAINER:=maz1 <ohmygod19993 at gamil dot com>
endef

define Package/libev/description
  A full-featured and high-performance event loop
endef


CONFIGURE_ARGS+= \
	--disable-ssp \


define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/ev.h $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/ev++.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libev.{a,so*} $(1)/usr/lib
endef

define Package/libev/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libev.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libev))
