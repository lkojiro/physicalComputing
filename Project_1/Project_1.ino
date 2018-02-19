#include "pitches.h"
#include <NewPing.h>
#include <Servo.h>

// notes in the melody: from http://www.arduino.cc/en/Tutorial/Tone
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

#define TRIGGER_PIN 12
#define ECHO_PIN    11
#define MAX_DIST    200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

int LED0 = 2;
int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;

Servo motor;
int servoPin = 10;

int BUZZ = 8;


int countdownClock = 0;
int counted = 0;
int pause = 500;
long timer = 0;



void setup(){
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  
  motor.attach(servoPin);
  motor.write(160);
  
  countdownClock = 0;
  counted = 0;

  
  Serial.begin(115200);
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
    

    //play a tune and wave the hand
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(BUZZ, melody[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(BUZZ);
      if (thisNote%2 == 0) motor.write(0);
      else motor.write(15);
    }

    

    //reset sequence
    delay(2000);
    while (true){ //after 2 seconds, move hand close to
                 //the ultrasonic sensor to reset motor
      delay(40);
      if (sonar.ping_cm() < 20) break;
    }
    setup();
    
    
    
}

void outRangeLED(){
  int scanFreq = 300;
  int when = millis()%scanFreq;
  int scanSegment = scanFreq/5;
  
  //flash LED with corresponding fifth of the time segment
  if (when < (scanSegment)){ //1/5
    digitalWrite(LED0,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 2*scanSegment){ //2/5
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 3*scanSegment){ //3/5
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (when < 4*scanSegment){//4/5
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);
  }
  else {                         //5/5
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,HIGH);
  }
}


void loop() {
  delay(40);
  
  int cutoffDist = 35;
  bool inRange = (sonar.ping_cm() < cutoffDist);

//  Serial.println(sonar.ping_cm());

//  Serial.println(countdownClock);
//  Serial.print("counter: ");
//  Serial.println(counted);
  
  if (inRange){ // if in range, increment timer every 500ms
    
    if ( (millis() - timer) > pause){ //from code-bites
      countdownClock++;
      timer = millis();
      if (countdownClock == 6){ //count up to 5 then reset
        counted++;
        countdownClock = 0;
      }
    }
    //after counting down 1-5 times, trigger launch
    //once final countdown sequence is complete
    if (counted == random(1,5) && countdownClock == 5){
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

