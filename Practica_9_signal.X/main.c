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

// Delcaring PR2 and duty cycle values. (They are subjected to change at any given moment)

int PR2Value = 149;
float DCycle = 90;

void main()
{
    LED = _ON;
    
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configLCD();
    OpenTimer2();
    OpenPWM1(PR2Value);
    SetDCPWM1(DCycle);
    
    __delay_ms(20);
    LCD_write("Generating Freq.");

    
    while(1);
}

