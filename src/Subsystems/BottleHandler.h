#ifndef BOTTLE_HANDLER_H
#define BOTTLE_HANDLER_H

#include <Arduino.h>

#define BREAK_PIN 24

class BottleHandler {
private:
    
public:
    BottleHandler();
    ~BottleHandler();
    void init();
    bool hasBottle();
};

BottleHandler::BottleHandler() {}

BottleHandler::~BottleHandler() {}

void BottleHandler::init() {
    pinMode(BREAK_PIN, INPUT_PULLUP);
}

bool BottleHandler::hasBottle() {
    return !digitalRead(BREAK_PIN);
}



#endif