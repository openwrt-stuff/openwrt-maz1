#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vpncert-clean
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/vpncert-clean
  SECTION:=LuCI
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=vpncert-clean.
  PKGARCH:=all
  MAINTAINER:=maz-1
endef

define Package/vpncert-clean/description
vpncert-clean.
endef

define Build/Compile
endef

define Package/vpncert-clean/postinst
#!/bin/sh 

[ -n "${IPKG_INSTROOT}" ] || {
	( . /etc/uci-defaults/vpncert-clean ) && rm -f /etc/uci-defaults/vpncert-clean
	/etc/init.d/vpncert-clean enable  >/dev/null 2>&1	
}
endef 

define Package/vpncert-clean/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,vpncert-clean))
