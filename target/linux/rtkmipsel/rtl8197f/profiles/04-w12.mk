#
# Copyright (C) 2006-2018 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/w12
  NAME:=w12 Profile
  PRIORITY:=1
   PACKAGES:= \
 	  -odhcpd-ipv6only \
 	  -wpad-mini \
 	  hostapd-common \
 	  iw \
 	  iwinfo \
 	  kmod-button-hotplug \
 	  kmod-cfg80211 \
 	  kmod-gpio-button-hotplug \
 	  kmod-input-core \
 	  kmod-input-evdev \
 	  kmod-input-gpio-keys \
 	  kmod-ledtrig-netdev \
 	  kmod-mac80211 \
 	  kmod-rtl8192cd \
 	  wireless-tools \
 	  wpad-wolfssl \
  

endef

define Profile/w12/Description
	Default package set compatible with Tenda W12
endef
$(eval $(call Profile,w12))
