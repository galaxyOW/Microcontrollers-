#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /2][96 MHz PLL Src: /3])
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF

// Including necessary files and libraries.

#include "config.h"
#include "globaldefinition.h"
#include <xc.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// Defining global variables.

float DCycle = 20;
float object;

int dist,timec;
int PR2Value = 200;

unsigned int flag = 1;

void main(void) {
    
    // Configuring PIC and CCP register. 
    
    configPIC();
    OpenTimer2();
    OpenPWM1(PR2Value);
    SetDCPWM2(DCycle);
    timer1config();

    TRIG = 0;                           // TRIG was meant to be used for the ultrasonic sensor. 
    LED = _OFF;                         // LED turned OFF at the start in order to see if the PIC initialised properly
    
    __delay_ms(1000);
    LED = _ON;
  
    while(1){
        
        if(flag == 1)
        {
            line_follow();              // Calling line follow function so that the car can follow a black line. 
        }
    }
}


