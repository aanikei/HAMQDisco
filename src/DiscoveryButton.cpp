#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryButton.h"

using namespace std;

DiscoveryButton::DiscoveryButton(string device, string shortName, string longName, std::map<string, string> config) : DiscoveryBase(device, shortName, longName, config) {
  baseTopic += "button/";
  json["cmd_t"] = "~/set";
  json["qos"] = 1;
}

const char* DiscoveryButton::getCommandTopic(int32_t i) {
  commandTopic = baseTopic + uniqId;
  commandTopic += (0 > i ? "/set" : to_string(i) + "/set");
  return commandTopic.c_str();
}
