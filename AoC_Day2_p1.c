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
  int c,min,max,sum=0;

  fseek(fp,0,SEEK_SET);
  while((getline(&lineptr,&n,fp))+1)
    {
      lp=lineptr;
      /*first*/
      c=strtol(lp,&lp,0);
      /*second*/
      min=strtol(lp,&lp,0);
      /*compare*/
      if(c>min)
	max=c;
      else
	{max=min;min=c;}
      /**/
      while(c=strtol(lp,&lp,0))
	{
	  if(c>max)
	    max=c;
	  else if(c<min)
	    min=c;
	}
      sum+=(max-min);
      printf("%i-%i=%i\n",max,min,max-min);
    }
  printf("\n%i\n",sum);
  printf("test:%i,%i",2%8,8%2);
  /**/
  return 0;
}

int check_even_div(char * lineptr)
{
  
}
