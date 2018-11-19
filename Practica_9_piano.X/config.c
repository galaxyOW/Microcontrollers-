#include "config.h"


void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    LED_TRIS = OUTPUT;
    
    DO_TRIS = INPUT;
    DO2_TRIS = INPUT;
    RE_TRIS = INPUT; 
    RE2_TRIS = INPUT;
    MI_TRIS = INPUT; 
    FA_TRIS = INPUT; 
    FA2_TRIS = INPUT;
    SOL_TRIS = INPUT;
     
    SOL2_TRIS = INPUT; 
    LA_TRIS = INPUT; 
    LA2_TRIS = INPUT; 
    SI_TRIS = INPUT; 

    // Activating Interruptions 
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    INTCONbits.INT0IE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2IE = 0;
   
    ADCON1 = 0b00001111;
       
    
    T0CONbits.TMR0ON = 0;        
    
}








