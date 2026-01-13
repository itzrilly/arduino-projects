int ledPin = 8;
int buttonPin = 2;

bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Détection d'un nouvel appui
  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;            // inverse l'état
    digitalWrite(ledPin, ledState);  // applique l'état
    delay(200);                      // anti-rebond simple
  }

  lastButtonState = buttonState;
}
