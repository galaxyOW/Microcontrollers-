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

// Declaring global variables that will be used throughout the program

unsigned long first_record,second_record, third_record;
float first_record_float,second_record_float, signal_period;
unsigned int frequency_array[20];              
char Duty_Cycle_array[20];
float Frequency, Duty_Cycle;
int length_freg, length_dc;
int x;
unsigned long count;

// Global interrupt used to count when an overflow of data has occured in the register

void __interrupt() isr(void){
    if(TMR1IF == 1){
        count++;
        TMR1IF = 0;
    }
}

// Since the TMR1 register uses 16 bits, it will overflow every 65536 + 1. 
// Reads frequencies between 192 Hz and 30kHz properly. Begins to fluctuate values on the LCD when outside the given range. 

void main()
{
    
    // Initializing PIC and LCD, and configuring CCP register. 
    
    configPIC();
    configCCP();
    configLCD();
    
    // Setting up bits for the CCP1CON register. 
    
    CCPR1 = 0;
    TMR1ON = 1;
    TMR1 = 0;
    count = 0;
    
    
    while(1)        
    {   
        // Waiting is displayed when there is no frequency
        
        __delay_ms(20);
        LCD_write("Waiting . . .");
    
        LCD_Command(CLEAR);
        
        // Configuring the register to read rising edges 
        
        CCP1CONbits.CCP1M=0b0101;
         while(!CCP1IF);                                    // Waiting for the flag in order to capture the data                    
        first_record = CCPR1 + (count*65537);               // Capturing value in the TMR1 register. 
        PIR1bits.CCP1IF = 0;                                // Reseting the flag to be able to read future values. 
        
        // Configuring the register to read falling edges
        
        CCP1CONbits.CCP1M=0b0100;
        while(!CCP1IF);
        CCP1IF=0;
        third_record = CCPR1 + (count*65537);
        
        // Configuring the register to read rising edges
        
         CCP1CONbits.CCP1M=0b0101;
        while(!CCP1IF);
        second_record = CCPR1 + (count*65537);
        PIR1bits.CCP1IF = 0;
       
        // IF used to ensure that the second time recorded is greater than the first
        
        if(second_record > first_record)
        {
            // X declared as count variable to push the LCD's cursor to the second row. 
            
            x = 40;
           
            // Calculating Frequency and Duty Cycle
            
            signal_period = (second_record - first_record);
            Frequency = (12000000 / signal_period);                 
            Duty_Cycle = ((third_record - first_record) / signal_period) * 100;
            
            // Converting the integer values to strings and storing the values in the array
            
            sprintf(frequency_array,"%f",Frequency);
            sprintf(Duty_Cycle_array,"%f",Duty_Cycle); 
            
            // Calculating the length of the strings in order to push the values to the second row 
            
            length_freg = strlen(frequency_array);
            length_dc = strlen(Duty_Cycle_array);
            x -= length_freg;
            x -= 2;
            
            // Printing the values calculated
            
            __delay_ms(200);
            LCD_write("F:");
            
            __delay_ms(20);

             LCD_write(frequency_array);
    
            for(int i = 0; i < x;i++)
            {              
                __delay_ms(33);
                LCD_Command(0b00010100);   
            }
            
            x = 37;
            x-= length_dc;
            
            __delay_ms(20);
            LCD_write("DC:");
            
            __delay_ms(20);
            LCD_write(Duty_Cycle_array);
            
            for(int i = 0; i < x;i++)
            {              
                __delay_ms(10);
                LCD_Command(0b00010100);   
            }
        
          
            // Reset the process by using MEMSET to clear data in the array and clear captured values in the TMR1 register.
        
            memset(frequency_array,0,20);
            memset(Duty_Cycle_array,0,20);
            count = 0;
            TMR1 = 0;
            CCPR1L = 0;
            CCPR1H = 0;
        }
    }
}


