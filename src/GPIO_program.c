#include "..\include\STD_TYPES.h"
#include "..\include\BIT_MATH.h"
#include "..\include\STM32F103C8.h"

#include "..\include\GPIO_interface.h"
#include "..\include\GPIO_private.h"
#include "..\include\GPIO_config.h"

static GPIO_REG_DEF_t * GPIO_PORT[7] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};

ERROR_enumSTATE GPIO_enumSETPinMODE( const GPIO_CONFIG_t * Copy_ptru8PIN )
{

	ERROR_enumSTATE LOC_u8State = STD_TYPES_OK;
	u8 LOC_u8CopyMode ;
	u8 LOc_u8CopyPin_num;
	u8 LOC_u8CopyPort_ID;

	if(Copy_ptru8PIN != NULL){

		LOC_u8CopyMode = Copy_ptru8PIN->PIN_MODE;
		LOc_u8CopyPin_num = Copy_ptru8PIN->PIN_NUM;
		LOC_u8CopyPort_ID =Copy_ptru8PIN->PORT_ID;

		if(  LOC_u8CopyPort_ID <= GPIOC_PORT )
		{
			if( LOc_u8CopyPin_num<=PIN_15 )
			{
				if( LOC_u8CopyMode ==  INPUT_PULL_UP )
				{
					GPIO_PORT[LOC_u8CopyPort_ID]->BSRR = (1<<LOc_u8CopyPin_num);
					LOC_u8CopyMode = 0b1000;

				}else if( LOC_u8CopyMode ==  INPUT_PULL_DOWN )
				{
					GPIO_PORT[LOC_u8CopyPort_ID]->BRR = (1<<LOc_u8CopyPin_num);
				}

				if( LOc_u8CopyPin_num<=PIN_7 )
				{
					(GPIO_PORT[LOC_u8CopyPort_ID]->CRL) &=  (~(0b1111<<(LOc_u8CopyPin_num * 4) ) );
					(GPIO_PORT[LOC_u8CopyPort_ID]->CRL) |=  ( LOC_u8CopyMode << ( LOc_u8CopyPin_num * 4 ) );

				}else if( LOc_u8CopyPin_num>=PIN_8 )
				{
					LOc_u8CopyPin_num-=8;
					GPIO_PORT[LOC_u8CopyPort_ID]->CRH &=  (~(0b1111<< (LOc_u8CopyPin_num * 4) ) ) ;
					GPIO_PORT[LOC_u8CopyPort_ID]->CRH |=  ( LOC_u8CopyMode << (  LOc_u8CopyPin_num * 4) );
				}

			}else{LOC_u8State = STD_TYPES_NOK;}

		}else{ LOC_u8State = STD_TYPES_NOK; }

	}else{ LOC_u8State = STD_TYPES_NOK; }

	return LOC_u8State;
}


ERROR_enumSTATE GPIO_enumSETPinValue( const GPIO_CONFIG_t * Copy_ptru8PIN  , u8 Pin_u8Value )
{
	ERROR_enumSTATE LOC_u8State = STD_TYPES_OK;

	if( Copy_ptru8PIN !=NULL){

		if( Copy_ptru8PIN->PORT_ID<=GPIOC_PORT )
		{
			if( Copy_ptru8PIN->PIN_NUM<=PIN_15 )
			{
				if( Pin_u8Value == GPIO_HIGH )
				{
					GPIO_PORT[Copy_ptru8PIN->PORT_ID]->BSRR = (1<<Copy_ptru8PIN->PIN_NUM);

				}else if (Pin_u8Value == GPIO_LOW )
				{
					GPIO_PORT[Copy_ptru8PIN->PORT_ID]->BRR = (1<<Copy_ptru8PIN->PIN_NUM);
				}
			}else{ LOC_u8State = STD_TYPES_NOK; }

		}else{ LOC_u8State = STD_TYPES_NOK; }
	}
	return LOC_u8State;
}


ERROR_enumSTATE GPIO_enumGETPinValue( const GPIO_CONFIG_t * Copy_ptru8PIN  , u8 *Pin_ptru8Value )
{

	ERROR_enumSTATE LOC_u8State = STD_TYPES_OK;

	if( Copy_ptru8PIN !=NULL )
	{
		if( Pin_ptru8Value != NULL)
		{
			if( Copy_ptru8PIN->PORT_ID<=GPIOC_PORT )
			{
				if( Copy_ptru8PIN->PIN_NUM<=PIN_15 )
				{
					*Pin_ptru8Value = GET_BIT( GPIO_PORT[Copy_ptru8PIN->PORT_ID]->IDR , Copy_ptru8PIN->PIN_NUM );

				}else{ LOC_u8State = STD_TYPES_NOK; }

			}else{ LOC_u8State = STD_TYPES_NOK; }
		}
	}

	return LOC_u8State;
}
