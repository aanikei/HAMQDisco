#pragma once
#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryGenericSensor.h"

class DiscoveryBinarySensor : public DiscoveryGenericSensor {
  public:
    DiscoveryBinarySensor(std::string device, std::string shortName, std::string longName, std::map<std::string, std::string> config = {});
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
};
