#ifndef SYSTICK_interface_H
#define SYSTICK_interface_H


void STK_voidInit(void);
ERROR_enumSTATE STK_voidSetBusyWait(u32 Copy_u32Tick_numbers );

ERROR_enumSTATE STK_enumSetIntervalSingle(u32 Copy_u32Tick_numbers ,void(*Copy_pfunc)(void));
ERROR_enumSTATE STK_enumSetIntervalPeriodic(u32 Copy_u32Tick_numbers ,void(*Copy_pfunc)(void));

void STK_voidStopTimer(void);

ERROR_enumSTATE STK_enumGetElapsedTime(volatile u32 *Copy_pu32ElapsedTime);
ERROR_enumSTATE STK_enumGetRemainingTime(u32 *Copy_pu32ElapsedTime);

#endif
