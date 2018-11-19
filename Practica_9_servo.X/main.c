#pragma config FOSC=INTOSC_EC
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
#pragma config FOSC=INTOSC_EC
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

#include "config.h"
#include <string.h>
#include <stdio.h>

// Two buttons are used to move the servo motor to 180 using 6 movements. 
// One button is used to move the blade forward while the other is used to move the blade backwards. 

void initLCD();
unsigned char BusyLCD();
void writeCommand(unsigned char);                          //unsigned char byte value (0-255)
void writeData(unsigned char);


unsigned char Presc=16;
int PWMFrec=50; 
int Period = 20;                                             //20ms 
long Fosc=500000;                                            //In this case we will use an internal clock of 500KHz with PR2 = 194 and using 40 Hz.

unsigned char calculatePR2() {
	unsigned char _PR2;
	_PR2 = ((Fosc / (4 * Presc*PWMFrec))) - 1;
	return _PR2;                                             //We save and return the value of PR2.
}
unsigned int calculateReg(float Ton){
	unsigned int Reg;                                       //10 bit value
    float DC = (Ton/Period);
    Reg=(calculatePR2()+1)*(4)*(DC);                        //Once we have the DC we solve for REG. 
	return Reg; //10 bits
}

void main(void) {
   
    float Ton1=0.9f; 
    float Ton2=1.2f; 
    float Ton3=1.5f; 
    float Ton4=1.7f; 
    float Ton5=2.0f;
    float Ton6=2.4f;
    
    configPIC();
    
    unsigned char Timer2Config=2;                           //16 Pre-scaler 1 0
    
    //Move to 0° Ton = 0.9
    
    OpenTimer2(Timer2Config);
    OpenPWM1(calculatePR2()); 
    
    int counter;
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA5=1;
    int position=1;
    
    while (1){
        
        // DECREASING 
        
        if(PORTAbits.RA0==1 && position>1){     
            if(position==2){
                SetDCPWM1(calculateReg(Ton1)); 
                __delay_ms(50);
            }
            if (position==3){
                SetDCPWM1(calculateReg(Ton2));
                __delay_ms(50);
            }
            
             if(position==4){
                SetDCPWM1(calculateReg(Ton3)); 
                __delay_ms(50);
            }
            
            if(position==5){
                SetDCPWM1(calculateReg(Ton4)); 
                __delay_ms(50);
            }
            
            if(position==6){
                SetDCPWM1(calculateReg(Ton5)); 
                __delay_ms(50);
            }
            position=position-1;
        }
        
        // INCREASING 
        
        if(PORTAbits.RA5==1 && position<6){
            if(position==5){
                SetDCPWM1(calculateReg(Ton6));
                __delay_ms(50);
            }
            
            if(position==4){
                SetDCPWM1(calculateReg(Ton5));
                __delay_ms(50);
            }
            
            if(position==3){
                SetDCPWM1(calculateReg(Ton4));
                __delay_ms(50);
            }
           
            if(position==2){
                SetDCPWM1(calculateReg(Ton3));
                __delay_ms(50);
            }
            if (position==1){
                SetDCPWM1(calculateReg(Ton2));
                __delay_ms(50);
            }
            position=position+1;
        } 
     
    }
            
}
