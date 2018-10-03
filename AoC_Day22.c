#include <stdio.h>

#define sca 225

int grid[sca][sca]={0};
int curr_dire;
int * subscript;

int burst(int);
void print_grid(void);

int main(void)
{
  FILE * fp;  
  int a,b,c;
  
  if((fp=fopen("Day22.txt","r"))==NULL)
    printf("file open failed");
  a=b=c=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c=='#')
	grid[100+a][100+b++]=1;
      else if(c==0xd)
	{a++;b=0;}
      else if(c=='.')
	b++;
    }
    fclose(fp);
    print_grid();
    printf("\n%u %u\n",a,b);
    /*  
  grid[0+(sca/3)][2+(sca/3)]=1;
  grid[1+(sca/3)][0+(sca/3)]=1;
    */
  subscript=&(grid[100+12][100+12]);
  curr_dire=0;
  
  for(a=0;a<10000;a++)
    {
      if(subscript > &grid[sca-1][sca-1] || subscript < grid)
	break;
      else if(*subscript==0)
	{
	  *subscript=1;
	  b++;
	  burst(2);
	}
      else if(*subscript==1)
	{
	  *subscript=0;
	  burst(3);
	}
    }
  printf("%u %u",a,b);
    
    /*
    
    */
  /*------------------------------*/
  
  return 0;
}

int burst(int turn_dire)
{
  switch(curr_dire)
    {
    case 0:/*up*/
      {
	if(turn_dire==2)/*left*/
	  {subscript--;curr_dire=2;}
	else if(turn_dire==3)/*right*/
	  {subscript++;curr_dire=3;}
	break;
      }
    case 1:/*down*/
      {
	if(turn_dire==2)/*left*/
	  {subscript++;curr_dire=3;}
	else if(turn_dire==3)/*right*/
	  {subscript--;curr_dire=2;}
	break;
      }
    case 2:/*left*/
      {
	if(turn_dire==2)/*left*/
	  {subscript+=sca;curr_dire=1;}
	else if(turn_dire==3)/*right*/
	  {subscript-=sca;curr_dire=0;}
	break;
      }
    case 3:/*right*/
      {
	if(turn_dire==2)/*left*/
	  {subscript-=sca;curr_dire=0;}
	else if(turn_dire==3)/*right*/
	  {subscript+=sca;curr_dire=1;}
	break;
      }
    }
  return 0;
}

void print_grid(void)
{
  int a,b;
  for(a=0;a<sca;a++)
    {
      for(b=0;b<sca;b++)
	printf("%u",grid[a][b]);
      printf("\n");
    }
}
