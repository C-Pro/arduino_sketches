#include <scanner.h>
#include <AFMotor.h>
#include <Servo.h>

/*
Simple obstacle avoiding robot
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
Scanner scan(HEAD_STEP);

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

void turn(int deg)
{
    scan.rotate(deg);
    if(deg>0)
   {
     motor1.run(FORWARD);
     motor2.run(BACKWARD);
   } else
   {
     motor1.run(BACKWARD);
     motor2.run(FORWARD);
   }
   //robot turns 261 degrees
   //per second on speed 200
   //with opposite motor directions
   Serial.write("Turning ");
   Serial.print(deg);
   Serial.write(" deg. (");
   Serial.print(((abs(deg)*100/TURN_SPEED))*10);
   Serial.println(" ms.)");
   delay(((abs(deg)*100/TURN_SPEED))*10);
}

void forward(int time)
{
  scan.forward((time * 38)/1000);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  Serial.write("Forward ");
  Serial.print(time);
  Serial.println("ms.");
  delay(time);
}

void backward(int time)
{
  scan.forward(-(time * 38)/1000);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  Serial.write("Backward ");
  Serial.print(time);
  Serial.println("ms.");
  delay(time);
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
  Serial.write("Scan[");
  Serial.print(head_deg);
  Serial.write("] = ");
  Serial.println(dist);
  
  scan.set_distance(head_deg,dist);
  if(head_deg >= 180 ||
     head_deg <= 0)
     head_dir = -head_dir;
   head_deg = head_deg + head_dir;
   servo.write(head_deg);
   delay(10);
}

void loop() {
  int dir;
  int dist = 100;
  int stuck_cnt = 0;
  int head_dir = HEAD_STEP;
  int head_deg = CENTER;
  set_speed(SPEED,SPEED);
  
  
  while (true)
  {      
    turn_head(head_dir, head_deg);
    dist = scan.get_distance(90);
    
    //why not to blink some leds?
    if(dist > 50)
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
    
    if (dist < TURN_DISTANCE)
    {
       dir = scan.get_free_way();
       turn(-(dir - 90));
       stuck_cnt++;
    }    
    forward(10);
    
      
    //if we are stuck
    if(stuck_cnt > 20)
    {
       backward(500);
       turn(180);
       stuck_cnt = 0;
    }
    
    if (Serial.peek() != -1) {
      Serial.print("Read: ");
      do {
        Serial.print((char) Serial.read());
      } while (Serial.peek() != -1);
      Serial.print("\n");
    }
    
  } 
}
