#include "lcd.h"
#include "miConfig.h"
unsigned char dispctrl = 0x00;

void LCD_Inicio(void){
    __delay_ms(15);             // espero 15 ms
	LATD = 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
	EN = 1; NOP(); EN = 0;      // Genero pulso
	                      
	__delay_ms(5);              // espero mas de 4,1 msg
	LATD= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
    EN = 1; NOP(); EN = 0;      // Genero pulso
    
    __delay_ms(1);              // espero mas de 100 useg

	LATD= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
	EN = 1; NOP(); EN = 0;      // Genero pulso 
	__delay_ms(1);              // Demora superior a 100 useg
    
    //LCD_Command(0x33);        // Establece comunicación en 8 bits
    //LCD_Command(0x32);        // Quiero cambiar al modo 4 bitrs
    LCD_Comando(0x02);          // Colocar el cursor en la posición de inicio
    LCD_Comando(0x28);          // Modo 4 bits, 2 lineas y fuente 5x8 pixeles
    LCD_Comando(0x01);          // Borrar pantalla
    LCD_Comando(0x0c);          // Display ON, cursor OFF, parpadeo OFF
	LCD_Comando(0x06);          // Incremento a la derecha, modo normal
    LATDbits.LATD3 = 1;
}

void LCD_Comando(unsigned char cmd){
	LATD = (LATD & 0x0f)|(0xF0 & cmd);    // Envía nibble alto al PORTD
	RS = 0;                                 // Selecciona registro comandos 
	EN = 1; NOP(); EN = 0;                                
	__delay_ms(1);
    
    LATD = (LATD & 0x0f) | (cmd<<4);      // Envía nibble bajo al PORTD
    EN = 1; NOP(); EN = 0;
	__delay_ms(3);
}

void LCD_Data(unsigned char dat){
	LATD = (LATD & 0x0f) | (0xF0 & dat);      // Envía nibble alto al PORTD
	RS = 1;                                     // Selecciona registro datos
    EN = 1; NOP(); EN = 0;
	__delay_ms(1);
    
    LATD = (LATD & 0x0f) | (dat<<4);          // Envía nibble bajo al PORTD
    EN = 1; NOP(); EN = 0;
	__delay_ms(3);
}

void LCD_Cadena(const char *msg){
	while((*msg)!=0){		
	  LCD_Data(*msg);
	  msg++;	
    }
}

void LCD_GotoXY(char fila, char columna){
    char posicion=0;
    switch(fila){
        case 1:
            posicion=(0x80) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 2:
            posicion=(0xc0) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 3:
            posicion=(0x94) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 4:
            posicion=(0xd4) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
    }
}

void LCD_Borrar(){
   	LCD_Comando(0x01);      // Comando para borrar
    __delay_ms(3);
}

void LCD_CrearChar(int charnum,const int *chardata){
    int i;
    charnum &= 0x07;
    LCD_Comando(0x40 | (charnum << 3));
    for(i = 0; i< 8;i++){
        LCD_Data(chardata[i]);
    }
}

void LCD_Apagar(){
    dispctrl &= ~(1<<2);
    LCD_Comando(0x08 | dispctrl);
    __delay_us(50);
}

void mostrarLogo(){
    LCD_GotoXY(2,8);
    LCD_Data(0);
    LCD_Data(1);
    LCD_Data(2);
    LCD_GotoXY(3,8);
    LCD_Data(3);
    LCD_Data(4);
    LCD_Data(5);
    __delay_ms(2000);
}