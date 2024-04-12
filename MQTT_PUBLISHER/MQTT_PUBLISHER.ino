#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
const char* mqtt_user = "";
const char* mqtt_pass = "";
const int mqtt_port = 0;

const int postingInterval = 5000;
long lastMsg = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void mqtt_publish() {

  // Prepare data to publish here
  char topic[] = "/iot/hello/";
  char msg[] = "Hello MQTT";
  client.publish(topic, msg);
  Serial.printf("Published: topic[%s] message[%s]\n", topic, msg);

}

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266ClientDDDD", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else
      delay(5000);
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  long now = millis();

  if (now - lastMsg > postingInterval) {
    mqtt_publish();
    lastMsg = now;
  }
}
