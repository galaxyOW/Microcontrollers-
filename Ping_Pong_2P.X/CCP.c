#include <pic18f4550.h>

#include "config.h"
#include "configLCD.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

void OpenTimer2(){
    
    // Configuring T2CON to have a pre-scaler value of 16 and turning the timer on
    T2CON = 0b00000101;
}

void OpenPWM1(unsigned int PR2Value){
    
    // Configuring CCP1CON to generate PWM signals
    CCP1CON = 0x0C;
    
    // Configuring CCP1 as output
    TRISCbits.RC2 = OUTPUT;
    
    // Stopping the TIMER2 
    TMR2 = _OFF;
    
    // Loading the PWM signals frequency using the register. 
    PR2 = PR2Value;
    
    // Starting the TMR2
    T2CONbits.TMR2ON = _ON;
}

void SetDCPWM1(float DC){
    // Loading the PWMs duty cycle into the registers
    CCPR1L = DC;
}

void SetDCPWM2(unsigned int DC2){
     CCPR1L = (DC2 >> 2);
     DC1B1 = (DC & 0x0002) ? 1:0;
     DC1B0 = (DC & 0x0001) ? 1:0;
}






