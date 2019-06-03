/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/
/* Edited the code for Gesture Controlled Robot by PradeeshJ. First Edit :03/June/19
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch and Roll values
float pitch = 0;
float roll = 0;
//motor control output pins
int motorL1 = 10; // left motor 1
int motorL2 = 11; // left motor 2
int motorR1 = 12; // right motor 1
int motorR2 = 13; // right motor 2

void setup() 
{
  Serial.begin(9600);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
  pinMode(motorL1,OUTPUT);
  pinMode(motorL2,OUTPUT);
  pinMode(motorR1,OUTPUT);
  pinMode(motorR2,OUTPUT);
}

void loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch and Roll
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
  //forward
  if ( pitch>12 && pitch<90)
   {
    digitalWrite(motorL1,HIGH);
    digitalWrite(motorL2,LOW);
    digitalWrite(motorR1,HIGH);
    digitalWrite(motorR2,LOW);
   }
    else if(pitch>-82 && pitch<-15) //backward
    {
     digitalWrite(motorL1,LOW);
     digitalWrite(motorL2,HIGH);
     digitalWrite(motorR1,LOW);
     digitalWrite(motorR2,HIGH);
    }
  //right  
  if (roll>15 && roll<85)
   {
    digitalWrite(motorL1,HIGH);
    digitalWrite(motorL2,LOW);
    digitalWrite(motorR1,LOW);
    digitalWrite(motorR2,HIGH);
   }
   else if(roll>-90 && roll<-10) // left
    {
     digitalWrite(motorL1,LOW);
     digitalWrite(motorL2,HIGH);
     digitalWrite(motorR1,HIGH);
     digitalWrite(motorR2,LOW);
   } 
     
}
