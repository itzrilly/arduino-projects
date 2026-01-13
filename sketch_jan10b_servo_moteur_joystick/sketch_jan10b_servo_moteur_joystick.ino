#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);  
}

void loop() {
  int joystickValue = analogRead(A0);    
  int angle = map(joystickValue, 0, 1023, 0, 180);

  myServo.write(angle);
  delay(15);
}
