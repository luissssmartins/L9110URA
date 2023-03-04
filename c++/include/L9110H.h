#ifndef L9110H_H

#define L9110H_H

#include <Arduino.h>

class L9110H {
    
    public:
      L9110H();

      void motor(int motorNumber, String instruction, int speed);

      void forward(int i);

      void backward(int i);

      void right(int i);

      void left(int i);

      void stop();

    private:

    int pinA;
    int pinB;
};

#endif