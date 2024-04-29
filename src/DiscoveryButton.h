#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryBase.h"

class DiscoveryButton : public DiscoveryBase {
  public:
    DiscoveryButton(std::string device, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
    const char* getCommandTopic(int32_t i = -1);
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
  private:
    std::string commandTopic;
};
