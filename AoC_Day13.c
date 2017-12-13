#include <stdio.h>

int main(void)
{
  FILE * fp;
  int test[7]={0};
  int rec[93]={0};
  int n,t;
  char c;
  /*--------------------*/
  if((fp=fopen("Day13_ex.txt","r")) == NULL)
    {printf("file open failed\n");return 1;}
  /*--------------------*/
  t=n=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==0xd)/*line end*/
	{
	  c=fgetc(fp);
	  rec[n]=t;
	  /*printf("%u\n",t);*/
	  t=0;
	  continue;
	}
      if(c==0x3a)/*:*/
	{
	  n=t;
	  t=0;
	  /*printf("%u:",n);*/
	  continue;
	}
      
      t=(t*10)+(c^(0x30));
    }
  rec[n]=t;
  printf("%u\n",n);
  /*--------------------*/
  n=t=0;
  /*step into 0(n=0) is step No.1*/
  /*step into 5(n=6) is step No.6*/
  while(n<93)
    {
      if(rec[n]==0)
	{n++;continue;}
      if(n%(2*rec[n]-2)==0)
	t=t+n*rec[n];
      n++;
    }
  printf("%u\n",t);

  /*--------------------*/
  n=t=0;
  while(t<100000000)
    {
      while(n<93)
	{
	  if((rec[n])==0)
	    {n++;continue;}
	  else if(((t+n)%((2*rec[n])-2))==0)
	    break;/*this t not satisfie*/
	  else
	    n++;
	}
      if(n>92)
	break;
      n=0;
      t++;
    }
  printf("%u",t);
  /*--------------------*/

  fclose(fp);
  return 0;
  
}
