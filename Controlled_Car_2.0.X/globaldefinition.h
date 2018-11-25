
#ifndef GLOBALDEFINITION_H
#define	GLOBALDEFINITION_H

#define _ON 1                
#define _OFF 0                  
#define INPUT 1
#define OUTPUT 0
#define BAJO 0

#define LED_TRIS TRISDbits.RD0
#define LED PORTDbits.RD0

#define TRIG PORTAbits.RA0 
#define TRIGTRIS TRISAbits.RA0
#define ECHO PORTBbits.RB0
#define ECHOTRIS TRISBbits.RB0

#define LEFTIR_TRIS TRISAbits.RA3
#define RIGHTIR_TRIS TRISAbits.RA1
#define CENTRALIR_TRIS TRISAbits.RA2

#define LEFTIR PORTAbits.RA3
#define RIGHTIR PORTAbits.RA1
#define CENTRALIR PORTAbits.RA2

#define RMOT1_TRIS TRISBbits.RB1
#define RMOT2_TRIS TRISBbits.RB2
#define LMOT1_TRIS TRISBbits.RB3
#define LMOT2_TRIS TRISBbits.RB4

#define RMOT1 PORTBbits.RB1
#define LMOT1 PORTBbits.RB3
#define RMOT2 PORTBbits.RB2
#define LMOT2 PORTBbits.RB4


// Defining pins that will be used to receive signals from TSOP.
// RB0 is used since it is an interruption pin. 

#define TSOP PORTBbits.RB0
#define TRIS_TSOP TRISBbits.RB0

#define Trigger_Pulse LATA0

// Defined function in order to use delays. 

#define _XTAL_FREQ 48000000  

#endif	/* GLOBALDEFINITION_H */

