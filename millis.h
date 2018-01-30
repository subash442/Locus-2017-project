/*
void timer2_init();
int millis();
int micros();
*/

#include<avr/io.h>
#include<avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


volatile unsigned long long milli=0;

ISR(TIMER2_COMP_vect)
{

milli++;
}
void timer2_init()
{
TCCR2|=(1<<WGM21)|(1<<CS22);
OCR2=250;
sei();

TIMSK|=(1<<OCIE2);
}

int millis()
{
return(milli);
}
int micros()
{
return (TCNT2*4);
}
