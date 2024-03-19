/* 
 *  OG Code at bottom of file..
 */


void launchWeb()
{
  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    wifi_menu();
  }
  //Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    //Serial.println("WiFi connected");
  //Serial.print("Local IP: ");
  //Serial.println(WiFi.localIP());
  //Serial.print("SoftAP IP: ");
  //Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  //Serial.println("Server started");
}


void setupAP(void)
{
  if (back < threshold) {      //  ~~~~~~~ Internal Touch 2 - Back/Delete ~~~~~~~
    //back = true;
    wifi_menu();
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";                    // start list
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<div><li><a href='#p' onclick='c(this)'>";
    //st += "<li>";               // list
    st += WiFi.SSID(i);         // ssid for list number
    //st += " (";
    //st += WiFi.RSSI(i);         // signal strength for ssid
    //st += ")";
    //st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li></a>&nbsp;</div>";
  }
  st += "</ol>";              // end list
  delay(100);
  WiFi.softAP("Setup_AP", "Tintin10");  // SSID, Password
  Serial.println("Initializing_softap_for_wifi credentials_modification");
  launchWeb();
  //Serial.println("over");
}




/*
void setup_ap()
{
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //reset settings - for testing
  //wifiManager.resetSettings();

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  //wifiManager.setTimeout(120);


  //WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
  //WiFi.mode(WIFI_STA);

  if (!wifiManager.startConfigPortal("Setup_AP", "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  wifi_state = true;
  Serial.println("Connection Established...");
  Serial.print("CONNECTED TO: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.localIP());
  Serial.print("SIGNAL: ");
  Serial.print(WiFi.RSSI()); 
}
*/
