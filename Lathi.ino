#include <L298NX2.h>

int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;

int uTBOB;
String str;

#define usE1 10
#define usT1 9
#define usE2 12
#define usT2 11
#define usE3 4
#define usT3 3

long duration, cm;

L298NX2 motor(IN1_A, IN2_A, IN1_B, IN2_B);

void setup() {
  Serial.begin(9600);

  pinMode(usE1, INPUT);
  pinMode(usT1, OUTPUT);
  pinMode(usE2, INPUT);
  pinMode(usT2, OUTPUT);
  pinMode(usE3, INPUT);
  pinMode(usT3, OUTPUT);

  double frontDist = getDistance(1, "cm");
  double leftDist = getDistance(2, "cm");
  double rightDist = getDistance(3, "cm");

  if (leftDist > rightDist) {
    uTBOB = 1;
    Serial.println("help");
  } else if (leftDist == rightDist) {
    Serial.println("shit");
  } else {
    uTBOB = 0;
    Serial.println("no help");
  }
  Serial.println("uTBOB:" + String(uTBOB));
}

void loop() {
  double frontDist = getDistance(1, "cm");
  double leftDist = getDistance(2, "cm");
  double rightDist = getDistance(3, "cm");

  delay(1000);

  if (frontDist <= 5) {
    motor.stopA();
    motor.stopB();
    uTurn(uTBOB);
    str += "\n";
  } else {
    forwardForever();
    if (leftDist <= 10 || rightDist <= 10) {
      str += "1";
    } else {
      str += "0";
    }
  }
}

void forwardForever() {
  motor.forwardA();
  motor.forwardB();
}
void backwardForever() {
  motor.backwardA();
  motor.backwardB();
}
void leftTurn() {
  motor.forwardForA(400);
  motor.backwardForB(400);
}
void rightTurn() {
  motor.forwardForA(400);
  motor.backwardForB(400);
}
void uTurn(int uTBOB) {
  if (uTBOB == 0) {
    motor.backwardForA(50);
    motor.backwardForB(50);
    rightTurn();
    motor.forwardForA(150);
    motor.forwardForB(150);
    rightTurn();
  } else {
    motor.backwardForA(50);
    motor.backwardForB(50);
    leftTurn();
    motor.forwardForA(150);
    motor.forwardForB(150);
    leftTurn();
  }
}
