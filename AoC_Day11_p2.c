#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE * fp;
  int c,i,r,t;
  int sum2dire(int,int *);
  int statistic(int * p);
  int direcord[6]={0};/*n,s,ne,sw,nw,se*/
  /*------------------------------*/
  if((fp=fopen("Day11.txt","r")) == NULL)
    {printf("file open failed\n");}
  /*------------------------------*/
  r=i=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==',')
	{
	  switch(i)
	    {
	    case 110:/*n*/
	      {direcord[0]++;break;}
	    case 115:/*s*/
	      {direcord[1]++;break;}
	    case 211:/*ne*/
	      {direcord[2]++;break;}
	    case 234:/*sw*/
	      {direcord[3]++;break;}
	    case 229:/*nw*/
	      {direcord[4]++;break;}
	    case 216:/*se*/
	      {direcord[5]++;break;}
	    default:break;
	    }
	  
	  t=statistic(&direcord);
	  if(t>r)
	    r=t;
	  
	  i=0;
	}
      else
	i+=c;
    }
  sum2dire(i,&direcord);
  fclose(fp);
  /*------------------------------*/
  /*
  printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n\n",direcord[0],direcord[1],direcord[2],direcord[3],direcord[4],direcord[5]);
  */
  /*------------------------------*/
  t=statistic(&direcord);
  if(t>r)
    r=t;
  /*------------------------------*/
  printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n\n",direcord[0],direcord[1],direcord[2],direcord[3],direcord[4],direcord[5]);
  printf("step:%d",r);
  /*------------------------------*/
  return 0;
}

int statistic(int * p)
{
  int t;
  int simp(int *,int *);
  int simp2(int *,int *);
  int sum(int *);
  /*-------- inverse ------------*/
  do
    {
      t=0;
      /*--------------------*/
      t+=simp(p,p+1);
      t+=simp(p+2,p+3);
      t+=simp(p+4,p+5);
      /*--------------------*/
      
      printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n\n",(*p),(*(p+1)),(*(p+2)),(*(p+3)),(*(p+4)),(*(p+5)));
      
      /*--------------------*/
      /*how much remained*/
      if((*p)*(*(p+3)))/*n+sw=nw*/
	{(*(p+4))+=simp2(p,p+3);t++;}
      else if((*p)*(*(p+5)))/*n+se=ne*/
	{(*(p+2))+=simp2(p,p+5);t++;}
      else if((*(p+1))*(*(p+4)))/*s+nw=sw*/
	{(*(p+3))+=simp2(p+1,p+4);t++;}
      else if((*(p+1))*(*(p+2)))/*s+ne=se*/
	{(*(p+5))+=simp2(p+1,p+2);t++;}
      else if((*(p+4))*(*(p+2)))/*nw+ne=n*/
	{(*p)+=simp2(p+4,p+2);t++;}
      else if((*(p+3))*(*(p+5)))/*sw+se=s*/
	{(*(p+1))+=simp2(p+3,p+5);t++;}
      else
	t=0;
    }while(t);
  /*--------------------*/
  return sum(p);
}

int sum(int * p)
{
  return ((*p)+(*(p+1))+(*(p+2))+(*(p+3))+(*(p+4))+(*(p+5)));
}

int simp2(int * a,int * b)
{
  int i;
  if((*a)>(*b))
    {*a=abs(*a-*b);i=*b;*b=0;}
  else
    {*b=abs(*a-*b);i=*a;*a=0;}
  return i;
}

int simp(int * a,int * b)
{
  if((*a)*(*b))
    ;
  else
    return 0;
  if((*a)>(*b))/*both >0*/
    {*a=abs(*a-*b);*b=0;}
  else
    {*b=abs(*a-*b);*a=0;}
  return 1;
}

int sum2dire(int i,int * p)
{
  switch(i)
    {
    case 110:/*n*/
      {(*p)++;break;}
    case 115:/*s*/
      {(*(p+1))++;break;}
    case 211:/*ne*/
      {(*(p+2))++;break;}
    case 234:/*sw*/
      {(*(p+3))++;break;}
    case 229:/*nw*/
      {(*(p+4))++;break;}
    case 216:/*se*/
      {(*(p+5))++;break;}
      
    default:break;
    }
  /*printf("%s ",s);*/
  return 0;
}

