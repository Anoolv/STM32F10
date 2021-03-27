/**********************************************************
 * @filename:spi_flash.c
 * @describe: spi��W25ϵ��оƬ  �ĳ�ʼ������д��������ͨ��
 *            �ȹ��ܺ�����ʵ��
 * *******************************************************/

#include "spi.h"
#include "W25X16.h"

void SPI_InitCfg()
{
    RCC->APB2ENR |= 0X00001008 ;
    GPIOB->CRH &= 0X0000FFFF ;
    GPIOB->CRH |= 0XB4BB ;

    SPI1->CR1 &= ~(0X000040CF) ;
    SPI1->CR1 |= 0X000040CF ;
    SPI1->CR2 &= ~(0X00000040) ;
    SPI1->CR2 |= 0X00000040 ;
}