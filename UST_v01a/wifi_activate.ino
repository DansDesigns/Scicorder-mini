

void wifi_activate()
{ 
  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    wifi_menu();
  }

  wifiactiv.createSprite(128, 113);       // screen w, screen h - statusbar
  wifiactiv1.createSprite(128, 113);       // screen w, screen h - statusbar
  wifiactiv2.createSprite(128, 113);       // screen w, screen h - statusbar
  wifiactiv3.createSprite(128, 113);       // screen w, screen h - statusbar
  wifiactiv4.createSprite(128, 113);       // screen w, screen h - statusbar
  //wifiactiv.loadFont(SansBold15); // Must load the font first
  //wifiactiv1.fillRect(0, 0, 128, 113, BLACK);        // clear screen except Statusbar, see below comment
  //wifiactiv1.setCursor(0, 0);    // set at 0 for Y axis, as menu is a sprite pushed to 0,13 to avoid statusbar
  wifiactiv1.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
  wifiactiv1.setCursor(5, 20);
  wifiactiv1.print("Looking for Saved");
  wifiactiv1.setCursor(5, 40);
  wifiactiv1.print("Credentials");
  wifiactiv1.unloadFont(); // Remove the font to recover memory used
  wifiactiv1.pushSprite(0, 15);              // Pushes Sprite to x, y location
  // print connecting message on oled..
  delay(1000);
  // check for existing ssid & password:
//  for (int i = 0; i < 32; ++i)
//  {
//    esid += char(EEPROM.read(i));
//  }
  // print the ssid to the oled....
  //Serial.println(esid);

//  for (int i = 32; i < 96; ++i)
//  {
//    epass += char(EEPROM.read(i));
//  }
  //print some kind of indicator for saved password on oled
  //Serial.println(epass);
  //WiFi.mode(WIFI_ON);
  delay(1500);
  //wifiactiv2.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
  wifiactiv2.setCursor(5, 40);
  wifiactiv2.print("Credentials Found");
  wifiactiv2.setCursor(5, 73);
  wifiactiv2.print("Connecting to ");
  wifiactiv2.print(esid);
  wifiactiv2.unloadFont(); // Remove the font to recover memory used
  wifiactiv2.pushSprite(0, 15);              // Pushes Sprite to x, y location
  WiFi.begin(esid.c_str(), epass.c_str());
  delay(1500);

  if ((WiFi.status() == WL_CONNECTED))
  {
    //Serial.print(esid);
    wifiactiv3.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    wifiactiv3.setCursor(5, 20);
    wifiactiv3.print("Connected to:");
    wifiactiv3.setCursor(5, 33);
    wifiactiv3.print(esid);
    //delay(1500);
    //enteredWIFI = -1;
    wifiactiv3.unloadFont(); // Remove the font to recover memory used
    wifiactiv3.pushSprite(0, 15);              // Pushes Sprite to x, y location
    delay(1000);
    return;
  }
  
  //if ((WiFi.status() == WL_CONNECT_FAILED))
  else //((WiFi.status() == WL_CONNECT_FAILED))
  {

    wifiactiv4.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    wifiactiv4.setCursor(5, 15);
    wifiactiv4.print("Unable to Connect");
    wifiactiv4.setCursor(5, 33);
    wifiactiv4.print("Press Here -->");
    wifiactiv4.setCursor(5, 53);
    wifiactiv4.print("To Launch Setup_AP");
    wifiactiv4.unloadFont(); // Remove the font to recover memory used
    wifiactiv4.pushSprite(0, 15);              // Pushes Sprite to x, y location
    delay(100);

    if (enter < threshold) {          //  ~~~~~~~ Internal Touch 4 - Enter/Select ~~~~~~~

      wifiactiv.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
      wifiactiv.setCursor(5, 33);
      wifiactiv.print("Launching Setup_AP");
      wifiactiv.setCursor(15, 73);
      wifiactiv.print("AccessPoint IP:");
      wifiactiv.setCursor(20, 93);
      wifiactiv.print(WiFi.softAPIP());
      createWebServer();                  // Start the server
      server.begin();
      setupAP();                          // Setup HotSpot
      wifiactiv.unloadFont(); // Remove the font to recover memory used
      wifiactiv.pushSprite(0, 15);              // Pushes Sprite to x, y location
      delay(100);

      while ((WiFi.status() != WL_CONNECTED))
      {
        if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
          //back = true;
          wifi_menu();
        }
        delay(100);
        server.handleClient();
        // test return to previous function here..
        //may need a if wifi connected condition..
        //return;
      }
    }
    //wifiactiv.unloadFont(); // Remove the font to recover memory used
    //wifiactiv.pushSprite(0, 12);              // Pushes Sprite to x, y location

    delay(100);
  }


  //wifiactiv.unloadFont(); // Remove the font to recover memory used
  //wifiactiv.pushSprite(0, 12);              // Pushes Sprite to x, y location
}
