#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-cpulimit
PKG_VERSION:=1.4
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-cpulimit
  SECTION:=luci
  CATEGORY:=LuCI
  DEPENDS:=+cpulimit-ng
  TITLE:=LuCI - Lua Configuration Interface
  URL:=http://
  MAINTAINER:=Jeroen Louwes <jeroen.louwes@gmail.com>
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for cpulimit-ng
endef

define Package/luci-app-cpulimit/description
A hotplug script that makes configuration of cpulimit.
endef

define Build/Compile
endef

define Package/luci-app-cpulimit/install
	$(CP) ./files/* $(1)
	chmod +x $(1)/etc/init.d/*
	chmod +x $(1)/usr/bin/*
endef

$(eval $(call BuildPackage,luci-app-cpulimit))
