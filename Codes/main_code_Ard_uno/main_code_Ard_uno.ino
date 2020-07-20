 #include <avr/interrupt.h>
#include <avr/io.h>
#include<Servo.h>
Servo sL,sR,sC;
unsigned int angleL=90, angleR=30 ,angleC=25;
unsigned int i,k;
char temp;

#define InL1            4                       // motor pin 
#define InL2            2                       // motor pin  

#define InR1            8                       // motor pin
#define InR2            7                       // motor pin 

void motorStop()
{
    digitalWrite(InL1, LOW);
    digitalWrite(InL2, LOW);
    digitalWrite(InR1, LOW);
    digitalWrite(InR2, LOW);
}
void motorForwardL()  
{
    digitalWrite(InL1, LOW);
    digitalWrite(InL2, HIGH);
}
void motorReverseL() 
{
    digitalWrite(InL1, HIGH);
    digitalWrite(InL2, LOW);
}

void motorForwardR()
{
    digitalWrite(InR1, LOW);
    digitalWrite(InR2, HIGH);
}
void motorReverseR()  
{
    digitalWrite(InR1, HIGH);
    digitalWrite(InR2, LOW);
}


void armForwardR()
{
  k=angleR+5;
  if(k<=130)
  {
    for(i=angleR;i<=k;i++)
    { 
      sR.write(i);
       angleR=i;
      delay(15);    
    }
  }
}

void armReverseR()
{
  k=angleR-5;
  if(k>=50)
  {
    for(i=angleR;i>=k;i--)
    {
      sR.write(i);
      angleR=i;
      delay(15);
    } 
  }
}

void armUpL()
{
   for(i=angleL;i<=120;i++)
  {
    sL.write(i);
    angleL=i;
    delay(15);
  }  
}
void armDownL()
{
  for(i=angleL;i>=70;i--)
  {
    sL.write(i);
    angleL=i;
    delay(15);
  }
}

void clawOpen()
{
    for(i=angleC;i>=100;i--)
    {
      sC.write(i);
      angleC=i;
      delay(15);
    }
}
void clawClose()
{
    for(i=angleC;i<=150;i++)
    {
      sC.write(i);
      angleC=i;
      delay(15);
    }
}

void setup()
{
   sL.attach(3);
   sR.attach(6);
   sC.attach(10);
   pinMode(13, OUTPUT);
   digitalWrite(13, HIGH);
   pinMode(InL1, OUTPUT);
   pinMode(InL2, OUTPUT);
   pinMode(InR1, OUTPUT);
   pinMode(InR2, OUTPUT);
   pinMode(11, OUTPUT);
   digitalWrite(11, HIGH);
   pinMode(12, OUTPUT);
   digitalWrite(12, HIGH);
   delay(1000);
   digitalWrite(11, LOW);
   digitalWrite(12, LOW);
   UBRR0 = 103; // for configuring baud rate of 9600bps
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 
// Use 8-bit character sizes
   UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  
// Turn on the transmission, reception, and Receive interrupt     
   sei();// enable global interrupt
}

void loop()
{
 
  switch(temp)
  {
    case '0':  //FORWARD
    motorForwardR();
    motorForwardL();
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    break;

    case '1':  //REVERSE
    motorReverseR();
    motorReverseL();
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    break;

    case '2':  //RIGHT
    motorReverseR();
    motorForwardL();
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    break;

    case '3':  //LEFT
    motorReverseL();
    motorForwardR();
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    break;

    case '4':  //ARM FORWARD
    armForwardR();
    motorStop();
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    break;

    case '5':  //ARM REVERSE
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    motorStop();
    armReverseR();
    break;

    case '6':   //ARM UP
    armUpL();
    motorStop();
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    break;

    case '7':   //ARM DOWN
    motorStop();
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    armDownL();
    break;

    case '8':   //CLAW OPEN
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    clawOpen();
    motorStop();
    break;
    
    case '9':   //CLAW CLOSE
    clawClose();
    motorStop();
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);    
    break; 
  }
}


ISR(USART_RX_vect)
{ 
  temp=UDR0;// read the received data byte in temp
}
