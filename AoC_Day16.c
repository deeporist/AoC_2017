#include <stdio.h>
#include <string.h>

#define len 16
#define p2 1000000000

char a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
char ta[len]={0};

char xa[]={'a','b','c','d','e'};

char ins[3]={0};/*0 1 2*/

int main(void)
{
  FILE * fp; 
  char c;
  void danec(void);
  int n,t,sn;
  /*------------------------------*/
  if((fp=fopen("Day16.txt","r")) == NULL)
    printf("file open failed\n");
  /*------------------------------*/
  for(sn=0;sn<p2;sn++)
    {
  while((c=fgetc(fp))!=EOF)/*no 'p' or ',' read in here*/
    {
      if(c=='s')
	{
	  ins[0]='s';

	  t=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)/*','*/
	    {t=t*10+(c^0x30);}/*sN read end*/	  
	  ins[1]=t;
	  ins[2]=0;
	}
      else if(c=='x')
	{
	  ins[0]='x';

	  t=0;
	  while( (c=fgetc(fp)) !=0x2f)/*'/'*/
	    {t=t*10+(c^0x30);}/*xN/*/
	  ins[1]=t;
	  
	  t=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)
	    {t=t*10+(c^0x30);}/*M read end*/
	  ins[2]=t;
	}
      else if(c=='p')
	{
	  ins[0]='p';
	  ins[1]=fgetc(fp);
	  fgetc(fp);/*'/'*/
	  ins[2]=fgetc(fp);
	  fgetc(fp);/*',' or EOF*/
	}
      else
	{printf("exception! %c", c);return 0;}

      danec();
    }
  fseek(fp,0,SEEK_SET);
    }
  /*------------------------------*/
  for(n=0;n<len;n++)
    printf("%c",a[n]);
  printf("\n");
  /*------------------------------*/
  fclose(fp);
  return 0;
}

void danec(void)
{
  /*printf("%x%x%x\n",ins[0],ins[1],ins[2]);*/
  int dn,dt,dx;    
  char tc;
  switch (ins[0])
    {
    case 's':
      {
	dn=len-ins[1];/*wo tm FJ*/
	for(dt=0;dt<len;dt++,dn++)
	  {ta[dt]=a[dn%len];}
	strcpy(a,ta);
	break;
      }
    case 'x':
      {	
	tc=a[ins[1]];
	a[ins[1]]=a[ins[2]];
	a[ins[2]]=tc;
	break;
      }
    case 'p':
      {		
	for(dt=0;dt<len;dt++)
	  {
	    if(a[dt]==ins[1])
	      dn=dt;
	    if(a[dt]==ins[2])
	      dx=dt;
	  }/*left: dn; right: dt*/
	tc=a[dn];
	a[dn]=a[dx];
	a[dx]=tc;	
	break;}
    default:
      break;
    }
  /*
  for(dn=0;dn<len;dn++)
    printf("%c",a[dn]);
  printf("\n");
  */
}
