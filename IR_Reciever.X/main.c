#pragma config PLLDIV = 1                   // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2           // System Clock Postscaler Selection bits ([Primary Oscillator Src: /2][96 MHz PLL Src: /3])
#pragma config FOSC = HSPLL_HS              // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF                  // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF                    // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON                   // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF                    // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF                    // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF                    // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// Including files and libraries necessary 

#include <xc.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "LCD_function.h"

// Defining global variables

unsigned int period = 0;                // Variable that stores time given by TMR3.
unsigned int time[64]={0};               // Variable that allows us to store the times in an array.
unsigned int count = 1;                 // Count to check that 31 bits have been sent to the TSOP.

void __interrupt() ISR() { 
    
    // Defining variables to be used for the interrupt.
    
    unsigned int true_value[64]={0};      // Array to store sorted values from time array. 
    
    // counts are used to double check that both array values are the same.
    
    unsigned int count_forward = 0;
    unsigned int count_right = 0;
    unsigned int count_down = 0;
    unsigned int count_left = 0;
    unsigned int count_menu = 0;
    unsigned int count_play = 0;

    // Defining the arrays that store the binary values that the signal should give. 
    
    unsigned int forward[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0};
    unsigned int right[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0};
    unsigned int down[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0};
    unsigned int left[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0};
    unsigned int menu[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0};
    unsigned int play[] = {0,9,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,1,0,0,0,0};
     
    if (INT0IF==1){                        // Checks if the Interrupt Flag (IF) was raised.
        
        TMR3ON = _ON;                      // Turns on TMR to start counting.
        period = TMR3;                     // Assigns TMR3 value to period.
        
        if (TMR3!=0)
        {                                  // The TMR must always be at 0 in order to time new values
            TMR3=0;
        }
        
        if (count!=0)                      // Checking the count 
        {
            time[count] = period;           // Key stores the TMR value in certain position in the array. 
        }
        
        count++;                           // Increasing count so that we can add and keep track of how many bits are being read. 
        
        
        // If we reached 31 bits then we can start analysing the values inside the time array. 
        
        if (count == 31)
        {
            count = 0;                                            // Setting count to 0 in order to receive new signals.
            
            Clear_Display();
            
            // FOR used to check each value in the time array and save it in a new array called SORTED. 
            // The check is used to sort each value as either 9, 0 or 1 depending on the time it took the PIC to receive the value. 
            // The calculated values for sort are subjected to variation due to errors when receiving the signal. 
            // Due to this variation a range is placed in order to be able to identify the signal if it comes with a small error. 

            for(unsigned int i = 0; i < 32; i++)
            {
                if ((time[i]>20200) && (time[i]<20300))               // Calculated value = 13500
                {
                    true_value[i]=9;
                }
                if ((time[i]>3300) && (time[i]<3400))                 // Calculated value = 1680
                {
                    true_value[i]=1;
                
                }
                if ((time[i]>1650) && (time[i]<1700))                 // Calculated value = 3375
                {
                    true_value[i]=0;
                }

            }
            
            // IF used to check if the values stored in the SORTED array match any of the saved values for 
            // control options.

            if (true_value[0] == 0)                                 // Checking that the first two values coincide. 
            {                
                for (unsigned int j = 18; j < 21; j++)
                { 
                    
                    if (forward[j] == true_value[j])
                    {   
                        count_forward++;
                        __delay_ms(20);
                    }
                    if(right[j] == true_value[j]){
                        count_right++;
                        __delay_ms(20);
                    }
                    if (down[j] == true_value[j])
                    {   
                        count_down++;
                        __delay_ms(20);
                    }
                    if(left[j] == true_value[j]){
                        count_left++;
                        __delay_ms(20);
                    }    
                    if(menu[j] == true_value[j]){
                        count_menu++;
                        __delay_ms(20);
                    }
                    if(play[j] == true_value[j]){
                        count_play++;
                        __delay_ms(20);
                    }
                }
            } else
                {                                                   // If the comparison fails an error message is given.
                    Clear_Display();
                    print_in_LCD ("Try Again!");
                    __delay_ms(2000);
                }
 
            // IF is used to check if 3 bits in the SORTED array are correct and carries out the functions 
            // inside the IF. 
            
            // Depending on the values read a message should be displayed on the LCD. If the word printed is
            // FORWARD, RIGHT, BACKWARDS, LEFT, MENU or PLAY then you have successfully read and compared the values. 
            
            if (count_forward == 3)
            {
                Clear_Display ();
                print_in_LCD("Forward");                              

            }
                else if(count_right == 3){
                Clear_Display ();
                print_in_LCD("Right");
            }
                else if (count_down == 3)
            {
                Clear_Display ();
                print_in_LCD("Backwards");                              

            }
                else if(count_left == 3){
                Clear_Display ();
                print_in_LCD("Left");
            }
                else if (count_menu == 3)
            {
                Clear_Display ();
                print_in_LCD("Menu");                                   

            }
                else if(count_play == 3){
                Clear_Display ();
                print_in_LCD("Play");
            }
            else{print_in_LCD("Error");}
            __delay_ms(100);
        }    
        INT0IF=0;                                                       // Resetting the interruption flag 
        memset(true_value, 0, sizeof(true_value));                      // Resetting the array value
    }
}
void main (){
    
    // Initialising PIC and LCD.
    
    configPic ();
    iniLCD();
    
    __delay_ms(100);
    
    // Activating the interrupts for the pin INT0.
    
    INTCONbits.INT0IE = 1;                  
    
    while (1);                                                          // While is kept empty in order to wait for the interruption. 
}




