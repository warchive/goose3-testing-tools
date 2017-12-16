#include "ArduinoJson/ArduinoJson.h"

void setup()
{
  Serial.begin(9600);
  
  char json[] = "{\"states\": [{\"pins\": {\"digital\": {\"1\": false,\"2\": true},\"analog\": {\"1\": 123}},\"delayAfter\": 1000},{\"pins\": {\"digital\": {\"1\": false,\"2\": true},\"analog\": {\"1\": 123}},\"delayAfter\": 1000}]}";

  StaticJsonBuffer<2000> jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(json);

  bool test = root["states"][0]["pins"]["digital"]["2"];
  Serial.print("Test Value: ");
  Serial.println(test);
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
