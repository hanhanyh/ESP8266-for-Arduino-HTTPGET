#include <Arduino.h>
#include<string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

String  serialbuff;
ESP8266WiFiMulti WiFiMulti;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("mi6x", "qiuyuhan");
}
void loop() {
  // wait for WiFi connection
  printf("wait for wifi.");
  while(WiFiMulti.run()!=WL_CONNECTED)
  {
    Serial.write(".");
    delay(1000);
  }
  //-------------------------------------------
  Serial.println("wait for serial.");
  while(!Serial.available())
  {
    Serial.write(".");
    delay(1000);
  }
  serialbuff=Serial.readStringUntil('#');
  Serial.println(serialbuff);
  
  //--------------------------------------------
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://119.29.11.92/", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    Serial.println(serialbuff);
    http.begin(serialbuff); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
