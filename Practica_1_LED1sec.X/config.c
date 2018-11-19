#include "config.h"

void configPIC(void)
{
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
            
    LED_TRIS = OUTPUT;
    GIE = _OFF;
    PEIE = _ON;
    
    //TMR0Config
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1;   // Prescalador a 1:128
    T0CONbits.PSA = 0;    //  asignar prescalador 
    T0CONbits.T0CS = 0;   // TMR0 trabaja como Timer
    T0CONbits.T08BIT = 1;  // TMR0 es un timer de 8 bits
    T0CONbits.TMR0ON = 1;
    
    T1CON = 0b10000001;
    PIE1bits.TMR1IE = 1;
}

