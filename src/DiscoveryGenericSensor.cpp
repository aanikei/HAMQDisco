#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryGenericSensor.h"

using namespace std;

DiscoveryGenericSensor::DiscoveryGenericSensor(string device, string entity, string shortName, string longName, std::map<string, string> config) : DiscoveryBase(device, shortName, longName, config) {
  baseTopic += entity + "/";
  json["stat_t"] = "~/state";
}

const char* DiscoveryGenericSensor::getStateTopic(int32_t i) {
  stateTopic = baseTopic + uniqId;
  stateTopic += (0 > i ? "/state" : to_string(i) + "/state");
  return stateTopic.c_str();
}

const char* DiscoveryGenericSensor::getDiscoveryMessage(int32_t i, int32_t j) {
  json["uniq_id"] = uniqId + to_string(i) + "_" + to_string(j);
  json["name"] = _device + " " + _longName + " " + to_string(i) + " / " + to_string(j);
  json["~"] = baseTopic + uniqId + to_string(i) + "_" + to_string(j);

  message = json.as<std::string>();
  return message.c_str();
}

const char* DiscoveryGenericSensor::getConfigurationTopic(int32_t i, int32_t j) {
  configTopic = baseTopic + uniqId;
  configTopic += to_string(i) + "_" + to_string(j) + "/config";
  return configTopic.c_str();
}

const char* DiscoveryGenericSensor::getStateTopic(int32_t i, int32_t j) {
  stateTopic = baseTopic + uniqId;
  stateTopic += to_string(i) + "_" + to_string(j) + "/state";
  return stateTopic.c_str();
}
