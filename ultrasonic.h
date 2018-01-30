/*
void return_distance()
oid ultrasonic_init();
void ultrasonic_trigger();
inline void ultrasonic_loop();
*/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define trigger_DDR DDRB
#define trigger_PORT PORTB
#define trigger_pin 0
#define trig_time 200
#define div_factor 58

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include"millis.h"

void ultrasonic_init();
void ultrasonic_trigger();
inline void ultrasonic_loop();
static volatile int i=1;
static volatile unsigned long long time1m=0;
static volatile unsigned long long time1u=0; 
static volatile unsigned long long time2m=0;
static volatile unsigned long long time2u=0;
static volatile unsigned long long ultra_time=0;

ISR (INT0_vect)
{
if ( i==0)
{
time1m=millis();
time1u=micros();
i=1;
}

else if ( i==1)
{
time2m=millis();
time2u=micros();
ultra_time=(time2m-time1m)*1000+(time2u-time1u);
print_char('\r');
i=0;
time1m=time2m=0;
}
}




void ultrasonic_init()
{
timer2_init();
sei();
GICR |=(1<<INT0);
MCUCR|=(1<<ISC00);
trigger_DDR |=(1<<trigger_pin);
trigger_PORT|=(1<<trigger_pin);
ultrasonic_trigger();
}

void ultrasonic_trigger()
{

trigger_PORT&=~(1<<trigger_pin);
		trigger_PORT|= (1<<trigger_pin);
		
}

ultrasonic_loop()
{
if (!(millis()%trig_time))
{
	//print_string("Starting");
	//print_char('\r');
ultrasonic_trigger(); 
//print_ulong(ultra_time);
//print_char('\r');
//print_string("Done");


//print_char('\r');
}
}

void return_distance()
{
return(ultra_time/div_factor);
}