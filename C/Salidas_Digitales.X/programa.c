//Grupo #3 -> EE604 Seccion M
#include "configuracion.h"

//Declaracion de funiones
void configurarPines();

void main(void){
    configurarPines();

    //Programa Principal
    while(1){
        LATDbits.LATD2 = 1;
        __delay_ms(300);
        LATDbits.LATD2 = 0;
        __delay_ms(300);
    }
}

void configurarPines(){
    //configuro frecuencia de 4MHz del oscilador interno
    OSCCON = 0x52;          //frecuencia 4MHz
    OSCCON2 = 0;            //limpiamos OSCCON2 para evitar errores
    
    //configuro puertos de entrada y salida   
    //TRISX -> 0 (salida), 1 (entrada)
    //ANSELX -> 0 (digital), 1 (analogico)
    //LATX -> 0 (apagar), 1 (encender)
    
    TRISDbits.RD2 = 0;
    ANSELDbits.ANSD2 = 0; 
}