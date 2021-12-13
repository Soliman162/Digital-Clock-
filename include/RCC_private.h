#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/*CR_BITS*/
#define  HSION          0         
#define  HSIRDY         1 
#define  HSEON          16 
#define  HSERDY         17 
#define  HSEBYP         18
#define  CSSON          19 
#define  PLLON          24 
#define  PLLRDY         25 

/*CFGR_BITS*/
#define SW_0                    0           
#define SW_1                    1       
#define SWS_2                   2      
#define SWS_3                   3      
#define HPRE_4                  4     
#define HPRE_5                  5     
#define HPRE_6                  6     
#define HPRE_7                  7     
#define PPRE1_8                 8    
#define PPRE1_9                 9    
#define PPRE1_10                10       
#define PPRE2_11                11       
#define PPRE2_12                12       
#define PPRE2_13                13       
#define ADCPRE_14               14      
#define ADCPRE_15               15      
#define PLLSRC_16               16      
#define PLLXTPRE_17             17             
#define PLLMUL_18               18      
#define PLLMUL_19               19      
#define PLLMUL_20               20      
#define PLLMUL_21               21      
#define USBPRE_22               22      
#define MCO_24                  24     
#define MCO_25                  25     
#define MCO_26                  26     


/*CLK_SOURCE*/
#define  HSE    0
#define  HSI    1
#define  PLL    2

/*HSE_TYPE*/
#define CRYSTAL     0
#define RC          1

/*PRESCALLERS*/
#define DIVIDEDBY_1             1
#define DIVIDEDBY_2             2
#define DIVIDEDBY_4             4
#define DIVIDEDBY_8             8
#define DIVIDEDBY_16            16  
#define DIVIDEDBY_64            64   
#define DIVIDEDBY_128           128 
#define DIVIDEDBY_256           256   
#define DIVIDEDBY_512           512   

/*MUL_FACTOR*/
#define MUL_2           2
#define MUL_3           3
#define MUL_4           4
#define MUL_5           5
#define MUL_6           6
#define MUL_7           7
#define MUL_8           8
#define MUL_9           9
#define MUL_10          10
#define MUL_11          11
#define MUL_12          12
#define MUL_13          13
#define MUL_14          14
#define MUL_15          15
#define MUL_16          16


#define NOT_USED	1000

void RCC_voidSETAHB_Prescaller(void);
void RCC_voidSETAPB1_Prescaller(void);
void RCC_voidSETAPB2_Prescaller(void);
void RCC_voidSETPLL_CLK_SOURCE(void);
void RCC_voidSETPLLPRESCALLER(void);
void RCC_voidSETPLL_MULTIPLCATION_FACTOR(void);
void RCC_voidHSEBYPASS(void);



#endif
