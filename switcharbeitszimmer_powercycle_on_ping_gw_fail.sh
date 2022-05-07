#!/bin/sh
## run this with cron every minute
## script is simple enough to run on openwrt

#SONOFFHOST=switcharbeitszimmer.local ##let us hope AP caches hostname for at least that minute via dnsmasq
				      ## .local is mdns and only works with mdnsresolver on local system
SONOFFHOST=192.168.x.x
GW=192.168.x.x

## cache DNS entry in local dnsmasq
ping -q -c1 "$SONOFFHOST"

## powercycle if gw not pingable through switch
if ! ping -q -c2 "$GW" && ! ping -q -c2 "$GW" ; then
  #curl -d "" http://${SONOFFHOST}/switch/powercycle_switch/toggle
  wget -q -O /dev/null --post-data="" http://${SONOFFHOST}/switch/powercycle_switch/toggle &
fi
