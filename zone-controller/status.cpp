#include "status.h"

void updateLedColor(uint8_t r, uint8_t g, uint8_t b) {
  rgbLedWriteOrdered(RGB_BUILTIN, LED_COLOR_ORDER_RGB, r, g, b);  
}

void updateStateOn() {
  updateLedColor(255, 255, 255);
}

void updateStateInitStage1() {
  updateLedColor(255, 255, 255);
}

void updateStateInitStage2() {
  updateLedColor(127, 127, 127);
}

void updateStateOff() {
  updateLedColor(0, 0, 0);
}

void updateStateCommissioningDevice() {
  updateLedColor(0, 191, 255);
}

void updateStateConnecting() {
  updateLedColor(254, 138, 24);
}

void updateStateOnLine() {
  updateLedColor(255, 255, 0);
}

void updateStateReady() {
  updateLedColor(0, 100, 0);
}

void updateStateBootPressed() {
  updateLedColor(255, 128, 0);
}