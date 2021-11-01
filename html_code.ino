#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led1 D5
#define led2 D6

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Infinix HOT 9 Play", "1234567899");
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
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println("");
  client.println("<html>");
  client.println(" <head>");

  client.println(" <title>Document</title>");
  client.println("</head>");

  client.println("<style>");

  client.println("  *{body{background-image: url(data:image/jpeg;base64,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); text-align: center;}}");
  client.println("  *{#a,#b,#c {color: azure; font-weight: bold; text-align: center;}}");
  client.println("  *{#d{ background: none; font-size: larger;border-width: thick; width: 4cm;  border-color: rgb(206, 205, 205);  color: blanchedalmond; }}");
  client.println("</style>");






  client.println(" <body>");

  client.println(" <h1 id=\"a"\">IOT ELECTRICAL SWITCH BOARD<h1>");
  client.println("   <h2 id=\"b"\">Welcome To IOT Appliances Control HomePage</h2>");
  client.println(" <h3 id=\"c"\">Press ON To Turn On Switch & Off To Turn Off Switch </h3>");
  client.println("  <h5 id=\"c"\"> Switch:01 Status OFF</h5>");
  client.println("  <button id =\"d" \"name=\"subject"\" type=\"submit"\" value=\"ON"\">ON</button> &nbsp;&nbsp;&nbsp;");
  client.println("  <button id =\"d"\" name=\"subject" \"type=\"submit"\" value=\"OFF"\">OFF</button>");
  client.println("   <h5 id=\"c"\"> Switch:02 Status OFF</h5>");
  client.println("  <button id =\"d"\" name=\"subject"\" type=\"submit"\" value=\"ON"\">ON</button> &nbsp;&nbsp;&nbsp;");
  client.println("  <button id =\"d"\" name=\"subject"\" type=\"submit"\" value=\"OFF"\">OFF</button>");
  client.println("  <h5 id=\"c"\"> Switch:03 Status OFF</h5>");
  client.println("  <button id =\"d"\" name=\"subject"\" type=\"submit"\" value=\"ON"\">ON</button> &nbsp;&nbsp;&nbsp;");
  client.println("  <button id =\"d"\" name=\"subject"\" type=\"submit"\" value=\"OFF"\">OFF</button>");
  client.println("  <h5 id=\"c"\"> Switch:04 Status OFF</h5>");
  client.println("  <button id =\"d"\" name=\"subject\"\" type=\"submit"\" value=\"ON"\">ON</button> &nbsp;&nbsp;&nbsp;");
  client.println("  <button id =\"d"\" name=\"subject"\" type=\"submit"\" value=\"OFF"\">OFF</button>");

  client.println("  </body>");
  client.println("   </html>");


}
