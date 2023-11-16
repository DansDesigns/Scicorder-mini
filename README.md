# Ultra-Slim-Tricorder
A multi sensor device based on ESP32, Inspired by Star Trek TNG Tricorder

NOTE, THIS IS STILL IN DEVELOPMENT AND CURRENTLY AROUND 85% DONE..

Youtube Development Channel:
https://www.youtube.com/channel/UC_F5HQEmCyoRnEubfEMa24g

No copyright infringment intended, this is purely an exercise in fun and an homage to some great Sci-Fi Technology!


Hardware:
```
ESP32-WROOM-32e
NS8002 Amplifier Module
8ohm 1Watt Speaker
Wireless Charging with internal TP4056 LiPo Charger
MPR121 12-Channel Capacitive Touch Sensor
Red/Green Power Status LED
Tricolour Status LED's

Integrated Sensors:
INMP441 I2S Mono Microphone
VL53L0X ToF Laser Distance Sensor
HMC5883L Magnetometer
BME280 Environmental Temperature, Humidity, Pressure & Altitude Sensor
SI1145 Visible Light, UV & IR Sensor
LTR-3900-UV UVA & UVB Sensor
TCS3200 RGB Colour Sensor
MPU6050 3-Axis Accelerometer, 3-Axis Gyroscope
  & Internal Temperature Sensor all-in-one
Magnetic Open-Close Lid Sensor
microSD Card Slot for Data Logging
Custom Dust/Particle Density Sensor


3D Printed Case featuring Electroplated Gold Capacitive Buttons & Highlights.
```

## Hardware Setup
```

```

## Code & Libraries
```

Arduino Tones library is used to generate the different notification sounds.

Capacitive Touch is powered by the MPR121 chip aswell as using the ESP32's onboard Capacitive Touch Pins

I2S Microphone Streaming was modified from here:
- https://github.com/pschatzmann/arduino-audio-tools/tree/main

Wifi Manager was taken from here:
- https://github.com/ozbotics/WIFIMANAGER-ESP32/tree/master


```

## Installation
```
If building yourself, Flash the OTA_Installer.ino to the ESP32 via Arduino IDE.

On reboot the OTA Updater will search GitHub for the latest Release,
it automatically Downloads, Installs and Reboots the Tricorder.

Wifi will then need to be setup again by using the Setup_AP Function.
- RETAIN SSID BETWEEN UPDATES - WIP

Manual checking for update is possible by typing "U" into the Serial Monitor.

If need to change WIFI SSID, press the WIFI Button and connect to the
"Setup_AP" WIFI Access Point from a wifi enabled device, following the on screen instructions.
```

## Usage
```


```

## ToDo
```
WIP = In Progress, TBS = To Be Started , TBD = To Be Decided, R&D = Research needed

- Make simple OTA_Installer.ino starter file to run OTA updater, pulling latest Release to flash full working code. - DONE
- Finish this ReadMe..

```

```
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

```



