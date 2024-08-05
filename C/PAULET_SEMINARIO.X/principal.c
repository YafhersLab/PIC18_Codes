// PIC18F45K50
#include <xc.h>

int miDato;

//Funciones
void USART_Init(void);
void USART_Transmit(void);
void USART_Receive(void);

void main(void) {
    USART_Init();
    USART_Transmit("HOLA");
    miDato = USART_Receive();
    return;
}

void USART_Init(void){
    RCSTAbits.SPEN = 1;             // habilitar el puerto 
    TXSTAbits.TX9 = 0;              // transmision de 8 bits
    TXSTAbits.TXEN = 1;             // activo la transmision
    TXSTAbits.SYNC = 0;             // modo asincrono
    RCSTAbits.RX9 = 0;              // recepcion de 8 bits
    RCSTAbits.CREN = 1;             // activo la recepcion
    TXSTAbits.BRGH = 1;             // indicar baja velocidad
    SPBRG = 25;                     // baudaje = 9600
}

void USART_Transmit(const char* palabra){
    while(*palabra){
        while(!TXSTAbits.TRMT){
            TXREG = *palabra++;
        }
    }
}

void USART_Receive(void){
    return RCREG;
}