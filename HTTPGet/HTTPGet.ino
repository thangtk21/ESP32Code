#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
const char* ssid = "DIAMOND ELECTRIC VN";
const char* password = "devietnam@2019#";
uint32_t lastTime = 0;
String cityID = "1559978";
String APIKey = "4f169a9ad333758d6f191e9074a6e299";
void setup()
{
  Serial.begin(115200);
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
      String path = "https://api.openweathermap.org/data/2.5/weather?id=" + cityID + "&appid=" + APIKey;
      http.begin(path);
      http.GET();
      String payload = http.getString();
      Serial.println(payload);
      JSONVar obj = JSON.parse(payload);
      Serial.println(obj["weather"][0]["main"]);
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
