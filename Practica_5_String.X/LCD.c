#include "LCD.h"
#include "globaldefinitions.h"
#include "LCD_Definitions.h"

void iniLCD (void){
   
    // 1. PONER EN BAJO TODOS LOS PINES 
    D7=0;
    D6=0;
    D5=0;
    D4=0;
    D3=0;
    D2=0;   
    D1=0;
    D0=1;
    
    // 2. CONFIGURAMOS EL PUERTO COMO SALIDA 
    TRISD = OUTPUT;
    
    // 3. CONFIGURAR LAS SENALES COMO SALIDA
    RW_TRIS = OUTPUT;
    RS_TRIS = OUTPUT;
    EN_TRIS = OUTPUT;
    
    // 4. PONER EN BAJO TODAS LAS SENALES DE CONTROL
    RW =_OFF;
    RS =_OFF;
    EN =_OFF;
    
    // 5. ESPERAR 15 MS. 
    __delay_ms(15);
    
    // 6. CONFIGURAR 8 BITS, 1 LINEA, 5X8
    Funtion_set(1,0,0);
    
    // 7. ESPERAR 4.167 MS
    __delay_us(167);
    __delay_ms(4);
    
    // 8.CONFIGURAR 8 BITS, 1 LINEA, 5X8
    Funtion_set(1,0,0);
    
    // 9 - ESPERAR 833 MS
    __delay_us (833);
    
    // 10. CONFIGURAR 8 BITS, 1 LINEA, 5X8
    Funtion_set(1,0,0);
    
    // 11. ESPERAR A QUE EL LCD SE DESOCUPE
    wait_BusyLCD();
    
    // 12. CONFIGURAR 8 BITS, 1 LINEA, 5X8
     Funtion_set(1,1,0);
     
     //13. ESPERAR A QUE EL LCD SE DESOCUPE
    wait_BusyLCD();
    
    // 14. CONFIGURAR DISPLAY, CURSOR Y PARADEO DESACTIVADOS
    Display_control (0,0,0);
    
    // 15. ESPERAR A QUE EL LCD SE DESOCUPE
    wait_BusyLCD();
    
    // 16. CONFIGURAR DISPLAY, CURSOR Y PARPADEO ACTIVADO
    Display_control (1,1,1 );
    
    // 17. ESPERAR A QUE EL LCD SE DESOCUPE
    wait_BusyLCD();
    
    // 18. LIMPIAR PANTALLA
    Clear_Display ();
    
    // 19. ESPERAR A QUE EL LCD SE DESOCUPE
    wait_BusyLCD();
    
    // 20. REGRESAR AL INICIO EL CURSOR. 
    Return_home ();
    
    // 21. ESPERAR A QUE EL LCD SE DESOCUPE. 
    wait_BusyLCD();
}


void LCD_command (void){
   unsigned  int  i;

    // 1. LOS DATOS LLEGAN DE LAS FUNCIONES DE INSTRUCCIONES 
    // 2. CONFIGURAR EL PUERTO DE DATOS COMO SALIDA 
    TRISD= OUTPUT;
    
    // 3. SENAL RW COMO ESCRIBIR
    RW= WRITE;
    
    // 4. SENAL RS COMO COMANDO
    RS= COMMAND;
    
    // 5. ESPERAR 2 MS 
    for( i=0; i<19; i++ ){
        NOP();
    }
    
    // 6. ENABLE HABILITADO
    EN = _ON;
    
    // 7. ESPERAR 2 MS
    for( i=0; i<19; i++ ){
        NOP();
    }
    
    // 8. ENABLE DESHABILITADO
    EN = _OFF;
    
    // 9. ESPERAR 2 MS. 
    for( i=0; i<19; i++ ){
        NOP();
    }
    // 10- DEFINIR PUERTO COMO ENTRADA. 
    TRISD= INPUT;
}

void wait_BusyLCD (void){
    int b=1;
    unsigned int i;
    while (b==1){
        
        // 1. SENAL DE CONTROL RW COMO LEER
        RW = READ;
        
        // 2. SENAL DE CONTROL RS COMO COMANDO
        RS= COMMAND;
        
        // 3. ESPERAR 2 MS
        for( i=0; i<19; i++ ){
            NOP();
        }
        // 4. HABILITAR ENABLE
        EN =_ON;
        
        // 5. ESPERAR 2 MS
        for( i=0; i<19; i++ ){
            NOP();
        }
        
        // 6. CHECAR SI LA BANDERA ESTA OCUPADO
        if (D7==1){
            EN  = _OFF;  
            RW = WRITE;
            b=1;
        } else{
                EN = _OFF;  
                RW = WRITE; 
                b=0;  
        
        }
    }    
}

void LCD_data (char t){
    
    // 1. ESTABLECIMOS DESDE ANTES LOS VALORES DE LOS PUERTOS D
    LATD=t;
    
    // 2. SE CONFIGURA EL PUERTO DE DATOS COMO SALIDA
    TRISD=OUTPUT;
    
    // 3. RW COMO ESCRIBIR
    RW= WRITE;
    
    // 4. RS COMO DATO
    RS=DATA;
    
    //5ESPERAR 1.5 MS
    for( int i=0; i<19; i++ ){
        NOP();
    }
    
    // 6. ENABLE HABILITADO
    EN=_ON;
    
    // 7. ESPERAR 1.5 MS
    for( int i=0; i<19; i++ ){
        NOP();
    }
    
    //  8. DESHABILITAR ENABLE
    EN =_OFF;
    
    //9. RS COMO COMANDO
    RS= COMMAND;
    
    // 10. CONFIGURAR EL PUERTO D COMO ENTRADA
    TRISD= INPUT;
    
}

// Function created to print characters on the LCD. 

void print_in_LCD (const char *t){
    
    // Variable created to keep track of position in the character array. 
    
    unsigned int c=0;
    
    // While used to print all the characters in the array as a string. 
    
    while (t[c] != 0){
        __delay_ms(10);
        LCD_data (t[c]);                        // Using the data function to print each character. 
        c++;                                    // Incrementing counter value in order to move through the array. 
    }

}

// Function created to print data on the first row or second row of the LCD. 

void Write_in_pos_LCD(int linea ,unsigned casilla)
{
    unsigned int  pos=0;
    if(linea==1)
    {
        pos=( 128 + casilla);                   // Prints a message on the first row from position 0 to 16. 
        LATD= pos;
        LCD_command();
    }
    else
    {
        pos=( 192 + casilla);                   // Prints a message on the second row form positions 0 to 16. S
        LATD= pos;
        LCD_command();    
    }  
}


void Clear_Display (void){  
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

void Return_home (void){  
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


void Entry_mode_set (int ID, int SH){ 
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

void Display_control ( int D, int C, int B){  

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

void Cursor_or_display_shift (int SC, int RL){  
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

void Funtion_set (int DL, int N, int F){  
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




