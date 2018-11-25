#include "config.h"

void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    LED_TRIS = OUTPUT;   
    LEFTIR_TRIS = INPUT;
    RIGHTIR_TRIS = INPUT;
    CENTRALIR_TRIS = INPUT;

    RMOT1_TRIS = OUTPUT;
    RMOT2_TRIS = OUTPUT;
    LMOT1_TRIS = OUTPUT;
    LMOT2_TRIS = OUTPUT;

    T3CONbits.RD16=1;

    ECHOTRIS = INPUT;
    TRIGTRIS = OUTPUT;
    
    // Deactivating TMR3 for the CCP1 and CCP2 modules
    
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 0;
    
    // Assigning pre-scaler value for the TMR3. 
    
    T3CONbits.T3CKPS =0b11;

    // Choosing signal source for the TMR3.
    
    T3CONbits.TMR3CS=0;
    
    TMR3ON = _OFF;                      // TMR3 natural state is off. This means the TMR is not counting.
    TMR3L = 0;
    TMR3H = 0;
    TMR3IF = 0;

    INTCONbits.GIE = 0;                 // Turning on global interruptions.
    INTCONbits.PEIE = 0;
    INTCONbits.INT0IE = 0;              // Deactivating external interruptions for INT0.
    INTCON2bits.INTEDG0 = 0;            // Interrupt is activated for falling edges. 
    INTCONbits.INT0IF =0;               // Starting with the flag at 0.
   
    ADCON1 = 0b00001111;
    
    
}

void timer1config(void){  
    // Configuring TMR1 registers
    
    T1CONbits.RD16 = 1;
    T1RUN = 0;                          //Using internal clock
    TMR1CS = 0b00;                      // (FOSC / 4)
    T1CKPS0 = 0;
    T1CKPS1= 0;
    T1OSCEN = 0;
    TMR1 = 0;
    TMR1IF = 0;
}

void _REVERSE(){                       // Function to make the car reverse.
    RMOT1 = 0;
    RMOT2 = 1;
    LMOT1 = 1;
    LMOT2 = 0;
    
}

void _FORWARD(){                       // Function to make the car advance.    
    RMOT1 = 1;
    RMOT2 = 0;
    LMOT1 = 0;
    LMOT2 = 1;
            
}

void _LEFT(){                          // Function to make the car turn left. 
    RMOT1 = 1;
    RMOT2 = 0;  
    LMOT1 = 0;  
    LMOT2 = 0;  
}

void _RIGHT(){                         // Function to make the car turn right.
    RMOT1 = 0;  
    RMOT2 = 0;  
    LMOT1 = 0;  
    LMOT2 = 1;
}

void _STOP(){                          // Function to make the car stop.  
    RMOT1 = 0;
    RMOT2 = 0;
    LMOT1 = 0;
    LMOT2 = 0;           
}

void line_follow()
{

    LED = _ON;
    
    if((LEFTIR == 0) && (RIGHTIR == 0) && (CENTRALIR == 1))                     // If the central IR detects black.
    { 
         _FORWARD();
    }
    
    if((LEFTIR == 1) && (RIGHTIR == 0) && (CENTRALIR == 0))                     // If the left IR detects black.
    { 
        _LEFT();
    }
    
    if((LEFTIR == 1) && (RIGHTIR == 0) && (CENTRALIR == 1))                     // If the left and central IRs detect black.
    { 
        RMOT1 = 0;
        RMOT2 = 1;
        LMOT1 = 0;
        LMOT2 = 1;
    }
    
    if((LEFTIR == 0) && (RIGHTIR == 1) && (CENTRALIR == 0))                     // If the right IR detects black. 
    {            
        _RIGHT();
     }
    
    if((LEFTIR == 0) && (RIGHTIR == 1) && (CENTRALIR == 1))                     // If the right and central IR detects black.
    {       
        RMOT1 = 1;
        RMOT2 = 0;
        LMOT1 = 1;
        LMOT2 = 0;        
     }    
}

void Trigger_Pulse_s()          // Function used to send pulses from the ultrasonic sensor. 
{
        TRIG = 1;
        __delay_us(10);
        TRIG = 0;
}

void Config_Ultrasonic(){       // Function used to configure the ultrasonic sensor and the TMR1 register to be used.
   
    TRISBbits.RB0 = INPUT;
    INTCON2bits.RBPU = 0;                                       // Enables PORTB pull-ups
    Trigger_Pulse = 0;
    
    // Enabling 16-bit TMR1 Register, no pre-scaler, internal clock, timer OFF
    T1CON = 0x80;                                               // 10000000
    TMR1IF = 0;                                                 // Make TMR1 overflow flat 0
    TMR1 = 0;
}

float Detect_object(){          // Function used to calculate the distance and send it when the function is called.
    
    // Defining variables to be used inside of the function.
    
    float Distance;
    int Time;
        
    Trigger_Pulse_s();
    while(PORTBbits.RB0 == 0);                              // Wait for rising edge at ECHO pin       
    TMR1 = 0;                                               // Start TMR1 at 0;

    TMR1ON = 1;                                             // Turning on TMR1
    while(PORTBbits.RB0 == 1 && !TMR1IF);                   // Waiting for falling edge
    Time = TMR1;
    TMR1ON = 0;
        
    Distance = ((float)Time / 117.00);   
    return Distance;
}

void Avoid_object(){            // Function used to create a routine to avoid objects. 
    
    _STOP();
    __delay_ms(500);
    
    _RIGHT();
    __delay_ms(100);
    
    _FORWARD();
    __delay_ms(300);
    
    _LEFT();
    __delay_ms(200);
    
    _FORWARD();
    
    while(CENTRALIR);           // While is placed so that the car will move forward until it finds the black line.     
    
}

void OpenTimer2(){
    
    // Configuring T2CON to have a pre-scaler value of 16 and turning the timer on
    T2CON = 0b00000111;
}

void OpenPWM1(unsigned char PR2Value){
    
    // Configuring CCP1CON to generate PWM signals
    CCP1CON = 0x0C;
    
    // Configuring CCP1 as output
    TRISCbits.RC2 = OUTPUT;
    
    // Stopping the TIMER2 
    TMR2 = _OFF;
    
    // Loading the PWM signals frequency using the register. 
    PR2 = PR2Value;
    
    // Starting the TMR2
    TMR2ON = _ON;
}

void SetDCPWM1(float DC){
    // Loading the PWMs duty cycle into the registers
    CCPR1L = DC;
}

void SetDCPWM2(unsigned int DC2){
    // Loading the PWMs duty cycle into the registers
    
    CCPR1L = (DC2 >> 2);
    DC1B1 = (DC & 0x0002) ? 1:0;
    DC1B0 = (DC & 0x0001) ? 1:0;
}


