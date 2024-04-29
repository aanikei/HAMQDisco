#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryGenericSensor.h"

class DiscoverySensor : public DiscoveryGenericSensor {
  public:
    DiscoverySensor(std::string device, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
};
