// Nate Winneg & Sohan Kulkarni
// Motor Encoder Test 1
// This script drives the motor and counts revolutions
// Pin 9 analog write goes one direction Pin 10 analog write goes the other way
// Duty cycle 40/255
// 36.4 counts per revolution on the encoder
// Encoder takes 5VDC
// No load test -- 53.02m in 10s -- ~ 5.3m/s top speed at this gear ratio


int motor1pin1 = 9;
int motor1pin2 = 10;

double pos = 0;
double revs;

int ENCA = 2;
int ENCB = 3;

void readEncoder()
{
  int b = digitalRead(ENCB);
  if(b>0) {
    pos++;
  }
  else {
    pos--;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(millis() < 10000) {
    analogWrite(10, 255);
    revs = pos/36.4;
    Serial.println(revs);
//  analogWrite(9,0);
//  analogWrite(10,0);
//  delay(1000);
//  analogWrite(10, 100);
//  delay(1000);
//  Serial.print(5*digitalRead(2));
//  Serial.print("\t");
//  Serial.println(5*digitalRead(3));
  }
}
