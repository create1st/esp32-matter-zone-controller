#include "buttonstate.h"

int buttonWriteStatePins[MAX_ZONES] = {
  D7,
  D8,
  D9,
  D10,
};

void initilizeButtonStateWriter() {
  Log.traceln("Initializing Button state writer");
  for (int i = 0; i < MAX_ZONES; i++) {
    pinMode(buttonWriteStatePins[i], OUTPUT); 
  }
  Log.traceln("Initializing Button state writer completed");
}

void setButtonState(int zone, bool state) {
  digitalWrite(buttonWriteStatePins[zone], state ? HIGH : LOW);

  Log.traceln("Button set to %d = %t", zone, state);
}

void pushButton(int zone) {
  digitalWrite(buttonWriteStatePins[zone], HIGH);
  delay(pushButtonDelay);
  digitalWrite(buttonWriteStatePins[zone], LOW);
  
  Log.traceln("Button pushed to %d", zone);
}

