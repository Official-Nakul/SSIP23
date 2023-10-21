#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WiFi_SSID "Nakul1234"
#define WiFi_Password "Nakul@250"
#define api_key_gd "AIzaSyC9iBakZssP8HMA8hlWAm64ou6rDZpvmcE"
#define database_url_gd "https://esp32-gas-detector-b245c-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define btnPin 26
#define ledPin 27

int btnState = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

unsigned long sendDataPrevMillis = 0;
bool signupOk = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.ready() && signupOk && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    btnState = digitalRead(btnPin);
    if (btnState == HIGH) {
      json.set("State", String("Ganpat univesity"));
      Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, "resp", &json) ? "ok" : fbdo.errorReason().c_str());
    } else {
     json.set("State", String("Guni"));
      Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, "resp", &json) ? "ok" : fbdo.errorReason().c_str());
    }
    // if (btnState == HIGH) {
    //   if (Firebase.RTDB.setBool(&fbdo, "Btn/State", true)) {
    //     Serial.println("Successfully saved to: " + fbdo.dataPath());
    //     Serial.println("Type: " + fbdo.dataType());
    //     digitalWrite(ledPin,HIGH);
    //   } else {
    //     Serial.println("Error: " + fbdo.errorReason());
    //   }
    // } else {
    //   if (Firebase.RTDB.setBool(&fbdo, "Btn/State", false)) {
    //     Serial.println("Successfully saved to: " + fbdo.dataPath());
    //     Serial.println("Type: " + fbdo.dataType());
    //     digitalWrite(ledPin,HIGH);
    //   } else {
    //     Serial.println("Error: " + fbdo.errorReason());
    //   }
    // }
  }
  delay(30);
}

