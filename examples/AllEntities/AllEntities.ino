#include <HAMQDisco.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <regex>

const std::string device_name = "TEST";
int32_t sleep_time = 5; //seconds
int32_t counter = 0; //will go to sleep after 10 iterations
const uint64_t uS_TO_S_FACTOR = 1000000ULL; //conversion factor for microseconds to seconds

char* ssid = "YourSSID"; //WIFI ssid
char* password = "YourPassword"; //WIFI password

char* mqtt_server = "192.168.1.1"; //mqtt broker IP
char* mqtt_user = "MqttUser";
char* mqtt_pass = "MqttPassword";

RTC_DATA_ATTR bool mqttDiscovery = true; //as discovery message is retained, no need to send it every time

std::map<std::string, int32_t> mp; //variable to store states of entities
std::map<std::string, bool> mpb; //variable to store states of entities

DiscoveryBinarySensor binarySensor(device_name, "bs", "binary sensor", {{"device_class", "door"}, {"exp_aft", "4000"}});
int32_t bs_num = 1; //number for demonstration of entity numbering

DiscoveryButton button(device_name, "btn", "button"); //, {{"dev_cla", "restart"}, {"ent_cat", "config"}}
int32_t button_num = 2;

DiscoveryLight light0(device_name, "lightA", "light0", true); //with brightness control
int32_t light0_num = 3;

DiscoveryLight light1(device_name, "lightB", "light1"); //without brightness control
int32_t light1_num = 4;

DiscoveryNumber number(device_name, "nmb", "number", {{"mode", "slider"}, {"min", "0",}, {"max", "30"}, {"icon", "mdi:volume-plus"}});
int32_t number_num = 5;

std::vector<std::string> options = {"Option 1", "Option 2"};
DiscoverySelect select1(device_name, "slct", "select", options);
int32_t select_num = 6;

DiscoverySensor sensor(device_name, "snsr", "sensor", {{"exp_aft", "4000"}});
int32_t sensor_num = 7;

DiscoverySwitch switch1(device_name, "swt", "switch", {{"icon", "mdi:resistor"}});
int32_t switch_num = 8;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  std::srand(std::time(nullptr));
  // The initial state of entities is set only on the first power on. The values in mp & mpb variables will be lost after deep sleep,
  // but as the checkMQTT() function is called first, it will populate them and then publish them again. Of course, you can
  // use RTC_DATA_ATTR & RTC_NOINIT_ATTR, which enable preserving values during deep sleep, as well as saving values in flash memory
  if (esp_reset_reason() != ESP_RST_DEEPSLEEP) {
    mpb["binary sensor"] = true;
    mpb["binary sensor" + std::to_string(bs_num)] = false;

    mpb["switch"] = false;
    mpb["switch" + std::to_string(switch_num)] = true;

    mpb["lightA"] = false;
    mpb["lightA" + std::to_string(light0_num)] = true;

    mpb["lightB"] = false;
    mpb["lightB" + std::to_string(light1_num)] = true;

    mp["lightAbrt"] = 1;
    mp["lightAbrt" + std::to_string(light0_num)] = 250;

    mp["number"] = 0;
    mp["number" + std::to_string(number_num)] = 0;

    mp["select"] = 0;
    mp["select" + std::to_string(select_num)] = 1;
  }

  esp_sleep_enable_timer_wakeup(sleep_time * uS_TO_S_FACTOR);

  if(connectToWifi()) {
    connectToMQTT();
  }
}

void loop() {
  if (client.connected()) {
    log_i("Free heap %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    checkMQTT(client);

    client.publish(binarySensor.getStateTopic(), mpb["binary sensor"] ? "ON" : "OFF"); //std::to_string(bs ?).c_str()
    client.publish(binarySensor.getStateTopic(bs_num), mpb["binary sensor" + std::to_string(bs_num)] ? "ON" : "OFF");
    mpb["binary sensor"] = !mpb["binary sensor"];
    mpb["binary sensor" + std::to_string(bs_num)] = !mpb["binary sensor" + std::to_string(bs_num)];

    client.publish(light0.getStateTopic(), mpb["lightA"] ? "ON" : "OFF");
    client.publish(light0.getBrightnessStateTopic(), std::to_string(mp["lightAbrt"]).c_str());
    client.publish(light0.getStateTopic(light0_num), mpb["lightA" + std::to_string(light0_num)] ? "ON" : "OFF");
    client.publish(light0.getBrightnessStateTopic(light0_num), std::to_string(mp["lightAbrt" + std::to_string(light0_num)]).c_str());

    client.publish(light1.getStateTopic(), mpb["lightB"] ? "ON" : "OFF");
    client.publish(light1.getStateTopic(light1_num), mpb["lightB" + std::to_string(light1_num)] ? "ON" : "OFF");

    client.publish(number.getStateTopic(), std::to_string(mp["number"]).c_str());
    client.publish(number.getStateTopic(number_num), std::to_string(mp["number" + std::to_string(number_num)]).c_str());

    client.publish(select1.getStateTopic(), options[mp["select"]].c_str());
    client.publish(select1.getStateTopic(select_num), options[mp["select" + std::to_string(select_num)]].c_str());

    client.publish(sensor.getStateTopic(), mpb["binary sensor"] ? "ON" : "OFF"); //using value of mpb["binary sensor"]
    client.publish(sensor.getStateTopic(sensor_num), std::to_string(std::rand()).c_str());
    client.publish(sensor.getStateTopic(sensor_num, 1), std::to_string(std::rand()).c_str());

    client.publish(switch1.getStateTopic(), mpb["switch"] ? "ON" : "OFF");
    client.publish(switch1.getStateTopic(switch_num), mpb["switch" + std::to_string(switch_num)] ? "ON" : "OFF");

    counter++;
    if (10 == counter) {
      sleep();
    }
  } else {
    sleep();
  }
}

void sleep() {
  if (client.connected()) {
    checkMQTT(client);
  }

  WiFi.disconnect();
  
  log_i("Going to sleep");
  esp_deep_sleep_start();
}

void connectToMQTT() {
  client.setBufferSize(512);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.setKeepAlive(1200);

  for (int32_t i = 0; i < 5; i++) {
    log_i("Connecting to MQTT, attempt %d", i);
    client.connect(device_name.c_str(), mqtt_user, mqtt_pass, sensor.getStateTopic(), 1, true, "OFF", false);
    if (client.connected()) {
      if (mqttDiscovery) {
        publishDiscoveryMessage(client, binarySensor);
        publishDiscoveryMessage(client, binarySensor, bs_num);

        publishDiscoveryMessage(client, button);
        publishDiscoveryMessage(client, button, button_num);

        publishDiscoveryMessage(client, light0);
        publishDiscoveryMessage(client, light0, light0_num);

        publishDiscoveryMessage(client, light1);
        publishDiscoveryMessage(client, light1, light1_num);

        publishDiscoveryMessage(client, number);
        publishDiscoveryMessage(client, number, number_num);

        publishDiscoveryMessage(client, select1);
        publishDiscoveryMessage(client, select1, select_num);

        publishDiscoveryMessage(client, sensor);
        publishDiscoveryMessage(client, sensor, sensor_num);
        publishDiscoveryMessage(client, sensor, sensor_num, 1);

        publishDiscoveryMessage(client, switch1);
        publishDiscoveryMessage(client, switch1, switch_num);

        mqttDiscovery = false;
      }
      
      client.subscribe(button.getCommandTopic(), true);
      client.subscribe(button.getCommandTopic(button_num), true);

      client.subscribe(light0.getCommandTopic());
      client.subscribe(light0.getBrightnessCommandTopic());
      client.subscribe(light0.getCommandTopic(light0_num));
      client.subscribe(light0.getBrightnessCommandTopic(light0_num));

      client.subscribe(light1.getCommandTopic());
      client.subscribe(light1.getCommandTopic(light1_num));

      client.subscribe(number.getCommandTopic());
      client.subscribe(number.getCommandTopic(number_num));

      client.subscribe(select1.getCommandTopic());
      client.subscribe(select1.getCommandTopic(select_num));

      client.subscribe(switch1.getCommandTopic());
      client.subscribe(switch1.getCommandTopic(switch_num));
      
      log_i("Connected to MQTT");
      break;
    }

    log_i("Failed to connected to MQTT: %d", client.state());
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void checkMQTT(PubSubClient& client) {
  log_i("CheckMQTT");
  uint32_t start = millis();
  while (start + 2000 > millis()) {
    client.loop();
  }
}

bool connectToWifi() {
  log_i("Attempting Wifi connection");
  WiFi.begin(ssid, password);
  uint8_t wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    log_i(".");
    wifiAttempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    WiFi.setAutoReconnect(true);
    log_i("ip: %s", WiFi.localIP().toString());
    return true;
  } else {
    WiFi.disconnect(true, true);
    return false;
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  std::string message((char*)payload, length);
  std::string setTopic(topic);

  log_i("----------------------------");
  log_i("Message: %s", message.c_str());
  log_i("Topic: %s", topic);

  if (setTopic.find(button.getShortName()) != std::string::npos) {
    int32_t index = getIndex(setTopic);
    if (index == -1) {
      log_i("button");
    } else {
      log_i("button %d", index);
    }

  } else if (setTopic.find(light0.getShortName()) != std::string::npos) {
    int32_t index = getIndex(setTopic);

    if (setTopic.find("brightness") != std::string::npos) {
      int32_t command = std::stoi(message);

      if (index == -1) {
        log_i("lightAbrt");
        mp["lightAbrt"] = command;
      } else {
        log_i("lightAbrt %d", index);
        mp["lightAbrt" + std::to_string(index)] = command;
      }
    } else {
      bool command = message.find("ON") != std::string::npos ? true : false;

      if (index == -1) {
        log_i("lightA");
        mpb["lightA"] = command;
      } else {
        log_i("lightA %d", index);
        mpb["lightA" + std::to_string(index)] = command;
      }
    }

  } else if (setTopic.find(light1.getShortName()) != std::string::npos) {
    bool command = message.find("ON") != std::string::npos ? true : false;
    int32_t index = getIndex(setTopic);

    if (index == -1) {
      log_i("lightB");
      mpb["lightB"] = command;
    } else {
      log_i("lightB %d", index);
      mpb["lightB" + std::to_string(index)] = command;
    }

  } else if (setTopic.find(number.getShortName()) != std::string::npos) {
    int32_t command = std::stoi(message);
    int32_t index = getIndex(setTopic);

    if (index == -1) {
      log_i("number");
      mp["number"] = command;
    } else {
      log_i("number %d", index);
      mp["number" + std::to_string(index)] = command;
    } 

  } else if (setTopic.find(select1.getShortName()) != std::string::npos) {
    int32_t command = getVectorIndex(options, message);
    int32_t index = getIndex(setTopic);
    log_i("command %d, index %d", command, index);

    if (index == -1) {
      log_i("select");
      mp["select"] = command;
    } else {
      log_i("select %d", index);
      mp["select" + std::to_string(index)] = command;
    }

  } else if (setTopic.find(switch1.getShortName()) != std::string::npos) {
    bool command = message.find("ON") != std::string::npos ? true : false;
    int32_t index = getIndex(setTopic);

    if (index == -1) {
      log_i("switch");
      mpb["switch"] = command;
    } else {
      log_i("switch %d", index);
      mpb["switch" + std::to_string(index)] = command;
    }
  } 
}

void publishDiscoveryMessage(PubSubClient& client, DiscoveryBase& dmb) {
  client.publish(dmb.getConfigurationTopic(), dmb.getDiscoveryMessage(), true);
}

void publishDiscoveryMessage(PubSubClient& client, DiscoveryBase& dmb, int32_t i) {
  client.publish(dmb.getConfigurationTopic(i), dmb.getDiscoveryMessage(i), true);
}

void publishDiscoveryMessage(PubSubClient& client, DiscoveryGenericSensor& dm, int32_t i, int32_t j) {
  client.publish(dm.getConfigurationTopic(i, j), dm.getDiscoveryMessage(i, j), true);
}

int32_t getIndex(std::string setTopic) {
  std::regex r(R"((?:\D*\d+\D+)(\d+))");
  std::smatch match;
  int32_t index = -1;

  if (std::regex_search(setTopic, match, r)) {
    index = std::stoi(match[1]);
  }

  return index;
}

int32_t getVectorIndex(std::vector<std::string> v, std::string value) {
  ptrdiff_t pos = find(v.begin(), v.end(), value) - v.begin();
  if (pos >= v.size()) {
    return -1;
  } else {
    return (int32_t)pos;
  }
}
