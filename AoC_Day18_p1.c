#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int intercode[41][5]={0};/*0:opcode 1:oprand1_flag 2:oprand1 3:oprand2_flag 4:oprand2*/
long int regs[26]={0};


int main(void)
{    
  FILE * fp;
  long int ic,fq;
  char tmpbuf[29]={0};
  char * tp;
  tp=tmpbuf;
  void postrans(int,char *);
  /*------------------------------*/
  if((fp=fopen("Day18.txt","r"))==NULL)
    printf("file open failed\n");
  /*------------------------------*/
  ic=0;
  while((tp=fgets(tp,29,fp))!=NULL)
    {
      
      postrans(ic++,tp);
    }
  /*------------------------------*/
  fclose(fp);
  /*------------------------------*/
  ic=0;
  while(ic>=0 && ic<41)
    {
      switch (intercode[ic][0])
	{
	case 225:
	  {
	    if(intercode[ic][1]==0)
	      fq=regs[intercode[ic][2]];
	    else
	      fq=intercode[ic][2];
	    ic++;
	    break;
	  }
	case 213:
	  {
	    if(intercode[ic][1]==0)
	      {
		if(regs[intercode[ic][2]]==0)
		  {ic++;break;}
		else
		  {printf("%ld\n",fq);ic++;break;}
	      }
	    else
	      {
		if(intercode[ic][2]==0)
		  {ic++;break;}
		else
		  {printf("%ld\n",fq);ic++;break;}
	      }
	  }
	case 216:
	  {
	    if(intercode[ic][3]==0)
	      regs[intercode[ic][2]]=regs[intercode[ic][4]];
	    else
	      regs[intercode[ic][2]]=intercode[ic][4];
	    ic++;
	    break;
	  }
	case 197:
	  {
	    if(intercode[ic][3]==0)
	      regs[intercode[ic][2]]+=regs[intercode[ic][4]];
	    else
	      regs[intercode[ic][2]]+=intercode[ic][4];
	    ic++;
	    break;
	  }
	case 226:
	  {
	    if(intercode[ic][3]==0)
	      regs[intercode[ic][2]]*=regs[intercode[ic][4]];
	    else
	      regs[intercode[ic][2]]*=intercode[ic][4];
	    ic++;
	    break;
	  }
	case 220:
	  {
	    if(intercode[ic][3]==0)
	      regs[intercode[ic][2]]%=regs[intercode[ic][4]];
	    else
	      regs[intercode[ic][2]]%=intercode[ic][4];
	    ic++;
	    break;
	  }
	case 209:
	  {
	    if(intercode[ic][1]==0)
	      {
		if(regs[intercode[ic][2]]>0)
		  {
		    if(intercode[ic][3]==0)
		      {ic+=regs[intercode[ic][4]];break;}
		    else
		      {ic+=intercode[ic][4];break;}
		  }
		else
		  {ic++;break;}
	      }
	    else
	      {
		if(intercode[ic][2]>0)
		  {
		    if(intercode[ic][3]==0)
		      {ic+=regs[intercode[ic][4]];break;}
		    else
		      {ic+=intercode[ic][4];break;}
		  }
		else
		  {ic++;break;}
	      }
	  }
	}
    }
  printf("%ld\n",fq);
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
  
  /*
  
  switch(opc)
    {
    case 225:
      {s="snd";break;}
    case 213:
      {s="rcv";break;}
    case 216:
      {s="set";break;}
    case 197:
      {s="add";break;}
    case 226:
      {s="mul";break;}
    case 220:
      {s="mod";break;}
    case 209:
      {s="jgz";break;}
    default:
      break;
    }
  printf("%s\n",s);
  */
}
