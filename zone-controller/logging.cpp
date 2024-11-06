#include "logging.h"

// #define DISABLE_LOGGING 

void connectSerial() {
  Serial.begin(115200);
  unsigned long startTime = millis();  // Record the current time
  while (millis() - startTime < 10000 && !Serial) {
    // Wait for serial input or timeout
  }
  int logLevel = Serial ? LOG_LEVEL_VERBOSE : LOG_LEVEL_SILENT;
  Log.begin(logLevel, &Serial, true);
  if (!Serial) {
    Serial.end();
  }
}