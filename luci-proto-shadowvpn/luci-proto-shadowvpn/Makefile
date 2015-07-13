include $(TOPDIR)/rules.mk

PKG_NAME:=luci-proto-shadowvpn
PKG_VERSION:=1.0
PKG_RELEASE:=2
PKG_MAINTAINER:=Jason Tse <jasontsecode@gmail.com>
PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/luci-proto-shadowvpn
   SECTION:=luci
   CATEGORY:=LuCI
   SUBMENU:=5. Protocols
   DEPENDS:=+shadowvpn
   TITLE:=ShadowVPN protocol support for LuCI
   MAINTAINER:=Jason Tse <jasontsecode@gmail.com>
   PKGARCH:=all
endef

define Package/luci-proto-shadowvpn/description
ShadowVPN protocol support for LuCI
endef

define Package/luci-proto-shadowvpn/install
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/cbi/admin_network
	$(INSTALL_DATA) ./files/cbi/proto_svpn.lua $(1)/usr/lib/lua/luci/model/cbi/admin_network
	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/network
	$(INSTALL_DATA) ./files/network/proto_svpn.lua $(1)/usr/lib/lua/luci/model/network
endef

define Build/Compile
endef

$(eval $(call BuildPackage,luci-proto-shadowvpn))
