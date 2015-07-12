#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-epg-oscam
PKG_VERSION:=1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-epg-oscam
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for oscam.
  DEPENDS:=+luci +oscam
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/luci-app-epg-oscam/description
MacVLan Configuration.
endef

define Build/Compile
endef


define Package/luci-app-epg-oscam/install
	$(CP) ./files/* $(1)
	chmod +x $(1)/usr/bin/epg
endef

$(eval $(call BuildPackage,luci-app-epg-oscam))
