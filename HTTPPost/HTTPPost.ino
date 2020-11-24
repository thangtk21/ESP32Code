#include <Adafruit_BME280.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_BME280 bme;
const char* ssid = "DIAMOND ELECTRIC VN";
const char* password = "devietnam@2019#";
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  bme.begin(0x76);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("wait for connecting...");
    delay(200);
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (millis() - lastTime > 5000)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      float value1 = bme.readTemperature();
      float value2 = bme.readHumidity();
      float value3 = bme.readPressure();
      String path = "https://api.thingspeak.com/update";
      http.begin(path);
      http.POST("api_key=CXX3YK89Z815XHBJ&field1=" + String(value1) + ",&field2=" + String(value2) + ",&field3=" + String(value3));
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
