//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(12,13);

// C++ code
//#define trigPin A0
//#define echoPin A1
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
{Serial.begin(9600);
mySerial.begin(9600);

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
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
    distance =(duration/2)*0.0343;
   Serial.println(distance);
  if(mySerial.available()>0)
  {
    

    reading=mySerial.read();
    switch(reading)
    {
      case 'F':
         if(distance>30){
        digitalWrite(leftIn1,HIGH);
        digitalWrite(rightIn1,HIGH);
        digitalWrite(leftIn2,LOW);
        digitalWrite(rightIn2,LOW);
        analogWrite(enLeft,255);
        analogWrite(enRight,255);}
        break;
      case 'B':
        digitalWrite(leftIn1,LOW);
        digitalWrite(rightIn1,LOW);
        digitalWrite(leftIn2,HIGH);
        digitalWrite(rightIn2,HIGH);
        analogWrite(enLeft,255);
        analogWrite(enRight,255);
        break;
      case 'L':
        digitalWrite(leftIn1,LOW);
        digitalWrite(rightIn1,HIGH);
        digitalWrite(leftIn2,LOW);
        digitalWrite(rightIn2,LOW);
        analogWrite(enLeft,0);
        analogWrite(enRight,255);
         break;
      case 'R':
        digitalWrite(leftIn1,HIGH);
        digitalWrite(rightIn1,LOW);
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
  
  
 while(!digitalRead(forward)) //while button is low both motors rotate counter clockwise
 { delay(10);   // delay for debouncing
//  
//  
 }
 while(!digitalRead(backward))//while button is low both motors rotate clockwise
 { delay(10);

 }
  while(!digitalRead(rightRotate))//while button is low,left motor is on and the right motor is off
 { delay(10);

 }
  while(!digitalRead(leftRotate))//while button is low,right motor is on and the left motor is off
 { delay(10);

 }


 

}
