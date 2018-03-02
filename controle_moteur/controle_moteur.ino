#include <Ultrasonic.h>

//-- MOTEUR A --
int ENA=5; //Connecté à Arduino pin 5(sortie pwm)
int IN1=2; //Connecté à Arduino pin 2
int IN2=3; //Connecté à Arduino pin 3

//-- MOTEUR B --
int ENB=6; //Connecté à Arduino pin 6(Sortie pwm)
int IN3=4; //Connecté à Arduino pin 4
int IN4=7; //Connecté à Arduino pin 7

//ultrasonic sensor
#define PIN_TRIG1 10
#define PIN_ECHO1 11

Ultrasonic ultrasonic1(PIN_TRIG1,PIN_ECHO1);

void setup() {
 pinMode(ENA,OUTPUT);//Configurer les broches comme sortie
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 
 //digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner (désactivation moteur)
 //digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner (désactivation moteur)
 set_directionA();
 Serial.begin(9600);

}

void loop() {
  int mesure = ultrasonic1.distanceRead();
  Serial.println(mesure);
  
  int tab_puissance[]={255,255,255,255};
  void (*tab_direction[])(void)={set_directionA,set_directionB,set_directionC,set_directionD};
  if ( mesure < 10 ) {set_power(100); set_directionB();}
  else if(mesure < 30 ) {set_power(100); set_directionC();}
  else if(mesure < 50){set_power(125); set_directionA();}
  else {set_power(255);set_directionA();}
}


void set_power(int puissance)
{
  // Moteur A - Plein régime
  //analogWrite(ENA,puissance);
  // Moteur B - Mi-régime
  //analogWrite(ENB,puissance);
  digitalWrite(ENA,HIGH); 
  digitalWrite(ENB,HIGH);
}


void set_directionD()
{
 // Direction du Moteur A
 digitalWrite(IN1,LOW); 
 digitalWrite(IN2,HIGH);

 // Direction du Moteur B
 // NB: en sens inverse du moteur A
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
}

void set_directionC()
{
 // Direction du Moteur A
 digitalWrite(IN1,HIGH); 
 digitalWrite(IN2,LOW);

 // Direction du Moteur B
 // NB: en sens inverse du moteur A
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
}

//marche arriere
void set_directionB()
{
 // Direction du Moteur A
 digitalWrite(IN1,HIGH); 
 digitalWrite(IN2,LOW);

 // Direction du Moteur B
 // NB: en sens inverse du moteur A
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
}


// marche avant
void set_directionA()
{
 // Direction du Moteur A
 digitalWrite(IN1,LOW); 
 digitalWrite(IN2,HIGH);

 // Direction du Moteur B
 // NB: en sens inverse du moteur A
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
}
