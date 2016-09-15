/*-----------------------------------------------
  名称：IIC协议 PCF8591 AD/DA转换 测试热敏电阻
  论坛：www.doflye.net
  编写：shifang
  修改：无
  内容：使用1路ad测试热敏电阻阻值，并查表得到温度值，温度精度和多种参数有关。
------------------------------------------------*/  
#include <reg52.h>                
#include "i2c.h"
#include "delay.h"
#include "display.h"
#include "keyport.h"
#include "warning.h"


   /*code unsigned int  vt_table[]=	// 电压温度对照表
	{
		4132,4098,4063,4026,3988,3949,3908,3866,3823,3779,
		3733,3686,3639,3590,3540,3489,3437,3385,3331,3277,
		3222,3166,3110,3054,2997,2940,2882,2824,2767,2709,
		2651,2593,2536,2478,2421,2365,2309,2253,2198,2143,
		2089,2036,1984,1932,1881,1831,1782,1734,1686,1640,
		1594,1550,1506,1464,1422,1381,1341,1303,1265,1228,
		1192
	
	};	*/

#define AddWr 0x90   //写数据地址 PCF8591
#define AddRd 0x91   //读数据地址 PCF8591

extern bit ack;
unsigned char ReadADC(unsigned char Chl);
/*------------------------------------------------
              主程序
------------------------------------------------*/
main()
{
double num;
double mv;
int temp;
  
Init_Timer0();

while (1)         //主循环
{
 
 keyport();

 mv=ReadADC(0)*0.0196; //变成v. 最大值255 ,255x19.6=5000mv，使用浮点计算增加精度   
 
 num=((mv/0.01961)-9.12);//计算温度

 warn(num);
 num=num*100;
if(num<1e-20)
 {
 TempData[0]=0x40;
 }
else
{
 TempData[0]=0x00;
} 
TempData[0]=0x00;
 temp=num;
TempData[1]=dofly_DuanMa[temp/10000];
TempData[2]=dofly_DuanMa[(temp%10000)/1000];
 TempData[3]=dofly_DDuanMa[((temp%10000)%1000)/100];
 TempData[4]=dofly_DuanMa[(((temp%10000)%1000)%100)/10];
 TempData[5]=dofly_DuanMa[(temp%100)%10];
 TempData[6]=dofly_DuanMa[12];
 TempData[7]=dofly_DuanMa[12];
 DelayMs(200);                    //延时防止采集频率过快
  }
}
/*------------------------------------------------
             读AD转值程序
输入参数 Chl 表示需要转换的通道，范围从0-3
返回值范围0-255
------------------------------------------------*/
  unsigned char ReadADC(unsigned char Chl)
 {
   unsigned char Val;
   Start_I2c();               //启动总线
   SendByte(AddWr);             //发送器件地址
     if(ack==0)return(0);
   SendByte(0x40|Chl);            //发送器件子地址
     if(ack==0)return(0);
   Start_I2c();
   SendByte(AddWr+1);
      if(ack==0)return(0);
   Val=RcvByte();
   NoAck_I2c();                 //发送非应位
   Stop_I2c();                  //结束总线
  return(Val);
 }

