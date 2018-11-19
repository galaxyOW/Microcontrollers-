// Including libraries necessary to use strings.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including files necessary to run the program

#include "configLCD.h"
#include "config.h"
#include "CCP.h"

int PR2_do = 238;
int PR2_do2 = 224;
int PR2_re = 212;
int PR2_re2 = 200;
int PR2_mi = 189;
int PR2_fa = 178;
int PR2_fa2 = 168;
int PR2_sol = 158;
int PR2_sol2 = 150;
int PR2_la = 141;
int PR2_la2 = 133;
int PR2_si = 126;

float DCycle;

void main()
{    
    LED = _OFF;
    
    configPIC();
    OpenTimer2();
    
    
    while(1){ 
        if(DO == 1){
            OpenPWM1(PR2_do);
            DCycle = PR2_do*(0.5);
            SetDCPWM1(DCycle);
            while(DO == 1);
        }
        if(DO2 == 1){
            OpenPWM1(PR2_do2);
            DCycle = PR2_do2*(0.5);
            SetDCPWM1(DCycle);
            while(DO2 == 1);
        }
        if(RE == 1){
            OpenPWM1(PR2_re);
            DCycle = PR2_re*(0.5);
            SetDCPWM1(DCycle);
            while(RE == 1);
        }
        if(RE2 == 1){
            OpenPWM1(PR2_re2);
            DCycle = PR2_re2*(0.5);
            SetDCPWM1(DCycle);
            while(RE2 == 1);
        }
        if(MI == 1){
            OpenPWM1(PR2_mi);
            DCycle = PR2_mi*(0.5);
            SetDCPWM1(DCycle);
            while(MI == 1);
        }
        if(FA == 1){
            OpenPWM1(PR2_fa);
            DCycle = PR2_fa*(0.5);
            SetDCPWM1(DCycle);
            while(FA == 1);
        }
        if(FA2 == 1){
            OpenPWM1(PR2_fa2);
            DCycle = PR2_fa2*(0.5);
            SetDCPWM1(DCycle);
            while(FA2 == 1);
        }
        if(SOL == 1){
            OpenPWM1(PR2_sol);
            DCycle = PR2_sol*(0.5);
            SetDCPWM1(DCycle);
            while(SOL == 1);
        }
        if(SOL2 == 1){
            OpenPWM1(PR2_sol2);
            DCycle = PR2_sol2*(0.5);
            SetDCPWM1(DCycle);
            while(SOL2 == 1);
        }
        if(LA == 1){
            OpenPWM1(PR2_la);
            DCycle = PR2_la*(0.5);
            SetDCPWM1(DCycle);
            while(LA == 1);
        }
        if(LA2 == 1){
            OpenPWM1(PR2_la2);
            DCycle = PR2_la2*(0.5);
            SetDCPWM1(DCycle);
            while(LA2 == 1);
        }
        if(SI == 1){
            OpenPWM1(PR2_si);
            DCycle = PR2_si*(0.5);
            SetDCPWM1(DCycle);
            while(SI == 1);
        }
        
        OpenPWM1(0);
        SetDCPWM1(0);
        
                
}
}

