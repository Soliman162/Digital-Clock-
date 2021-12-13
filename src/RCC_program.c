#include "..\include\STD_TYPES.h"
#include "..\include\BIT_MATH.h"
#include "..\include\STM32F103C8.h"


#include "..\include\RCC_interface.h"
#include "..\include\RCC_private.h"
#include "..\include\RCC_config.h"

void RCC_voidCLKInit(void){

#ifdef  CLK_SOURCE

    #if CLK_SOURCE == HSE

      RCC_voidHSEBYPASS();
      RCC_voidSETAHB_Prescaller();
      RCC_voidSETAPB1_Prescaller();
      RCC_voidSETAPB2_Prescaller();
      SET_BIT( RCC->CFGR , SW_0);
      CLR_BIT( RCC->CFGR , SW_1);
      SET_BIT( RCC->CR , HSEON );

      while( (GET_BIT( RCC->CR , HSERDY )) == 0 );

    #elif CLK_SOURCE == HSI

      RCC_voidSETAHB_Prescaller();
      RCC_voidSETAPB1_Prescaller();
      RCC_voidSETAPB2_Prescaller();
      CLR_BIT( RCC->CFGR , SW_0);
      CLR_BIT( RCC->CFGR , SW_1);
      SET_BIT( RCC->CR , HSION );
      while( (GET_BIT( RCC->CR , HSIRDY )) == 0 );

    #elif CLK_SOURCE == PLL

      RCC_voidSETAHB_Prescaller();
      RCC_voidSETAPB1_Prescaller();
      RCC_voidSETAPB2_Prescaller();
      RCC_voidSETPLL_MULTIPLCATION_FACTOR();
      RCC_voidSETPLL_CLK_SOURCE();
      CLR_BIT( RCC->CFGR , SW_0);
      SET_BIT( RCC->CFGR , SW_1);
      SET_BIT( RCC->CR , PLLON );
      while( (GET_BIT( RCC->CR , PLLRDY )) == 0 );

    #endif
#endif

}
ERROR_enumSTATE RCC_enumPeripheralCLKEnable( u8 Copy_u8BUS ,u8 Copy_u8Peripheral ){

	ERROR_enumSTATE   LOC_u8Error_STATE = STD_TYPES_OK;

	  if( Copy_u8Peripheral <32 )
	  {
		  switch ( Copy_u8BUS )
		  {
			  case AHB_BUS:

				SET_BIT( RCC->AHBENR , Copy_u8Peripheral );
				break;

			  case APB2_BUS:

				SET_BIT( RCC->APB2ENR , Copy_u8Peripheral );
				break;

			  case APB1_BUS:

				SET_BIT( RCC->APB1ENR , Copy_u8Peripheral );
				break;

			  default:
				  LOC_u8Error_STATE = STD_TYPES_NOK;
		  }

	  }else
	  {
	      LOC_u8Error_STATE = STD_TYPES_NOK;
	  }

	  return LOC_u8Error_STATE;
}
ERROR_enumSTATE RCC_enumPeripheralCLKDisable(  u8 Copy_u8BUS ,u8 Copy_u8Peripheral ){

  ERROR_enumSTATE   LOC_u8Error_STATE = STD_TYPES_OK;

  if( Copy_u8Peripheral <32 )
  {
	  switch ( Copy_u8BUS )
	  {
		  case AHB_BUS:

			CLR_BIT( RCC->AHBENR , Copy_u8Peripheral );
			break;

		  case APB2_BUS:

			CLR_BIT( RCC->APB2ENR , Copy_u8Peripheral );
			break;

		  case APB1_BUS:

			CLR_BIT( RCC->APB1ENR , Copy_u8Peripheral );
			break;

		  default:
			  LOC_u8Error_STATE = STD_TYPES_NOK;
	  }


  }else
  {
      LOC_u8Error_STATE = STD_TYPES_NOK;
  }

  return LOC_u8Error_STATE;

}

void RCC_voidSETAHB_Prescaller(void){

    #ifdef AHB_PRESCALLER

      #if AHB_PRESCALLER ==  DIVIDEDBY_1

        CLR_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_2

        CLR_BIT( RCC->CFGR , HPRE_4 );
        CLR_BIT( RCC->CFGR , HPRE_5 );
        CLR_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_4

        SET_BIT( RCC->CFGR , HPRE_4 );
        CLR_BIT( RCC->CFGR , HPRE_5 );
        CLR_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_8

        CLR_BIT( RCC->CFGR , HPRE_4 );
        SET_BIT( RCC->CFGR , HPRE_5 );
        CLR_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_16

        SET_BIT( RCC->CFGR , HPRE_4 );
        SET_BIT( RCC->CFGR , HPRE_5 );
        CLR_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_64

        CLR_BIT( RCC->CFGR , HPRE_4 );
        CLR_BIT( RCC->CFGR , HPRE_5 );
        SET_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_128

        SET_BIT( RCC->CFGR , HPRE_4 );
        CLR_BIT( RCC->CFGR , HPRE_5 );
        SET_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_256

        CLR_BIT( RCC->CFGR , HPRE_4 );
        SET_BIT( RCC->CFGR , HPRE_5 );
        SET_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #elif AHB_PRESCALLER ==  DIVIDEDBY_512

        SET_BIT( RCC->CFGR , HPRE_4 );
        SET_BIT( RCC->CFGR , HPRE_5 );
        SET_BIT( RCC->CFGR , HPRE_6 );
        SET_BIT( RCC->CFGR , HPRE_7 );

      #endif
    #endif
}

void RCC_voidSETAPB1_Prescaller(void){

  #ifdef APB1_PRESCALLER

    #if APB1_PRESCALLER ==  DIVIDEDBY_1
        CLR_BIT( RCC->CFGR , PPRE1_10 );
    #elif DIVIDEDBY_2

        CLR_BIT( RCC->CFGR , PPRE1_8 );
        CLR_BIT( RCC->CFGR , PPRE1_9 );
        SET_BIT( RCC->CFGR , PPRE1_10 );

    #elif APB1_PRESCALLER ==  DIVIDEDBY_4

        SET_BIT( RCC->CFGR , PPRE1_8 );
        CLR_BIT( RCC->CFGR , PPRE1_9 );
        SET_BIT( RCC->CFGR , PPRE1_10 );

    #elif APB1_PRESCALLER == DIVIDEDBY_8

        CLR_BIT( RCC->CFGR , PPRE1_8 );
        SET_BIT( RCC->CFGR , PPRE1_9 );
        SET_BIT( RCC->CFGR , PPRE1_10 );

    #elif APB1_PRESCALLER == DIVIDEDBY_16

        SET_BIT( RCC->CFGR , PPRE1_8 );
        SET_BIT( RCC->CFGR , PPRE1_9 );
        SET_BIT( RCC->CFGR , PPRE1_10 );

    #endif
  #endif
}


void RCC_voidSETAPB2_Prescaller(void){

  #ifdef APB2_PRESCALLER

    #if APB2_PRESCALLER ==  DIVIDEDBY_1
        CLR_BIT( RCC->CFGR , PPRE2_13 );
    #elif APB2_PRESCALLER == DIVIDEDBY_2

        CLR_BIT( RCC->CFGR , PPRE2_11);
        CLR_BIT( RCC->CFGR , PPRE2_12);
        SET_BIT( RCC->CFGR , PPRE2_13 );

    #elif APB2_PRESCALLER == DIVIDEDBY_4

        SET_BIT( RCC->CFGR , PPRE2_11);
        CLR_BIT( RCC->CFGR , PPRE2_12);
        SET_BIT( RCC->CFGR , PPRE2_13 );

    #elif APB2_PRESCALLER == DIVIDEDBY_8

        CLR_BIT( RCC->CFGR , PPRE2_11 );
        SET_BIT( RCC->CFGR , PPRE2_12);
        SET_BIT( RCC->CFGR , PPRE2_13 );

    #elif APB2_PRESCALLER == DIVIDEDBY_16

        SET_BIT( RCC->CFGR , PPRE2_11);
        SET_BIT( RCC->CFGR , PPRE2_12);
        SET_BIT( RCC->CFGR , PPRE2_13 );

    #endif
  #endif

}

void RCC_voidSETPLL_CLK_SOURCE(void){

      #ifdef PLL_CLK_SOURCE

        #if   PLL_CLK_SOURCE == HSE

          RCC_voidHSEBYPASS();
          RCC_voidSETPLLPRESCALLER();
          SET_BIT( RCC->CFGR , PLLSRC_16);

        #elif   PLL_CLK_SOURCE == HSI

          CLR_BIT( RCC->CFGR , PLLSRC_16);

        #endif
      #endif
}

void RCC_voidSETPLLPRESCALLER(void){

    #ifdef PLL_PRESCALLER

        #if PLL_PRESCALLER == DIVIDEDBY_1

          CLR_BIT( RCC->CFGR ,PLLXTPRE_17);

        #elif PLL_PRESCALLER == DIVIDEDBY_2

          SET_BIT( RCC->CFGR ,PLLXTPRE_17);

        #endif
    #endif
}

void RCC_voidSETPLL_MULTIPLCATION_FACTOR(void){

  #ifdef  PLL_MULTIPLCATION_FACTOR

    #if     PLL_MULTIPLCATION_FACTOR == MUL_2

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_3

        SET_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_4

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_5

        SET_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_6

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_7

        SET_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_8

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_9

        SET_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        CLR_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_10

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_11

        SET_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_12

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_13

        SET_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        CLR_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_14

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_15

        SET_BIT(RCC->CFGR , PLLMUL_18);
        CLR_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #elif  PLL_MULTIPLCATION_FACTOR ==MUL_16

        CLR_BIT(RCC->CFGR , PLLMUL_18);
        SET_BIT(RCC->CFGR , PLLMUL_19);
        SET_BIT(RCC->CFGR , PLLMUL_20);
        SET_BIT(RCC->CFGR , PLLMUL_21);

    #endif
  #endif
}

 void RCC_voidHSEBYPASS(void){

	#ifdef    HSE_TYPE

		#if (HSE_TYPE == CRYSTAL)
				CLR_BIT( RCC->CR, HSEBYP );

		#elif  (HSE_TYPE == RC)
				SET_BIT( RCC->CR, HSEBYP );

		#endif
	#endif
}
