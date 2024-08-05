PROCESSOR 18F45K50    ; modelo del MICRO
#include "miConfiguracion.inc"    ; llama a la configuración de bits    
   
PSECT udata_acs    ; sección de datos
X1:    DS 1;    TMP -> 1 BYTE
X2:    DS 1;    TMP -> 1 BYTE
X3:    DS 1;    TMP -> 1 BYTE
cuenta:    DS 1;   TMP -> 1 BYTE
aux: DS  1;
PSECT labo1, CLASS = CODE, reloc=2, abs    ; sección de programa
labo1:
   
    ORG    000000H    ; vector de reset
    GOTO    INICIO
       
    ORG    000020H    ; zona de programa de usuario
INICIO:
;configuro frecuencia de 4MHz
    MOVLB   0FH ; CONMUTA banco 15
    MOVLW   56H
    MOVWF   OSCCON,1 ; HFINTOSC a 4MHz
    CLRF    OSCCON2,1
;configuro puerto de E/S
    CLRF    LATB,1 ; Limpia latch de salida
    CLRF    TRISB,1 ; PB como salida
    CLRF    ANSELB,1 ; configura todo PB como digital
    MOVLB   0
    MOVLW   0
    MOVWF   cuenta
    MOVLW   1
    MOVWF   cuenta
   
loop:
    MOVFF   cuenta, LATB
    RLNCF   cuenta, 1
    MOVLW   5
    call    delay_50ms
    MOVLW   80h
    cpfseq  cuenta
    goto    loop
    goto    invertir
   
invertir:
    MOVFF   cuenta, LATB
    RRNCF   cuenta, 1
    MOVLW   5
    call    delay_50ms
    MOVLW   1
    cpfseq  cuenta
    goto    invertir
    goto    loop
;***********************
;area de subrutinas o procedimientos
;***********************
delay_50ms:    ;inicio de subrutina
   ;1C = 1uS
    MOVWF   X1,0    ;tiempo = X1 * 50ms
LX1:
MOVLW   50    ;1C
MOVWF   X2,0    ;1C
LX2:    ;tiempo XL2 = 50*1ms = 50ms
   MOVLW   200
   MOVWF   X3,0
LX3: ;tiempo bucle XL3 = 200*5*C = 1000*1us=1ms
   NOP    ;1C
   NOP    ;1C
   DECFSZ  X3,1,0  ;1C  
   GOTO    LX3    ;2C
DECFSZ  X2,1,0    ;1C    
GOTO    LX2    ;2C
    DECFSZ  X1,1,0    ;1C    
    GOTO    LX1    ;2C
    RETURN

   
    END    labo1 ; fin del programa prueba



