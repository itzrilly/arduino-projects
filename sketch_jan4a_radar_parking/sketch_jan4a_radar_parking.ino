const int trigPin = 9;
const int echoPin = 10;

const int ledPin = 6;
const int buzzerPin = 5;

long duration;
int distanceCm;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

int readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long d = pulseIn(echoPin, HIGH, 30000);

  if (d == 0) return -1;               // invalide (pas d'écho)
  int cm = (int)(d * 0.034 / 2.0);

  // Filtre simple : HC-SR04 fiable grosso modo entre 2cm et 400cm
  if (cm < 2 || cm > 400) return -1;   // invalide
  return cm;
}

void loop() {
  int cm = readDistanceCm();
  Serial.println(cm);

  if (cm != -1 && cm < 30) {  
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1200);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  delay(100);
}


