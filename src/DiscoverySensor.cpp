#include <string>
#include <map>
#include <stdint.h>
#include "DiscoverySensor.h"

using namespace std;

DiscoverySensor::DiscoverySensor(string device, string shortName, string longName, std::map<string, string> config) : DiscoveryGenericSensor(device, "sensor", shortName, longName, config) { }
