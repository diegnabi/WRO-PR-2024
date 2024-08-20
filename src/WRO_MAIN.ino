//Import Libraries
  #include <SR04.h>
  #include <NewServo.h>
  #include <SPI.h>
  #include <Wire.h>
  #include <MPU6050.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>


//Define Pin Number With Name Of Components
  //Defining Pin To Start Running The Program
    const int startButton = 13;

  //Defining everything needed for Left Distance Sensor
    const int L_TrigPin = 22; //Pin # for Trigger Pin
    const int L_EchoPin = 23; //Pin # for Echo Pin
    SR04 L_sr04 = SR04(L_EchoPin, L_TrigPin);
    long L_Dist; //Defining a Variable to Store the Data form the Left Sensor

  //Defining everything needed for Right Distance Sensor
    const int R_TrigPin = 53; //Pin # for Trigger Pin
    const int R_EchoPin = 52; //Pin # for Echo Pin
    SR04 R_sr04 = SR04(R_EchoPin, R_TrigPin);
    long R_Dist; //Defining a Variable to Store the Data form the Right Sensor

  //Defining Servomotor Pin #
    NewServo Steering(3);

  //Defining DC Motor Pin #
  const int in1 = 36;
  const int in2 = 37;
  const int ENB = 4;

  //Defining Pins for Color Sensor
    #define S0 30
    #define S1 29
    #define S2 26
    #define S3 27
    #define sensorOut 28

    #define S02 49
    #define S12 48
    #define S22 46
    #define S32 45
    #define sensorOut2 47

  //Defining Gyro name, variables and functions
    MPU6050 mpu;

    // Timers
      unsigned long timer = 0;
      float timeStep = 0.01;

    //Yaw values
      float yaw = 0;
  

//Define Variables Outside of Voids
  
  //Reset Corner Count to 0
  int corner = 0; 

  // Stores frequency read by the photodiodes of the color sensor 
  int red = 0;
  int green = 0;
  int blue = 0;
  int clear = 0;
  
  //Stores the "degree" value for the turning radius
  //int degree = 0;


void setup(){
  Serial.begin(115200); //Begin Serial Communication 

  //Setting up Servo Motor
  Steering.setMin(0); //Set Minimum Angle for Servo Motor
  Steering.setMax(180); //Set Maximum Angle for Servo Motor
  Steering.setInit(84); //Set Initial Position for Servo Motor
  Steering.begin(); //Start Servo Activity
  Steering.goInit(); //Servo Go To Initial Position

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Setting the inputs
  pinMode(sensorOut, INPUT);
  pinMode(startButton, INPUT); //Indicate that "startButton" will be an input signal

  // Setting frequency scaling of the Color Sensor to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Initialize Gyroscope
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyroscope
  mpu.calibrateGyro();

  // Gyroscope Sensitivity
  mpu.setThreshold(1);

  //Drive Motor Foward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
}

void checkDist(){
  //Left Sensor Distance
  L_Dist = L_sr04.Distance();
  if (int (L_Dist)<11){ //If the Distance from the Left Sensor is Less Than 15cm
    Serial.println("Left side is close"); //Feedback in Serial Monitor
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(4, 150);
    delay(800);
    Steering.move(63); //Servo Go to Designated Angle
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(4, 150);
    delay(1000);
    Steering.goInit(); //Servo Go To Initial Position
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(4, 150);
    delay(500);
  } 

  else {
      Serial.println("Left side is far"); //Feedback in Serial Monitor
  }

  //Right Sensor Distance 
  R_Dist = R_sr04.Distance(); 
  if (int (R_Dist)<13){ //If the Distance from the Right Sensor is Less Than 15cm
    Serial.println("Right side is close"); //Feedback in Serial Monitor
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(4, 150);
    delay(800);
    Steering.move(95); //Servo Go to Designated Angle
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(4, 150);
    delay(1000);
    Steering.goInit(); //Servo Go To Initial Position
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(4, 150);
    delay(500);
  }

  else {
      Serial.println("Right side is far"); //Feedback in Serial Monitor
  }
}


void gyro(){ //Reads Gyro Yaw Angle Values
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Yaw
  yaw = yaw + norm.ZAxis * timeStep;

  //Output Yaw Angle
  Serial.print("Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
  
}

void Rturn() { //Turns the Robot 90 Degrees to the Right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(1000);
  Steering.move(62); // Turn right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2060);
  checkDist();
  Steering.goInit();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(500);
  corner++; // Indicate a corner has been passed
}


void Lturn() { //Turns the Robot 90 Degrees to the Left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(1000);
  checkDist();
  Steering.move(107); // Turn right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  checkDist();
  delay(2050);
  checkDist();
  Steering.goInit();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  checkDist();
  delay(500);
  corner++; // Indicate a corner has been passed
}

void open() { //Code for Open Challenge
  int clear = 0;
  //    Min level of Light
  while (int (clear) <25){  //Whilst on the white part of track do the following)
    //CLEAR
    digitalWrite(S2,HIGH);
    digitalWrite(S3,LOW);
  
    // Reading the output frequency
    clear = pulseIn(sensorOut, LOW);
    delay(25);

    checkDist();

    //Drive Motor Foward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(4, 150); //Speed of DC Motor
  }
  analogWrite(4, 180);
  Serial.println("OpenFinsih");
  Rturn();
}

void loop(){
  //If the Start Button has been Pressed then Run the Code until 12 Corners have been Completed
  if (digitalRead(startButton) == HIGH && corner < 12){
      //Run code here
      open();
  }
  if (corner >= 12) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}




