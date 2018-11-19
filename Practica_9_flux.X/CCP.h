#ifndef CCP_H
#define	CCP_H

#include <xc.h>
#include "config.h"
#include "globaldefinition.h"

void OpenTimer2();
void OpenPWM1(unsigned int PR2Value);
void SetDCPWM1(float DC);
void SetDCPWM2(unsigned int DC2);


#endif	/* CCP_H */

