//libraries


#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <Servo.h>

// Create two servo instances
Servo back_left_servo;
Servo back_right_servo;
//define pins

//range sensor pins
#define trigPin 13
#define echoPin 12

//soundboard pins
// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_TX 5
#define SFX_RX 6

// Connect to the RST pin on the Sound Board
#define SFX_RST 4


// not all servos stop at exactly 90, so adjust default stop here
#define LEFT_DEFAULT_STOP 90
#define RIGHT_DEFAULT_STOP 90


//declare variables
//soundboard variables and objects

SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

//sound sensor variables
const int soundPin = A0;
int threshold = 483;

// Sending signals to servos:
// 90 is no servo movement (mid-point)
// 0 is full speed forward
// 180 is full speed backward
int back_left_speed = 90;
int back_right_speed = 90;


void setup()
{
  Serial.begin(9600);
  Serial.println("Adafruit Sound Board!");

  // softwareserial at 9600 baud
  ss.begin(9600);
  // can also do Serial1.begin(9600)

  if (!sfx.reset()) {
    Serial.println("Not found");
    while (1);
  }
  Serial.println("SFX board found");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servos on Arduino PWM pin 9 and PWM pin 10
  back_left_servo.attach(9);
  back_right_servo.attach(10);
  // Set servos to mid-range, ie, default stop
  back_left_servo.write(LEFT_DEFAULT_STOP);
  back_right_servo.write(RIGHT_DEFAULT_STOP);


}


void loop()
{

  char byte = 0;
  //variables for the ultrasonic range
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  int value = analogRead(soundPin);//read the value of A0
  // Serial.println(value);//print the value of the sound sensor



  //-----the robot part woo------------------
  //if statement for combo of range and sound sensors


  //if person is LOUD AND CLOSEST ==== SCARED AND MOVES BACKWARDS
  if ((value > threshold) && (distance > 0 && distance <= 30)) //if the value is greater than 600
  {
    Serial.println(value);  //print the value of the sound sensor

    //display on monitor for range sensor response
    Serial.print("Hey Watch it! that's close enough!!");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println(value);
    //delay(250);

    //moving backwards
    back_left_speed += 5;  // Decrease speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed -= 5;  // Decrease speed by 5
    back_right_servo.write(back_right_speed);






    //soundboard info  display track
    Serial.print("\nPlaying track #");
    Serial.println(6);
    sfx.playTrack(6);

    Serial.print("\nPlaying track #");
    Serial.println(5);
    sfx.playTrack(5);

    Serial.print("\nPlaying track #");
    Serial.println(7);
    sfx.playTrack(7);

    Serial.print("\nPlaying track #");
    Serial.println(7);
    sfx.playTrack(7);

    Serial.print("\nPlaying track #");
    Serial.println(7);
    sfx.playTrack(7);

    Serial.print("\nPlaying track #");
    Serial.println(11);
    sfx.playTrack(11);

    Serial.print("\nPlaying track #");
    Serial.println(12);
    sfx.playTrack(12);

    if (! sfx.playTrack(6) && ! sfx.playTrack(7) && !sfx.playTrack(11) && !sfx.playTrack(12) && ! sfx.playTrack(5)) {
      Serial.println("Failed to play tracks?");
    }
    else {
      delay (20);
    }

    delay(2000);//delay 200ms
  }

//-------situation 2 -----
  //IF PERSON IS MEDIUM SOUND AND IN MIDDLE DISTANCE ==== CURIOUS CAT MEOW AND MOVE SLOWLY FORWARD
  else if  ((value < threshold) && (distance > 30 && distance <= 90))
  {
    Serial.println(value);//print the value of the sound sensor

    Serial.print("That's an interesting face you got there.");
    Serial.print(distance);
    Serial.println(" cm");
    //soundboard track 678
    delay(250);

    //move forward slowly

    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);


    //soundboard info  display track
    Serial.print("\nPlaying track #");
    Serial.println(3);
    sfx.playTrack(3);

    Serial.print("\nPlaying track #");
    Serial.println(3);
    sfx.playTrack(3);

    Serial.print("\nPlaying track #");
    Serial.println(2);
    sfx.playTrack(2);

    Serial.print("\nPlaying track #");
    Serial.println(2);
    sfx.playTrack(2);

    Serial.print("\nPlaying track #");
    Serial.println(13);
    sfx.playTrack(13);

    Serial.print("\nPlaying track #");
    Serial.println(13);
    sfx.playTrack(13);

    Serial.print("\nPlaying track #");
    Serial.println(10);
    sfx.playTrack(10);

    Serial.print("\nPlaying track #");
    Serial.println(10);
    sfx.playTrack(10);

    if (! sfx.playTrack(3) && ! sfx.playTrack(13) && ! sfx.playTrack(10) && ! sfx.playTrack(2)) {
      Serial.println("Failed to play tracks?");
    }
    else {
      delay (20);
    }

    delay(2000);//delay 200ms


////situation 3/////

    ////IF PERSON IS LOUD AND NEARLY FAR === CAT SCREECHES AND MOVES FORWARD AND SIDE WAYS
  } else if ((value > threshold) && (distance > 90 && distance <= 120)) {

    Serial.println(value); //print the value of the sound sensor

    Serial.print("Ya you should stay there!");
    Serial.print(distance);
    Serial.println(" cm");

    //move forward then left then right then left then forward
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);
    delay(250);
    //left move
    back_left_speed += 5;  // Decrease speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);

    //right move
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed -= 5;  // Decrease speed by 5
    back_right_servo.write(back_right_speed);
    //left move again
    back_left_speed += 5;  // Decrease speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);
    //right  again
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed -= 5;  // Decrease speed by 5
    back_right_servo.write(back_right_speed);
    delay(250);

    //move forward
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);


    //sfx
    //soundboard info  display track
    Serial.print("\nPlaying track #");
    Serial.println(1);
    sfx.playTrack(1);

    Serial.print("\nPlaying track #");
    Serial.println(1);
    sfx.playTrack(1);

    Serial.print("\nPlaying track #");
    Serial.println(4);
    sfx.playTrack(4);

    Serial.print("\nPlaying track #");
    Serial.println(4);
    sfx.playTrack(4);

    Serial.print("\nPlaying track #");
    Serial.println(14);
    sfx.playTrack(14);

    Serial.print("\nPlaying track #");
    Serial.println(14);
    sfx.playTrack(14);

    Serial.print("\nPlaying track #");
    Serial.println(15);
    sfx.playTrack(15);

    Serial.print("\nPlaying track #");
    Serial.println(15);
    sfx.playTrack(15);

    if (! sfx.playTrack(1) && ! sfx.playTrack(4) && !sfx.playTrack(14) && ! sfx.playTrack(15)) {
      Serial.println("Failed to play tracks?");
    }
    else {
      delay (20);
    }

    delay(2000);//delay 200ms

  }



//////situation 4////
  //IF PERSON IS NORMAL SOUND AND FAR AWAY === CAT MOVES SIDEWAYS FORWARD AND BACK AND THEN MEOOW SCREECH AND PURR
  else if ((value < threshold) && (distance > 120 && distance <= 200)) {

    Serial.println(value);//print the value of the sound sensor

    Serial.print("Get out of my swamp!");
    Serial.print(distance);
    Serial.println(" cm");

    //move forward
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);
    delay(250);

    //move back
    back_left_speed += 5;  // Decrease speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed -= 5;  // Decrease speed by 5
    back_right_servo.write(back_right_speed);

    //move forward again
    back_left_speed -= 5;  // Increase speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed += 5;  // Increase speed by 5
    back_right_servo.write(back_right_speed);
    delay(250);

    //move back
    back_left_speed += 5;  // Decrease speed by 5
    back_left_servo.write(back_left_speed);

    back_right_speed -= 5;  // Decrease speed by 5
    back_right_servo.write(back_right_speed);

    //sfx
    //soundboard info  display track
    sfx.playTrack(3);
    Serial.print("\nPlaying track #");
    Serial.println(3);


    Serial.print("\nPlaying track #");
    Serial.println(3);
    sfx.playTrack(3);

    Serial.print("\nPlaying track #");
    Serial.println(12);
    sfx.playTrack(12);

    Serial.print("\nPlaying track #");
    Serial.println(1);
    sfx.playTrack(1);

    Serial.print("\nPlaying track #");
    Serial.println(8);
    sfx.playTrack(8);

    Serial.print("\nPlaying track #");
    Serial.println(9);
    sfx.playTrack(9);

    Serial.print("\nPlaying track #");
    Serial.println(13);
    sfx.playTrack(13);


    if (! sfx.playTrack(3) && ! sfx.playTrack(12) && !sfx.playTrack(8) && !sfx.playTrack(9) && !sfx.playTrack(1) && !sfx.playTrack(13)) {
      Serial.println("Failed to play tracks?");
    }
    else {
      delay (20);
    }



    delay(2000);//delay 200ms

  }
////////////////situation 5 nothing happens so there is a default settings basically 
  ////IF PERSON IS OUT OF RANGE DO NOTHING
  else if (distance >= 200 || distance <= 0) {
    Serial.println(value);//print the value of the sound sensor
    Serial.println("Out of range");
    back_left_servo.write(LEFT_DEFAULT_STOP);
    back_right_servo.write(RIGHT_DEFAULT_STOP);
    Serial.print("\nPlaying track #");
    Serial.println(9);
    sfx.playTrack(9);

  }

  delay(2000);


}
