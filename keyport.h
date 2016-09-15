#include<reg52.h>

#ifndef __KEYPORT_H__
#define __KEYPORT_H__

#define KeyPort P3	//定义数据端口

extern char tempH;
extern char tempL;

void dlim(void);
unsigned char KeyScan(void);   //键盘扫描
void keyport(void);

#endif