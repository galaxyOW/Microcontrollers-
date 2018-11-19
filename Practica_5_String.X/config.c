#include "config.h"


void configPIC(void)
{
    ADCON1 = 0x0F;
    TRISA= OUTPUT; 
    LED=0;
    BOTON_TRIS = INPUT;
    BOTON=0;
    
    // Activating the interruptions. 
    
    INTCONbits.GIE = 1; 
    INTCONbits.PEIE = 1;            // Periferical interruption. 
}



