#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------- RFID ----------
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------- LCD ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- SERVO ----------
Servo lockServo;
const int SERVO_PIN = 3;
const int LOCKED_ANGLE = 0;
const int UNLOCKED_ANGLE = 90;

// UID autorisé (remplace si besoin)
byte allowedUID[4] = {0xBB, 0xB9, 0x3A, 0x06};

bool uidMatches() {
  if (rfid.uid.size != 4) return false;
  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != allowedUID[i]) return false;
  }
  return true;
}

void showMessage(const char* l1, const char* l2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(l1);
  lcd.setCursor(0,1);
  lcd.print(l2);
}

void setup() {
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.backlight();
  showMessage("RFID Door Lock", "Initialisation");

  // Servo
  lockServo.attach(SERVO_PIN);
  lockServo.write(LOCKED_ANGLE);

  // RFID
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);

  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  rfid.PCD_Init();
  rfid.PCD_AntennaOn();

  delay(1000);
  showMessage("Approche carte", "");
  Serial.println("Systeme pret.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (uidMatches()) {
    showMessage("ACCES AUTORISE", "Ouverture...");
    lockServo.write(UNLOCKED_ANGLE);
    delay(3000);
    lockServo.write(LOCKED_ANGLE);
    showMessage("Porte fermee", "Approche carte");
  } else {
    showMessage("ACCES REFUSE", "Carte inconnue");
    delay(2000);
    showMessage("Approche carte", "");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(500);
}
