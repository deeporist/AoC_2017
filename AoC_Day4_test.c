#include <stdio.h>

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
	  if(*lp==0xd)
	    break;
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
  
  char buffer[20]={0};
  char * car=buffer;
  int equal=0;

  /*car lineptr*/  
  while(*lineptr!=0x20 && *lineptr!=0xd)/*default word not longer than buffer*/
    {
      *car=*lineptr;
      car++;
      lineptr++;
    }
  *car=0;
  /*end of buffer*/
  
  if(*lineptr==0x20)/*middle*/
    lineptr++;/*first char of the next word*/
  
  while(*lineptr!=0xd)
    {
      car=buffer;
      equal=1;
      /*cdr lineptr*/
      while(*lineptr!=0x20 && *lineptr!=0xd && *car!=0)
	{
	  if((*car)^(*lineptr))/*unequal -> next word*/
	    {equal=0;break;}
	  else/*equal -> next char*/
	    {car++;lineptr++;}
	}

      /**/
      if(equal)
	{
	  if(*car)/*buffer not end & lineptr end*/
	    equal=0;
	  else/*buffer end*/
	    {
	      if(*lineptr!=0x20 && *lineptr!=0xd)/*lineptr not end*/
		equal=0;
	      else
		break;/*all end, equal=1*/
	    }
	}
      /**/

      while(*lineptr!=0x20 && *lineptr!=0xd)
	lineptr++;/*next word*/
      
      if(*lineptr==0x20)/*middle*/
	lineptr++;
      if(*lineptr==0xd)/*tail*/
	break;
      
    }
  
  return equal;
}

/*------------------------------*/
