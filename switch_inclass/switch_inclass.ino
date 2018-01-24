void setup() {
  pinMode(7,INPUT);
  Serial.begin(9600);

}

void loop() {
  bool isSwitched = digitalRead(7);
  Serial.println(isSwitched);

}
