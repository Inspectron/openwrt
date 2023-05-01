#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=bootcheck
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/bootcheck
  SUBMENU:=Other modules
  TITLE:=Device reset after unsuccessful boot kernel module
  FILES:=$(PKG_BUILD_DIR)/bootcheck.ko
  AUTOLOAD:=$(call AutoLoad,10,bootcheck,1)
  DEPENDS:=+libstdcpp
  KCONFIG:=
endef

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	SUBDIRS="$(PKG_BUILD_DIR)"
	LINUXINCLUDE="-I$(LINUX_DIR)/include \
	-I$(LINUX_DIR)/include/$(LINUX_UAPI_DIR) \
	-Iarch/$(LINUX_KARCH)/include \
	-Iarch/$(LINUX_KARCH)/include/$(LINUX_UAPI_DIR) \
	-I$(BUILD_DIR)/uClibc++-0.2.5/include "

define Build/Compile
	echo "========================================================================"
	echo $(BUILD_DIR)
	echo $(LINUX_DIR)
	echo $(PKG_BUILD_DIR)
	echo "========================================================================"


	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,bootcheck))

