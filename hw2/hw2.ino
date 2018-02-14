#define LEDY 5
#define LEDR 6
#define LEDG 7
#define B0 8
#define B1 9
#define B2 10
#define B3 11


void setup() {
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDY,OUTPUT);
  pinMode(B0,INPUT);
  pinMode(B1,INPUT);
  pinMode(B2,INPUT);
  pinMode(B3,INPUT);
  
}

void loop() {
  
  int vote0 = (digitalRead(B0)) ? 1 : 0;
  int vote1 = (digitalRead(B1)) ? 1 : 0;
  int vote2 = (digitalRead(B2)) ? 1 : 0;
  int vote3 = (digitalRead(B3)) ? 1 : 0;
  
  int votes = vote0 + vote1 + vote2 + vote3;
  
  if (votes == 0 || votes == 4) {
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDY,LOW);
  }

  else if (votes == 1 || votes == 3){
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDY,HIGH);
  }
  else {
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDY,LOW);
  }

}








bool isPrime(int n){
  if (n < 2) return false;
  else if (n == 2) return true;
  for (int factor = 2; factor < pow(n,0.5); factor++){
    if (n%factor ==0) return false;
  }
  return true;
}

