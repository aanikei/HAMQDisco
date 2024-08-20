#include <string>
#include <map>
#include <stdint.h>
#include <stdexcept>
#include "DiscoveryLight.h"

using namespace std;

DiscoveryLight::DiscoveryLight(string device, string shortName, string longName, std::vector<std::string> properties, std::map<string, string> config) : DiscoveryGenericControl(device, "light", shortName, longName, config) {
  for (const auto& prop : properties) {
    createTopics(prop);
  }
}

void DiscoveryLight::createTopics(const std::string& property) {
  if (property == "brightness") {
    json["bri_cmd_t"] = "~/brightness/set";
    json["bri_stat_t"] = "~/brightness/state";
  }
}

const char* DiscoveryLight::getBrightnessCommandTopic(int32_t i) {
  brightnessCommandTopic = baseTopic + uniqId;
  brightnessCommandTopic += (0 > i ? "/brightness/set" : to_string(i) + "/brightness/set");
  if (json.containsKey("bri_cmd_t")) {
    return brightnessCommandTopic.c_str();
  }
  
  throw std::runtime_error("Error: brightness is not configured");
}

const char* DiscoveryLight::getBrightnessStateTopic(int32_t i) {
  brightnessStateTopic = baseTopic + uniqId;
  brightnessStateTopic += (0 > i ? "/brightness/state" : to_string(i) + "/brightness/state");
  if (json.containsKey("bri_stat_t")) {
    return brightnessStateTopic.c_str();
  }
  
  throw std::runtime_error("Error: brightness is not configured");
}
