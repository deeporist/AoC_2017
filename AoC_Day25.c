#include <stdio.h>

#define scale 20000

int main(void)
{
  int tape[scale]={0};
  int a,f,i,t,s;
  a=scale/2;
  s=0;
  f=0;/*0A 1B 2C 3D 4E 5F*/
  for(i=0;i<12459852;i++)
    {
      switch(f)
	{
	case 0:
	  {
	    t=(tape[a]==0)?(1):(-1);
	    f=(tape[a]==0)?1:4;
	    tape[a]=1;
	    a+=t;	    
	    break;
	  }
	case 1:
	  {
	    /*t=1;*/
	    f=(tape[a]==0)?2:5;
	    tape[a]=1;	    
	    /*a+=t;*/
	    a++;
	    break;
	  }
	case 2:
	  {
	    t=(tape[a]==0)?(-1):(1);
	    f=(tape[a]==0)?3:1;
	    tape[a]=!(tape[a]);	    
	    a+=t;
	    
	    break;
	  }
	case 3:
	  {
	    t=(tape[a]==0)?(1):(-1);
	    f=(tape[a]==0)?4:2;
	    tape[a]=!(tape[a]);	    
	    a+=t;
	    
	    break;
	  }
	case 4:
	  {
	    t=(tape[a]==0)?(-1):(1);
	    f=(tape[a]==0)?0:3;
	    tape[a]=!(tape[a]);	    
	    a+=t;
	    
	    break;
	  }
	case 5:
	  {
	    /*t=(tape[a]==0)?(1):(-1);*/
	    f=(tape[a]==0)?0:2;
	    tape[a]=1;	    
	    /*a+=t;*/
	    a++;
	    break;
	  }

	}
    }
  
  for(i=0;i<scale;i++)
    s+=tape[i];  
  printf("%u",s);

  return 0;
}
