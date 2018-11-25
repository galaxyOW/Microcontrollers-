
#include <pic18f4550.h>

#include "config.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

void OpenTimer2(){
    
    // Configuring T2CON to have a pre-scaler value of 16 and turning the timer on
    T2CON = 0b00000111;
}

void OpenPWM1(unsigned char PR2Value){
    
    // Configuring CCP1CON to generate PWM signals
    CCP1CON = 0x0C;
    
    // Configuring CCP1 as output
    TRISCbits.RC2 = OUTPUT;
    
    // Stopping the TIMER2 
    TMR2 = _OFF;
    
    // Loading the PWM signals frequency using the register. 
    PR2 = PR2Value;
    
    // Starting the TMR2
    TMR2ON = _ON;
}

void SetDCPWM1(float DC){
    // Loading the PWMs duty cycle into the registers
    CCPR1L = DC;
}



