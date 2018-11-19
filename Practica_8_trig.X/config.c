#include "config.h"


void configPIC(void){
    
    TRISA = OUTPUT;
    TRISB = OUTPUT;
    TRISC = OUTPUT;
    TRISD = OUTPUT;
    TRISE = OUTPUT;
        
    LED_TRIS = OUTPUT;
    
    // Activating Interruptions 
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    INTCONbits.INT0IE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2IE = 0;
   
    ADCON1 = 0b00001111;
       
    T0CONbits.T0CS = 0;                                     //0 = temporizador
    T0CONbits.TMR0ON = 0;        
    
}

void initADC(){
    TRISAbits.RA0 = 1;                                      // Puerto A como entrada
    ADCON1 = 0b00001101;                                    //TODOS LOS PUERTOS ANALÓGICOS PONIENDO TODO EL PUERTO EN 0
    ADCON0 = 0;                                             //ADCON --> Escoge las fuentes de voltaje
    ADCON2 = 0b10100110; 
}

unsigned int ADC_read(unsigned char x){
    if (x > 13) return 0;
    
    ADCON0bits.ADON = 1; 
    ADCON0bits.CHS = x ;
    
    while(1)
    {
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE == 1);                     //mientras que se este convirtiend
        ADCON0bits.ADON = 0;                                //YA QUE SE HAYA CONVERTIDO 
        return ADRES; 
    } 
}





