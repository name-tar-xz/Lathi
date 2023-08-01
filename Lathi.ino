w #include<L298NX2.h>
#include <HCSR04.h>

    HCSR04 front(9, 10); // trigger , echo |10cm away form wall to consider it
                         // as a wall, forward=5
HCSR04 left(11, 12);
HCSR04 right(3, 4);

int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;

L298NX2 motor(IN1_A, IN2_A, IN1_B, IN2_B);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double frontDist = front.dist();
  double leftDist = left.dist();
  double rightDist = right.dist();

  delay(2500);
  if (frontDist > 5) {

    motor.forwardForA(100); // so that dude doesnt crash cause fatness
    motor.backwardForB(100);
    forwardForever();
    if (leftDist <= 10) {
      // issawall/object idk append array bs
      Serial.print(1);
    } else {
      // issaemptyspace idk append array bs
      Serial.print(0);
    }
  } else if (frontDist < 5) {
    // end array
    // start a new array
    uturn();
    forwardForever();
    if (left > 5) {
      // issaemptyspace idk append array bs
      Serial.println(0);

    } else {
      // issa object idk append
      Serial.print(1);
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
void rightTurn() {
  motor.forwardForA(400);
  motor.backwardForB(400);
}
void leftTurn() {
  motor.forwardForA(400);
  motor.backwardForB(400);
}
void uTurn() {

  motor.backwardForA(250);
  motor.backwardForB(250);
  rightTurn();
  rightTurn();
}
