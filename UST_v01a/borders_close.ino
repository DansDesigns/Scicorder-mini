
void borders_close() {
  tft.fillRect(0, 12, 128, 128, BLACK);        // clear screen except Statusbar
  //tft.fillRect(45, 0, 128, 15, BLACK);        // clear screen except Statusbar
  cyt = 12;
  for  (int i = 0; i < 16; i++)
  {
    cyt = cyt + 4;
    cyb = cyb - 4;

    if (cyt > 64) cyt = -13;
    tft.drawLine(0, cyt, 128, cyt, BLACK);        // Erase Previous Top line
    cyt = cyt + 4;    // increase incriment to make new line
    tft.drawLine(0, cyt, 128, cyt, ORANGE);        // Top line
    cyt = cyt - 4;    // reduce incriment to match overall

    //tft.fillRect(20, 15, 90, 90, BLACK);

    if (cyb < 64) cyb = 128;
    tft.drawLine(0, cyb, 128, cyb, BLACK);    // Erase Previous Bottom Line
    cyb = cyb - 4;    // increase incriment to make new line
    tft.drawLine(0, cyb, 128, cyb, ORANGE);    // Bottom Line
    cyb = cyb + 4;    // reduce incriment to match overall

    delay(30);
  }

  tft.drawLine(0, 12, 128, cyt, BLACK);        // Erase middle line
  if (cyb == 64) borders_open();

  cyt = 0;
  cyb = 128;

}
