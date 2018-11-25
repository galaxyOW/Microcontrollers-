#include "LCD_function.h"

void iniLCD (void){
   
    // 1- poner en bajo los puertos de datos.
    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=0;
    D2=0;   
    D1=0;
    D0=1;
    // 2- configurar el puerto de datos como salida.
    TRISD = OUTPUT;
    
    // 3- configurar las señales de control como salida.
    TRIS_RW=OUTPUT;
    TRIS_RS=OUTPUT;
    TRIS_ENABLE=OUTPUT;
    // 4- poner en bajo todas las señales de control.
    RW=_OFF;
    RS=_OFF;
    ENABLE=_OFF;
    // 5-esperar 15 ms
    __delay_ms(15);
    // 6-configurar -- 8 bits--1 linea-- 5x8
    Funtion_set(1,0,0);
    // 7- esperar 4.167 ms
    __delay_us(167);
    __delay_ms(4);
    // 8-configurar -- 8 bits--1 linea-- 5x8
    Funtion_set(1,0,0);
    //9 - esperrar 833 us
    __delay_us (833);
    // 10-configurar -- 8 bits--1 linea-- 5x8
    Funtion_set(1,0,0);
    // 11-esperar a que el LCD se desocupe
    wait_BusyLCD();
    // 12- configurar - 8 bits--2 linea-- 5x8
     Funtion_set(1,1,0);
     //13-esperar a que el LCD se desocupe
    wait_BusyLCD();
    // 14-configurar display, cursor y parpade desactivados.
    Display_control (0,0,0);
    // 15- esperar a que el LCD se desocupe
    wait_BusyLCD();
    // 16-configurar display, cursor y parpade activados.
    Display_control (1,1,1 );
    // 17-esperar a que el LCD se desocupe
    wait_BusyLCD();
    //18- limpiar pantalla
    Clear_Display ();
    // 19-esperar a que el LCD se desocupe
    wait_BusyLCD();
    //20 - regresar a casa el cursor
    Return_home ();
    // 21-esperar a que el LCD se desocupe
    wait_BusyLCD();
}







void LCD_command (void){
   unsigned  int  i;
    //1- los datos llegan de las funciones de instrucciones
    // 2- comfigurar el puerto de datos como salida.
    TRISD= OUTPUT;
    // 3- señal RW como escribir
    RW= WRITE;
    // 4- señal RS como comando
    RS= COMMAND;
    // 5- esperar 2 us 
    for( i=0; i<19; i++ ){
        NOP();
    }
    //  6-ENABLE habilitado
    ENABLE = _ON;
    // 7- esperar 2 us
    for( i=0; i<19; i++ ){
        NOP();
    }
    // 8- ENABLE deshabilitado
    ENABLE = _OFF;
    // 9-señal RS como comando
    for( i=0; i<19; i++ ){
        NOP();
    }
    // 10- 
    TRISD= INPUT;
    
    
    
}

//******************** FUNCION PARA ESPERAR MIENTRAS ESTE OCUPADO EL LCD**********************//

void wait_BusyLCD (void){
    int b=1;
    unsigned int i;
    while (b==1){
        
        // 1-Señal de control e RW en leer.
        RW = READ;
        // 2- señal de control RS en comando
        RS= COMMAND;
        // 3-esperar 2 us
        for( i=0; i<19; i++ ){
        NOP();
    }
        // 4-habilitar enable
        ENABLE=_ON;
        // 5-esperar 2 us
        for( i=0; i<19; i++ ){
        NOP();
    }
        
        // 6-checar la bandera de ocupado-
        if (D7==1){
        
            ENABLE = _OFF;  // deshibilitar enable
            RW = WRITE; // RW en leer
            b=1;
        
        }
        
        else{
        ENABLE = _OFF;  // deshibilitar enable
            RW = WRITE; // RW en leer
            b=0;  // regresarpara un valor 0 salir del bucle
        
        }
    }    
}






//****************DEMADREEEEEEEE**************//



void print_in_LCD (const char *t){
    unsigned int c=0;
    while (t[c]!=0){
    __delay_ms(10);
    LCD_data (t[c]);
    c++;
    
    }

}


void LCD_data ( char t){
    
    // 1- establecimos desde antes los vlaores de los puertos D
    LATD=t;
    // 2- se configura el puertou de datos como salida
    TRISD=OUTPUT;
    // 3- RW como ecribir
    RW= WRITE;
    // 4- RS como dato.
    RS=DATA;
    //5- espererar 1,5 us
    for( int i=0; i<19; i++ ){
        NOP();
    }
    // 6- habilitar ENABLE
    ENABLE=_ON;
    // 7- esperar 1.5 us
    for( int i=0; i<19; i++ ){
        NOP();
    }
    //  8- deshabilitar enable
    ENABLE=_OFF;
    //9- RS configurar como comando
    RS= COMMAND;
    // 10- configurar el puerto D de datos cmo entrada
    TRISD= INPUT;
    
}

void Write_in_pos_LCD(int linea ,unsigned casilla)
{
    unsigned int  pos=0;
    if(linea==1)
    {
        pos=( 128 + casilla); //imprime un mensaje en la primera linea en la casilla 0-16
        LATD= pos;
        LCD_command();
    }
    else
    {
        pos=( 192 + casilla); // imprime un mensaje en la segunda linea en la casilla 0-16
        LATD= pos;
        LCD_command();    
    }  
}

//*********FUNCIONES DE INTRUSCCIONES*************//


void Clear_Display (void){  // funcion para limpiar el LCD
    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=0;
    D2=0;   
    D1=0;
    D0=1;
    
    LCD_command();
}

void Return_home (void){  // funcion para regresar al origen
    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=0;
    D2=0;   
    D1=1;
    D0=0;
    
     LCD_command();

}


void Entry_mode_set (int ID, int SH){  // funcion para establcer modo de entrada
    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=0;
    D2=1;   
    D1=ID;
    D0=SH;
    LCD_command();
}

void Display_control ( int D, int C, int B){  // funcionn para control del DIsplay

    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=1;
    D2=D;   
    D1=C;
    D0=B;
    LCD_command();

}

void Cursor_or_display_shift (int SC, int RL){  // funcion de cambio del cursos o del display
    D7=0;
    D6=0;
    D5=0;
    D4=1;
    D3=SC;
    D2=RL;   
    D1=0;
    D0=0;
    LCD_command();
}

void Funtion_set (int DL, int N, int F){  //funcion para establecer formato del display
    D7=0;
    D6=0;
    D5=1;
    D4=DL;
    D3=N;
    D2=F;   
    D1=0;
    D0=0;
    LCD_command();
}



