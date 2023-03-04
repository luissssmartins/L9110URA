#include "L9110H.h"

L9110H::L9110H(int pA_1A, int pA_1B, int pB_1A, int pB_1B){
    pinAPWM = pA_1A;
    pinBPWM = pB_1A;
    pinADir = pA_1B;
    pinBDir = pB_1B;
}

void L9110H::setup() {
    pinMode(pinAPWM, OUTPUT);
    pinMode(pinADir, OUTPUT);
    pinMode(pinBPWM, OUTPUT);
    pinMode(pinBDir, OUTPUT);

    digitalWrite(pinAPWM, LOW);
    digitalWrite(pinADir, LOW);
    digitalWrite(pinBPWM, LOW);
    digitalWrite(pinBDir, LOW);
}

void L9110H::setSpeedA(int i, int pwm) {
    digitalWrite(pinADir, i);
    
    analogWrite(pinAPWM, 255 - pwm);
}

void L9110H::setSpeedB(int i, int pwm) {
    digitalWrite(pinBDir, i);

    if (i) {
        analogWrite(pinBPWM, 255 - pwm);
    } else {
        analogWrite(pinBPWM, pwm);
    }
}

void L9110H::stopMotorA() {
    digitalWrite(pinADir, LOW);
    digitalWrite(pinAPWM, LOW);
}

void L9110H::stopMotorB() {
    digitalWrite(pinBDir, LOW);
    digitalWrite(pinBPWM, LOW);
}