/*
 * File:   main.c
 * Author: roner
 *
 * Created on 30 de Julho de 2016, 17:01
 * 
 * 
 * 
 */


// PIC16F1938 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


//DISPLAY
/*
 *  0 = 3f         4 = 66       8 = 7f
    1 = 06         5 = 6d       9 = 6f
    2 = 5b         6 = 7d
    3 = 4f         7 = 07
 *
 */




// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//roner remenber this ordem of config must be respected 

#define  _XTAL_FREQ 32000000
#include <xc.h>
#include <stdio.h>
#include "lcdflex.h"


unsigned char const VectorDisplay [10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //display

void main(void) {
    
    //configuration

    TRISB = 0x00; //portb as output

    unsigned char buffer1 [20];

    OSCCONbits.IRCF = 0b1110; //8Mhz   32000000/4
    OSCCONbits.SCS = 0b00;

    ANSELA = 0b00000000;
    
    
    
    //code


    Lcd_Init(); //start lcd
    Lcd_Cmd(LCD_CLEAR); //clear lcd 
    Lcd_Cmd(LCD_CURSOR_OFF); //TURN OFF CURSOR
    __delay_ms(100);

    char counter = 0;


    while (1) {


        int counter = 0;

        PORTB = (VectorDisplay[counter]);

        int i;

        for (i = 10; i > 10; i--) {
            sprintf(buffer1, "wait %03d ", i); //save on word buffer the counter three digits
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(100);


        }


        Lcd_Out(1, 4, "mensagem 1 ");
        Lcd_Out(2, 1, "mensagem 2"); //write on row two 
        __delay_ms(1000); //esperamos 600ms
        Lcd_Cmd(LCD_BLINK_CURSOR_ON); //appear cursor
        __delay_ms(1000);
        Lcd_Cmd(LCD_UNDERLINE_ON);
        __delay_ms(1000); //esperamos 1s
        Lcd_Cmd(LCD_CURSOR_OFF); //disappear cursor
        __delay_ms(1000);
        Lcd_Cmd(LCD_CLEAR); //clear cursor
        Lcd_Out(1, 4, "mensagem lcd"); //
        Lcd_Out(2, 4, "mensagem lcd"); //


        //this part for the display
        char r;
        for (r = 0; r < 10; r++) {
            PORTB = (VectorDisplay[r]);

            for (int time = 0; time < 20; time++)__delay_ms(50); //making 100ms
            counter++;

        }
        Lcd_Out(1, 4, "mensagem");
        Lcd_Out(2, 4, "mensagem"); //imprimims thank u
        for (int time = 0; time < 40; time++)__delay_ms(50); //making 2000ms











        return;
    }

}