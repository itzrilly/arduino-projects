const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // ROUGE
  setColor(255, 0, 0);
  delay(1000);

  // VERT
  setColor(0, 255, 0);
  delay(1000);

  // BLEU
  setColor(0, 0, 255);
  delay(1000);

  // JAUNE (rouge + vert)
  setColor(255, 255, 0);
  delay(1000);

  // CYAN (vert + bleu)
  setColor(0, 255, 255);
  delay(1000);

  // VIOLET (rouge + bleu)
  setColor(255, 0, 255);
  delay(1000);

  // BLANC
  setColor(255, 255, 255);
  delay(1000);

  // OFF
  setColor(0, 0, 0);
  delay(1000);
}
