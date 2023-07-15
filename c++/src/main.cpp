#include <Arduino.h>
#include <SimpleFTPServer.h>
#include <ArduinoJson.h>

#include "L9110H.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "AsyncTCP.h"

String command;

L9110H robot;

AsyncWebServer server(80);

FtpServer ftpSrv;

StaticJsonDocument<200> document;

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Can't initialize SPIFFS, please restart and try again.");
    return;
  }

  File configFile = SPIFFS.open("/config.json", "r");

  if (!configFile) {
    Serial.println("Can't read config.json, please restart and try again.");
    return;
  }

  DeserializationError error = deserializeJson(document, configFile);

  if (error) {
    Serial.println(error.f_str());
    return;
  }

  const char* SSID = document["ssid"];
  const char* PASSWORD = document["password"];

  WiFi.softAP(SSID, PASSWORD);

  Serial.println("WiFi AP started!");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html");   
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "style.css");
  });
  
  server.on("/frt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.forward(255, 300, true);

    Serial.println("command frt");
    
    request->send(204);
  });

  server.on("/trs", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.backward(255, 300, true);

    Serial.println("command trs");

    request->send(204);
  });

   server.on("/esq", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.left(255, 300, true);

    Serial.println("command esq");

    request->send(204);
  });

   server.on("/drt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.right(255, 300, true);

    Serial.println("command drt");

    request->send(204);
  });
  

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest* request) {

    robot.stop();

    Serial.println("command stop");

    request->send(204);
  });

  server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request) {

    if (request->hasParam("action")) {

      request->send(204);

      String action = request->getParam("action")->value();

      if (action == "quadrado") {

        robot.forward(255, 2000, true);

        delay(2000);

        robot.right(255, 300, true);

        delay(2000);

        robot.forward(255, 2000, true);

        delay(2000);

        robot.right(255, 300, true);

        delay(2000);

        robot.forward(255, 2000, true);

        delay(2000);

        robot.right(255, 300, true);

        delay(2000);

        robot.forward(255, 2000, true);

        delay(2000);

        robot.stop();

      }
    }
  });

  server.begin();

  ftpSrv.begin("ura", "l9110ura");
}

void loop() {
  ftpSrv.handleFTP();
}