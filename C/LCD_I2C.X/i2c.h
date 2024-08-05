#include "miConfig.h"

//Pines
#define TRIS_SCL TRISBbits.RB1
#define TRIS_SDA TRISBbits.RB0

//Declaracion de Funciones
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_TX(char data);
char I2C_RX(void);