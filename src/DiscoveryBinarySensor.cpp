#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryBinarySensor.h"

using namespace std;

DiscoveryBinarySensor::DiscoveryBinarySensor(string device, string shortName, string longName, std::map<string, string> config) : DiscoveryGenericSensor(device, "binary_sensor", shortName, longName, config) { }
