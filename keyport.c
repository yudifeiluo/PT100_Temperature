/*-----------------------------------------------
  名称：独立按键检测
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：
------------------------------------------------*/
#include <math.h>
#include "keyport.h"
#include "delay.h"
#include "display.h"
#include "i2c.h"

#define KeyPort P3	//定义按键端口


char tempH=100,tempL=1; 

/*------------------------------------------------
按键扫描函数，返回扫描键值
------------------------------------------------*/

void dlim()
{
   
   if(tempL<(-1e-20))
	 {
	 TempData[0]=0x40;
	 }
	 else
	 {
	 TempData[0]=0x00;
	 }
 if(tempH<1e-20)
	 {
	 TempData[4]=0x40;
	 }
	 else
	 {
	 TempData[4]=dofly_DuanMa[abs(tempH)/100];
	 }
 TempData[1]=dofly_DuanMa[abs(tempL)/10];
 TempData[2]=dofly_DuanMa[abs(tempL)%10];
 TempData[3]=dofly_DuanMa[11];
 TempData[5]=dofly_DuanMa[(abs(tempH)%100)/10];
 TempData[6]=dofly_DuanMa[(abs(tempH)%100)%10];
 TempData[7]=dofly_DuanMa[10];
 Init_Timer0();
 DelayMs(200);                    //延时防止采集频率过快
}

unsigned char KeyScan()
{
 unsigned char keyvalue;
 if(KeyPort!=0xff)
   {
    DelayMs(10);
    if(KeyPort!=0xff)
	   {
	    keyvalue=KeyPort;
	    
		while(KeyPort!=0xff);
	
		switch(keyvalue)
		{
		 case 0xfe:return 1;break;
		 case 0xfd:return 2;break;
		 case 0xfb:return 3;break;
		 case 0xf7:return 4;break;
		 case 0xef:return 5;break;
		 case 0xdf:return 6;break;
		 case 0xbf:return 7;break;
		 case 0x7f:return 8;break;
		 default:return 0;break;
		}
	  }
   }
   return 0;
}

void keyport()
{
 char num2;
 
 IRcvStr(0xae,4,&tempH,1); 
 IRcvStr(0xae,5,&tempL,1); 

 num2=KeyScan();
 if(5==num2)
       {
	    while(1)
		{
		 char num3;
		 dlim();
		 num3=KeyScan();
		 switch(num3)
		 {
		case 1:if(tempH<127)tempH++;ISendStr(0xae,4,&tempH,1);break;
		case 2:if(tempH>-55)tempH--;ISendStr(0xae,4,&tempH,1);break;
		case 3:if(tempL<127)tempL++;ISendStr(0xae,5,&tempL,1);break;
		case 4:if(tempL>-55)tempL--;ISendStr(0xae,5,&tempL,1);break;
		default:break; 
		 }
		  if(5==num3)
		  {
		  break;
		  }
		}
		
	   }	  
 }
