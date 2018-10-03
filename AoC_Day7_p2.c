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
  
  void travelsal_tree(struct program * tp);
  /*travelsal_tree(&root);*/
  long int travelsal_add_tree(struct program * tp);
  /*
  int n=travelsal_add_tree(&root);
  printf("%d\n",n);
  */
  struct program * travelsal_search_tree(struct program * tp, char * name);
  /*
  struct program * t = travelsal_search_tree(&root, *(argv+1));
  printf("%s",t->name);
  */
  /*------------------------------*/
  struct program * t;
  long int n;
  int c='0';
  char dool[10]={0};

  while(c=='0')
    {
      printf("parent program name: ");
      
      fgets(dool,10,stdin);
      dool[strcspn(dool,"\n")]=0;

      t=travelsal_search_tree(&root, dool);
      if(t==NULL){printf("ERROR!\n");exit(1);}
      t=t->cl;
      while(t)/*error with leaf node*/
	{
	  if(t->cl) n=travelsal_add_tree(t->cl)+t->weigh;
	  else n=t->weigh;
	  printf("%s-%ld ",t->name,n);
	  t=t->sl;
	}
      printf("\ncontinue(0)?");
      scanf("%c%*c", &c);
    }
  
  
  /*------------------------------*/
  fclose(fp);
  /*------------------------------*/
  return 0;
}









/*--------------------------------------------------*/
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
  if(s==NULL){printf("CAN'T FIND!!!!!!");}
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
    {      printf("%s\n",s);    }
}

/*tp point to root*/
void filltree(FILE * fp,struct program * tp)
{
  /*--------------------*/
  struct program * cp;
  struct program * rp;
  char * d;
  char dool[10]={0};
  /*--------------------*/
  /*printf("name@%s\n",tp->name);*/
  char * s = retline(fp,tp->name);
  if(s==NULL){printf("ERROR!!!!!!");exit(1);}
  /*--------------------*/
  
  tp->weigh=retnum(fp,tp->name);
  /*printf("%s",s);*/
  
  if(strchr(s,'>')!=NULL)/*if tp has child*/
    {
      tp->cl=(struct program *)malloc(sizeof(struct program));
      cp=tp->cl;
      /**/
      while((*s)!='>')s++;
      while((*s)!=0xd)
	{
	  /*--------------------*/
	  d=dool;
	  s++;s++;
	  while((*s)!=',' && (*s)!=0xd)
	    *d++=*s++;
	  *d=0;
	  /*printf("%s ",dool);*/
	  /*--------------------*/
	  strcpy(cp->name,dool);
	  cp->sl=(struct program *)malloc(sizeof(struct program));
	  rp=cp;
	  cp=cp->sl;
	}
      /*last brother*/
      free(cp);
      rp->sl=NULL;
      /*printf("\n");*/
      
      /**/
      cp=tp->cl;
      while(cp!=NULL)/*same level traversal*/
	{
	  filltree(fp,cp);
	  cp=cp->sl;
	}
    }
  
  else/*tp is leaf*/
    {
      tp->cl=NULL;
      /*printf("-leaf-\n");*/
    }
  
}
/*------------------------------*/

void travelsal_tree(struct program * tp)
{
  printf("%s-%d\n",tp->name,tp->weigh);
  
  if(tp->cl)
    { travelsal_tree(tp->cl); }
  
  if(tp->sl)
    { travelsal_tree(tp->sl); }
}

/*------------------------------*/
long int travelsal_add_tree(struct program * tp)
{
  long int n=0;
  /*printf("%s-%d\n",tp->name,tp->weigh);*/
  
  if(tp->cl)
    {
      n=travelsal_add_tree(tp->cl);
    }
  
  if(tp->sl)
    {
      n=n+travelsal_add_tree(tp->sl);
    }

  n=n+tp->weigh;
  return n;
}

/*------------------------------*/
struct program * travelsal_search_tree(struct program * tp, char * name)
{
  struct program * pp=NULL;
  
  if (strcmp(tp->name,name))
    ;
  else
    return tp;

  if(tp->cl)
    { pp=travelsal_search_tree(tp->cl,name); }
  if(pp!=NULL)return pp;
  if(tp->sl)
    { pp=travelsal_search_tree(tp->sl,name); }
  return pp;
}
/*------------------------------*/
