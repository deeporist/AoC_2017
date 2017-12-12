#include <stdio.h>

int main(void)
{
  FILE * fp;
  char c;
  int n;
  int rec[8224]={0};
  /*---------open file-----------*/
  if((fp=fopen("Day11_ex.txt","r")) == NULL)
    {printf("file open failed\n");return 1;}
  
  /*---------get numric rec-----------*/
  n=0;
  while((c=fgetc(fp))!=EOF)
    {
      if(!(c==','))
	rec[n++]=c^(0x30);
    }
  rec[8223]=9;
  printf("%u,%u,%u\n\n",n,rec[8222],rec[8223]);
  /*--------------------*/
  n=0;
  int n1,n2,n3,n4,n5,n6;
  n1=n2=n3=n4=n5=n6=0;
  while(n<8224)
    {
      switch(rec[n])
	{
	case 1:{n1++;break;}
	case 2:{n2++;break;}
	case 3:{n3++;break;}	  
	case 4:{n4++;break;}
	case 5:{n5++;break;}
	case 6:{n6++;break;}
	default:break;
	}
      n++;
    }
  printf("%u %u %u %u %u %u \n\n",n1,n2,n3,n4,n5,n6);
  /*--------------------*/
  /*nw=1 n=2 ne=3*/
  /*sw=4 s=5 se=6*/
  /*discared=0 end=9*/
  n=0;
  while(n<8224)
    {
      switch(rec[n])
	{
	case 1:
	  {
	    switch(rec[n+1])
	      {
	      case 3:{rec[n]=0;rec[n+1]=2;break;}
	      case 5:{rec[n]=0;rec[n+1]=5;break;}
	      case 6:{rec[n]=0;rec[n+1]=0;break;}
	      default:{n++;break;}
	      }
	    break;
	  }

	case 2:
	  {
	    switch(rec[n+1])
	      {
		case 4:{rec[n]=0;rec[n+1]=1;break;}
	      case 5:{rec[n]=0;rec[n+1]=0;break;}
	      case 6:{rec[n]=0;rec[n+1]=3;break;}
		default:{n++;break;}
	      }
	    break;
	  }

	case 3:
	  {
	    switch(rec[n+1])
	      {
		case 1:{rec[n]=0;rec[n+1]=2;break;}
	      case 4:{rec[n]=0;rec[n+1]=0;break;}
	      case 5:{rec[n]=0;rec[n+1]=6;break;}
		default:{n++;break;}
	      }
	    break;
	  }

	case 4:
	  {
	    switch(rec[n+1])
	      {
		case 2:{rec[n]=0;rec[n+1]=1;break;}
	      case 3:{rec[n]=0;rec[n+1]=0;break;}
	      case 6:{rec[n]=0;rec[n+1]=5;break;}
		default:{n++;break;}
	      }
	    break;
	  }

	case 5:
	  {
	    switch(rec[n+1])
	      {
		case 1:{rec[n]=0;rec[n+1]=4;break;}
	      case 2:{rec[n]=0;rec[n+1]=0;break;}
	      case 3:{rec[n]=0;rec[n+1]=6;break;}
		default:{n++;break;}
	      }
	    break;
	  }

	case 6:
	  {
	    switch(rec[n+1])
	      {
		case 1:{rec[n]=0;rec[n+1]=0;break;}
	      case 2:{rec[n]=0;rec[n+1]=3;break;}
	      case 4:{rec[n]=0;rec[n+1]=5;break;}
		default:{n++;break;}
	      }
	    break;
	  }
	  /*rec[n]==0*/
	default:
	  {n++;break;}
	}
    }
  /*--------------------*/
  /*--------------------*/
  
  fclose(fp);
  return 0;
}
