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
  char head;
  int sum=0;
  
  getline(&lineptr,&n,fp);/*only one line*/
  lp=lineptr;
  head=*lp;
  while(*lp!=0)
    {
      if(*lp==*(lp+1))
	sum+=(*lp-48);
      lp++;
    }

  if(head==*(lp-1))
    sum+=(head-48);

  printf("%i\n",sum);
  /**/
  return 0;
}
