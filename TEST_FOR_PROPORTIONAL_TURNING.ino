#include <NewPing.h>
#include <Servo.h>

Servo myservo;
//#define enA 6
//#define in1 7
//#define in2 8
#define TRIGGER_PIN 5
#define ECHO_PIN 3
#define MAX_DIST 400

enum servoStates {
  STRAIGHT,
  LEFT
};

enum servoStates state = STRAIGHT;
unsigned int microSec;
int distance;
int desired_distance;
int actual_distance;
int error;
int turn_signal;
unsigned long currentTime=0, previousTime=0;
int angleStr = 80;
int angleTurn;

void setup() {

  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(angleStr);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  analogWrite(6, 170);

  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);

}

void loop() {
 sonarEcho();
 turningFix();

}

void sonarEcho(){
  NewPing mySonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);
  microSec = mySonar.ping_median(5);
  delay(40);
  distance = (float)microSec/US_ROUNDTRIP_CM;
  Serial.println(distance);
}



void turningFix(){
  desired_distance = 9;
  actual_distance = distance;
  error = desired_distance - actual_distance;
  turn_signal = error * 5;
  
  angleTurn = angleStr - turn_signal;
  if(angleTurn > 125){
    angleTurn = 125;
  }
  if(angleTurn < 35){
    angleTurn = 35;
  }
  
  myservo.write(angleTurn);
  
}
