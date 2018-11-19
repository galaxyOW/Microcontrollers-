#include "config.h"


void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    // Activating Interruptions 
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INT0IE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2IE = 0;
   
    ADCON1 = 0b00001111;
       
    T0CONbits.T0CS = 0;   //0 = temporizador
    T0CONbits.TMR0ON = 0;        
    
}




