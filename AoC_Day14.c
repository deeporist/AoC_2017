#include <stdio.h>

int list[256]={0};
int length[17]={0};

unsigned short diks[256*256]={0};
int dn=0;
unsigned short pre,cur;

int s=0;
int knot_hash();
void chcek1(int);
void aoc14p2(void);
  
int main(void)
{
  FILE * fp;  
  int n;
  char c;
  int y=0;
  /*------------------------------*/
  if((fp=fopen("Day14.txt","r")) == NULL)
    printf("fail\n");
  /*------------------------------*/
  /*stpzcrnm-0 --- stpzcrnm-127*/
  /*------------------------------*/
  n=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==0xd)/*one line*/
	{
	  fgetc(fp);/*increase fp*/
	  /*pad extra lengths*/
	  length[n++]=17;
	  length[n++]=31;
	  length[n++]=73;
	  length[n++]=47;
	  length[n++]=23;
	  /*call knot_hash*/
	  printf("%u\n",y++);
	  knot_hash();
	  n=0;
	  continue;
	}
      length[n++]=c;/*treate as ascii code*/
    }
  length[n++]=17;/*127*/
  length[n++]=31;
  length[n++]=73;
  length[n++]=47;
  length[n++]=23;
  /*call knot_hash AoC_Day10_p2*/
  printf("%u\n",y++);
  knot_hash();
  aoc14p2();
  /*--------------------*/
  fclose(fp);
  return 0;
}

/*----------------------------------------*/

int knot_hash()
{  
  int n;  
  int en=0;/*round*/
  int skip=0;
  int len=0;/*reserve length*/
  int cp=0;/*current position in list*/
  int ucp=0;
  int t=0;
  /*---------initial list-----------*/
  n=0;
  while(n<256)/*0-255*/
    {list[n]=n;n++;}  
  
  /*---------knot hash-----------*/
  n=0;/*location in length*/
  for(en=0;en<64;en++)/*0-63*/
    {      
      for(n=0;n<17;n++)/*0-16*/
	{
	  if(length[n]==0)/*reach the array end*/
	    break;
	  
	  ucp=cp;
	  len=length[n]-1;/*get length*/
	  
	  while(!(len<0))
	    {
	      ucp=ucp%256;/*circurment in */
	      /*twist*/
	      t=list[ucp];
	      list[ucp]=list[(ucp+len)%256];
	      list[(ucp+len)%256]=t;
	      
	      ucp++;
	      len=len-2;
	    }
	  
	  cp=cp+skip+length[n];
	  skip++;	   
	}      
    }  
  /*--------XOR------------*/
  n=0;
  while(n<255)/*0-255*/
    {
      skip=1;
      while(skip<16)/*1-15*/
	{
	  list[n]=list[n]^list[n+skip];
	  skip++;
	}
      chcek1(list[n]);
      printf("%02x ",list[n]);
      n=n+16;
    }
  printf("\n%u\n",s);

  /*--------------------*/  
  return 0;
}

void chcek1(int n)
{
  int x;  
  unsigned short m=(unsigned short)n;
  for(x=0;x<8;x++)/*0-7*/
    {
      if(m & 1)/*most right is 1*/
	{
	  s++;/*used +1*/
	  diks[dn++]=1;
	}
      else
	dn++;/*jump over*/
      
      m = m >> 1;
	
    }
}

void aoc14p2(void)
{
  s=0;
  pre=cur=0;
  for(dn=0;dn<256*256;dn++)
    {
      pre=cur;cur=diks[dn];s++;
      
    }
}
