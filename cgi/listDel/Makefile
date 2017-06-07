# 
# Copyright (C) 2006-2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=zio_garp
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/zio_garp

include $(INCLUDE_DIR)/package.mk

define Package/zio_garp
  SECTION:=net
  CATEGORY:=Network
  TITLE:=zio gARP Request
  DEPENDS:=+libc
endef

define Package/zio_garp/description
 	Wan Interface gARP Request Program
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/zio_garp/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/zio_garp $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/zio_garp.init $(1)/etc/init.d/zio_garp
endef

$(eval $(call BuildPackage,zio_garp))
