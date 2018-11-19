#ifndef GLOBALDEFINITIONS_H
#define	GLOBALDEFINITIONS_H

// Defining simple definitions for signals. 

#define _ON 1                
#define _OFF 0                  
#define INPUT 1
#define OUTPUT 0
#define BAJO 0

#define LED PORTAbits.RA0
#define LED_TRIS TRISAbits.RA0 

// Defining inputs and outputs needed for LCD initialization. 

#define READ 1
#define WRITE 0
#define DATA 1
#define COMMAND 0
#define HABILITADO 1
#define DESHABILITADO 0

// Clear is defined in binary to clean the display

#define CLEAR 0b00000001    

// Pins are defined using PORT in order to put LOW signals. 

#define RS PORTBbits.RB1       
#define RW PORTBbits.RB2       
#define EN PORTBbits.RB3 

// Pins are defined as TRIS in order to use them as outputs. 

#define RS_TRIS TRISBbits.RB1   
#define RW_TRIS TRISBbits.RB2
#define EN_TRIS TRISBbits.RB3

// LDATA is used to define which variables will go into the port D. 

#define ldata LATD       

// Defined function in order to use delays. 

#define _XTAL_FREQ 8000000   

#define DO_TRIS TRISAbits.RA1 
#define DO2_TRIS TRISAbits.RA2 
#define RE_TRIS TRISAbits.RA3
#define RE2_TRIS TRISAbits.RA4 
#define MI_TRIS TRISAbits.RA5 
#define FA_TRIS TRISEbits.RE0
#define FA2_TRIS TRISEbits.RE1 
#define SOL_TRIS TRISBbits.RB0

#define SOL2_TRIS TRISCbits.RC6
#define LA_TRIS TRISCbits.RC7
#define LA2_TRIS TRISBbits.RB4
#define SI_TRIS TRISBbits.RB5


#define DO PORTAbits.RA1 
#define DO2 PORTAbits.RA2 
#define RE PORTAbits.RA3
#define RE2 PORTAbits.RA4 
#define MI PORTAbits.RA5 
#define FA PORTEbits.RE0
#define FA2 PORTEbits.RE1 
#define SOL PORTBbits.RB0

#define SOL2 PORTCbits.RC6
#define LA PORTCbits.RC7
#define LA2 PORTBbits.RB4
#define SI PORTBbits.RB5


#endif	

