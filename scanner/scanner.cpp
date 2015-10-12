#include "scanner.h"

Scanner::Scanner()
{
for(int i=0;i<360;i++)
  scan_data[i]=-1;
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
  for(int i=0;i<360;i++)
    data2[i]=scan_data[(i-direction)%360];
  for(int i=0;i<360;i++)
    scan_data[i] = data2[i];
}

void Scanner::forward(int distance)
{
  int k;
  for(int i=0;i<360;i++)
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

int Scanner::get_free_way()
{
  int max_dist=0;
  int direction;
  for(int i=0;i<360;i++)
  {
    if (scan_data[i] > max_dist)
    {
      max_dist = scan_data[i];
      direction = i;
    }
  }
  return direction;
}