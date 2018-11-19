#include "config.h"
#include "configLCD.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

void configCCP(){
    
    // Configuring the CCP1 module with the TMR1 module
    
    TRISCbits.RC2 = OUTPUT;
    CCP1CON = 0b00001011;
    T1CON = 0b11000000;
    PIE1bits.CCP1IE = 0;
    PIR1bits.CCP1IF = 0;
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    TMR1ON = 1;
    CCPR1 = 65535;
    

      
}



