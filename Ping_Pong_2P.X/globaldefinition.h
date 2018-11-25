#ifndef GLOBALDEFINITIONS_H
#define	GLOBALDEFINITIONS_H

// Defining simple definitions for signals. 

#define _ON 1                
#define _OFF 0                  
#define INPUT 1
#define OUTPUT 0
#define BAJO 0



// Defining inputs and outputs needed for LCD initialization. 

#define READ 1
#define WRITE 0
#define DATA 1
#define COMMAND 0
#define HABILITADO 1
#define DESHABILITADO 0

// Clear is defined in binary to clean the display

#define CLEAR 0b00000001    
#define HOME 0b00000010
// Pins are defined using PORT in order to put LOW signals. 

#define RS PORTBbits.RB4       
#define RW PORTBbits.RB2       
#define EN PORTBbits.RB3 

// Pins are defined as TRIS in order to use them as outputs. 

#define RS_TRIS TRISBbits.RB4   
#define RW_TRIS TRISBbits.RB2
#define EN_TRIS TRISBbits.RB3

// LDATA is used to define which variables will go into the port D. 

#define ldata LATD       

// Defined function in order to use delays. 

#define _XTAL_FREQ 48000000   

//Leds for Ping Pong

#define COUNTTRIS1 TRISAbits.TRISA0
#define COUNT1 LATAbits.LA0

#define COUNTTRIS2 TRISAbits.RA1
#define COUNT2 LATAbits.LA1

#define COUNTTRIS3 TRISEbits.RE2
#define COUNT3 LATEbits.LE2

#define COUNTTRIS4 TRISAbits.RA3
#define COUNT4 LATAbits.LA3

//Raquets

#define BUTTONTRIS1 TRISBbits.RB0                   
#define BUTTON1 PORTBbits.RB0
                                                    //BOTONES DE RAQUETA
#define BUTTONTRIS2 TRISBbits.RB1
#define BUTTON2 PORTBbits.RB1   
                                                 
#define BUTTONTRIS3 TRISCbits.RC2            //reset button
#define BTNRESET PORTCbits.RC2



#define RANDOMTRIS1 TRISCbits.RC5
#define RANDOMBIT1 PORTCbits.RC5

#define RANDOMTRIS2 TRISCbits.RC4
#define RANDOMBIT2 PORTCbits.RC4

#define RANDOMTRIS3 TRISCbits.RC0
#define RANDOMBIT3 PORTCbits.RC0

#define RANDOMTRIS4 TRISCbits.RC1 
#define RANDOMBIT4 PORTCbits.RC1

#define ENABLETRIS TRISEbits.RE1
#define ENABLERANDOM PORTEbits.RE1

#endif	

