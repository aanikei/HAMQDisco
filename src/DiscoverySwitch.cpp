#include <string>
#include <map>
#include <stdint.h>
#include "DiscoverySwitch.h"

using namespace std;

DiscoverySwitch::DiscoverySwitch(string device, string shortName, string longName, std::map<string, string> config) : DiscoveryGenericControl(device, "switch", shortName, longName, config) { }
