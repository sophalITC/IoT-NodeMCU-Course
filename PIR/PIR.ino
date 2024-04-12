#define sensor D4  // Digital pin D7

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);   // declare sensor as input
}

void loop() {

  long state = digitalRead(sensor);
  if (state == HIGH) {
    digitalWrite (LED_BUILTIN, HIGH);
    Serial.println("Motion detected!");
    delay(1000);
  }
  else {
    digitalWrite (LED_BUILTIN, LOW);
    Serial.println("Motion absent!");
    delay(1000);
  }
}
