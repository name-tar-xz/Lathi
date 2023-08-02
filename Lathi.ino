#include <L298NX2.h>

#define usE1 10
#define usT1 9
#define usE2 12
#define usT2 11
#define usE3 4
#define usT3 3
int IN1_A = 5;
int IN2_A = 6;
int IN1_B = 7;
int IN2_B = 8;

int uTBOB;
String str;

double duration, cm;

L298NX2 motor(IN1_A, IN2_A, IN1_B, IN2_B);

double getDistance(int sensor = 1, String type = "cm") {
    int trig, echo;
    if (sensor == 1) {
        trig = usT1;
        echo = usE1;
    } else if (sensor == 2) {
        trig = usT2;
        echo = usE2;
    } else if (sensor == 3) {
        trig = usT3;
        echo = usE3;
    } else {
        trig = usT1;
        echo = usE1;
    }

    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    cm = (duration / 2) / 29.1;
    return cm;
}
void forwardForever() {
    motor.forwardA();
    motor.forwardB();
}
void backwardForever() {
    motor.backwardA();
    motor.backwardB();
}
int d1=325;
int ds=250;
void leftTurn() {
    motor.forwardB();
    motor.backwardA();
    delay(d1);
    motor.stop();
    delay(ds);
}
void rightTurn() {
    motor.forwardA();
    motor.backwardB();
    delay(d1);
    motor.stop();
    delay(ds);
}
void uTurn(int uTBOB) {
    int d2=250;
    motor.stop();
    if (uTBOB == 0) {
        rightTurn();
        motor.forward();
        delay(d2);
        motor.stop();
        delay(ds);
        rightTurn();
    } else {
        leftTurn();
        motor.forward();
        delay(d2);
        motor.stop();
        delay(ds);
        leftTurn();
    }
}
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
    } else if (leftDist == rightDist) {
        Serial.println("shit");
    } else {
        uTBOB = 0;
    }
}

void loop() {
    double frontDist = getDistance(1, "cm");
    double leftDist = getDistance(2, "cm");
    double rightDist = getDistance(3, "cm");
    // Serial.println("frontDist:" + String(frontDist) + "\nleftDist:" +
    // String(leftDist) + "\nrightDist:" + String(rightDist));

    if (frontDist <= 10) {
        uTurn(uTBOB);
        if(uTBOB==0) {
            uTBOB=1;
        }
        else if(uTBOB==1) {
            uTBOB=0;
        }
        // Serial.println("uTBOB:" + String(uTBOB));
        str += "\n";
    } else {
        motor.forward();
        if (leftDist <= 10 || rightDist <= 10) {
            str += "1";
        } else {
            str += "0";
        }
    }
    Serial.println("---\n" + str + "\n---");
}
