#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*  Options:-
    *   HSE
    *   HSI
    *   PLL
*/

#define  CLK_SOURCE      HSI

/*  Options:-
    * HSE
    * HSI
    * NOT_USED
*/
#define PLL_CLK_SOURCE		NOT_USED

/*
    Options:-
    *CRYSTAL
    *RC
    *NOT_USED
*/
#define HSE_TYPE	NOT_USED

/*  Options:-
    *  DIVIDEDBY_1
    *  DIVIDEDBY_2
    *  DIVIDEDBY_4
    *  DIVIDEDBY_8
    *  DIVIDEDBY_16
    *  DIVIDEDBY_64
    *  DIVIDEDBY_128
    *  DIVIDEDBY_256
    *  DIVIDEDBY_512
*/
#define AHB_PRESCALLER  	DIVIDEDBY_1

/*   Options:-
    *  DIVIDEDBY_1
    *  DIVIDEDBY_2
    *  DIVIDEDBY_4
    *  DIVIDEDBY_8
    *  DIVIDEDBY_16
 
*/
#define APB1_PRESCALLER  	DIVIDEDBY_1

/*   Options:-
    *  DIVIDEDBY_1
    *  DIVIDEDBY_2
    *  DIVIDEDBY_4
    *  DIVIDEDBY_8
    *  DIVIDEDBY_16
 
*/
#define APB2_PRESCALLER 	DIVIDEDBY_1

/*
    Options:-

    *  DIVIDEDBY_1
    *  DIVIDEDBY_2
    *  NOT_USED
*/
#define PLL_PRESCALLER		NOT_USED

/*
    Options:-
    *  MUL_2  
    *  MUL_3  
    *  MUL_4  
    *  MUL_5  
    *  MUL_6  
    *  MUL_7  
    *  MUL_8  
    *  MUL_9  
    *  MUL_10 
    *  MUL_11 
    *  MUL_12 
    *  MUL_13 
    *  MUL_14 
    *  MUL_15 
    *  MUL_16 
    *  NOT_USED

 */
#define PLL_MULTIPLCATION_FACTOR		NOT_USED


#endif
