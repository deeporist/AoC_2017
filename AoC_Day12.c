#include <stdio.h>

int rec[2000][8]={0};
int a[2000]={0};

int main(void)
{
  FILE * fp;
  char c;
  int t,n;
  int chcek(int);
  /*--------------------*/
  if((fp=fopen("Day12_ex.txt","r")) == NULL)
    {printf("file open failed\n");return 1;}
  /*--------------------*/
  n=0;
  t=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==0xd)
	{
	  c=fgetc(fp);
	  rec[n++][t]=9999;
	  t=0;
	  continue;
	}
      if(c==0x20)
	{
	  t++;
	  continue;
	}
      rec[n][t]=rec[n][t]*10+(c^(0x30));
    }
    fclose(fp);
  /*--------------------*/
  n=0;
  t=1;
  while(n<2000)
    {
      if(a[n]!=0)
	{n++;continue;}

      t++;
      chcek(n);      
      
      printf("%u %u\n",n++,t);
    }
  /*--------------------*/

  
  return 0;
}

int chcek(int p)
{
  a[p]=1;
  int i=0;
  
  if(rec[p][i]==p)
    return 0;
  
  while(rec[p][i]!=9999 && i<8)
    {
      if(a[rec[p][i]]==1)
	{i++;continue;}
      else
	{a[rec[p][i]]=1;}
      
      chcek(rec[p][i]);

      i++;
    }
  
  return 0;
}
