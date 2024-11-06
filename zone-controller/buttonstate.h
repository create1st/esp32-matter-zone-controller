#include <Arduino.h>
#include <ArduinoLog.h>
#include "zonestate.h"

#ifndef BUTTON_STATE_H_
#define BUTTON_STATE_H_

const int pushButtonDelay = 500; // msec

void initilizeButtonStateWriter();
void setButtonState(ZoneState zoneState);

#endif