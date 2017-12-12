#include <stdio.h>

int main(void)
{
  FILE * fp;
  int list[256]={0};
  int length[57]={0};
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
      length[n++]=c;
    }
  length[n++]=17;
  length[n++]=31;
  length[n++]=73;
  length[n++]=47;
  length[n++]=23;
  printf("%u\n",n);
  /*---------hash test-----------*/
  n=0;/*location in length*/
  int en=0;
  int skip=0;
  int len=0;/*reserve length*/
  int cp=0;/*current position in list*/
  int ucp=0;
  int t;
  /*
  int testlist[]={0,1,2,3,4};
  int testlength[]={3,4,1,5};
  */
  while(en<64)
    {n=0;
  while(n<57)
    {
      ucp=cp;
      len=length[n]-1;
      while(!(len<0))
	{
	  ucp=ucp%256;
	  t=list[ucp];
	  list[ucp]=list[(ucp+len)%256];
	  list[(ucp+len)%256]=t;
	  ucp++;
	  len=len-2;
	}
      cp=cp+skip+length[n];
      n++;
      skip++;
    }
  en++;
    }
  
  /*--------XOR------------*/
  n=0;
  
  while(n<16)/*0-15*/
    {
      skip=1;
      while(skip<16)/*1-15*/
	{
	  list[n]=list[n]^list[n+(skip*16)];
	  skip++;
	}
      printf("%02x ",list[n]);
      n++;
    }
  printf("\n\n%d",65 ^ 27 ^ 9 ^ 1 ^ 4 ^ 3 ^ 40 ^ 50 ^ 91 ^ 7 ^ 6 ^ 0 ^ 2 ^ 5 ^ 68 ^ 22);

  /*--------------------*/

  fclose(fp);
  return 0;
}
