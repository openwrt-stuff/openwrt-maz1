include $(TOPDIR)/rules.mk

PKG_NAME:=uksmtools
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/uksmtools
  SECTION:=utils
  CATEGORY:=Utilities
	TITLE:=Tools to control uksm.
	MAINTAINER:=maz1 <ohmygod19993 at gmail dot com>
endef

define Package/uksmtools/description
	Tools to control uksm.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/uksmtools/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uksmctl/uksmctl $(1)/usr/sbin/uksmctl
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uksmstat/uksmstat $(1)/usr/sbin/uksmstat
endef

$(eval $(call BuildPackage,uksmtools))
