#ifndef GLOBALDEFINITIONS_H
#define	GLOBALDEFINITIONS_H

// Declaring which pins the LED and button will be connected to. 

#define FLANCO_TRIS TRISAbits.RA4 
#define LED_TRIS TRISAbits.RA0
#define LED PORTAbits.RA0

// Declaring simple signal definitions.

#define _ON 1 
#define _OFF 0 
#define INPUT 1
#define OUTPUT 0


#endif

