/*-----------------------------------------------
  ���ƣ�IICЭ�� PCF8591 AD/DAת�� ������������
  ��̳��www.doflye.net
  ��д��shifang
  �޸ģ���
  ���ݣ�ʹ��1·ad��������������ֵ�������õ��¶�ֵ���¶Ⱦ��ȺͶ��ֲ����йء�
------------------------------------------------*/  
#include <reg52.h>                
#include "i2c.h"
#include "delay.h"
#include "display.h"
#include "keyport.h"
#include "warning.h"


   /*code unsigned int  vt_table[]=	// ��ѹ�¶ȶ��ձ�
	{
		4132,4098,4063,4026,3988,3949,3908,3866,3823,3779,
		3733,3686,3639,3590,3540,3489,3437,3385,3331,3277,
		3222,3166,3110,3054,2997,2940,2882,2824,2767,2709,
		2651,2593,2536,2478,2421,2365,2309,2253,2198,2143,
		2089,2036,1984,1932,1881,1831,1782,1734,1686,1640,
		1594,1550,1506,1464,1422,1381,1341,1303,1265,1228,
		1192
	
	};	*/

#define AddWr 0x90   //д���ݵ�ַ PCF8591
#define AddRd 0x91   //�����ݵ�ַ PCF8591

extern bit ack;
unsigned char ReadADC(unsigned char Chl);
/*------------------------------------------------
              ������
------------------------------------------------*/
main()
{
double num;
double mv;
int temp;
  
Init_Timer0();

while (1)         //��ѭ��
{
 
 keyport();

 mv=ReadADC(0)*0.0196; //���v. ���ֵ255 ,255x19.6=5000mv��ʹ�ø���������Ӿ���   
 
 num=((mv/0.01961)-9.12);//�����¶�

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
 DelayMs(200);                    //��ʱ��ֹ�ɼ�Ƶ�ʹ���
  }
}
/*------------------------------------------------
             ��ADתֵ����
������� Chl ��ʾ��Ҫת����ͨ������Χ��0-3
����ֵ��Χ0-255
------------------------------------------------*/
  unsigned char ReadADC(unsigned char Chl)
 {
   unsigned char Val;
   Start_I2c();               //��������
   SendByte(AddWr);             //����������ַ
     if(ack==0)return(0);
   SendByte(0x40|Chl);            //���������ӵ�ַ
     if(ack==0)return(0);
   Start_I2c();
   SendByte(AddWr+1);
      if(ack==0)return(0);
   Val=RcvByte();
   NoAck_I2c();                 //���ͷ�Ӧλ
   Stop_I2c();                  //��������
  return(Val);
 }

