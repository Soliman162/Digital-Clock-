
#include "..\include\STD_TYPES.h"
#include "..\include\BIT_MATH.h"
#include "..\include\STM32F103C8.h"

#include "..\include\RCC_interface.h"
#include "..\include\SysTick_interface.h"
#include "..\include\GPIO_interface.h"

#include "../include/CLCD_interface.h"



int main (void){

	RCC_voidCLKInit();
	STK_voidInit();
	RCC_enumPeripheralCLKEnable(  APB2_BUS ,IOPA );
	RCC_enumPeripheralCLKEnable(  APB2_BUS ,IOPC );

	CLCD_voidInit();

	u8 Hours_u8Tens = 0;
	u8 Hours_u8Units = 0;

	u8 Minuts_u8Tens = 0;
	u8 Minuts_u8Units = 0;

	u8 Second_u8Tens = 0;
	u8 Second_u8Units = 0;

	u8 *Day_ptru8Time = "AM";

	u16 Clock_u16Counter = 0;

	while(1){

		Clear_voidCLCD();
		CLCD_voidSetPosition(CLCD_ROW_1,CLCD_COL_1);

		CLCD_void_Send_Number(Hours_u8Tens);
		CLCD_void_Send_Number(Hours_u8Units);

		CLCD_voidSend_Data(':');

		CLCD_void_Send_Number(Minuts_u8Tens);
		CLCD_void_Send_Number(Minuts_u8Units);

		CLCD_voidSend_Data(':');

		CLCD_void_Send_Number(Second_u8Tens);
		CLCD_void_Send_Number(Second_u8Units);

		CLCD_voidSend_String(Day_ptru8Time);

		STK_voidSetBusyWait(1000000);
		Clock_u16Counter++;

		if( Clock_u16Counter == 3600 )
		{
			Hours_u8Units++;
			if( Hours_u8Units == 10)
			{
				Hours_u8Tens++;
				Hours_u8Units = 0;
			}else if( Hours_u8Units == 3 && Hours_u8Tens == 1 )
			{
				Hours_u8Units = 1;
				Hours_u8Tens = 0;
				if( Day_ptru8Time == "AM" ){Day_ptru8Time = "PM";}
				else{Day_ptru8Time = "AM";}
			}
			Clock_u16Counter = 0;

		}
		if( Clock_u16Counter%60 == 0 )
		{
			Minuts_u8Units++;
			if( (Minuts_u8Tens == 5) && (Minuts_u8Units == 10) )
			{
				Minuts_u8Tens = 0;
				Minuts_u8Units = 0;
			}else if( Minuts_u8Units == 10)
			{
				Minuts_u8Tens++;
				Minuts_u8Units = 0;
			}

		}

		Second_u8Units++;
		if( Second_u8Units == 10 )
		{
			Second_u8Tens ++;
			Second_u8Units = 0;
		}
		if ( Second_u8Units == 0 && Second_u8Tens == 6)
		{
			Second_u8Tens = 0;
			Second_u8Units = 0;
		}


	}

	return 0;
}
