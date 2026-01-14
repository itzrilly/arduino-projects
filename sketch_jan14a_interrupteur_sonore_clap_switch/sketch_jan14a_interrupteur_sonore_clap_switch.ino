const int soundPin = A0;
const int ledPin = 6;

int threshold = 550;      // seuil à ajuster
bool ledState = false;

unsigned long lastClap = 0;
unsigned long debounceTime = 300; // anti double-clap

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soundValue = analogRead(soundPin);
  Serial.println(soundValue);

  if (soundValue > threshold) {
    unsigned long now = millis();

    if (now - lastClap > debounceTime) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
      lastClap = now;
    }
  }

  delay(10);
}
