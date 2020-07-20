 #include <avr/interrupt.h>
#include <avr/io.h>
char temp;

#define InL1            2                      // motor pin 
#define InL2            4                      // motor pin  

#define InR1            8                       // motor pin
#define InR2            7                       // motor pin 

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


void setup()
{
   pinMode(InL1, OUTPUT);
   pinMode(InL2, OUTPUT);
   pinMode(InR1, OUTPUT);
   pinMode(InR2, OUTPUT);
   for(int i=90;i>=30;i--)
  {
    delay(15);
  }
   pinMode(13, OUTPUT);  // configuring pin 13 as output
   UBRR0 = 103; // for configuring baud rate of 9600bps
   UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 
// Use 8-bit character sizes
   UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  
// Turn on the transmission, reception, and Receive interrupt     
   sei();// enable global interrupt
}

void loop()
{

 motorForwardR();
 motorForwardL();
 delay(3000);
 
 motorReverseR();
 motorReverseL();
 delay(3000);

 motorForwardL();
 motorReverseR();
 delay(3000);

 motorForwardR();
 motorReverseL();
 delay(3000);

 motorForwardR();
 motorReverseL();
 delay(3000);
 
 motorForwardL();
 motorReverseR();
 delay(3000); 
}




ISR(USART_RX_vect)
{ 
  temp=UDR0;// read the received data byte in temp
}
