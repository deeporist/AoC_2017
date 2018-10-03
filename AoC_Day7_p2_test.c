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
  
  char dool[10]={0};
  char * d;
  
  fseek(fp,0,SEEK_SET);
  /*make fp point to head of file*/
  /*getline*/
  /*https://www.gnu.org/software/libc/manual/html_node/Line-Input.html*/
  /*This function reads an entire line from stream, storing the text (including the newline and a terminating null character) in a buffer and storing the buffer address in *lineptr.*/
  /*If you set *lineptr to a null pointer, and *n to zero, before the call, then getline allocates the initial buffer for you by calling malloc. This buffer remains allocated even if getline encounters errors and is unable to read any bytes.*/
  /*getline makes the buffer bigger using realloc, storing the new buffer address back in *lineptr and the increased size back in *n.*/
  /*When getline is successful, it returns the number of characters read (including the newline, but not including the terminating null). This value enables you to distinguish null characters that are part of the line from the null character inserted as a terminator.*/
  /*If an error occurs or end of file is reached without any bytes read, getline returns -1.*/
  while((getline(&lineptr,&n,fp))+1)
    {
      s=strdup(lineptr);
      printf("%s",s);
      /*vpryah (310) -> iedlpkf, epeain*/
      while((*s)!='>')s++;
      while((*s)!=0xd)
	{
	  d=dool;
	  s++;/*space*/
	  s++;/*1st char*/
	  while((*s)!=',' && (*s)!=0xd)
	    *d++=*s++;
	  *d=0;
	  printf("%s ",dool);	  
	}
	
      /**/
      printf("\n");
    }
  free(lineptr);
  /**/
  fclose(fp);
  /*------------------------------*/
  return 0;
}

/*https://www.gnu.org/software/libc/manual/html_node/Finding-Tokens-in-a-String.html*/
