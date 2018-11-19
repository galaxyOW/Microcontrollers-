#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "config.h"
#include "globalDefinitions.h"


void configLCD(void);
unsigned char BusyLCD();
void LCD_Data(unsigned char data);
void LCD_Command(unsigned char cmd);

#endif	/* LCD_H */

