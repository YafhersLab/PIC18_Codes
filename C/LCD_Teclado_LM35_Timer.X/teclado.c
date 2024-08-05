#include "teclado.h"

void Teclado_Inicio(void){
    ROW0_DIR = 0;
    ROW1_DIR = 0;
    ROW2_DIR = 0;
    ROW3_DIR = 0;
    COL0_DIR = 1;
    COL1_DIR = 1;
    COL2_DIR = 1;
    COL3_DIR = 1;
}

char Teclado_Obtener(void){
    ROW0_PIN = 0;
    ROW1_PIN = 1;
    ROW2_PIN = 1;
    ROW3_PIN = 1;
    if(COL0_PIN == 0){
        __delay_ms(2);
        while(COL0_PIN == 0);
        __delay_ms(5);
        return 'D';
    }
    if(COL1_PIN == 0){
        __delay_ms(2);
        while(COL1_PIN == 0);
        __delay_ms(5);
        return 'C';
    }
    if(COL2_PIN == 0){
        __delay_ms(2);
        while(COL2_PIN == 0);
        __delay_ms(5);
        return 'B';
    }
    if(COL3_PIN == 0){
        __delay_ms(2);
        while(COL3_PIN == 0);
        __delay_ms(5);
        return 'A';
    }
    
    ROW0_PIN = 1;
    ROW1_PIN = 0;
    ROW2_PIN = 1;
    ROW3_PIN = 1;
    if(COL0_PIN == 0){
        __delay_ms(2);
        while(COL0_PIN == 0);
        __delay_ms(5);
        return 'E';
    }
    if(COL1_PIN == 0){
        __delay_ms(2);
        while(COL1_PIN == 0);
        __delay_ms(5);
        return '9';
    }
    if(COL2_PIN == 0){
        __delay_ms(2);
        while(COL2_PIN == 0);
        __delay_ms(5);
        return '6';
    }
    if(COL3_PIN == 0){
        __delay_ms(2);
        while(COL3_PIN == 0);
        __delay_ms(5);
        return '3';
    }
    
    ROW0_PIN = 1;
    ROW1_PIN = 1;
    ROW2_PIN = 0;
    ROW3_PIN = 1;
    if(COL0_PIN == 0){
        __delay_ms(2);
        while(COL0_PIN == 0);
        __delay_ms(5);
        return '0';
    }
    if(COL1_PIN == 0){
        __delay_ms(2);
        while(COL1_PIN == 0);
        __delay_ms(5);
        return '8';
    }
    if(COL2_PIN == 0){
        __delay_ms(2);
        while(COL2_PIN == 0);
        __delay_ms(5);
        return '5';
    }
    if(COL3_PIN == 0){
        __delay_ms(2);
        while(COL3_PIN == 0);
        __delay_ms(5);
        return '2';
    }
    
    ROW0_PIN = 1;
    ROW1_PIN = 1;
    ROW2_PIN = 1;
    ROW3_PIN = 0;
    if(COL0_PIN == 0){
        __delay_ms(2);
        while(COL0_PIN == 0);
        __delay_ms(5);
        return 'F';
    }
    if(COL1_PIN == 0){
        __delay_ms(2);
        while(COL1_PIN == 0);
        __delay_ms(5);
        return '7';
    }
    if(COL2_PIN == 0){
        __delay_ms(2);
        while(COL2_PIN == 0);
        __delay_ms(5);
        return '4';
    }
    if(COL3_PIN == 0){
        __delay_ms(2);
        while(COL3_PIN == 0);
        __delay_ms(5);
        return '1';
    }
    return 0;
}