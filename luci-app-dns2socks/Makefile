#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-dns2socks
PKG_VERSION:=1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-dns2socks
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=dns2socks.
  DEPENDS:=+luci +dns2socks
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/luci-app-dns2socks/description
dns2socks.
endef

define Build/Compile
endef


define Package/luci-app-dns2socks/install
	$(CP) ./files/* $(1)
	rm $(1)/usr/lib/lua/luci/i18n/dns2socks.zh-cn.po
endef

$(eval $(call BuildPackage,luci-app-dns2socks))
