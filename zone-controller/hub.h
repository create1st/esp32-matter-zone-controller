#include <ArduinoLog.h>
#include <Matter.h>
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
bool matterStateChanged(int zone, bool state);
void IRAM_ATTR hardwareStateChanged(int zone);

#endif