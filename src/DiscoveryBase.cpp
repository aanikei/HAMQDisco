#include <ArduinoJson.h>
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryBase.h"

using namespace std;

DiscoveryBase::DiscoveryBase(string device, string shortName, string longName, std::map<string, string> config) {
  baseTopic = "homeassistant/";
  _device = device;
  _shortName = shortName;
  _longName = longName;
  uniqId = _device + "_" + _shortName;
  json["name"] = _device + " " + _longName;
  json["uniq_id"] = uniqId;
  this->setConfig(config);
};

const char* DiscoveryBase::getDiscoveryMessage(int32_t i) {
  if (0 > i) {
    json["~"] = baseTopic + uniqId;
  } else {
    json["uniq_id"] = uniqId + to_string(i);
    json["name"] = _device + " " + _longName + " " + to_string(i);
    json["~"] = baseTopic + uniqId + to_string(i);
  }

  message = json.as<std::string>();
  return message.c_str();
}

const char* DiscoveryBase::getConfigurationTopic(int32_t i) {
  /*if (0 > i) {
    configTopic = baseTopic + uniqId + "/config";
  } else {
    configTopic = baseTopic + uniqId + to_string(i) + "/config";
  }*/
  configTopic = baseTopic + uniqId;
  configTopic += (0 > i ? "/config" : to_string(i) + "/config");
  return configTopic.c_str();
}

const char* DiscoveryBase::getShortName() {
  return _shortName.c_str();
}

void DiscoveryBase::setConfig(std::map<string, string> config) {
  for (auto const& [key, val] : config) {
    json[key] = val;
  }
}
