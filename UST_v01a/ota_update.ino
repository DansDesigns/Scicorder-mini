

//const char * ssid = "Workshop-Wifi";
//const char * wifiPassword = "Tintin10";

int status = WL_IDLE_STATUS;
int incomingByte;
int httpCode;

// Text file containing Version Number:
#define URL_fw_Version "https://raw.githubusercontent.com/DansDesigns/Ultra-Slim-Tricorder/main/firmware/version.txt"
// .bin file if New Version
#define URL_fw_Bin "https://raw.githubusercontent.com/DansDesigns/Ultra-Slim-Tricorder/main/firmware/fw.bin"



void ota_update() {// UI Elements:
  
  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    wifi_menu();
  }
  //Serial.print("Connecting to WiFi");
  otamenu.createSprite(128, 128);       // screen w, screen h - statusbar
  //otamenu.loadFont(SansBold15); // Must load the font first
  if (WiFi.status() != WL_CONNECTED) {
    wifi_state = true;
    otamenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    otamenu.setCursor(5, 20);
    otamenu.print("Looking for Saved");
    otamenu.setCursor(5, 40);
    otamenu.print("Wifi Credentials");
    // print connecting message on oled..
    // check for existing ssid & password:
    otamenu.unloadFont(); // Remove the font to recover memory used
    otamenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
    delay(200);
    for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
    // print the ssid to the oled....
    //Serial.println(esid);

    for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
    //print some kind of indicator for saved password on oled
    //Serial.println(epass);
    //WiFi.mode(WIFI_ON);
    otamenu.setCursor(5, 40);
    otamenu.print("Wifi Credentials found");
    otamenu.setCursor(5, 53);
    otamenu.print("Connecting to Wifi");
    otamenu.setCursor(5, 73);
    otamenu.setCursor(5, 93);
    otamenu.unloadFont(); // Remove the font to recover memory used
    otamenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
    WiFi.begin(esid.c_str(), epass.c_str());

    if ((WiFi.status() == WL_CONNECTED))
    {
      //Serial.print(esid);
      otamenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
      otamenu.setCursor(5, 40);
      otamenu.print("Connected to:");
      otamenu.setCursor(5, 53);
      otamenu.print(esid);
      otamenu.unloadFont(); // Remove the font to recover memory used
      otamenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
      delay(1500);
      //use these to trigger update.. ie in setup? or from oled menu?
      if (FirmwareVersionCheck()) {
        firmwareUpdate();
      }
    }
    else while ((WiFi.status() != WL_CONNECTED))
      {
        otamenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
        otamenu.setCursor(5, 40);
        otamenu.print("Unable to Connect");
        otamenu.setCursor(5, 53);
        otamenu.print("Launching Setup_AP");

        createWebServer();                  // Start the server
        server.begin();
        setupAP();                          // Setup HotSpot

        otamenu.setCursor(15, 73);
        otamenu.print("AccessPoint IP:");
        otamenu.setCursor(15, 93);
        otamenu.print(WiFi.softAPIP());
        otamenu.unloadFont(); // Remove the font to recover memory used
        otamenu.pushSprite(0, 12);              // Pushes Sprite to x, y location

        while ((WiFi.status() != WL_CONNECTED))
        {
          //Serial.print(".");
          delay(100);
          server.handleClient();
          if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
            //back = true;
            wifi_menu();
          }
        }
        delay(1000);
      }
  }

  //Serial.println("Connected To Wifi");
  //wifi_state = true;
  //delay(1000);
  Serial.print("Current Firmware Version: ");
  Serial.println(FirmwareVer);

  /*
    if (WiFi.status() != WL_CONNECTED) {
      wifi_state = false;
      //reconnect();
      // print message, cant connect..
      // start Setup_AP

      createWebServer();                  // Start the server
      server.begin();
      setupAP();                          // Setup HotSpot
      enteredWIFI = 0;
    }
  */
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (enter < threshold) {          //  ~~~~~~~ Internal Touch 2 - Enter/Select ~~~~~~~
      //enter = true;
    }

    if (back < threshold) {      //  ~~~~~~~ Internal Touch 3 - Back/Delete ~~~~~~~
      //back = true;
    }
    if (incomingByte == 'U') {
      Serial.println("Firmware Update In Progress..");

      //use these to trigger update.. ie in setup? or from oled menu?
      if (FirmwareVersionCheck()) {
        firmwareUpdate();
      }
    }
  }
  otamenu.unloadFont(); // Remove the font to recover memory used
  otamenu.pushSprite(0, 12);              // Pushes Sprite to x, y location

}


/*
  void reconnect() {
  int i = 0;
  // Loop until we're reconnected
  status = WiFi.status();
  if (status != WL_CONNECTED) {
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (i == 10) {
        //ESP.restart();
        // add "no connection error" here..
        // add "no wifi credentials saved" here..
        return;
      }
      i++;
    }
    Serial.println("Connected to AP");
    wifi_state = true;
  }
  }
*/

void firmwareUpdate(void) {

  wifimenu.createSprite(128, 116);       // screen w, screen h - statusbar
  wifimenu.loadFont(SansBold15); // Must load the font first
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  t_httpUpdate_return ret = httpUpdate.update(client, URL_fw_Bin);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      wifimenu.setCursor(5, 20);
      wifimenu.print("HTTP_UPDATE_FAILD");
      wifimenu.setCursor(5, 40);
      wifimenu.printf("Error (%d): %s\n");
      wifimenu.setCursor(15, 53);
      wifimenu.print(httpUpdate.getLastError());
      wifimenu.setCursor(15, 73);
      wifimenu.print(httpUpdate.getLastErrorString().c_str());
      wifimenu.setCursor(15, 93);
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      wifimenu.setCursor(5, 20);
      //wifimenu.print("                 ");
      wifimenu.setCursor(5, 40);
      wifimenu.setCursor(15, 53);
      wifimenu.setCursor(15, 73);
      wifimenu.setCursor(15, 93);
      break;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      wifimenu.setCursor(5, 20);
      //wifimenu.print("                 ");
      wifimenu.setCursor(5, 40);
      wifimenu.setCursor(15, 53);
      wifimenu.setCursor(15, 73);
      wifimenu.setCursor(15, 93);
      break;
  }
  wifimenu.unloadFont(); // Remove the font to recover memory used
  wifimenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
}


int FirmwareVersionCheck(void) {
  wifimenu.createSprite(128, 116);       // screen w, screen h - statusbar
  wifimenu.loadFont(SansBold15); // Must load the font first
  String payload;
  int httpCode;
  String FirmwareURL = "";
  FirmwareURL += URL_fw_Version;
  FirmwareURL += "?";
  FirmwareURL += String(rand());
  Serial.println(FirmwareURL);
  WiFiClientSecure * client = new WiFiClientSecure;

  if (client) {
    client -> setCACert(rootCACertificate);
    HTTPClient https;

    if (https.begin( * client, FirmwareURL)) {
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      delay(100);
      httpCode = https.GET();
      delay(100);
      if (httpCode == HTTP_CODE_OK) // if version received
      {
        payload = https.getString(); // save received version
      } else {
        Serial.print("Error During Version Check: ");
        wifimenu.setCursor(5, 20);
        wifimenu.print("Error During Version Check");
        wifimenu.setCursor(5, 40);
        wifimenu.setCursor(15, 53);
        wifimenu.setCursor(15, 73);
        wifimenu.setCursor(15, 93);
        Serial.println(httpCode);
      }
      https.end();
    }
    delete client;
  }

  if (httpCode == HTTP_CODE_OK) // if version received
  {
    payload.trim();
    if (payload.equals(FirmwareVer)) {
      //Serial.print("No Update Needed");
      wifimenu.setCursor(5, 20);
      wifimenu.print("No Update Needed ");
      wifimenu.setCursor(5, 40);
      wifimenu.setCursor(5, 53);
      wifimenu.print("Already on Latest Release");
      wifimenu.setCursor(15, 73);
      wifimenu.print(FirmwareVer);
      wifimenu.setCursor(15, 93);
      //Serial.print(FirmwareVer);
      return 0;
    } else {
      wifimenu.setCursor(5, 20);
      wifimenu.print("New Firmware Found");
      wifimenu.setCursor(5, 40);
      wifimenu.setCursor(15, 53);
      wifimenu.print("Downloading Now..");
      wifimenu.setCursor(15, 73);
      wifimenu.setCursor(15, 93);
      //Serial.println(payload);
      //Serial.println("Downloading..");
      return 1;
    }
  }
  wifimenu.unloadFont(); // Remove the font to recover memory used
  wifimenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
  return 0;
}
