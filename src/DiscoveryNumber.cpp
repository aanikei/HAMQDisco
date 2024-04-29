#include <string>
#include <map>
#include <stdint.h>
#include "DiscoveryNumber.h"

using namespace std;

DiscoveryNumber::DiscoveryNumber(string device, string shortName, string longName, std::map<string, string> config) : DiscoveryGenericControl(device, "number", shortName, longName, config) { }
