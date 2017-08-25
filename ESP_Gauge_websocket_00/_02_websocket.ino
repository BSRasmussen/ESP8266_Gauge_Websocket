//-----------------------------------------------------------------------
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  static uint32_t lastMillis = 0;
  
  Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
  switch(type) {

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\r\n", num);
      break;

    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // Send the current LED status
        if (new_temp) {
          sprintf(ws_text,"%d",(int)temp);
          webSocket.sendTXT(num, ws_text, strlen(ws_text));
                // send data to all connected clients
			//webSocket.broadcastTXT(webtemp, strlen(webtemp));
     new_temp=0;
        }
        /*else {
          webSocket.sendTXT(num, LEDOFF, strlen(LEDOFF));
        }*/
      }
      break;
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- --       
    case WStype_TEXT:
      Serial.printf("[%u] [%u ms] get Text: %s\r", num, millis()-lastMillis, payload);
      lastMillis = millis();


      break;
    
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- --   
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\r\n", num, length);
      //hexdump(payload, length);
/*
      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
*/
      break;
      
    // -- -- -- -- -- -- -- -- -- -- -- -- -- -- --       
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
}



