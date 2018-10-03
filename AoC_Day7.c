#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  /*------------------------------*/
  FILE * fp,* fp2;
  if((fp2=fp=fopen("Day7.txt","r"))==NULL)
    printf("file open failed");
  /*------------------------------*/
  int find_match(FILE *,char *);
  char * lineptr=NULL;
  size_t n=0;
  long int pos;
  while((getline(&lineptr,&n,fp))+1)
    {
      if(strchr(lineptr,45)!=NULL)/*line has -*/
	{
	  pos=ftell(fp);
	  find_match(fp2,strtok(lineptr," "));/*first string*/
	  fseek(fp,pos,SEEK_SET);
	}
      else
	;
    }
  /*------------------------------*/
  free(lineptr);
  fclose(fp);
  /*------------------------------*/
  return 0;
}

int find_match(FILE * fp,char * s)
{
  int r=0;
  char * lineptr=NULL;
  size_t n=0;
  rewind(fp);/*set fp to the head of file*/
  while((getline(&lineptr,&n,fp))+1)
    {
      if(strchr(lineptr,45)!=NULL)
	if(strstr(lineptr,s)!=NULL)/*line has s*/
	  r++;
	else
	  ;
      else
	;
    }
  if(r==1)
    printf("%s",s);
  else
    ;
  return r;
}
