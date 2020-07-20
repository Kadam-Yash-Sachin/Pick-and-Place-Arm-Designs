#include <Arduino.h>

unsigned char val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()==1)
  {
    val=Serial.read();
    Serial.print("val=");Serial.print(val);
    if(val==0x31)
    {
      Serial.println("Upwards");
    }
    else if(val==0x32)
    {
      Serial.println("Downwards");
    }
    }  
}
