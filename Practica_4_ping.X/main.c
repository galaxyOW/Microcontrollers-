#pragma config PLLDIV = 5               // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2       // System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config FOSC = HSPLL_HS          // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF              // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config WDT = OFF                // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF                // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF                // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF                // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)


#include "config.h"
#include "configLCD.h"
#include "GlobalDefinitions.h"

void main(void) {
    
    // Configuring the PIC and the LCD so that they can be used. 
    
    configPIC();                   
    configLCD();                   
    
    // Cleaning the screen with the CLEAR command. 
    
    LCD_Command(CLEAR);            
    __delay_ms(10);
    
    // Deactivating the cursor and blink, setting the LCD to use 2 lines.  
    
    LCD_Command(0b00001100);         
    __delay_ms(10);
    LCD_Command(0b00111000);            // Command for 2 lines. 
    
    int count = 0;
    int counts = 0;
    
    // FOR is used to push the cursor down to the second row. 
    
    for(int i = 0; i < 40;i++){              
        __delay_ms(10);
        LCD_Command(0b00010100);   
    }
    
    //Printing PING on the second row. 
        
    __delay_ms(10);                            
    LCD_Data('P');
    __delay_ms(10);
    LCD_Data('I');
    __delay_ms(10);
    LCD_Data('N');
    __delay_ms(10);
    LCD_Data('G');
    
    // FOR is used to return the cursor to the start of the first row. 
    
    for(int x = 0; x < 44;x++){               
        __delay_ms(10);
        LCD_Command(0b00010000);   
    }
    
    // Printing the first ball. It will be placed in the first position of the first row. 
    
    __delay_ms(10);                  
    LCD_Data('o');
    
//-------------------------------- MOVING PING-PONG BALL FORWARD ----------------------------
    
    
    // While loop will allow the ping-pong ball to move back and forward.
    
    while(1){
        
        // FOR used to move the ball 15 spaces across the first row.
        
        for(int i = 0;i < 15;i++){         
            
            // We move back one position to delete the ball using a space. 
            
            __delay_ms(100);                  
            LCD_Command(0b00010000);
            __delay_ms(10);
            LCD_Data(' ');               
            
            // Moves one space less than the original FOR in order to move the cursor 2 spaces forward.
            
            for(int z = 0;z < i-count; z++){    
                 __delay_ms(10);
                LCD_Command(0b00010100);
            }
            
            // Printing the ping-pong ball forward. 
            
            __delay_ms(10);        
            LCD_Data('o');
            __delay_ms(100);

            count++;                     
 
        }
//-------------------------------- MOVING PING-PONG BALL BACKWARDS  ------------------------------------
        
        // Reseting variables. 
        
        __delay_ms(10);
        LCD_Command(0b00000001);
        count = 0;
        
        // FOR used to move the cursor down to the second row. 
        
        for(int i = 0; i < 40;i++){             
                __delay_ms(10);
                LCD_Command(0b00010100);   
        }
        
        // Printing PONG on the second row. 
        
        __delay_ms(10);                           
        LCD_Data('P');
        __delay_ms(10);
        LCD_Data('O');
        __delay_ms(10);
        LCD_Data('N');
        __delay_ms(10);
        LCD_Data('G');
        
        // FOR used to move the cursor to the ending of the first row. 
        
        for(int x = 0; x < 29;x++){                
                __delay_ms(10);
                LCD_Command(0b00010000);   
        }
        
        // Printing the first ball going back. 
        
        __delay_ms(10);                    
        LCD_Data('o');
        
        // FOR used to move the ball back 15 spaces. 
        
        for(int t = 0;t < 16;t++){           
            
            //Moving the cursor back a space in order to delete the ball by replacing it with a space. 
            
            __delay_ms(200);                   
            LCD_Command(0b00010000);
            __delay_ms(10);
            LCD_Data(' ');                     
            
            // Moving the cursor two spaces forward. 
            
            __delay_ms(10);
            LCD_Command(0b00010000);
            __delay_ms(10);
            LCD_Command(0b00010000);
            
            // Printing the ping-pong ball moving backwards. 
            
            __delay_ms(10);                 
            LCD_Data('o');
            
            counts++;                            
 
        }
//------------------------------------------------- REPEATING FIRST PROCESS -------------------------------------------------    
        
        __delay_ms(10);
        LCD_Command(CLEAR);
        
        // Moving the cursor down to the second row. 
        
        for(int i = 0; i < 40;i++){             
            __delay_ms(10);
            LCD_Command(0b00010100);   
        }
        
        // Printing the word PING on the second row. 
        
        __delay_ms(10);                             
        LCD_Data('P');
        __delay_ms(10);
        LCD_Data('I');
        __delay_ms(10);
        LCD_Data('N');
        __delay_ms(10);
        LCD_Data('G');
        
        // FOR used to return the cursor to the start of the first row. 
        
        for(int x = 0; x < 44;x++){                
            __delay_ms(10);
            LCD_Command(0b00010000);   
        }
        
        // Printing first ping-pong ball. 
        
        __delay_ms(10);                   
        LCD_Data('o');

        }

    }






