#include <Ultrasonic.h>

//-- MOTEUR A --
int ENA=5; //Connecté à Arduino pin 5(sortie pwm)
int IN1=2; //Connecté à Arduino pin 2
int IN2=3; //Connecté à Arduino pin 3

//-- MOTEUR B --
int ENB=6; //Connecté à Arduino pin 6(Sortie pwm)
int IN3=4; //Connecté à Arduino pin 4
int IN4=7; //Connecté à Arduino pin 7

// direction of motor
#define NB_MOTOR 4
#define NB_DIRECTION 4

typedef enum {
  forward  = 0,
  backward = 1,
  left     = 2,
  right    = 3,
  unknown  = 4,
}direction;

int Direction[NB_DIRECTION][NB_MOTOR]={{LOW, HIGH, LOW, HIGH},
                                       {HIGH, LOW, HIGH, LOW},
                                       {HIGH, LOW, LOW, HIGH},
                                       {LOW, HIGH, HIGH, LOW}};

int ListMotor[NB_MOTOR] = {IN1, IN2, IN3, IN4};

//ultrasonic sensor
#define PIN_TRIG1 10
#define PIN_ECHO1 11

Ultrasonic ultrasonic1(PIN_TRIG1,PIN_ECHO1);

//parameter for motor power
#define MOTOR_ELEMENT 50
int MotorFilter[MOTOR_ELEMENT];
int IndMotorFilter;

#define SENSOR_ELEMENT 10
int SensorFilter[SENSOR_ELEMENT];
int IndSensorFilter;

void InitFilter(int* tab, int nbElement, int* Index)
{
  memset(tab,0,sizeof(int)*nbElement);
  *Index = 0;
}

int SetAndGetFilter(int val, int* tab, int* index, int nbElement)
{
  tab[*index] = val;
  *index = (*index + 1) % nbElement;
  int accu = 0;
  for(int iloop = 0; iloop < nbElement ; iloop++) 
      accu += tab[iloop];
  return (accu/nbElement);
}

void ResetMotor()
{
  InitFilter(MotorFilter, MOTOR_ELEMENT, &IndMotorFilter);
}

void InitSensor()
{
  InitFilter(SensorFilter, SENSOR_ELEMENT, &IndSensorFilter);
  for(int iloop = 0; iloop < SENSOR_ELEMENT; iloop++)
  {
      SetAndGetFilter(ultrasonic1.distanceRead(), SensorFilter, &IndMotorFilter, SENSOR_ELEMENT);
      delay(20);
  }
}

void set_power(int puissance)
{
  puissance = SetAndGetFilter(puissance, MotorFilter, &IndMotorFilter, MOTOR_ELEMENT);
  analogWrite(ENA,puissance); 
  analogWrite(ENB,puissance);
}

void SetDirection(direction dir)
{
  for(int iloop = 0; iloop < NB_MOTOR ; iloop ++)
      digitalWrite(ListMotor[iloop], Direction[dir][iloop]);
}

void UpdateDirAndPow(int mesure)
{
    direction WantedDir;
    if ( mesure < 20 ) WantedDir = backward;
    else if(mesure < 60 ) WantedDir = left;
    else WantedDir = forward;
    
    UpDirection(WantedDir, 255);
}

void UpDirection(direction newDirection, int power)
{
  static direction oldDirection = unknown;
  if(oldDirection != newDirection)
  {
    ResetMotor();
    SetDirection(newDirection);
    set_power(power);
    oldDirection = newDirection;
  }
  else{
    set_power(power);
  }
}

void setup() {
 pinMode(ENA,OUTPUT);//Configurer les broches comme sortie
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 pinMode(ENA,OUTPUT);
 pinMode(ENB,OUTPUT);
 
 Serial.begin(9600);
 ResetMotor();
 InitSensor();
}

void loop() {
  int mesure = SetAndGetFilter(ultrasonic1.distanceRead(), SensorFilter, &IndSensorFilter, SENSOR_ELEMENT);
  Serial.println(mesure);
  UpdateDirAndPow(mesure);
  delay(20);
}
