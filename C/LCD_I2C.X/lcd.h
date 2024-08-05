#include "miConfig.h"
#define RS LATD0           
#define WR LATD1            
#define EN LATD2   

//Declaracion de Funciones
void LCD_Inicio();                     
void LCD_Comando(unsigned char);           
void LCD_Data(unsigned char x);            
void LCD_Cadena(const char *);              
void LCD_GotoXY(char fila, char columna);             
void LCD_Borrar();                         
void LCD_Apagar();
void LCD_CrearChar(int charnum, const int *chardata);
void mostrarLogo();

//Caracteres para el Logo
const int bit1[8] = {
    0b00000110,
    0b00001001,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00011111,
    0b00010111,
    0b00010011
};
const int bit2[8] = {
    0b00000000,
    0b00000000,
    0b00010001,
    0b00001110,
    0b00000000,
    0b00011111,
    0b00011001,
    0b00010010
};
const int bit3[8] = {
    0b00001100,
    0b00010010,
    0b00000010,
    0b00000010,
    0b00000010,
    0b00011111,
    0b00011101,
    0b00011001
};
const int bit4[8] = {
    0b00010000,
    0b00010001,
    0b00001001,
    0b00000100,
    0b00000011,
    0b00000000,
    0b00000000,
    0b00000000
};
const int bit5[8] = {
    0b00000000,
    0b00000100,
    0b00011111,
    0b00000000,
    0b00011111,
    0b00000000,
    0b00000000,
    0b00000000
};
const int bit6[8] = {
    0b00000001,
    0b00010001,
    0b00010010,
    0b00000100,
    0b00011000,
    0b00000000,
    0b00000000,
    0b00000000
};