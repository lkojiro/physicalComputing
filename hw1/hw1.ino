//Outputs: LED,servo
//Inputs:  Potentiometer, button/switch, photoresistor


void setup() {
  
  pinMode(12,OUTPUT);//LED
  pinMode(A0,INPUT);//Photoresistor
  pinMode(A1,INPUT); //potentiometer 
  pinMode(7,INPUT); //switch
  pinMode(A2,OUTPUT); //servo

}

void loop() {
  
  int currBrightness = analogRead(A0);
  int threshold = analogRead(A1);
  bool nightMode = digitalRead(7); //change this if use button

  if (nightMode){ //darker room = light on
    if ((currBrightness < threshold)){
      digitalWrite(12,HIGH);
    }
    else digitalWrite(12,LOW);
  }
  else { //brighter room = light on
    if ((currBrightness >= threshold)){
      digitalWrite(12,HIGH);
    }
    else digitalWrite(12,LOW);
  }

  analogWrite(A2,currBrightness); //Write to servo
  

}
