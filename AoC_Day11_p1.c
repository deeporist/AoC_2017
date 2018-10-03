#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE * fp;
  int c,i;
  int sum2dire(int,int *);
  int simp(int *,int *);
  int simp2(int *,int *);
  int direcord[6]={0};/*n,s,ne,sw,nw,se*/
  /*------------------------------*/
  if((fp=fopen("Day11.txt","r")) == NULL)
    {printf("file open failed\n");}
  /*--------------------*/
  /*
  printf("%*d\n",-4,123456789);
  fscanf(stdin,"%[^,0123456789 \f\n\r\t\v]",&buf);
  printf("%s\n",&buf);
  */
  i=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(c==',')
	{sum2dire(i,&direcord);i=0;}
      else
	i+=c;
    }
  sum2dire(i,&direcord);
  fclose(fp);
  
  /*------------------------------*/
  printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n",direcord[0],direcord[1],direcord[2],direcord[3],direcord[4],direcord[5]);
  /*------------------------------*/
  i=0;
  i^=simp(&direcord[0],&direcord[1]);
  i=i<<1;
  i^=simp(&direcord[2],&direcord[3]);
  i=i<<1;
  i^=simp(&direcord[4],&direcord[5]);
  printf("%d\n",i);
  /*3 remains*/
  /*------------------------------*/
  printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n",direcord[0],direcord[1],direcord[2],direcord[3],direcord[4],direcord[5]);
  /*------------------------------*/
  switch(i)
    {
    case 0:
      {direcord[0]+=simp2(&direcord[2],&direcord[4]);break;}
    case 1:
      {direcord[2]+=simp2(&direcord[0],&direcord[5]);break;}
    case 2:
      {direcord[4]+=simp2(&direcord[0],&direcord[3]);break;}
    case 3:
      {
	direcord[4]+=simp2(&direcord[0],&direcord[3]);
	simp(&direcord[4],&direcord[5]);break;}
    case 4:
      {direcord[5]+=simp2(&direcord[1],&direcord[2]);
	simp(&direcord[4],&direcord[5]);break;}
    case 5:
      {direcord[5]+=simp2(&direcord[1],&direcord[2]);break;}
    case 6:
      {direcord[3]+=simp2(&direcord[1],&direcord[4]);break;}
    case 7:
      {direcord[1]+=simp2(&direcord[3],&direcord[5]);break;}
    default:break;

    }
  
  /*------------------------------*/
  printf("n:%d\ns:%d\nne:%d\nsw:%d\nnw:%d\nse:%d\n",direcord[0],direcord[1],direcord[2],direcord[3],direcord[4],direcord[5]);
  /*------------------------------*/
  c=direcord[0]+direcord[1]+direcord[2]+direcord[3]+direcord[4]+direcord[5];
  printf("%d",c);
  /*------------------------------*/
  return 0;
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
  int i=0;
  if((*a)>(*b))
    {*a=abs(*a-*b);*b=0;}
  else
    {*b=abs(*a-*b);*a=0;i=1;}
  return i;
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
