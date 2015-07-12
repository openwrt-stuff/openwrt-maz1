#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-adbyby
PKG_VERSION:=1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-adbyby
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=adbyby.
  DEPENDS:=+luci +adbyby
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/luci-app-adbyby/description
adbyby.
endef

define Build/Compile
endef


define Package/luci-app-adbyby/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,luci-app-adbyby))
