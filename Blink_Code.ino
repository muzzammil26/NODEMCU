#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led1 D5
#define led2 D6

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Mooazam", "mooazam123");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.
  if (client == 1)
  {
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request == "GET /led1on HTTP/1.1")
    {
      digitalWrite(led1, HIGH);
      Serial.println("LED 1 is ON");
    }
    if (request == "GET /led1off HTTP/1.1")
    {
      digitalWrite(led1, LOW);
      Serial.println("LED 1 is OFF");
    }
    if (request == "GET /led2on HTTP/1.1")
    {
      digitalWrite(led2, HIGH);
      Serial.println("LED 2 is ON");
    }
    if (request == "GET /led2off HTTP/1.1")
    {
      digitalWrite(led2, LOW);
      Serial.println("LED 2 is OFF");
    }
  }}
