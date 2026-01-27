#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SOUND_PIN = A0;
const int LED_PIN = 6;
const int BUZZER_PIN = 7;

int THRESHOLD = 520;

const int HIT_NEEDED = 6;
int hitCount = 0;

void show(const char* l1, const char* l2) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  show("Sound Detector", "Init...");
  delay(1200);
  show("Calibrage...", "Silence 3s");

  long sum = 0;
  const int samples = 300;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(SOUND_PIN);
    delay(10);
  }
  int ambient = sum / samples;

  THRESHOLD = ambient + 40;

  Serial.print("Ambient = "); Serial.println(ambient);
  Serial.print("Threshold = "); Serial.println(THRESHOLD);

  show("Pret", "Seuil auto OK");
  delay(1200);
  show("Bruit > seuil ?", "...");
}

void alarmOn() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 2000);
}

void alarmOff() {
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);
}

void loop() {
  int value = analogRead(SOUND_PIN);
  Serial.println(value);

  if (value > THRESHOLD) {
    hitCount++;
  } else {
    hitCount = 0;
  }

  if (hitCount >= HIT_NEEDED) {
    show("ALERTE SON !", "Bruit detecte");
    alarmOn();
    delay(800);
    alarmOff();
    show("Bruit > seuil ?", "...");
    hitCount = 0;
  }

  delay(20);
}
