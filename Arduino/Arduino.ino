// #include <WiFiLink.h>

// #include <WiFi.h>
// #include <WebServer.h>


// #include <UnoWiFiDevEd.h>v

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// #include <ArduinoHttpClient.h>


int redPin = 7;
int greenPin = 12;
int btnPin = 8;
int btnState = 0;

// const char* ssid = "Nakul_5G";       // Your Wi-Fi network name
// const char* password = "Nakul@250";  // Your Wi-Fi network password


// HttpClient http;

/* ------------------------josn generator------------ */

void JsonGen() {
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
  serializeJson(jsonReport, jsonStr);

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
  Serial.println("True");
}

/* -------------- Setup ------------------- */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(btnPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  //http.begin("192.168.29.5");
  //int responseCode = http.POST;
  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  //   }

  //   Serial.println("Connected to WiFi");
  }

  void loop() {
    // put your main code here, to run repeatedly:`
    btnState = digitalRead(btnPin);
    JsonGen();
    delay(5000);
    if (btnState == HIGH) {
      greenLightOn();
    } else {
      redLightOn();
    }
  }
