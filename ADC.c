/************************************************************************
* 模块名称：数模转换
* 文件名称：ADC.c
*************************************************************************/

#include "LPC11xx.h"
#include "ADC.h"

uint32_t ADCBuf , ADCFlag;
uint8_t Buff[20];                              

/*************************************************************************
*函数名：  ADC_Init
*函数功能：初始化ADC
**************************************************************************/

void ADC_Init (void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->R_PIO1_0 &=~0xbf;
	LPC_IOCON->R_PIO1_0 |= 0x02;
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
	LPC_SYSCON->PDRUNCFG &=~(0x01<<4);           
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	  
	LPC_ADC->CR = (0x01<<1)|((SystemCoreClock/1000000-1)<<8)|(0<<16)|(0<<17)|(0<<24)|(0<<27);	
}

/*******************************************
* 函数功能：读取电压值                   
********************************************/
uint32_t ADC_Read(uint8_t Channel)
{
	uint32_t adc_value=0;
	uint32_t ADCBuf=0;
	uint8_t i;
	
	for(i=0;i<50;i++)
	{
		adc_value = ((LPC_ADC->DR[Channel]>>6)&0x3FF);			    
		ADCBuf += adc_value;
	}
	adc_value = ADCBuf / 50;
	adc_value = (adc_value*3300)/1024; // 转换为真正的电压值
	
	return adc_value; 
}

/*************************************************************************
*函数名：  ADC_GetData
*函数功能：ADC 取值（十次平均）
**************************************************************************/
uint32_t ADC_GetData (void)
{
	uint32_t ADCDat=0 , ADCBuf=0;
	uint8_t i=0;

	for(i=0;i<10;i++)
	{
		LPC_ADC->CR |= (1<<24);
		while((LPC_ADC->DR[1]&0x80000000) == 0);
		LPC_ADC->CR |= (1<<24);
		while((LPC_ADC->DR[1]&0x80000000) == 0);
		ADCBuf = LPC_ADC->DR[1];//读取结果寄存器
		ADCBuf = (ADCBuf>>6)&0x3ff;//取10位数据
		ADCDat += ADCBuf;
	}
	ADCDat = ADCDat / 10;
	ADCDat = (ADCDat*3300)/1024;//数字量转模拟量
	
	return ADCDat;
}

/*************************************************************************
*函数名：  ADC_IRQHandler
*函数功能：ADC中断服务函数
**************************************************************************/
void ADC_IRQHandler (void)
{
	ADCBuf = LPC_ADC->DR[1];
	ADCBuf = (ADCBuf>>6)&0x3ff;
	ADCFlag = 1;
}

