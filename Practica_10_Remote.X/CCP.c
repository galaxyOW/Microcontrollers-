#include <pic18f4550.h>

#include "config.h"
#include "configLCD.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

void OpenTimer2(){
    
    // Configuring T2CON to have a pre-scaler value of 16 and turning the timer on
    T2CON = 0b00000101;
}

void OpenPWM1(unsigned int PR2Value){
    
    // Configuring CCP1CON to generate PWM signals
    CCP1CON = 0x0C;
    
    // Configuring CCP1 as output
    TRISCbits.RC2 = OUTPUT;
    
    // Stopping the TIMER2 
    TMR2 = _OFF;
    
    // Loading the PWM signals frequency using the register. 
    PR2 = PR2Value;
    
    // Starting the TMR2
    T2CONbits.TMR2ON = _ON;
}

void SetDCPWM1(float DC){
    // Loading the PWMs duty cycle into the registers
    CCPR1L = DC;
}

void SetDCPWM2(unsigned int DC2){
     CCPR1L = (DC2 >> 2);
     DC1B1 = (DC & 0x0002) ? 1:0;
     DC1B0 = (DC & 0x0001) ? 1:0;
}

void sendCode(const char *x){
    int i = 0;
    LCD_write("OK ");
    __delay_ms(20);
    //9ms de inicio
    OpenPWM1(79);
    SetDCPWM1(39.5);
    __delay_ms(9);
    //4.5 ms de pausa
    SetDCPWM1(0);
    __delay_us(4500);
    //empieza a iterar 
    while(i < 32){
        CCP1CONbits.CCP1M = 1100;
        
        if(x[i] == 1){
            
            //pulso
            SetDCPWM1(39.5);
            __delay_us(560);
            //pausa
            SetDCPWM1(0);
            __delay_ms(1);
            __delay_us(690);
            
        }
  
        
        if(x[i] == 0){
            
            //pulso
            SetDCPWM1(39.5);
            __delay_us(560);
            //pausa
            SetDCPWM1(0);
            __delay_us(590);
            
        }
        i++;
    }
    
    SetDCPWM1(39.5);
    __delay_us(560);
    SetDCPWM1(0);
    LCD_write("...");
    __delay_ms(2000);
    LCD_Command(CLEAR);
}

void SEND0(){
    CCP1CON = 0x0C;
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    
    CCP1CON = 0;
    __delay_us(560);
}

void SEND1(){
    CCP1CON = 0x0C;
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    
    CCP1CON = 0;
    __delay_ms(1);
    __delay_us(690);
}

void UP_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

void LEFT_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND0();    
    SEND0();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

void RIGHT_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();    
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();        
    SEND0();        
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

void CENTRAL_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

void DOWN_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();            
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

void MENU_BTN(){
    CCP1CON = 0x0C;
    
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_ms(9);
    
    CCP1CON = 0;
    __delay_ms(4);
    __delay_us(500);
    
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();            
    SEND0();        
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND0();
    SEND0();
    SEND0();
    SEND1();
    SEND1();
    SEND0();
    SEND1();

    
    
    //bit de parada
    OpenPWM1(79);
    SetDCPWM1(37.5);
    __delay_us(560);
    CCP1CON = 0;

}

