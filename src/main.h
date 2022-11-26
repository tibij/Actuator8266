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

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 12000; // 12 seconds 
unsigned int contor = 0;
float sum = 0;

float readTemperature;