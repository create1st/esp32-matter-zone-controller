#include <Arduino.h>
#include <ArduinoLog.h>
#include "zonestate.h"

#ifndef LED_STATE_H_
#define LED_STATE_H_

void initilizeLedStateReader();
ZoneState getLedState();

#endif