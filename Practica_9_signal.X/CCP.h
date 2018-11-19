#ifndef CCP_H
#define	CCP_H

#include <xc.h>
#include "config.h"
#include "globaldefinition.h"

void OpenTimer2();
void OpenPWM1(unsigned char PR2Value);
void SetDCPWM1(float DC);


#endif	/* CCP_H */

