
void borders_open() {
  oyt = 64;

  for  (int i = 0; i < 16; i++)
  {
    oyt = oyt - 4;
    oyb = oyb + 4;

    if (oyt < 12) oyt = -4;
    oyt = oyt + 4;    // reduce incriment to match overall
    tft.drawLine(0, oyt, 128, oyt, BLACK);        // Erase Previous Top line
    oyt = oyt - 4;    // increase incriment to make new line
    tft.drawLine(0, oyt, 128, oyt, ORANGE);        // Top line

    if (oyb > 128) oyb = 64;
    oyb = oyb - 4;    // reduce incriment to match overall
    tft.drawLine(0, oyb, 128, oyb, BLACK);    // Erase Previous Bottom Line
    oyb = oyb + 4;    // increase incriment to make new line
    tft.drawLine(0, oyb, 128, oyb, ORANGE);    // Bottom Line

    delay(30);
  }
  
  //tft.drawLine(0, 0, 128, 0, ORANGE);        // Top line
  //tft.drawLine(0, 127, 128, 127, ORANGE);    // Bottom Line  
  tft.drawLine(0, 0, 128, 0, BLACK);        // Top line
  //tft.drawLine(0, 127, 128, 127, BLACK);    // Bottom Line
  tft.drawLine(0, 12, 128, 12, BLACK);        // Erase Previous Top line
  //tft.drawLine(0, 56, 128, 56, BLACK);        // Erase middle line
  
  oyt = 0;
  oyb = 64;
  
  return;
}
