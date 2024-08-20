#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "DiscoveryGenericControl.h"

class DiscoveryLight : public DiscoveryGenericControl {
  public:
    DiscoveryLight(std::string device, std::string shortName, std::string longName, const std::vector<std::string> properties = {}, const std::map<std::string, std::string> config = {}); //https://stackoverflow.com/questions/4128776/how-to-pass-stdmap-as-a-default-constructor-parameter
	using DiscoveryBase::getDiscoveryMessage;
	using DiscoveryBase::getConfigurationTopic;
    const char* getBrightnessCommandTopic(int32_t i = -1);
    const char* getBrightnessStateTopic(int32_t i = -1);
  private:
    void createTopics(const std::string& property);
    std::string brightnessCommandTopic;
    std::string brightnessStateTopic;
};
