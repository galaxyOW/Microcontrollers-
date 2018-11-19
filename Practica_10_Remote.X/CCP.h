#ifndef CCP_H
#define	CCP_H

#include <xc.h>
#include "config.h"
#include "globaldefinition.h"

void OpenTimer2();
void OpenPWM1(unsigned int PR2Value);
void SetDCPWM1(float DC);
void SetDCPWM2(unsigned int DC2);
void sendCode(const char *x);
void UP_BTN();
void LEFT_BTN();
void RIGHT_BTN();
void SEND0();
void SEND1();
void CENTRAL_BTN();
void DOWN_BTN();
void MENU_BTN();



#endif	/* CCP_H */

