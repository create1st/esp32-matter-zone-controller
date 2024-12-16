#include <ArduinoLog.h>
#include "logging.h"
#include "thread.h"
#include "hub.h"
#include "ledstate.h"
#include "buttonstate.h"
#include "status.h"

unsigned long statusTimer = 0;
bool readyOn = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_BUILTIN, INPUT_PULLUP);
  initStatusLed();
  
  updateStateOn();
  connectSerial();
  initilizeLedStateReader();
  initilizeButtonStateWriter();
  connectWiFi();
  initHub();
  initMatter();
  connectThreadNetwork();
  discoverDevices();
  updateStateInitStage1();
  updateStateInitStage2();  
  updateStateReady();
}

void loop() {  
  updateStateHandler();
  hubLoop();
  decommissionHandler();
}
