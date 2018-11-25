#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include "globaldefinition.h"

void configPIC(void);
void _FORWARD();
void _LEFT();
void _RIGHT();
void _STOP(); 
void line_follow();
void Trigger_Pulse_s();
void Config_Ultrasonic();
float Detect_object();
void Avoid_object();
void _REVERSE();
void timer1config(void);;
void OpenTimer2();
void OpenPWM1(unsigned char PR2Value);
void SetDCPWM1(float DC);
void SetDCPWM2(unsigned int DC2);
#endif	/* CONFIG_H */

