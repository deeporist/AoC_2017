#include <stdio.h>
#include <stdlib.h>

#define times 50000000
#define steps 329


int main(void)
{
  unsigned int t,s;
  unsigned int list_len;
  unsigned int value_after_zero;
  /*------------------------------*/  
  list_len=1;
  s=0;
  for(t=0;t<times;t++)
    {
      s=(s+steps) % list_len;

      if(s==0)
	{
	  value_after_zero=t+1;
	  printf("%u\n",value_after_zero);
	}

      list_len++;
      s++;
      
    }
  /*------------------------------*/
  printf("%u",value_after_zero);
  /*------------------------------*/
  return 0;
}
