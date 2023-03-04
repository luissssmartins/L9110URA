#ifndef L9110H_H

#define L9110H_H

#include <Arduino.h>

class L9110H {
    
    public:
      L9110H(int pA_1A, int pA_1B, int pB_1A, int pB_1B);
      
      void setup();

      void setSpeedA(int i, int pwm);

      void setSpeedB(int i, int pwm);

      void stopMotorA();
      
      void stopMotorB();

    private:

    int pinAPWM;
    int pinADir;
    int pinBPWM;
    int pinBDir;
};

#endif