const int frontEchoPin = 7;
const int frontTriggerPin = 6;    
const int leftEchoPin = 11;
const int leftTriggerPin = 10;
const int rightEchoPin = 9;
const int rightTriggerPin = 8;
const int motorF = 2;
const int motorL = 3;
const int motorR = 4;
const int Buzzer = 5;
volatile float maxFrontDistance = 50.00;                     
volatile float frontDuration, frontDistanceCm, leftDuration, leftDistanceCm, rightDuration, rightDistanceCm;
volatile float maxLeftDistance = 40.00;
volatile float maxRightDistance = 40.00;
void setup() {
  // serial
  Serial.begin(9600);
  // ultrasonic
  pinMode(frontTriggerPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  // LED
  pinMode(motorF, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}
void loop() {
  digitalWrite(motorF, LOW);
  digitalWrite(motorL, LOW);
  digitalWrite(motorR, LOW);
  digitalWrite(Buzzer, LOW);
  // front distance check life of a blind user, we have used technology to upgrade this cane to provide more safety. The ultrasonic sensors detect the objects in front of them and guides them accordingly using the buzzer and vibration motors.
  checkFrontDistance();
  if (frontDistanceCm < maxFrontDistance) {
    Serial.println("Too close");
    digitalWrite(Buzzer, HIGH);
    checkLeftDistance();
    delay(20);
    checkRightDistance();
    delay(20);
    if (leftDistanceCm < rightDistanceCm)
      moveRight();
    else if (leftDistanceCm > rightDistanceCm) {
      moveLeft();
    }
  }
  else {
    Serial.println("OK");
    moveForward();
  }
  // left distance check
  checkLeftDistance();
  if (leftDistanceCm < maxLeftDistance) {
    Serial.println("Left too close");
    delay(20);
    checkLeftDistance();
    delay(20);
    checkRightDistance();
    delay(20);
    if (leftDistanceCm > rightDistanceCm)
      moveForward();
    else if (leftDistanceCm < rightDistanceCm) {
      moveRight();
    }
  }
  // right distance check
  checkRightDistance();
  if (rightDistanceCm < maxRightDistance) {
    Serial.println("Right too close");
    delay(20);
    checkRightDistance();
    delay(20);
    checkLeftDistance();
    delay(20);
    if (rightDistanceCm > leftDistanceCm)
      moveForward();
    else if (rightDistanceCm < leftDistanceCm) {
      moveLeft();
    }
  }
}
void checkFrontDistance() {
  digitalWrite(frontTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(frontTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  frontDistanceCm = frontDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Distance: ");
  Serial.print(frontDistanceCm);
  Serial.println(" cm");
}
void checkLeftDistance() {
  digitalWrite(leftTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(leftTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  leftDistanceCm = leftDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Left distance: ");
  Serial.print(leftDistanceCm);
  Serial.println(" cm");
}
void checkRightDistance() {
  digitalWrite(rightTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(rightTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  rightDistanceCm = rightDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Right distance: ");
  Serial.print(rightDistanceCm);
  Serial.println(" cm");
}
void moveBackward() {
  Serial.println("Backward.");
  digitalWrite(Buzzer, HIGH);
  //  digitalWrite(motorL2, LOW);
  //  digitalWrite(motorR1, HIGH);
  //  digitalWrite(motorR2, LOW);
}
void moveForward() {
  Serial.println("Forward.");
  digitalWrite(motorF, HIGH);
  delay(100);
}


void moveLeft() {
  Serial.println("Left.");
  digitalWrite(motorL, HIGH);
  delay(100);
}


void moveRight() {
  Serial.println("Right.");
  digitalWrite(motorR, HIGH);
  delay(100);
}


 