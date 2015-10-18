#include "scanner.h"

Scanner::Scanner(int step)
{
  init_data();
  calculate_boundary(step);
}

void Scanner::init_data()
{
for(int i=0;i<360;i++)
  scan_data[i]=-1;
}

void Scanner::calculate_boundary(int step)
{
  STEP = step;
  START = CENTER % step;
  END = ((360 - START) / step) * step + START;
}

int Scanner::get_start()
{
  return START;
}

int Scanner::get_end()
{
 return END;
}

int Scanner::normalize(int direction)
{
  direction = direction % 360;
  if (direction < 0)
    direction = 360 + direction;
  return direction;
}

void Scanner::set_distance(int direction,
                           int distance)
{
  direction = normalize(direction);
  if(direction >= 0 &&
     direction < 360)
     scan_data[direction] = distance;
}

int Scanner::get_distance(int direction)
{
  
  return scan_data[normalize(direction)];
}

void Scanner::rotate(int direction)
{
  int data2[360];
  for(int i=START;i<END;i = i + STEP)
    data2[i]=scan_data[(i-direction)%360];
  for(int i=START;i<END;i = i + STEP)
    scan_data[i] = data2[i];
}

void Scanner::forward(int distance)
{
  int k;
  for(int i=START;i<END;i = i + STEP)
  {
    if(0<=i && i<90)
      k = (100*i)/90;
    if(90<=i && i<180)
      k = (100*(180-i))/90;
    if(180<=i && i<270)
      k = -(100*(i-180))/90;
    if(270<=i && i<360)
      k = -(100*(360-i))/90;
    scan_data[i] = scan_data[i] - (distance*k)/100 ;
  }
}

int Scanner::get_median(int direction)
{
  int a = get_distance(direction - STEP);
  int b = get_distance(direction);
  int c = get_distance(direction + STEP);
  if (a >= b && a <= c || a <= b && a >= c) return a;
  if (b >= a && b <= c || b <= a && b >= c) return b;
  if (c >= a && c <= b || c <= a && c >= b) return c;
}

int Scanner::get_free_way()
{
  int max_med=0;
  int median;
  int direction = 180;
  for(int i=START;i<END;i = i + STEP)
  {
    median = get_median(i);
    if (median > max_med)
    {
      max_med = median;
      direction = i;
    }
  }
  return direction;
}
