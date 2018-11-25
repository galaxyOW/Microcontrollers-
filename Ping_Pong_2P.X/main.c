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
#include <time.h>

// Including files necessary to run the program

#include "configLCD.h"
#include "config.h"
#include "CCP.h"

// Declaring Global Variables to be used 

int qwe = 1;
int dificultad = 1;
char result[2]; 
int count = 0;
int countTmr = 0;
int r = 0;
unsigned int start;
int scoreP1 = 0;
int scoreP2 = 0;
int begin = 1;
int countDificult = 1;
int i = 1;
int up = 1;
char pScore1[1];
char pScore2[1];
int breakPoint = 0;
int saque = 1;
int BtnPress = 0;
int BtnPress2 = 0;
int reset = 0;
int first = 1;
int timeMs = 500;

// External interrupts used to detect when a button has been pressed

void __interrupt() ISR(void){
    
    if(INT0IF)
    {
        if(dificultad <= 5)
            __delay_ms(20);
        
        INT0IF = 0;
        BtnPress = 1;
        
        // Checks if the player clicked the button in the half court where he/she 
        // shouldn't have. If the button was clicked at this point the game resets 
        // and the other player receives a point. 
        
        if(count >= 5)
        {
            // restarting game 
            TMR1L = 6;
            begin = 1;
            dificultad = 1;
            r = 1;
            scoreP2++;
            breakPoint = 1;
        }
        else                // If button wasn't clicked at a bad time the direction of the ball is reversed. 
            {
                up = 1;
            }
    }
    
    if(INT1IF)
    {
        if(dificultad <= 5)
            __delay_ms(20);
        
        INT1IF = 0;
        BtnPress2 = 1;
        
        // Checks if the player clicked the button in the half court where he/she 
        // shouldn't have. If the button was clicked at this point the game resets 
        // and the other player receives a point.
         
        if(count <= 4)
        {
            TMR1L = 6;
            begin = 1;
            dificultad = 1;
            r = 0;
            scoreP1++;
            breakPoint = 1;
        }
        else
           { 
                up = 0;
            }
    }
    
    // Configuration of TMR1 to increase difficulty every 3 seconds. 
    
    if(TMR1IF)
    {
        TMR1IF = 0;
        countTmr++;
        TMR1L = 6;
        TMR0L = 0;
        
        if(countTmr == 1125)
        { 
            timeMs = timeMs/2;
            countTmr = 0;
            dificultad++;
            sprintf(result,"%d",dificultad);
            LCD_Command(0b00010000);
            LCD_write(result);
            
        }
        
    }
}

// Function to print the games current status. 

void scoreLCD(){
        
        // Variable declared at 40 in order to jump to second line of LCD. 
        
         int x = 40;

        LCD_write("P1: ");
        
        sprintf(pScore1,"%d",scoreP1);
        LCD_write(pScore1);
        
        LCD_write(" | ");
        
        LCD_write("P2: ");
        
        sprintf(pScore2,"%d",scoreP2);
        LCD_write(pScore2);
        
        // Adjusting variable declared in order to jump to the second line. 
        
        x -= 13;
        
        for(int i = 0; i < x+1; i++){
            __delay_ms(20);
            LCD_Command(0b00010100);
        }
        LCD_write("Difficulty: ");
        
        sprintf(result,"%d",dificultad);
        LCD_write(result);
           
}

// Function created to blink LEDs rapidly after someone wins the game. 

void blinkLeds(){
    
    // Since the module used has 4 entry pins, the output pins are controlled by 
    // sending HIGH outputs to the pins, counting in binary. 
    
    for(int j = 0; j < 17; j++){
        __delay_ms(25);
        COUNT1 = 1;
        COUNT2 = 0;
        COUNT3 = 0;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 0;
        COUNT2 = 1;
        COUNT3 = 0;
        COUNT4 = 0;
        
        __delay_ms(25); 
        COUNT1 = 1;
        COUNT2 = 1;
        COUNT3 = 0;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 0;
        COUNT2 = 0;
        COUNT3 = 1;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 1;
        COUNT2 = 0;
        COUNT3 = 1;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 0;
        COUNT2 = 1;
        COUNT3 = 1;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 1;
        COUNT2 = 1;
        COUNT3 = 1;
        COUNT4 = 0;
        
        __delay_ms(25);
        
        COUNT1 = 0;
        COUNT2 = 0;
        COUNT3 = 0;
        COUNT4 = 1;
    }
}


void main()
{
    // Configuring the PIC and LCD to be used. 
    
    configPIC();
    configLCD();

    __delay_ms(20);
    LCD_write("Welcome!");
    __delay_ms(2010);
    
    LCD_Command(CLEAR);

    while(1)
    {
        // Reset conditions
    
        if(reset == 1)
        {
            // Random is enabled so that the starting LED is not always the same. 
            
            ENABLERANDOM = 1;
            __delay_us(17);
            
            // Restarting counts for OUTPUTS.
            
            COUNT1 = 0;
            COUNT2 = 0;
            COUNT3 = 0;
            COUNT4 = 0;
            
            TMR1ON = 0;                         // Resetting TMR1.
            reset = 0;                          // Clearing RESET so that it can be used again.
            
            LCD_Command(CLEAR);
            LCD_write("Restarting Game..");
            
            __delay_ms(1000);
            LCD_Command(CLEAR);
             LCD_write("Welcome!");
             
            __delay_ms(1000);
            LCD_Command(CLEAR);
            
            // Resetting scores and difficulty level. 
            
            scoreP2 = 0;
            scoreP1 = 0;
            dificultad = 1;
            begin = 1;
            first = 1;
        }
        
        
        
        if(first == 1 || qwe == 1)
        {
            qwe = 0;
            RANDOMBIT1 = INPUT;
            RANDOMBIT2 = INPUT;
            RANDOMBIT3 = INPUT;
            RANDOMBIT4 = INPUT;
             
            if(RANDOMBIT1)
                r += 8;
            if(!RANDOMBIT1)
                r += 0;
            if(RANDOMBIT2)
                r += 4;
            if(!RANDOMBIT2)
                r += 0;
            if(RANDOMBIT3)
                r += 2;
            if(!RANDOMBIT3)
                r += 0;
            if(RANDOMBIT4)
                r += 1;
            if(!RANDOMBIT4)
                r += 0;
        
            r = r%2;
        
            RANDOMBIT1 = OUTPUT;
            RANDOMBIT2 = OUTPUT;
            RANDOMBIT3 = OUTPUT;
            RANDOMBIT4 = OUTPUT;
        
            ENABLERANDOM = 0;
        
            first = 0;
        }
        
        // Printing score and difficulty level.
        
        scoreLCD();

        // Choose who starts randomly    
        // Next iteration start with the winner
        // After someone loses, the PIC starts with a random user
            
        if(begin == 1)                              // Starting the game when begin == 1.
        {
            // Reseting TMR1 time every time the game starts over.
            
            TMR1ON = 0;
            
            // Depending on the value of r (it can be 1 or 0) it will start the game 
            // with player 1 or player 2. 
            
            if(r == 0)
            {
                // Setting the interrupt back to 0.
                
                INTCON3bits.INT1IE = 0;
                
                // OUTPUT condition to start the game on player 1 side. 
                
                COUNT1 = 1;
                COUNT2 = 0;
                COUNT3 = 0;
                COUNT4 = 0;
                
                count = 1;

                up = 1;
                i = 1;
                
                // Checking if the reset button wasn't clicked. 
                
                while(BUTTON1 == 0)
                {
                    if(BTNRESET)
                    {
                        reset = 1;
                        break;
                    }
                }
                
            }
            else if(r == 1)
            {
                // Setting the interrupt back to 0.
                
                INTCONbits.INT0IE = 0;
                
                // OUTPUT condition to start the game on player 2 side. 
                
                COUNT1 = 0;
                COUNT2 = 0;
                COUNT3 = 0;
                COUNT4 = 1;
                
                count = 8;

                up = 0;
                i = 8;
                
                // Checking that the reset button wasn't clicked. 
                
                while(BUTTON2 == 0)
                {
                    if(BTNRESET)
                    {
                        reset = 1;
                        break;
                    }
                }
            }
            
            // Turning on interruptions. 
            
            INTCONbits.INT0IE = 1;
            INTCON3bits.INT1IE = 1;
            begin = 0;
            TMR1ON = 1;
            start = i;
            
        }   
     
        // While used to move the LED forward or backwards using the interrupts
   
        while(1)
        {
           
            if(reset == 1)
                break;
            
            if(BTNRESET)
            {
                reset = 1;
                begin = 1;
                break;
            }
                
            if(breakPoint == 1 || i >= 11)
            {
                break;
                i = start;
            }
            
            if(up == 1)
                i++;
            if(up == 0)
                i--;
                        
            if(i == 0)
            {
                scoreP2++;
                dificultad = 1;
                countDificult = 1;
                begin = 1;
                r =  1;
                TMR1L = 6;
                TMR1ON = 0;
                break;
            }
            
            if(i == 1)
            {
                COUNT1 = 1;
                COUNT2 = 0;
                COUNT3 = 0;
                COUNT4 = 0;
                count = 1;
            }
            
            if(i == 2)
            {
                COUNT1 = 0;
                COUNT2 = 1;
                COUNT3 = 0;
                COUNT4 = 0;
                count = 2;
            }
            
            if(i == 3)
            {
                COUNT1 = 1;
                COUNT2 = 1;
                COUNT3 = 0;
                COUNT4 = 0;
                count = 3;
            }
            
            if(i == 4)
            {
                COUNT1 = 0;
                COUNT2 = 0;
                COUNT3 = 1;
                COUNT4 = 0;
                count = 4;
            }
            
            if(i == 5)
            {
                COUNT1 = 1;
                COUNT2 = 0;
                COUNT3 = 1;
                COUNT4 = 0;
                count = 5;
            }
            
            if(i == 6)
            {
                COUNT1 = 0;
                COUNT2 = 1;
                COUNT3 = 1;
                COUNT4 = 0;
                count = 6;
            }
            
            if(i == 7)
            {
                COUNT1 = 1;
                COUNT2 = 1;
                COUNT3 = 1;
                COUNT4 = 0;
                count = 7;
            }
           
            if(i == 8)
            {
                COUNT1 = 0;
                COUNT2 = 0;
                COUNT3 = 0;
                COUNT4 = 1;
                count = 8;
            }
            
            if(i == 9)
            {
                COUNT1 = 1;
                COUNT2 = 0;
                COUNT3 = 0;
                COUNT4 = 1;
                count = 9;
            }
            
            if(i == 10)
            {
                scoreP1++;
                dificultad = 1;
                countDificult = 1;
                begin = 1;
                r = 0;
                TMR1L = 6;
                TMR1ON = 0;
                break;
            }

            delay_ms(timeMs);
        }
 
        timeMs = 500;
        breakPoint = 0;
        LCD_Command(CLEAR);
        
        // Check every time a point is made if someone wins
        // Once the points of a player reaches 5, the player wins.

        if(scoreP1 >= 5)
        {
            TMR1ON = 0;
            scoreLCD();
            __delay_ms(250);
            
            scoreP1 = 0;
            scoreP2 = 0;
            
            dificultad = 1;
            countDificult = 1;
            r = rand()% 2;
            
            begin = 1;
            LCD_Command(CLEAR);
            LCD_write("Player 1 Wins!");
            __delay_ms(4000);
            blinkLeds();
        }
        else if(scoreP2 >= 5)
        {
            TMR1ON = 0;
            scoreLCD();
            __delay_ms(250);
            
            scoreP1 = 0;
            scoreP2 = 0;
            
            dificultad = 1;
            countDificult = 1;
            r = rand()% 2;
            
            begin = 1;
            LCD_Command(CLEAR);
            LCD_write("Player 2 Wins!");
            __delay_ms(4000);
            blinkLeds();
            
        }
        
        LCD_Command(CLEAR);
    }
    
}