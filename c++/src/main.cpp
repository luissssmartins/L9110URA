#include <Arduino.h>

#include "L9110H.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

L9110H robot(13, 12, 5, 23);

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Can't initialize SPIFFS, please restart and try again.");
    return;
  }

  robot.setup();
}

void loop() {
  
}