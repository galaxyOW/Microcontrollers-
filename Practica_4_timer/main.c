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
#include "configLCD.h"

/*
 It is important to note that the code for this program has a lot of room for improvement. Because of time, the 
 counter for the timer was done manually.
 */

void main(void) {
    
    // Configuring the PIC and LCD so that they can be used. 
    
    configPIC();                   
    configLCD();                 
    
    // Cleaning the screen. 
    
    LCD_Command(CLEAR);             
    __delay_ms(20);             
    
    // Command needed to use 2 lines. 
    
    LCD_Command(0b00111000);     
    
    // Printing the TIMER on the first row of the LCD.
    // Important to know that LCD-Data can only print one letter at a time. 
    
    __delay_ms(20);                
    LCD_Data('T');               
    __delay_ms(20);
    LCD_Data('I');
    __delay_ms(20);
    LCD_Data('M');
    __delay_ms(20);
    LCD_Data('E');
    __delay_ms(20);
    LCD_Data(' ');
    __delay_ms(20);
    LCD_Data('(');
    __delay_ms(20);
    LCD_Data('S');
    __delay_ms(20);
    LCD_Data('E');
    __delay_ms(20);
    LCD_Data('C');
    __delay_ms(20);
    LCD_Data('.');
    __delay_ms(20);
    LCD_Data(')');
    __delay_ms(20);
    LCD_Data(':');
    
    // Moving the cursor to the second row of the LCD.
    
    for(int i = 0; i < 28; i++){
      __delay_ms(20);
      LCD_Command(0b00010100);
    }
    
    LCD_Command(0b00001110);
    
    // Manually counting up and down. 
    
    while(1){
        
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('1');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('2');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('3');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('4');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('5');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('6');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('7');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('8');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('0');
    __delay_ms(20);
    LCD_Data('9');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1');
    __delay_ms(20);
    LCD_Data('0');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1'); 
    __delay_ms(20);
    LCD_Data('1');
    
       __delay_ms(1000);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1'); 
    __delay_ms(20);
    LCD_Data('2');
    
       __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1'); 
    __delay_ms(20);
    LCD_Data('3');
    
       __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1'); 
    __delay_ms(20);
    LCD_Data('4');
    
       __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    
    __delay_ms(1000);
    LCD_Data('1'); 
    __delay_ms(20);
    LCD_Data('5');
    
    __delay_ms(20);
    LCD_Command(0b00010000);
    __delay_ms(20);
    LCD_Command(0b00010000);
    }
}

