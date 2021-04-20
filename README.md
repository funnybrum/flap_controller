# Flap Controller

Controll two servos attached to an ESP8266. These are regular RC servos and they are attached to a ventilation flap valve. There are two parameters configured for each flap - duty cycle for closed and for opened valve. The implemented REST api allows to set air flow through each of the valves in percentage (0 is closed, 100 is fully open).

The OTA is supported. Use the regular /update API to upload new version of the sketch.

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```