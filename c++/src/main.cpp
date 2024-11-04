#include <Arduino.h>
#include <SimpleFTPServer.h>
#include <ArduinoJson.h>
#include <vector>

#include "L9110H.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "AsyncTCP.h"

using namespace std;

String command;

L9110H robot;

AsyncWebServer server(80);

FtpServer ftpSrv;

StaticJsonDocument<200> document;

struct Command {
  String name;
  String parameter;

  int seconds;
};

vector<Command> commandList;

void operateCommands() {
  for (const auto& command : commandList) {

    if (command.name == "forward" || command.name == "frente") {
      robot.forward(command.parameter.toInt(), command.seconds * 1000, true);
    } else if (command.name == "backward" || command.name == "tras") {
      robot.backward(command.parameter.toInt(), command.seconds * 1000, true);
    } else if (command.name == "left" || command.name == "esquerda") {
      robot.left(command.parameter.toInt(), command.seconds * 1000, true);
    } else if (command.name == "right" || command.name == "direita") {
      robot.right(command.parameter.toInt(), command.seconds * 1000, true);
    } else if (command.name == "stop" || command.name == "parar") {
      robot.stop();
    }

    delay(command.seconds * 1000);
  }

  commandList.clear();
}

void parseCommands(String commands) {
  char b[commands.length() + 1];

  commands.toCharArray(b, commands.length() + 1);

  char* consumer = strtok(b, ";");

  while (consumer != nullptr) {
    Command command;

    command.name = String(consumer);

    consumer = strtok(nullptr, ";");
    if (consumer != nullptr) {
      command.parameter = String(consumer);
    }

    consumer = strtok(nullptr, ";");
    if (consumer != nullptr) {
      command.seconds = atoi(consumer);
    }

    commandList.push_back(command);

    consumer = strtok(nullptr, ";");
  }
}

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

  if (commandList.size() > 0) {
    commandList.clear();
  }

  const char* SSID = document["ssid"];
  const char* PASSWORD = document["password"];

  WiFi.softAP(SSID, PASSWORD);

  Serial.println("WiFi AP started!");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html");   
  });

  server.on("/favicon.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/favicon.png", "image/png");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css");
  });

  server.on("/logo.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/logo.svg");
  });

  server.on("/downbutton.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/downbutton.svg");
  });

  server.on("/leftbutton.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/leftbutton.svg");
  });

  server.on("/line.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/line.svg");
  });

  server.on("/rightbutton.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/rightbutton.svg");
  });

  server.on("/upbutton.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/upbutton.svg");
  });

  server.on("/stopbutton.svg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/stopbutton.svg");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/script.js");
  });

  server.on("/frt", HTTP_GET, [](AsyncWebServerRequest *request) {
    robot.forward(255, 150, true);    

    request->send(204);
  });

  server.on("/trs", HTTP_GET, [](AsyncWebServerRequest *request) {
    robot.backward(255, 150, true);

    request->send(204);
  });

   server.on("/esq", HTTP_GET, [](AsyncWebServerRequest *request) {
    robot.left(255, 150, true);

    request->send(204);
  });

   server.on("/drt", HTTP_GET, [](AsyncWebServerRequest *request) {
    robot.right(255, 150, true);

    request->send(204);
  });
  

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest* request) {
    robot.stop();

    request->send(204);
  });

  server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request) {

    if (request->hasParam("action")) {
      String action = request->getParam("action")->value();

      request->send(204);

      parseCommands(action);
      operateCommands();
    }
  });

  server.begin();

  ftpSrv.begin("ura", "l9110ura");
}

void loop() {
  ftpSrv.handleFTP();
}