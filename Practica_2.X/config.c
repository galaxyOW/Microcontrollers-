#include "config.h"

void configPIC(void){
    
    // Declaring ports as outputs.
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
    
    // Defining LED variable as an output. 
    
    LED_TRIS = OUTPUT;
    
    // Deactivating internal interruptions. 
    GIE = _OFF;
    
    // Defining the push as input. 
    
    FLANCO_TRIS = INPUT;
    
    //Deactivating internal clock configurations. 
    
    T0CONbits.T0CS = 1;   //0 = temporizador
    T0CONbits.PSA = 1; //no escalador
    T0CONbits.T08BIT = 1;  //TMR0 16bit timer
    T0CONbits.TMR0ON = 1;        
}

