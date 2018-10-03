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
  char cbuf[length]={0};
  int i,s;
  int addinlist(int);
  int checkinlist(int);
  int freelist(void);
  int showline(FILE *,char *,int);
  int showlist(void);
  /*------------------------------*/
  start.mae=end.ushiro=NULL;
  start.i=end.i=2000;
  start.ushiro=&end;
  end.mae=&start;
  /*------------------------------*/
  /*
  addinlist(1);
  printf("%d",checkinlist(1));
  freelist();
  */
  /*--------------------*/
  if((fp=fopen("Day12.txt","r")) == NULL)
    {printf("file open failed\n");}
  /*--------------------*/
  /*
  showline(fp,&cbuf,780);
  */
  /*--------------------*/
  /*parse order is matter*/
  struct dynamic_record * dp;
  addinlist(0);
  rewind(fp);
  for(dp=start.ushiro;dp->ushiro!=NULL;dp=dp->ushiro)
    {
      cp=cbuf;
      /*get (dp->i)th line in cp*/
      showline(fp,cp,dp->i);
      
      /*jump index number*/
      strtol(cp,&cp,0);

      /*first number, may be 0*/
      cp+=5;
      s=(int)strtol(cp,&cp,10);
      addinlist(s);

      cp+=2;
      while((s=(int)strtol(cp,&cp,0)))
	{
	  addinlist(s);
	  cp+=2;
	}
    }
  
  /*------------------------------*/
  i=showlist();
  printf("\n%d",i);
  /*------------------------------*/
  fclose(fp);
  freelist();
  /*------------------------------*/
  return 0;
}

int showlist(void)
{
  int c=0;
  struct dynamic_record * dp;
  for(dp=start.ushiro;dp->ushiro!=NULL;dp=dp->ushiro)
    {
      printf("%d ",dp->i);
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

int addinlist(int i)
{
  int checkinlist(int);
  struct dynamic_record * p;

  if(checkinlist(i))
    return 0;
  else
    {
      p=(struct dynamic_record *)malloc(sizeof(struct dynamic_record));
      p->i=i;
      p->mae=end.mae;
      p->ushiro=&end;
      end.mae->ushiro=p;
      end.mae=p;
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
