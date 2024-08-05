#include "miConfiguracion.h"

#define ROW0_PIN PORTBbits.RB7
#define ROW1_PIN PORTBbits.RB6
#define ROW2_PIN PORTBbits.RB5
#define ROW3_PIN PORTBbits.RB4
#define COL0_PIN PORTBbits.RB3
#define COL1_PIN PORTBbits.RB2
#define COL2_PIN PORTBbits.RB1
#define COL3_PIN PORTBbits.RB0

#define ROW0_DIR TRISBbits.TRISB7
#define ROW1_DIR TRISBbits.TRISB6
#define ROW2_DIR TRISBbits.TRISB5
#define ROW3_DIR TRISBbits.TRISB4
#define COL0_DIR TRISBbits.TRISB3
#define COL1_DIR TRISBbits.TRISB2
#define COL2_DIR TRISBbits.TRISB1
#define COL3_DIR TRISBbits.TRISB0

void Teclado_Inicio(void);
char Teclado_Obtener(void);