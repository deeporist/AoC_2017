

#define _GNU_SOURCE

#include <stdio.h>
#include "string.h"

int main()
{
  /*load file*/
  FILE * fp;
  if((fp=fopen("Day4.txt","r"))==NULL)
    printf("file open failed");
  /*--------------------*/
  /*variable declaration*/
  char * lineptr=NULL;
  size_t n=0;
  int flag=0;
  int sum=0;
  /*
  fseek(fp,0,SEEK_SET);
  getline(&lineptr,&n,fp);
  cp=strdupa(lineptr);
  token=strtok(cp,delimiters);
  printf("lineptr:%s\ncp:%s\ntoken:%s\n",lineptr,cp,token);
  while(token=strtok(NULL,delimiters))
    printf("token:%s\n",token);
  */
  int check_duplicate(char * lineptr);
  fseek(fp,0,SEEK_SET);
  while((getline(&lineptr,&n,fp))+1)
    {
      printf("%s",lineptr);
      while(*lineptr!=0xd)
	{
	  flag=check_duplicate(lineptr);
	  /*duplicate*/
	  if(flag)
	    {break;}
	  else
	    ;
	  
	  /*cdr lineptr*/
	  while(*lineptr!=0x20 && *lineptr!=0xd)
	    lineptr++;
	  if(*lineptr==0x20)
	    lineptr++;
	  if(*lineptr==0xd)
	    break;
	}
      if(flag)
	{printf("invalid\n");}
      else
	{sum++;printf("valid\n");}
      /*break;*/
    }
  printf("valid passphrase:%i",sum);

  /*code end*/
  return 0;
}

/*------------------------------*/

int check_duplicate(char * lineptr)
{
  if(lineptr==NULL)
    return 1;
  char * sp, * car, * carcdr;
  int r=0;
  const char delimiters[] = {0x20,0xd,0xa};  

  /*car lineptr*/
  sp=strdupa(lineptr);
  car=strtok(sp,delimiters);
  
  while(*lineptr!=0xd)
    {
      /*cdr lineptr*/
      while(*lineptr!=0x20 && *lineptr!=0xd)
	lineptr++;
      if(*lineptr==0x20)/*middle*/
	lineptr++;
      if(*lineptr==0xd)/*tail*/
	break;
      
      sp=strdupa(lineptr);
      carcdr=strtok(sp,delimiters);/*car (cdr lineptr)*/
      
      if(strcmp(car,carcdr))
	;
      else/*equal*/
	{
	  printf("%s-%s---",car,carcdr);
	  r=1;
	  break;
	}
    }
  
  return r;
}

/*------------------------------*/
