void setup(){
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
  
}



bool isPrime(int n){
  if (n < 2) return false;
  else if (n == 2) return true;
  for (int factor = 2; factor < pow(n,0.5); factor++){
    if (n%factor ==0) return false;
  }
  return true;
}

void loop() {
    // s ... o--- s...
    int readStuff = analogRead(A0);
 

    if (isPrime(readStuff)){
      digitalWrite(12,HIGH);
      digitalWrite(7,LOW);
    }
    else {
      digitalWrite(7,HIGH);
      digitalWrite(12,LOW);
    }
    
    Serial.println(readStuff);
}

