int LEDY = 5;
int LEDR = 6;
int LEDG = 7;
int B0 = 8;   #one point
int B1 = 9;   #two points
int B2 = 10;  #three points
int B3 = 11;  #reset

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
  pinMode(B0,INPUT);
  pinMode(B1,INPUT);
  pinMode(B2,INPUT);
  pinMode(B3,INPUT);
  Serial.begin(9600);
}




void loop() {
  bool onePoint = digitalRead(B0);
  bool twoPoint = digitalRead(B1);
  bool threePoint = digitalRead(B2);
  bool reset = digitalRead(B3);

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
}

