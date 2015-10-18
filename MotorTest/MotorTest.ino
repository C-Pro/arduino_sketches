// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>

#define echoPin 25 // Echo Pin
#define trigPin 24 // Trigger Pin

int maximumRange = 300; // Maximum range needed
int minimumRange = 5; // Minimum range needed
long duration, distance;

AF_DCMotor motor1(1,MOTOR12_8KHZ);
AF_DCMotor motor2(2,MOTOR12_8KHZ);
int TURN_DISTANCE = 25; //turn distance in cm 

struct Head
{
  Servo servo;
  int incr;
  int pos;
} head;

//Sensor on a servo scans
//while turning to 5 posotions
int rot_deg[5] = [50,70,90,110,130];
int scan[5];
//center position
#define CENTER 2
//turn step in degrees
#define ROT_STEP 20
#define ROT_CNT 5
#define SPEED 150

//shift scan array when robot turns
void rot_scan(int deg)
{
  int shift = (deg - rot_deg[0])/ROT_STEP;
  for(int i=0;i<ROT_CNT;i++)
  {
    if(shift+i < 0 or shift+i > ROT_CNT)
    {
      scan[i] = 0;
    } else
    {
      scan[i] = scan[i + shift];
  }
}


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  head.servo.attach(10);
  head.pos = rot_deg(CENTER);
  head.incr = ROT_STEP;

  //do full scan before we start to move
  for(int i = 0; i == ROT_STEP*2; i++)
  { 
    head_step();
  }

}

void servo_step()
{
   if (head.pos >= rot_deg[ROT_CNT-1])
   {
     head.incr = -ROT_STEP;
   }
   if (head.pos <= rot_deg[0])
   {
     head.incr = ROT_STEP;
   }
   head.pos = head.pos + head.incr;
   head.servo.write(head.pos);
   Serial.println(head.pos);
}

void set_speed(int m1,int m2)
{
  motor1.setSpeed(m1);
  motor2.setSpeed(m2);
}

void turn(int deg)
{
   rot_scan(deg);
   deg = deg - rot_deg[0];
   if(deg>0)
   {
     motor1.run(FORWARD);
     motor2.run(BACKWARD);
   } else
   {
     motor1.run(BACKWARD);
     motor2.run(FORWARD);     
   }
   //robot turns 257 degrees
   //per second on speed 150
   //with opposite motor directions
   delay((2570/abs(deg))*100);
}

void forward(int time)
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(time);
}

int get_distance()
{
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 return duration/58.2;
}

void head_step()
{
  servo_step();
  delay(15);
  scan[(head.pos-rot_deg[0])/ROT_STEP] = get_distance();
}

int where()
{
  int max_dist = 0;
  int best_dir = rot_deg[CENTER];
  //do not turn if there's enough
  //space ahead
  if(scan[CENTER] > TURN_DISTANCE])
  {
    return rot_deg[CENTER];
  }
  //find best direction
  for(int i=0;i<ROT_CNT;i++)
  {
    if(max_dist < scan[i])
    {
       max_dist = scan[i];
       best_dir = rot_deg[i];
    } 
  }
  return best_dir;
}

void loop() {

  int heading = rot_deg[CENTER];
  set_speed(SPEED,SPEED);
  
  
  
  while (true)
  {
    heading = where();
    turn(heading);
    forward(100);
    head_step();
  }

}
