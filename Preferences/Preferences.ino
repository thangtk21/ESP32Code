#include "Preferences.h"
Preferences pr;

void setup() 
{
  Serial.begin(115200);
  pr.begin("DEVN",false);
  uint8_t a = pr.getUInt("cnt",0);
  Serial.println(a);
  pr.end();
}

void loop() 
{
  
}
