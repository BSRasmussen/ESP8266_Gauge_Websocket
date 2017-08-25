
//--- LOOP ---
void loop(void){
  webSocket.loop();
    ftpSrv.handleFTP();        //make sure in loop you call handleFTP()!!  
  server.handleClient();
  yield();
  misura_temp();
}
