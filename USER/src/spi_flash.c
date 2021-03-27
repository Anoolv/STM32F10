/**********************************************************
 * @filename:spi_flash.c
 * @describe: spi和W25系列芯片  的初始化、读写、擦除和通信
 *            等功能函数的实现
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