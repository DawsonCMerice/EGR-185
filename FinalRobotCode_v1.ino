#include <Servo.h> 

Servo myservo;

#define enA 6
#define in1 7
#define in2 8

#include <NewPing.h>
#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

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
int angleStr = 1500;
int angleTurn;
int strSpd = 155;
int trnSpd = 210;

void setup() {

  Serial.begin(115200);
  myservo.attach(5);  //attach servo to pin9
  myservo.write(90);  // set servo to mid-point

 pinMode(enA, OUTPUT);      //assign pins as output
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);

 analogWrite(enA,strSpd);

 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);

}

void loop() {
 sonarEcho();
 turningFix();
 Serial.println(myservo.read());
 if(myservo.read() < 55 || myservo.read() > 135) {
  analogWrite(enA,trnSpd);
 }
 else {
  analogWrite(enA, strSpd);
 }

}

void sonarEcho(){
  NewPing mySonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  microSec = mySonar.ping_median(5);
  delay(30);
  distance = (float)microSec/US_ROUNDTRIP_CM;
  Serial.println(distance);
}



void turningFix(){
  desired_distance = 9;
  actual_distance = distance;
  error = desired_distance - actual_distance;
  turn_signal = error * 50;
  
  angleTurn = angleStr + turn_signal;
  if(angleTurn < 750){
    angleTurn = 750;
  }
  if(angleTurn > 2250){
    angleTurn = 2250;
  }
  
  myservo.writeMicroseconds(angleTurn);
  
}
