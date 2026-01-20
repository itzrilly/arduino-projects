const int waterPin = A0;
const int ledPin = 6;
const int buzzerPin = 5;

int threshold = 300; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int waterValue = analogRead(waterPin);
  Serial.println(waterValue);

  if (waterValue > threshold) { 
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 2000);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  delay(200);
}
