/*******************************************************************************
 * Func:	clock_config.c
 * Describle: thiese functions are used to configure the SYStick,
 * 			for the function of delay.  
 * Created on: 2021��3��2��
 * Author: kaysen
*******************************************************************************/
#include "clock_config.h"


/*******************************************************************************
 * @�� �� ��         : delay_us
 * @��������		   : us��ʱ��
 * @��    ��         : nus��Ҫ��ʱ��us��
 *					ע��:nus��ֵ,��Ҫ����798915us(���ֵ��2^24/fac_us@fac_us=21)
 * @��    ��         : ��
 *******************************************************************************/
void delay_us(uint32_t us) 
{
	uint32_t temp;
	SysTick->LOAD = SystemCoreClock/8/ULTS*us; 		//ʱ�����,YSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8
	SysTick->VAL = 0x00;        					//��ռ�����
	SysTick->CTRL = 0x01;							//��ʼ����
	do 
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));		//�ȴ�ʱ�䵽��
	SysTick->CTRL = 0X00;								//�رռ�����
	SysTick->VAL = 0X00;      					 		//��ռ�����
}
 
/*******************************************************************************
 * �� �� ��         : delay_ms
 * ��������		   : ms��ʱ��
 * ��    ��         : nms��Ҫ��ʱ��ms��
 *					ע��:nms��ֵ,SysTick->LOADΪ24λ�Ĵ�����
 *					��Ҫ����0xffffff*8*1000/SYSCLK
 *					��72M������,nms<=1864ms
 * ��    ��         : ��
 *******************************************************************************/
void delay_ms(uint16_t ms) 
{
	u32 temp;
	SysTick->LOAD = (uint32_t)SystemCoreClock/8/MILLIS*ms;			//ʱ�����(SysTick->LOADΪ24bit)
	//SysTick->LOAD = (uint32_t)9000000/MILLIS*ms;
	SysTick->VAL = 0x00;											//��ռ�����
	SysTick->CTRL = 0x01;											//��ʼ����
	do 
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));					//�ȴ�ʱ�䵽��
	SysTick->CTRL = 0X00;											//�رռ�����
	SysTick->VAL = 0X00;      					 					//��ռ����� 
}

void delay_s(uint8_t s) 
{
	u32 temp;
	SysTick->LOAD = (u32)SystemCoreClock/8/SECOND*s;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;											//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;						//��ʼ����
	SysTick->CTRL = 0x01;											//��ʼ����
	do {
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));					//�ȴ�ʱ�䵽��
	SysTick->CTRL = 0X00;											//�رռ�����
	SysTick->VAL = 0X00;      					 					//��ռ�����  
}
