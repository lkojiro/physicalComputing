#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN    11
#define MAX_DIST    200

Servo motor;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

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
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  countdownClock = 0;
  counted = 0;

  
  motor.attach(servoPin);
  Serial.begin(115200);
  motor.write(90);
  
  
}




void inRangeLED(){
  switch (countdownClock){
    case 0:
      writeAll(LOW);
      break;
    case 1:
      digitalWrite(LED0,HIGH);
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      break;
      
    case 2:
      digitalWrite(LED0,HIGH);
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      break;
    case 3:
      digitalWrite(LED0,HIGH);
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      break;
      
    case 4:
      digitalWrite(LED0,HIGH);
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,LOW);
      break;
      
    case 5:
      writeAll(HIGH);
      break;
      
    default:
      writeAll(LOW);
      break;
  }
}



void writeAll(bool val){
    digitalWrite(LED0,val);
    digitalWrite(LED1,val);
    digitalWrite(LED2,val);
    digitalWrite(LED3,val);
    digitalWrite(LED4,val);
}


void launch(){
    //flash the LEDs
    
    Serial.println("LAUNCH\n\n");
    writeAll(HIGH);
    delay(100);
    writeAll(LOW);
    delay(100);
    writeAll(HIGH);
    delay(100);

    //launch the ball
    motor.write(180);
    delay(3000);
    setup();
    
    
    
}

void outRangeLED(){
  int scanFreq = 500;
  int when = millis()%scanFreq;
  int scanSegment = scanFreq/5;

  if (when < (scanSegment)){
    digitalWrite(LED0,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 2*scanSegment){
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 3*scanSegment){
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 4*scanSegment){
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
  delay(40);
  
  randomizer++;
  int cutoffDist = 15;
  bool inRange = (sonar.ping_cm() < cutoffDist);

  Serial.println(countdownClock);
  Serial.print("counter: ");
  Serial.println(counted);
  
  if (inRange){ // if in range, increment timer every 500ms
    
    if ( (millis() - timer) > pause){ //from code-bites
      countdownClock++;
      timer = millis();
      if (countdownClock == 6){ //count up to 5 then reset
        counted++;
        countdownClock = 0;
      }
    }
    if (counted == random(1,20) && countdownClock == 5){
    //if counted down 1-3 times, launch ball
      if (counted !=0) launch();
    }
    inRangeLED();
    
  }
  else {
    countdownClock = 0;
    counted = 0;
    outRangeLED();
  }
 }

