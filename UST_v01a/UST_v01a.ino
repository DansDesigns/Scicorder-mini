
/*
        UST - Ultra-Slim Tricorder - V0.1a

        Software:
                  - GUI: TFT_eSPI
        Hardware:
                  -

*/


// Libraries:

// File System & File Browser:
#include "FS.h"
#include <LittleFS.h>
#include <EEPROM.h>
//#include <SD_MMC.h>
//#include <SD.h>
#include <ESPxWebFlMgr.h>

// System Hardware:
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_MPR121.h>            // Capacitive Touch Sensor @ 0x5A
//#include "Arduino-MAX17055_Driver.h"    // Battery monitor

// Wifi:
#include <WiFi.h>
#include "WebServer.h"    //https://github.com/zhouhan0126/WebServer-esp32
#include "DNSServer.h"    //https://github.com/zhouhan0126/DNSServer---esp32
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>  //https://github.com/ozbotics/WIFIMANAGER-ESP32
#include "ArduinoJson.h"  //https://github.com/bblanchon/ArduinoJson
#include "cert.h"

// Graphics:

//      TFT_eSPI
#include "TFT_eSPI.h"
// Included Fonts:
#include "TimeBurner12.h"
#define timeburner12 TimeBurner12
#include "Aspergit.h"
#define aspergit18 Aspergit
#include "NotoSansBold15.h"
#define SansBold15 NotoSansBold15
#include "Trench35.h"
#define trench35 Trench35
#include "Trench28.h"
#define trench28 Trench28


//    Adafruit_GFX
//#include "Adafruit_GFX.h"               // Core graphics library
//#include "Adafruit_SSD1351.h"           // 1.5" OLED library
// Included Fonts:
//#include "Whipsmart_XMvZ8pt7b.h"
//#include <Fonts/FreeSans12pt7b.h>

// Audio:
#include <DacESP32.h>


// Sensors:
#include <Adafruit_Sensor.h>
#include <Seeed_BME280.h>               // BME280 Temperature, Humidity, Pressure Sensor @ 0x76
//#include <VL53L0X.h>                    // IR Time-of-Flight Distance Sensor @ 0x29
//#include <LTR390.h>                     // UV Sensor
//#include <MPU6050_tockn.h>              // Gryoscopic Accelerometer
//#include "Adafruit_HMC5883_U.h"         // GY-271 Magnetometer

// Deffinitions:
// TouchPins:
#define touchPin T7   // GPIO27   enter IntTouch1 
#define touchPin T4   // GPIO33   up    IntTouch4 
#define touchPin T5   // GPIO12   back  IntTouch2 
#define touchPin T8   // GPIO13   down  IntTouch3 

// I2S:
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14

// DAC:
//#define DAC1 25
DacESP32 dac1(GPIO_NUM_25);
#define ns8002_mute 2
//#define Tones 26
#define EXT0_wake_Pin 35

// I2C:
// SDA 21 (42)
// SCL 22 (39)
#define ltr390_I2C_ADDRESS 0x53
#define BME280_ADDRESS   0x76

// UART:
// Serial0: RX0 on GPIO3, TX0 on GPIO1

//SPI OLED:
// Screen setup done in libraries/TFT_eSPI/User_Setup.h
// Pins referenced here & in "About" file..
//#define _sclk 18
//#define _mosi 23
//#define _dc   16
//#define _cs   17
//#define _rst  5


// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// SPI microSD card:
#define sd_sclk 18
#define sd_mosi 23
#define sd_miso 19
#define sd_dc   16
#define sd_rst  5
#define sd_cs   4


// Colour Conversion from RGB to HEX:
#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
// Colour definitions:
#define BLACK     RGB (0, 0, 0)
#define WHITE     RGB(255,255,255)
#define GREY      RGB(127, 127, 127)
#define DARKGREY  RGB(64, 64, 64)
#define TURQUOISE RGB(0, 128, 128)
#define PINK      RGB(255, 128, 192)
#define PINKRED   RGB(235, 158, 220)
#define OLIVE     RGB(128, 128, 0)
#define PURPLE    RGB(128, 0, 128)
#define AZURE     RGB(0, 128, 255)
#define ORANGE    RGB(255,136,0)
#define YELLOW    RGB(255,255,0)
#define GREEN      RGB(51,255,51)
#define SKYBLUE   RGB(135,206,235)
#define BLUE      RGB(0,0,255)
#define BLUEVIOLET RGB(138,43,226)
#define AQUAMARINE RGB(127,255,212)
#define RED        RGB(255,53,0)
#define DARKRED    RGB(193,0,0)
#define HONEY      RGB(255,204,153)
#define BUTTER     RGB(255,238,204)
#define OCTSUNSET  RGB(255,68,0)
#define WARNING    RGB(255,88,20)
#define BACKGROUND RGB(56,32,32)


// ~~~~~~~~~~~~~~~~~~~~~~~~~~FIRMWARE VERSION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Current Version to compare to Server Version (!) 0.1 for base testing(!)
String FirmwareVer = "0.2";
//{
//    "0.1"
//};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Initillizations & Variables:

Adafruit_MPR121 cap = Adafruit_MPR121();      // Capacitive Sensor
BME280 bme280;
//VL53L0X tof;
//LTR390 ltr390(ltr390_I2C_ADDRESS);
//MPU6050 mpu6050(Wire);
//Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

const char* ssid = "Default SSID";
const char* passphrase = "Default passord";

const word filemanagerport = 8080;

ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver

//bools, chars, consts, floats, ints etc:
bool bt_state = false;
bool wifi_state = WiFi.status();
bool sd_state = false;
float BattLevel;
char Mode = 'z';
int scan_counter = 0;       // Scan Frequency Toggle Counter
float pressure;
float Altitude;
unsigned long eventInterval = 500;       // Screen Update Interval
unsigned long previousTime = 0;
unsigned long currentTime = millis();   // timer function for page update
int i = 0;
int statusCode;
String st;
String content;
String esid;
String epass = "";

//Function Decalrations
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local server at port 80
WebServer server(80);

//Touch Settings (Internal):
const int threshold = 40 ;
int up;
int back;
int down;
int enter;

//Touch Settings (MPR121):
uint16_t lasttouched = 0;
uint16_t currtouched = 0;


// UI Elements:
// Adafruit_GFX OLED:
//Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, _cs, _dc, _mosi, _sclk, _rst);
// TFT_eSPI OLED:
TFT_eSPI tft = TFT_eSPI();
// TFT_eSPI OLED Sprites:
TFT_eSprite imghi = TFT_eSprite(&tft);     // Welcome Sprite -
TFT_eSprite title = TFT_eSprite(&tft);       // title Sprite -
//TFT_eSprite imgbatt = TFT_eSprite(&tft);   // Battery Sprite -
TFT_eSprite imgstat = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite imgtemp = TFT_eSprite(&tft);      // Sprite 1 -
TFT_eSprite imghum = TFT_eSprite(&tft);      // Sprite 2 -
TFT_eSprite imgpres = TFT_eSprite(&tft);      // Sprite 3 -
TFT_eSprite imgalt = TFT_eSprite(&tft);      // Sprite 3 -
TFT_eSprite img1 = TFT_eSprite(&tft);      // Sprite 1 -
TFT_eSprite img2 = TFT_eSprite(&tft);      // Sprite 2 -
TFT_eSprite img3 = TFT_eSprite(&tft);      // Sprite 3 -
TFT_eSprite otamenu = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifiactiv = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifiactiv1 = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifiactiv2 = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifiactiv3 = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifiactiv4 = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite filebroswer = TFT_eSprite(&tft);       // Status Icons Sprite -
TFT_eSprite wifimenu = TFT_eSprite(&tft);       // Wifi Menu Sprite -
TFT_eSprite btmenu = TFT_eSprite(&tft);       // Status Icons Sprite -

// Embedded Icons:
static const unsigned char PROGMEM image_Battery[] = {0x7f, 0xff, 0xfe, 0x00, 0x80, 0x00, 0x01, 0x00, 0x80, 0x00, 0x01, 0xc0, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01, 0x40, 0x80, 0x00, 0x01, 0xc0, 0x80, 0x00, 0x01, 0x00, 0x7f, 0xff, 0xfe, 0x00};
static const unsigned char PROGMEM image_Bluetooth[] = {0x20, 0xb0, 0x68, 0x30, 0x30, 0x68, 0xb0, 0x20};
static const unsigned char PROGMEM image_ir[] = {0x3f, 0x00, 0x40, 0x80, 0x9e, 0x40, 0x21, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x1a, 0x00, 0x1e, 0x00, 0xff, 0xc0};
static const unsigned char PROGMEM image_SDcardFail[] = {0xff, 0xe0, 0xed, 0xe0, 0xff, 0xe0, 0xe1, 0xe0, 0xde, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xe6, 0x00};
static const unsigned char PROGMEM image_SDcardMounted[] = {0xff, 0xe0, 0xff, 0x20, 0xff, 0xe0, 0xff, 0x20, 0xff, 0xe0, 0xff, 0x20, 0xff, 0xe0, 0xe6, 0x00};
static const unsigned char PROGMEM image_wifi[] = {0x40, 0x80, 0x92, 0x40, 0xa1, 0x40, 0xad, 0x40, 0xad, 0x40, 0x80, 0x40, 0x4c, 0x80, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00};
// Border Maximums
int oyt = 64;     //opening borders y top
int oyb = 64;     //opening borders y bottom
int cyt = 0;     //closing borders y top
int cyb = 128;   //closing borders y bottom


//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup() {
  // Hardware Initilization:
  Serial.begin(115200);   //Serial on usb
  //SPIFFS.begin();
  Wire.begin();  //I2C_0.begin(SDA=21 , SCL=22 , 100000 );

  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
  //WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  Serial.println("Reading EEPROM ssid");
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  
  Serial.println("Reading EEPROM pass");
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  //WiFi.begin(esid.c_str(), epass.c_str());
  
  pinMode(EXT0_wake_Pin, INPUT_PULLUP);          // External wake0 pin, goes HIGH from A3144 magnet sensor when no magnet near, goes LOW when manget close.

  // Sounnd Settings:
  dac1.disable();
  pinMode(ns8002_mute, OUTPUT);         // Mute Pin for Amp
  //pinMode(Tones, OUTPUT);               //PWM Tone Output to Amp
  analogWrite(ns8002_mute, 0);
  //digitalWrite(ns8002_mute, LOW);

  // OLED Settings:
  // Adafruit GFX:
  //tft.begin();                            // Starts OLED 128x128 SPI (Adafruit_GFX)
  //tft.setTextSize(1);
  //tft.setFont(&Whipsmart_XMvZ8pt7b);       // Font Selection
  //tft.setTextWrap(false);
  //tft.fillRect(0, 0, 128, 128, BLACK);        // clear screen except borders
  //tft.drawLine(64, 64, 128, 2, BLACK);        // Top line

  // TFT_eSPI:
  tft.init();                               //Starts OLED 128x128 SPI (TFT eSPI)
  //tft.setPivot(64, 64);                     // ?? not sure what this does..
  tft.fillScreen(BLACK);
  //tft.loadFont(AA_FONT_SMALL); // Must load the font first
  //tft.setFreeFont(&MonoBold24); // Must load the font first
  //tft.loadFont(SansBold15); // Must load the font first
  tft.setTextWrap(false);


  // I2C Inits:
  cap.begin(0x5A);                      // Starts MPR121 Capacitive Touch @ 0x5A
  cap.setThreshholds(12, 6);
  bme280.init();                        // Starts BME280          @ 0x76
  //mpu6050.begin();                      // Starts MPU6050 Gyroscopic Accelerometer
  //mag.begin();                           // Starts GY-271 Magnetometer @
  //ltr390.init();
  //tof.setTimeout(500);
  //tof.init();

  //Settings Config End..
  // Welcome Screen:
  delay(100);
  imghi.createSprite(128, 116);       // Creates Sprite 1 in (size of sprite in pixels)
  imghi.setTextColor(WHITE);
//  imghi.setCursor(38, 10);
//  imghi.loadFont(trench28);   //alittle thin..
//  imghi.print("Open");
//  imghi.unloadFont(); // Remove the font to recover memory used
  imghi.setCursor(3, 28);
  imghi.loadFont(trench35);
  imghi.setTextColor(BLUE);
  imghi.print("S");
  imghi.unloadFont(); // Remove the font to recover memory used
  imghi.loadFont(trench28);
  imghi.setCursor(22, 32);
  imghi.print("ci");
  imghi.setTextColor(WHITE);
  imghi.print("corder");
  imghi.unloadFont(); // Remove the font to recover memory used
  imghi.setCursor(100, 55);
  imghi.loadFont(timeburner12);   // great for small text
  imghi.setTextColor(HONEY);
  imghi.print("mini");
  imghi.unloadFont(); // Remove the font to recover memory used
  imghi.setCursor(45, 105);
  //imghi.setTextColor(HONEY);
  imghi.print("V ");
  imghi.print(FirmwareVer);
  borders_open();
  imghi.pushSprite(0, 12);



}

//EOF
