#include <HAMQDisco.h>

DiscoverySwitch switch1("DeviceName", "swt", "switch", {{"icon", "mdi:resistor"}}); //Device name should not contain spaces as they are not allowed in the discovery topic

void setup() {
  log_i("getDiscoveryMessage() %s", switch1.getDiscoveryMessage());
  // {
  //   "name":"DeviceName switch",
  //   "uniq_id":"DeviceName_swt",
  //   "icon":"mdi:resistor",
  //   "cmd_t":"~/set",
  //   "stat_t":"~/state",
  //   "retain":true,
  //   "~":"homeassistant/switch/DeviceName_swt"
  // }

  log_i("getDiscoveryMessage(1) %s", switch1.getDiscoveryMessage(1));
  // {
  //   "name":"DeviceName switch 1",
  //   "uniq_id":"DeviceName_swt1",
  //   "icon":"mdi:resistor",
  //   "cmd_t":"~/set",
  //   "stat_t":"~/state",
  //   "retain":true,
  //   "~":"homeassistant/switch/DeviceName_swt1"
  // }

  log_i("getDiscoveryMessage(2) %s", switch1.getDiscoveryMessage(2));
  // {
  //   "name":"DeviceName switch 2",
  //   "uniq_id":"DeviceName_swt2",
  //   "icon":"mdi:resistor",
  //   "cmd_t":"~/set",
  //   "stat_t":"~/state",
  //   "retain":true,
  //   "~":"homeassistant/switch/DeviceName_swt2"
  // }
  
  log_i("getConfigurationTopic() %s", switch1.getConfigurationTopic()); //homeassistant/switch/DeviceName_swt/config
  log_i("getConfigurationTopic(1) %s", switch1.getConfigurationTopic(1)); //homeassistant/switch/DeviceName_swt1/config
  log_i("getConfigurationTopic(2) %s", switch1.getConfigurationTopic(2)); //homeassistant/switch/DeviceName_swt2/config

  log_i("getStateTopic() %s", switch1.getStateTopic()); //homeassistant/switch/DeviceName_swt/state
  log_i("getStateTopic(1) %s", switch1.getStateTopic(1)); //homeassistant/switch/DeviceName_swt1/state
  log_i("getStateTopic(2) %s", switch1.getStateTopic(2)); //homeassistant/switch/DeviceName_swt2/state

  log_i("getCommandTopic() %s", switch1.getCommandTopic()); //homeassistant/switch/DeviceName_swt/set
  log_i("getCommandTopic(1) %s", switch1.getCommandTopic(1)); //homeassistant/switch/DeviceName_swt1/set
  log_i("getCommandTopic(2) %s", switch1.getCommandTopic(2)); //homeassistant/switch/DeviceName_swt2/set
}

void loop() {}
