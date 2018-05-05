/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>

//ultrasonic sensor part
#define PIN_ECHO1 2
#define PIN_TRIG1 3
#define PIN_ECHO2 4
#define PIN_TRIG2 5

Ultrasonic ultrasonic1(PIN_TRIG1,PIN_ECHO1);
Ultrasonic ultrasonic2(PIN_TRIG2,PIN_ECHO2);

//LED in
#define PIN_LED1 6
#define PIN_LED2 7
#define PIN_LED3 8
#define PIN_LED4 9

// bluetooh
#define PIN_RX 10
#define PIN_TX 11
SoftwareSerial mySerial(PIN_RX, PIN_TX);

//dafruit_PWMServo part
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define PWM14     14
#define PWM15     15


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  mySerial.begin(9600);
  Serial.println("startup_bluetooh");

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(PIN_LED1, INPUT);
  pinMode(PIN_LED2, INPUT);
  pinMode(PIN_LED3, INPUT);
  pinMode(PIN_LED4, INPUT);

  delay(10);
}

void loop() {
  // Drive each servo one at a time
  Serial.print("servonum ");
  Serial.print(servonum);
  Serial.print(" sound 1 :");
  Serial.print(ultrasonic1.distanceRead());
  delay(1);
  Serial.print(" sound 2 :");
  Serial.print(ultrasonic2.distanceRead());
  Serial.print(" PIN_LED1:");
  Serial.print(digitalRead(PIN_LED1));
  Serial.print(" PIN_LED2:");
  Serial.print(digitalRead(PIN_LED2));
  Serial.print(" PIN_LED3:");
  Serial.print(digitalRead(PIN_LED3));
  Serial.print(" PIN_LED4:");
  Serial.print(digitalRead(PIN_LED4)); 
  Serial.println("");


  // set po A
  pwm.setPWM(PWM14, 0, SERVOMIN);
  pwm.setPWM(PWM15, 0, SERVOMIN);
  delay(500);

  // set po B
  pwm.setPWM(PWM14, 0, SERVOMAX);
  pwm.setPWM(PWM15, 0, SERVOMAX);
  delay(500);
  
  // set po C
  pwm.setPWM(PWM14, 0, SERVOMIN);
  pwm.setPWM(PWM15, 0, SERVOMAX);
  delay(500);
  
  // set po D
  pwm.setPWM(PWM14, 0, SERVOMAX);
  pwm.setPWM(PWM15, 0, SERVOMIN);
  delay(500);
  servonum ++;
  if (servonum > 15) servonum = 0;
}
