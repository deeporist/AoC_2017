#include <stdio.h>

int main()
{
  /*square 1 is at (0,0)*/
  /*order is: right, up, left, down*/
  int number;
  int x,y;
  int line;
  int buffer[101][101]={0};
  /**/
  number=1;
  x=y=50;/*init coord*/
  buffer[50][50]=1;
  line=1;
  int i=0;
  while(number<289326)
    {
      /*right*/
      for(i=0;i<line;i++)
	{
	  x++;
	  number=buffer[x][y]=buffer[x-1][y]+buffer[x-1][y+1]+buffer[x][y+1]+buffer[x+1][y+1];
	  printf("(%i,%i)@%i\n",x,y,number);
	}
      /*up*/
      for(i=0;i<line;i++)
	{
	  y++;
	  number=buffer[x][y]=buffer[x-1][y+1]+buffer[x-1][y]+buffer[x-1][y-1]+buffer[x][y-1];
	  printf("(%i,%i)@%i\n",x,y,number);
	}
      line++;
      /*left*/
      for(i=0;i<line;i++)
	{
	  x--;
	  number=buffer[x][y]=buffer[x-1][y-1]+buffer[x][y-1]+buffer[x+1][y-1]+buffer[x+1][y];
	  printf("(%i,%i)@%i\n",x,y,number);
	}
      /*down*/
      for(i=0;i<line;i++)
	{
	  y--;
	  number=buffer[x][y]=buffer[x][y+1]+buffer[x+1][y+1]+buffer[x+1][y]+buffer[x+1][y-1];
	  printf("(%i,%i)@%i\n",x,y,number);
	}
      line++;
    }
  printf("@%i:(%i,%i)@%i",number,x,y,line);
  /**/
  return 0;
}
