/*
 The 48 MHz clock that's normally used could not be used since it gave us 10 bit values for 
 * the PR2 register that can only hold 8 bit values. The clock was changed to an internal 
 * clock that has a speed of 8 MHz. The configuration for this can be found in the config.c 
 * and config.h files. 
 */

// Including libraries necessary to use strings.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including files necessary to run the program

#include "configLCD.h"
#include "config.h"
#include "CCP.h"

// Declaring PR2 and duty cycle values. (They are subjected to change at any given moment)

int PR2Value = 62;

// ----------------------

float Duty_Cycle = 0;
float d;

void main()
{
    OSCCON=0x72;                        // Configure oscillator frequency to 8MHz 
    LED = _ON;
    
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configLCD();
    OpenTimer2();
    OpenPWM1(PR2Value);
    SetDCPWM1(Duty_Cycle);
    
    while(1){    

        for( Duty_Cycle = 0; Duty_Cycle <= 1.05; Duty_Cycle = Duty_Cycle + .05)
        {
            d = (Duty_Cycle * 63.5);     // Calculating exact value for duty cycle.
            SetDCPWM1(d);                // Loading new duty cycle
            __delay_ms(125);
        }
        
        
        for(Duty_Cycle = 1; Duty_Cycle >= 0; Duty_Cycle = Duty_Cycle - .05)
        {
            d = (Duty_Cycle * 63.5);     // Calculating exact value for duty cycle.
            SetDCPWM1(d);                // Loading new duty cycle
            __delay_ms(125);
        }
        
        // Just ensuring that the Duty cycle ends at 0. 
        
        SetDCPWM1(0);
          
    }
}


