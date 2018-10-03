#include <stdio.h>
#include <string.h>

#define ll 18

int defset[ll]={'s','t','p','z','c','r','n','m','-',0,0,0,0,0,0,0,0,0};
int length[ll]={0};
int hashlist[256]={0};
int testlength[]={'f','l','q','r','g','n','k','x','-',0,0,0,0,0,0,0,0,0};
int hexbin(int b,unsigned char i);
int cnthex(int s,unsigned char n);

int main(void)
{  
  int i,t;  
  void fill_length(int *,int);
  int knothash(int *);
  /*------------------------------*/
  /*stpzcrnm-0 --- stpzcrnm-127*/
  t=0;
  for(i=0;i<128;i++)
    {
      fill_length(defset,i);
      t+=knothash(length);
    }
  printf("%d\n",t);
  /*------------------------------*/
  /*
  fill_length(120);
  knothash(testlength);
  */
  /*------------------------------*/
  /*
  t=0;
  hexbin(8,(unsigned char)145);
  t=cnthex(t,(unsigned char)145);
  printf("\n%d",t);
  */
  /*------------------------------*/
  return 0;
}

void fill_length(int * defset,int i)
{
  memcpy(length,defset,sizeof(int)*ll);/*sizeof(char)==1*/
  /*length[9]-length[11]*/
  /*48-57*/
  int t=0;
  int * p1=&length[9];

  do
    {
      *(p1+2)=*(p1+1);
      *(p1+1)=*p1;
      *p1=(i%10)+48;
      i/=10;
      t++;
    }
  while((i/10)+(i%10));
  
  p1+=t;
  
  *(p1++)=17;
  *(p1++)=31;
  *(p1++)=73;
  *(p1++)=47;
  *(p1++)=23;
  
}

int knothash(int * ad)
{
  int rn;/*64 round*/
  int cp,ucp;/*current position*/
  int skip,len;
  int t;
  int * p;
  for(t=0;t<256;t++){hashlist[t]=t;}
  /*------------------------------*/
  skip=cp=0;
  for(rn=0;rn<64;rn++)
    {
      for(p=ad;(*p)!=0;p++)
	{
	  ucp=cp;
	  len=(*p)-1;
	  while(len>0)
	    {
	      ucp=ucp%256;

	      t=hashlist[ucp];
	      hashlist[ucp]=hashlist[(ucp+len)%256];
	      hashlist[(ucp+len)%256]=t;

	      ucp++;
	      len-=2;
	    }
	  cp+=(*p+skip);
	  skip++;
	}
    }
  /*------------------------------*/
  /*16 (0-255(FF))s xor each other*/
  rn=0;
  for(cp=0;cp<256;)
    {
      p=&hashlist[cp];
      for(t=*p++,len=0;len<15;len++)
	{t^=*p++;}
      
      cp+=16;
      /*printf("%02x",t);*/
      rn=cnthex(rn,(unsigned char)t);
    }
  /*printf("\n");*/
  /*------------------------------*/
  return rn;
}

int hexbin(int b,unsigned char i)
{
  if(b<1)
    return 0;  
  hexbin(b-1,i>>1);
  printf("%d",i&1);
  return 0;
}

int cnthex(int s,unsigned char n)
{
  int c;
  for(c=0;c<8;c++)
    {
      s+=(n&1);
      n=n>>1;
    }
  return s;
}
