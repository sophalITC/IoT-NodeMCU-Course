#include "DHT.h"
#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "Shinjuku"; // ใส่ชื่อของ WiFi ที่ใช้งาน
const char* password = "0817677402"; // ใส่รหัสของ WiFi ที่ใช้งาน

#define APPID   "HelloNETPIEKorn" // ใส่ AppID (Application ID)
#define KEY     "mywnbxL6OyzcnjH" // ใส่ Key
#define SECRET  "CwLl1Pq8mZZHiOkboI7xcJzke" // ใส่ Secret
#define ALIAS   "piedht" // ตั้งชื่ออุปกรณ์ของเรา Alias Name
#define FEEDNAME  "DHT11TempHumid" // ใส่ชื่อของ FEEDID

#define MAX_TEMP 100
#define MAX_HUMID 100

WiFiClient client; // สร้าง client ขึ้นมา
MicroGear microgear(client); // นำ client ที่สร้างขึ้นมาเชื่อมต่อกับ netpie

#define DHTPIN D4    // ใช้ขา D4 เป็นขารับข้อมูลจาก DHT 11
#define DHTTYPE DHT22  // เลือกใช้ DHT 11
DHT dht(DHTPIN, DHTTYPE); // กำหนด DHT ว่าจะส่งไปยังขาไหน และใช้ DHT อะไร

float humid; 
float temp; 
int delays = 15000; 

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() {
  dht.begin();
  
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);
  
  Serial.begin(115200);
  Serial.println("Starting...");

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
}

void loop() {
   humid = dht.readHumidity();
   temp = dht.readTemperature();
   
  if (microgear.connected()) {
    Serial.println("connected");
    microgear.loop();
	
    delay(delays);
	
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" *C ");
    Serial.println();

    String data = "{\"humid\":";
            data += humid ;
            data += ", \"temp\":";
            data += temp ;
            data += "}";
	
    
    if ( isnan(humid) || isnan(temp)|| humid >= MAX_HUMID || temp>= MAX_TEMP){
      Serial.println("Failed to read from DHT sensor!");
      return;
    } else {
      microgear.publish("/dht/humid", humid);
      microgear.publish("/dht/temp", temp);
	  Serial.print("Sending -->");  
      Serial.println(data);
      microgear.writeFeed(FEEDNAME,data);
      Serial.println("Write Feed Success....");
    }    
  } else {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(100);
}

