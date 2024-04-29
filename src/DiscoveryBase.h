#pragma once
#include <ArduinoJson.h>
#include <string>
#include <map>
#include <stdint.h>

class DiscoveryBase {
  public:
    DiscoveryBase(std::string device, std::string shortName, std::string longName, std::map<std::string, std::string> config);
    const char* getDiscoveryMessage(int32_t i = -1);
    const char* getConfigurationTopic(int32_t i = -1);
    const char* getShortName();
  protected:
    void setConfig(std::map<std::string, std::string> config);
    std::string baseTopic;
    std::string configTopic;
    std::string uniqId;
    std::string message;
    std::string _device;
    std::string _longName;
    std::string _shortName;
    JsonDocument json;    
};
