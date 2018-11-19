#include "config.h"

void configPIC(void){
    
    // Defining all ports as outputs.
    
    TRISA = OUTPUT;
    TRISB = INPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
    
    // Defining LED as an output.
    
    LED_TRIS = OUTPUT;
    
    // Activating interruptions.
    
    INTCONbits.GIE = _ON;
    INTCONbits.PEIE = _ON;
    INTCONbits.INT0IE = _ON;
    INTCON3bits.INT1IE = _ON;
    INTCON3bits.INT2IE = _ON;
    INTCON2bits.INTEDG0 = 1;
    INTCON2bits.INTEDG1 = 0;
    INTCON2bits.INTEDG2 = 0;
    
    ADCON1 = 0xFF;
    
    // Defining the interruptions as inputs in order to read the buttons.
    
    FLANCO_TRIS = INPUT;
    INTERRUPCION_A = INPUT;
    INTERRUPCION_B = INPUT;
    
}

