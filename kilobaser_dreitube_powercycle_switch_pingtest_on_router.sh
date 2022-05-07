#!/usr/bin/zsh

##
## Run this minutely from cron
##

SONOFFHOST=dreitubeoutlet.lan
COUNTFILE=/tmp/failcount-dreitube
WANDEV=eth0.xx
MQTT_BROKER=xxxx

CMD_TOGGLE_MODEM=( wget -q -O /dev/null --post-data="" "http://${SONOFFHOST}/button/powercycle_drei-tube_steckdose/press" )
#CMD_TOGGLE_MODEM=( mosquitto_pub -h ${MQTT_BROKER} -p 1883 -t 'dreitubeoutlet/button/powercycle_drei-tube_steckdose/command' -m 'PRESS' )

if ! ip link show dev $WANDEV | grep -q UP,LOWER_UP; then
  ## might be down on purpouse
  exit 0
fi

GW=$(ip route show default dev $WANDEV | head -n1 | cut -d' ' -f 3)
if test -e $COUNTFILE ; then
  FAILCOUNT=$(( $(cat $COUNTFILE) ))
else
  FAILCOUNT=0
fi


if [[ -z $GW ]]; then
  #Not yet connected
  FAILCOUNT=$((FAILCOUNT +1))
  echo $FAILCOUNT > "$COUNTFILE"
  echo "gateway failcount: $FAILCOUNT"
else
  if ping -q -c3 "$GW" ; then
    ## reset fail count
    if [[ $FAILCOUNT -ne 0 ]]; then
      FAILCOUNT=0
      echo $FAILCOUNT > "$COUNTFILE"
      echo "gateway failcount: $FAILCOUNT"
    fi
  else
    ## increase fail count
    FAILCOUNT=$((FAILCOUNT +1))
    echo $FAILCOUNT > "$COUNTFILE"
    echo "gateway failcount: $FAILCOUNT"
  fi
fi

## every 20min if the problem persists and every 3h if it takes longer than 3h
if (( (FAILCOUNT % 20 == 0 && FAILCOUNT > 0 && FAILCOUNT < 60*3) || (FAILCOUNT >= 60*3 && FAILCOUNT % 60*3 == 0)  )); then
  echo "gateway recovery: cycling DreiTube"
#  ip link set down dev $IFWANDEV
  $CMD_TOGGLE_MODEM
#  ip link set up dev $IFWANDEV
fi
