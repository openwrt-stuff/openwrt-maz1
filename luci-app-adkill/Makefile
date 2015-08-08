# Mantainer : maz-1 < ohmygod19993 at gmail dot com >

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-adkill
PKG_VERSION=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

PO2LMO:=$(STAGING_DIR_HOST)/bin/po2lmo

include $(INCLUDE_DIR)/package.mk

define Package/luci-app-adkill
	SECTION:=luci
	CATEGORY:=LuCI
	DEPENDS:=+kmod-adkill +luci
	SUBMENU:=3. Applications
	TITLE:=kmod-adkill for LuCI
	PKGARCH:=all
endef

define Package/luci-app-adkill/description
	This package contains LuCI configuration pages for kmod-adkill.
endef

define Package/luci-app-adkill/conffiles
/etc/config/adkill
endef

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/luci-app-adkill/install
	$(CP) ./files/* $(1)
	${PO2LMO} $(1)/usr/lib/lua/luci/i18n/adkill.zh-cn.po $(1)/usr/lib/lua/luci/i18n/adkill.zh-cn.lmo
	rm $(1)/usr/lib/lua/luci/i18n/adkill.zh-cn.po
endef

$(eval $(call BuildPackage,luci-app-adkill))
