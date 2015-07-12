#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-nfsd
PKG_VERSION:=1.4
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-nfsd
  SECTION:=luci
  CATEGORY:=LuCI
  DEPENDS:=+nfs-kernel-server
  TITLE:=LuCI - Lua Configuration Interface
  URL:=http://
  MAINTAINER:=Jeroen Louwes <jeroen.louwes@gmail.com>
  SUBMENU:=3. Applications
  TITLE:=LuCI Support for nfsd
endef

define Package/luci-app-nfsd/description
A hotplug script that makes configuration of nfsd.
endef

define Build/Compile
endef

define Package/luci-app-nfsd/install
	$(CP) ./files/* $(1)
endef

$(eval $(call BuildPackage,luci-app-nfsd))
