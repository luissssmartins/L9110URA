#include "L9110H.h"

#include <Arduino.h>

L9110H::L9110H() {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void L9110H::motor(int motorNumber, String command, int speed) {

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

    if (command == "A") {
        analogWrite(pinB, 1);
        analogWrite(pinA, speed);
    } else if (command == "B") {
        analogWrite(pinA, 1);
        analogWrite(pinB, speed);
    } else if (command = "STOP") {
        analogWrite(pinA, 0);
        analogWrite(pinB, 0);
    }
}

void L9110H::forward(int i) {
    motor(1, "B", i);
    motor(2, "A", i);

    delay(300);

    stop();
}

void L9110H::backward(int i) {
    motor(1, "A", i);
    motor(2, "B", i);

    delay(300);

    stop();
}

void L9110H::right(int i) {
    motor(1, "B", i);
    motor(2, "B", i);

    delay(300);

    stop();
}

void L9110H::left(int i) {
    motor(1, "A", i);
    motor(2, "A", i);

    delay (300);

    stop();
}

void L9110H::stop() {
    motor(1, "STOP", 0);
    motor(2, "STOP", 0);
}
