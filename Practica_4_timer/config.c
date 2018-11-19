#include "config.h"

void configPIC(void){

    // Setting the ports as outputs. 
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
    
    //Deactivating the internal interrupt. 
    
    INTCONbits.GIE = _OFF;

    ADCON1 = 0xFF;
}

