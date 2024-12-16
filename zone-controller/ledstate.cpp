#include "ledstate.h"

int ledReadStatePins[MAX_ZONES] = {
  D3,
  D4,
  D5,
  D6,
};

void initilizeLedStateReader() {
  Log.traceln("Initializing LED state reader");
  for (int i = 0; i < MAX_ZONES; i++) {
    pinMode(ledReadStatePins[i], INPUT_PULLUP);
  }
  Log.traceln("Initializing LED state reader completed");
}

bool getLedState(int zone) {
  bool state = !digitalRead(ledReadStatePins[zone]);
  Log.traceln("LED %d = %t", zone, state);
  return state;
}

int getLedPin(int zone) {
  return ledReadStatePins[zone];
}
