#include "hub.h"

MatterOnOffLight matterButtons[MAX_ZONES];
Preferences lastStatePref[MAX_ZONES];
ZoneState lastZoneState;

bool hubReadyOn = false;
char fmtStrBuffer[20];

void initHub() {
  for (int i = 0; i < MAX_ZONES; i++) {
    sprintf(fmtStrBuffer, "Zone%d", i);
    lastStatePref[i].begin(fmtStrBuffer, false);
    sprintf(fmtStrBuffer, "ZoneState%d", i);
    bool lastOnOffState = lastStatePref[i].getBool(fmtStrBuffer, true);
//    matterButtons[i].begin();
    matterButtons[i].begin(lastOnOffState);
    matterButtons[i].onChangeOnOff(setLightOnOff);
  }
}

void discoverDevices() {
  Log.traceln("Waiting for Matter device discovery...");
  //for (int i = 0; i < MAX_ZONES; i++) {
  //  Log.traceln("Waiting for Matter device discovery: %d", i);
  //  while (!matterButtons[i].is_online()) {      
  //    if (hubReadyOn) {
  //      updateStateOff();
  //    } else {
  //      updateStateOnLine();
  //    }
  //    hubReadyOn = !hubReadyOn;
  //    delay(connectionWaitTime);      
  //    decommissionHandler();
  //  }
  //}
  Log.traceln("Matter device is now online");
  ZoneState zoneState = getLedState();
  for (int i = 0; i < MAX_ZONES; i++) {
    matterButtons[i].setOnOff(zoneState.enabled[i]);
    lastZoneState.enabled[i] = zoneState.enabled[i];
    Log.traceln("Matter button set state %d = %t", i, zoneState.enabled[i]);
  }
}

bool setLightOnOff(bool state) {
  Log.traceln("User Callback :: New Light State = %s\r\n", state ? "ON" : "OFF");
//  if (state) {
//    digitalWrite(ledPin, HIGH);
//  } else {
//    digitalWrite(ledPin, LOW);
//  }
  // store last OnOff state for when the Light is restarted / power goes off
  //lastStatePref.putBool("lastOnOffState", state);
  // This callback must return the success state to Matter core
  return true;
}

void hubLoop() {
  ZoneState zoneState = getLedState();
  ZoneState buttonState;
  for (int i = 0; i < MAX_ZONES; i++) {
    buttonState.enabled[i] = lastZoneState.enabled[i] != matterButtons[i].getOnOff(); // UI state changed, press the real button
    if (zoneState.enabled[i] != lastZoneState.enabled[i] && !buttonState.enabled[i]) {
      Log.traceln("LED state changed %d = %t", i, zoneState.enabled[i]);
      matterButtons[i].setOnOff(zoneState.enabled[i]);
      sprintf(fmtStrBuffer, "ZoneState%d", i);    
      lastStatePref[i].putBool(fmtStrBuffer, zoneState.enabled[i]);
    }
    lastZoneState.enabled[i] = zoneState.enabled[i];
  }
  setButtonState(buttonState);
}
