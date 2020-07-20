#include<Servo.h>
Servo sL,sR,sC;
void setup() {
  // put your setup code here, to run once:
   sL.attach(3);
   sR.attach(6);
   sC.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  for(i=70;i<=120;i++)
  {
    sL.write(i);
    delay(20);
  }
  for(i=120;i>=70;i--)
  {
    sL.write(i);
    delay(20);
  }

    for(i=25;i<=65;i++)
  {
    sC.write(i);
    delay(20);
  }
    for(i=65;i>=25;i--)
  {
    sC.write(i);
    delay(20);
  }

    for(i=50;i<=80;i++)
  {
    sR.write(i);
    delay(20);
  }

    for(i=80;i>=50;i--)
  {
    sR.write(i);
    delay(20);
  }

}
