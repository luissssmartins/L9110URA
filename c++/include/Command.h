#ifndef COMMAND_H

#define COMMAND_H

#include <Arduino.h>


class Command {

    public:
      Command();

      enum CommandType {
        MANUAL_COMMAND,
        TIMED_COMMAND,
        BLOCK_COMMAND
      };

      void createCommand(int id, String name, CommandType type);

      void registerCommand(int id);

      void unregisterCommand(int id);
};

#endif