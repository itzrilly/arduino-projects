const int LDR_PIN = A0;
const int LED_PIN = 6;

int threshold = 500;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("=== TEST LDR ===");
  Serial.println("Cache la LDR -> valeur doit CHANGER");
  Serial.println("Si LED inverse, on corrigera.");
}

void loop() {
  int value = analogRead(LDR_PIN);
  Serial.print("LDR = ");
  Serial.println(value);

  if (value < threshold) {
    digitalWrite(LED_PIN, HIGH); // NUIT -> LED ON
  } else {
    digitalWrite(LED_PIN, LOW);  // JOUR -> LED OFF
  }

  delay(200);
}
