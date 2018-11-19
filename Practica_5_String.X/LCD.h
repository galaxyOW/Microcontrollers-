#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "LCD_Definitions.h"

void iniLCD ();
void LCD_command ();
void LCD_data ( char t);
void print_in_LCD (const char *t);
void Write_in_pos_LCD();
void wait_BusyLCD ();
void Clear_Display ();
void Return_home ();
void Entry_mode_set ();
void Display_control ();
void Cursor_or_display_shift ();
void Funtion_set ();

#endif

