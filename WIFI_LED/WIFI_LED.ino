#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid  = "";
const char* password = "";

const int led = D1;
bool ledState;

ESP8266WebServer server(80);

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for(uint8_t i=0; i<server.args(); i++){
  message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain" , message);
}

void handleRoot()
{
  server.send(200, "text/plain" , "hello from esp8266!");
}

void handleLed()
{
  if (server.args() == 1 && server.argName(0) == "light")
  {
  if (server.arg(0) == "0")
  {
    digitalWrite(led,HIGH);
    ledState = false;
  }
  else
  {
    digitalWrite(led,LOW);
    ledState = true;
  }
  }
  String html =
  "<html>\n"
  " <hed><title>IoT</title></hed>\n"
  " <meta http-equiv=refresh content=10>\n"
  " <body>\n"
  "   <form action=\"led.php\" method=\"post\">\n";
  if (ledState)
  html +=
  " <button type='submit' name='light' value='0'>Turn Off</button></td>\n";
  else
  html +=
  " <button type='submit' name='light' value='1'>Turn On</button></td>\n"; 
  html +=
  "   </form>\n"
  " </body>\n"
  "</html>\n";
  server.send(200 , "text/html" , html); 
}

void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/led.php" , handleLed);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(led, HIGH);
  ledState = false;
}

void loop() {
  server.handleClient();
}

