#include <string>
#include <map>
#include <vector>
#include <stdint.h>
#include "DiscoverySelect.h"

using namespace std;

DiscoverySelect::DiscoverySelect(string device, string shortName, string longName, std::vector<string> options, std::map<string, string> config) : DiscoveryGenericControl(device, "select", shortName, longName, config) {
  JsonArray array = json.createNestedArray("options");
  for (const string& i : options) {
    array.add(i);
  }
}
