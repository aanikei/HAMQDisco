#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryGenericControl.h"

class DiscoverySwitch : public DiscoveryGenericControl {
  public:
    DiscoverySwitch(std::string device, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
};
