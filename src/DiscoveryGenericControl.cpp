#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryGenericControl.h"

using namespace std;

DiscoveryGenericControl::DiscoveryGenericControl(string device, string entity, string shortName, string longName, std::map<string, string> config) : DiscoveryBase(device, shortName, longName, config) {
  baseTopic += entity + "/";
  json["cmd_t"] = "~/set";
  json["stat_t"] = "~/state";
  json["retain"] = true;
}

const char* DiscoveryGenericControl::getCommandTopic(int32_t i) {
  commandTopic = baseTopic + uniqId;
  commandTopic += (0 > i ? "/set" : to_string(i) + "/set");
  return commandTopic.c_str();
}

const char* DiscoveryGenericControl::getStateTopic(int32_t i) {
  stateTopic = baseTopic + uniqId;
  stateTopic += (0 > i ? "/state" : to_string(i) + "/state");
  return stateTopic.c_str();
}
