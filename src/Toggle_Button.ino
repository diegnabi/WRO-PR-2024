//Define Pin Numbers to Components

const int button = 12;
const int led = 13;
int status = LOW;

void setup(){
pinMode(led, OUTPUT);
pinMode(button, INPUT_PULLUP); 
}

void loop(){

if (digitalRead(button) == HIGH) {
status = !status;
digitalWrite(led, status);
} 
while(digitalRead(button) == HIGH);
delay(50);
}

// == equal to
// = defining (what it means)