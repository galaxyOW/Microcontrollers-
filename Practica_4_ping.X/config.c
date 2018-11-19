#include "config.h"

void configPIC(void){
    
    // Defining ports as outputs.
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
    
    //Deactivating internal interruptions.
    
    INTCONbits.GIE = _OFF;

    ADCON1 = 0xFF;
}





