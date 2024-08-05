PROCESSOR 18F45K50
#include "mi_configuracion.inc" 
    
PSECT udata_acs	    ; sección de datos
X1:    DS 1;	    TMP -> 1 BYTE 
X2:    DS 1;	    TMP -> 1 BYTE 
X3:    DS 1;	    TMP -> 1 BYTE 
   
PSECT prueba,CLASS =CODE,reloc=2,abs	;seccion de programa
prueba:
    
    ORG	    000000H	    ; vector de reset
    GOTO    INICIO
        
    ORG	    000020H	    ; zona de interrupciones
    
INICIO:
;configuro frecuencia de 4MHz
    MOVLB   0FH			; CONMUTA banco 15
    MOVLW   56H
    MOVWF   OSCCON,1		; HFINTOSC a 4MHz
    CLRF    OSCCON2,1
;configuro puerto de E/S
    CLRF    LATB,1		; Limpia latch de salida
    CLRF    TRISB,1		; PB como salida 
    CLRF    ANSELB,1		; configura todo PB como digital
    MOVLB   0			; Retorna al banco CERO

loop:
    MOVLW   0H
    MOVWF   LATB,0		; PORTB cero
    MOVLW   5
    CALL    delay_50ms
    MOVLW   0FFH
    MOVWF   LATB,0		; PORTB cero
    MOVLW   5
    CALL    delay_50ms    
    GOTO    loop

;*****************************************************************
;area de subrutinas o procedimientos
;*****************************************************************
delay_50ms:		    ;inicio de subrutina
			    ;1C = 1uS
    MOVWF   X1,0	    ;tiempo = X1 * 50ms		
LX1:
	MOVLW   50	    ;1C 
	MOVWF   X2,0	    ;1C 
LX2:			    ;tiempo XL2 = 50*1ms = 50ms
	    MOVLW   200	
	    MOVWF   X3,0	
LX3:			;tiempo bucle XL3 = 200*5*C = 1000*1us=1ms
	    NOP		    ;1C
	    NOP		    ;1C
	    DECFSZ  X3,1,0  ;1C   
	    GOTO    LX3	    ;2C
	DECFSZ  X2,1,0	    ;1C    
	GOTO    LX2	    ;2C 
    DECFSZ  X1,1,0	    ;1C    
    GOTO    LX1		    ;2C 	
    RETURN		

;*****************************************************************
   
    END	    prueba		; fin del programa prueba



