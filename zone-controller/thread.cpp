#include "thread.h"
#include "reset.h"

bool threadReadyOn = false;
bool threadDecomminsionPressed = false;
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void initMatter() {
  Matter.begin();
}

void connectThreadNetwork() {
  if (!Matter.isDeviceCommissioned()) {
    Log.traceln("Matter device is not commissioned");
    Log.traceln("Commission it to your Matter hub with the manual pairing code or QR code");
    Log.traceln("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Log.traceln("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  } else {
    Log.traceln("Matter device is commissioned");
  }
  while (!Matter.isDeviceCommissioned()) {
    if (threadReadyOn) {
      updateStateOff();
    } else {
      updateStateCommissioningDevice();
    }
    threadReadyOn = !threadReadyOn;
    delay(connectionWaitTime);    
    decommissionHandler();
  }
  updateStateConnecting();
  //Log.traceln("Waiting for Thread network...");
  //while (!Matter.isDeviceThreadConnected()) {
  //  if (threadReadyOn) {
  //    updateStateOff();
  //  } else {
  //    updateStateConnecting();
  // }
  //  threadReadyOn = !threadReadyOn;
  //  delay(connectionWaitTime);    
  //  decommissionHandler();    
  //}
  //Log.traceln("Connected to Thread network");
}

void connectWiFi() {
  //String fv = WiFi.firmwareVersion();
  //if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
  //  Log.traceln("Please upgrade the firmware");
  //}
  //Log.traceln("WiFi firmware version: %s", fv.c_str());
  WiFi.begin(ssid, pass);
  while (status != WL_CONNECTED) {
    Log.traceln("Connecting to WiFi: %s", ssid);
    status = WiFi.status();
    if (status == WL_CONNECTED) break;
    if (threadReadyOn) {
      updateStateOff();
    } else {
      updateStateConnecting();
    }
    threadReadyOn = !threadReadyOn;
    delay(connectionWaitTime);    
    decommissionHandler(); 
  }
  Log.traceln("Connected");
}

void showNetworkConnectionDetails() {
  Log.traceln("Board Information:");
  IPAddress ip = WiFi.localIP();
  Log.traceln("IP Address: %p", ip);
  Log.traceln("Network Information:");
  Log.traceln("SSID: %s", WiFi.SSID());
  long rssi = WiFi.RSSI();
  Log.traceln("signal strength (RSSI): %d dBm", rssi);
//  byte encryption = WiFi.encryptionType();
//  Log.traceln("Encryption Type: %X", encryption);
  byte mac[6];
  WiFi.macAddress(mac);
  String macString = macToString(mac);
  Log.traceln("MAC: %s", macString.c_str());
}

String macToString(byte mac[]) {
  String macString = "";
  char buffer[3];
  for (int i = 5; i >= 0; i--) {
    sprintf(buffer, "%02X", mac[i]);
    macString += buffer;
    if (i > 0) {
      macString += ":";
    }
  }
  return macString;
}

void decommissionHandler() {
  if (digitalRead(BTN_BUILTIN) == LOW) {  //Push button pressed
    // measures time pressed
    int startTime = millis();
    while (digitalRead(BTN_BUILTIN) == LOW) {
      //delay(50);

      int elapsedTime = (millis() - startTime) / 1000.0;

      if (elapsedTime > 10) {
        Log.traceln("Decommissioning!");
        for (int i = 0; i < 10; i++) {
          if (threadDecomminsionPressed) {
            updateStateBootPressed();
          } else {
            updateStateOff();
          }
          threadDecomminsionPressed = !threadDecomminsionPressed;
          delay(connectionWaitTime);
        };

        if (!Matter.isDeviceCommissioned()) {
          Log.traceln("Decommission done!");
          updateStateOff();
        } else {
          Log.traceln("Matter device is commissioned-> Starting Decommission process");
          updateStateOff();
          Matter.decommission();          
          Log.traceln("Decommission done!");
          ESP.restart();
        }
        break;
      }
    }
  }
}

