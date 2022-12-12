
/*
Throw a switch based on the status of a value in a mysql DB
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "[SSID]"
#define STAPSK  "[password]"
#endif

int switchstate = 0;
int relaisPin = D3;
int payloadInt = 0;

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WiFiMulti WiFiMulti;

//////////////////////////////////////////////////////////////////
void setup() {
 Serial.begin(115200);
 pinMode(relaisPin, OUTPUT);
 digitalWrite(relaisPin, LOW);
 
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1500);
  }

  Serial.println("");
  Serial.println("Setup Arduino");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Relais status: ");
  Serial.println(switchstate);
  Serial.print("Payload status: ");
  Serial.println(payloadInt);
  Serial.println("");  
  delay(1500);
}

void loop()
{
  WiFiClient client;
  HTTPClient http;
  Serial.println("Check code");
  Serial.println("");
  http.begin(client, "[server]/check.php");
  int httpCode = http.GET();
      if(httpCode > 0) {
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            payloadInt = payload.toInt();
         if (payloadInt == 1) {
             switchstate = payloadInt;
         }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
     }
  http.end();
  Serial.println("Einde check code. wacht 10 sec");
  delay(10000);
  Serial.println("");
  if (switchstate == 1) {
  Serial.println("Reset code");
  Serial.println("");
  // Zet het kunstwerk aan.
  Serial.println("Pin 3 Hoog"); 
  digitalWrite(relaisPin, HIGH);
  delay(2000);
  Serial.println("Pin 3 Laag");  
  digitalWrite(relaisPin, LOW);
  delay(2000);  
//Reset DB    
    http.begin(client, "[server]/reset.php");
        int httpCode = http.GET();
   if(httpCode > 0) {
      switchstate = 0;
   } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
     }
  http.end();
  Serial.println("Wachten tot het item klaar is");
    delay(180000);  // wait 3min minutes 
 }
}
