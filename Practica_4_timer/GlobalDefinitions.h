#ifndef GLOBALDEFINITIONS_H
#define	GLOBALDEFINITIONS_H

// Defining simple signal states. 

#define _ON 1                  
#define _OFF 0                  
#define INPUT 1
#define OUTPUT 0
#define READ 1
#define WRITE 0
#define BAJO 0


// Defining simple commands for the LCD to use. 

#define COMMAND 0
#define DATA 1
#define HABILITADO 1
#define DESHABILITADO 0

// Defining the CLEAR to clean the LCD's display using binary. 

#define CLEAR 0b00000001     

// PORT is being used to put the pins in a LOW state. 

#define RS PORTBbits.RB2       
#define RW PORTBbits.RB3       
#define EN PORTBbits.RB4 

// TRIS is being used to put the pins as output. 

#define RS_TRIS TRISBbits.RB2   
#define RW_TRIS TRISBbits.RB3
#define EN_TRIS TRISBbits.RB4

// LDATA is used to define which vaiables will go into port D.

#define ldata LATD              

// Defining function in order to use delays. 

#define _XTAL_FREQ 48000000    

#endif	

