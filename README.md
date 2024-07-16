### About HAMQDisco

This library enables creation of MQTT entities in Home Assistant using [MQTT discovery feature](https://www.home-assistant.io/integrations/mqtt/#mqtt-discovery). The library allows the generation of discovery payloads and configuration, state, and command topics.
As the purpose of the library is mostly the creation of repetitive entities (button 1, button 2, etc.), it’s sufficient to create one object and then use a positive integer as a method argument to get entities with the corresponding number in their name, e.g.:
```
DiscoverySwitch switch1("Device Name", "swt", "switch", {{"icon", "mdi:resistor"}});
switch1.getDiscoveryMessage(); // ... "name":"DeviceName switch"
switch1.getDiscoveryMessage(1); // ... "name":"DeviceName switch 1"
switch1.getConfigurationTopic();
switch1.getConfigurationTopic(1);
switch1.getStateTopic();
switch1.getStateTopic(1);
switch1.getCommandTopic();
switch1.getCommandTopic(1);
```
For sensor entities, an additional level of numbers in the name can be used:
```
DiscoverySensor sensor("DeviceName", "snsr", "sensor", {{"exp_aft", "4000"}});
sensor.getDiscoveryMessage(1, 1); // ... "name":"DeviceName sensor 1 / 1"
sensor.getConfigurationTopic(1, 1);
sensor.getStateTopic(1, 1);
```

Check examples for further details. Note that only limited number of configuration variables is supported as well as limited testing was done.

Next controls are currently supported:
- Binary Sensor
- Button
- Light
- Number
- Select
- Sensor
- Switch

### How to use

To use it with Arduino IDE, download the archive (Code / Download ZIP), unzip it and put it in `libraries` folder.