#include <stdio.h>
#include <string.h>
#include <math.h>

#define siez 19*19
#define rules 108

struct fractal_info
{
  unsigned short rule_num;
  unsigned short size;/*whole size */
  unsigned short block_size;
  unsigned short block_num;
  unsigned short rule2;
  unsigned short rule3;
} pixel;

char rule[rules][35]={0};
char input[4*4+3]=".#./..#/###";/*3x3*/

char ip_bf[81][4*4+3]={0};/*at most 18 blocks*/
char result[siez]={0};

void ro_fl(int,int,int);
int parse_result(struct fractal_info *);
int match_rule(struct fractal_info *);
int reconstruct(struct fractal_info *);
int print_result(struct fractal_info *);
int print_rule(int);
int print_ip_bf(struct fractal_info *);

int main(void)
{
  FILE * fp;  
  int c,rn,rnn,n;
  /*-------------open file-----------------*/
  if((fp=fopen("Day21.txt","r"))==NULL)
    printf("file open failed");
  /*--------load rules into array------------*/
  rnn=0;/*child subscript*/
  rn=0;/*parent subscript*/
  while((c=fgetc(fp))!=EOF)/*each line is one rule*/
    {
      if(c!=0xd)
	{rule[rn][rnn++]=c;}
      else
	{
	  fgetc(fp);/*0xa*/
	  rn++;/*new rule*/
	  rnn=0;
	}
    }
  rn++;
  pixel.rule_num=rn;  
  pixel.rule2=0;
  pixel.rule3=6;
  fclose(fp);
  /*------------------------------*/
  /*
  for(rnn=0;rnn<rn;rnn++)
    {
      printf("%03u: ",rnn);
      for(c=0;c<35;c++)
	{	  
	  fputc(rule[rnn][c],stdout);
	}
      printf("\n");
    }
  fgetc(stdin);
  */
  /*------------------------------*/
  pixel.size=n=3;  
  memcpy(result,input,n*n+(n-1));
  
  for(c=1;c<7;c++)
    {
      printf("Iterate: %u\n",c);
      parse_result(&pixel);
      match_rule(&pixel);
      printf("\n");
      reconstruct(&pixel);
    }  
  /*------------------------------*/
  
  for(n=0,c=0;c<19*19;c++)
    {
      if(result[c]=='#')
	n++;
    }
  printf("%u #\n",n);
  /*------------------------------*/
  
  return 0;
}

int parse_result(struct fractal_info * fip)
{
  /*parse result[], break it into ip_bf*/
  int n=fip->size;
  int a,b,s,fit,offset;
  /*-------print result-------------*/
  print_result(fip);
  /*--------parse------------*/  
  fit=offset=0;
  if(!(n%2))
    {
      fip->block_size=2;
      s=n/2;
      fip->block_num=s*s;
      for(b=0,a=0;a<s*s;a++)
	{
	  if(b==s)
	    {
	      b=0;
	      fit=fit+((n*2)+2);
	      offset=fit;
	    }
	  printf("%u[0]=%u ",a,offset);
	  ip_bf[a][0]=result[offset];
	  printf("%u[1]=%u ",a,offset+1);
	  ip_bf[a][1]=result[offset+1];

	  ip_bf[a][2]='/';
	  
	  printf("%u[3]=%u ",a,offset+n+1);
	  ip_bf[a][3]=result[offset+n+1];
	  printf("%u[4]=%u ",a,offset+n+2);
	  ip_bf[a][4]=result[offset+n+2];
	  
	  printf("\n");
	  b++;
	  offset+=2;
	}
      printf("result parsed into %u blocks\n",s*s);
      print_ip_bf(fip);    
    }
  /*--------------------*/
  else if(!(n%3))
    {
      fip->block_size=3;
      s=n/3;
      fip->block_num=s*s;
      
      for(b=0,a=0;a<s*s;a++)
	{
	  if(b==s)
	    {
	      b=0;
	      fit=fit+(n*3+3);
	      offset=fit;
	    }
	  printf("%u[0]=%u ",a,offset);
	  ip_bf[a][0]=result[offset];
	  printf("%u[1]=%u ",a,offset+1);
	  ip_bf[a][1]=result[offset+1];
	  printf("%u[2]=%u ",a,offset+2);
	  ip_bf[a][2]=result[offset+2];

	  ip_bf[a][3]=result[offset+3];

	  printf("%u[4]=%u ",a,offset+n+1);
	  ip_bf[a][4]=result[offset+n+1];
	  printf("%u[5]=%u ",a,offset+n+1+1);
	  ip_bf[a][5]=result[offset+n+1+1];
	  printf("%u[6]=%u ",a,offset+n+1+2);
	  ip_bf[a][6]=result[offset+n+1+2];

	  ip_bf[a][7]=result[offset+n+1+3];

	  printf("%u[8]=%u ",a,offset+n*2+2);
	  ip_bf[a][8]=result[offset+n*2+2];
	  printf("%u[9]=%u ",a,offset+n*2+2+1);
	  ip_bf[a][9]=result[offset+n*2+2+1];
	  printf("%u[10]=%u ",a,offset+n*2+2+2);
	  ip_bf[a][10]=result[offset+n*2+2+2];
	  
	  printf("\n");
	  b++;
	  offset+=3;
	}
      printf("result parsed into %u blocks\n",s*s);
      print_ip_bf(fip);
    }
  return 0;
}

int match_rule(struct fractal_info * fip)
{
  int a,b,c,r,blocks,rn,rnn,n;
  
  blocks=fip->block_num;
  rn=fip->rule_num;
  r=fip->block_size;
  n=r+1;/*2=>3 3=>4*/
  
  for(a=0;a<blocks;a++)/*ip_bf*/
    {
      b=0;
      if(r==2)
	{
	  rnn=fip->rule2;
	  rn=fip->rule3;
	}
      else if(r==3)
	{
	  rnn=fip->rule3;
	}
      
      for(;rnn<rn;rnn++)
	{
	  memcpy(input,ip_bf[a],r*r+(r-1));
	  
	  for(c=0;c<8;c++)/*7 type change, r90 r180 r270 fud frl fdia1 fdia2*/
	    {
	      if(!(memcmp(rule[rnn],input,r*r+(r-1))))
		{
		  printf("\nip_bf[%u] match rule[%u]\n",a,rnn);
		  print_rule(rnn);
		  memcpy(ip_bf[a],rule[rnn]+r*r+(r-1)+4,n*n+(n-1));/*expand*/
		  b=1;
		  break;
		}
	      else
		ro_fl(r,a,c);
	    }
	  
	  if(b)
	    {
	      fip->block_size=n;
	      break;
	    }
	}
    }

  fip->size=sqrt(fip->block_num) * fip->block_size;
  print_ip_bf(fip);
  return 0;
}


int reconstruct(struct fractal_info * fip)/*ip_bf into result one line*/
{
  int blocks=fip->block_num;
  int side_num=sqrt(blocks);
  int offset,line,step;
  int a,b,c,e;

  if(fip->block_size==3)
    {
      offset=e=0;
      for(a=0;a<blocks;)
	{
	  step=0;
	  for(b=0;b<side_num;b++)
	    {	     	      
	      line=e=0;
	      for(c=0;c<3;c++)
		{
		  result[offset+line+step+0]=ip_bf[a][e++];
		  result[offset+line+step+1]=ip_bf[a][e++];
		  result[offset+line+step+2]=ip_bf[a][e++];
		  e++;/*'/'*/
		  line=line+fip->size+1;
		}
	      a++;	      
	      step=step+3;			      
	    }
	  result[offset+(fip->size)]='/';
	  result[offset+(fip->size)*2+1]='/';
	  if(a<blocks)
	    result[offset+(fip->size)*3+2]='/';
	  offset=offset+(fip->size)*3+3;
	}      	
    }
  else if(fip->block_size==4)
    {
      offset=e=0;
      for(a=0;a<blocks;)
	{
	  step=0;
	  for(b=0;b<side_num;b++)
	    {
	      line=e=0;
	      for(c=0;c<4;c++)
		{
		  result[offset+line+step+0]=ip_bf[a][e++];
		  result[offset+line+step+1]=ip_bf[a][e++];
		  result[offset+line+step+2]=ip_bf[a][e++];
		  result[offset+line+step+3]=ip_bf[a][e++];
		  e++;
		  line=line+fip->size+1;
		}
	      a++;
	      step=step+4;
	    }
	  result[offset+(fip->size)]='/';
	  result[offset+(fip->size)*2+1]='/';
	  result[offset+(fip->size)*3+2]='/';
	  if(a<blocks)
	    result[offset+(fip->size)*4+3]='/';
	  offset=offset+(fip->size)*4+4;
	}
    }
  print_result(fip);
  return 0;
}

int print_result(struct fractal_info * fip)
{
  int a,b,s,n;
  n=fip->size;
  printf("result\n");
  printf("size:%u block_size:%u block_num:%u\n",fip->size,fip->block_size,fip->block_num);
  for(a=0,b=0,s=0;a<n*n+(n-1);a++)
    {
      if(b==n)/*coloum 0-n include '/'*/
	{
	  printf("%c\n",result[a]);
	  b=0;
	  s++;
	  continue;
	}
      else if(s==n)/*row*/
	break;
      else
	fputc(result[a],stdout);
      b++;
    }
  printf("\n\n");
  return 0;
}

int print_rule(int rnn)
{  
  int a;
  for(a=0;a<35;a++)
    fputc(rule[rnn][a],stdout);

  printf("\n");
  return 0;
}

int print_ip_bf(struct fractal_info * fip)
{
  int s=fip->block_num;  
  int len=fip->block_size;
  len=len*len+(len-1);
  int a,b;
  printf("ip_bf\n");
  for(a=0;a<s;a++)
    {
      for(b=0;b<len;b++)
	fputc(ip_bf[a][b],stdout);
      printf("\n");
    }
  return 0;
}

void ro_fl(int r,int a,int c)
{
  /*r:block_size, a:ip_bf[a], c: choose*/

  memcpy(input,ip_bf[a],r*r+(r-1));
  
  if(r==3)
    {
      switch(c)
	{
	case 0:/*rotate right 90*/
	  {
	    input[0]=ip_bf[a][8];
	    input[1]=ip_bf[a][4];
	    input[2]=ip_bf[a][0];

	    input[4]=ip_bf[a][9];	    
	    input[6]=ip_bf[a][1];
	    
	    input[8]=ip_bf[a][10];
	    input[9]=ip_bf[a][6];
	    input[10]=ip_bf[a][2];
	    break;
	  }
	case 1:/*rotate right 180*/
	  {
	    input[0]=ip_bf[a][10];
	    input[1]=ip_bf[a][9];
	    input[2]=ip_bf[a][8];
	    
	    input[4]=ip_bf[a][6];
	    input[6]=ip_bf[a][4];
	    
	    input[8]=ip_bf[a][2];
	    input[9]=ip_bf[a][1];
	    input[10]=ip_bf[a][0];
	    break;
	  }
	case 2:
	  {
	    input[0]=ip_bf[a][2];
	    input[1]=ip_bf[a][6];
	    input[2]=ip_bf[a][10];
	    
	    input[4]=ip_bf[a][1];
	    input[6]=ip_bf[a][9];
	    
	    input[8]=ip_bf[a][0];
	    input[9]=ip_bf[a][4];
	    input[10]=ip_bf[a][8];
	    break;
	  }
	case 3:
	  {
	    input[0]=ip_bf[a][8];
	    input[1]=ip_bf[a][9];
	    input[2]=ip_bf[a][10];
	    
	    input[4]=ip_bf[a][4];
	    input[6]=ip_bf[a][6];

	    input[8]=ip_bf[a][0];
	    input[9]=ip_bf[a][1];
	    input[10]=ip_bf[a][2];
	    break;
	  }
	case 4:
	  {
	    input[0]=ip_bf[a][2];
	    input[1]=ip_bf[a][1];
	    input[2]=ip_bf[a][0];

	    input[4]=ip_bf[a][6];
	    input[6]=ip_bf[a][4];
	    
	    input[8]=ip_bf[a][10];
	    input[9]=ip_bf[a][9];
	    input[10]=ip_bf[a][8];
	    break;
	  }
	case 5:
	  {
	    input[1]=ip_bf[a][4];
	    input[2]=ip_bf[a][8];

	    input[4]=ip_bf[a][1];
	    input[6]=ip_bf[a][9];
	    
	    input[8]=ip_bf[a][2];
	    input[9]=ip_bf[a][6];
	    break;
	  }
	case 6:
	  {
	    input[0]=ip_bf[a][10];
	    input[1]=ip_bf[a][6];

	    input[4]=ip_bf[a][9];
	    input[6]=ip_bf[a][1];
	    
	    input[9]=ip_bf[a][4];
	    input[10]=ip_bf[a][0];
	    break;
	  }
	default:break;
	}
      input[3]='/';
      input[7]='/';
    }  

  else if(r==2)
    {
      switch(c)
	{
	case 0:/*rotate right 90*/
	  {
	    input[0]=ip_bf[a][3];
	    input[1]=ip_bf[a][0];
	    input[3]=ip_bf[a][4];
	    input[4]=ip_bf[a][1];
	    break;
	  }	
	case 1:/*rotate right 180*/
	  {
	    input[0]=ip_bf[a][4];
	    input[1]=ip_bf[a][3];
	    input[3]=ip_bf[a][1];
	    input[4]=ip_bf[a][0];
	    break;
	  }	
	case 2:/*rotate right 360*/
	  {
	    input[0]=ip_bf[a][1];
	    input[1]=ip_bf[a][4];
	    input[3]=ip_bf[a][0];
	    input[4]=ip_bf[a][3];
	    break;
	  }	
	case 3:/*flip up down*/
	  {
	    input[0]=ip_bf[a][3];
	    input[1]=ip_bf[a][4];
	    input[3]=ip_bf[a][0];
	    input[4]=ip_bf[a][1];
	    break;
	  }	
	case 4:/*flip left right*/
	  {
	    input[0]=ip_bf[a][1];
	    input[1]=ip_bf[a][0];
	    input[3]=ip_bf[a][4];
	    input[4]=ip_bf[a][3];
	    break;
	  }
	case 5:
	  {
	    input[0]=ip_bf[a][4];
	    input[4]=ip_bf[a][0];
	    break;
	  }
	case 6:
	  {
	    input[1]=ip_bf[a][3];
	    input[3]=ip_bf[a][1];
	    break;
	  }
	default:break;
	}
      input[2]='/';
    }
}
