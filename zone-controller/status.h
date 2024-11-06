#include <Arduino.h>

#ifndef STATUS_H_
#define STATUS_H_

void updateLedColor(uint8_t r, uint8_t g, uint8_t b);
void updateStateInitStage1();
void updateStateInitStage2();
void updateStateOn();
void updateStateOff();
void updateStateCommissioningDevice();
void updateStateConnecting();
void updateStateOnLine();
void updateStateReady();
void updateStateBootPressed();

#endif