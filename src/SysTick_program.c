#include "..\include\\STD_TYPES.h"
#include "..\include\\BIT_MATH.h"
#include "..\include\\STM32F103C8.h"

#include "..\include\SysTick_interface.h"
#include "..\include\SysTick_private.h"
#include "../include\SysTick_config.h"

void (* STK_CallBack)(void) = NULL;

static u8 STK_u8ModeOfInterval ;

void STK_voidInit(void)
{
    #ifdef  STK_CLK_SOURCE

        #if STK_CLK_SOURCE == AHB
            SET_BIT(STK->CTRL,2);
        #elif STK_CLK_SOURCE == AHB_DIVIDEDBY_8
            CLR_BIT(STK->CTRL,2);
        #endif
    #endif
}
ERROR_enumSTATE STK_voidSetBusyWait(u32 Copy_u32Tick_numbers )
{
    ERROR_enumSTATE LOC_enumError_State = STD_TYPES_OK;

    if( Copy_u32Tick_numbers <= MAX_TICK_TIMES )
    {
        STK->LOAD = Copy_u32Tick_numbers;
        SET_BIT(STK->CTRL ,0);

        while(GET_BIT(STK->CTRL ,16) != 1);

        CLR_BIT(STK->CTRL ,0);
        STK->LOAD = 0;
        STK->VAL = 0;

    }else{ LOC_enumError_State = STD_TYPES_NOK; }

    return LOC_enumError_State;
}

ERROR_enumSTATE STK_enumSetIntervalSingle(u32 Copy_u32Tick_numbers ,void(*Copy_STK_CallBack)(void))
{
    ERROR_enumSTATE LOC_enumError_State = STD_TYPES_OK;
    if( Copy_STK_CallBack != NULL )
    {
        if( Copy_u32Tick_numbers <= MAX_TICK_TIMES )
        {
            CLR_BIT(STK->CTRL ,0);
            STK->VAL = 0;

            STK->LOAD = Copy_u32Tick_numbers;

            SET_BIT(STK->CTRL ,0);

            STK_CallBack = Copy_STK_CallBack;

            STK_u8ModeOfInterval =  MODE_OF_INTERVAL_SINGLE ;
   
            SET_BIT(STK->CTRL ,1);

        }else{ LOC_enumError_State = STD_TYPES_NOK; }
    }else{ LOC_enumError_State = STD_TYPES_NOK; }

    return LOC_enumError_State;

}
ERROR_enumSTATE STK_enumSetIntervalPeriodic(u32 Copy_u32Tick_numbers ,void(*Copy_STK_CallBack)(void))
{
    ERROR_enumSTATE LOC_enumError_State = STD_TYPES_OK;
    if( Copy_STK_CallBack != NULL )
    {
        if( Copy_u32Tick_numbers <= MAX_TICK_TIMES )
        {

            STK->LOAD = Copy_u32Tick_numbers-1;

            SET_BIT(STK->CTRL ,0);

            STK_CallBack = Copy_STK_CallBack;
            
            STK_u8ModeOfInterval = MODE_OF_INTERVAL_PERIODIC;

            SET_BIT(STK->CTRL ,1);

        }else{ LOC_enumError_State = STD_TYPES_NOK; }
    }else{ LOC_enumError_State = STD_TYPES_NOK; }

    return LOC_enumError_State;
}

void STK_voidStopTimer(void)
{
    CLR_BIT(STK->CTRL ,1);

    CLR_BIT(STK->CTRL ,0);
    STK->LOAD = 0;
    STK->VAL = 0;

}

ERROR_enumSTATE STK_enumGetElapsedTime(volatile u32 *Copy_pu32ElapsedTime)
{
    ERROR_enumSTATE LOC_enumError_State = STD_TYPES_OK;
    if( Copy_pu32ElapsedTime != NULL)
    {
        *Copy_pu32ElapsedTime = (STK->LOAD - STK->VAL) ;

    }else{ LOC_enumError_State = STD_TYPES_NOK;}

    return  LOC_enumError_State;
}
ERROR_enumSTATE STK_enumGetRemainingTime(u32 *Copy_pu32RemainingTime)
{
    ERROR_enumSTATE LOC_enumError_State = STD_TYPES_OK;
    if( Copy_pu32RemainingTime != NULL)
    {
        *Copy_pu32RemainingTime = STK->VAL ;

    }else{ LOC_enumError_State = STD_TYPES_NOK;}

    return  LOC_enumError_State;
}

void SysTick_Handler(void)
{
    static u8 LOC_u8Temp_CLR = 0;
    if( STK_CallBack != NULL )
    {
    	if ( STK_u8ModeOfInterval == MODE_OF_INTERVAL_SINGLE )
    	{
    		/* Disable STK Interrupt */
    		CLR_BIT(STK->CTRL, 1);

    		/* Stop Timer */
    		CLR_BIT(STK->CTRL, 0);
    		STK -> LOAD = 0;
    		STK -> VAL  = 0;
    	}

    	/* Callback notification */
    	STK_CallBack();

    	/* Clear interrupt flag */
    	LOC_u8Temp_CLR =GET_BIT(STK->CTRL,16);
    }

}
