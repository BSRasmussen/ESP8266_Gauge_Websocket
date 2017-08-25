//--- FUNCTIONS ----

void misura_temp(void){
  //Usato millis per non bloccare il web server ESP 
  long time=millis();
    if(time>temp_time+INTERVAL*1000){
		temp=random(0,51);
		temp_time=millis();
}
  
  if (temp != old_temp)
  {
    new_temp=1;
    // aggiorna il valore di temperatura precedentemente registrato
    //Swebtemp.toCharArray(ws_text, strlen(ws_text));
    sprintf(ws_text,"%d",(int)temp);

  DBG_OUTPUT_PORT.print("Temperatura cambiata: ");
	DBG_OUTPUT_PORT.println(temp);
  DBG_OUTPUT_PORT.println(ws_text);
  old_temp=temp;

  //send data to all connected clients
  webSocket.broadcastTXT(ws_text, strlen(ws_text));
  
  }
  }


/*
 dtostrf(resistance, 6, 2, result);

sprintf(str, "String value: %d.%02d", (int)f, abs((int)(f*100)%100));
 */


