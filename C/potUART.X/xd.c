//Enviar datos de un potenciometro por UART a AppDesigner
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "config.h"

void ADC_Init(void);
void GPIO_Init(void);
void USART_Init(void);
void USART_Transmit(const char* str);
char USART_Receive(void);

char datos[40];

void main(void)
{
// Configuracion de la frecuencia
    OSCCON = 0x52;                                                              //frecuencia 4MHz y activar reloj interno
    OSCCON2 = 0;                                                                //limpiar OSCCON2
    
// Configuracion de perifericos
    GPIO_Init();
    ADC_Init();
    USART_Init();
    
    while(1)
    {
        ADCON0bits.GODONE = 1;
        while(ADCON0bits.GODONE == 1);
        PORTD = ADRESL;
        sprintf(datos,"%d\n",ADRESL);
        USART_Transmit(datos);
        __delay_ms(1000);
    }
}

void GPIO_Init(void)
{
    //Leds
    TRISD = 0x00;                                                               // configurar el TRID como salida
    ANSELD = 0x00;                                                              // configurar el PORTD como digital
    
    //ADC
    TRISA = 0xFF;                                                               // configurar el TRISA como entrada
    ANSELA = 0xFF;                                                              // configurar el PORTA como analogico
    
    //UART
    TRISCbits.RC6 = 0;                                                          // RC6 = Tx -> Salida
    TRISCbits.RC7 = 1;                                                          // RC7 = Rx -> Entrada
    ANSELC = 0x00;                                                              // configurar el PORTC como digital
}

void ADC_Init(void)
{    
    ADCON1bits.PVCFG = 0;                                                       // seleccionar el voltaje de referencia VDD
    ADCON2bits.ADCS = 0b101;                                                    // reloj de conversión de fosc / 16                                                          
    ADCON0bits.CHS = 1;                                                         // seleccionar el canal AN1 = RA1
    ADCON2bits.ADFM = 1;                                                        // justificacion a la derecha
    ADCON2bits.ACQT = 0b011;                                                    // tiempo de adquisicion de 6TAD
    ADCON0bits.ADON = 1;                                                        // habilitamos el ADC
}

void USART_Init(void)
{
    RCSTAbits.SPEN = 1;                                                         // habilitar el puerto UART
    TXSTAbits.TX9 = 0;                                                          // transmision de 8 bits
    TXSTAbits.TXEN = 1;                                                         // activar transmision
    TXSTAbits.SYNC = 0;                                                         // selecciono modo asincrono
    RCSTAbits.RX9 = 0;                                                          // recepcion de 8 bits
    RCSTAbits.CREN = 1;                                                         // activar recepcion   
    TXSTAbits.BRGH = 1;                                                         // indicar baja velocidad      
    SPBRG = 25;                                                                 // configurar el baudaje
}

void USART_Transmit(const char* str)
{
    while(*str)
    {
        while(!TXSTAbits.TRMT);                                                 // Espera hasta que el registro de transmisión esté vacío
        TXREG = *str++;                                                         // Envía el caracter actual y luego incrementa el puntero
    }
}

char USART_Receive(void)
{
    return RCREG;
}