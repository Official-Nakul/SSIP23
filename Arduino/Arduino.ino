// #include <WiFiLink.h>

// #include <WiFi.h>
// #include <WebServer.h>


// #include <UnoWiFiDevEd.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// #include <ArduinoHttpClient.h>


int redPin = 7;
int greenPin = 12;
int btnPin = 8;
int btnState = 0;

const char* ssid = "Your_SSID"; // Your Wi-Fi network name
const char* password = "Your_Password"; // Your Wi-Fi network password


// HTTPClient http;

/* ------------------------josn generator------------ */

void JsonGen()
{
  StaticJsonDocument<200> jsonReport;
  JsonArray array = jsonReport.to<JsonArray>();

  JsonObject obj1 = array.createNestedObject();
  obj1["Gas"] = "CNG";
  obj1["Value"] = 25;

  JsonObject obj2 = array.createNestedObject();
  obj2["Gas"] = "LNG";
  obj2["Value"] = 20;

  JsonObject obj3 = array.createNestedObject();
  obj3["Gas"] = "CO2";
  obj3["Value"] = 30;

  String jsonStr;
  serializeJson(jsonReport,jsonStr);

  Serial.println(jsonStr); 
}

/* ---------------Light function-------------------- */
void redLightOn() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
}

void greenLightOn() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
}

/* -------------- Setup ------------------- */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(btnPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // http.begin("google.com");
  // int responseCode = http.POST;
  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }

  // Serial.println("Connected to WiFi");
}

void loop() {
  // put your main code here, to run repeatedly:`
  btnState = digitalRead(btnPin);

  if (btnState == HIGH) {
    greenLightOn();
  } else {
    redLightOn();
  }
}
