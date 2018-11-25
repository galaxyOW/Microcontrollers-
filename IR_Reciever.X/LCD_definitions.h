#ifndef LCD_DEFINITIONS_H
#define	LCD_DEFINITIONS_H

//DEFINE CONTROL SIGNAL 
#define ENABLE LATBbits.LB4
#define RW LATBbits.LB3
#define RS LATBbits.LB2

#define TRIS_RS TRISBbits.RB2
#define TRIS_RW TRISBbits.RB3
#define TRIS_ENABLE TRISBbits.RB4


//DEFINE PORT D
#define D0 LATDbits.LD0
#define D1 LATDbits.LD1
#define D2 LATDbits.LD2
#define D3 LATDbits.LD3
#define D4 LATDbits.LD4
#define D5 LATDbits.LD5
#define D6 LATDbits.LD6
#define D7 LATDbits.LD7




// DEFINE INSTRUCTIONS
#define COMMAND 0
#define DATA 1

#define WRITE 0
#define READ 1


// YOU KNOW
#define _ON 1
#define _OFF 0
#define OUTPUT 0
#define INPUT 1
#define _XTAL_FREQ 48000000



#endif	/* LCD_DEFINITIONS_H */

