#include <L298NX2.h>
#include <HCSR04.h>

HCSR04 front(2,3);//trigger , echo
HCSR04 ultra2(4,5);
HCSR04 ultra3(6,7);

int IN1_A = 8;
int IN2_A = 9;
int IN1_B = 10;
int IN2_B = 11;

L298NX2 motor(IN1_A, IN2_A, IN1_B, IN2_B);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  motor.forwardForB(1000);
  motor.forwardForA(1000);

    
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(front.dist());

}
void rightTurn(){
  motor.forwardForA(1000);
  motor.backwardForB(1000);
}
void leftTurn(){
  motor.forwardForA(1000);
  motor.backwardForB(1000);
}
void uTurn(){
  motor.backwardForA(500);
  motor.backwardForB(500);
  motor.stopA();
  motor.stopB();
  rightTurn();
  motor.forwardA();
  motor.forwardB();
  rightTurn();
}
