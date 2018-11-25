#ifndef GLOBAL_DEFINITIONS_H
#define	GLOBAL_DEFINITIONS_H

#define _XTAL_FREQ 48000000             // Defining frequency of the PIC

// Defining basic INPUT and OUTPUT.

#define _OFF  0  
#define _ON 1    
#define OUTPUT 0 
#define INPUT 1  


#define READ 1
#define WRITE 0
#define DATAS 1
#define COMMAND 0
#define HABILITADO 1
#define DESHABILITADO 0



// Defining pins that will be used to receive signals from TSOP.
// RB0 is used since it is an interruption pin. 

#define TSOP PORTBbits.RB0
#define TRIS_TSOP TRISBbits.RB0

#define ldata LATD      

#endif	/* GLOBAL_DEFINITIONS_H */
