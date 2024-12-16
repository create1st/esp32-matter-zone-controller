#include "status.h"

hw_timer_t *ledTimer = NULL;
volatile uint8_t ledr = 0;
volatile uint8_t ledg = 0;
volatile uint8_t ledb = 0;
volatile uint8_t prevLedr = 0;
volatile uint8_t prevLedg = 0;
volatile uint8_t prevLedb = 0;
volatile bool ledOn = false;
volatile bool lastLedOnState = false;

void ARDUINO_ISR_ATTR onTimer() {
  ledOn = !ledOn;
}

void initStatusLed() {
  // Set timer frequency to 1Mhz
  ledTimer = timerBegin(1000000);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(ledTimer, &onTimer);
  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
  timerAlarm(ledTimer, 1000000, true, 0);
}

void updateStateHandler() {
  if (lastLedOnState != ledOn) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    if (ledOn) {
      r = ledr;
      g = ledg;
      b = ledb;
    }
    digitalWrite(LED_BUILTIN, r > 0 || b > 0 || g > 0 ? HIGH : LOW);
    // rgbLedWriteOrdered(RGB_BUILTIN, LED_COLOR_ORDER_RGB, r, g, b);
    lastLedOnState = ledOn;
  }
}

void updateLedColor(uint8_t r, uint8_t g, uint8_t b) {
  //rgbLedWriteOrdered(RGB_BUILTIN, LED_COLOR_ORDER_RGB, r, g, b);
  digitalWrite(LED_BUILTIN, r > 0 || b > 0 || g > 0 ? HIGH : LOW);
  ledr = r;
  ledg = g;
  ledb = b;
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
  prevLedr = ledr;
  prevLedg = ledg;
  prevLedb = ledb;
  updateLedColor(255, 128, 0);
}

void updateStateBootReleased() {
  updateLedColor(prevLedr, prevLedg, prevLedb);
}