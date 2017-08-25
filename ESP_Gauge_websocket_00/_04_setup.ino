//--- SETUP ---

void setup(void){
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {    
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    DBG_OUTPUT_PORT.printf("\n");
  }


	Wifi_STA_Connect();


  //MDNS.begin(host);
//  DBG_OUTPUT_PORT.print("Open http://");
//  DBG_OUTPUT_PORT.print(host);
//  DBG_OUTPUT_PORT.println(".local/edit to see the file browser");
  
  
  //SERVER INIT
  //called when the url is not defined here
  //use it to load content from SPIFFS
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");


  /////FTP Setup, ensure SPIFFS is started before ftp;  /////////
  
  if (SPIFFS.begin()) {
      DBG_OUTPUT_PORT.println("SPIFFS opened!");
      ftpSrv.begin("esp","esp");
/*Username, Password for ftp.  set ports in ESP8266FtpServer.h  (default 21, 50009 for PASV)
tested with Filezilla, and the basics work (update/download/rename/delete).
There's no create/modify directory support(no directory support in SPIFFS yet).
You need to setup Filezilla(or other client) to only allow 1 connection..  FileZilla Go to File/Site Manager then select your site.
In Transfer Settings, check "Limit number of simultaneous connections" and set the maximum to 1
Only supports Passive ftp mode....
It does NOT support any encryption, so you'll have to disable any form of encryption...
*/
  } 


// Avvia Websocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  DBG_OUTPUT_PORT.println("websocket started");
}
