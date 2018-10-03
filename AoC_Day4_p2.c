#include <stdio.h>
#include <string.h>

int main()
{
  /*load file*/
  FILE * fp;
  if((fp=fopen("Day4.txt","r"))==NULL)
    printf("file open failed");
  /*--------------------*/
  /*variable declaration*/
  char * lineptr=NULL;
  char * lp;
  size_t n=0;
  int flag=0;
  int sum=0;
  int valid=0;

  int check_duplicate(char * lineptr);
  fseek(fp,0,SEEK_SET);
  
  while((getline(&lineptr,&n,fp))+1)
    {
      lp=lineptr;
      printf("%i: %s",sum++,lp);
      
      while(*lp!=0xd)
	{
	  flag=check_duplicate(lp);
	  
	  if(flag)
	    {break;}
	  else
	    ;
	  	  
	  while(*lp!=0x20 && *lp!=0xd)
	    lp++;
	  
	  if(*lp==0x20)
	    lp++;
	}
      
      if(flag)
	{printf("invalid\n");}
      else
	{valid++;printf("valid\n");}

    }

  printf("%i/%i",sum,valid);
  /*code end*/
  return 0;
}

/*------------------------------*/

int check_duplicate(char * lineptr)
{
  if(lineptr==NULL)
    return 1;
  
  char buffer1[26]={0};
  char buffer2[26]={0};
  int c;
  int equal=0;

  /*get car lineptr*/  
  while(*lineptr!=0x20 && *lineptr!=0xd)
    {
      c=*lineptr-97;
      buffer1[c]++;
      lineptr++;
    }
  /**/
  if(*lineptr==0x20)
    lineptr++;
  
  while(*lineptr!=0xd)
    {
      /*get car (cdr lineptr)*/
      while(*lineptr!=0x20 && *lineptr!=0xd)
	{
	  c=*lineptr-97;
	  buffer2[c]++;
	  lineptr++;
	}
      /**/
      c=memcmp(buffer1,buffer2,26);
      if(c==0)
	equal=1;
      else
	equal=0;

      if(equal)
	break;
      else
	memset(buffer2,0,26);
      
      if(*lineptr==0x20)/*middle*/
	lineptr++;
    }
  
  return equal;
}

/*------------------------------*/
