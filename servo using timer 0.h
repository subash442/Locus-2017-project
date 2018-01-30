/*
void servo_init();
void servo (int angle)
*/

#ifndef SERVO_H
#define SERVO_H

#include<avr/io.h>
#include<avr/interrupt.h>

#define servo_DDR PORTB
#define servo_pin 1
#define servo_up_angle servo_up_angle

int count=0;
volatile int angle;

void servo_init()
{


TCCR0|=(1<<WGM01);//CTC mode
TCCR0|=(1<<CS02);
TIMSK=(1<<OCIE0);
sei();
TCNT0=0;
servo_DDR|=(1<<servo_pin);
OCR0=(int)(61+((float)64/180)*servo_up_angle);

}

ISR (TIMER0_COMP_vect)
{
OCR0=(int)(61+((float)64/180)*angle);
if (count==0)
servo_DDR=(1<<output_pin);
else
servo_DDR&=~(1<<output_pin);

count ++;
if (count >=10)
count=0;


}

void servo(int a)
{
angle=a;
}

#endif