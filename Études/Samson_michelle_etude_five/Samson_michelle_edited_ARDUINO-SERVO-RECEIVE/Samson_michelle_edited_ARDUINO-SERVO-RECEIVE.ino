#include <Servo.h>

#define SERVO_PIN_1 9
#define SERVO_PIN_2 10
#define SERVO_PIN_3 11

int currentId = 0;
byte incomingByte;
int angle = 0;
int angle2 = 0;


Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  // initialize the button pin as an input:

  // initialize serial communication:
  Serial.begin(9600);
  myservo1.attach(SERVO_PIN_1);
  myservo2.attach(SERVO_PIN_2);
  myservo3.attach(SERVO_PIN_3);
}


void loop() {
  while (Serial.available() > 0)
  {

    incomingByte = Serial.read(); // read it

    if (incomingByte == 'A' ) {


      while (currentId < 1) {
        delay(10);
        incomingByte = Serial.read();
        if (incomingByte > 0 && incomingByte <= 90) {
          myservo1.write(incomingByte);
          delay(10);
          myservo2.write(incomingByte);
          delay(20);
        } else {

          myservo1.write(incomingByte);
          delay(10);


        }


        currentId++;
      }
    }

    else if (incomingByte == 'B' ) {


      while (currentId < 1) {
        delay(10);
        incomingByte = Serial.read();
        if (incomingByte >= angle) {
          for (angle = 0; angle < 180; angle++)
          {
            myservo1.write(angle);
            myservo3.write(angle);
            delay(10);
            myservo2.write(angle);
            delay(10);
          }
          // now scan back from 180 to 0 degrees
          for (angle = 180; angle > 0; angle--)
          {
            myservo1.write(angle);
            myservo3.write(angle);
            delay(10);
            myservo2.write(angle);
            delay(10);
          }
        }



        currentId++;
        //analogWrite(LED,incomingByte);

      }
    }

    else if (incomingByte == 'C' ) {


      while (currentId < 1) {
        delay(10);
        incomingByte = Serial.read();

        if (incomingByte >= 90 && incomingByte <= 180) {
          for (angle2 = 180; angle2 > 0; angle2--)
          {
            myservo3.write(angle2);
            myservo2.write(angle2);
            delay(10);
          }

          for (angle2 = 0; angle2 < 180; angle2++)
          {
            myservo3.write(angle2);
            myservo2.write(angle2);
            delay(10);
          }


        } else {

          myservo3.write(incomingByte);

          delay(10);

        }


        currentId++;
        //analogWrite(LED,incomingByte);

      }
    }
  }
  currentId = 0;


}











