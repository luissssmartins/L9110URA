#include <Arduino.h>

#include "L9110H.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "URA TESTE";
const char* password = "12345678";

String command;

L9110H robot;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Can't initialize SPIFFS, please restart and try again.");
    return;
  }

  WiFi.softAP(ssid, password);

  Serial.println("WiFi AP started!");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "style.css");
  });

  server.on("/newura.png", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "newura.png", String(), false);
  }); 

  server.on("/frt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.forward(255);

    Serial.println("command frt");

    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/trs", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.backward(255);

    Serial.println("command trs");

    request->send(SPIFFS, "/index.html", String(), false);
  });

   server.on("/esq", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.left(255);

    Serial.println("command esq");

    request->send(SPIFFS, "/index.html", String(), false);
  });

   server.on("/drt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.right(255);

    Serial.println("command drt");

    request->send(SPIFFS, "/index.html", String(), false);
  });
  

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest* request) {

    robot.stop();

    Serial.println("command stop");

    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.begin();
}

void loop() {

}