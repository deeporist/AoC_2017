#include <stdio.h>
#include <ctype.h>

#define sca 203*201
#define testsca 18*6

#define row 18

int main(void)
{
  FILE * fp;
  int n,c,r;
  int mx[testsca]={0};
  int * p;
  /*------------------------------*/
  if((fp=fopen("Day19_test.txt","r")) == NULL)
    printf("open error\n");
  /*------------------------------*/
  /*
  r=n=c=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==0xd)
	{
	  r++;
	  printf("%u\n",n);
	  fgetc(stdin);
	}
      fputc(c,stdout);
      n++;
    }
  printf("\n%u %u",n,r);
  */
  /*this is a 201x201 matrix*/
  r=n=c=0;
  p=mx;
  while((c=fgetc(fp))!=EOF)
    {      
      *p++=c;	
    }
  /*--------------------*/
  
  p=mx;
  while(p!=(mx+testsca-1))
    {
      if(*p==0xd || *p==0xa)
	fputc(*p++,stdout);
      else
	printf("%x",*p++);
    }
  /*--------------------*/
  for(p=mx;p<(mx+testsca-1);p++)
    if(*p=='|')
      break;
  printf("\n");
  /*--------------------*/
  r=row;/*record direction:down-18, up-(-18), right-(1), left-(-1)*/
  c=1;
  while(p<(mx+testsca-1))
    {
      switch(*p)
	{
	case '|':
	  {c++;p=p+r;break;}
	case '-':
	  {c++;p=p+r;break;}
	case '+':
	  {
	    c++;
	    if(r==row || r==(-1)*row)
	      {
		if(*(p-1)!=0x20)
		  r=-1;
		else
		  r=1;
	      }
	    else if(r==1 || r==-1)
	      {
		if(*(p+row)!=0x20 && (p+row)<(mx+testsca-1))
		  r=row;
		else
		  r=(-1)*row;
	      }
	    p=p+r;
	    break;
	  }
	case 0x20:
	  {p=mx+testsca;break;}
	default:
	  {
	    c++;
	    if(isalpha(*p))
	      {fputc(*p,stdout);}
	    p=p+r;
	  }
	}
    }
  printf("\n%u\n",c);
  /*------------------------------*/
  return 0;
}
