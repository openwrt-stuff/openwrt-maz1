#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mono
_PKG_VERSION:=4.0.1.44
PKG_VERSION=4.0.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(_PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://download.mono-project.com/sources/mono/
PKG_MD5SUM:=d55c9d8aab2cdfde53f830ae6ea75358
PKG_MAINTAINER:=maz-1 <ohmygod19993 at gmail dot com>
PKG_LICENSE:=GPL

PKG_INSTALL:=1
PKG_USE_MIPS16:=0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/mono/Default
  SUBMENU:=Mono
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Free implementation of the .NET platform.
  URL:=http://www.mono-project.com/
  MAINTAINER:=maz-1
  DEPENDS:=+libc +zlib +libpthread +libstdcpp +librt +libattr
endef

define Package/mono
	$(call Package/mono/Default)
endef

define Package/mono/description
  Free implementation of the .NET platform.
endef

CONFIGURE_ARGS += --disable-gtk-doc \
	--with-mcs-docs=no \
	--with-moonlight=no \
	--with-ikvm-native=no \
	--enable-minimal=aot,profiler,debug \
	--enable-static

define Package/Compile
	cd $(PKG_BUILD_DIR) && make EXTERNAL_MCS=false EXTERNAL_RUNTIME=false
endef

define Package/mono/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/usr/lib $(1)/usr/share $(1)/etc/
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/mono-sgen $(1)/usr/bin/mono
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so{,*} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/mono-2.0 $(1)/usr/share
	$(CP) $(PKG_INSTALL_DIR)/usr/share/locale $(1)/usr/share
	$(CP) $(PKG_INSTALL_DIR)/etc/mono $(1)/etc/mono
endef

$(eval $(call BuildPackage,mono))
