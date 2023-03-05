#include <Arduino.h>
#include <SimpleFTPServer.h>

#include "L9110H.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "URA TESTE";
const char* password = "12345678";

String command;

L9110H robot;

AsyncWebServer server(80);

FtpServer ftpSrv;

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
    request->send(SPIFFS, "/index.html");   
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "style.css");
  });

  server.on("/newura.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/newura.png", "image/png");
  });

  // server.on("/action", HTTP_POST, [](AsyncWebServerRequest *request) {
  //   String input = request->arg("input-text");

  //   if (input == "FRT") {
  //     robot.forward(255);
  //     request->send(200);
  //   }

  //   //request->send(200);
  // });

  server.on("/frt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.forward(255);

    Serial.println("command frt");

    request->send(SPIFFS, "/index.html");
  });

  server.on("/trs", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.backward(255);

    Serial.println("command trs");

    request->send(SPIFFS, "/index.html");
  });

   server.on("/esq", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.left(255);

    Serial.println("command esq");

    request->send(SPIFFS, "/index.html");
  });

   server.on("/drt", HTTP_GET, [](AsyncWebServerRequest *request) {

    robot.right(255);

    Serial.println("command drt");

    request->send(SPIFFS, "/index.html");
  });
  

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest* request) {

    robot.stop();

    Serial.println("command stop");

    request->send(SPIFFS, "/index.html");
  });

  server.begin();

  ftpSrv.begin("ura", "l9110ura");
}

void loop() {
  ftpSrv.handleFTP();
}