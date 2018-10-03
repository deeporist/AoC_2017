#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*------------------------------*/

#define particle_num 1000/*0-999*/

struct particle
{
  int a[3];
  int v[3];
  int p[3];
};

struct particle pa[particle_num];

char buff[65]={0};

void parse_file(int);
void print_particle(int);
int distance(int,int);
void _distance(int,int);
void far(int, double);

/*------------------------------*/

int main(void)
{
  FILE * fp;
  memset(pa,0,sizeof(struct particle)*particle_num);
  char * bp;
  int c,i;
  /*------------------------------*/
  if((fp=fopen("Day20.txt","r")) == NULL)
    printf("file open failed\n");
  /*------------------------------*/
  i=0;
  while((c=fgetc(fp))!=EOF)
    {
      bp=buff;
      memset(buff,0,sizeof(char)*65);
      for(;c!=0xa;c=fgetc(fp))
	{*bp++=c;}
      parse_file(i);
      i++;
    }
  /*------------------------------*/  
  fclose(fp);
  /*------------------------------*/
  
  for(i=0;i<particle_num;i++)
    {
      for(c=i+1;c<particle_num;c++)
	distance(i,c);
    }
  
    /*------------------------------
  distance(137,138);
  _distance(137,138);
  ------------------------------*/
  return 0;
}

int distance(int a,int b)
{
  double qcoe,lcoe,cons,t1,t2,tb,ra,rb,rc,rd,re,rf;
  /*qcoe*t^2+lcoe*t+cons*/
  /*---------------X---------------*/
  qcoe=(double)(pa[a].a[0]-pa[b].a[0]);
  qcoe=qcoe/2;
  lcoe=(double)(pa[a].v[0]-pa[b].v[0]);
  lcoe=lcoe+qcoe;
  cons=(double)(pa[a].p[0]-pa[b].p[0]);

  if(qcoe==0)
    {
      if(lcoe==0)
	return 1;
      else
	t1=t2=(-1)*(cons/lcoe);
    }
  else
    {
      t1=((lcoe)*(lcoe))-(4*qcoe*cons);
      if(t1>0)
	{
	  t1=sqrt(t1);
	  tb=(-2)*qcoe;
	  t2=(lcoe+t1)/tb;
	  t1=(lcoe-t1)/tb;
	}
      else if(t1<0)
	return 1;
      else
	t1=t2=lcoe/((-2.0)*qcoe);
    }

  if((t1<0) && (t2<0))
    return 1;

  if(t1<t2)
    {tb=t1;t1=t2;t2=tb;}
  
  if(t2>0)
    {ra=t2;rb=t1;}
  else
    rb=ra=t1;
  /*---------------Y---------------*/
  qcoe=(double)(pa[a].a[1]-pa[b].a[1]);
  qcoe=qcoe/2;
  lcoe=(double)(pa[a].v[1]-pa[b].v[1]);
  lcoe=lcoe+qcoe;
  cons=(double)(pa[a].p[1]-pa[b].p[1]);

  if(qcoe==0)
    {
      if(lcoe==0)
	return 1;
      else
	t1=t2=(-1)*(cons/lcoe);
    }
  else
    {
      t1=((lcoe)*(lcoe))-(4*qcoe*cons);
      if(t1>0)
	{
	  t1=sqrt(t1);
	  tb=(-2)*qcoe;
	  t2=(lcoe+t1)/tb;
	  t1=(lcoe-t1)/tb;
	}
      else if(t1<0)
	return 1;
      else
	t1=t2=lcoe/((-2.0)*qcoe);
    }
  
  
  if((t1<0) && (t2<0))
    return 1;

  if((t1!=ra) && (t2!=ra) && (t1!=rb) && (t2!=rb))
    return 1;
  
  if(t1<t2)
    {tb=t1;t1=t2;t2=tb;}
  
  if(t2>0)
    {rc=t2;rd=t1;}
  else
    rc=rd=t1;
  
  /*---------------Z---------------*/
  qcoe=(double)(pa[a].a[2]-pa[b].a[2]);
  qcoe=qcoe/2;
  lcoe=(double)(pa[a].v[2]-pa[b].v[2]);
  lcoe=lcoe+qcoe;
  cons=(double)(pa[a].p[2]-pa[b].p[2]);

  if(qcoe==0)
    {
      if(lcoe==0)
	return 1;
      else
	t1=t2=(-1)*(cons/lcoe);
    }
  else
    {
      t1=((lcoe)*(lcoe))-(4*qcoe*cons);
      if(t1>0)
	{
	  t1=sqrt(t1);
	  tb=(-2)*qcoe;
	  t2=(lcoe+t1)/tb;
	  t1=(lcoe-t1)/tb;
	}
      else if(t1<0)
	return 1;
      else
	t1=t2=lcoe/((-2.0)*qcoe);
    }
  
  if((t1<0) && (t2<0))
    return 1;
  
  if(t1<t2)
    {tb=t1;t1=t2;t2=tb;}
  
  if(t2>0)
    {re=t2;rf=t1;}
  else
    re=rf=t1;
  /*------------------------------*/
  if((ra==rc || ra==rd) && (ra==re || ra==rf))
    printf("%d %d %f\n",a,b,ra);
  if((rb==rc || rb==rd) && (rb==re || rb==rf))
    printf("%d %d %f\n",a,b,rb);
  /*------------------------------*/
  
  return 0;
}

void _distance(int a,int b)
{
  double qcoe,lcoe,cons,t1,t2,tb;
  int i;
  /*------------------------------
  printf("particle %d:\n",a);
  print_particle(a);
  printf("particle %d:\n",b);
  print_particle(b);
  ------------------------------*/
  for(i=0;i<3;i++)
    {
      /*-------------------------
      
      printf("%c\n%f*t^2 + %f*t + %f\n",88+i,
	     (double)pa[a].a[i] / 2,
	     (double)pa[a].v[i] + (double)pa[a].a[i] / 2,
	     (double)pa[a].p[i]);
      printf("%f*t^2 + %f*t + %f\n",
	     (double)pa[b].a[i] / 2,
	     (double)pa[b].v[i] + (double)pa[b].a[i] / 2,
	     (double)pa[b].p[i]);
      
      -------------------------*/
      
      qcoe=(double)(pa[a].a[i]-pa[b].a[i]);
      qcoe=qcoe/2;
      lcoe=(double)(pa[a].v[i]-pa[b].v[i]);
      lcoe=lcoe+qcoe;
      cons=(double)(pa[a].p[i]-pa[b].p[i]);
      
      /*qcoe*t^2 + lcoe*t + cons*/
      /*printf("%f*t^2 + %f*t + %f ",qcoe,lcoe,cons);*/
      /*-------------------------
      t=14.0;
      s = qcoe * t * t + lcoe * t + cons;
      printf("%f\n",s);
      -------------------------*/      
      
      if(qcoe==0)
	{
	  if(lcoe==0)
	    t1=t2=-1.0;
	  else
	    t1=t2=(-1)*(cons/lcoe);
	}
      else
	{
	  t1=((lcoe)*(lcoe))-(4*qcoe*cons);
	  if(t1>0)
	    {
	      t1=sqrt(t1);
	      tb=(-2)*qcoe;
	      t2=(lcoe+t1)/tb;
	      t1=(lcoe-t1)/tb;	      
	    }
	  else if(t1<0)
	    t1=t2=-1.0;
	  else
	    t1=t2=lcoe/((-2.0)*qcoe);
	}
      
      printf("%c %f %f\n",88+i,t1,t2);
      
    }
  
  printf("\n");
}

void far(int x, double t)
{
  double p,v,a,s;
  int i;
  for(i=0;i<3;i++)
    {
      p=(double)pa[x].p[i];
      v=(double)pa[x].v[i];
      a=(double)pa[x].a[i];
      s = p + (v+(a/2))*t + (a/2)*t*t;
      printf("%f ",s);
    }
  printf("\n");
}

void parse_file(int i)
{
  char *ep;
  /*Position*/
  pa[i].p[0]=(int)strtol(&buff[3],&ep,10);
  
  pa[i].p[1]=(int)strtol(ep+1,&ep,10);

  pa[i].p[2]=(int)strtol(ep+1,&ep,10);
  /*velocity*/
  pa[i].v[0]=(int)strtol(ep+6,&ep,10);

  pa[i].v[1]=(int)strtol(ep+1,&ep,10);

  pa[i].v[2]=(int)strtol(ep+1,&ep,10);
  /*acceleration*/
  pa[i].a[0]=(int)strtol(ep+6,&ep,10);

  pa[i].a[1]=(int)strtol(ep+1,&ep,10);

  pa[i].a[2]=(int)strtol(ep+1,&ep,10);
  /*check*/
}

void print_particle(int i)
{
  printf("position: <%d %d %d>\n",pa[i].p[0],pa[i].p[1],pa[i].p[2]);
  printf("velocity: <%d %d %d>\n",pa[i].v[0],pa[i].v[1],pa[i].v[2]);
  printf("acceleration: <%d %d %d>\n\n",pa[i].a[0],pa[i].a[1],pa[i].a[2]);
}
