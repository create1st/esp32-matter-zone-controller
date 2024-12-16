#include "hub.h"
#include <FunctionalInterrupt.h>

MatterOnOffLight matterButtons[MAX_ZONES];
Preferences lastStatePref[MAX_ZONES];
bool zoneStateChanged[MAX_ZONES];

bool hubReadyOn = false;
char fmtStrBuffer[20];

void IRAM_ATTR isr() {
}

void initHub() {
  for (int i = 0; i < MAX_ZONES; i++) {
    sprintf(fmtStrBuffer, "Zone%d", i);
    lastStatePref[i].begin(fmtStrBuffer, false);
    sprintf(fmtStrBuffer, "ZoneState%d", i);
    bool lastOnOffState = lastStatePref[i].getBool(fmtStrBuffer, true);
    matterButtons[i].begin(lastOnOffState);
    matterButtons[i].onChangeOnOff(std::bind(matterStateChanged, i, std::placeholders::_1));    
    zoneStateChanged[i] = false;
    attachInterrupt(getLedPin(i), std::bind(&hardwareStateChanged, i), CHANGE);    
  }
}

void discoverDevices() {
  Log.traceln("Waiting for Matter device discovery...");
  for (int i = 0; i < MAX_ZONES; i++) {
    bool state = getLedState(i);
    matterButtons[i].setOnOff(state);
    Log.traceln("Matter button set state %d = %s", i, state ? "ON" : "OFF");
  }
}

bool matterStateChanged(int zone, bool state) {
  Log.traceln("Matter state changed for zone %d = %s\r\n", zone, state ? "ON" : "OFF");
  // store last zone state
  sprintf(fmtStrBuffer, "ZoneState%d", zone);
  lastStatePref[zone].putBool(fmtStrBuffer, state);  
  bool currentState = getLedState(zone);
  if (currentState != state) {
    //setButtonState(zone, state);
    pushButton(zone);
    getLedState(zone);
  }
  // This callback must return the success state to Matter core
  return true;
}

void IRAM_ATTR hardwareStateChanged(int zone) {
  zoneStateChanged[zone] = true;
}

void hubLoop() {
  for (int i = 0; i < MAX_ZONES; i++) {
    if (zoneStateChanged[i]) {
      zoneStateChanged[i] = false;
      bool state = getLedState(i);
      Log.traceln("Hardware state changed for zone %d = %s\r\n", i, state ? "ON" : "OFF");
      matterButtons[i].setOnOff(state);
    }
  }
}
