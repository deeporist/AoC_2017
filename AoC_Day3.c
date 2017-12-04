#include <stdio.h>

int main(void)
{
  int num=1,row=1,col=1;
  char dire='d';

  while(num<289326)
    {
      switch(dire)
	{
	case 'u':
	  dire='l';
	  num=num+col;
	  col++;
	  break;
	  
	case 'd':
	  dire='r';
	  num=num+col;
	  col++;
	  break;
	  
	case 'r':
	  dire='u';
	  num=num+row;
	  row++;
	  break;
	  
	case 'l':
	  dire='d';
	  num=num+row;
	  row++;
	  break;
	  
	default:
	  break;
	}
    }

  printf("%i %i %i %c",num,row,col,dire);

  if(dire=='l' || dire=='r')
    {}

  if(dire=='u'||dire=='d')
    {}



  return 0;
}
