PROCESSOR 18F45K50
#include "mi_configuracion.inc"
    
PSECT main,CLASS = CODE,reloc=2,abs
main:
    ORG	    000000H			    ; vector de reset
    GOTO    INICIO
        
    ORG	    000020H			    ; zona deinterrupciones

INICIO:
;configuro frecuencia de 4MHz
    MOVLB   0FH			; banco 15
    MOVLW   52H
    MOVWF   OSCCON,1		; HFINTOSC a 4MHz
    CLRF    OSCCON2,1
;configuro puerto de E/S    
    CLRF    LATB,1		; Limpia latch de salida
    BCF	    TRISB,3		; PB.3 como salida 
    BCF	    ANSELB,3		; PB.3 como digital
    BSF	    TRISA,0		; PA.0 como entrada 
    BCF	    ANSELA,0		; PA.0 como digital
    MOVLB   0			; Retorna al banco CERO

lee1:
    BTFSS   PORTA,0		; pregunto si PA.0 es uno?
    GOTO    noes
    BCF	    LATB,3		; es uno, prende LED
    GOTO    lee1		; repite proceso
noes:
    BSF	    LATB,3		; no es uno, apaga LED
    GOTO    lee1
    
    END	    main