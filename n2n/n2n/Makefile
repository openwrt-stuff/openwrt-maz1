
include $(TOPDIR)/rules.mk

PKG_NAME:=n2n
PKG_REV=5f424b8
PKG_VERSION:=2.1_git_$(PKG_REV)
PKG_RELEASE:=10
PKG_LICENSE:=GPLv3
PKG_LICENSE_FILES:=LICENSE

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REV).tar.bz2
PKG_SOURCE_URL:=https://github.com/maz-1/n2n_v2.git

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)/$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/n2n-edge
  SECTION:=net
  CATEGORY:=Network
  TITLE:=N2N VPN tunneling daemon(V2)
  URL:=http://www.ntop.org/n2n/
  SUBMENU:=VPN
  DEPENDS:=+libpthread +kmod-tun +libopenssl +resolveip +N2N_POLARSSL:libpolarssl +N2N_OPENSSL:libopenssl \
	+N2N_IPROUTE2:ip-full
endef

define Package/n2n-supernode
  SECTION:=net
  CATEGORY:=Network
  TITLE:=N2N VPN tunneling daemon(V2)
  URL:=http://www.ntop.org/n2n/
  SUBMENU:=VPN
  DEPENDS:=+libpthread
endef

define Package/n2n-edge/config
	source "$(SOURCE)/Config.in"
endef

N2N_SED=sed -i

ifeq ($(CONFIG_N2N_POLARSSL),y)
  N2N_SED+= -e 's/N2N_OPTION_POLARSSL:="no"/N2N_OPTION_POLARSSL:="yes"/g'
endif

ifeq ($(CONFIG_N2N_IPROUTE2),y)
  N2N_SED+= -e 's/N2N_HAVE_IPROUTE2:="no"/N2N_HAVE_IPROUTE2:="yes"/g'
endif

ifeq ($(N2N_SED),sed -i)
  N2N_SED:=true
endif

define Build/Compile
	$(N2N_SED) $(PKG_BUILD_DIR)/Makefile
	$(call Build/Compile/Default)
endef

define Package/n2n-edge/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/edge $(1)/usr/sbin/
	#$(INSTALL_DIR) $(1)/lib/netifd/proto
	#$(INSTALL_BIN) ./files/n2n.sh $(1)/lib/netifd/proto
endef

define Package/n2n-supernode/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/supernode $(1)/usr/sbin/
	#$(INSTALL_DIR) $(1)/etc/init.d
	#$(INSTALL_BIN) ./files/n2n-supernode.init $(1)/etc/init.d/n2n
	#$(INSTALL_DIR) $(1)/etc/config
	#$(INSTALL_DATA) ./files/n2n-supernode.config $(1)/etc/config/n2n
endef

$(eval $(call BuildPackage,n2n-edge))
$(eval $(call BuildPackage,n2n-supernode))
