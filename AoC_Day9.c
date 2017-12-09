#include <stdio.h>

char * o;

int main(void)
{
  FILE * fp;
  char c;
  char a[8260]={0};
  char * p;
  int n,f;  
  int test(int);
  int lr;
    
  if((fp=fopen("Day9.txt","r")) == NULL)
    printf("file open failed\n");

  /*----------parse '!' rule----------*/  
  n=0;
  f=0;
  while((c=fgetc(fp))!=EOF)
    {   
      if(f!=1 && c==0x21)/*no.1 '!'*/
	{f=1;}/*flag*/
      else if(f==1)/*!(!), X(X), !(X)*/
	{f=0;}/*ignore char after '!'*/
      else/*not '!' or after it*/
	{	  
	  a[n++]=c;
	}
    }
  a[n]='\n';
  printf("%u\n",n);
  /*----------statics garbage----------*/
  lr=0;
  n=0;
  while(a[n]!=0xa)
    {
      if(a[n]=='<')
	{
	  n++;
	  while(a[n]!='>' && a[n]!=0xa)
	    {lr++;n++;}
	}
      if(a[n]=='\n')
	break;
      n++;
    }
  printf("%u\n",lr);
  /*-------parse '<>' rule-------------*/
  n=0;
  f=0;
  p=a;
  lr=0;
  while(a[n]!=0xa)
    {
      if(a[n]=='<')
	{
	  while(a[n]!='>')
	    {a[n++]=0x20;}
	  a[n++]=0x20;
	}
      *p=a[n++];
      p++;
    }
  *p=0;
  /*printf("%s\n\n",a);*/
  /*----------test recursive----------*/
  char b[7]="{{{}}}";
  b[6]=0;
  p=b;
  n=0;
  lr=0;
  while(*p!=0)
    {
      if(*p=='{')
	lr++;
      else if(*p=='}')
	{
	  n+=lr;
	  lr--;
	}
      p++;
    }
  printf("%u\n",n);
  /*---------parse {} rule---------------------*/
  p=a;
  n=0;
  lr=0;
  while(*p!=0)
    {
      if(*p=='{')
	lr++;
      else if(*p=='}')
	{
	  n+=lr;
	  lr--;
	}
      p++;
    }
  printf("%u\n",n);
  /*--------------------------------------------------*/
  fclose(fp);
  return 0;
}

int test(int n)
{
  if(n==0)
    return 0;
  else
    test(--n);
  return n;
}
