#include "Command.h"

#include <Arduino.h>

int availableCommands[];

Command::Command() {
    Serial.println("Command system initialized.");
}

void Command::registerCommand(int id) {
    availableCommands[id];
}

void Command::unregisterCommand(int id) {
    availableCommands[id] = -1;
}

void Command::createCommand(int id, String name, CommandType type) {
    registerCommand(id);
}

int getCommandById(int id) {
    return availableCommands[id];
}
