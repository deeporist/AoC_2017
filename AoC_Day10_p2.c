#include <stdio.h>

int main(void)
{
  FILE * fp;
  int list[256]={0};
  int length[57]={0};
  int testlength[]={49,44,50,44,51,17,31,73,47,23};
  int n;
  char c;
  
  /*---------initial list-----------*/
  n=0;
  while(n<256)/*0-255*/
    {list[n]=n;n++;}
  /*---------fill length-----------*/
  if((fp=fopen("Day10.txt","r")) == NULL)
    printf("fail\n");
  /*------------------------------*/
  n=0;
  while((c=fgetc(fp))!=EOF)
    {      
      length[n++]=c;/*treate as ascii code*/
    }
  length[n++]=17;
  length[n++]=31;
  length[n++]=73;
  length[n++]=47;
  length[n++]=23;
  printf("%u\n",n);
    fclose(fp);
  /*---------hash test-----------*/
  n=0;/*location in length*/
  int en=0;/*round*/
  int skip=0;
  int len=0;/*reserve length*/
  int cp=0;/*current position in list*/
  int ucp=0;
  int t=0;
 
  for(en=0;en<64;en++)/*0-63*/
    {      
      for(n=0;n<57;n++)/*0-9 testlength*/
	{
	  ucp=cp;
	  len=length[n]-1;/*get length*/
	  
	  while(!(len<0))
	    {
	      ucp=ucp%256;/*circurment in 256*/
	      /*twist*/
	      t=list[ucp];
	      list[ucp]=list[(ucp+len)%256];
	      list[(ucp+len)%256]=t;
	      /*----------*/
	      ucp++;
	      len=len-2;
	    }
	  
	  cp=cp+skip+length[n];
	  skip++;	   
	}      
    }
  printf("%u\n",en);
  /*--------XOR------------*/
  n=0;
  while(n<255)/*0-15*/
    {
      skip=1;
      while(skip<16)/*1-15*/
	{
	  list[n]=list[n]^list[n+skip];
	  skip++;
	}
      printf("%02x",list[n]);
      n=n+16;
    }    

  /*--------------------*/


  return 0;
}
