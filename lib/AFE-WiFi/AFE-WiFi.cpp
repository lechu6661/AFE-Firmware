#include "AFE-Wifi.h"

AFEWiFi::AFEWiFi() {}

void AFEWiFi::begin(uint8_t mode) {

  AFEDataAccess Data;
  LED LEDConfiguration;

  LEDConfiguration = Data.getLEDConfiguration();
  networkConfiguration = Data.getNetworkConfiguration();

  // Init LED
  if (LEDConfiguration.present) {
    Led.begin(LEDConfiguration.gpio);
  }

  // Cleaning @TODO is it neded?
  Data = {};
  LEDConfiguration = {};

  WiFi.hostname(networkConfiguration.host);
  if (mode == MODE_ACCESS_POINT) {
    IPAddress apIP(192, 168, 5, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(networkConfiguration.host);
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(53, "www.example.com", apIP);
  } else {
    if (!networkConfiguration.isDHCP) {
      WiFi.config(networkConfiguration.ip, networkConfiguration.gateway,
                  networkConfiguration.subnet);
    }
    WiFi.mode(WIFI_STA);
  }
}

void AFEWiFi::connect() {

  if (sleepMode) {
    if (millis() - sleepStartTime >=
        networkConfiguration.waitTimeSeries * 1000) {
      sleepMode = false;
    }
  } else {
    uint8_t connections = 0;
    WiFi.begin(networkConfiguration.ssid, networkConfiguration.password);
    while (WiFi.status() != WL_CONNECTED) {
      Led.on();
      /*
            Serial << endl
                   << "INFO: WiFi connection attempt: " << connections + 1 << "
         from "
                   << networkConfiguration.noConnectionAttempts;
      */
      connections++;
      delay(networkConfiguration.waitTimeConnections * 500);
      Led.off();
      delay(networkConfiguration.waitTimeConnections * 500);
      if (connections == networkConfiguration.noConnectionAttempts) {
        sleepMode = true;
        WiFi.disconnect();
        sleepStartTime = millis();
        /*
                Serial << endl
                       << "WARN: Not able to connect.Going to sleep mode for "
                       << networkConfiguration.waitTimeSeries << "sec.";
        */
        break;
      }
    }
  }
}

boolean AFEWiFi::connected() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

void AFEWiFi::APListener() { dnsServer.processNextRequest(); }
