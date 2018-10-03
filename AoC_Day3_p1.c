#include <stdio.h>

int main()
{
  /*square 1 is at (0,0)*/
  /*order is: right, up, left, down*/
  int number;
  int x,y;
  int line;
  /**/
  number=1;
  x=y=0;
  line=1;
  while(number<289326)
    {
      /*right*/
      if(number<289326)
	{
	  x=x+line;
	  number=number+line;
	}
      else
	{
	  printf("right");
	  break;
	}
      /*up*/
      if(number<289326)
	{
	  y=y+line;
	  number=number+line;
	  line++;
	}
      else
	{
	  printf("up");
	  break;
	}
      /*left*/
      if(number<289326)
	{
	  x=x-line;
	  number=number+line;
	}
      else
	{
	  printf("left");
	  break;
	}
      /*down*/
      if(number<289326)
	{
	  y=y-line;
	  number=number+line;
	  line++;
	}
      else
	{
	  printf("down");
	  break;
	}
    }
  printf("@%i:(%i,%i)@%i",number,x,y,line);
  /**/
  return 0;
}
