#include<WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include<HTTPClient.h>
#include<Firebase_ESP_Client.h>

int btnPin = 27;
int btnState=0;

const char* SSID = "Nakul1234";
const char* Password = "Nakul@250";
WiFiServer server(8080);  //serving port

void GenerateJson(String x)
{
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["ReturnVal"] = x;

  String jsonString;
  serializeJson(jsonDoc,jsonString);
  Serial.println(jsonString);
} 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(btnPin,INPUT);

  //connect to wifi

  Serial.print("Connecting to: ");
  Serial.println(SSID);

  WiFi.begin(SSID,Password);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting...");
    delay(500);
  }
  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  btnState=digitalRead(btnPin);
  if(btnState==HIGH)
  {
    //Serial.println("True");
    GenerateJson("True");
  }
  else
  {
    GenerateJson("False");
    //Serial.println("False");
  }
  delay(20);

}
