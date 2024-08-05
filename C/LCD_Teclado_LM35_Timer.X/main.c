//Grupo #3 -> EE604 Seccion M
#include "miConfiguracion.h"
#include "LCD.h"
#include <string.h>
#include <stdio.h>

//Mapeo de pines para el Teclado
#define    columna1    PORTBbits.RB4    // Define la Columna 1
#define    columna2    PORTBbits.RB5    // Define la Columna 2
#define    columna3    PORTBbits.RB6    // Define la Columna 3
#define    columna4    PORTBbits.RB7    // Define la Columna 4

//Definicion de Funciones
void LCD_Inicio();                          // inicializar el LCD
void LCD_Comando(unsigned char);            // enviar comando al LCD
void LCD_Data(unsigned char x);             // enviar data al LCD
void LCD_Cadena(const char *);              // mostrar mensaje en LCD
void LCD_GotoXY(char fila, char columna);   // ubicar cursor            
void LCD_Borrar();                          // borra pantalla
void LCD_Apagar();
void LCD_CrearChar(int charnum, const int *chardata);
void LCD_Numero(float numero, unsigned char fila, unsigned char columna);
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

//Mis variables
int intervalo = 20;
int temp = 0;
char temperatura [4];
int cont1 = 0;
int cont2 = 0;
int i = 1;
int num_muestras;
int flag = 0; 
unsigned char flag1 = 0xFF;
unsigned char flag3 = 0xFF;
unsigned char flag4 = 0xFF;
unsigned char flag5 = 0xFF;
int cuenta = 0;
int contador = 0;
unsigned char fantastico = 0x01;
unsigned char scan[4] = {0XFE,0XFD,0XFB,0XF7};
unsigned char tecla = 0;
unsigned char fila,  
 // Teclado matricial
 teclado[4][4] = {  0X01, 0X02, 0X03, 0X0A,
                    0X04, 0X05, 0X06, 0X0B,
                    0X07, 0X08, 0X09, 0X0C,
                    0X0F, 0X00, 0X0E, 0X0D
                },
        
 // Codigo en ASCII a desplegar en LCD
 display[16] =  {'0','1','2','3',
                 '4','5','6','7',
                 '8','9','A','B',
                 'C','D','E','F'};  

void main(void){
//configuro frecuencia de 4MHz
    OSCCON = 0x52;          //frecuencia 4MHz
    OSCCON2 = 0;
    
//configuro puertos de entrada y salida  
    TRISA = 0;               //PA como salida (Leds)
    TRISB = 0xF0;            // PB[7..4]=entrada, PB[3..0]=salida
    TRISD = 0;               //PD como salida (LCD)
    ANSELA = 0;              //PA como digital (Leds)
    ANSELB = 0;              //PB como digital (Teclado)  
    ANSELD = 0;              //PD como digital(LCD) 
    INTCON2bits.RBPU = 0;    //Configura el PULL-UP del PB.
    TRISEbits.RE0= 1;        //RE0 como entrada
    ANSELEbits.ANSE0= 1;     //RE0 analógico
    
// Configura el canal analogico 
    ADCON0= 0x14;           //00010100b, selecciono canal5, deshabilitado, no empieza conv.
    ADCON1= 0x00;           //voltaje referencia: 5V - 0V  (internos)  
    ADCON2= 0x14;           //Tacq= 4xTAD, FOSC/4, justificación izquierda
    ADCON0bits.ADON= 1;     //Habilitamos el ADC.
    /*
//configuro y habilito interrupciones
    INTCONbits.GIE = 0;         // Deshabilito todas las interrupciones    
    INTCON2bits.RBPU = 0;       // Configura el PULL-UP.
    INTCONbits.IOCIE = 1;       // Habilito interrupciones del PB y PC
    IOCB = 0xF0;                // Habilito las interrupciones individuales PB
    INTCONbits.PEIE = 1;        // Habilito Interrupción de baja prioridad
    INTCON2bits.IOCIP = 0;      // Teclado en baja prioridad
      
    */
//configuro el TIMER0
    T0CONbits.TMR0ON = 1;       //TMR0 empieza
    T0CONbits.T08BIT = 0;       //16 bits
    T0CONbits.T0CS = 0;         //Habilitar temporizador
    T0CONbits.T0SE = 0;         //Bit sin importancia
    T0CONbits.PSA = 0;          //Habilitar preescaler
    T0CONbits.T0PS = 0b111;     //Preescaler 1/256
    INTCONbits.GIE = 1;         // Habilito todas las interrupciones 
    INTCONbits.TMR0IE = 1;      //Habilito interrupcion del timer
    
   
//Programa Principal
    LCD_Inicio();
    __delay_ms(50);
    TMR0 = 61630;
//Auto fantastico de 6 ledxs
    while(1){
        
        
        LATA = fantastico & flag1;
        if (fantastico == 0x01 || flag == 1){
            fantastico = fantastico << 1;
            flag = 1;
        }
        LATA = fantastico & flag1;
        if (fantastico == 0x20 || flag == 0){
            fantastico = fantastico >> 1;
            flag = 0;
        }
        __delay_ms(200);
    }
   
}

/****************** mis funciones o interrupciones ******************/
void __interrupt () ISR_TIMER_0(void){
    
    if(INTCONbits.TMR0IF){
        for(fila = 0;fila <= 3;fila ++){
            PORTB = scan[fila];
            if(columna1 == 0)
                tecla = teclado[fila][0];
            if(columna2 == 0)
                tecla = teclado[fila][1];
            if(columna3 == 0)
                tecla = teclado[fila][2];
            if(columna4 == 0)
                tecla = teclado[fila][3];
        }
        LATB = 0X00;
        if(tecla>0x09 && tecla!=0x0F && flag3 == 0xFF){
            cont1++;
            cuenta = 1;
            flag1 = 0xFF;
            LCD_Inicio();
            LCD_GotoXY(2,4);
            LCD_Cadena("Bienvenido!!");
            tecla = 0;
            __delay_ms(2000);
            cuenta = 0;
            contador = 0;
            LCD_Borrar();
            LCD_GotoXY(0,0);
            LCD_Cadena("Numero de muestras:");
            flag3 = 0x00;
            tecla = 0;
            
        }
        else if(tecla == 0x0F){
            LCD_Borrar();
            LATDbits.LATD3 = 0;
            cont1 = 0;
            cont2 = 0;
            tecla = 0;
            flag1 = 0x00;
            flag3 = 0xFF;
            flag4 = 0xFF;
            flag5 = 0xFF;
            i=1;
        }
        else if(cont1 > 0 && cont2 == 0 && tecla <= 0x09 && tecla !=0 && flag4 == 0xFF ){
            LATB = 0X00;
            LCD_GotoXY(9,2);
            LCD_Data(display[tecla]);
            cont2++;
            cont1 = 0;
            num_muestras = tecla;
            tecla = 0;
            flag4 = 0x00;
        }    
        else if(tecla == 0x0B && cont2 > 0 && flag5 == 0xFF){
            
            LCD_GotoXY(3,0);
            LCD_Cadena("Temperatura[");
            LCD_GotoXY(12,3);
            LCD_Data(i + 0x30);
            LCD_GotoXY(14,3);
            LCD_Cadena("] = ");
            ADCON0bits.GO_DONE = 1;
            while(ADCON0bits.GO_DONE);
            float temp = (ADRESH * 150.) / 77.;
            char valor[5];
            sprintf(valor,"%.2f",temp);
            LCD_GotoXY(4,4);
            LCD_Cadena(valor);
            __delay_ms(1000);   
            i++;
            if(i>num_muestras)
                flag5 = 0x00;
            tecla = 0;
        }
        INTCONbits.TMR0IF = 0;
        TMR0 = 61630;
    }
}  

unsigned char dispctrl = 0x00;
void LCD_Inicio(void){
    __delay_ms(15);             // espero 15 ms
	LATD= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
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

void LCD_Numero(float numero, unsigned char fila, unsigned char columna){
    unsigned int cuenta;
    LCD_GotoXY(fila, columna);        // Posiciona cursor al inicio de la fila 2
// Se imprime en el LCD
    
    int num = (long) ( numero * 10 / 1);
    int cociente = num / 10;                // Divide y toma la parte entera
    int residuo = num % 10;                 // Divide y toma el residuo
    LCD_Data(cociente + 0x30);              // Convierte a ASCII e imprime en LCD
    LCD_Data('.');                          // Imprime punto decimal
    int divisor = 10;
    for(cuenta=2; cuenta<3; cuenta++){
        cociente = (residuo / divisor);     // Divide y toma la parte entera
        residuo = residuo % divisor;        // Divide y toma el residuo
        LCD_Data(cociente + 0x30);          // Convierte a ASCII e imprime en LCD
        divisor = divisor /10;
    }
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