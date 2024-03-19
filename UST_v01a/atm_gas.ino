void atm_gas()
{

  // TEST Batt Lvel
  BattLevel = 100;
  imgtemp.createSprite(64, 40);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  //imgtemp.createSprite(128, 116);       // Creates Sprite 1 in (size of sprite in pixels: W, H)

  // if (currentTime - previousTime >= eventInterval)
  // {
  imgtemp.loadFont(SansBold15); // Must load the font first
  //get and print Temperature
  if (bme280.getTemperature() < 5)
  {
    //tft.fillRect(70, 15, 70, 20, SKYBLUE);// box: start X, start Y, width, height, fill-colour (prints from points downwards, text is 12 tall + 2 for border)
    imgtemp.fillRoundRect(64, 0, 64, 40, 0, SKYBLUE);      // x, y, w, h, corner radius, colour
  }

  else if ((bme280.getTemperature() > 5) && (bme280.getTemperature() < 15))
  {
    //tft.fillRect(70, 15, 70, 20, AQUAMARINE);// box: start X, start Y, width, height, fill-colour (prints from points downwards, text is 12 tall + 2 for border)
    imgtemp.fillRoundRect(64, 0, 64, 40, 0, AQUAMARINE);      // x, y, w, h, corner radius, colour
  }

  else if ((bme280.getTemperature() > 15) && (bme280.getTemperature() < 26))
  {
    //tft.fillRect(70, 15, 70, 20, GREEN);// box: start X, start Y, width, height, fill-colour (prints from points downwards, text is 12 tall + 2 for border)
    imgtemp.fillRoundRect(64, 0, 64, 40, 0, GREEN);      // x, y, w, h, corner radius, colour
  }

  else if ((bme280.getTemperature() > 26) && (bme280.getTemperature() < 30))
  {
    imgtemp.fillRoundRect(64, 0, 64, 40, 0, ORANGE);      // x, y, w, h, corner radius, colour
    //tft.fillRect(70, 15, 70, 20, ORANGE);// box: start X, start Y, width, height, fill-colour (prints from points downwards, text is 12 tall + 2 for border)
  }

  else if (bme280.getTemperature() > 30)
  {
    imgtemp.fillRoundRect(64, 0, 64, 40, 0, WARNING);// box: start X, start Y, width, height, fill-colour (prints from points downwards, text is 12 tall + 2 for border)
  }

  imgtemp.setCursor(84, 20);            // text prints upwards.. so minus y value
  imgtemp.setTextColor(BLACK);
  imgtemp.print(bme280.getTemperature());
  //tft.print( random(10, 60) );         // Random digits print
  imgtemp.unloadFont(); // Remove the font to recover memory used
  imgtemp.pushSprite(64, 13);              // Pushes Sprite to x, y location

  imghum.createSprite(64, 40);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  imghum.loadFont(SansBold15); // Must load the font first
  //get and print Humidity
  if ((bme280.getHumidity() > 1) && (bme280.getHumidity() < 41))
  {
    imghum.fillRect(0, 0, 64, 40, RED);
  }

  else if ((bme280.getHumidity() > 41) && (bme280.getHumidity() < 75))
  {
    imghum.fillRect(0, 0, 64, 40, ORANGE);
  }

  else if (bme280.getHumidity() > 75)
  {
    imghum.fillRect(0, 0, 64, 40, BLUE);
  }
  imghum.setCursor(20, 20);
  imghum.setTextColor(BLACK);
  imghum.print(bme280.getHumidity());
  //tft.print( random(10, 99) );         // Random digits print
  imghum.unloadFont(); // Remove the font to recover memory used
  imghum.pushSprite(0, 13);              // Pushes Sprite to x, y location


  imgpres.createSprite(128, 40);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  imgpres.loadFont(SansBold15); // Must load the font first
  //get and print Pressure
  pressure = bme280.getPressure();
  if ((pressure > 90000) && (pressure < 10000))
  {
    imgpres.fillRect(0, 40, 128, 40, ORANGE);
  }

  else if ((pressure > 10001) && (pressure < 100200))
  {
    imgpres.fillRect(0, 40, 128, 40, GREEN);
  }

  else if (pressure > 100200)
  {
    imgpres.fillRect(0, 40, 128, 40, RED);
  }

  imgpres.setCursor(20, 60);
  imgpres.setTextColor(BLACK);
  imgpres.print(pressure);
  //tft.print( random(100, 999) );         // Random digits print
  imgpres.unloadFont(); // Remove the font to recover memory used
  imgpres.pushSprite(0, 53);              // Pushes Sprite to x, y location


  imgalt.createSprite(128, 28);       // Creates Sprite 1 in (size of sprite in pixels: W, H)
  imgalt.loadFont(SansBold15); // Must load the font first
  //get and print Altitude
  imgalt.fillRect(0, 80, 128, 48, BLACK);
  imgalt.setTextColor(WHITE);
  imgalt.setCursor(20, 95);
  Altitude = bme280.calcAltitude(pressure);
  imgalt.print(Altitude);
  //tft.print( random(10, 508) );         // Random digits print
  imgalt.unloadFont(); // Remove the font to recover memory used
  imgalt.pushSprite(0, 12);              // Pushes Sprite to x, y location
  //previousTime = currentTime;           // Called after Sprite
  //}
  delay(500);
}
