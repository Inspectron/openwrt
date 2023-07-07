include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=inspscript
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:= git@github.com:Inspectron/inspscript.git
PKG_SOURCE_VERSION:=e391c1d9bf3666a2f6e2c32736556e415c4bd56c

include $(INCLUDE_DIR)/package.mk

# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/inspscript
	SECTION:=inspectron
	CATEGORY:=inspectron
	TITLE:=inspscript
endef

# Package description; a more verbose description on what our package does
define Package/inspscript/description
	This package adds boot script and wireless config to snap-on board
endef

define Build/Compile
	#$(warning add commands to compile inspscript)
endef

# Install boot and wireless config
define Build/InstallDev
	# Install boot
	$(INSTALL_DIR) $(1)/etc/init.d
	$(CP) $(PKG_BUILD_DIR)/snaponBoot $(1)/etc/init.d

	# Install wireless config
	$(INSTALL_DIR) $(1)/etc/config
	$(CP) $(PKG_BUILD_DIR)/snapon_wireless_config $(1)/etc/config/wireless

	# Install uboot env config
	$(INSTALL_DIR) $(1)/etc/config
	$(CP) $(PKG_BUILD_DIR)/fw_env.config $(1)/etc/fw_env.config

	# Install script to kill HDLE application and toggles GPIO pin to shutdown the device
	$(INSTALL_DIR) $(1)/root
	$(CP) $(PKG_BUILD_DIR)/kill_appln_toggle_gpio.sh $(1)/root

	# Install script to enable yellow power led
	$(INSTALL_DIR) $(1)/root
	$(CP) $(PKG_BUILD_DIR)/set_power_led_yellow.sh $(1)/root

	# Install new mosquitto config
	$(INSTALL_DIR) $(1)/etc/mosquitto
	$(CP) $(PKG_BUILD_DIR)/handle_mosquitto.conf $(1)/etc/mosquitto/mosquitto.conf

	# Update mosquitto init.d config
	$(CP) $(PKG_BUILD_DIR)/mosquitto $(TOPDIR)/feeds/packages/net/mosquitto/files/etc/init.d/mosquitto
endef

define Package/inspscript/install
	# Install boot
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/snaponBoot $(1)/etc/init.d

	# Install wireless config
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/snapon_wireless_config $(1)/etc/config/wireless

        # Install uboot env config
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fw_env.config $(1)/etc/fw_env.config

	# Install script to kill HDLE application and toggles GPIO pin to shutdown the device
	$(INSTALL_DIR) $(1)/root
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/kill_appln_toggle_gpio.sh $(1)/root

	# Install script to enable yellow power led
	$(INSTALL_DIR) $(1)/root
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/set_power_led_yellow.sh $(1)/root

	# Install new mosquitto config
	$(INSTALL_DIR) $(1)/etc/mosquitto
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/handle_mosquitto.conf $(1)/etc/mosquitto/mosquitto.conf
endef

$(eval $(call BuildPackage,inspscript))
