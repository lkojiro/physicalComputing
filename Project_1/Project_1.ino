#include <Servo.h>

Servo motor;
int servoPin = 10;
int LED0 = 2;
int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;

int countdownClock = 0;
int counted = 0;
int randomizer = 0;
int pause = 500;
long timer = 0;



void setup(){
  motor.attach(servoPin);
  pinMode(pot,INPUT);
  Serial.begin(9600);
  
  
}

int getDist(){
  return 42;
}

void inRangeLED(){
  //write me!
}

void launch(){
  //write me!
}

void outRangeLED(){
  int when = millis()%500;

  if (when < 100){
    digitalWrite(LED0,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 200){
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 300){
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 400){
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);
  }
  else {
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,HIGH);
  }
}


void loop() {
  randomizer++;
  bool inRange;
  int dist = getDist();
  if (dist < 30){   
    inRange = true;
  }
  else inRange = false;
  
  if (inRange){ // if in range, increment timer every 500ms
    
    if ( (millis() - timer) > pause){ //from code-bites
      countdownClock++;
      timer = millis();
      if (countdownClock ==6){
        counted++;
        countdownClock = 0;
      }
    }
    if (counted == randomizer%3){
    //if counted down 1-3 times, launch ball
      launch();
    }
    inRangeLED();
    
  }
  else {
    countdownClock = 0;
    counted = 0;
    outRangeLED();
  }
 }

