/* 
 * File:   main.c
 * Author: Stefano
 *
 * Created on 16 aprile 2012, 21.07
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include "delay.h"

#define BUZZER_DELAY 20

__CONFIG (FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF & CP_OFF);
/*
 * 
 */

typedef enum display_char {ZER,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGTH,NINE,CHAR_S,CHAR_A,CHAR_F,CHAR_E,CHAR_B,CHAR_O,CHAR_M,CHAR_OFF} display_char;
typedef enum display_port {CENTSEC,DECSEC,SEC,DDSEC} display_port;

void writeOn7SegmentDisplay(display_port displaynum, display_char value);
void display_test();

int centsecval = 0;
int decsecval = 0;
int secval = 0;
int DDsecval = 0;
int buz;
char myportd=0;

int main(int argc, char** argv) {
    TRISA=0b00000000;
    TRISB=0b00000000; 
    TRISC=0b10000000;
    TRISD=0b00000000;
    TRISE=0b00000000;
    PORTA=0;
    PORTB=0; 
    PORTC=0;
    PORTD=0;
    PORTE=0;

    centsecval = 0;
    decsecval = 0;
    secval = 0;
    DDsecval = 6;
    writeOn7SegmentDisplay(CENTSEC,centsecval);
    writeOn7SegmentDisplay(DECSEC,decsecval);
    writeOn7SegmentDisplay(SEC,secval);
    writeOn7SegmentDisplay(DDSEC,DDsecval);
    RB7 = 1;    //sec dot
    RD7 = 0;    //buzzer

    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);

    while(RC7 == 1)
    {
        DelayMs(6);
        writeOn7SegmentDisplay(CENTSEC,centsecval);
        writeOn7SegmentDisplay(DECSEC,decsecval);
        writeOn7SegmentDisplay(SEC,secval);
        writeOn7SegmentDisplay(DDSEC,DDsecval);
        if(centsecval < 0)
        {
            centsecval=9;
            decsecval--;
        }
        else
        {
            centsecval--;
        }
        if(decsecval < 0)
        {
            decsecval=9;
            secval--;
            RB7=RB7^1;
            buz = 2000;
            writeOn7SegmentDisplay(CENTSEC,8);
            RD7 = 0;
            while(buz>0)
            {
                RD7=RD7^1;
                buz--;
                DelayUs(BUZZER_DELAY);
            }
            RD7 = 0;
        }
        if(secval < 0)
        {
            secval=9;
            DDsecval--;
        }
        if(DDsecval < 0)
        {
            writeOn7SegmentDisplay(CENTSEC,ZER);
            writeOn7SegmentDisplay(DECSEC,ZER);
            writeOn7SegmentDisplay(SEC,ZER);
            writeOn7SegmentDisplay(DDSEC,ZER);
            RB7=1;
            DelayMs(250);
            DelayMs(250);
            RB7=0;
            DelayMs(250);
            DelayMs(250);
            writeOn7SegmentDisplay(CENTSEC,CHAR_OFF);
            writeOn7SegmentDisplay(DECSEC,CHAR_OFF);
            writeOn7SegmentDisplay(SEC,CHAR_OFF);
            writeOn7SegmentDisplay(DDSEC,CHAR_OFF);
            DelayMs(250);
            DelayMs(250);
            writeOn7SegmentDisplay(CENTSEC,CHAR_M);
            writeOn7SegmentDisplay(DECSEC,CHAR_O);
            writeOn7SegmentDisplay(SEC,CHAR_O);
            writeOn7SegmentDisplay(DDSEC,CHAR_B);
            while(1)
            {
                RD7=RD7^1;
                buz--;
                DelayUs(BUZZER_DELAY);
            }
        }
    }

    RB7=1;
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);

    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    RB7=0;
    
    while(1)
    {
        writeOn7SegmentDisplay(CENTSEC,CHAR_E);
        writeOn7SegmentDisplay(DECSEC,CHAR_F);
        writeOn7SegmentDisplay(SEC,CHAR_A);
        writeOn7SegmentDisplay(DDSEC,CHAR_S);
        DelayMs(250);
        DelayMs(250);
        DelayMs(250);
        DelayMs(250);
        writeOn7SegmentDisplay(CENTSEC,CHAR_OFF);
        writeOn7SegmentDisplay(DECSEC,CHAR_OFF);
        writeOn7SegmentDisplay(SEC,CHAR_OFF);
        writeOn7SegmentDisplay(DDSEC,CHAR_OFF);
        DelayMs(250);
        DelayMs(250);
    }
    return (EXIT_SUCCESS);
}

/*
dispalynum: E:A=3; B=2; C=1; D=0
*/
void writeOn7SegmentDisplay(display_port displaynum, display_char value)
{
    char codedvalue = 0, myrb7, myre0;

    switch(value)	//codevalue=0b0gfedcba
    {
        case ZER:
            codedvalue=0b00111111;	//0
        break;

        case ONE:
            codedvalue=0b00000110;	//1
        break;

        case TWO:
            codedvalue=0b01011011;	//2
        break;

        case THREE:
            codedvalue=0b01001111;	//3
        break;

        case FOUR:
            codedvalue=0b01100110;	//4
        break;

        case FIVE:
            codedvalue=0b01101101;	//5
        break;

        case SIX:
            codedvalue=0b01111101;	//6
        break;

        case SEVEN:
            codedvalue=0b00000111;	//7
        break;

        case EIGTH:
            codedvalue=0b01111111;	//8
        break;

        case NINE:
            codedvalue=0b01101111;	//9
        break;

        case CHAR_S:
            codedvalue=0b01101101;	//S
        break;

        case CHAR_A:
            codedvalue=0b01110111;	//A
        break;

        case CHAR_F:
            codedvalue=0b01110001;	//F
        break;

        case CHAR_E:
            codedvalue=0b01111001;	//E
        break;

        case CHAR_B:
            codedvalue=0b01111100;	//B
        break;

        case CHAR_O:
            codedvalue=0b01011100;	//O
        break;

        case CHAR_M:
            codedvalue=0b01010100;	//M
        break;

        case CHAR_OFF:
            codedvalue=0b00000000;	//OFF
        break;
    }

    switch(displaynum)
        {
        case CENTSEC:
            PORTD=codedvalue;
        break;

        case DECSEC:
            PORTC=codedvalue;
        break;

        case SEC:
            myrb7 = RB7;
            PORTB=codedvalue;
            RB7 = myrb7;
        break;

        case DDSEC:
            PORTA=codedvalue;
            PORTE=(codedvalue >> 6) & 0b00000001;
        break;
    }
    return;
}

void display_test()
{
    writeOn7SegmentDisplay(CENTSEC,ZER);
    writeOn7SegmentDisplay(DECSEC,ZER);
    writeOn7SegmentDisplay(SEC,ZER);
    writeOn7SegmentDisplay(DDSEC,ZER);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,ONE);
    writeOn7SegmentDisplay(DECSEC,ONE);
    writeOn7SegmentDisplay(SEC,ONE);
    writeOn7SegmentDisplay(DDSEC,ONE);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,TWO);
    writeOn7SegmentDisplay(DECSEC,TWO);
    writeOn7SegmentDisplay(SEC,TWO);
    writeOn7SegmentDisplay(DDSEC,TWO);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,THREE);
    writeOn7SegmentDisplay(DECSEC,THREE);
    writeOn7SegmentDisplay(SEC,THREE);
    writeOn7SegmentDisplay(DDSEC,THREE);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,FOUR);
    writeOn7SegmentDisplay(DECSEC,FOUR);
    writeOn7SegmentDisplay(SEC,FOUR);
    writeOn7SegmentDisplay(DDSEC,FOUR);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,FIVE);
    writeOn7SegmentDisplay(DECSEC,FIVE);
    writeOn7SegmentDisplay(SEC,FIVE);
    writeOn7SegmentDisplay(DDSEC,FIVE);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,SIX);
    writeOn7SegmentDisplay(DECSEC,SIX);
    writeOn7SegmentDisplay(SEC,SIX);
    writeOn7SegmentDisplay(DDSEC,SIX);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,SEVEN);
    writeOn7SegmentDisplay(DECSEC,SEVEN);
    writeOn7SegmentDisplay(SEC,SEVEN);
    writeOn7SegmentDisplay(DDSEC,SEVEN);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,EIGTH);
    writeOn7SegmentDisplay(DECSEC,EIGTH);
    writeOn7SegmentDisplay(SEC,EIGTH);
    writeOn7SegmentDisplay(DDSEC,EIGTH);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,NINE);
    writeOn7SegmentDisplay(DECSEC,NINE);
    writeOn7SegmentDisplay(SEC,NINE);
    writeOn7SegmentDisplay(DDSEC,NINE);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_S);
    writeOn7SegmentDisplay(DECSEC,CHAR_S);
    writeOn7SegmentDisplay(SEC,CHAR_S);
    writeOn7SegmentDisplay(DDSEC,CHAR_S);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_A);
    writeOn7SegmentDisplay(DECSEC,CHAR_A);
    writeOn7SegmentDisplay(SEC,CHAR_A);
    writeOn7SegmentDisplay(DDSEC,CHAR_A);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_F);
    writeOn7SegmentDisplay(DECSEC,CHAR_F);
    writeOn7SegmentDisplay(SEC,CHAR_F);
    writeOn7SegmentDisplay(DDSEC,CHAR_F);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_E);
    writeOn7SegmentDisplay(DECSEC,CHAR_E);
    writeOn7SegmentDisplay(SEC,CHAR_E);
    writeOn7SegmentDisplay(DDSEC,CHAR_E);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_B);
    writeOn7SegmentDisplay(DECSEC,CHAR_B);
    writeOn7SegmentDisplay(SEC,CHAR_B);
    writeOn7SegmentDisplay(DDSEC,CHAR_B);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_O);
    writeOn7SegmentDisplay(DECSEC,CHAR_O);
    writeOn7SegmentDisplay(SEC,CHAR_O);
    writeOn7SegmentDisplay(DDSEC,CHAR_O);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    writeOn7SegmentDisplay(CENTSEC,CHAR_M);
    writeOn7SegmentDisplay(DECSEC,CHAR_M);
    writeOn7SegmentDisplay(SEC,CHAR_M);
    writeOn7SegmentDisplay(DDSEC,CHAR_M);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    DelayMs(250);
    return;
}