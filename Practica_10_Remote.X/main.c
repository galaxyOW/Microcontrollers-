#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /2][96 MHz PLL Src: /3])
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF   


// Including libraries necessary to use strings.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including files necessary to run the program

#include "configLCD.h"
#include "config.h"
#include "CCP.h"

int PR2Value = 79;
float DCycle = (.5)*79;                     // Using a 50% duty cycle.

void main()
{   
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configLCD();
    OpenTimer2();
    OpenPWM1(79);
    SetDCPWM1(79);

    
    while(1)
    {
        
        
        if(UP == 1)
        {
            UP_BTN();
            while(UP == 1);
        }
        
        if(LEFT == 1)
        {
            LEFT_BTN();
            while(LEFT == 1);
        }
        
        if(RIGHT == 1)
        {
            RIGHT_BTN();
            while(RIGHT == 1);
        }
        
        // The central buttons sends two signals
        
        if(CENTRAL == 1 ){
            CENTRAL_BTN();
            CENTRAL_BTN();
            while(CENTRAL == 1);
        }
        
        // The down button also sends two signals. 
        
        if(DOWN == 1)
        {
            DOWN_BTN();
            DOWN_BTN();
            while(DOWN == 1);
        }
        
        if(MENU == 1)
        {
            MENU_BTN();
            while(MENU ==1);
        }
    }
    
}
