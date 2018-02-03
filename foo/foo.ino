#include <Servo.h>

//Servo motor;
int servoPin = 3;
int pot = A0;


void setup(){
  //motor.attach(servoPin);
  //pinMode(pot,INPUT);
  //Serial.begin(9600);
  pinMode(12,OUTPUT);
  
}



void loop() {
  digitalWrite(12,HIGH);
  delay(2500);
  digitalWrite(12,LOW);
  delay(2500);
}








bool isPrime(int n){
  if (n < 2) return false;
  else if (n == 2) return true;
  for (int factor = 2; factor < pow(n,0.5); factor++){
    if (n%factor ==0) return false;
  }
  return true;
}

