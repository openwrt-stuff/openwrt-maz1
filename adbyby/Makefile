#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=adbyby
PKG_VERSION:=2.1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/adbyby
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=adbyby.
  DEPENDS:=+libc
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/adbyby/description
adbyby.
endef

define Build/Compile
endef


define Package/adbyby/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,adbyby))
