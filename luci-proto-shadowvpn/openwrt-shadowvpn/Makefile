include $(TOPDIR)/rules.mk

PKG_NAME:=shadowvpn
PKG_VERSION:=0.2.0
PKG_RELEASE=3

PKG_SOURCE_URL:=https://github.com/clowwindy/ShadowVPN/releases/download/$(PKG_VERSION)
PKG_SOURCE:=shadowvpn-$(PKG_VERSION).tar.gz

PKG_MAINTAINER:=clowwindy <clowwindy42@gmail.com>
PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/ShadowVPN-$(PKG_VERSION)

PKG_INSTALL:=1
PKG_FIXUP:=autoreconf
PKG_USE_MIPS16:=0
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/shadowvpn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=ShadowVPN Proto
  DEPENDS:=+kmod-tun +resolveip +libsodium
  URL:=https://shadowvpn.org
endef

define Package/shadowvpn/description
A fast, safe VPN based on libsodium
    with native interface protocol support
endef

CONFIGURE_ARGS+= \
	--sysconfdir=/etc \
	--disable-static

define Package/shadowvpn/install
	$(INSTALL_DIR) $(1)/lib/netifd/proto
	$(INSTALL_BIN) ./files/shadowvpn.sh $(1)/lib/netifd/proto
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/shadowvpn $(1)/usr/bin
endef

$(eval $(call BuildPackage,shadowvpn))
