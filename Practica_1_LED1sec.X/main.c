#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)


#include "config.h"

void main(void)
{  
   
    configPIC();
    TMR1L = 6;
    count = 0;  //detenerse al llegar a 375
	
    while(1)
    {
        LED = 1;
    
        while(count<375)
        { 
            while(!TMR1IF);
            TMR1IF = 0;
            count++;
            TMR0L = 6;
        }

        count = 0;
        LED = 0;

        while(count<375)
        { 
            while(!TMR1IF);
            TMR1IF = 0;
            count++;
            TMR1L = 6;
        }

    count = 0;
    } 
}
