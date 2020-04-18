// PubNub MQTT example using ESP32.
#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"
// Connection info.
int val=0;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;
int ledpin=2;
char* timer;
const char* ssid = "Hemanth";
const char* password =  "hellisboy";
const char* mqttServer = "mqtt.pndsn.com";
const int mqttPort = 1883;
const char* clientID = "pub-c-6ec004b0-0381-4766-8ceb-a110f9be79b8/sub-c-22c36d12-74a8-11ea-b179-9eded212fb8b/Client-mhvkx";
const char* channelName = "Channel-4hjnvug9z";
WiFiClient MQTTclient;
PubSubClient client(MQTTclient);
void callback(char* topic, byte* payload, unsigned int length) {
  String payload_buff;
  for (int i=0;i<length;i++) {
    payload_buff = payload_buff+String((char)payload[i]);
  }
  Serial.println(payload_buff); // Print out messages.
}
long lastReconnectAttempt = 0;
boolean reconnect() {
  if (client.connect(clientID)) {
    client.subscribe(channelName); // Subscribe to channel.
  }
  return client.connected();
}
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
  Serial.begin(9600);
  Serial.println("Attempting to connect...");
  WiFi.begin(ssid, password); // Connect to WiFi.
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Couldn't connect to WiFi.");
      while(1) delay(100);
  }
 
  client.setServer(mqttServer, mqttPort); // Connect to PubNub.
  client.setCallback(callback);
  lastReconnectAttempt = 0;
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printTimeNow();
   }
void loop() {
  if (!client.connected()) {
    long now = millis();
    
if(val<=0&& val>=-15) //hall effect sensor value range when tested with an aluminium box
{
  digitalWrite(ledpin,LOW);
  }
  else
  {
    digitalWrite(ledpin,HIGH);
    delay(50); //delay and wait for 50 seconds

  }
  delay(500);
    if (now - lastReconnectAttempt > 5000) { // Try to reconnect.
      lastReconnectAttempt = now;
      if (reconnect()) { // Attempt to reconnect.
        lastReconnectAttempt = 0;
      }
    }
  } else { // Connected.
    client.loop();
    delay(2000);
    val=hallRead();
    if(val<=0&& val>=-15)
    {
      digitalWrite(ledpin,LOW);
    client.publish(channelName,"Box is Closed"); // Publish message.
    delay(1000);
    }    
    
    else
    {
      digitalWrite(ledpin,HIGH);
      delay(200);
      client.publish(channelName,"Box is Open");
      delay(5000);
      }
  }
}
