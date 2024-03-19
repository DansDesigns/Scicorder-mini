


void loop()
{
  unsigned long currentTime = millis();   // timer function for page update
  currtouched = cap.touched();        //Call first thing to read from MPR121
  up = touchRead(T4);// UP - 33
  back = touchRead(T5);// BACK - 12
  down = touchRead(T8);// DOWN - 13
  enter = touchRead(T7);// ENTER - 27


  // Check for Sleep state:
  if (EXT0_wake_Pin == HIGH)
  {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_35,0); //1 = High, 0 = Low
    esp_deep_sleep_start();
    // Serial.println("This will never be printed");
  }

  else if (EXT0_wake_Pin == LOW)
  {
    // lights on here..
    // power on things here?
  }
  
  // UI Elements:

  // Battery:
  //imgbatt.createSprite(30, 12);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  imgstat.createSprite(128, 12);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  imgstat.fillRect(0, 0, 128, 12, BLACK);    // Clear Statusbar
  imgstat.drawBitmap( 98, 1, image_Battery, 26, 8, GREY);
  if (BattLevel < 14)
  {
    imgstat.fillRect(100, 3, 4, 4, RED);    // Battery 0-10% - set red when here
    imgstat.fillRect(105, 3, 5, 4, GREY);    // Battery 11-35% - set orange when here & set grey when lower than this
    imgstat.fillRect(111, 3, 5, 4, GREY);    // Battery 36-75% - set grey when lower than this
    imgstat.fillRect(117, 3, 3, 4, GREY);    // Battery 75-100% - set grey when lower than this
  }
  else if ((BattLevel > 15) && (BattLevel < 34))
  {
    imgstat.fillRect(100, 3, 4, 4, ORANGE);    // Battery 0-10% - set red when here
    imgstat.fillRect(105, 3, 5, 4, GREY);    // Battery 11-35% - set orange when here & set grey when lower than this
    imgstat.fillRect(111, 3, 5, 4, GREY);    // Battery 36-75% - set grey when lower than this
    imgstat.fillRect(117, 3, 3, 4, GREY);    // Battery 75-100% - set grey when lower than this
  }
  else if ((BattLevel > 35) && (BattLevel < 49))
  {
    imgstat.fillRect(100, 3, 4, 4, ORANGE);    // Battery 0-10% - set red when here
    imgstat.fillRect(105, 3, 5, 4, ORANGE);    // Battery 11-35% - set orange when here & set grey when lower than this
    imgstat.fillRect(111, 3, 5, 4, GREY);    // Battery 36-75% - set grey when lower than this
    imgstat.fillRect(117, 3, 3, 4, GREY);    // Battery 75-100% - set grey when lower than this
  }
  else if ((BattLevel > 50) && (BattLevel < 75))
  {
    imgstat.fillRect(100, 3, 4, 4, GREEN);    // Battery 0-10% - set red when here
    imgstat.fillRect(105, 3, 5, 4, GREEN);    // Battery 11-35% - set orange when here & set grey when lower than this
    imgstat.fillRect(111, 3, 5, 4, GREEN);    // Battery 36-75% - set grey when lower than this
    imgstat.fillRect(117, 3, 3, 4, GREY);    // Battery 75-100% - set grey when lower than this
  }
  else if (BattLevel > 76)
  {
    imgstat.fillRect(100, 3, 4, 4, GREEN);    // Battery 0-10% - set red when here
    imgstat.fillRect(105, 3, 5, 4, GREEN);    // Battery 11-35% - set orange when here & set grey when lower than this
    imgstat.fillRect(111, 3, 5, 4, GREEN);    // Battery 36-75% - set grey when lower than this
    imgstat.fillRect(117, 3, 3, 4, GREEN);    // Battery 75-100% - set grey when lower than this
  }
  //delay(50);
  //imgbatt.pushSprite(98, 0);

  // WIFI, BT & SD card Status:

  // WIFI:
  if (wifi_state == WL_CONNECTED)
  {
    //tft.drawBitmap( 0, 1, image_wifi, 10, 10, AZURE);
    imgstat.drawBitmap( 0, 1, image_wifi, 10, 10, GREEN);
  }
  else if (wifi_state == WL_DISCONNECTED)
  {
    imgstat.drawBitmap( 0, 1, image_wifi, 10, 10, RED);
  }
  else if (wifi_state == WL_CONNECTION_LOST)
  {
    imgstat.drawBitmap( 0, 1, image_wifi, 10, 10, ORANGE);
  }
  else
  {
    imgstat.drawBitmap( 0, 1, image_wifi, 10, 10, GREY);
  }

  // BT:
  if (bt_state == true) {
    imgstat.drawBitmap( 13, 1, image_Bluetooth, 5, 8, BLUE);
  }
  else if (bt_state == false)
  {
    imgstat.drawBitmap( 13, 1, image_Bluetooth, 5, 8, GREY);
  }

  // SD Card:
  if (sd_state == true)
  {
    imgstat.drawBitmap( 22, 1, image_SDcardMounted, 11, 8, TURQUOISE);
  }
  else if (sd_state == false)
  {
    imgstat.drawBitmap( 22, 1, image_SDcardFail, 11, 8, GREY);
  }
  delay(200);
  imgstat.pushSprite(0, 0);


  /*

    // Internal TouchPad - Multi Function:
    if (up < threshold) {      //  ~~~~~~~ Internal Touch 1 - SCAN MODE TOGGLE ~~~~~~~
      Serial.println("T1 Touched");
      //ButtonTone(Tones);
      scan_counter++;      // needed for multi-function mode
    }

    if (scan_counter == 0) {       //  ~~~~~~~ multi-function first tap ~~~~~~~
      //  1st function
      eventInterval = 400;       // Screen Update Interval
    }


    if (scan_counter == 1) {       //  ~~~~~~~ multi-function second tap ~~~~~~~
      // 2nd function
      eventInterval = 1000;       // Screen Update Interval
    }

    if (scan_counter > 1) {      //  ~~~~~~~ Over-tap protection or replace ">" with "==" to make third tap function ~~~~~~~
      // 3rd function
      scan_counter = 0;  // comment out it ofther functions than off
    }

    // ~~~~~~~~~~ Internal TouchPads: ~~~~~~~~~~
    if (up < threshold) {          //  ~~~~~~~ Internal Touch 1 - Up/Previous ~~~~~~~

    }

    if (back < threshold) {          //  ~~~~~~~ Internal Touch 2 - Enter/Select ~~~~~~~

    }

    if (down < threshold) {      //  ~~~~~~~ Internal Touch 3 - Back/Delete ~~~~~~~


    }

    if (enter < threshold) {      //  ~~~~~~~ Internal Touch 4 - Down/Next ~~~~~~~

    }


    if (back < threshold) {          //  ~~~~~~~ Internal Touch 2 - Data Logging ~~~~~~~
    Serial.println("T2 Touched");
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("Mode-a");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'a';                         // Scan mode
    }

    if (down < threshold) {      //  ~~~~~~~ Internal Touch 3 ~~~~~~~
    Serial.println("T3 Touched");
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("Mode-s");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 's';                         // Scan mode

    }

    if (enter < threshold) {      //  ~~~~~~~ Internal Touch 4 ~~~~~~~
    Serial.println("T4 Touched");
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("Rst Icons");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'i';                         // Scan mode
    sd_state = false;
    bt_state = false;
    wifi_state = false;
    BattLevel = 100;
    }

  */
  // MPR121 TouchPads:

  if (cap.touched() & (1 << 0))             // Button 0 - MET/DIST
  {
    ButtonTone();
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("MET/DST");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'B';                         // Scan mode
  }


  if (cap.touched() & (1 << 1))             // Button 1 - AUD SPEC
  {
    ButtonTone();
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("AUDSPC");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'A';                         // Scan mode
  }


  if (cap.touched() & (1 << 2))             // Button 2 - VIS
  {
    ButtonTone();
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print(" Visible");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '2';                         // Scan mode
  }

  if (cap.touched() & (1 << 3))             // Button 3 - IR
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("    IR");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '3';                         // Scan mode
  }

  if (cap.touched() & (1 << 4))             // Button 4 - UV
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("    UV");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '4';                         // Scan mode
  }


  if (cap.touched() & (1 << 5))             // Button 5 - BT
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("    BT");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '5';                         // Scan mode
  }


  if (cap.touched() & (1 << 6))             // Button 6 - WIFI
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    //tft.setTextSize(1);
    //tft.setTextColor(WHITE);
    //tft.setCursor(35, 11);
    //tft.print("   WIFI");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '6';                         // Scan mode
  }


  if (cap.touched() & (1 << 7))             // Button 7 - EMF/MAG
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("EMF/MAG");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '7';                         // Scan mode
  }


  if (cap.touched() & (1 << 8))             // Button 8 - GYR
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("   GYR");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '8';                         // Scan mode
  }


  if (cap.touched() & (1 << 9))             // Button 9 - COLR SPEC
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("COLRSPC");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = '9';                         // Scan mode
  }

  if (cap.touched() & (1 << 10))             // Button 10 - DEVICE
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print(" DEVICE");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'A';                         // Scan mode
  }

  if (cap.touched() & (1 << 11))             // Button 11 - ATM/GAS
  {
    //ButtonTone(Tones);
    borders_close();
    delay(50);
    tft.setTextSize(1);
    tft.setTextColor(WHITE);
    tft.setCursor(35, 11);
    //tft.print("ATM/GAS");
    //scan_counter = 0;                 // reset screen update interval to default 333ms
    Mode = 'B';                         // Scan mode
  }


  lasttouched = currtouched;


  // ~~~~~~~~~~~~~~~~~~~~~~~~~ Wake from Sleep Reason and Reaction: ~~~~~~~~~~~~~~~~~~~~~~~~~
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.print("wake_from_ext0()") ; break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("TouchPad WakeUp Cause"); break;
    case ESP_SLEEP_WAKEUP_TIMER : callback(); break;
    case ESP_SLEEP_WAKEUP_ULP : callback() ; break;
    case ESP_SLEEP_WAKEUP_UNDEFINED : callback() ; break;
    case ESP_SLEEP_WAKEUP_ALL : callback() ; break;
    case ESP_SLEEP_WAKEUP_EXT1 : callback() ; break;
    case ESP_SLEEP_WAKEUP_GPIO : callback() ; break;
    case ESP_SLEEP_WAKEUP_UART : callback() ; break;
    case ESP_SLEEP_WAKEUP_WIFI : callback() ; break;
    case ESP_SLEEP_WAKEUP_BT : callback() ; break;
    case ESP_SLEEP_WAKEUP_COCPU : Serial.println("COCPU WakeUp Cause") ; break;
    case ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG : Serial.println("COCPU_TRAP_TRIG WakeUp Cause") ; break;
      //    case ESP_SLEEP_WAKEUP_UNDEFINED : Serial.println("UNKNOWN WakeUp Cause") ; break;
  }


  switch (Mode)
  {
    case 'a':
      // ~~~~~~~ sleepmode ~~~~~~~
      //lightSleep();
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("Ready");

      if (up < threshold) {      //  ~~~~~~~ Internal Touch 1 - SCAN MODE TOGGLE ~~~~~~~
        Serial.println("T1 Touched");
        //ButtonTone(Tones);
        tft.fillRect(28, 50, 50, 20, BLACK);        // clear content text is 11 pixels high (actually -x from point of reference)
        scan_counter++;      // needed for multi-function mode
      }
      break;


    case 'b':
      // ~~~~~~~ I2C Scanner ~~~~~~~
      //i2c_scanner();
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("Steady");

      if (up < threshold) {      //  ~~~~~~~ Internal Touch 1 - SCAN MODE TOGGLE ~~~~~~~
        Serial.println("T1 Touched");
        //ButtonTone(Tones);
        tft.fillRect(28, 50, 50, 20, BLACK);        // clear content text is 11 pixels high (actually -x from point of reference)
        scan_counter++;      // needed for multi-function mode
      }
      break;


    case 'c':
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("Go!");
      if (up < threshold) {      //  ~~~~~~~ Internal Touch 1 - SCAN MODE TOGGLE ~~~~~~~
        Serial.println("T1 Touched");
        //ButtonTone(Tones);
        tft.fillRect(28, 50, 50, 20, BLACK);        // clear content text is 11 pixels high (actually -x from point of reference)
        scan_counter++;      // needed for multi-function mode
      }

      if (currentTime - previousTime >= eventInterval)
      {
        //EMPTY
        //tft.fillRect(28, 63, 50, 15, BLACK);        // clear content
        //tft.setCursor(28, 63);
        //tft.print("scan !");
      }
      previousTime = currentTime;           // Called after Sprite

      break;

    case 's':
      // ~~~~~~~ sleepmode ~~~~~~~
      //lightSleep();
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("Mode s");
      break;

    case 'i':
      // ~~~~~~~ sleepmode ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("Reset Icons");
      BattLevel = 100;
      break;

    case '0':
      // ~~~~~~~ MET/DIST ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("MET/DIST");
      sd_state = true;
      BattLevel = 65;
      break;

    case '1':
      // ~~~~~~~ AUD SPEC ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("AUD SPEC");
      wifi_state = true;
      BattLevel = 44;
      break;

    case '2':
      // ~~~~~~~ VIS ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("VIS");
      bt_state = true;
      BattLevel = 8;
      break;

    case '3':
      // ~~~~~~~ IR ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("IR");
      break;

    case '4':
      // ~~~~~~~ UV ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("UV");
      break;

    case '5':
      // ~~~~~~~ BT ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      //tft.print("BT");
      bt_menu();
      break;

    case '6':
      // ~~~~~~~ WIFI ~~~~~~~
      //tft.setTextColor(GREEN);
      //tft.setCursor(28, 63);
      //tft.print("WIFI");
      wifi_menu();
      break;

    case '7':
      // ~~~~~~~ EMF/MAG ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("EMF/MAG");
      break;

    case '8':
      // ~~~~~~~ GYR ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("GYR");
      break;

    case '9':
      // ~~~~~~~ COLR SPEC ~~~~~~~
      tft.setTextColor(GREEN);
      tft.setCursor(28, 63);
      tft.print("COLR SPEC");
      break;

    case 'A':
      // ~~~~~~~ DEVICE ~~~~~~~
      //tft.setTextColor(GREEN);
      //tft.setCursor(28, 63);
      //tft.print("DEVICE");
      //tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar


      break;

    case 'B':
      // ~~~~~~~ ATM/GAS ~~~~~~~
      atm_gas();
      break;


  }
}

//EOF
