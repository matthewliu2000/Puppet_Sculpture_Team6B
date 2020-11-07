#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int small = 20;

const unsigned int A = 110;
const unsigned int B2 = 123;
const unsigned int C3 = 131;
const unsigned int D3 = 147;
const unsigned int E3 = 165;
const unsigned int F3 = 175;
const unsigned int G3 = 196;
const unsigned int Gsharp3 = 208;


int servo1Pos[] = {45,90,-45,-90,45,90,-45,-90};
int servo2Pos[] = {90,-45,-90,45,-90,45,90,-45};
int servo3Pos[] = {-45,-90,45,90,90,-45,-90,45};
int servo4Pos[] = {-90,45,90,-45,-45,-90,45,90};

void driveServos(int note){
  switch(note){
    case A:
    servo1.write(servo1Pos[0]);
    delay(small);
    servo2.write(servo2Pos[0]);
    delay(small);
    servo3.write(servo3Pos[0]);
    delay(small);
    servo4.write(servo4Pos[0]);
    delay(small);
    break;
    case B2:
    servo1.write(servo1Pos[1]);
    delay(small);
    servo2.write(servo2Pos[1]);
    delay(small);
    servo3.write(servo3Pos[1]);
    delay(small);
    servo4.write(servo4Pos[1]);
    delay(small);
    break;
    case C3:
    servo1.write(servo1Pos[2]);
    servo2.write(servo2Pos[2]);
    servo3.write(servo3Pos[2]);
    servo4.write(servo4Pos[2]);
    break;
    case D3:
    servo1.write(servo1Pos[3]);
    servo2.write(servo2Pos[3]);
    servo3.write(servo3Pos[3]);
    servo4.write(servo4Pos[3]);
    break;
    case E3:
    servo1.write(servo1Pos[4]);
    servo2.write(servo2Pos[4]);
    servo3.write(servo3Pos[4]);
    servo4.write(servo4Pos[4]);
    break;
    case F3:
    servo1.write(servo1Pos[5]);
    servo2.write(servo2Pos[5]);
    servo3.write(servo3Pos[5]);
    servo4.write(servo4Pos[5]);
    break;
    case G3:
    servo1.write(servo1Pos[6]);
    servo2.write(servo2Pos[6]);
    servo3.write(servo3Pos[6]);
    servo4.write(servo4Pos[6]);
    break;
    case Gsharp3:
    servo1.write(servo1Pos[7]);
    servo2.write(servo2Pos[7]);
    servo3.write(servo3Pos[7]);
    servo4.write(servo4Pos[7]);
    break;
    }
  }

void setup() {
  // put your setup code here, to run once:

pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
servo1.attach(5);
servo2.attach(6);
servo3.attach(9);
servo4.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:

driveServos(A);
delay(250);
driveServos(B2);
delay(250);
driveServos(C3);
delay(250);

}
