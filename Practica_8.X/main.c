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
#include "configLCD.h"
#include "config.h"
#include "CCP.h"

/*
 To calculate the counts for CCP1:
 *      output = Oscillator Frequency / 4;
 *      Instruction cycle = 1 / output;
 *      Count = Desired delay / Instruction Cycle;
 * 
 In this case we used an oscillator frequency of 12MHz. 
 * Since we needed a frequency of 1kHz we needed a delay of 0.4ms and 0.6ms.
 */

void main()
{
    
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configCCP();
    configLCD();
    
    // Setting up bits for the CCP1CON register. 
    // The CCPR1 values are the counts previously calculated. 
    //They change to produce highs and lows for frequency
    
    TMR1 = 0;   
    CCPR1 = 0x1C20;
    T1CONbits.TMR1ON = 1;
    
    while(1)        
    {   
        // Waiting for the flag's status to change. 
        
        while(!CCP1IF);
        PIR1bits.CCP1IF = 0;
        TMR1 = 0;
        CCP1CON = 0b00001000;
        CCPR1 = 0x12C0;
        
        while(!CCP1IF);
        PIR1bits.CCP1IF = 0;
        TMR1 = 0;
        CCP1CON = 0b00001001;
        CCPR1 = 0x1C20;
    }
}



