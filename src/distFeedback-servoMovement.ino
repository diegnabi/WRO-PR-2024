#include <SR04.h>
#include <NewServo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

//Defining Reset Protocal
#define OLED_RESET -1 //-1 to Share Reset Button with Arduino Board
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
  Serial.begin(9600); //Begins Serial Communication

  Steering.setMin(0); //Set Minimum Angle for Servo Motor
  Steering.setMax(180); //Set Maximum Angle for Servo Motor
  Steering.setInit(93); //Set Initial Position for Servo Motor
  Steering.begin(); //Start Servo Activity
  Steering.goInit(); //Servo Go To Initial Position

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Initializes Display
  display.clearDisplay(); //Clears Display
  display.setTextSize(2); //Sets the Text Size
  display.setTextColor(WHITE); //Sets The Color of the Text
  display.startscrollleft(0x00, 0x0F); //Scrolls from Left to Right
}

void loop() {
  //Left distance
  L_Dist = L_sr04.Distance();
  display.setCursor(0,0); //Sets the Position of Where the Text is being Printed
  if (int (L_Dist)<17){
    Serial.println("Left side is close"); //Text Printed in Serial Monitor
    display.print("L_Close"); //Text Printed on Oled Display
    Steering.move(80);
    delay(1000);
    Steering.goInit();
  }

  else {
    Serial.println("Left side is far"); //Text Printed in Serial Monitor
    display.print("L_Far"); //Text Printed on Oled Display
    delay (1000);
  }

  //Right distance 
  R_Dist = R_sr04.Distance();
  display.setCursor(0,32); //Sets the Position of Where the Text is being Printed
  if (int (R_Dist)<17){
    Serial.println("Right side is close"); //Text Printed in Serial Monitor
    display.print("R_Close"); //Text Printed on Oled Display
    Steering.move(120);
    delay(1000);
    Steering.goInit();
  }

  else {
    Serial.println("Right side is far"); //Text Printed in Serial Monitor
    display.print("R_Far"); //Text Printed on Oled Display
    delay (1000);
  }
}