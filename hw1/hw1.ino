//Outputs: LED,Serial feedback
//Inputs:  Potentiometer, button/switch, photoresistor


void setup() {
  
  pinMode(12,OUTPUT);//LED
  pinMode(A0,INPUT);//Photoresistor
  pinMode(A1,INPUT); //potentiometer 
  pinMode(7,INPUT); //switch
  Serial.begin(9600); //serial comm

}

void loop() {
  
  int currBrightness = analogRead(A0);
  int threshold = analogRead(A1);
  bool nightMode = digitalRead(7); //change this if use button
  bool LEDon = false;

  if (nightMode){ //darker room = light on
    if ((currBrightness > threshold)){
      digitalWrite(12,HIGH);
      LEDon = true;
    }
    else {
      digitalWrite(12,LOW);
      LEDon = false;
    }
    
  }
  
  else { //brighter room = light on
    if ((currBrightness <= threshold)){
      digitalWrite(12,HIGH);
      LEDon = true;
    }
    else {
      digitalWrite(12,LOW);
      LEDon = false;
    }
  }

  Serial.print("Room Brightness: ");
  Serial.print(currBrightness);
  Serial.print("; Setpoint: ");
  Serial.print(threshold);
  
  Serial.print("; Switch is in ");
  if (nightMode) Serial.print("night mode ");
  else Serial.print("day mode ");

  Serial.print("and the LED is ");
  if (LEDon) Serial.print("on\n");
  else Serial.print("off\n");
  
  


}
