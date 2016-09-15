#include "delay.h"
#include "keyport.h"
#include "keyport.h"
#include "i2c.h"
sbit BEEP=P2^4;

void warn(double T)
{
  
 
   if((T>=tempH)||(T<=tempL))
   {
   	unsigned int i;
    for(i=0;i<200;i++)
      {
      DelayUs2x(200); 
	  BEEP=!BEEP;
	  }
	  BEEP=0;//防止一直给喇叭通电造成损坏
    for(i=0;i<200;i++)
      {
      DelayMs(1);  
	  }
	  BEEP=1;
   }
   else
   {
   BEEP=0;
   }       
}