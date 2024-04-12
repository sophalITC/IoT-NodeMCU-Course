#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);
void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
display.setTextSize(1); // กำหนดขนาดตัวอักษร
display.setTextColor(WHITE);
display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
display.println(" OLED 0.96 TESTER ");
display.setCursor(0,10);
display.setTextSize(2);
display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
display.println(" Myarduino");
display.setCursor(0,32);
display.setTextSize(1);
display.setTextColor(WHITE);
display.println("128 x 64 Pixels 0.96");
display.setCursor(0,48);
display.setTextSize(1);
display.setTextColor(WHITE);
display.println(" www.myarduino.net "); // แสดงผลข้อความ www.Myarduino.net
display.display();
}
void loop() {
}
