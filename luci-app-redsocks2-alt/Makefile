#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-redsocks2-alt
PKG_VERSION:=1.1f
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-redsocks2-alt
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for redsocks2.
  DEPENDS:=+luci +redsocks2-alt
  PKGARCH:=all
  MAINTAINER:=maz-1
endef

define Package/luci-app-redsocks2-alt/description
Luci interface for redsocks.
endef

define Build/Compile
endef

define Package/luci-app-redsocks2-alt/postinst
#!/bin/sh
[ -n "${IPKG_INSTROOT}" ] || {
	( . /etc/uci-defaults/luci-redsocks2 ) && rm -f /etc/uci-defaults/luci-redsocks2
	chmod 755 /etc/init.d/redsocks2 >/dev/null 2>&1
	/etc/init.d/redsocks2 enable >/dev/null 2>&1
	exit 0
}

endef 

define Package/luci-app-redsocks2-alt/install
	$(CP) ./files/* $(1)
	rm $(1)/usr/lib/lua/luci/i18n/*.po
endef

$(eval $(call BuildPackage,luci-app-redsocks2-alt))
