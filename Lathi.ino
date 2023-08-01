#include <HCSR04.h>
#include <L298NX2.h>

HCSR04 front(9, 10); // trigger , echo |10cm away form wall to consider it
                     // as a wall, forward=5
HCSR04 left(11, 12);
HCSR04 right(3, 4);

int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;

int uTBOB;
String str;

L298NX2 motor(IN1_A, IN2_A, IN1_B, IN2_B);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (left.dist() > right.dist()) {
    const int uTBOB = 1;
  } else {
    const int uTBOB = 0;
  }
}

void loop() {

  // put your main code here, to run repeatedly :
  double frontDist = front.dist();
  double leftDist = left.dist();
  double rightDist = right.dist();

  delay(2500);
  if (frontDist <= 5) {
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
