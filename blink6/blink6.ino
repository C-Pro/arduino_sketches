/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  { 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  analogWrite(8, brightness%256);
  analogWrite(9, (brightness+42)%256);
  analogWrite(10, (brightness+84)%256);
  analogWrite(11, (brightness+126)%256);
  analogWrite(12, (brightness+168)%256);
  analogWrite(13, (brightness+210)%256);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(10);
  Serial.print(brightness%256);  
}

