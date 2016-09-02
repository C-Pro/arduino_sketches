#include <AFMotor.h>
#include <Servo.h>

/*
Control robot from Android phone via USB
by cpro29a@gmail.com

all distances are in cm
all angles are in degrees
*/

//Ultrasonic distance meter pins:
#define echoPin 25 // Echo Pin
#define trigPin 24 // Trigger Pin

#define ledPin 13
// Maximum measurable distance
#define maximumRange 300
// Minimum measurable distance
#define minimumRange 5


#define TURN_DISTANCE 30 
#define CENTER 90
#define SPEED 200
#define TURN_SPEED 261
#define HEAD_STEP 20
AF_DCMotor motor1(1,MOTOR12_8KHZ);
AF_DCMotor motor2(2,MOTOR12_8KHZ); 

#define SERVO_PIN 10
Servo servo;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Begin");
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  servo.attach(SERVO_PIN);
  //center servo to align sensor
  servo.write(CENTER);
  Serial.println("Align sensor!");
  delay(5000);
}

void set_speed(int m1,int m2)
{
  //Not all motors are created equal
  motor1.setSpeed(m1-35);
  motor2.setSpeed(m2);
}

void right()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    set_speed(SPEED/2,SPEED/2)
}

void left()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    set_speed(SPEED/2,SPEED/2)
}

void forward()
{
  //scan.forward((time * 38)/1000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  set_speed(SPEED,SPEED)
}

void backward()
{
  //scan.forward(-(time * 38)/1000);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  set_speed(SPEED,SPEED)
}

void stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

int get_distance()
{
 long duration;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);

 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

 //Calculate the distance (in cm) based on the speed of sound.
 return duration/58;
}


void turn_head(int &head_dir,
               int &head_deg)
{
  int dist = get_distance();
  Serial.write("(");
  Serial.print(head_deg);
  Serial.write(",");
  Serial.print(dist);
  Serial.write(")");
  
  if(head_deg >= 180 ||
     head_deg <= 0)
     head_dir = -head_dir;
   head_deg = head_deg + head_dir;
   servo.write(head_deg);
}

void loop() {
  int head_dir = 30;
  int head_deg = 90;
  
  set_speed(SPEED,SPEED);  
  
  while (true)
  {
    turn_head(head_dir, head_deg);
    if (Serial.peek() != -1) {
      char cmd = Serial.read();
      switch (cmd) {
        case 'S':stop();
                 break;
        case 'F':forward();
                 break;
        case 'B':backward();
                 break;
        case 'L':left();
                 break;
        case 'R':right();
                 break; }
    }
    delay(30);   
  } 
}
