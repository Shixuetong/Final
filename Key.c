/************************************************************************
* 模块名称：按键控制
* 文件名称：KEY.c
*************************************************************************/
#include "LPC11xx.h"
#include "KEY.h"

uint8_t chance=1;

void KEY_Init()
{
LPC_GPIO3->DIR = 0xf8;
LPC_GPIO3->IE |= (1<<0);
LPC_GPIO3->IS &= ~(1<<0);
LPC_GPIO3->IEV &= ~(1<<0);
NVIC_EnableIRQ(EINT3_IRQn);
}
void PIOINT3_IRQHandler (void)
{
	uint32_t i,j;
	for(i=0;i<2500;i++)
	for(j=0;j<100;j++);
  if((LPC_GPIO3->MIS&(1<<0))==(1<<0))
	 {
		 if(chance==1) chance=0;
		 else chance=1;
		 LPC_GPIO3->IC = (1<<0);
	 } 
}
