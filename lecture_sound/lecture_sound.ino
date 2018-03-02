void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
//  pinMode(8,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  //If there is a big sound nearby, make the led light for one second.
//  if(sensorValue>500)
//  {
//    digitalWrite(8,HIGH);
//    delay(1000);
//  }
//  else
//  digitalWrite(8,LOW);
}
