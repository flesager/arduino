//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

#define NB_LINE 2
#define NB_ROW  16
#define PIN_TRIG1 10
#define PIN_ECHO1 11

#define PIN_TRIG2 5
#define PIN_ECHO2 6

LiquidCrystal_I2C lcd(0x27,NB_ROW,NB_LINE);
Ultrasonic ultrasonic1(PIN_TRIG1,PIN_ECHO1);
Ultrasonic ultrasonic2(PIN_TRIG2,PIN_ECHO2);

void setup()
{
  int val=10;
  lcd.init();                      // initialize the lcd
  //lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ultrasound1:");
  lcd.setCursor(0,1);
  lcd.print("ultrasound2:");
}


void loop()
{
  lcd.setCursor(12,0);
  lcd.print(ultrasonic1.distanceRead());
  lcd.print("   ");
  lcd.setCursor(12,1);
  lcd.print(ultrasonic2.distanceRead());
  lcd.print("   ");
  delay(300);
}
