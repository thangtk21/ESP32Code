#include "WiFi.h"
#include "ESPAsyncWebServer.h"
const char* ssid = "DIAMOND ELECTRIC VN";
const char* password = "devietnam@2019#";
AsyncWebServer server(80);
void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  server.on("/hello",HTTP_GET,[](AsyncWebServerRequest *rq)
  {
    rq->send(200,"text/plain","Hello World");
  }
  );
  server.begin();
}

void loop() 
{

}
