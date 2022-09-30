#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,13); //instead of tx and rx in arduino

int trigPin = A0;    // Trigger
int echoPin = A1;    // Echo
long cm, inches;
#define leftIn1 11
#define leftIn2 10
#define rightIn1 6
#define rightIn2 4
#define enLeft 5
#define enRight 3 
char reading;
long duration, distance;

void setup()
{Serial.begin(9600);//for serial monitor
 mySerial.begin(9600);//for bluetooth connection

 pinMode(leftIn1,OUTPUT);
 pinMode(leftIn2,OUTPUT);
 pinMode(rightIn1,OUTPUT);
 pinMode(rightIn2,OUTPUT);
 pinMode(enLeft,OUTPUT);
 pinMode(enRight,OUTPUT);
 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
}

void loop()
{
  digitalWrite(trigPin,LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    duration=pulseIn(echoPin,HIGH);
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343 which is sound velocity

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
   Serial.println(distance);
  if(mySerial.available()>0)//when bluetooth sends data
  {
    

    reading=mySerial.read();
    switch(reading)  //bluetooth app sends only one letter
    {
      case 'F'://F to move car forward
         if(distance>30){       
        digitalWrite(leftIn1,HIGH);        //both motors rotate counter clockwise
        digitalWrite(rightIn1,HIGH);
        digitalWrite(leftIn2,LOW);
        digitalWrite(rightIn2,LOW);
        analogWrite(enLeft,255);
        analogWrite(enRight,255);}
        break;
      case 'B'://B to move car backward
        digitalWrite(leftIn1,LOW);
        digitalWrite(rightIn1,LOW);
        digitalWrite(leftIn2,HIGH);  //both motors rotate clockwise
        digitalWrite(rightIn2,HIGH);
        analogWrite(enLeft,255);
        analogWrite(enRight,255);
        break;
      case 'L'://L to rotate car left
        digitalWrite(leftIn1,LOW);    //right motor is on and the left motor is off
        digitalWrite(rightIn1,HIGH);
        digitalWrite(leftIn2,LOW);
        digitalWrite(rightIn2,LOW);
        analogWrite(enLeft,0);
        analogWrite(enRight,255);
         break;
      case 'R'://R to rotate car right
        digitalWrite(leftIn1,HIGH);
        digitalWrite(rightIn1,LOW);  //left motor is on and the right motor is off
        digitalWrite(leftIn2,LOW);
        digitalWrite(rightIn2,LOW);
        analogWrite(enLeft,255);
        analogWrite(enRight,0);
          break;
        default:
          analogWrite(enLeft,0);  //to stop all motors after button release
           analogWrite(enRight,0);

        
    }
  }

}
