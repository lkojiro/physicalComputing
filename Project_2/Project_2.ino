const int coinSwitch = 2;
const int dispPin = 3;
const int startPin = A3;
const int resetPin = A4;
const int slider = A5;
const int washLED = 4;
const int dryLED = 5;
const int alarmLED = 6;


const int clockMuxA = 7;
const int clockMuxB = 8;
const int clockMuxC = 9;

const int barMuxA = 10;
const int barMuxB = 12;
const int barMuxC = 13;

const int servoPin = 11;

/*#######    GLOBALS   ###### */
int coinCount = 0;

long timer = 0;
bool counting = true;
bool wash = true;
const long wash_time = 1800000;
const long dry_time = 2 * wash_time;


bool prevDisp = false;
bool currDisp;

bool prevStart = false;
bool currStart;

bool prevReset = false;
bool currReset;

bool prevCoin = false;
bool currCoin;




void writeBars(){
  if (!counting) return;
  if (timer <= 0){
    digitalWrite(alarmLED,HIGH);
  }
  else {
    timer--;
  }

  int frac = wash ? (timer/wash_time) : (timer/dry_time);
  int numBars = frac * 5;

  //selecting on MUX which LEDs to light up
  switch (numBars) {
    case 0:
      digitalWrite(barMuxA,HIGH);
      digitalWrite(barMuxB,LOW);
      digitalWrite(barMuxC,HIGH);
      break;
    case 1:
      digitalWrite(barMuxA,LOW);
      digitalWrite(barMuxB,LOW);
      digitalWrite(barMuxC,LOW);
      break;
    case 2:
      digitalWrite(barMuxA,LOW);
      digitalWrite(barMuxB,LOW);
      digitalWrite(barMuxC,HIGH);
      break;
    case 3:
      digitalWrite(barMuxA,LOW);
      digitalWrite(barMuxB,HIGH);
      digitalWrite(barMuxC,LOW);
      break;
    case 4:
      digitalWrite(barMuxA,LOW);
      digitalWrite(barMuxB,HIGH);
      digitalWrite(barMuxC,HIGH);
      break;
    case 5:
      digitalWrite(barMuxA,HIGH);
      digitalWrite(barMuxB,LOW);
      digitalWrite(barMuxC,LOW);
      break;
  }
}

long loopCounter = 0;
void writeCount(){
  loopCounter++;
  int quarters = coinCount % 4;
  long oneMod = loopCounter % 4;
  int twoMod = loopCounter % 3;
  int threeMod = loopCounter % 5;
  int thisMod = loopCounter % 2;


  switch (quarters){
    case 0:
      digitalWrite(clockMuxA,HIGH);
      digitalWrite(clockMuxB,HIGH);
      digitalWrite(clockMuxC,LOW);
      
      if (loopCounter%2 == 0){
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW); 
      }
      else {
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      break;



    case 1:
      
      if (oneMod == 0){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW);
      }
      else if (oneMod == 1){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW);
      }
      else if (oneMod == 2){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (oneMod == 3){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      break;



    case 2:
      
      if (twoMod == 0){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (twoMod == 1){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (twoMod == 2){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW);
      }
      break;



    case 3:
      

      if (threeMod == 0){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (threeMod == 1){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (threeMod == 2){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,HIGH);
      }
      else if (threeMod == 3){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW);
      }
      else if (threeMod == 4){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,LOW);
        digitalWrite(barMuxB,LOW);
        digitalWrite(barMuxC,LOW);
      }
      break;
  }

  int dollars = coinCount / 4;
  switch (dollars) {
    case 0: 
      digitalWrite(clockMuxA,HIGH);
      digitalWrite(clockMuxB,HIGH);
      digitalWrite(clockMuxC,LOW);
      digitalWrite(barMuxA,HIGH);
      digitalWrite(barMuxB,HIGH);
      digitalWrite(barMuxC,LOW);
      break;


    case 1:
      if (threeMod == 0){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      else if (threeMod == 1){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      else if (threeMod == 2){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      else if (threeMod == 3){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      else if (threeMod == 4){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      break;


    case 2:
      

      if (thisMod == 0){
        digitalWrite(clockMuxA,HIGH);
        digitalWrite(clockMuxB,LOW);
        digitalWrite(clockMuxC,HIGH);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      else if (thisMod == 1){
        digitalWrite(clockMuxA,LOW);
        digitalWrite(clockMuxB,HIGH);
        digitalWrite(clockMuxC,LOW);
        digitalWrite(barMuxA,HIGH);
        digitalWrite(barMuxB,HIGH);
        digitalWrite(barMuxC,LOW);
      }
      break;
  }
}




void setup() {
  pinMode(coinSwitch,INPUT);
  pinMode(dispPin,INPUT);
  pinMode(startPin, INPUT);
  pinMode(resetPin,INPUT);
  pinMode(slider,INPUT);
  pinMode(washLED,OUTPUT);
  pinMode(dryLED,OUTPUT);
  pinMode(alarmLED,OUTPUT);
  pinMode(clockMuxA,OUTPUT);
}



void loop() {
  int washdry = analogRead(slider);
  wash = (washdry < 512);
  if (wash){
    digitalWrite(washLED,HIGH);
    digitalWrite(dryLED,LOW);
  }
  else {
    digitalWrite(washLED,LOW);
    digitalWrite(dryLED,HIGH);
  }

  //add a coin
  currCoin = digitalRead(coinSwitch);
  if (currCoin && !prevCoin){
    coinCount++;
  }

  //dispense a coin
  currDisp = digitalRead(dispPin);
  if (currDisp && !prevDisp){
    //move the servo up for a hot sec
    coinCount--;
  }

  //reset the timer
  currReset = digitalRead(resetPin);
  if (currReset && !prevReset){
    counting = false;
    timer = wash ? wash_time : dry_time;
    
  }

  //start the timer
  currStart = digitalRead(startPin);
  if (currStart && !prevStart){
    counting = true;
  }

  writeBars();
  writeCount();

}
