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

#include "Function_serial_communication.h"
#include "config.h"
#include "LCD.h"
#include <string.h>  


unsigned int w = 0;
char string_reciver[16];

// Interrupt function created to detect when an event has occurred. 
// The interrupt is detected automatically. 

__interrupt()void RX_CHAR() { 
    
    char msg;
    
    if (RCIF==1){
    
        msg=RCREG;
        
        // If the counter's position is 0, the position 0 is the end of the string. 
        
        if (w == 0){ 
            for (unsigned int i=0; i<16; i++){
                string_reciver[i] = '\0';
            }
        }

        // Condition in order to not have a chain of more than 16 characters. 
        
        if (w < 16){  
       
            string_reciver[w] = msg;
            w++;
        }
     
         // Condition in order to return to the string's first position (0).    
        
        if(msg == '\0'){   
            w = 0;
        }      

        // Overrun error overwrites de data in the receptor. It reads slower than it writes.     
        
        if(RCSTAbits.OERR) 
        {        
            print_in_LCD("ERROR");
            CREN = 0;
        }
        
        // Error printed if the protocols don't coincide. 
        
        if(RCSTAbits.FERR) 
        {    
            print_in_LCD("ERROR");
            CREN = 0; 
        }
  
        RCIF=0;
    }        
}
    

void main (void){
     
    // Declaring variables that will be used during the program. 
    
    char string [16];
    int a;
    int b;
    
    // Initializing the PIC, LCD and USART so that they can be used. 
    
    configPIC();
    USART_ini();
    __delay_ms(50);
    iniLCD ();
    __delay_ms(10);
  
    // Starting the program off with the LED off. 
    
    LED=_OFF;

    while (1){
       
       // Waits until the button has been pressed before continuing. 
        
       while (BOTON == 0);
       __delay_ms(200);
       
      // IF statements used to check if LED is on or off to determine what characters to send. 
      // The RX will receive either OFF or ON from the TX pin. 
       
      if (LED==_ON){
          Send_String_TX ("OFF");
      }
      if (LED==_OFF){
          Send_String_TX ("ON");
      }
       
       // The LCD will display whatever was received from the TX. 
       
       __delay_ms(500);
       print_in_LCD(string_reciver);
       
       // This cleans the array in order to be able to receive new data. 
       
       w = 0;                                      
       
       // Compares strings sent with the values that are expected, the function returns 0 if the arguments are coherent. 
       
       a = strncmp(string_reciver,"ON",16);        
       b = strncmp(string_reciver,"OFF",16);        
       
       // If the strings are coherent then the LED will either turn ON or OFF.
       
       if(a == 0)
       {
           LED=_ON;
       }
       
       if(b == 0){
           LED=_OFF;
       }
    
       
    }
}

















//}

