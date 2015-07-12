#
# Copyright (C) 2009-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=abduco
PKG_VERSION:=0.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.brain-dump.org/projects/abduco/
PKG_MD5SUM:=cc1e01b5333e36e01e058476ed3efa96
PKG_MAINTAINER:=maz-1 <ohmygod19993 at gmail dot com>
PKG_LICENSE:=ISC

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/abduco/Default
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=A session management and attach/detach functionality.
  URL:=http://www.brain-dump.org/projects/abduco/
  MAINTAINER:=maz-1
  DEPENDS:=+dvtm
endef

define Package/abduco
	$(call Package/abduco/Default)
endef

define Package/abduco/description
  A session management and attach/detach functionality.(to use together with dvtm(1)).
endef

define Package/abduco/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/bin/abduco
endef

$(eval $(call BuildPackage,abduco))
