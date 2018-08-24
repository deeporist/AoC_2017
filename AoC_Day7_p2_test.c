#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc,char * * argv)
{

  FILE * fp;
  if((fp=fopen("Day7_test.txt","r"))==NULL)
    printf("file open failed");

  char * lineptr=NULL;
  char * s=NULL;
  size_t n=0;
  char delimiters[]={0x20,0x2c,0xd,0xa};
  
  fseek(fp,0,SEEK_SET);/*make fp point to head of file*/
  while((getline(&lineptr,&n,fp))+1)
    {
      s=strdup(lineptr);
      printf("%s",s);
      
      strtok(s,">");
      while((s=strtok(NULL,delimiters))!=NULL)
	{ printf("%s ",s); }
      printf("\n");
    }
  free(lineptr);
  /**/
  fclose(fp);
  /*------------------------------*/
  return 0;
}

