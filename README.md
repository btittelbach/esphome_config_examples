# esphome_config_examples
a collection of esphome configurations, possibly useful as example for others

### bathroom_devices_charging_on_schedule_s26.yaml

Sonoff S20 outlet which powers stuff like e.g. electric rasor etc
Device should charge only twice a week for three hours, in order to 
minimize the evaporation of the rasor cleaning fluid which is otherwise
heated permanently and needs to be changed much more often.

### dehumidifier_automation_s20_bme280.yaml

Switches a dehumidifer via Sonoff S20 outlet
measure humidity, temperature and pressure via BME280
automatically switches Dehumidifier on if humidity exceedes some treshold

### dishwasher_s20_bme280.yaml

Simple appliance controlled via Sonoff S20 outlet
and on the side, measure humidity, temperature and pressure via BME280

### gegensprechanlage_esp32.yaml

Experimental. Work in progress.

Put an ESP32 (or optionally permanently powered) relais between
the doorbell and the door opener.

- Silence the doorbell via homeassistant
- open the front door via homeassitant

### gpio_tristate_output.h

Custom Class that allows for tri-stating outputs
- HIGH
- LOW
- Z aka High Impedance

### kilobaser_dreitube_powercycle

Use with Sonoff S20/S26 outlet
powercycles a Drei-Tube 5G Router (fallback uplink)
in case a script decides the router has crashed or the GW is no longer reachabe
(which happens irregularly)

### kueche_wallswitch_t4eu1c.yaml

Simple example controlling a Sonoff T4eu1C WiFi Wall Switch

### r3_olgadecke_wallswitch_t4eu1c.yaml

Another example controlling a Sonoff T4eu1C WiFi Wall Switch

### livingroomsensor_wemosD1mini.yaml

Simple ESP8266 D1 Mini with three sensor connected via I2C
Sensors:
- BH1750 illuminance
- HTU21D temperature + humidity
- BMP180 temperature + pressure

### luster_power_mode_cycle_sonoff_dual_r2.yaml

Control two ceiling lights using a Sonoff Dual R2
the second of which can cycle between Cold-White, Warm-White and Full-Light-Both-White if you power-cycle it quickly
The esp tracks which mode is currently active and exports it as an effect to homeassistant

### new_Sxx.yaml

Template configuration.

I use this to pre-flash Sonoff S20, so they can be quickly deployed later. Homeassistant API and mqtt are disabled.

### pcpower_sonoff_pow.yaml

Sonoff Pow Example

which monitors a PCs power for
- statistics
- in order for PC to act as master-power to switch other devices via homeassistant
- to visualize power useage via it's LED

### r3_subtable_sonoff_pow.yaml

another Sonoff Pow example

which switches a light and visualizes power useage via it's LED

### rollo_zb35_esp8266.yaml

Control a GW60 blinds motor / rollandenmotor using a ZB35 remote hacked with an esp8266.

see https://wiki.realraum.at/xro:rollohack_gw60

the remote's buttons remain useable, by using the custom MyTriStateOutput class.

### switcharbeitszimmer_powercycle

Workaround for old buggy switch before it was replaced (likely it was just the power-supply, but the S20 was on hand)
it's a good example for an appliance that
- needs regular powercycling (3 times a week)
- needs automatic powercycling on external trigger (wget/curl)

### windowlight_h801.yaml

Example for esp8266 based H801 (controls 5 low-side mosfets for 5V-24V RGB-WW-CW led strips)

In this case it controls two lights:
- a single-colour WW LED strip mounted around the window, simulating daylight
- as well as a RGB+W LED strip mounted below the desk
  - which also implements a random-colour effect