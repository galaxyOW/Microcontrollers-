#include "config.h"


void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = INPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    LED_TRIS = OUTPUT;
    
    // Activating Interruptions 
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    INTCONbits.INT0IE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2IE = 0;
   
    ADCON1 = 255;
       
    
    T0CONbits.TMR0ON = 0;        
    
}











