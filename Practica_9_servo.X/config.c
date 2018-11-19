#include "config.h"

int flag=0;

void configPIC(void)
{
    // Selecting the oscilator for the clock 
    
    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 0;
   
    // Selecting the speed for the internal oscilator (2 MHz)
    
    OSCCONbits.IRCF0=1;
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF2=0;
    OSCCONbits.OSTS=1;
    

    TRISA = OUTPUT;
    TRISB = INPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
    
    INTCONbits.GIE = 1;  
    INTCONbits.PEIE= 1;
    TMR1IE=1;
    ADCON1=0xFF;

    
}

void OpenTimer2(unsigned char Timer2Config){
    T2CONbits.T2CKPS=Timer2Config;   
    TMR2ON=1; 
}

void OpenPWM1(unsigned char PR2Value){
    CCP1CONbits.CCP1M0=0;
    CCP1CONbits.CCP1M1=0;
    CCP1CONbits.CCP1M2=1;
    CCP1CONbits.CCP1M3=1;
    CCP1CONbits.P1M0=0; 
    CCP1CONbits.P1M1=0;
    
    TRISCbits.RC2=0;
    TMR2ON=0; 
    PR2=PR2Value; 
    TMR2ON=1; 
}

void SetDCPWM1(unsigned int DC){
    CCPR1L=DC>>2; 
    DC1B1=(DC & 0x0002)?1:0;
    DC1B0=(DC & 0x0001)?1:0;
}

