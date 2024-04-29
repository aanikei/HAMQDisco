#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryBase.h"

class DiscoveryGenericControl : public DiscoveryBase {
  public:
    DiscoveryGenericControl(std::string device, std::string entity, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
    const char* getCommandTopic(int32_t i = -1);
    const char* getStateTopic(int32_t i = -1);
  private:
    std::string stateTopic;
    std::string commandTopic;
};
