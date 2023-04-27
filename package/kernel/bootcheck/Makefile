include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=bootcheck
PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git@github.com:Inspectron/inspscript.git
PKG_SOURCE_VERSION:=917658ffb8bb102406c4640195589d5aecdca476

include $(INCLUDE_DIR)/package.mk

define KernelPackage/bootcheck
	TITLE:=Device reset after unsuccessful boot kernel module
	SECTION:=kernel
	CATEGORY:=inspectron
	FILES:=$(PKG_BUILD_DIR)/bootcheck/modules/bootcheck.ko
	AUTOLOAD:=$(call AutoLoad,10,bootcheck)
endef

include $(INCLUDE_DIR)/kernel-defaults.mk

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(DL_DIR)/$(PKG_SOURCE) $(PKG_BUILD_DIR)/
	xzcat $(PKG_BUILD_DIR)/$(PKG_SOURCE) | tar -C $(PKG_BUILD_DIR)/ -xf -

	mv $(PKG_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)/* $(PKG_BUILD_DIR)/
	rm -rf $(PKG_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
	$(Build/Patch)
endef

define Build/Compile
	$(KERNEL_MAKE) SUBDIRS="$(PKG_BUILD_DIR)/bootcheck/modules" \
		MODFLAGS="-DMODULE -mlong-calls" \
		modules

#	echo "============================================================================================="
#	echo $(LINUX_KARCH)
#	echo $(LINUX_DIR)
#	echo $(LINUX_UAPI_DIR)
#	$(MAKE) -C "$(LINUX_DIR)" \
#		$(KERNEL_MAKE_FLAGS) \
#		SUBDIRS="$(PKG_BUILD_DIR)/bootcheck/modules" \
#		$(PKG_EXTRA_KCONFIG) \
#		LINUXINCLUDE="-I$(LINUX_DIR)/include \
#			-Iarch/$(LINUX_KARCH)/include/uapi/asm/ \
#			-I$(LINUX_DIR)/include/generated/uapi/ -Iarch/$(LINUX_KARCH)/include \
#			-Iarch/$(LINUX_KARCH)/include/$(LINUX_UAPI_DIR) \
#			-Iarch/$(LINUX_KARCH)/include/generated \
#			-Iarch/$(LINUX_KARCH)/include/generated/$(LINUX_UAPI_DIR) \
#			-include generated/autoconf.h" \
#			V="$(V)" \
#			modules
endef

#define Build/Compile
#        $(KERNEL_MAKE) SUBDIRS="$(PKG_BUILD_DIR)/bootcheck/modules" \
#                MODFLAGS="-DMODULE -mlong-calls" \
#                modules
#endef

$(eval $(call KernelPackage,bootcheck))
