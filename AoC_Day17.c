#include <stdio.h>
#include <stdlib.h>

#define times 2018
#define steps 329

struct node
{
  unsigned short val;
  struct node * next;
};

typedef struct node * nodelist;

int main(void)
{
  unsigned short t,s;
  struct node root;
  nodelist np,tnp;  
  /*------------------------------*/
  root.val=0;
  root.next=&root;

  np=&root;
  /*
  np=malloc(sizeof(struct node));
  if(np==NULL)return 0;
  else
    {
      np->val=1;
      np->next=np;
    }
  */
  /*------------------------------*/
  for(t=0;t<times;t++)
    {
      for(s=0;s<steps;s++)
	{
	  np=np->next;
	}
      
      tnp=malloc(sizeof(struct node));
      if(tnp == NULL)return 0;
      else
	{
	  tnp->val=t+1;
	  
	  tnp->next=np->next;
	  np->next=tnp;
	  
	  np=np->next;
	}
    }
  /*------------------------------*/
  np=&root;
  for(t=0;t<times;t++)
    {
      printf("%u ",np->val);
      if(np->val == 2017)
	{tnp=np;}
      np=np->next;
    }
  printf("\n%u %u\n",tnp->val,tnp->next->val);
  /*------------------------------*/
  return 0;
}
