#define LED 7
#define SW 8
#define B0 9
#define B1 10


void setup() {
  pinMode(LED,OUTPUT);
  pinMode(SW,INPUT);
  pinMode(B0,INPUT);
  pinMode(B1,INPUT);
  
}

void loop() {
  bool closed1 = digitalRead(SW);
  bool closed2 = digitalRead(B0);
  bool closed3 = digitalRead(B1);

  bool allClosed = closed1 & closed2 & closed3;

  if (!allClosed){
    digitalWrite(LED,HIGH);
  }
  else digitalWrite(LED,LOW);
}








bool isPrime(int n){
  if (n < 2) return false;
  else if (n == 2) return true;
  for (int factor = 2; factor < pow(n,0.5); factor++){
    if (n%factor ==0) return false;
  }
  return true;
}

