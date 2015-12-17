#include "LCD.h"

//Define MCU {
#ifdef AVR_MEGA
#include <util/delay.h>
#include <avr/io.h>
#endif

#ifdef PIC
#define _delay_us      Delay_us
#define _delay_ms      Delay_ms
#endif
//Define MCU }

//define controls {
#define     pSET_E()    do{pLCD_PORT |= (1 << NUMBER_OF_PIN_E); }while(0)
#define     pCLR_E()    do{pLCD_PORT &= ~(1 << NUMBER_OF_PIN_E); }while(0)
#define     pSET_RS()   do{pLCD_PORT |= (1 << NUMBER_OF_PIN_RS); }while(0)
#define     pCLR_RS()   do{pLCD_PORT &= ~(1 << NUMBER_OF_PIN_RS); }while(0)
#define     pSET_RW()   do{pLCD_PORT |= (1 << NUMBER_OF_PIN_RW); }while(0)
#define     pCLR_RW()   do{pLCD_PORT &= ~(1 << NUMBER_OF_PIN_RW); }while(0)
//define controls }

void pLCD_SendNibble(uint8_t Nibble)
{
        uint8_t tmp;
        tmp = 0;
        pSET_E();
        _delay_us(200);
		
        Nibble &= 0xF0;
        //Construction the output data
        tmp |= (((Nibble >> 4) & 1) << NUMBER_OF_PIN_D4)
			| (((Nibble >> 5) & 1) << NUMBER_OF_PIN_D5)
			| (((Nibble >> 6) & 1) << NUMBER_OF_PIN_D6)
			| (((Nibble >> 7) & 1) << NUMBER_OF_PIN_D7);
        //Clear all data pins on port
        pLCD_PORT &= ~(1 << NUMBER_OF_PIN_D4) & ~(1 << NUMBER_OF_PIN_D5) 
                  & ~(1 << NUMBER_OF_PIN_D6) & ~(1 << NUMBER_OF_PIN_D7);
        //Send data                        
        pLCD_PORT |= tmp;
                
        pCLR_E();
        _delay_us(200);
}

void pLCD_SendCmd(uint8_t Data)
{
        pCLR_RS();
        pLCD_SendNibble(Data);
        pLCD_SendNibble(Data << 4);
}

void LCD_Init(void)
{
    //Configure output port
    #ifdef AVR_MEGA
		pLCD_DDR |= (1 << NUMBER_OF_PIN_D4) | (1 << NUMBER_OF_PIN_D5)
                 | (1 << NUMBER_OF_PIN_D6) | (1 << NUMBER_OF_PIN_D7)
                 | (1 << NUMBER_OF_PIN_E) | (1 << NUMBER_OF_PIN_RS)
                 | (1 << NUMBER_OF_PIN_RW);
    #endif
    #ifdef PIC
		pLCD_DDR &= ~(1 << NUMBER_OF_PIN_D4) & ~(1 << NUMBER_OF_PIN_D5)
                 & ~(1 << NUMBER_OF_PIN_D6) & ~(1 << NUMBER_OF_PIN_D7)
                 & ~(1 << NUMBER_OF_PIN_E) & ~(1 << NUMBER_OF_PIN_RS)
                 & ~(1 << NUMBER_OF_PIN_RW);
    #endif
        
    //Clear data on port
	pLCD_PORT &= ~(1 << NUMBER_OF_PIN_D4) & ~(1 << NUMBER_OF_PIN_D5)
              & ~(1 << NUMBER_OF_PIN_D6) & ~(1 << NUMBER_OF_PIN_D7)
              & ~(1 << NUMBER_OF_PIN_E) & ~(1 << NUMBER_OF_PIN_RS)
              & ~(1 << NUMBER_OF_PIN_RW); 
    //Init display
    _delay_ms(50);
    pLCD_SendNibble(0b00110000);
    _delay_us(100);
    pLCD_SendNibble(0b00110000);
    _delay_us(100);
    pLCD_SendNibble(0b00110000);
    _delay_us(100);
    pLCD_SendNibble(0b00100000);
    _delay_ms(10);
    pLCD_SendCmd(0b00101000);
    _delay_ms(10);
    pLCD_SendCmd(0b00001100);
    _delay_ms(10);
    pLCD_SendCmd(0b00000001);
    _delay_ms(10);
    pLCD_SendCmd(0b00000100);
    _delay_ms(10);
    //Cursor on
    //pLCD_SendCmd(0b00001111); 
    //_delay_ms(10);
}

void LCD_SendChar(uint8_t Data)
{
        pSET_RS();
        pLCD_SendNibble(Data);
        pLCD_SendNibble(Data << 4);
        _delay_us(200);
        pCLR_RS();
}

void LCD_SendString(char * Data, uint8_t Length)
{      
       uint8_t i;
       for(i = 0; i < Length; i++)
           LCD_SendChar(Data[i]);
}

void LCD_GoToPosition(uint8_t X, uint8_t Y)
{
        uint8_t Address = 0;
        switch(Y)
        {
                case 0: Address = 0x00; break;
                case 1: Address = 0x40; break;
                case 2: Address = 0x10; break;
                case 3: Address = 0x50; break;
                default: Address = 0; break;
        }
        Address += (X & 0x0F);

        pLCD_SendCmd(0x80 | Address);
        _delay_us(200);
}

void LCD_Clear(void)
{
	pLCD_SendCmd(0b00000001);
    _delay_ms(50);
}

void LCD_AddSymbol(uint8_t * SymDiscr, uint8_t SymNum)
{
        uint8_t i;
        uint8_t adr;
        SymNum &= 0x07;
        SymNum = SymNum << 3;
        adr = 0b01000000 + SymNum;
        for (i = 0; i < 6; i++)
        {
                pLCD_SendCmd(adr);                //Set CGRAM Address
                LCD_SendChar(SymDiscr[i]);        //Write char line
                adr++;
        }
}

/*
char CharReplace(char ch)
{
        switch (ch)
        {
                case 0xC0 : return 0x41; break;        //A
                case 0xC1 : return 0xA0; break;        //Á
                case 0xC2 : return 0x42; break;        //Â
                case 0xC3 : return 0xA1; break;        //Ã
                case 0xC4 : return 0xE0; break;        //Ä
                case 0xC5 : return 0x45; break;        //Å
                case 0xC6 : return 0xA3; break;        //Æ
                case 0xC7 : return 0xAC; break;        //Ø
                case 0xC8 : return 0xA5; break;        //È
                
                default: return ch; break;
        };
}
*/