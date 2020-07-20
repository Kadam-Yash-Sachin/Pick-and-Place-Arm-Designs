#include <avr/io.h>
#include <avr/interrupt.h>
#include<Servo.h>
#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
unsigned int u8TempData;
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

void USART2Init(void)
{
  // Set baud rate
  UCSR2A = 0x00; //Clear send and receive flags
  UBRR2H = (uint8_t)(UBRR_VALUE >> 8);
  UBRR2L = (uint8_t)UBRR_VALUE;
  // Set frame format to 8 data bits, no parity, 1 stop bit
  UCSR2C |= (1 << UCSZ20) | (1 << UCSZ21);
  //enable transmission and reception
  //UCSR1C = (1<<URSEL1)|(3<<UCSZ0);
  UCSR2B |= (1<<RXEN2)|(1<<TXEN2)|(1<<RXCIE2);;
}


ISR(USART2_RX_vect)
{
  Serial.println("receive interrupt occur");
  while (!(UCSR2A & (1 << RXC2))) {};
  temp = UDR2; // Fetch the received byte value into the variable "ByteReceived"
  UDR2 = temp; // Echo back the received byte back to the computer
}

void setup ()
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
  noInterrupts();     
  pinMode(16,INPUT);
  pinMode(17,OUTPUT);

  //Initialize USART0
   USART2Init();
  //sei();
   interrupts();       

  Serial.begin(9600);

  Serial.print("123");
  //delay(100);
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
