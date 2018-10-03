#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char mc[32][15]={0};
void print_mc(int);
void print_regs(void);

int esp;
long int regs[8]={0};/*a-h*/

int SET(long int * reg,long int * opr);
int SUB(long int * reg,long int * opr);
int MUL(long int * reg,long int * opr);
int JNZ(long int * reg,long int * opr);

int main(void)
{
  FILE * fp;
  
  long int a,b,c;
  long int * pa, * pb;
  /*------------------------------*/
  
  if((fp=fopen("Day23.txt","r"))==NULL)
    printf("file open failed");
  a=b=c=0;
  while((c=fgetc(fp))!=EOF)
    {
      mc[a][b++]=c;
      if(c==0xa)
	{
	  /*print_mc(a);*/
	  a++;
	  b=0;
	}      	
    }  
  fclose(fp);
  
  /*------------------------------*/
  /*
  for(a=0;a<32;a++)
    {
      if(!memcmp(mc[a],"set",3))
	printf("SET");
      else if(!memcmp(mc[a],"sub",3))
	printf("SUB");
      else if(!memcmp(mc[a],"mul",3))
	printf("MUL");
      else if(!memcmp(mc[a],"jnz",3))
	printf("JNZ");

      if((mc[a][6]<0x61)||(mc[a][6]>0x68))
	printf(" %ld\n",strtol(&mc[a][6],(char **)NULL,10));
      else
	printf(" %c\n",mc[a][6]);      
    }
  */
  /*------------------------------*/
  regs[0]=1;
  /*------------------------------*/
  int s=0;
  for(esp=0;esp<32 && s<51;s++)
    {
      if(esp<0 || esp>31)
	break;
      print_mc(esp);

      if((mc[esp][4]<97)||(mc[esp][4]>104))
	{a=strtol(&mc[esp][6],(char **)NULL,10);pa=&a;}
      else
	{c=mc[esp][4]-97;pa=&regs[c];}

      if((mc[esp][6]<97)||(mc[esp][6]>104))
	{b=strtol(&mc[esp][6],(char **)NULL,10);pb=&b;}
      else
	{c=mc[esp][6]-97;pb=&regs[c];}
	
      if(!memcmp(mc[esp],"set",3))
	{esp=SET(pa,pb);}
      else if(!memcmp(mc[esp],"sub",3))
	{esp=SUB(pa,pb);}
      else if(!memcmp(mc[esp],"mul",3))
	{esp=MUL(pa,pb);}
      else if(!memcmp(mc[esp],"jnz",3))
	{esp=JNZ(pa,pb);}

      print_regs();
    }
  printf("%ld",regs[7]);
  /*-----------PART 2-------------------*/
  c=0;
  for(a=106700;a<=123700;)
    {
      for(b=2;b!=a;b++)
	{
	  if(!(a%b))
	    {
	      c++;
	      break;
	    }
	}
      a=a+17;
    }
  printf("\n%ld",c);
  /*------------------------------*/
  return 0;
}

int SET(long int * reg,long int * opr)
{
  *reg=*opr;
  return esp+1;
}

int SUB(long int * reg,long int * opr)
{
  *reg=*reg-*opr;
  return esp+1;
}

int MUL(long int * reg,long int * opr)
{
  *reg=(*reg)*(*opr);
  return esp+1;
}

int JNZ(long int * reg,long int * opr)
{
  if(!(*reg==0))
    return esp+*opr;
  else
    return esp+1;
}

void print_mc(int n)
{
  int i;  
  for(i=0;i<15;i++)
    {
      fputc(mc[n][i],stdout);
    }
}

void print_regs(void)
{
  int i;
  for(i=0;i<8;i++)
    printf("%ld ",regs[i]);
  printf("\n");
}
