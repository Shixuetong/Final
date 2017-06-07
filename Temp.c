/************************************************************************
* 模块名称：温度计算
* 文件名称：Temp.c
*************************************************************************/
#include "LPC11xx.h"
#include "Temp.h"
float mf58 (uint32_t AD)
{
	float r=0 , T=0;
	uint16_t k;
				
	r = (AD*10000)/(3296-AD);    
			
	if( (r<29371)&&(r>=18680) ) 	
	{
		k = 1069;
		T = ((29370-r)/k)+0;
	}
	else if( (r<18681)&&(r>=12240) )
	{
		k = 644;
		T = ((18680-r)/k)+10;
	}
	else if( (r<12241)&&(r>=8221) )	
	{
		k = 402;
		T = ((12240-r)/k)+20;
	}
	else if( (r<8222)&&(r>=5648) )	
	{
		k = 257;
		T = ((8221-r)/k)+30;
	}
	else if( (r<5649)&&(r>=3958) )	
	{
		k = 169;
		T = ((5648-r)/k)+40;
	}
	else if( (r<3959)&&(r>=2823) )	
	{
		k = 114;
		T = ((3959-r)/k)+50;
	}
	else if( (r<2824)&&(r>=2047) )	
	{
		k = 78;
		T = ((2824-r)/k)+60;
	}
	else if( (r<2048)&&(r>=1506) )	
	{
		k = 54;
		T = ((2048-r)/k)+70;
	}
	else if( (r<1507)&&(r>=1124) )	
	{
		k = 38;
		T = ((1507-r)/k)+80;
	}
	else if( (r<1125)&&(r>=850) )	
	{
		k = 27;
		T = ((1125-r)/k)+90;
	}
	else if( (r<851)&&(r>=651) )	
	{
		k = 20;
		T = ((851-r)/k)+100;
	}
	else if( (r<652)&&(r>=504) )	
	{
		k = 15;
		T = ((652-r)/k)+110;
	}
	else if( (r<505)&&(r>=395) )	
	{
		k = 11;
		T = ((505-r)/k)+120;
	}
	else if( (r<47731)&&(r>=29370) )
	{
		k = 1836;
		T = ((47730-r)/k)-10;
	}
	else if( (r<80361)&&(r>=47730) )
	{
		k = 3263;
		T = ((80360-r)/k)-20;
	}
	else if( (r<140001)&&(r>=80360) )
	{
		k = 5964;
		T = ((140000-r)/k)-30;
	}
	else if( (r<249600)&&(r>=140000) )
	{
		k = 10960;
		T = ((249600-r)/k)-40;
	}
	return T;
}


