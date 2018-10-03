#include <stdio.h>
#include <string.h>

#define len 16
#define p2 1000000000

char a[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
char ta[len]={0};

char ca[]={0x6f,'c','i','e','d','p','j','b','m','f','n','k','h','l','g','a'};

char ins[10000][3]={0};/*0 1 2*/

int main(void)
{
  FILE * fp; 
  unsigned int c;
  
  register unsigned int t,sn;
  register unsigned int dn,dt,dx;    
  register unsigned char tc,td;
  /*------------------------------*/
  if((fp=fopen("Day16.txt","r")) == NULL)
    printf("file open failed\n");
  /*------------------------------*/
  dn=0;
  while((c=fgetc(fp))!=EOF)
    if(c==0x2c)
      dn++;
  dn++;  
  printf("%u\n",dn);
  fseek(fp,0,SEEK_SET);
  printf("%u\n",memcmp(a,ca,len));
  /*------------------------------*/
  sn=0;
  while((c=fgetc(fp))!=EOF && sn<10000)/*no 'p' or ',' read in here*/
    {
      if(c=='s')
	{
	  ins[sn][0]='s';

	  dt=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)/*','*/
	    {dt=dt*10+(c^0x30);}/*sN read end*/	  
	  ins[sn][1]=dt;
	  ins[sn][2]=0;
	}
      else if(c=='x')
	{
	  ins[sn][0]='x';

	  dt=0;
	  while( (c=fgetc(fp)) !=0x2f)/*'/'*/
	    {dt=dt*10+(c^0x30);}/*xN/*/
	  ins[sn][1]=dt;
	  
	  dt=0;
	  while( (c=fgetc(fp)) !=0x2c && c!=EOF)
	    {dt=dt*10+(c^0x30);}/*M read end*/
	  ins[sn][2]=dt;
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
  /*----------1e9--------------------*/  
  for(t=0;t<40;t++)
    {
      sn=0;
      while(sn<10000)
	{
	  
	  switch (ins[sn][0])
	    {
	    case 's':
	      {
		dn=len-ins[sn][1];
		for(dt=0;dt<len;dt++,dn++)
		  {ta[dt]=a[dn%len];}
		memcpy(a,ta,16);/*overflow!!!!*/
		break;
	      }
	    case 'x':
	      {	
		dn=ins[sn][1];
		dt=ins[sn][2];
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
		    if(!(a[dx]^ins[sn][1]))
		      {dn=dx;tc++;}
		    if(!(a[dx]^ins[sn][2]))
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
	  sn++;	  
	}
     
      if(!(memcmp(a,ca,len)))
	{printf("%u\n",t);fgetc(stdin);}                       
    }
  /*------------------------------*/
  for(dn=0;dn<len;dn++)
    printf("%c",a[dn]);
  printf("\n");
  /*------------------------------*/
  fclose(fp);
  return 0;
}

