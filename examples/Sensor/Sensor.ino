#include <HAMQDisco.h>

DiscoverySensor sensor("DeviceName", "snsr", "sensor", {{"exp_aft", "4000"}});

void setup() {
  log_i("getDiscoveryMessage() %s", sensor.getDiscoveryMessage());
  // {
  //   "name":"DeviceName sensor",
  //   "uniq_id":"DeviceName_snsr",
  //   "exp_aft":"4000",
  //   "stat_t":"~/state",
  //   "~":"homeassistant/sensor/DeviceName_snsr"
  // }

  log_i("getDiscoveryMessage(1) %s", sensor.getDiscoveryMessage(1));
  // {
  //   "name":"DeviceName sensor 1",
  //   "uniq_id":"DeviceName_snsr1",
  //   "exp_aft":"4000",
  //   "stat_t":"~/state",
  //   "~":"homeassistant/sensor/DeviceName_snsr1"
  // }

  log_i("getDiscoveryMessage(1, 1) %s", sensor.getDiscoveryMessage(1, 1));
  // {
  //   "name":"DeviceName sensor 1 / 1",
  //   "uniq_id":"DeviceName_snsr1_1",
  //   "exp_aft":"4000",
  //   "stat_t":"~/state",
  //   "~":"homeassistant/sensor/DeviceName_snsr1_1"
  // }

  log_i("getConfigurationTopic() %s", sensor.getConfigurationTopic()); //homeassistant/sensor/DeviceName_snsr/config
  log_i("getConfigurationTopic(1) %s", sensor.getConfigurationTopic(1)); //homeassistant/sensor/DeviceName_snsr1/config
  log_i("getConfigurationTopic(1, 1) %s", sensor.getConfigurationTopic(1, 1)); //homeassistant/sensor/DeviceName_snsr1_1/config
  

  log_i("getStateTopic() %s", sensor.getStateTopic()); //homeassistant/sensor/DeviceName_snsr/state
  log_i("getStateTopic(1) %s", sensor.getStateTopic(1)); //homeassistant/sensor/DeviceName_snsr1/state
  log_i("getStateTopic(1, 1) %s", sensor.getStateTopic(1, 1)); //homeassistant/sensor/DeviceName_snsr1_1/state
}

void loop() {
  // put your main code here, to run repeatedly:

}
