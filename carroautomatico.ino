#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

#define TRIG_PIN A0
#define ECHO_PIN A1
#define LED_PIN 13

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  stopCar();
}

float medir() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracion = pulseIn(ECHO_PIN, HIGH, 15000);

  if (duracion == 0) return 999.0;
  return (duracion * 0.0343) / 2.0;
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void loop() {
  float d = medir();

  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println(" cm");

  if (d > 0 && d <= 25.0) {
    digitalWrite(LED_PIN, HIGH);
    
    stopCar();
    delay(200);

    moveBackward();
    delay(350);

    stopCar();
    delay(150);

    turnRight();
    delay(300);

    stopCar();
    delay(200);
  } else {
    digitalWrite(LED_PIN, LOW);
    moveForward();
  }

  delay(40);
}