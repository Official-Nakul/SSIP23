#include <MQ2.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WiFi_SSID "Nakul1234"
#define WiFi_Password "Nakul@250"
#define api_key_gd "AIzaSyC9iBakZssP8HMA8hlWAm64ou6rDZpvmcE"
#define database_url_gd "https://esp32-gas-detector-b245c-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define buzPin 26
#define ledPin 27
#define MQ2APin 34
#define MQ2DPin 35
#define scl 22 
#define sda 21 

MQ2 mq2(MQ2APin);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

unsigned long sendDataPrevMillis = 0;
bool signupOk = false;

int LPG, CO, Smoke;

void setup() {
  // put your setup code here, to run once:
  WiFi.begin(WiFi_SSID, WiFi_Password);
  Serial.print("Connecting to: ");
  Serial.println(WiFi_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected");
  Serial.print("Local ip: ");
  Serial.print(WiFi.localIP());

  config.api_key = api_key_gd;
  config.database_url = database_url_gd;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("SignUp ok");
    signupOk = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  pinMode(MQ2APin, INPUT);
  pinMode(buzPin, OUTPUT);
  Serial.begin(115200);

  Serial.println("MQ2 warming up!");
	delay(20000);
}

void loop() {
  // put your main code here, to run repeatedly:

  float Gasvalue = analogRead(MQ2APin);

  if (Gasvalue > 3000) {
    Serial.println("True");
    analogWrite(ledPin, 255);
  } else {
    analogWrite(ledPin, 0);
  }


  if (Firebase.ready() && signupOk && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    json.set("GasVal", String(Gasvalue));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, "MQ2Data", &json) ? "ok" : fbdo.errorReason().c_str());
  }
  
}
