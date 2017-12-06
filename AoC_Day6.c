#include <stdio.h>
#include <memory.h>

int ln=0;/*how many records logged in nam or testm*/
int na[16]={0};
int * nap;
int nam[5000][16];

int test[]={0,2,7,0};
int testm[15][4]={0};

/*
#define rs 4
*/
#define rs 16

int main(void)
{
  FILE * fp;
  char c=0;
  int n=0;

  void lg(int (*)[rs],int *,int);  
  int comp(int (*)[rs],int *,int);
  void ncycleex(int *,int);
  void pna(int *,int);
  
  memset(nam,0,sizeof(nam));
  nap=na;
  
  if((fp=fopen("Day6.txt","r")) == NULL)
    printf("file open failed\n");
  
  while((c=fgetc(fp))!=EOF)
    {
      if(c==0x9)
	{
	  printf("%u ",n);
	  *nap=n;
	  nap++;
	  n=0;
	}
      else
	{
	  n=n*10+(c^(0x30));	  
	}
    }  
  printf("%u \n\n",n);
  *nap=n;
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
  while((comp(testm,test,rs))!=0 && ln<15)
    {
      pna(test,rs);
      lg(testm,test,rs);
      ncycleex(test,rs);
    }
  printf("\n%u\n",ln);
  pna(test,rs);

  ln=0;
  lg(testm,test,rs);
  ln=0;
  ncycleex(test,rs);
  int y=1;
  while((comp(testm,test,rs))!=0 && ln<15)
    {
      ncycleex(test,rs);
      y++;
    }
  printf("%u",y);
  
  ------------------------------*/
  while((comp(nam,na,rs))!=0 && ln<5000)
    {
      pna(na,rs);
      lg(nam,na,rs);
      ncycleex(na,rs);
    }
  printf("\n%u\n",ln);
  pna(na,rs);

  ln=0;
  lg(nam,na,rs);
  ln=0;
  ncycleex(na,rs);
  int y=1;
  while((comp(nam,na,rs))!=0 && ln<5000)
    {
      ncycleex(na,rs);
      y++;
    }
  printf("%u",y);

  /*------------------------------*/
  
  return 0;
}

/*----------------------------------------*/

void lg(int (*r)[rs],int * p,int c)
{
  int i;
  for(i=0;i<c;i++)
    {
      r[ln][i]=p[i];      
    }
  ln++;
}

int comp(int (*r)[rs],int * p,int c)
{/*compare p & r[]*/
  int t,i,e=1;
  for(t=0;t<=ln&&e!=0;t++)
    {
      for(i=0;i<c;i++)
	{
	  if(r[t][i]!=p[i])
	    {
	      e=1;
	      break;/*jump to next compare directly*/
	    }
	  else
	    e=0;/*remain after last compare*/
	}      
    }
  return e;
}

void ncycleex(int * p,int q)
{
  int max=0,i=0,w;

  for(i=0;i<q;i++)
    {
      if(p[i]>max)
	{max=p[i];w=i;}
    }

  p[w]=0;
  w++;
  if(!(w<q))w=0;

  for(;max>0;w++)
    {
      if(!(w<q))w=0;
      p[w]++;
      max--;
    }
  
}

void pna(int * p,int c)
{
  int i=0;
  for(i=0;i<c;i++)
    printf("%u ",p[i]);
  printf("\n");
}
