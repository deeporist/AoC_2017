#include <stdio.h>
#include <string.h>

int main(void)
{
  int a,b,c,i,f;
  long int x,p;
  int buf1[127]={0};
  int buf2[127]={0};
  int * bp1;
  int * bp2;

  i=31;
  x=1;
  while(i>0)
    {
      x*=2;
      i--;
    }
  printf("%ld %ld %ld %ld\n",sizeof(char),sizeof(int),x,sizeof(buf1));

  x-=1;
  i=127;
  p=316;
  c=0;
  bp1=buf1;
  while(i>0)
    {
      p*=8505;
      p%=x;
      p*=129749;
      p+=12345;
      p%=x;
      b=p;
      b%=10000;
      (*bp1++)=b;
      c++;
      i--;
    }
  
  for(bp1=buf1,b=0;b<127;b++,printf("%d ",*bp1++));
  printf("\n%d",c);

  p=0;
 label1:
  f=0;
  bp1=buf1;
  bp2=buf2;
  i=126;
  
  a=(*bp1++);
  
  while(i>0)
    {      
      b=(*bp1++);
      
      if(a<b)
	{*bp2++=b;f=1;}
      else
	{*bp2++=a;a=b;}
      i--;
      c++;
    }
  
  *bp2=a;c++;/*smallest*/
  memcpy(buf1,buf2,sizeof(buf1));
  memset(buf2,0,sizeof(buf2));

  if(f>0)
    {p++;goto label1;}

  /*
  printf("\n\n");
  for(bp1=buf1,b=0;b<127;b++,printf("%d ",*bp1++));
  */

  printf("\n%ld %d",p,c);
  
  /*------------------------------*/
  return 0;
}

  /*
  for(b=0;b<127;b++)
    {
      for(bp=buf1,c=1;c<(127-b);c++,bp++)
	{
	  if(*bp<*(bp+1))
	    {
	      (*bp)^=(*(bp+1));
	      (*(bp+1))^=(*bp);
	      (*bp)^=(*(bp+1));
	    }
	}
    }
  for(bp=buf1,b=0;b<127;b++,printf("%d ",*bp++));
  */
