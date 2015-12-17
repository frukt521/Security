#ifndef _LCD_H
#define _LCD_H

#define AVR_MEGA
#define pLCD_PORT           (PORTA) //PORTX
#define pLCD_DDR            (DDRA) //for AVR: DDRX; for PIC TRISX;
#define NUMBER_OF_PIN_D4        4
#define NUMBER_OF_PIN_D5        5
#define NUMBER_OF_PIN_D6        6
#define NUMBER_OF_PIN_D7        7
#define NUMBER_OF_PIN_E         2
#define NUMBER_OF_PIN_RS        0
#define NUMBER_OF_PIN_RW        1

#ifdef AVR_MEGA
#include <avr/io.h>
#endif

#ifdef PIC
typedef unsigned int uint8_t;
#endif

void LCD_Init(void);
void LCD_SendChar(uint8_t Data);
void LCD_SendString(char * Data, uint8_t Length);
void LCD_GoToPosition(uint8_t X, uint8_t Y);
void LCD_Clear(void);
void LCD_AddSymbol(uint8_t * SymDiscr, uint8_t SymNum);
#endif