#include "config.h"


void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    CENTRAL_TRIS = INPUT;
    UP_TRIS = INPUT;
    LEFT_TRIS = INPUT;
    RIGHT_TRIS = INPUT;
    DOWN_TRIS = INPUT;
    MENU_TRIS = INPUT;
    // Activating Interruptions 
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 0;
   
    ADCON1 = 0b00001111;
       
    
    T0CONbits.TMR0ON = 0;        
    
}










