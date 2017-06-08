/************************************************************************
* ģ�����ƣ���ģת��
* �ļ����ƣ�ADC.c
*************************************************************************/

#include "LPC11xx.h"
#include "ADC.h"

uint32_t ADCBuf , ADCFlag;
uint8_t Buff[20];                              

/*************************************************************************
*��������  ADC_Init
*�������ܣ���ʼ��ADC
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
* ��������ADC_Read
* �������ܣ���ȡ��ѹֵ                   
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
	adc_value = (adc_value*3300)/1024; // ת��Ϊ�����ĵ�ѹֵ
	
	return adc_value; 
}

/*************************************************************************
*��������  ADC_GetData
*�������ܣ�ADC ȡֵ��ʮ��ƽ����
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
		ADCBuf = LPC_ADC->DR[1];//��ȡ����Ĵ���
		ADCBuf = (ADCBuf>>6)&0x3ff;//ȡ10λ����
		ADCDat += ADCBuf;
	}
	ADCDat = ADCDat / 10;
	ADCDat = (ADCDat*3300)/1024;//������תģ����
	
	return ADCDat;
}

/*************************************************************************
*��������  ADC_IRQHandler
*�������ܣ�ADC�жϷ�����
**************************************************************************/
void ADC_IRQHandler (void)
{
	ADCBuf = LPC_ADC->DR[1];
	ADCBuf = (ADCBuf>>6)&0x3ff;
	ADCFlag = 1;
}

