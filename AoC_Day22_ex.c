#include <stdio.h>

#define sca 525
#define offset 250
/*#define sca 480*/

int grid[sca][sca]={0};
int curr_dire;
int * subscript;

int burst(int);
int print_grid(void);

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
	grid[offset+a][offset+b++]=1;
      else if(c==0xd)
	{a++;b=0;}
      else if(c=='.')
	b++;
    }
    fclose(fp);    
    printf("\n%u %u\n",a,b);
  
  
    /*
  grid[0+(sca/3)][2+(sca/3)]=1;
  grid[1+(sca/3)][0+(sca/3)]=1;
  subscript=&(grid[1+(sca/3)][1+(sca/3)]);
    */
  /*print_grid();*/
  
    
  subscript=&(grid[offset+12][offset+12]);
  
  curr_dire=0;

  /*0: clean; 1: infected; 2: weakened; 3: flagged*/
  
  for(a=0;a<10000000;a++)
    {
      if(subscript > &grid[sca-1][sca-1] || subscript < grid)
	break;
      else if(*subscript==0)
	{
	  *subscript=2;
	  burst(2);	  
	}
      else if(*subscript==1)
	{
	  *subscript=3;
	  burst(3);
	}
      else if(*subscript==2)
	{
	  *subscript=1;
	  burst(0);
	  b++;
	}
      else if(*subscript==3)
	{
	  *subscript=0;
	  burst(1);
	}
    }
  printf("%u %u\n",a,b);  
    
    /*
    
    */
  /*------------------------------*/
  
  return 0;
}

int burst(int turn_dire)
{
  /*
curr_dire
0: up
1: down
2: left
3: right

turn_dire
0: curr_dire
1: reverse curr_dire
2: left
3: right
*/
  switch(curr_dire)
    {
    case 0:/*up*/
      {
	if(turn_dire==2)/*left*/
	  {subscript--;curr_dire=2;}
	else if(turn_dire==3)/*right*/
	  {subscript++;curr_dire=3;}
	else if(turn_dire==0)/*continue*/
	  {subscript-=sca;}
	else if(turn_dire==1)/*reverse*/
	  {subscript+=sca;curr_dire=1;}
	break;
      }
    case 1:/*down*/
      {
	if(turn_dire==2)/*left*/
	  {subscript++;curr_dire=3;}
	else if(turn_dire==3)/*right*/
	  {subscript--;curr_dire=2;}
	else if(turn_dire==0)/*continue*/
	  {subscript+=sca;}
	else if(turn_dire==1)/*reverse*/
	  {subscript-=sca;curr_dire=0;}
	break;
      }
    case 2:/*left*/
      {
	if(turn_dire==2)/*left*/
	  {subscript+=sca;curr_dire=1;}
	else if(turn_dire==3)/*right*/
	  {subscript-=sca;curr_dire=0;}
	else if(turn_dire==0)/*continue*/
	  {subscript--;}
	else if(turn_dire==1)/*reverse*/
	  {subscript++;curr_dire=3;}
	break;
      }
    case 3:/*right*/
      {
	if(turn_dire==2)/*left*/
	  {subscript-=sca;curr_dire=0;}
	else if(turn_dire==3)/*right*/
	  {subscript+=sca;curr_dire=1;}
	else if(turn_dire==0)/*continue*/
	  {subscript++;}
	else if(turn_dire==1)/*reverse*/
	  {subscript--;curr_dire=2;}
	break;
      }
    }
  return 0;
}

int print_grid(void)
{
  int a,b;
  for(a=0;a<sca;a++)
    {
      for(b=0;b<sca;b++)
	{
	  printf("%u",grid[a][b]);	  
	}
      printf("\n");
    }
  return 0;
}
