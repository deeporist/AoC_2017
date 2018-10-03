#include <stdio.h>

int main()
{
  FILE * fp;
  if((fp=fopen("Day1.txt","r"))==NULL)
    printf("file open failed");
  /**/
  char * lineptr=NULL;
  size_t n=0;
  char * lp;
  int sum=0,count,step=0;
  
  getline(&lineptr,&n,fp);/*only one line*/
  
  /**/
  lp=lineptr;
  count=1;
  while(*lp!=0)
    {count++;lp++;}
  step=count/2;
  printf("step=%i\n",step);
  
  /**/
  lp=lineptr;
  sum=0;
  for(count=0;count<step;count++)
    {
      if(*lp==*(lp+step))
	sum+=(*lp-48);
      lp++;
    }
  printf("%i",sum*2);

  /**/
  return 0;
}
