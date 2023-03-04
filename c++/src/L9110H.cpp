#include "L9110H.h"

#include <Arduino.h>

L9110H::L9110H() {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void L9110H::motor(int motorNumber, String instruction, int speed) {

    switch (motorNumber) {

        case 1: {
            pinA = 13;
            pinB = 12;
            break;
        }

        case 2: {
            pinA = 5;
            pinB = 23;
            break;
        }

        default: {
            break;
        }
    }

    if (instruction == "FORWARD") {
        analogWrite(pinB, 1);
        analogWrite(pinA, speed);
    } else if (instruction == "BACKWARD") {
        analogWrite(pinA, 1);
        analogWrite(pinB, speed);
    } else if (instruction == "STOP") {
        analogWrite(pinA, 0);
        analogWrite(pinB, 0);
    }
}

void L9110H::forward(int i) {
    motor(1, "BACKWARD", i);
    motor(2, "FORWARD", i);

    delay(300);

    stop();
}

void L9110H::backward(int i) {
    motor(1, "FORWARD", i);
    motor(2, "BACKWARD", i);

    delay(300);

    stop();
}

void L9110H::right(int i) {
    motor(1, "BACKWARD", i);
    motor(2, "BACKWARD", i);

    delay(300);

    stop();
}

void L9110H::left(int i) {
    motor(1, "FORWARD", i);
    motor(2, "FORWARD", i);

    delay(300);

    stop();
}

void L9110H::stop() {
    motor(1, "STOP", 0);
    motor(2, "STOP", 0);
}
