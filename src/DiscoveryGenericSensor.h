#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryBase.h"

class DiscoveryGenericSensor : public DiscoveryBase {
  public:
    DiscoveryGenericSensor(std::string device, std::string entity, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage; //needed to force the compiler to consider parent's methods as they are overloaded
	using DiscoveryBase::getConfigurationTopic;
    const char* getStateTopic(int32_t i = -1);
    const char* getDiscoveryMessage(int32_t i, int32_t j);
    const char* getConfigurationTopic(int32_t i, int32_t j);
    const char* getStateTopic(int32_t i, int32_t j);
  private:
    std::string stateTopic;
};
