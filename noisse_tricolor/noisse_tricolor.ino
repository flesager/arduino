/*
  Noise Warning
  Reads an analog input on pin 0, then light the 3 leds based on the value
 */
#define FILTER_SIZE 4

int filter[FILTER_SIZE]={};
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  init_filter();
}

void loop() {
  // read the input on analog pin 0:
  int noisyValue = analogRead(A0);
  noisyValue = update_filter(noisyValue);
  // sennd on serial port
  
  //light the specific LED based on the analog value
  int switch_noise = noisyValue / 30;
  if(switch_noise > 10) switch_noise = 10;
  
  //Serial.println(switch_noise);
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  switch(switch_noise)
  {
    case (10) : digitalWrite(12,HIGH);
    case (9) : digitalWrite(11,HIGH);
    case (8) : digitalWrite(10,HIGH);
    case (7) : digitalWrite(9,HIGH);
    case (6) : digitalWrite(8,HIGH);
    case (5) : digitalWrite(7,HIGH);
    case (4) : digitalWrite(6,HIGH);
    case (3) : digitalWrite(5,HIGH);
    case (2) : digitalWrite(4,HIGH);
    case (1) : digitalWrite(3,HIGH);
    default : digitalWrite(2,HIGH);
    Serial.println("digitalWrite(2,HIGH)");
  }
  //delay(1);
}

int init_filter()
{
  for(int iloop=0;iloop<(FILTER_SIZE);iloop++)
  {
    filter[iloop]=0;
  }
}

int update_filter(int new_val)
{
  //shif old value and accumulate
  int accumulate=0;
  for(int iloop=0;iloop<(FILTER_SIZE-1);iloop++)
  {
    filter[iloop]=filter[iloop+1];
    accumulate += filter[iloop];
  }
  filter[FILTER_SIZE-1] = new_val;
  accumulate += new_val;
  return accumulate;
}

