#include <Preferences.h>
Preferences prf;

void setup()
{
  Serial.begin(115200);
  prf.begin("DEVN",false);
  uint16_t counter = prf.getUInt("cnt",0);
  counter++;
  Serial.printf("Current counter value: %d\n",counter);
  prf.putUInt("cnt",counter);
  prf.end();
}
void loop()
{
  
}
