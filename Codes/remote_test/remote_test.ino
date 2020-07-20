#include <Arduino.h>

#define buzz_pin        34                     // Buzzer pin

#define InL1            22                      // motor pin
#define PWML            46                      // PWM motor pin  
#define InL2            23                      // motor pin  

#define InR1            24                      // motor pin
#define PWMR            45                       // PWM motor pin
#define InR2            25                       // motor pin 

unsigned char val;

void motor_init(){
    pinMode(InL1, OUTPUT);
    pinMode(InL2, OUTPUT);
    pinMode(PWML, OUTPUT);
    
    pinMode(InR1, OUTPUT);
    pinMode(InR2, OUTPUT);
    pinMode(PWMR, OUTPUT);
}

void BUZZ_init(){
      pinMode(buzz_pin, OUTPUT);
      digitalWrite(buzz_pin, LOW);
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
      delay(500);
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
}

void motorForwardL(int PWM_val)  {
    analogWrite(PWML, PWM_val);
    digitalWrite(InL1, LOW);
    digitalWrite(InL2, HIGH);
}
void motorReverseL(int PWM_val)  {
    analogWrite(PWML, PWM_val);
    digitalWrite(InL1, HIGH);
    digitalWrite(InL2, LOW);
}

void motorForwardR(int PWM_val)  {
    analogWrite(PWMR, PWM_val);
    digitalWrite(InR1, LOW);
    digitalWrite(InR2, HIGH);
}
void motorReverseR(int PWM_val)  {
    analogWrite(PWMR, PWM_val);
    digitalWrite(InR1, HIGH);
    digitalWrite(InR2, LOW);
}

void setup() {
  // put your setup code here, to run once:
  motor_init();
  BUZZ_init();
  Serial3.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial3.available()>0)
  {
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
    val=Serial3.read();
    if(val==0x31)
    {
      motorForwardL(255);
      motorForwardR(255);
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
    }
    if(val==0x32)
    {

      
      motorReverseR(255);
      motorReverseR(255);
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
      delay(500);
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
    }
    }  
}
