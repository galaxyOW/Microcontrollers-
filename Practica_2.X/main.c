#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)


#include "config.h"

// Creating function that will wait till x amount of pulses before turning ON/OFF LED> 

 void waitForNCounts(unsigned int n, unsigned char edge){
    
    // Converting a char into a number. 
     
    int a;
    a = edge - '0';
    T0CONbits.T0SE = a;
    
    // Reseting the counter variable. 
    TMR0L = 0;
    T0IF = 0;
    
    int help;
    help = n/255;
    
    while(help != 0){
        if(T0IF == 1){
            T0IF = 0;
            help--;
        }
    }
    int x;
    x = n%255;
    while(TMR0L < x){
        
    }
    
}
 
void main(void) {
    
    // Calling function which will allow us to be able to use the PIC. 
    
    configPIC();
    
    // Starting the program with the LED turned OFF. 
    
    LED = _OFF;
    
    while (1){
        
        // Wait function called to check that 10 pulses have been pressed before continuing. 
        
        waitForNCounts(10,'0');
        LED = _ON; 
        
        waitForNCounts(10,'0');
        LED = _OFF;
    }
    return;
}