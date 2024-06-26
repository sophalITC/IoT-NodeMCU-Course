#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 15
Adafruit_SSD1306 OLED(OLED_RESET);  // New object OLED
void setup()   {
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  // initialize with the I2C addr 0x3C (for the 128x64)
}
void loop() {
  OLED.clearDisplay();               //Clear display
  OLED.setTextColor(WHITE);          //Set text color
  OLED.setCursor(15,0);               //Set display start position
  OLED.setTextSize(2);               //Set text size x1
  OLED.println("Read ADC");          //Type message
  OLED.setCursor(15,35);             //Set display postion
  OLED.setTextSize(2);               //Set text size x2 
  OLED.println("A0=" + String(analogRead(A0)));  // Show result value
  OLED.display();                    //Enable display
}

