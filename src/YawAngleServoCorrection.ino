#include <Wire.h>
#include <MPU6050.h>
#include <NewServo.h>

NewServo Steering(3);
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float yaw = 0;

void setup() {
  //Gyro Setup
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyroscope
  mpu.calibrateGyro();

  // Gyroscope Sensitivity
  mpu.setThreshold(0);

  //Servo Setup
  Steering.setMin(0); //Set Minimum Angle for Servo Motor
  Steering.setMax(180); //Set Maximum Angle for Servo Motor
  Steering.setInit(83); //Set Initial Position for Servo Motor
  Steering.begin(); //Start Servo Activity
  Steering.goInit(); //Servo Go To Initial Position
}

void gyro(){
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Yaw
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));

}

void loop(){
  while (yaw < 90) {
Steering.move(62); // Turn right
gyro();
analogWrite(4, 170);
}

Steering.goInit();

}