#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dynamic_record
{
  struct dynamic_record * mae;
  struct dynamic_record * ushiro;
  int i;
}start,end;

#define length 50

int main(void)
{
  FILE * fp;
  char * cp;
  struct dynamic_record * dp;
  char cbuf[length]={0};
  int i,s;
  int addinlist(int);
  int checkinlist(int);
  int freelist(void);
  int showline(FILE *,char *,int);
  int showlist(struct dynamic_record *);
  int searchinlist(FILE *,char *);
  /*------------------------------*/
  if((fp=fopen("Day12.txt","r")) == NULL)
    {printf("file open failed\n");}
  /*--------------------*/
  start.mae=end.ushiro=NULL;
  start.i=end.i=2000;
  start.ushiro=&end;
  end.mae=&start;
  /*------------------------------*/

  i=0;
  for(s=0;s<2000;s++)
    {
      if(checkinlist(s))
	;
      else
	{
	  i++;
	  addinlist(s);
	  dp=end.mae;
	  searchinlist(fp,cbuf);
	  printf("%d-%d ",s,showlist(dp));
	}
    }
  printf("\n%d",i);
  /*------------------------------*/
  fclose(fp);
  freelist();
  /*------------------------------*/
  return 0;
}

int searchinlist(FILE * fp,char * cp)
{
  struct dynamic_record * dp;
  int addinlist(int);
  int showline(FILE *,char *,int);
  char * cp2;
  int s;
  /*------------------------------*/
  for(dp=end.mae;dp->ushiro!=NULL;dp=dp->ushiro)
    {
      cp2=cp;/*cbuf*/
      showline(fp,cp2,dp->i);/*get that line in file into cbuf*/
      strtol(cp2,&cp2,0);/*jump index number*/
      cp2+=5;
      s=(int)strtol(cp2,&cp2,0);/*1th member may be 0*/
      addinlist(s);
      cp2+=2;
      while((s=(int)strtol(cp2,&cp2,0)))
	{
	  addinlist(s);
	  cp2+=2;
	}
    }
  return 0;
}

int addinlist(int i)
{
  int checkinlist(int);
  struct dynamic_record * dp;
  /*insert i before end*/
  if(checkinlist(i))
    return 0;
  else
    {
      dp=(struct dynamic_record *)malloc(sizeof(struct dynamic_record));
      dp->i=i;
      dp->mae=end.mae;
      dp->ushiro=&end;
      end.mae->ushiro=dp;
      end.mae=dp;
    }
  return 0;
}

int checkinlist(int i)
{
  /*iru: r=1; inai: r=0;*/
  struct dynamic_record * p=&start;
  int r=1;
  while(p->i!=i)
    {
      if(p->ushiro==NULL)
	{r=0;break;}
      else
	p=p->ushiro;
    }
  return r;
}

int freelist(void)
{
  /*only regions allocated from functions like malloc could be freed!*/
  struct dynamic_record * p=start.ushiro;
  while((p->ushiro)!=NULL)
    {
      p=p->ushiro;
      free(p->mae);
    }
  return 0;
}

int showlist(struct dynamic_record * dp)
{
  int c=0;
  
  for(;dp->ushiro!=NULL;dp=dp->ushiro)
    {
      /*printf("%d ",dp->i);*/
      c++;
    }
  return c;
}

int showline(FILE * fp,char * cp,int i)
{
  rewind(fp);
  int n;
  for(n=0;n<=i;n++)
    {
      memset(cp,0,sizeof(char)*length);
      fgets(cp,length,fp);
    }
  /*printf("%s",cp);*/
  return 0;
}
