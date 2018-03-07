int LEDY = 5;
int LEDR = 6;
int LEDG = 7;
int b0 = 8;   //one point
int b1 = 9;   //two points
int b2 = 10;  //three points
int b3 = 11;  //reset

int score = 0;

bool litY = false;
bool litG = false;
bool litR = false;

unsigned long timerG = 0;
unsigned long timerY = 0;
unsigned long timerR = 0;


void setup() {
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDY,OUTPUT);
  pinMode(b0,INPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  Serial.begin(9600);
}




void loop() {
  bool onePoint = digitalRead(b0);
  bool twoPoint = digitalRead(b1);
  bool threePoint = digitalRead(b2);
  bool reset = digitalRead(b3);

  if (onePoint){
    score++;
    Serial.print("millis = ");
    Serial.print(millis());
    Serial.print(", free throw scored, ");
    Serial.print(score);
    Serial.println("points");
    litG = true;
    timerG = millis();
  }
  else if (twoPoint){
    score = score + 2;
    Serial.print("millis = ");
    Serial.print(millis());
    Serial.print(", field goal scored, ");
    Serial.print(score);
    Serial.println("points");
    litY = true;
    timerY = millis();
  }
  else if (threePoint){
    score = score + 3;
    Serial.print("millis = ");
    Serial.print(millis());
    Serial.print(", three pointer scored, ");
    Serial.print(score);
    Serial.println("points");
    litR = true;
    timerR = millis();
  }
  else if (reset){
    score = 0;
    Serial.print("millis = ");
    Serial.print(millis());
    Serial.print(", reset, ");
    Serial.print(score);
    Serial.println("points");
  }


  lightControl(litG,timerG,LEDG);
  lightControl(litY,timerY,LEDY);
  lightControl(litR,timerR,LEDR);
  
  
}

void lightControl(bool lit, unsigned long timer, int LED){
  if (lit){
    digitalWrite(LED,HIGH);
    if (millis() - timer >= 2000){
      lit = false;
      digitalWrite(LED,LOW);
      timer = millis();
    }
  }
  else digitalWrite(LED,LOW);
}

