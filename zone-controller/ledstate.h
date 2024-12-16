#include <Arduino.h>
#include <ArduinoLog.h>
#include "zonestate.h"

#ifndef LED_STATE_H_
#define LED_STATE_H_

void initilizeLedStateReader();
bool getLedState(int zone);
int getLedPin(int zone);

#endif