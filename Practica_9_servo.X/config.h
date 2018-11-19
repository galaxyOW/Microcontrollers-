#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include "globalDefinition.h"
void configPIC(void);
void initCompareMode(void);
void OpenTimer2(unsigned char);
void OpenPWM1(unsigned char); //PR2
void SetDCPWM1();
unsigned char calculatePR2();
unsigned int calculateReg(float);

#endif	/* CONFIG_H */