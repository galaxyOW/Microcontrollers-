#include "config.h"
#include "configLCD.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

void configCCP(){
    
    TRISCbits.RC2 = OUTPUT;
    CCP1CON = 0b00001001;
    T1CON = 0b11000000;
    PIE1bits.CCP1IE = 0;
    PIR1bits.CCP1IF = 0;
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    
    
    CCPR1H = 0b00000000;
    CCPR1L = 0b00000000;
    
       
}


