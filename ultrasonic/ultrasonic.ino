/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 7 
 Trig to Arduino pin 8
 
 This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
 Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
 on 10 Nov 2012.
 */
#include <LiquidCrystal.h>
#include <LCDKeypad.h>

#define echoPin 25 // Echo Pin
#define trigPin 24 // Trigger Pin
//#define LEDPin 13 // Onboard LED
//#define m1  10

byte c_heart[8] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

LCDKeypad lcd;
int maximumRange = 400; // Maximum range    for(i=1;i++;i==16)needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int i;

void setup() {
 lcd.createChar(1,c_heart);
 lcd.begin(16, 2);
 lcd.clear();
 lcd.print("Waiting for you..."); 
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 //pinMode(m1, OUTPUT);
 pinMode(echoPin, INPUT);
 //pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 Serial.println(distance);
 
 if (distance >= 15 && distance <= 100){
   lcd.clear();
   for(i=1;i++;i==16)
     { lcd.write(1); } 
 } else
 {
   lcd.clear();
   lcd.print("Waiting for you...");
 }
 
 //Delay 50ms before next reading.
 delay(500);
}
