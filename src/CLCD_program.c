#include "..\include\BIT_MATH.h"
#include "..\include\STD_TYPES.h"
#include "..\include\STM32F103C8.h"

#include "..\include\GPIO_interface.h"
#include "..\include\RCC_interface.h"
#include "..\include\SysTick_interface.h"

#include "..\include\CLCD_interface.h"
#include "..\include\CLCD_private.h"
#include "..\include\CLCD_config.h"

GPIO_CONFIG_t CLCD_strData_Pins[CLCD_U8DATA_PIN_NUM] ;
GPIO_CONFIG_t CLCD_strControl_Pins[CLCD_U8CONTROL_PIN_NUM] ;

void CLCD_voidInit(void){

    for( u8 LOC_u8Pin_Iterator = 0;LOC_u8Pin_Iterator<CLCD_U8DATA_PIN_NUM;LOC_u8Pin_Iterator++)
    {
    	CLCD_strData_Pins[LOC_u8Pin_Iterator].PORT_ID  = CLCD_DATA_PORT;
    	CLCD_strData_Pins[LOC_u8Pin_Iterator].PIN_NUM  = LOC_u8Pin_Iterator;
    	CLCD_strData_Pins[LOC_u8Pin_Iterator].PIN_MODE = GENERAL_PURPOSE_OUTPUT_PUSH_PULL_10MHZ;
        GPIO_enumSETPinMODE( &CLCD_strData_Pins[LOC_u8Pin_Iterator]);
    }

    for( u8 LOC_u8Pin_Iterator = CLCD_CONTROL_PIN_RS;LOC_u8Pin_Iterator<=CLCD_CONTROL_PIN_EN;LOC_u8Pin_Iterator++)
    {
        CLCD_strControl_Pins[LOC_u8Pin_Iterator-CLCD_CONTROL_PIN_RS].PORT_ID  = CLCD_CONTROL_PORT;
        CLCD_strControl_Pins[LOC_u8Pin_Iterator-CLCD_CONTROL_PIN_RS].PIN_NUM  = LOC_u8Pin_Iterator;
		CLCD_strControl_Pins[LOC_u8Pin_Iterator-CLCD_CONTROL_PIN_RS].PIN_MODE = GENERAL_PURPOSE_OUTPUT_PUSH_PULL_10MHZ;
        GPIO_enumSETPinMODE( &CLCD_strControl_Pins[LOC_u8Pin_Iterator-CLCD_CONTROL_PIN_RS]);
    }

    STK_voidSetBusyWait(5000);
	//FUNCTION SET COMMEND
	CLCD_voidSendCommand(0b00111000);
    STK_voidSetBusyWait(1000);
	//DISPLAY ON / OFF
	CLCD_voidSendCommand(0b00001110);
    STK_voidSetBusyWait(1000);
	//DISPLAY CLEAR
	CLCD_voidSendCommand(0b00000001);
    STK_voidSetBusyWait(3000);
	//DISPLAY ENTRY MODE
	CLCD_voidSendCommand(0b00000010);
    STK_voidSetBusyWait(3000);

}
void CLCD_voidSend_Data(u8 Copy_u8Data){

    for( u8 LOC_u8Pin_Iterator = 0;LOC_u8Pin_Iterator<CLCD_U8DATA_PIN_NUM;LOC_u8Pin_Iterator++)
    {
        GPIO_enumSETPinValue(&CLCD_strData_Pins[LOC_u8Pin_Iterator] , GET_BIT(Copy_u8Data,LOC_u8Pin_Iterator) );
    }

    GPIO_enumSETPinValue(&CLCD_strControl_Pins[RW_PIN_INDEX], GPIO_LOW );
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[RS_PIN_INDEX], GPIO_HIGH);
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[EN_PIN_INDEX], GPIO_HIGH);
    STK_voidSetBusyWait(1000);

    GPIO_enumSETPinValue(&CLCD_strControl_Pins[EN_PIN_INDEX], GPIO_LOW);
    STK_voidSetBusyWait(1000);

}
void CLCD_voidSendCommand(u8 Copy_u8Command){

    for( u8 LOC_u8Pin_Iterator = 0;LOC_u8Pin_Iterator<CLCD_U8DATA_PIN_NUM;LOC_u8Pin_Iterator++)
    {
        GPIO_enumSETPinValue(&CLCD_strData_Pins[LOC_u8Pin_Iterator] , GET_BIT(Copy_u8Command,LOC_u8Pin_Iterator) );
    }
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[RW_PIN_INDEX], GPIO_LOW );
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[RS_PIN_INDEX], GPIO_LOW);
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[EN_PIN_INDEX], GPIO_HIGH);

    STK_voidSetBusyWait(1000);
    GPIO_enumSETPinValue(&CLCD_strControl_Pins[EN_PIN_INDEX], GPIO_LOW);
    STK_voidSetBusyWait(1000);
}
void CLCD_voidSend_String(u8 *Copy_u8PtrString){

	u8 LOC_u8Iterator=0;
	while(Copy_u8PtrString[LOC_u8Iterator]!='\0'){

		CLCD_voidSend_Data(Copy_u8PtrString[LOC_u8Iterator]);
		LOC_u8Iterator++;
	}
}

void CLCD_void_Send_Number(u64 Copy_u64Number){

	u64 LOC_u64Reversed =1;
	if(Copy_u64Number==0){CLCD_voidSend_Data('0');}
	else{

		while(Copy_u64Number!=0){
			LOC_u64Reversed = (LOC_u64Reversed*10)+(Copy_u64Number%10);
			Copy_u64Number/=10;
		}
		while(LOC_u64Reversed!=1){
			CLCD_voidSend_Data((LOC_u64Reversed%10)+48);
			LOC_u64Reversed/=10;
		}
	}
}

void CLCD_voidSetPosition (u8 Copy_u8Row , u8 Copy_u8Col){

	if(Copy_u8Row==CLCD_ROW_1){

		CLCD_voidSendCommand((0x80)+(Copy_u8Col-1));

	}else if (Copy_u8Row==CLCD_ROW_2){

		CLCD_voidSendCommand((0x80)+64+(Copy_u8Col-1));

	}
}


void Send_voidExtraString   (u8 Copy_u8Row , u8 Copy_u8Col  ){

	//go to CGRAM
	CLCD_voidSendCommand(0b01000000);
	//Draw Char
	for(u8 i =0 ;i<(sizeof(Arr_u8ExtraChar)/sizeof(Arr_u8ExtraChar[0]));i++){

			CLCD_voidSend_Data(Arr_u8ExtraChar[i]);

	}
	//Back to DDRAM
	CLCD_voidSetPosition (Copy_u8Row , Copy_u8Col);
	//Send Address
	for(u8 i =0 ;i<5;i++){
		CLCD_voidSend_Data(i);
	}
}

void Clear_voidCLCD(void){

	CLCD_voidSendCommand(0b00000001);
    STK_voidSetBusyWait(1000);
}

void Display_voidOff_On(void){

	CLCD_voidSendCommand(0b00001000);
    STK_voidSetBusyWait(1000);
}
