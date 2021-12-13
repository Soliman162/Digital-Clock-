#ifndef  RCC_INTERFACE_H
#define  RCC_INTERFACE_H

/*ENABLE_CLK_BUSS*/
#define AHB_BUS            0
#define APB2_BUS           1
#define APB1_BUS           2

/*AHB_Peripherals*/
#define DMA1_Peripheral    0
#define DMA2    1
#define SRAM    2
#define FLITF   4
#define CRC     6
#define FSMC    8
#define SDIO    10

/*APB2_Peripherals*/
#define AFIO_PRE    0
#define IOPA    2
#define IOPB    3
#define IOPC    4
#define IOPD    5
#define IOPE    6
#define IOPF    7
#define IOPG    8
#define ADC1    9
#define ADC2    10
#define TIM1    11
#define SPI1_Peripheral    12
#define TIM8    13
#define USART1  14
#define ADC3    15
#define TIM9    19
#define TIM10   20  
#define TIM11   21

/*APB1_Peripherals*/
#define TIM2    0
#define TIM3    1
#define TIM4    2
#define TIM5    3
#define TIM6    4
#define TIM7    5
#define TIM12   6
#define TIM13   7
#define TIM14   8
#define WWDG_Peripheral    11
#define SPI2    14
#define SPI3    15
#define USART2  17  
#define USART3  18
#define UART4   19 
#define UART5   20 
#define I2C1    21
#define I2C2    22
#define USB     23
#define CAN     25
#define BKP     27
#define PWR     28
#define DAC     29

void RCC_voidCLKInit(void);
ERROR_enumSTATE   RCC_enumPeripheralCLKEnable( u8 Copy_u8BUS ,u8 Copy_u8Peripheral);
ERROR_enumSTATE   RCC_enumPeripheralCLKDisable( u8 Copy_u8BUS ,u8 Copy_u8Peripheral);

#endif
