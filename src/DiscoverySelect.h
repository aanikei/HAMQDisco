#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "DiscoveryGenericControl.h"

class DiscoverySelect : public DiscoveryGenericControl {
  public:
    DiscoverySelect(std::string device, std::string shortName, std::string longName, std::vector<std::string> options, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
};
