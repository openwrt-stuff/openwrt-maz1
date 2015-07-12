#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


include $(TOPDIR)/rules.mk

PKG_NAME:=tsocks
PKG_VERSION:=git-20150611
PKG_RELEASE:=1


PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://github.com/Elysion-tcfa/tsocks.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=be36c83a7326c75123fa019a4cb53792ecd8f689

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/tsocks
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Transparent SOCKS v4 proxying library
  URL:=http://tsocks.sourceforge.net/
endef

define Package/tsocks/description
Transparent SOCKS v4 proxying library
endef

define Build/Configure
	$(call Build/Configure/Default,\
                  --with-conf=/etc/tsocks.conf \
	)
endef

define Package/tsocks/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/tsocks $(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/lib/libtsocks.so{,*} $(1)/usr/lib/
endef

$(eval $(call BuildPackage,tsocks))
