#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE * fp;
  if((fp=fopen("Day2.txt","r"))==NULL)
    printf("file open failed");
  /**/
  char * lineptr=NULL;
  size_t n=0;
  char * lp;
  int c,sum=0;
  int check_even_div(int n,char * lineptr);

  fseek(fp,0,SEEK_SET);
  while((getline(&lineptr,&n,fp))+1)
    {
      lp=lineptr;
      while(c=strtol(lp,&lp,0))
	{
	  c=check_even_div(c,lp);
	  if(c)
	    break;
	}
      sum+=c;
      /*next line*/
    }
  printf("\n%i\n",sum);

  /**/
  return 0;
}

int check_even_div(int n,char * lp)
{
  int c,min,max;
  while(c=strtol(lp,&lp,0))
    {
      if(c<n)
	{min=c;max=n;}
      else
	{max=c;min=n;}
      
      if(max%min)
	;
      else
	{
	  printf("%i/%i=%i\n",max,min,max/min);
	  return max/min;
	}
    }
  return 0;
}
