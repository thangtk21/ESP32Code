#define LED_ON  1
#define LED_OFF 0

#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

void onHandle();
void offHandle();
void rootHandle();
String sendHTML(bool);

const char* ssid = "DIAMOND ELECTRIC VN";
const char* password = "devietnam@2019#";
WebServer server(80);

bool ledStatus = LED_OFF;

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("wait for connecting...");
    delay(200);
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  

  server.on("/ledon", onHandle);
  server.on("/ledoff", offHandle);
  server.on("/", rootHandle);
  server.begin();
}

String sendHTML(bool ledstat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  if (ledstat)
  {
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}


void onHandle()
{
  ledStatus = LED_ON;
  digitalWrite(2, ledStatus);
  server.send(200, "text/html", sendHTML(ledStatus));
}

void offHandle()
{
  ledStatus = LED_OFF;
  digitalWrite(2, ledStatus);
  server.send(200, "text/html", sendHTML(ledStatus));
}

void rootHandle()
{
  server.send(200, "text/html", sendHTML(ledStatus));
}

void loop()
{
  server.handleClient();
}
