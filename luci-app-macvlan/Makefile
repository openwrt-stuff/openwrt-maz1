#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-macvlan
PKG_VERSION:=1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-macvlan
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for MacVLan.
  DEPENDS:=+luci +kmod-macvlan
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/luci-app-macvlan/description
MacVLan Configuration.
endef

define Build/Compile
endef


define Package/luci-app-macvlan/install
	$(CP) ./files/* $(1)
	rm $(1)/usr/lib/lua/luci/i18n/macvlan.zh-cn.po
endef

$(eval $(call BuildPackage,luci-app-macvlan))
