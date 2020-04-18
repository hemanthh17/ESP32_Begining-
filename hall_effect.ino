#include <WiFi.h>
#include "time.h"

int val=0;
int ledpin=2;
const char* ssid       = "Hemanth";
const char* password   = "hellisboy";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;//we do not do this in India

void printTimeNow()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(ledpin,OUTPUT);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
     Serial.print(".");
  }
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printTimeNow();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
val= hallRead();
Serial.println(val);
delay(1000);
if(val<=0&& val>=-15) //hall effect sensor value range when tested with an aluminium box
{
  digitalWrite(ledpin,LOW);
  Serial.println("BOX is Closed");//most of the time the same value comes even for open box...possibly due to stray magnetic fields in the room with electricity or due to laptop|| An LDR can be fitted to verify it secondarily and confirm the box is open or not
      }
  else
  {
    digitalWrite(ledpin,HIGH);
    Serial.println("BOX is Open");
    printTimeNow();
    delay(50000); //delay and wait for 50 seconds

  }
}
