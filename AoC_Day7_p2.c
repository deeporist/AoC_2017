#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/*------------------------------*/
struct program
{
  char name[10];
  int weigh;
  struct program * sl;
  struct program * cl;
};
/*------------------------------*/
int main(int argc,char * * argv)
{
  /*------------------------------*/
  if (argc==1)
    {
      printf("name of root program");
      return 0;
    }
  FILE * fp;
  if((fp=fopen("Day7.txt","r"))==NULL)
    printf("file open failed");

  /*------------------------------*/
  
  char * retline(FILE * fp,char * arg);
  
  int retnum(FILE * fp,char * s);
    
  struct program root;
  strcpy(root.name,*(argv+1));
  root.sl=NULL;

  void filltree(FILE * fp,struct program * tp);
  filltree(fp,&root);
  
  /*------------------------------*/
  fclose(fp);
  /*------------------------------*/
  return 0;
}

/*------------------------------*/
char * retline(FILE * fp,char * arg)
{
  char * lineptr=NULL;
  char * s=NULL;
  size_t n=0;
  fseek(fp,0,SEEK_SET);/*make fp point to head of file*/
  while((getline(&lineptr,&n,fp))+1)
    {
      /*If the two strings are equal, strcmp returns 0*/
      if(!memcmp(lineptr,arg,strlen(arg)))
	{
	  s=strdup(lineptr);
	  break;
	}
      else
	;
    }
  free(lineptr);
  return s;
}

/*------------------------------*/
int retnum(FILE * fp,char * p)
{
  char * s = retline(fp,p);
  if (s==NULL) return 0;
  int n=0;
  while(*s!='(')
    s++;
  n=(int)strtol(++s,(char **)NULL,10);
  return n;
}

/**/
void retmember(char * s)
{
  strtok(s,">");
  while((s=strtok(NULL,", "))!=NULL)
    {
      printf("%s\n",s);
    }
}

/*tp point to root*/
void filltree(FILE * fp,struct program * tp)
{
  /*--------------------*/
  struct program * cp;
  struct program * rp;
  char * p, * t;
  const char delimiters[]={0x20,0x2c,0xd,0xa};
  char * s = retline(fp,tp->name);
  /*--------------------*/
  
  tp->weigh=retnum(fp,tp->name);
  printf("%s",s);
  
  if(strchr(s,'>')!=NULL)/*if tp has child*/
    {
      tp->cl=(struct program *)malloc(sizeof(struct program));
      cp=tp->cl;
      
      p=strdup(s);
      strtok(p,">");
      while((t=strtok(NULL,delimiters))!=NULL)
	{
	  printf("%s ",t);
	  strcpy(cp->name,t);
	  cp->sl=(struct program *)malloc(sizeof(struct program));
	  rp=cp;
	  cp=cp->sl;
	  sleep(1);
	}
      /*last brother*/
      free(cp);
      rp->sl=NULL;
      printf("\n");
      
      /**/
      cp=tp->cl;
      while(cp!=NULL)/*same level traversal*/
	{
	  filltree(fp,cp);
	  cp=cp->sl;
	}
    }
  
  else/*tp is leaf*/
    {tp->cl=NULL;printf("-leaf-\n");}
  
}
