/* ESP_Gauge_websocket_00.ino
 * 
 * 
 * 
= SPIFFS
upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md#uploading-files-to-file-system

= Javascript GAUGE
Javascript Gauge
http://www.esp8266.com/viewtopic.php?p=36089
http://newmaan.com/gauge.min.js
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <FS.h>
#include <ESP8266FtpServer.h> //https://github.com/nailbuster/esp8266FTPServer

#include <WebSocketsServer.h>
#include <Hash.h>



#define DBG_OUTPUT_PORT Serial



const char* ssid = "Rete";
const char* password = "pippo2017";

IPAddress myIP;


//const char* host = "esp8266fs";
ESP8266WebServer server(80);
//holds the current upload
//File fsUploadFile;

FtpServer ftpSrv;   //set #define FTP_DEBUG in ESP8266FtpServer.h to see ftp verbose on serial


WebSocketsServer webSocket = WebSocketsServer(81);


#define INTERVAL 30 // in sec
float temp=20; 
float old_temp=20; 
//String Swebtemp="20"; //temperatura per web
char ws_text[5];
long temp_time;

bool new_temp=0;

//Dichiarazione funzioni
void Wifi_AP_Connect();
void Wifi_STA_Connect();
String formatBytes(size_t bytes);
String getContentType(String filename);
bool handleFileRead(String path);
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void misura_temp(void);

