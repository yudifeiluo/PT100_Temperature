#include<reg52.h>

#ifndef __KEYPORT_H__
#define __KEYPORT_H__

#define KeyPort P3	//�������ݶ˿�

extern char tempH;
extern char tempL;

void dlim(void);
unsigned char KeyScan(void);   //����ɨ��
void keyport(void);

#endif