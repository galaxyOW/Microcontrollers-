#include "config.h"

void configPIC(void){
    
    // Defining ports as OUTPUTS 
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
  
    //LEDS
    
    COUNTTRIS1 = OUTPUT;
    COUNTTRIS2 = OUTPUT;
    COUNTTRIS3 = OUTPUT;
    COUNTTRIS4 = OUTPUT;
    
 
    //RAQUET BUTTONS
    BUTTONTRIS1 = INPUT;
    BUTTONTRIS2 = INPUT;
    BUTTONTRIS3 = INPUT;
    
    // Random condition
    RANDOMBIT1 = INPUT;
    RANDOMBIT2 = INPUT;
    RANDOMBIT3 = INPUT;
    RANDOMBIT4 = INPUT;
    
    
    ENABLETRIS = OUTPUT;
            
    COUNT1 = 0;
    COUNT2 = 0;
    COUNT3 = 0;
    COUNT4 = 0;

    // Activating Interruptions  
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 0;
    TMR1IE = 0;
    
    ADCON1 = 0xFF;
    
    // TMR0 Configuration
    
    T0CONbits.T0PS0 = 0;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 0;   // Pre-scale value at 1:128
    T0CONbits.PSA = 1;    //  Assigning pre-scaler  
    T0CONbits.T0CS = 0;   // TMR0 
    T0CONbits.T08BIT = 1;  // TMR0 is an 8 bit timer
    T0CONbits.TMR0ON = 1;
    
    T1CON = 0b10000001;
    PIE1bits.TMR1IE = 1;
    TMR1ON = 0;
    TMR1L = 6;
    TMR0L = 0;
}


void delay_ms(unsigned int milliseconds){
    while(milliseconds > 0){
        __delay_ms(1);
        milliseconds--;
    }
}








