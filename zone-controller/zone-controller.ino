#include <Hashtable.h>

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

  updateStateOn();
  connectSerial();
  connectWiFi();
  initHub();
  initMatter();
  connectThreadNetwork();
  discoverDevices();
  updateStateInitStage1();
  initilizeLedStateReader();
  updateStateInitStage2();
  initilizeButtonStateWriter();  
  updateStateReady();
}

void loop() {  
  unsigned long current = millis();
  if (current - statusTimer >= 2000) {
    readyOn = !readyOn;
    statusTimer = current;
    if (readyOn) {
      updateStateReady();
    } else {
      updateStateOff();
    }
  }
  hubLoop();
  decommissionHandler();
}
