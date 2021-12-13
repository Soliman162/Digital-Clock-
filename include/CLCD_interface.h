#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H



#define CLCD_ROW_1 1
#define CLCD_ROW_2 2




#define Start_char1  3
#define Start_char2  2
#define Start_char3  1
#define Start_char4  0

#define Iterator_char1  1
#define Iterator_char2  2
#define Iterator_char3  3
#define Iterator_char4  4

#define CLCD_COL_1  1
#define CLCD_COL_2  2
#define CLCD_COL_3  3
#define CLCD_COL_4  4
#define CLCD_COL_5  5
#define CLCD_COL_6  6
#define CLCD_COL_7  7
#define CLCD_COL_8  8
#define CLCD_COL_9  9
#define CLCD_COL_10 10
#define CLCD_COL_11 11
#define CLCD_COL_12 12
#define CLCD_COL_13 13
#define CLCD_COL_14 14
#define CLCD_COL_15 15
#define CLCD_COL_16 16


void CLCD_voidInit(void);
void CLCD_void_4_BitInit(void);
void CLCD_voidSend_Data  (u8 Copy_u8Data);
void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSend_String (u8 *Copy_u8PtrString);
void CLCD_void_Send_Number(u64 Copy_u64Number);

void CLCD_voidSetPosition (u8 Copy_u8Row , u8 Copy_u8Col);
void Send_voidExtraString   (u8 Copy_u8Row , u8 Copy_u8Col);

void Clear_voidCLCD(void);
void Display_voidOff_On(void);


#endif