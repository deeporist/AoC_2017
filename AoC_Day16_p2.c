#include <stdio.h>
#include <string.h>

#define len 16
#define p2 1000000000

char a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
char ta[len]={0};

char ca[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};

char ins[10000][3]={0};/*0 1 2*/

int main(void)
{
  FILE * fp; 
  unsigned int c;
  void danec(char [3]);
  register unsigned int n,t,sn;
  /*------------------------------*/
  if((fp=fopen("Day16.txt","r")) == NULL)
    printf("file open failed\n");
  /*------------------------------*/
  n=0;
  while((c=fgetc(fp))!=EOF)
    if(c==0x2c)
      n++;
  n++;  
  printf("%u\n",n);
  fseek(fp,0,SEEK_SET);
  printf("%u\n",memcmp(a,ca,len));
  /*------------------------------*/
  sn=0;
  while((c=fgetc(fp))!=EOF && sn<10000)/*no 'p' or ',' read in here*/
    {
      if(c=='s')
	{
	  ins[sn][0]='s';

	  t=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)/*','*/
	    {t=t*10+(c^0x30);}/*sN read end*/	  
	  ins[sn][1]=t;
	  ins[sn][2]=0;
	}
      else if(c=='x')
	{
	  ins[sn][0]='x';

	  t=0;
	  while( (c=fgetc(fp)) !=0x2f)/*'/'*/
	    {t=t*10+(c^0x30);}/*xN/*/
	  ins[sn][1]=t;
	  
	  t=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)
	    {t=t*10+(c^0x30);}/*M read end*/
	  ins[sn][2]=t;
	}
      else if(c=='p')
	{
	  ins[sn][0]='p';
	  ins[sn][1]=fgetc(fp);
	  fgetc(fp);/*'/'*/
	  ins[sn][2]=fgetc(fp);
	  fgetc(fp);/*',' or EOF*/
	}
      else
	{printf("exception! %c", c);return 0;}
      sn++;
    }  
  /*------------------------------*/  
  for(t=0;t<p2;t++)
    {
      sn=0;
      while(sn<10000)
	{
	  danec(ins[sn]);
	  sn++;	  
	}
      /*
      if(!(memcmp(a,ca,len)))
	break;
      */
      printf("%u\n",t);      
      
    }
  /*------------------------------*/
  for(n=0;n<len;n++)
    printf("%c",a[n]);
  printf("\n");
  /*------------------------------*/
  fclose(fp);
  return 0;
}

void danec(char tins[3])
{
  /*printf("%x%x%x\n",tins[0],tins[1],tins[2]);*/
  register unsigned int dn,dt,dx;    
  register unsigned char tc,td;
  switch (tins[0])
    {
    case 's':
      {
	dn=len-tins[1];
	for(dt=0;dt<len;dt++,dn++)
	  {ta[dt]=a[dn%len];}
	strcpy(a,ta);
	break;
      }
    case 'x':
      {	
	dn=tins[1];
	dt=tins[2];
	tc=a[dn];
	td=a[dt];
	
	tc=tc^td;
	td=tc^td;
	tc=tc^td;

	a[dn]=tc;
	a[dt]=td;
	
	break;
      }
    case 'p':
      {		
	for(tc=0,dx=0;dx<len&&tc<2;dx++)
	  {
	    if(!(a[dx]^tins[1]))
	      {dn=dx;tc++;}
	    if(!(a[dx]^tins[2]))
	      {dt=dx;tc++;}
	  }
	
	tc=a[dn];
	td=a[dt];
	
	tc=tc^td;
	td=tc^td;
	tc=tc^td;

	a[dn]=tc;
	a[dt]=td;
	
	break;
      }
    default:
      break;
    }
  /*
  for(dn=0;dn<len;dn++)
    printf("%c",a[dn]);
  printf("\n");
  */
}
