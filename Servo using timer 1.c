/*
 * Servo.c
 *
 * Created: 12/27/2016 9:34:18 PM

 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void servo_init()
{
	TCCR1A |= (1<<WGM11)|(1<<COM1A1);
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	DDRD |= (1<<PD5);
	ICR1 = 39999;
}

void servo_angle(float angle)
{
	int valueTimer =((float)angle/180)*3999;
	OCR1A = valueTimer;
	//OCR1A=4000;
}

int main(void)
{
    /* Replace with your application code */
	servo_init();
	servo_angle(42.0);
    while (1) 
    {
		
    }
}

