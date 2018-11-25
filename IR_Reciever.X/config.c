#include "global_definitions.h"
#include "config.h"

void configPic (){
    
    ADCON1 = 0x0F;              // Set all pins as digital pins. 

    TRIS_TSOP = INPUT;
    TSOP = _OFF;

    T3CONbits.RD16=1;

    // Deactivating TMR3 for the CCP1 and CCP2 modules
    
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 0;
    
    // Assigning pre-scaler value for the TMR3. 
    
    T3CONbits.T3CKPS =0b11;

    // Choosing signal source for the TMR0.
    
    T3CONbits.TMR3CS=0;
    
    TMR3ON = _OFF;                      // TMR3 natural state is off. This means the TMR is not counting.
    TMR3L = 0;
    TMR3H = 0;
    TMR3IF = 0;

    INTCONbits.GIE = 1;                 // Turning on global interruptions.
    INTCONbits.PEIE = 1;
    INTCONbits.INT0IE = 0;              // Deactivating external interruptions for INT0.
    INTCON2bits.INTEDG0 = 0;            // Interrupt is activated for falling edges. 
    INTCONbits.INT0IF =0;               // Starting with the flag at 0.
}


