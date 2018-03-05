/* 
  RF Blink - Transmit sketch 
     Written by ScottC 17 Jun 2014
     Arduino IDE version 1.0.5
     Website: http://arduinobasics.blogspot.com
     Transmitter: FS1000A/XY-FST
     Description: A simple sketch used to test RF transmission.          
 ------------------------------------------------------------- */

 #define rfTransmitPin 4  //RF Transmitter pin = digital pin 4
 #define ledPin 13        //Onboard LED = digital pin 13
const unsigned int upperThreshold = 70;  //upper threshold value
const unsigned int lowerThreshold = 50; //lower threshold value

 void setup(){
   pinMode(rfTransmitPin, OUTPUT);     
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);   
 }

 void loop(){
     digitalWrite(rfTransmitPin, HIGH);     //Transmit a HIGH signal
     int data = analogRead(A0);
     for(int i ; i< 10 ; i++)
     {
        Serial.println(analogRead(A0));
        data = analogRead(A0);
     }
     //digitalWrite(ledPin, HIGH);            //Turn the LED on
     delay(1000);                           //Wait for 1 second
     
     digitalWrite(rfTransmitPin,LOW);      //Transmit a LOW signal
     data = analogRead(A0);
     //digitalWrite(ledPin, LOW);            //Turn the LED off
     for(int i ; i< 10 ; i++)
     {
        Serial.println(analogRead(A0));
        data = analogRead(A0);
     }
     delay(1000);
}
