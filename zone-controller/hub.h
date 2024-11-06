#include <ArduinoLog.h>
#include <MatterOnOffLight.h>
#include <Preferences.h>
#include "ledstate.h"
#include "buttonstate.h"
#include "zonestate.h"
#include "thread.h"
#include "status.h"

#ifndef HUB_H_
#define HUB_H_

void initHub();
void discoverDevices();
void hubLoop();
bool setLightOnOff(bool state);

#endif