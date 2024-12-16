#include <ArduinoLog.h>
#include <Matter.h>
#include <WiFi.h>
#include "status.h"
#include "credentials.h"

// Set up the onboard button
#ifndef BTN_BUILTIN
#define BTN_BUILTIN D0
#endif

#ifndef THREAD_H_
#define THREAD_H_
const int connectionWaitTime = 200; // msec

void initMatter();
void connectThreadNetwork();
void decommissionHandler();
void connectWiFi();
void showNetworkConnectionDetails();
String macToString(byte mac[]);

#endif