#include "config.h"
#include "configLCD.h"
#include "globaldefinition.h"
#define _XTAL_FREQ 48000000

//This file contains the functions, along with their instructions, used to initialize the LCD. 

void LCD_Command(unsigned char cmd){
    //PASO 1 - PONER EL PUERTO DE DATOS CON EL VALOR DE COMANDO 
    ldata = cmd;    
    
    //PASO 2 - CONFIGURAR EL PUERTO DE DATOS COMO SALIDA
    TRISD = OUTPUT;    
    
    //PASO 3 - SENAL DE CONTROL RW = ESCRIBIR 
    RW = WRITE;
    
    //PASO 4 - SENAL DE CONTROL RS = COMANDO 
    RS = COMMAND;
    
    //PASO 5 - ESPERAR 1.5 US
    for(int i = 0; i < 19; i++){
        NOP();
    }

    //PASO 6 - SENAL DE CONTROL EN = HABILITADO 
    EN = HABILITADO;
    
    //PASO 7 - ESPERAR 1.5 US 
    for(int i = 0; i < 19; i++){
        NOP();
    }
    
    //PASO 8 - SENAL DE CONTROL EN = DESHABILITADO 
    EN = DESHABILITADO;
   
    //PASO 9 - ESPERAR 1.5 US
    for(int i = 0; i < 19; i++){
        NOP();
    }

    //PASO 10 - CONFIGURAR EL PUERTO DE DATOS COMO ENTRADA 
    TRISD = 255;
}

void LCD_Data(unsigned char data){
    
    //PASO 1 - PONER EN EL PUERTO DE DATOS EL VALOR DEL DATO 
    ldata = data;
    
    //PASO 2 - CONFIGURAR EL PUERTO DE DATOS COMO SALIDA 
    TRISD = OUTPUT;     
    
    //PASO 3 - SENAL DE CONTROL RW = ESCRIBIR 
    RW = WRITE;
    
    //PASO 4 - SENAL DE CONTROL RS = DATO 
    RS = DATA;
    
    //PASO 5 - ESPERAR 1.5 US
    for(int i = 0; i < 19; i++){
        NOP();
    }

    //PASO 6 - SENAL DE CONTROL EN = HABILITADO 
    EN = HABILITADO;
    
    //PASO 7 - ESPERAR 1.5 US
    for(int i = 0; i < 19; i++){
        NOP();
    }

    //PASO 8 - SENAL DE CONTROL EN = DESHABILITADO 
    EN = DESHABILITADO;
    
    //PASO 9 - SENAL DE CONTROL RS = COMANDO 
    RS = COMMAND;
    
    //PASO 10 - CONFIGURAR EL PUERTO DE DATOS COMO ENTRADA 
    TRISD = 255;
}

unsigned char BusyLCD(){
    //PASO 1 - SENAL DE CONTROL RW = LEER
    RW = READ;

    //PASO 2 - SENAL DE CONTROL RS = COMANDO 
    RS = COMMAND;

    //PASO 3 - ESPERAR 1.5 US
    __delay_us(2);

    //PASO 4 - SENAL DE CONTROL EN = HABILITADO 
    EN = HABILITADO;

    //PASO 5 - ESPERAR 1.5 US
    __delay_us(2);

    EN = DESHABILITADO;
    RW = WRITE;
    
    //PASO 6 - CHECAR LA BANDERA DE "OCUPADO"

    if(ldata & 0x80){
        return 1;
    }
    else{
        return 0;
    } 
}

void configLCD(void){
    
    //PASO 1 - PONER EN BAJO TODO EL PUERTO DE DATOS
    ldata = BAJO;  
    
    //PASO 2 - CONFIGURAR PUERTO DE DATOS COMO SALIDA
    TRISD = OUTPUT;     
    
    //PASO 3 - CONFIGURAR TODAS LAS SEÑALES DE CONTROL COMO SALIDA
    RS_TRIS = OUTPUT;                    
    RW_TRIS = OUTPUT;        
    EN_TRIS = OUTPUT;
    
    //PASO 4 - PONER EN BAJO TODAS LAS SEÑALES DE CONTROL
    RS = BAJO;
    RW = BAJO;              
    EN = BAJO;
    
    //PASO 5 - ESPERAR AL MENOS 15 MS PARA QUE SE ENERGICE EL LCD
    __delay_ms(20); 
    
    //PASO 6 - CONFIGURAR 8 BIT, 1 LINE, 5 X 8
    LCD_Command(0b00110000);  
    
    //PASO 7 - ESPERAR 4.167 MS
    __delay_ms(4);
    __delay_us(167);
    
    //PASO 8 - CONFIGURAR 8 BIT, 1 LINE, 5 X 8
    LCD_Command(0b00110000);
    
    //PASO 9 - ESPERAR 0.8333MS
    __delay_us(833);    //ESPERAR .833 MS
    
    //PASO 10 - CONFIGURAR 8 BIT,1 LINE, 5X8
    LCD_Command(0b00110000);
    
    //PASO 11 - ESPERAR A QUE EL LCD SE DESOCUPE
    while(BusyLCD());   
    
    //PASO 12 - CONFIGURAR 8BIT,2 LINES, 5x8
    LCD_Command(0b00111000); 
    
    //PASO 13 - ESPERAR A QUE EL LCD SE DESOCUPE
    while(BusyLCD());   
   
    //PASO 14 - CONFIGURAR: DISPLAY, CURSOR Y PARPADEO DESACTIVADO
    LCD_Command(0b00001000);    
    
    //PASO 15 - ESPERAR A QUE EL LCD SE DESOCUPE
    while(BusyLCD());
    
    //PASO 16 - CONFIGURAR: DISPLAY, CURSOR Y PARPADEO ACTIVADO
    LCD_Command(0b00001111);    
    
    //PASO 17 - ESPERAR A QUE EL LCD SE DESOCUPE
    while(BusyLCD());
    
    //PASO 18 - LIMPIAR PANTALLA
    LCD_Command(CLEAR);   
    
    //PASO 19 - ESPERAR HASTA QUE EL LCD SE DESOCUPE
    while(BusyLCD());
    
    //PASO 20 - ENVIAR CURSOS AL INICIO 
    LCD_Command(0b00000010);    
    
    //PASO 21 - ESPERAR HASTA QUE EL LCD SE DESOCUPE
    while(BusyLCD());
}

void LCD_write(const char *c){
    unsigned int k = 0;
    while(c[k] !=0 ){
    __delay_ms(10);
    LCD_Data(c[k]);
    k++;
    }
}








