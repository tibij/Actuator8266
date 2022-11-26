#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13      // DS18B20 pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
extern float readTemperature;

DeviceAddress  sensors[3];


void setupOneWireBus(int precision) {
  
  int available = -1;

  // setup OneWire bus
  DS18B20.begin();

  available = DS18B20.getDeviceCount();
  Serial.print("Found devices: ");
  Serial.println(available);

  for(int x = 0; x!= available; x++)
  {
    if(DS18B20.getAddress(sensors[x], x))
    {
      Serial.println(x);
      DS18B20.setResolution(sensors[x], precision);
    }
  }
}

String getTemperature(int address) {  

  // float readTemperature;

  if (DS18B20.getAddress(sensors[address], address))
  {
    // Read temperature
    DS18B20.requestTemperatures();
    readTemperature = DS18B20.getTempC(sensors[address]);
    
    // Convert temperature to a string with two digits before the comma and 2 digits for precision
    char convertedTemperature[6];
    dtostrf(readTemperature, 2, 2, convertedTemperature);
    return (String)convertedTemperature;

  }
  else
    return "";  
}
