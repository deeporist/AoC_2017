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
int rule_3to9[rules][10]={0};/*0-8:rule[n]s  9: hashtag num*/
char input[4*4+3]={0};/*3x3*/

char ip_bf[81][4*4+3]={0};/*at most 18 blocks*/
char result[siez]={0};

void ro_fl(int,int,int);
int parse_result(struct fractal_info *);
int match_rule(struct fractal_info *);
int match_ruleEX(struct fractal_info * , int *);
int reconstruct(struct fractal_info *);
int print_result(struct fractal_info *);
int print_rule(int);
int print_ip_bf(struct fractal_info *);
void update_rule(struct fractal_info *);
int static_hashtag(void);
void print_rule_3to9(int);
long int recur_sum(int,int);

int main(void)
{
  FILE * fp;  
  int c,rn,rnn;
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

  /*----------update rule 0-5--------------------*/
  /*
  pixel.block_num=1;
  pixel.block_size=2;
  pixel.size=3;
  update_rule(&pixel);
  */
  /*0-5 can not be updated*/
  /*----------update rule 6-107--------------------*/
  
  pixel.block_num=1;
  pixel.block_size=3;
  pixel.size=4;
  update_rule(&pixel);
  
  /*------------check updated rules------------------*/
  /*
  for(rnn=0;rnn<rn;rnn++)
    print_rule(rnn);
  fgetc(stdin);
  */
  /*------------part 1------------------*/
  /*
  memcpy(result,".#./..#/###",11);
  */
  /*
  memcpy(result,"##./#.#/#..",11);
  pixel.size=3;
  
  for(c=1;c<6;c++)
    {
      printf("\nIterate: %u\n",c);
      parse_result(&pixel);
      match_rule(&pixel);      
      reconstruct(&pixel);
    }
  printf("\n%u\n",static_hashtag());
  */
  /* 
  match_ruleEX(&pixel,rule_3to9[0]);
  print_rule_3to9(0);
  static_hashtag();
  */
  /*------------------------------*/
  /*parse 6-107 rule's inputs to fill 3to9*/
  
  for(rnn=6;rnn<rn;rnn++)
    {
      print_rule(rnn);
      memcpy(result,rule[rnn],11);
      pixel.size=3;

      for(c=1;c<4;c++)
	{
	  printf("\nIterate: %u\n",c);
	  parse_result(&pixel);
	  match_rule(&pixel);
	  reconstruct(&pixel);
	}
      rule_3to9[rnn][9]=static_hashtag();
      match_ruleEX(&pixel,rule_3to9[rnn]);      
    }
  /*
  for(rnn=0;rnn<rn;rnn++)
    {print_rule_3to9(rnn);}
  */
  /*-----------part 2-------------------*/
  
  rnn=recur_sum(62,8);
  printf("\n%u\n",rnn);
  
  /*------------------------------*/
  
  return 0;
}

int parse_result(struct fractal_info * fip)
{
  /*parse result[], break it into ip_bf*/  
  int a,b,c,s,step,offset;
  /*-------print result-------------*/
  print_result(fip);
  /*--------parse------------*/  
  offset=0;
  int n=fip->size;
  int line=n+1;
  if(!(n%2))
    {
      fip->block_size=2;
      s=(fip->size)/2;/*single side block num*/
      fip->block_num=s*s;
      
      for(a=0;a<s*s;)/*block num*/
	{
	  step=0;
	  for(b=0;b<s;b++)/*i result line s block*/
	    {
	      /*--------------------*/
	      ip_bf[a][0]=result[offset+step];
	      ip_bf[a][1]=result[offset+step+1];
	      ip_bf[a][2]='/';
	      /*--------------------*/
	      ip_bf[a][3]=result[offset+step+line];
	      ip_bf[a][4]=result[offset+step+line+1];
	      /*--------------------*/
	      step+=2;
	      a++;
	    }
	  offset=offset+line*2;	  
	}       
    }
  /*--------------------*/
  
  else if(!(n%3))
    {
      fip->block_size=3;
      s=n/3;
      fip->block_num=s*s;
      
      for(a=0;a<s*s;)
	{
	  step=0;
	  for(b=0;b<s;b++)/*1 block line*/
	    {
	      for(c=0;c<3;c++)/*1 block 3 line*/
		{
		  ip_bf[a][c]=result[offset+step+c];
		  ip_bf[a][c+4]=result[offset+step+line+c];
		  ip_bf[a][c+8]=result[offset+step+line*2+c];
		}
	      ip_bf[a][3]=ip_bf[a][7]='/';
	      step+=3;
	      a++;
	    }
	  offset=offset+line*3;
	}            
    }
  
  printf("parsed into %u blocks, block_size:%u\n",s*s,fip->block_size);
  print_ip_bf(fip);
  
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
		  printf("ip_bf[%u] match ",a);
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
  print_ip_bf(fip);
  return 0;
}

int match_ruleEX(struct fractal_info * fip, int * rp)
{
  /*record rule_3to9*/
  parse_result(&pixel);/*result -> ip_bf*/
  
  int a,b,c,rnn;
  for(a=0;a<9;a++)
    {
      b=0;
      for(rnn=6;rnn<108;rnn++)
	{
	  memcpy(input,ip_bf[a],11);
	  for(c=0;c<8;c++)
	    {
	      if(!(memcmp(rule[rnn],input,11)))
		{
		  printf("ip_bf[%u] match ",a);
		  print_rule(rnn);
		  *rp=rnn;
		  rp++;
		  b=1;
		  break;
		}
	      else
		ro_fl(3,a,c);
	    }
	  if(b)
	    break;
	}      
    }
  return 0;
}

int reconstruct(struct fractal_info * fip)/*ip_bf into result one line*/
{
  fip->size=sqrt(fip->block_num) * fip->block_size;
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
  else if(fip->block_size==2)
    {
      offset=0;
      for(a=0;a<4;)/*4 blocks*/
	{
	  step=0;
	  for(b=0;b<2;b++)/*1 line 2 block*/
	    {
	      line=e=0;
	      for(c=0;c<2;c++)/*1 block 2 line*/
		{
		  result[offset+step+line+0]=ip_bf[a][e++];
		  result[offset+step+line+1]=ip_bf[a][e++];
		  e++;/*jump over '/' in block*/
		  line+=5;/*next line*/
		}
	      a++;
	      step+=2;
	    }
	  result[offset+4]='/';
	  if(a<4)
	    result[offset+9]='/';
	  offset+=10;
	}
    }
  print_result(fip);
  return 0;
}

void update_rule(struct fractal_info * fip)
{
  /*
rule -> result
result -parsed-> ip_bf
ip_bf -change-> new ip_bf
new ip_bf -reconstruct-> result
result -> rule

*/
  int a,b,c,d,ri,ro,rs,re,cs,ce,rnn,n;

  ri=fip->block_size;/*rule input*/
  ro=fip->size;/*rule output*/
  if(ri==2)/*0-5*/
    {
      cs=0;ce=6;/*update scale*/
      rs=6;re=108;/*match scale*/
    }
  else if(ri==3)/*6-107*/
    {
      cs=6;ce=108;
      rs=0;re=6;
    }
  
  int offset,len;
  offset=ri*ri+(ri-1)+4;/*rule output offset*/
  len=ro;
  len=len*len+(len-1);/*output length*/
  
  for(rnn=cs;rnn<ce;rnn++)/*rules*/
    {      
      print_rule(rnn);

      memcpy(result,rule[rnn]+offset,len);/*rule -> result*/

      fip->size=ro;
      parse_result(fip);/*result -> ip_bf*/
      n=fip->block_size;/*ip_bf length*/
      
      for(a=0;a<fip->block_num;a++)/*ip_bf s*/
	{
	  d=0;
	  for(b=rs;b<re;b++)/*target rules*/
	    {
	      memcpy(input,ip_bf[a],n*n+(n-1));
	      for(c=0;c<8;c++)
		{
		  if(!(memcmp(rule[b],input,n*n+(n-1))))
		    {		      		      
		      d=1;
		      break;
		    }
		  else
		    ro_fl(n,a,c);
		}
	      if(d)
		break;
	    }
	  printf("match ");
	  print_rule(b);
	  memcpy(ip_bf[a],rule[b],n*n+(n-1));
	}
      print_ip_bf(fip);
      reconstruct(fip);
      memcpy(rule[rnn]+offset,result,len);
      print_rule(rnn);
      printf("\n");

    }  
}

int print_result(struct fractal_info * fip)
{
  int a,b,cn,n;
  n=fip->size;
  cn=n*n+n-1;/*charters sum*/
  
  printf("result\n");
  for(a=0;a<cn;a++)
    {
      for(b=0;b<n;b++)
	fputc(result[a++],stdout);
      if(a<cn)
	fputc(result[a],stdout);
      printf("\n");
    }  
  return 0;
}

int print_rule(int rnn)
{  
  int a;
  printf("rule-%02u: ",rnn);
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
	/*printf("%u-%u ",a,b);*/
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

int static_hashtag(void)
{
  int a,c;
  for(a=0,c=0;c<19*19;c++)
    {
      if(result[c]=='#')
	a++;
    }
  /*printf("%u\n\n",a);*/
  return a;
}

void print_rule_3to9(int n)
{
  int a;
  printf("rule_3to9[%03u]: ",n);
  for(a=0;a<10;a++)
    printf("%02u ",rule_3to9[n][a]);
  printf("\n");
}

long int recur_sum(int r,int n)
{
  /*rule_3to9*/
  int a,s=0;
  /*a public variable set tp 0 befor call this function*/
  if(n==0)/*this 3x3 is one of the last recu's 9x9r*/
    return 0;
  else if(n==1)
    {      
      return rule_3to9[r][9];
    }

  else/*n>1*/
    {
      
      for(a=0;a<9;a++)
	s+=recur_sum(rule_3to9[r][a],n-1);
    }
  
  return s;
}
