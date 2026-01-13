#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int tempPin = A0;

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int value = analogRead(tempPin);
  float voltage = value * (5.0 / 1023.0);
  float temperature = voltage * 100;

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" C");

  delay(1000);
}
