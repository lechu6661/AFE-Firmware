#include "AFE-Configuration-Panel.h"

AFEConfigurationPanel::AFEConfigurationPanel() {}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      boolean data) {

  Serial << endl << "INFO: Generating site";

  String page = Site.generateHeader();

  if (option == "upgrade") {
    page += Site.addUpgradeSection();
  } else if (option == "reset") {
    page += Site.addResetSection();
  } else if (option == "exit") {
    page += Site.addExitSection();
  } else {
    page += "<h1>Page Not Found</h1>";
  }
  page += Site.generateFooter();

  Serial << endl << "INFO: Site generated";
  return page;
}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      NETWORK data) {

  Serial << endl << "INFO: Generating Network configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=basic&command=1\"  method=\"post\">";
  page += Site.addNetworkConfiguration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

/* @TODO Only for MQTT */
String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      MQTT data) {

  Serial << endl << "INFO: Generating MQTT configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=mqtt&command=1\"  method=\"post\">";
  page += Site.addMQTTBrokerConfiguration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

/* @TODO Only for Domoticz */
String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      DOMOTICZ data) {

  Serial << endl << "INFO: Generating Domoticz configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=domoticz&command=1\"  method=\"post\">";
  page += Site.addDomoticzConfiguration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      RELAY data) {

  Serial << endl << "INFO: Generating Relay configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(0, data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=relay&command=1\"  method=\"post\">";
  page += Site.addRelayConfiguration(1);
  page += Site.addRelayConfiguration(2);
  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      SWITCH data) {

  Serial << endl << "INFO: Generating Switch configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(0, data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=switch&command=1\"  method=\"post\">";

  page += Site.addSwitchConfiguration(1);
  page += Site.addSwitchConfiguration(2);

  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}

String AFEConfigurationPanel::getSite(const String option, uint8_t command,
                                      DS18B20 data) {

  Serial << endl << "INFO: Generating DS18B20 configuration site";

  if (command == SERVER_CMD_SAVE) {
    AFEDataAccess save;
    save.saveConfiguration(data);
  }

  String page = Site.generateHeader();
  page += "<form action=\"/?option=ds18b20&command=1\"  method=\"post\">";
  page += Site.addDS18B20Configuration();
  page += "<input type=\"submit\" class=\"b bs\" value=\"Zapisz\">";
  page += "</form>";
  page += Site.generateFooter();
  return page;
}
