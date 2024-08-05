#include "miConfig.h"
#include "i2c.h"

void I2C_Init(void){
    //Colocamos los pines como entrada
    TRIS_SCL = 1;
    TRIS_SDA = 1;
    //Configuramos el baudaje
    SSPSTATbits.CKE = 0;        //Desactivar SMBus
    SSPSTATbits.SMP = 1;        //100kHz
    //Configuramos el SSPCON
    SSPCON1bits.SSPEN = 1;       //Para usar SDA y SCL
    SSPCON1bits.SSPM = 0b1000;  //Modo maestro
    
    SSPCON2 = 0x00;             //Apagamos este registro porsiacaso
    SSPADD = 9;                 //Lo sacamos por formula para 100kHz
}

void I2C_Start(void){
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN == 1);
}

void I2C_Stop(void){
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN == 1);
}

void I2C_Restart(void){
    SSPCON2bits.RSEN = 1;
    while(SSPCON2bits.RSEN == 1);
}

void I2C_ACK(void){
    PIR1bits.SSPIF = 0;     //Generar interrupcion
    SSPCON2bits.ACKDT = 0;  //Enviar ACK
    SSPCON2bits.ACKEN = 1;  //Habilitar
    while(PIR1bits.SSPIF == 0);
}

void I2C_NACK(void){
    PIR1bits.SSPIF = 0;     //Generar interrupcion
    SSPCON2bits.ACKDT = 1;  //Enviar NACK
    SSPCON2bits.ACKEN = 1;  //Habilitar
    while(PIR1bits.SSPIF == 0);
}

void I2C_TX(char data){
    PIR1bits.SSPIF = 0;
    SSPBUF = data;
    while(PIR1bits.SSPIF == 0);
}

char I2C_RX(void){
    PIR1bits.SSPIF = 0;
    SSPCON2bits.RCEN = 1;   //Habilitar recepcion
    while(PIR1bits.SSPIF == 0);
    return SSPBUF;
}