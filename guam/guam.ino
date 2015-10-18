#include <AFMotor.h>
#include <Servo.h> =

AF_DCMotor motor1(1,MOTOR12_8KHZ);
AF_DCMotor motor2(2,MOTOR12_8KHZ);

Servo servo;


void setSpeed(int spd)
{
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
}

void stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);  
}

void left()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void right()
{
  motor2.run(FORWARD);
  motor1.run(BACKWARD);
}

void setup()
{
  servo.attach(10);
  stop();
  setSpeed(150);
}

void loop()
{
  int incr = - 30;
  int deg = 0;
  int loop_cnt = 0;
  while(true)
  {
    servo.write(deg);
    delay(70);
    if(abs(deg)>140)
    {
      incr = -incr;
      loop_cnt++;
      switch(loop_cnt%6)
      {
        case 0:
        case 1:
        case 2:
          stop();
          break;
        case 3:
          left();
          break;
        case 4:
          stop();
          break;
        case 5:
          right();
          break;
      }
    }
    deg = deg + incr;
  }
}
