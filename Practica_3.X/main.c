#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

#include "config.h"

void __interrupt() a_practica(void){
    
    // --------------------- PART A ------------------------------------------
    // INT0 being checked to see if the button is being pressed, if so the LED will be turned ON. 
    
    if (INT0IF == 1){
        INT0IF = 0;             // Reseting state of pin. 
        LED = _ON;
    }
    
    // --------------------- PART B ------------------------------------------
    // INT1 being checked to see if the button was pressed, if so the LED will change its current state. 
    
    if(INT1IF == 1){
        INT1IF = 0;             // Reseting state of pin.
        
        // IF statements used to change the LED's current state.
        
        if(LED == _OFF){
            LED = _ON;  
        }
        else if(LED == _ON){
            LED = _OFF;
        }
    }
    
    // --------------------- PART C ------------------------------------------
    // INT2 will wait 10 seconds before allowing any interruptions to be read. 
    
    if(INT2IF == 1){
        INT2IF = 0;             // Reseting state of pin.
        if(count == 100000){    // Checks that the count has reached 10 seconds before allowing it to proceed.
            count = 0;
            
            // IF statements used to change the LED's current state.
            
            if(LED == _OFF){
                LED = _ON;  
            }
            else if(LED == _ON){
                 LED = _OFF;
            }
        }
       
    }
    
}
void main(void) {
    
    // Calling function that will allow the user to use the PIC.
    
    configPIC();
    
    // Initializing LED's state as OFF.
    LED = _OFF;
    
    /* 
     The interrupt does not need to be called in the main since the PIC has an 
     internal interrupt system that will automatically detect when an event has 
     occurred at a certain interrupt pin. 
     */
    
    //While loop used to keep the process ongoing and thus the PIC will wait for more interrupts. 
    
    while(1){}
    return;
}

