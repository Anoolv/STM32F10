#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"


#define SPI1_PORT        GPIOB
#define SPI1_CS_PIN      GPIO_Pin_12
#define SPI1_SCK_PIN     GPIO_Pin_13
#define SPI1_MISO_PIN    GPIO_Pin_14
#define SPI1_MOSI_PIN    GPIO_Pin_15

void SPI_InitCfg();

#endif
