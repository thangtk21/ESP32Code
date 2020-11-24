#include "SPIFFS.h"
void setup()
{
  Serial.begin(115200);
  SPIFFS.begin(true);
  File file = SPIFFS.open("/data.txt");
  if(!file)
  {
    Serial.println("can not open file");
    return;
  }

  Serial.println("File content");
  while(file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}

void loop()
{
  
}
