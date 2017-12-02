#include <stdio.h>
#include <stdlib.h>

char line[80];

int main(void)
{
  FILE * fp;
  int hasa(char *);
  int result=0;
  
  fp = fopen("Day2.txt", "r");
  if (fp==NULL) exit(EXIT_FAILURE);

  while((fgets(line,80,fp))!=NULL)
    {
      printf("%i\n",result+=hasa(line));
      printf("%s\n",line);      
    }

  fclose(fp);  
  
  return 0;
}

int hasa(char * p)
{
  int n=0,max=0,min=0,tmp=0;
  char num[5];

  while(*p!=0xa)
    {     
      if(*p==0x9 || *p==0xd)
	{
	  num[n]='\n';
	  if(tmp==0)
	    tmp=max=min=atoi(num);
	  else
	    {
	      tmp=atoi(num);
	      if(tmp<min) min=tmp;
	      if(tmp>max) max=tmp;
	    }
	  n=0;
	}
      else
	{
	  num[n++]=*p;
	}
      p++;
    }

  
  return max-min;
}
