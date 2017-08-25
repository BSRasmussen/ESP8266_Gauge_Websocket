
//--- Wifi Functions ---

//----------------------------------------------------------------------- 
// Station Configuration
//-----------------------------------------------------------------------
void Wifi_STA_Connect()
{
  WiFi.mode(WIFI_STA);
  Serial.println("mode is station only");
  Serial.print("Connecting to AP");
  WiFi.begin(ssid, password);
  //Connessione alla rete WiFi con IP Statico
  WiFi.config(IPAddress(192,168,1,220), IPAddress(192,168,1,1),IPAddress(255,255,255,0));
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20){
	   delay(500);
	   Serial.print(".");
  }
  if(WiFi.status() == WL_CONNECTED){
  Serial.print("IP address is:");
  myIP = WiFi.localIP();
  Serial.println(myIP);
   }
  // Dopo 10 secondi se non si è connesso si ferma l'esecuzione 
  if(i == 21){
    Serial.print("Could not connect to"); Serial.println(ssid);
    Wifi_AP_Connect();
  }
  }
  
//----------------------------------------------------------------------- 
// Access Point configuration
//-----------------------------------------------------------------------  
 void Wifi_AP_Connect()
{ 
    WiFi.mode(WIFI_AP);      
    Serial.println("mode is Access Point only");

    Serial.println("Configuring access point...");
    // You can remove the password parameter if you want the AP to be open. /
    //WiFi.softAP(ssid, password);
    //WiFi.softAP("esp8266_ap", "");
    WiFi.softAP("esp8266_ap");
    myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }      
