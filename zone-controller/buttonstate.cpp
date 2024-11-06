#include "buttonstate.h"

int buttonWriteStatePins[MAX_ZONES] = {
  // A0, // D14
  // A1, // D15
  14, //EX2-5
  14,
  14,
  14,
};

void initilizeButtonStateWriter() {
  Log.traceln("Initializing Button state writer");
  for (int i = 0; i < MAX_ZONES; i++) {
    pinMode(buttonWriteStatePins[i], OUTPUT); 
  }
  Log.traceln("Initializing Button state writer completed");
}

void setButtonState(ZoneState zoneState) {
  // Log.traceln("Set Button state");
  for (int i = 0; i < MAX_ZONES; i++) {
    if (zoneState.enabled[i]) {
      digitalWrite(buttonWriteStatePins[i], zoneState.enabled[i] ? HIGH : LOW);
      delay(pushButtonDelay);
      digitalWrite(buttonWriteStatePins[i], LOW);
      Log.traceln("Button set to %d = %t", i, zoneState.enabled[i]);
    }
  }
  // Log.traceln("Set button state completed");
}
