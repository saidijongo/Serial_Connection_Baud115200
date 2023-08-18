
const int sensorRightPin = 3; // Right sensor pin
const int sensorLeftPin = 4;  // Left sensor pin
const int motorCWPIN = 5;     // CW motor control pin
const int motorCCWPIN = 7;    // CCW motor control pin


int motorPosition = 0;

void setup() {
  pinMode(sensorRightPin, INPUT_PULLUP);
  pinMode(sensorLeftPin, INPUT_PULLUP);
  pinMode(motorCWPIN, OUTPUT);
  pinMode(motorCCWPIN, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  // Checking for commands from Raspberry Pi
  if (Serial.available()) {
    String command = Serial.read();
    switch (command) {
      case 'RESET':
        resetToHomeBase();
        break;
      case 'CW':
        rotateCW(60);
        break;
      case 'CCW':
        rotateCCW(60);
        break;
      case 'STOP':
        stopMotor();
        break;
      case 'HOME':
        moveToHomeBase();
        break;
    }
  }
}

void resetToHomeBase() {
  rotateCCW(360); 
  while (!digitalRead(sensorRightPin)) {
    rotateCCW(1);
  }
  rotateCW(8); 
  Serial.println("Motor at Home Base");
}

void rotateCW(int angle) {
  digitalWrite(motorCWPIN, HIGH);
  delay(angle * 5);
  digitalWrite(motorCWPIN, LOW);
  motorPosition += angle;
  Serial.print("Rotated CW by ");
  Serial.print(angle);
  Serial.println(" degrees");
}

void rotateCCW(int angle) {
  digitalWrite(motorCCWPIN, HIGH);
  delay(angle * 5); 
  digitalWrite(motorCCWPIN, LOW);
  motorPosition -= angle;
  Serial.print("Rotated CCW by ");
  Serial.print(angle);
  Serial.println(" degrees");
}

void stopMotor() {
  digitalWrite(motorCWPIN, LOW);
  digitalWrite(motorCCWPIN, LOW);
  Serial.print("Motor stopped at position: ");
  Serial.print(motorPosition);
  Serial.println(" degrees");
}

void moveToHomeBase() {
  rotateCW(360); 
  while (!digitalRead(sensorLeftPin)) {
    rotateCCW(1);
  }
  rotateCW(8); 
  stopMotor();
}
