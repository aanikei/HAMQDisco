#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryLight.h"

using namespace std;

DiscoveryLight::DiscoveryLight(string device, string shortName, string longName, bool brightness, std::map<string, string> config) : DiscoveryGenericControl(device, "light", shortName, longName, config) {
  _brightness = brightness;
  if (_brightness) {
    json["bri_cmd_t"] = "~/brightness/set";
    json["bri_stat_t"] = "~/brightness/state";
  }
}

const char* DiscoveryLight::getBrightnessCommandTopic(int32_t i) {
  brightnessCommandTopic = baseTopic + uniqId;
  brightnessCommandTopic += (0 > i ? "/brightness/set" : to_string(i) + "/brightness/set");
  return _brightness ? (brightnessCommandTopic).c_str() : NULL;
}

const char* DiscoveryLight::getBrightnessStateTopic(int32_t i) {
  brightnessStateTopic = baseTopic + uniqId;
  brightnessStateTopic += (0 > i ? "/brightness/state" : to_string(i) + "/brightness/state");
  return _brightness ? (brightnessStateTopic).c_str() : NULL;
}
