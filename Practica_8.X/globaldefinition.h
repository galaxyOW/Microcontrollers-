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

#define _XTAL_FREQ 48000000   

#endif	

