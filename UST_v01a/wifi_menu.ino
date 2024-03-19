
// Change menu entry names here:
const char *optionsWIFI[6] = {
  "ON/OFF",
  "File Browser",
  "RSSI Meter",
  "Setup_AP",
  "FW Update"
};

int selectedWIFI = 0;
int enteredWIFI = -1;


void wifi_menu(void)
{ 

  // ~~~~~~~~~~ Internal TouchPads: ~~~~~~~~~~
  if (up < threshold) {          //  ~~~~~~~ Internal Touch 1 - Up/Previous ~~~~~~~
    //up = true;
    selectedWIFI = selectedWIFI + 1;
    if (selectedWIFI > 4) {
      selectedWIFI = 0;
    }
    delay(200);
  }

  if (enter < threshold) {          //  ~~~~~~~ Internal Touch 4 - Enter/Select ~~~~~~~
    //enter = true;
    enteredWIFI = selectedWIFI;
  }

  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    enteredWIFI = -1;
  }

  if (down < threshold) {      //  ~~~~~~~ Internal Touch 3 - Down/Next ~~~~~~~
    //down = true;
    selectedWIFI = selectedWIFI - 1;
    delay(200);
  }

  wifimenu.createSprite(128, 113);       // screen w, screen h - statusbar
  wifimenu.loadFont(SansBold15); // Must load the font first
  //wifimenu.fillRect(0, 0, 128, 113, BLACK);        // clear screen except Statusbar, see below comment
  //wifimenu.setCursor(0, 0);    // set at 0 for Y axis, as menu is a sprite pushed to 0,13 to avoid statusbar

  if (selectedWIFI < -0) {
    selectedWIFI = 4;
  }

  if (enteredWIFI == -1) {
    //main menu?
    //back?
    wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar, see below comment
    wifimenu.setCursor(0, 0);    // set at 0 for Y axis, as menu is a sprite pushed to 0,13 to avoid statusbar
    for (int i = 0; i < 5; i++) {
      if (i == selectedWIFI) {
        //tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar
        wifimenu.setTextColor(GREEN);
        wifimenu.print("> ");                          // indents & Highlights SELECTED Menu Items
        wifimenu.setTextColor(BUTTER);
        //wifimenu.setTextColor(HONEY);
        wifimenu.print(optionsWIFI[i]);
        wifimenu.setTextColor(GREEN);
        wifimenu.println(" <");
      }
      else if (i != selectedWIFI) {
        //tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar
        wifimenu.setTextColor(WHITE);
        wifimenu.print("  ");                          // indents NON selected Menu Items
        wifimenu.println(optionsWIFI[i]);
      }
    }

  }

  else if (enteredWIFI == 0) {
    //page1 - wifi toggle

    if (wifi_state == false)
    { // turn wifi ON
      wifi_state = true;
      wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
      wifimenu.setCursor(45, 40);
      wifimenu.print("Wifi Enabled");
      delay(200);
      wifi_activate();
      delay(200);
      enteredWIFI = -1;
    }

    else if (wifi_state == true) {    // turn wifi OFF
      wifi_state = false;
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      // print wifi disabled message on oled..
      wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
      wifimenu.setCursor(45, 40);
      wifimenu.print("Wifi Disabled");
      delay(1000);
      enteredWIFI = -1;
    }
  }

  else if (enteredWIFI == 1) {
    //page2 - File Browser
    //wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    //wifimenu.setCursor(5, 13);
    //wifimenu.print("File Broswer");
    //wifimenu.setCursor(45, 53);
    //wifimenu.print("2");
    //delay(200);
    file_browser();
    enteredWIFI = -1;
  }

  else if (enteredWIFI == 2) {
    //page 3 - rssi meter
    wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    wifimenu.setCursor(5, 13);
    wifimenu.print("Menu Option");
    wifimenu.setCursor(45, 53);
    wifimenu.print("3");
    delay(200);
  }

  else if (enteredWIFI == 3) {
    //page 4 - setup_AP
    //wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    //wifimenu.setCursor(5, 13);
    //wifimenu.print("Menu Option");
    //wifimenu.setCursor(45, 53);
    //wifimenu.print("4");
    delay(200);
    setupAP();
    enteredWIFI = -1;
  }


  else if (enteredWIFI == 5) {
    //page 5 - FW Update
    wifimenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    //wifimenu.setCursor(5, 13);
    //wifimenu.print("Menu Option");
    //wifimenu.setCursor(45, 53);
    //wifimenu.print("6");
    delay(200);
    ota_update();
    enteredWIFI = -1;
  }



  wifimenu.unloadFont(); // Remove the font to recover memory used
  wifimenu.pushSprite(0, 15);              // Pushes Sprite to x, y location
  //delay(200);
}


void file_browser()
{

  ESPxWebFlMgr_FileSystem.begin();
  /*
    SD.begin();
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    //return;
    }
    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
    Serial.println("MMC");
    } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
    } else {
    Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
  */


  // login to wifi here..
  wifi_activate();

  filebroswer.createSprite(128, 128);       // screen w, screen h - statusbar
  //filebroswer.loadFont(SansBold15); // Must load the font first
  filebroswer.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
  filebroswer.setCursor(5, 15);
  filebroswer.print("Opening Fileserver..");
  filebroswer.setCursor(5, 33);
  filebroswer.print("Please go to:");
  filebroswer.setCursor(15, 73);
  filebroswer.print(WiFi.localIP());
  filebroswer.print(":");
  filebroswer.print(filemanagerport);
  //filebroswer.setCursor(20, 93);
  filebroswer.unloadFont(); // Remove the font to recover memory used
  filebroswer.pushSprite(0, 15);              // Pushes Sprite to x, y location
  delay(100);

  // start File Broswer
  filemgr.begin();

  // test while loop here, may need to adjust handleClient..
  filemgr.handleClient();

  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    //enteredWIFI = -1;
    wifi_menu();
  }

}
