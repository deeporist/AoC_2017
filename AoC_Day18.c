#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

long int ra,rb,rf,ri,rp;/*registers need to be long int!*/

int main(void)
{
  FILE * fp;
  
  int c,n;

  int instructs[41][3]={0};/*[0] ins, [1] op1, [2]op2*/
  int in;
  
  int last_sn;
  
  long int * r_p;
  
  char tni[10]={0};

  long int * change_rp(int);
  /*------------------------------*/
  if((fp=fopen("Day18_ex.txt","r")) == NULL)
    printf("open error\n");  
  /*---------preprocess---------------------*/
  c=in=0;
  while((c=fgetc(fp))!=EOF)
    {
      /*space 0x20; '-' 0x2d, lf 0xd*/      
      switch(c)
	{
	case 'F':
	case 'A':
	  {
	    instructs[in][0]=c;/*operator*/
	    fgetc(fp);/*space*/
	    
	    c=fgetc(fp);/*snd op1 register name, but may be a number!!!!!!!*/
	    if(isalpha(c))
	      {instructs[in][1]=c;}
	    else
	      {
		for(n=0;c!=0xd && c!=0x20 && c!=EOF;)/*get op1*/
		  {				  
		    tni[n++]=c;
		    c=fgetc(fp);
		  }
		tni[n]='\n';
		instructs[in][1]=atoi(tni);/*set op1*/		
	      }
	    in++;
	    break;
	  }
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'G':
	  {
	    instructs[in][0]=c;/*operator*/
	    fgetc(fp);/*space*/
	    	    
	    c=fgetc(fp);/*op1 register name, but may be a number!!!!!!!*/
	    if(isalpha(c))
	      {instructs[in][1]=c;fgetc(fp);}
	    else
	      {
		for(n=0;c!=0xd && c!=0x20 && c!=EOF;)/*get op1*/
		  {				  
		    tni[n++]=c;
		    c=fgetc(fp);
		  }
		tni[n]='\n';
		instructs[in][1]=atoi(tni);/*set op1*/
	      }	   	    

	    c=fgetc(fp);/*get op2*/
	    if(isalpha(c))/*register name*/
	      {instructs[in][2]=c;}
	    else/*number include sign*/
	      {
		for(n=0;c!=0xd && c!=EOF;)/*set op2*/
		  {				  
		    tni[n++]=c;
		    c=fgetc(fp);
		  }
		tni[n]='\n';
		instructs[in][2]=atoi(tni);/*set op2*/
	      }
	    in++;
	    break;
	  }
	default:break;	  
	}      
    }
  /*--------load successfully----------------------*/
  fclose(fp);
  /*------------RUN IT!------------------*/
  ra=rb=rf=ri=rp=0;
  last_sn=in=0;
  while(in<41)
    {
      c=instructs[in][1];
      if(isalpha(c))
	r_p=change_rp(c);
      else
	r_p=&(instructs[in][1]);
      
      switch(instructs[in][0])
	{
	  /*snd*/
	case 'A':
	  {	    
	    last_sn=*r_p;
	    in++;
	    break;
	  }
	  /*rcv*/
	case 'F':
	  {	    
	    if((*r_p)!=0)	      
	      {printf("last sound: %d\n",last_sn);return 0;}
	    in++;
	    break;
	  }
	  /*set*/
	case 'B':
	  {
	    if(isalpha(c=instructs[in][2]))
	      {*r_p=*(change_rp(c));}
	    else
	      {*r_p=c;}
	    in++;
	    break;
	  }
	  /*add*/
	case 'C':
	  {
	    if(isalpha(c=instructs[in][2]))
	      {*r_p=(*r_p) + (*(change_rp(c)));}
	    else
	      {*r_p=(*r_p) + c;}
	    in++;
	    break; 
	  }
	  /*mul*/
	case 'D':
	  {
	    if(isalpha(c=instructs[in][2]))
	      {*r_p=(*r_p) * (*(change_rp(c)));}
	    else
	      {*r_p=(*r_p) * (c);}
	    in++;
	    break;
	  }
	  /*mod*/
	case 'E':
	  {
	    if(isalpha(c=instructs[in][2]))
	      {*r_p=(*r_p) % (*(change_rp(c)));}
	    else
	      {*r_p=(*r_p) % c;}
	    in++;
	    break;
	  }
	  /*jgz*/
	case 'G':
	  {
	    if((*r_p)>0)
	      {
		if(isalpha(c=instructs[in][2]))
		  {in=in + (*(change_rp(c)));}
		else
		  in=in+c;		  
	      }
	    else
	      in++;
	    break;
	  }
	default:break;
	}      
    }

  /*------------------------------*/
  return 0;
}

long int * change_rp(int r)
{
  long int * t;
  switch(r)
    {
    case 'a':{t=&ra;break;}
    case 'b':{t=&rb;break;}
    case 'f':{t=&rf;break;}
    case 'i':{t=&ri;break;}
    case 'p':{t=&rp;break;}
    default:{break;}
    }
  
  return t;
}
