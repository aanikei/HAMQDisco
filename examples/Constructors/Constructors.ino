#include <HAMQDisco.h>

// The constructor of all objects has mandatory arguments: device name, short name (used for unique_id generation), 
// and full name. The last argument is a map that is initialized with pairs of key-value that represent configuration variables
DiscoveryBinarySensor binarySensor("DeviceName", "bs", "binary sensor");
DiscoveryBinarySensor binarySensor1("DeviceName", "bs", "binary sensor", {{"device_class", "door"}, {"exp_aft", "4000"}});

DiscoveryButton button("DeviceName", "btn", "button");
DiscoveryButton button1("DeviceName", "btn", "button", {{"dev_cla", "restart"}, {"ent_cat", "config"}});

DiscoveryLight light0("DeviceName", "light", "light", true); //true adds brightness control, it's the only additional control that's currently available for light
DiscoveryLight light1("DeviceName", "light", "light", false); //without brightness control
DiscoveryLight light2("DeviceName", "light", "light"); //false is default argument and can be omitted
DiscoveryLight light3("DeviceName", "light", "light", true, {}); //not using configuration variables for light
DiscoveryLight light4("DeviceName", "light", "light", false, {});

DiscoveryNumber number("DeviceName", "nmb", "number");
DiscoveryNumber number1("DeviceName", "nmb", "number", {{"mode", "slider"}, {"min", "0",}, {"max", "30"}, {"step", "2",}, {"icon", "mdi:volume-plus"}});

std::vector<std::string> options = {"Option 1", "Option 2"};
DiscoverySelect select1("DeviceName", "slct", "select", options);
DiscoverySelect select2("DeviceName", "slct", "select", options, {});

DiscoverySensor sensor("DeviceName", "snsr", "sensor");
DiscoverySensor sensor1("DeviceName", "snsr", "sensor", {{"unit_of_meas", "°C"}, {"dev_cla", "temperature"}, {"val_tpl", "{{ value | round(1) }}"}, {"exp_aft", "4000"}});

DiscoverySwitch switch1("DeviceName", "swt", "switch");
DiscoverySwitch switch2("DeviceName", "swt", "switch", {{"icon", "mdi:resistor"}});

void setup() { }

void loop() { }
