#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  FILE * fp;
  int a,b,c,t;
  char buff[13];
  char * bp;
  int p[1000]={0};
  /*------------------------------*/
  if((fp=fopen("Day20_ex_last.txt","r"))==NULL)
    printf("file open failed\n");
  /*------------------------------*/
  while((c=fgetc(fp))!=EOF)
    {
      bp=buff;
      memset(buff,0,sizeof(char)*13);

      for(;c!=0xa;c=fgetc(fp))
	*bp++=c;

      a=(int)strtol(&buff[0],&bp,10);
      b=(int)strtol(bp+1,&bp,10);
      t=(int)strtol(bp+1,&bp,10);

      /*------------------------------*/
      if((p[a]+p[b])==0)
	p[a]=p[b]=t;
      else if(p[a]==t)
	p[b]=t;
      else if(p[b]==t)
	p[a]=t;
      else
	printf("FUCK\n");
	
      /*------------------------------*/
    }
  
  /*------------------------------*/
  for(a=0,t=0;t<1000;t++)
    if(p[t]==0)
      {a++;}
  printf("%d",a);
  /*------------------------------*/
  return 0;
}
