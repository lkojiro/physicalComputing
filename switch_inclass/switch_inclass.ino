void setup() {
  pinMode(7,INPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);

}

void loop() {
  bool isSwitched = digitalRead(7);
  int readVal = analogRead(A0);
  Serial.print("Switch says: %d Pot says: %d\n",isSwitched,readVal);

}
