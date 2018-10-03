#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int intercode[41][5]={0};
/*0:opcode 1:oprand1_flag 2:oprand1 3:oprand2_flag 4:oprand2*/
long int regs1[26]={0};
long int regs2[26]={0};
long int ic1,ic2;
long int buff1[10]={0};
long int buff2[10]={0};
int head1,tail1,head2,tail2;
void snd1(int);
void snd2(int);
int rcv1();
int rcv2();

int main(void)
{    
  FILE * fp;
  char tmpbuf[29]={0};
  char * tp;
  tp=tmpbuf;
  void postrans(int,char *);
  int player1();
  int player2();
  /*------------------------------*/
  if((fp=fopen("Day18.txt","r"))==NULL)
    printf("file open failed\n");
  /*------------------------------*/
  int i=0;
  while((tp=fgets(tp,29,fp))!=NULL)
    {
      postrans(i++,tp);
    }
  /*------------------------------*/
  fclose(fp);
  /*------------------------------*/
  int a,b;
  a=b=1;
  ic1=ic2=0;
  head1=tail1=head2=tail2=0;
  while(a*b)
    {
      a=player1();
      b=player2();
    }
  /*------------------------------*/
  
  /*------------------------------*/
  return 0;
}

void postrans(int ic,char * tp)
{  
  int opc,opr;

  opc=*tp+*(tp+1);
  intercode[ic][0]=opc;
  
  opr=*(tp+4);
  if(opr>=97 && opr<=122)
    {intercode[ic][1]=0;intercode[ic][2]=opr-97;}/*map to index*/
  else if(opr>=48 && opr<=57)
    {intercode[ic][1]=1;intercode[ic][2]=(int)strtol(tp+4,NULL,10);}
  else if(opr==0x2d)
    {intercode[ic][1]=1;intercode[ic][2]=(-1)*((int)strtol(tp+5,NULL,10));}
  else
    printf("Wrong oprand\n");

  if(opc!=225 && opc!=213)
    {
      opr=*(tp+6);
      if(opr>=97 && opr<=122)
	{intercode[ic][3]=0;intercode[ic][4]=opr-97;}
      else if(opr>=48 && opr<=57)
	{intercode[ic][3]=1;intercode[ic][4]=(int)strtol(tp+6,NULL,10);}
      else if(opr==0x2d)
	{intercode[ic][3]=1;intercode[ic][4]=(-1)*((int)strtol(tp+7,NULL,10));}
      else
	printf("Wrong oprand\n");
    }
  
  printf("%d %d %d %d %d\n",intercode[ic][0],intercode[ic][1],intercode[ic][2],intercode[ic][3],intercode[ic][4]);
  
}


void snd1(int fq)
{
  buff2[tail2%10]=fq;
  tail2++;
  if((tail2-head2)>10)
    printf("buff2 overflow!\n");
}

void snd2(int fq)
{
  buff1[tail1%10]=fq;
  tail1++;
  if((tail1-head1)>10)
    printf("buff1 overflow!\n");
}

int rcv1()
{
  if(tail1<=head1)
    return 0;
  else
    return head1;
}

int rcv2()
{
  if(tail2<=head2)
    return 0;
  else
    return head2;
}


int player1()
{
  int rcv,fq;
  if(ic1<0 || ic1>40)
    return 0;
  
  switch (intercode[ic1][0])
	{
	case 225:/*snd*/
	  {
	    if(intercode[ic1][1]==0)
	      fq=regs1[intercode[ic1][2]];
	    else
	      fq=intercode[ic1][2];
	    snd1(fq);
	    ic1++;
	    break;
	  }
	case 213:/*rcv*/
	  {
	    rcv=rcv1();
	    
	    if(rcv!=0)
	      {
		regs1[intercode[ic1][2]]=buff1[rcv%10];
		ic1++;
		head1++;
		break;
	      }
	    else
	      {
		break;
	      }
	    
	  }
	case 216:
	  {
	    if(intercode[ic1][3]==0)
	      regs1[intercode[ic1][2]]=regs1[intercode[ic1][4]];
	    else
	      regs1[intercode[ic1][2]]=intercode[ic1][4];
	    ic1++;
	    break;
	  }
	case 197:
	  {
	    if(intercode[ic1][3]==0)
	      regs1[intercode[ic1][2]]+=regs1[intercode[ic1][4]];
	    else
	      regs1[intercode[ic1][2]]+=intercode[ic1][4];
	    ic1++;
	    break;
	  }
	case 226:
	  {
	    if(intercode[ic1][3]==0)
	      regs1[intercode[ic1][2]]*=regs1[intercode[ic1][4]];
	    else
	      regs1[intercode[ic1][2]]*=intercode[ic1][4];
	    ic1++;
	    break;
	  }
	case 220:
	  {
	    if(intercode[ic1][3]==0)
	      regs1[intercode[ic1][2]]%=regs1[intercode[ic1][4]];
	    else
	      regs1[intercode[ic1][2]]%=intercode[ic1][4];
	    ic1++;
	    break;
	  }
	case 209:
	  {
	    if(intercode[ic1][1]==0)
	      {
		if(regs1[intercode[ic1][2]]>0)
		  {
		    if(intercode[ic1][3]==0)
		      {ic1+=regs1[intercode[ic1][4]];break;}
		    else
		      {ic1+=intercode[ic1][4];break;}
		  }
		else
		  {ic1++;break;}
	      }
	    else
	      {
		if(intercode[ic1][2]>0)
		  {
		    if(intercode[ic1][3]==0)
		      {ic1+=regs1[intercode[ic1][4]];break;}
		    else
		      {ic1+=intercode[ic1][4];break;}
		  }
		else
		  {ic1++;break;}
	      }
	  }

	}
  return 1;	
}

int player2()
{
  int rcv,fq;
  if(ic2<0 || ic2>40)
    return 0;
  switch (intercode[ic2][0])
	{
	case 225:/*snd*/
	  {
	    if(intercode[ic2][1]==0)
	      fq=regs2[intercode[ic2][2]];
	    else
	      fq=intercode[ic2][2];
	    snd2(fq);
	    ic2++;
	    break;
	  }
	case 213:/*rcv*/
	  {
	    rcv=rcv2();
	    if(rcv!=0)
	      {
		regs2[intercode[ic2][2]]=buff2[rcv%10];
		ic2++;
		head2++;
		break;
	      }
	    else
	      {
		break;
	      }
	  }
	case 216:
	  {
	    if(intercode[ic2][3]==0)
	      regs2[intercode[ic2][2]]=regs2[intercode[ic2][4]];
	    else
	      regs2[intercode[ic2][2]]=intercode[ic2][4];
	    ic2++;
	    break;
	  }
	case 197:
	  {
	    if(intercode[ic2][3]==0)
	      regs2[intercode[ic2][2]]+=regs2[intercode[ic2][4]];
	    else
	      regs2[intercode[ic2][2]]+=intercode[ic2][4];
	    ic2++;
	    break;
	  }
	case 226:
	  {
	    if(intercode[ic2][3]==0)
	      regs2[intercode[ic2][2]]*=regs2[intercode[ic2][4]];
	    else
	      regs2[intercode[ic2][2]]*=intercode[ic2][4];
	    ic2++;
	    break;
	  }
	case 220:
	  {
	    if(intercode[ic2][3]==0)
	      regs2[intercode[ic2][2]]%=regs2[intercode[ic2][4]];
	    else
	      regs2[intercode[ic2][2]]%=intercode[ic2][4];
	    ic2++;
	    break;
	  }
	case 209:
	  {
	    if(intercode[ic2][1]==0)
	      {
		if(regs2[intercode[ic2][2]]>0)
		  {
		    if(intercode[ic2][3]==0)
		      {ic2+=regs2[intercode[ic2][4]];break;}
		    else
		      {ic2+=intercode[ic2][4];break;}
		  }
		else
		  {ic2++;break;}
	      }
	    else
	      {
		if(intercode[ic2][2]>0)
		  {
		    if(intercode[ic2][3]==0)
		      {ic2+=regs2[intercode[ic2][4]];break;}
		    else
		      {ic2+=intercode[ic2][4];break;}
		  }
		else
		  {ic2++;break;}
	      }
	  }

	}
  return 1;
}
