#include <stdio.h>

#define times 5000000
unsigned int j,s;

int main(void)
{
  unsigned long int a,b,ta,tb,ra,rb;
  void chech(unsigned long int,unsigned long int);
  /*------------------------------*/
  j=s=0;
  a=116;
  b=299;  
  while(j<times)
    {
      ta=(a*16807)%2147483647;
      tb=(b*48271)%2147483647;

      ra=ta%4;
      rb=tb%8;

      if(ra==0 && rb==0)
	{
	  a=ta;
	  b=tb;
	  chech(ta,tb);
	}
      else if(ra==0 && !(rb==0))
	{b=tb;}
      else if(!(ra==0) && rb==0)
	{a=ta;}
      else/*ra!=0 && rb!=0*/
	{a=ta;b=tb;}
      
    }
  printf("%u\n",s);
  /*------------------------------*/
  return 0;
}

void chech(unsigned long int ca,unsigned long int cb)
{
  ca=ca&0xffff;
  cb=cb&0xffff;
  if(!(ca^cb))s++;
  j++;
}
