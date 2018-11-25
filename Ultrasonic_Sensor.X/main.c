/*
 * 8MHz oscillator frequency is being used for this project. 
 */

// Including libraries necessary to use strings.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including files necessary to run the program

#include "configLCD.h"
#include "config.h"

void Trigger_Pulse_s();

#define _XTAL_FREQ 8000000                      // Defining frequency 
#define Trigger_Pulse LATA0                     // Defining Trigger pin of HC-SR04

void main()
{
    // Initialising PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configLCD();
    LED = _ON;
    OSCCON=0x72;                        // Configure oscillator frequency to 8MHz 
 
    float Distance;
    float total_Distance[10];
    int Time;
    
    INTCON2bits.RBPU = 0;               // Enables PORTB pull-ups
    Trigger_Pulse = 0;

    // Enabling 16-bit TMR1 Reg, no prescaler, internal clock, timer OFF
    T1CON = 0x80;                                               // 10000000
    TMR1IF = 0;                                                 // Make TMR1 overflow flat 0
    TMR1 = 0;
    

    LCD_write("Distance: ");
    
    while(1)
    {    
        Trigger_Pulse_s();
        while(PORTBbits.RB0 == 0);                              // Wait for rising edge at ECHO pin       
        TMR1 = 0;                                               // Start TMR1 at 0;

        TMR1ON = 1;                                             // Turning on TMR1
        while(PORTBbits.RB0 == 1 && !TMR1IF);                   // Waiting for falling edge
        Time = TMR1;
        TMR1ON = 0;
        
        Distance = ((float)Time / 117.00);                      // Distance = (velocity * time) / 2
        sprintf(total_Distance,"%.03f",Distance);
        LCD_write(total_Distance);
        
        __delay_ms(100);
        LCD_Command(CLEAR);
        
        if(total_Distance < 20){
            LED = _OFF;
        }
    }
}

void Trigger_Pulse_s()
{
    Trigger_Pulse = 1;
    __delay_us(10);
    Trigger_Pulse = 0;
}


