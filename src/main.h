// Main.h

const char* mqttTopicTempCircuitPardoseala = "house/etaj/birou/tempCircuitPardoseala/value";
const char* mqttTopicTempBirou = "house/etaj/birou/temp/value";

void setupGPIOs();

int setupWiFi();

void setupMQTT();

int checkMQTT();

void subscribeMQTT(const char* mqttTopic);

void publishMQTT(const char* mqttTopic, String value);

void setupOneWireBus(int precision);

String getTemperature(int address);
