#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>
#include "globaldefinition.h"

void configPIC(void);
void initADC();
unsigned int ADC_read(unsigned char x);


#endif	/* CONFIG_H */