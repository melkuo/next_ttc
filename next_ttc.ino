#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFiClientSecureBearSSL.h>

// Setup variables
const char* ssid = "";
const char* password = "";
String stopsUrlString = "&stops=504|1159&stops=501|10272";
int delayBetweenPredictions = 20000;

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 12
#define DATA_PIN_1 D7  // GPIO13
#define CLK_PIN_1 D5   // GPIO14
#define CS_PIN_1 D8    // GPIO15
#define DATA_PIN_2 D2 // GPIO4
#define CLK_PIN_2 D1  // GPIO5
#define CS_PIN_2 D3   // GPIO0

MD_Parola display2 = MD_Parola(HARDWARE_TYPE, DATA_PIN_1, CLK_PIN_1, CS_PIN_1, MAX_DEVICES);
MD_Parola display1 = MD_Parola(HARDWARE_TYPE, DATA_PIN_2, CLK_PIN_2, CS_PIN_2, MAX_DEVICES);

void setup() {
  Serial.begin(9600);
  display1.begin();
  display1.setIntensity(0);
  display1.displayClear();
  display2.begin();
  display2.setIntensity(0);
  display2.displayClear();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    display1.print("Connecting to wifi");
    delay(500);
    display1.print("Connecting to wifi.");
    delay(500);
    display1.print("Connecting to wifi..");
    delay(500);
    display1.print("Connecting to wifi...");
    delay(500);
  }

  display1.displayClear();
  display2.displayClear();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    display1.print("Wifi disconnected");
  }

  String requestUrl = "https://retro.umoiq.com/service/publicJSONFeed?command=predictionsForMultiStops&a=ttc" + stopsUrlString;
  String response = httpsGetRequest(requestUrl);
  JsonDocument doc;
  deserializeJson(doc, response);

  JsonArray predictions = doc["predictions"];
  for (JsonVariant preds : predictions) {
    if (preds["direction"]) {
      // Case when there is one direction
      if (preds["direction"]["title"]) {
        const char* displayText1 = "";
        displayText1 = preds["direction"]["title"];
        display1.print(displayText1);

        JsonArray pred = preds["direction"]["prediction"];
        char displayText2[50] = "";
        for (JsonVariant p : pred) {
          strcat(displayText2, p["minutes"]);
          strcat(displayText2, " ");
        }

        strcat(displayText2, "mins");
        display2.print(displayText2);
        delay(delayBetweenPredictions);
        continue;
      }

      // Case when there is more than one direction
      JsonArray direction = preds["direction"];
      for (JsonVariant dir : direction) {
        const char* displayText1 = "";
        displayText1 = dir["title"];
        display1.print(displayText1);

        JsonArray pred = dir["prediction"];
        char displayText2[50] = "";
        for (JsonVariant p : pred) {
          strcat(displayText2, p["minutes"]);
          strcat(displayText2, " ");
        }

        strcat(displayText2, "mins");
        display2.print(displayText2);
        delay(delayBetweenPredictions);
      }
    }
  }
}

String httpsGetRequest(String serverName) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();

  HTTPClient https;
  https.begin(*client, serverName);
  int httpCode = https.GET();
  String response = "{}";

  if (httpCode > 0) {
    response = https.getString();

    if (httpCode != 200) {
      display1.displayClear();
      display1.print(httpCode);
    }
  } else {
    display1.print("Error: no response code");
  }

  https.end();
  return response;
}
