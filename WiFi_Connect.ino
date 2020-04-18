#include<WiFi.h>
 const char* ssid ="Hemanth";
 const char* pwd= "hellisboy";
 int ledpin=2;

void setup()
{
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  Serial.printf("connecting to %s",ssid);
  WiFi.begin(ssid,pwd);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
      
    }
    Serial.println("connected");
    digitalWrite(ledpin,HIGH);
     WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
  }
 void loop()
 {}
 
