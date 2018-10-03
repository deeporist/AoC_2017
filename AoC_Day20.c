#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define particle_num 1000
#define turn 1000000

int main(void)
{
  FILE * fp;
  int particles[particle_num][3][3]={0};
  char atoibuff[6]={0};
  int pn,c,n,p,cn;
  long int sum,cum;
  /*------------------------------*/
  if((fp=fopen("Day20.txt","r")) == NULL)
    printf("file open failed\n");
  /*------------------------------*/
  cn=p=n=pn=c=0;
  /*particles[pn][p][cn]*/
  while((c=fgetc(fp))!=EOF)
    {
      if(isalpha(c))
	{
	  if(c=='p')p=0;
	  else if(c=='v')p=1;
	  else if(c=='a')p=2;
	  else
	    {printf("Error!");return 0;}
	  
	  fgetc(fp);/*=*/
	  fgetc(fp);/*<*/

	  n=cn=0;
	  while((c=fgetc(fp))!='>')
	    {
	      if(c!=',')
		atoibuff[n++]=c;
	      else
		{
		  atoibuff[n]='\n';
		  particles[pn][p][cn++]=atoi(atoibuff);
		  n=0;
		}
	    }
	  atoibuff[n]='\n';
	  particles[pn][p][cn]=atoi(atoibuff);

	}

      else if(c=='\n')
	pn++;      
    }
  fclose(fp);
  /*------------------------------*/
  p=98;/*storge partile number*/
  sum=2058;/*storage least distance*/
  for(n=0;n<1;n++)
    {
      for(sum=0,cum=0,pn=0;pn<particle_num;pn++)
	{
	  /*--------V=V+A------------*/
	  
	  
	  cum+=abs(particles[pn][2][0]);
	  cum+=abs(particles[pn][2][1]);
	  cum+=abs(particles[pn][2][2]);
	  /*--------------------*/
	  if(sum==0)
	    sum=cum;
	  else if(sum>cum)
	    {sum=cum;p=pn;}
	  cum=0;
	  /*--------------------*/
	}
      printf("%u %lu\n",p,sum);
    }
  /*------------------------------*/
  fp=NULL;/*debug breakpoint*/
  return 0;
}
