const int flamePin = 2;
const int ledPin = 6;
const int buzzerPin = 5;

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int flameDetected = digitalRead(flamePin);

  Serial.print("Flame: ");
  Serial.println(flameDetected);

  if (flameDetected == LOW) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 2000);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  delay(100);
}
