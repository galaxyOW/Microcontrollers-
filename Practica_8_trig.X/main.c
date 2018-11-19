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

// Declaring global variables

unsigned int value;
float light;
char chain[20];
int count = 0;

void main()
{
    LED = _ON;
    
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configCCP();
    configLCD();
    initADC();
    
    TMR1 = 0;
    
    while(1)        
    {   

        while(!CCP1IF);
        PIR1bits.CCP1IF = 0;
        count++;

        // If checks that the register has overflowed 183 times (which is equivalent to 1 second)
        
        if(count == 183)
        {
            LCD_Command(CLEAR);
            __delay_ms(20);
            value = ADC_read(0);
            light = ((value * 500) / 1023);
            sprintf(chain,"%.2f",light);  
            
            // Printing results
            
            __delay_ms(20);
            LCD_write("Intensity: ");
            __delay_ms(20);
            LCD_write(chain);
            
            // Count is reset in order to read 1 sec again. 
            
            count = 0;   
        }
    }
}
