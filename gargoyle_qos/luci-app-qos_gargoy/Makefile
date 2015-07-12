#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-qos_gargoyle
PKG_VERSION:=1.1f
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-qos_gargoyle
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for qos_gargoyle.
  DEPENDS:=+luci +gargoyle-firewall-util +libericstools +libiptbwctl +qos-gargoyle
  PKGARCH:=all
  MAINTAINER:=maz1
endef

define Package/luci-app-qos_gargoyle/description
qos_gargoyle.
endef

define Build/Compile
endef

define Package/luci-app-qos_gargoyle/postinst
#!/bin/sh 

[ -n "${IPKG_INSTROOT}" ] || {
	/etc/init.d/qos_gargoyle enable
	exit 0
}
endef 

define Package/luci-app-qos_gargoyle/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,luci-app-qos_gargoyle))
