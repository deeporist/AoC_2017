#include <stdio.h>

int main(void)
{
  FILE * fp;
  int list[256]={0};
  int length[16]={0};
  int n;
  char c;
  
  /*---------initial list-----------*/
  n=0;
  while(n<256)
    {list[n]=n;n++;}
  /*---------fill length-----------*/
  if((fp=fopen("Day10.txt","r")) == NULL)
    printf("fail\n");  
  n=0;
  while((c=fgetc(fp))!=EOF)
    {      
      if(c==0x2c)
	{n++;continue;}
      length[n]=length[n]*10+(c^(0x30));
    }  
  /*---------hash test-----------*/
  n=0;/*location in length*/
  int skip=0;
  int len=0;/*reserve length*/
  int cp=0;/*current position in list*/
  int ucp=0;
  int t;
  
  int testlist[]={0,1,2,3,4,5};
  int testlength[]={4,4,1,5};
  

  while(n<4)/*length*/
    {
      ucp=cp;
      len=testlength[n]-1;
      while(!(len<0))
	{
	  ucp=ucp%5;
	  t=testlist[ucp];
	  testlist[ucp]=testlist[(ucp+len)%5];
	  testlist[(ucp+len)%5]=t;
	  ucp++;
	  len=len-2;
	}
      cp=cp+skip+testlength[n];
      n++;
      skip++;
    }
  printf("%u %u %u %u %u\n",testlist[0],testlist[1],testlist[2],testlist[3],testlist[4]);
  printf("%u %u\n",cp%5,skip);
  /*--------------------*/

  fclose(fp);
  return 0;
}
