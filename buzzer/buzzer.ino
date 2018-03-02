/*
  Active Buzzer Warning
  Make the Buzzer sound for one second, then off for one second, repeatedly.
*/

void setup() {                
  // initialize the digital pin as an output.
  pinMode(7, OUTPUT);     
}

void loop() {
  digitalWrite(7, HIGH);   // make the Buzzer sound
  delay(50);              // wait for a second
  digitalWrite(7, LOW);    // set the Buzzer off
  delay(10);              // wait for a second
}
