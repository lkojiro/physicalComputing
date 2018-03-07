int LED = A0;


void setup() {
  pinMode(LED,INPUT);
  Serial.begin(9600);
  
}

void loop() {
  Serial.println(digitalRead(LED));
  
}








bool isPrime(int n){
  if (n < 2) return false;
  else if (n == 2) return true;
  for (int factor = 2; factor < pow(n,0.5); factor++){
    if (n%factor ==0) return false;
  }
  return true;
}

