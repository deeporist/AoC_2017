#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE * fp;
  if((fp=fopen("Day5.txt","r")) == NULL)
    printf("file open failed\n");

  char s[5];
  char c;
  char * sp=s;
  int l[1037]={0};
  int * lp;
  lp=l;
  while((c=fgetc(fp)) != EOF)
    {
      if(c==0xd)
	{
	  *sp=fgetc(fp);
	  sp=s;
	  printf("%i ",*lp=atoi(s));
	  lp++;
	}
      else
	{
	  *sp=c;
	  sp++;
	}
    }
  *sp=0xa;
  *lp=atoi(s);
  lp++;
  
  fclose(fp);

  printf("\n%i %li\n",*(lp-1),lp-l);

  int testa[5]={0,3,0,1,-3};
  lp=l;
  int * tlp;
   int sn=0;
  while((lp-l)<1037 && (lp-l)>=0)
    {
      tlp=lp;
      lp=lp+(*lp);
      if((*tlp)>=3)
	(*tlp)--;
      else
	(*tlp)++;
      sn++;
    }
  printf("\n%i",sn);
  
  return 0;
}
