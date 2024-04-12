// #include  2 บรรทัดนี้ ต้องมีเสมอ
#include <ESP8266WiFi.h>
#include <MicroGear.h>       


const char* ssid     = "WiFi-J8";        // ชื่อ ssid
const char* password = "0817677402";    // รหัสผ่าน wifi

#define APPID   "PhuketCODE"          // ให้แทนที่ด้วย AppID
#define KEY     "QQKAfRrmczSvfwO"            // ให้แทนที่ด้วย Key
#define SECRET  "j0gqYsHA5OZi2xmMjRZTl3RaS"         // ให้แทนที่ด้วย Secret

#define ALIAS   "Light1"  // ตั้งชื่อเล่นให้ device นี้

#define LED D1

WiFiClient client;

int timer = 0;
char state = 0;

MicroGear microgear(client);     // ประกาศตัวแปร microgear

// สร้างฟังก์ชั่นที่จะถูกเรียกเมื่อมี message เข้ามา
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);

// ถ้า message ที่เข้ามาเป็น 1 ให้เปิด LED ถ้าเป็น 0 ให้ปิด LED
    if(*(char *)msg == '1'){
      digitalWrite(LED, LOW);  // LED on
    }else{
      digitalWrite(LED, HIGH);  // LED off
    }
}

// สร้างฟังก์ชั่นที่จะถูกเรียกเมื่อ microgear connect กับ NETPIE สำเร็จ
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    // เราอาจจะใช้โอกาสนี้ ตั้งชื่อ หรือเปลี่ยนชื่อ หรืออาจจะทำอะไรบางอย่าง เช่น subscribe 
    microgear.setAlias(ALIAS);
}

void setup() {
   // ประกาศให้ เวลามี message เข้ามา ให้กระโดดไปทำฟังก์ชั่น onMsghandler()
    microgear.on(MESSAGE,onMsghandler);

   // ประกาศให้เมื่อ connect สำเร็จ ให้กระโดดไปทำฟังก์ชั่น onConnected()
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    while (!Serial){
      Serial.print(".");
    }
    Serial.println("Starting...");

    pinMode(LED, OUTPUT);

   // initiate Wifi
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected"); 
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

   // initial ตัวแปร microgear 
    microgear.init(KEY,SECRET,ALIAS);

   // เชื่อมต่อไป NETPIE ไปยัง AppID ที่กำหนด
    microgear.connect(APPID);  // ฟังก์ชั่นเชื่อมต่อ NETPIE
}

void loop() {
    // เช็คว่า  microgear ยัง connect หรือเปล่า
    if (microgear.connected()) { // ตรวจสอบการเชื่อมต่อ NETPIE
        Serial.println("..."); // พิมพ์แจ้งการเชื่อมต่อ NETPIE สำเร็จ
       // เราต้องเรียก microgear.loop() เป็นระยะ ไม่เช่นนั้น connection จะหลุด
        microgear.loop();
       
    }
    else {
        Serial.println("connection lost, reconnect..."); 
        if (timer >= 5000) {
            microgear.connect(APPID); 
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
