;Laboratorio Calificado N°1
PROCESSOR 18F45K50		    ; modelo del MICRO
#include "miConfiguracion.inc"		    ; llama a la configuración de bits    
    
PSECT udata_acs	    ; sección de datos
X1:    DS 1;	    TMP -> 1 BYTE 
X2:    DS 1;	    TMP -> 1 BYTE 
X3:    DS 1;	    TMP -> 1 BYTE 
cuenta:	    DS 1;   TMP -> 1 BYTE 
PSECT labo1, CLASS = CODE, reloc=2, abs    ; sección de programa
labo1:
    ORG	    000000H	    ; vector de reset
    GOTO    INICIO
        
    ORG	    000020H	    ; zona de programa de usuario
INICIO:
;configuro frecuencia de 4MHz
    MOVLB   0FH			; CONMUTA banco 15
    MOVLW   56H
    MOVWF   OSCCON,1		; HFINTOSC a 4MHz
    CLRF    OSCCON2,1
;configuro puerto de E/S
    SETF    TRISA,1		; PA como entrada
    CLRF    ANSELA,1		; configura todo PA como digital
    
    CLRF    LATB,1		; Limpia latch de salida
    CLRF    TRISB,1		; PB como salida
    CLRF    ANSELB,1		; PB como digital
    
    CLRF    LATD,1		; Limpia latch de salida
    CLRF    TRISD,1		; PD como salida 
    CLRF    ANSELD,1		; configura todo PD como digital
    
    MOVLB   0			; Retorna al banco CERO
    CLRF    cuenta,1		;limpiamos cuenta
    
apagaralarma:
    BCF	    PORTB,0     ;RB0 0
    BCF	    PORTB,1	;RB1 0
    GOTO    testA
testA:
    BTFSS   PORTA,3	;testea A
    GOTO    testB
    GOTO    test_error	;A pulsado
testB:
    BTFSS   PORTA,2	;testea B
    GOTO    testC
    GOTO    test_error2  ;B pulsado
testC:
    BTFSS   PORTA,1     ;testea C
    GOTO    testD
    GOTO    test_error3  ;C pulsado
testD:
    BTFSS   PORTA,0      ;testea D
    GOTO    apagarms     ;D desactivada, se apagan los motores
    GOTO    prenderms    ;D activado, va a A y se genera bucle

test_error:
    BTFSS   PORTA,2   ;testeando B
    GOTO    alarma
    GOTO    test_error2    ;B activado
test_error2:    
    BTFSS   PORTA,1	;TESTEANDO C
    GOTO    alarma
    GOTO    test_error3	;C activado
test_error3:
    BTFSS   PORTA,0	;testea D
    GOTO    alarma
    GOTO    decision    ;D activado

decision:  ;si llega hasta aqui significa que minimo CyD estan activados    
    BTFSS   PORTA,2       ;testea B
    GOTO    prenderms     ;B no prendido, entonces CyD sí, prende ambos motores
    BTFSS   PORTA,3	  ;testea A
    GOTO    prender_m1    ;A no prendido, entonces B,C,D sí, prende 1
    GOTO    apagarms	  ;A,B,C,D prendidos entonces apaga ambos para que no rebalse
    
alarma:
    BSF	    PORTB,0     ;RB0 1
    BCF	    PORTB,1	;RB1 0
    BCF     PORTD,0
    BCF     PORTD,1
    BCF	    PORTD,2
    BCF	    PORTD,3	;apagamotores
    GOTO    testA	;si hay un error llega aqui y vuelve a testear a ver si se soluciona el error para ver si apaga     
    
prender_m1:
    BSF    PORTD,0
    BCF    PORTD,1
    GOTO   apagaralarma
prenderms:
    BSF    PORTD,0
    BCF    PORTD,1
    BSF    PORTD,2
    BCF    PORTD,3
    GOTO   apagaralarma
apagarms:
    BCF    PORTD,0
    BCF    PORTD,1
    BCF	   PORTD,2
    BCF	   PORTD,3
    GOTO   apagaralarma
    
;*********************
;area de subrutinas o procedimientos
;***********************
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

   
    END	    labo1		; fin del programa prueba