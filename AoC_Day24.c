#include <stdio.h>
#include <stdlib.h>

int comps[55][3]={0};/*port1 port2 sum*/
int i,f,sum,l;
int stack[55]={0};

int print_comp(int);
int tempt_search(int);
int noin_stack(int);
void stack2comps();
void pops();
void pushs();

int main(void)
{
  FILE * fp;
  int a,b,c,d;
  char s[7]={0};
  /*------------------------------*/
  if((fp=fopen("Day24.txt","r"))==NULL)
    printf("file open failed");
  d=c=a=0;
  while((c=fgetc(fp))!=EOF)
    {
      b=0;
      while(c!=0xa)
	{
	  s[b++]=c;
	  if(c=='/')
	    d=b;
	  c=fgetc(fp);
	}
      comps[a][0]=strtol(s,(char **)NULL,10);
      comps[a][1]=strtol(&s[d],(char **)NULL,10);
      a++;      
    }
  fclose(fp);
  /*------------------------------*/
  for(a=0;a<55;a++)
    {
      comps[a][2]=comps[a][0]+comps[a][1];
    }
  /*------------------------------*/
  l=i=f=sum=0;
  tempt_search(0);
  printf("\n%u %u",l,sum);
  /*------------------------------*/
  return 0;
}

int tempt_search(int curr_pin)
{
  int n;
  for(n=0;n<55;n++)
    {
      if(comps[n][0]==curr_pin && noin_stack(n)!=0)
	{
	  f=1;
	  stack[i++]=n;
	  tempt_search(comps[n][1]);
	}
      else if(comps[n][1]==curr_pin && noin_stack(n)!=0)
	{
	  f=1;
	  stack[i++]=n;
	  tempt_search(comps[n][0]);
	}
    }
  if(f==1)
    {
      stack2comps();
    }
  f=0;
  i--;
  return 0;
}

void stack2comps()
{
  int n,s,y;
  s=0;
  
  for(n=0;n<i;n++)
    {
      y=stack[n];
      /*printf("%u ",y);*/
      s+=comps[y][2];
    }
  if(i>l)l=i;
  if(s>sum)
    sum=s;
  printf("%u %u\n",i,s);
}

int noin_stack(int n)
{
  int m;
  for(m=0;m<=i;m++)
    {if(stack[m]==n)return 0;}
  return 1;
}

void pushs(int n)
{
  stack[i++]=n;
}

void pops()
{i--;}

int print_comp(int n)
{  
  printf("%u ",n);
  return 0;
}
