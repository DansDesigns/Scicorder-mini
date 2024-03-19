


int selectedBT = 0;
int enteredBT = -1;


void bt_menu(void)
{
  btmenu.createSprite(128, 116);       // screen w, screen h - statusbar
  btmenu.loadFont(SansBold15); // Must load the font first


  // ~~~~~~~~~~ Internal TouchPads: ~~~~~~~~~~
  if (up < threshold) {          //  ~~~~~~~ Internal Touch 1 - Up/Previous ~~~~~~~
    //up = true;
    selectedBT = selectedBT + 1;
    if (selectedBT > 5) {
      selectedBT = 0;
    }
    delay(200);
  }

  if (enter < threshold) {          //  ~~~~~~~ Internal Touch 4 - Enter/Select ~~~~~~~
    //enter = true;
    enteredBT = selectedBT;
  }

  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    enteredBT = -1;
  }

  if (down < threshold) {      //  ~~~~~~~ Internal Touch 3 - Down/Next ~~~~~~~
    //down = true;
    selectedBT = selectedBT - 1;
    delay(200);
  }

  // Change menu entry names here:
  const char *optionsBT[5] = {    // 0,1,2,3,4,5
    "ON/OFF",
    "Scan Area",
    "RSSI Meter",
    "BT Feature",
    "BT Feature"
  };

  if (selectedBT < -0) {
    selectedBT = 5;
  }

  if (enteredBT == -1) {
    //main menu?
    //back?
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar, see below comment
    btmenu.setCursor(0, 0);    // set at 0 for Y axis, as menu is a sprite pushed to 0,13 to avoid statusbar
    for (int i = 0; i < 5; i++) {
      if (i == selectedBT) {
        //tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar
        btmenu.setTextColor(BLUEVIOLET);
        btmenu.print("> ");                          // indents & Highlights SELECTED Menu Items
        btmenu.print(optionsBT[i]);
        btmenu.println(" <");
      }
      else if (i != selectedBT) {
        //tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar
        btmenu.setTextColor(WHITE);
        btmenu.print("  ");                          // indents NON selected Menu Items
        btmenu.println(optionsBT[i]);
      }
    }

  }

  else if (enteredBT == 0) {
    //page1 - bt toggle

    if (bt_state == false) {
      bt_state = true;
      //btStart();
      delay(200);
      enteredBT = -1;
    }

    else if (bt_state == true) {
      bt_state = false;
      delay(200);
      enteredBT = -1;
    }
  }

  else if (enteredBT == 1) {
    //page2 - scan area
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    btmenu.setCursor(5, 13);
    btmenu.print("Menu Option");
    btmenu.setCursor(45, 53);
    btmenu.print("2");
    delay(200);
  }

  else if (enteredBT == 2) {
    //page 3 - rssi meter
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    btmenu.setCursor(5, 13);
    btmenu.print("Menu Option");
    btmenu.setCursor(45, 53);
    btmenu.print("3");
    delay(200);
  }

  else if (enteredBT == 3) {
    //page 4 - BLANK
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    btmenu.setCursor(5, 13);
    btmenu.print("Menu Option");
    btmenu.setCursor(45, 53);
    btmenu.print("4");
    delay(200);
  }

  else if (enteredBT == 4) {
    //page 5 - BLANK
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    btmenu.setCursor(5, 13);
    btmenu.print("Menu Option");
    btmenu.setCursor(45, 53);
    btmenu.print("5");
    delay(200);
  }

  else if (enteredBT == 5) {
    //page 5 - BLANK
    btmenu.fillRect(0, 0, 128, 128, BLACK);        // clear screen except Statusbar
    btmenu.setCursor(5, 13);
    btmenu.print("Menu Option");
    btmenu.setCursor(45, 53);
    btmenu.print("6");
    delay(200);
  }



  btmenu.unloadFont(); // Remove the font to recover memory used
  btmenu.pushSprite(0, 12);              // Pushes Sprite to x, y location
}
