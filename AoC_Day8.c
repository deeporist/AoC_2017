#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define cont 30

struct reg
{
  char name[5];
  int number;
}regs[cont]={{0},0};

int main()
{
  FILE * fp;
  if((fp=fopen("Day8.txt","r"))==NULL)
    printf("file open failed");
  /**/
  char * lineptr=NULL;
  size_t n=0;
  /*
  int count=0;
  while((getline(&lineptr,&n,fp))+1)
    {
      printf("%s",lineptr);
      count++;
    }
  */
  /*
  printf("\n%i\n",count);
  */
  /**/
  /**/
  char * np=NULL;
  char * lp=NULL;
  char buffer[5]={0};
  char * cp=NULL;
  int i=1;
  int get_reg(char * lp);
  int excute_instruct(char * lp);
  int check_condition(char * lp);
  /**/
  rewind(fp);
  while((getline(&lineptr,&n,fp))+1)
    {
      lp=lineptr;
      cp=buffer;
      while(*lp!=0x20)
	{*cp++=*lp++;}
      *cp=0;
      
      if(get_reg(buffer))/*exist*/
	;
      else
	{
	  np=regs[i++].name;
	  memcpy(np,buffer,5);
	}
    }
  /**/
  /*
  for(i=0;i<cont;i++)
    printf("%s:%i\n",regs[i].name,regs[i].number);
  */
  /**/
  int c=0;
  rewind(fp);
  while((getline(&lineptr,&n,fp))+1)
    {
      lp=lineptr;
      cp=buffer;
      while(*lp!=0x20)
	{*cp++=*lp++;}
      *cp=0;
     
      i=get_reg(buffer);
      /*printf("%i\n",i);*/
      /**/
      if(check_condition(lp))
	{
	  lp++;
	  regs[i].number+=excute_instruct(lp);

	  /*p2*/
	  /**/
	  
	      if(regs[i].number > c)
		c=regs[i].number;
	  
	  /**/
	}
      else
	;
      /**/
    }
  /**/
  /*p1*/
  /*
  int c=0;
  for(i=1;i<cont;i++)
    {
      if(regs[i].number > c)
	c=regs[i].number;
    }
  */
  printf("max:%i",c);
  /**/
  return 0;
}

/**/
int get_reg(char * buffer)
{
  int i=0;
  int r=0;
  /**/
  for(i=1;i<cont;i++)
    {
      if(strcmp(regs[i].name,buffer))
	;
      else
	{r=i;break;}
    }
  /**/
  return r;
}


/**/
int check_condition(char * lp)
{
  int get_reg(char * lp);
  char buffer[5]={0};
  char * cp=NULL;
  int i=0;
  int t=0;
  int c;
  /**/
  while(memcmp(lp," if ",4))
    lp++;
  /**/
  lp+=4;
  /**/
  cp=buffer;
  while(*lp!=0x20)
    {*cp++=*lp++;}
  *cp=0;
  /**/
  i=get_reg(buffer);
  if(i)
    t=regs[i].number;
  else
    return 0;
  /**/
  lp++;
  /**/
  cp=lp;
  while(*cp!=0x20)
    cp++;
  cp++;
  c=(int)strtol(cp,NULL,0);
  /**/
  /*< > == <= >= !=*/
  /**/
  i=1;
  if((memcmp(lp,"< ",2)==0) && t<c)
    ;
  else if((memcmp(lp,"> ",2)==0) && t>c)
    ;
  else if((memcmp(lp,"==",2)==0) && t==c)
    ;
  else if((memcmp(lp,"<=",2)==0) && t<=c)
    ;
  else if((memcmp(lp,">=",2)==0) && t>=c)
    ;
  else if((memcmp(lp,"!=",2)==0) && t!=c)
    ;
  else
    i=0;
  /**/
  return i;
}

/**/
int excute_instruct(char * lp)
{
  int sign=0;
  int n=0;
  /**/
  if(memcmp(lp,"inc",3)==0)
    sign=1;
  else if(memcmp(lp,"dec",3)==0)
    sign=-1;
  else
    return 0;
  /**/
  while(*lp!=0x20)
    lp++;
  lp++;
  /**/
  n=(int)strtol(lp,NULL,0);
  n=n*sign;
  /**/
  return n;
}

