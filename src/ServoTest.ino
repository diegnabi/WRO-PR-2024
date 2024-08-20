#include <NewServo.h>

NewServo Steering(3);
void setup() {
  Steering.setMin(0); //Set Minimum Angle for Servo Motor
  Steering.setMax(180); //Set Maximum Angle for Servo Motor
  Steering.setInit(94); //Set Initial Position for Servo Motor
  Steering.begin(); //Start Servo Activity
  
}


void loop() {

  Steering.move(70);


}