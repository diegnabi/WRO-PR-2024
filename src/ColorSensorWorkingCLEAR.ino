#include <SPI.h>
#include <Wire.h>

#define S0 30
#define S1 29
#define S2 26
#define S3 27
#define sensorOut 28

//Defining DC Motor Pin #
  const int in1 = 36;
  const int in2 = 37;
  const int ENB = 4;

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int clear;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ENB, OUTPUT);

  //Drive Motor Foward
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(115200);

  analogWrite(4, 250);
  delay(200);
  analogWrite(4, 200);
}
void loop() {
  
//CLEAR
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  clear = pulseIn(sensorOut, LOW);
  
  // Printing the CLear value 
  Serial.print(" clear = ");
  Serial.println(clear);
  delay(100);

}

