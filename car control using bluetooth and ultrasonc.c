#define F_CPU 16000000UL

#define FORWARD 1
#define BACKWARD 0
#define safe_distance 100
#define rotate_time 100


#define rotate_DDR
#define rotate_PORT
#define rotate_pin1
#define rotate_pin2

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"
#include"ultrasonic.h"
#include"servo.h"
#include"dc.h"



void rotate_init()
rotate_forward();
rotate_backward();
rotate_stop();


int safe_flag=1;
int pick_flag=0;

void pwm_init()
{
	TCCR1A |=(1<<WGM11)|(1<<COM1A1)|(1<<COM1B1);
	TCCR1B |=(1<<WGM12)|(1<<WGM13)|(1<<CS10);
	DDRD |=(1<<PD5)|(1<<PD4);
	ICR1 = 3999;
	sei();
}

void setdirectiona(int direction)
{
	DDRC |= (1<<PC2)|(1<<PC3);
	if (direction == FORWARD)
	{
		PORTC |= (1<<PC2);
		PORTC &= ~(1<<PC3);
	}
	else if(direction == BACKWARD)
	{
		PORTC &= ~(1<<PC2);
		PORTC |= (1<<PC3);
	}
}

void setdirectionb(int direction)
{
	DDRC |=(1<<PC4)|(1<<PC5);
	if (direction == FORWARD)
	{
		PORTC |= (1<<PC4);
		PORTC &= ~(1<<PC5);
	}
	else if(direction == BACKWARD)
	{
		PORTC &= ~(1<<PC4);
		PORTC |= (1<<PC5);
	}

}


unsigned int dutycycle (int per)
{
	return (((float) per/100)*3999);
}

void speed_ctrl(int speeda , int speedb)
{
		OCR1A = speeda;
		OCR1B = speedb;
}

void setdutycycle(unsigned int *x,unsigned int *y,int num)
{
	*x=dutycycle(num);
	*y=dutycycle(num);
}


int main(void)
{
	unsigned int dutya=0;
	unsigned int dutyb=0;
	uart_init();
	pwm_init();
		ultrasonic_init();

	OCR1A = dutya;
	OCR1B = dutyb;
			print_string("\n\r Character for performance:");

    while (1)
    {
ultrasonic_loop();
if (ultra_time<300)
safe_flag=0;
		else
safe_flag=1;
if (safe_flag==1)
{
		switch(info)
		{
			case 'F':

				setdirectiona(FORWARD);
				setdirectionb(FORWARD);
				speed_ctrl(dutya,dutyb);
				break;
			case 'B':
				setdirectiona(BACKWARD);
				setdirectionb(BACKWARD);
				speed_ctrl(dutya,dutyb);
				break;
			case 'L':

				setdirectiona(FORWARD);
				setdirectionb(BACKWARD);
				speed_ctrl(dutya,dutyb);
				break;
			case 'R':

				setdirectionb(FORWARD);
				setdirectiona(BACKWARD);
				speed_ctrl(dutya,dutyb);
				break;
			case 'G':
				setdirectiona(FORWARD);
				setdirectionb(FORWARD);
				speed_ctrl(dutya,(dutyb-600));
				break;
			case 'I':
				setdirectiona(FORWARD);
				setdirectionb(FORWARD);
				speed_ctrl((dutya-600),dutyb);
				break;
			case '0':

				setdutycycle(&dutya,&dutyb,0);
								speed_ctrl(dutya,dutyb);

				break;
			case '1':
				setdutycycle(&dutya,&dutyb,10);
								speed_ctrl(dutya,dutyb);

				break;
			case '2':
				setdutycycle(&dutya,&dutyb,20);
								speed_ctrl(dutya,dutyb);

				break;
			case '3':
				setdutycycle(&dutya,&dutyb,30);
								speed_ctrl(dutya,dutyb);

				break;
			case '4':
				setdutycycle(&dutya,&dutyb,40);
								speed_ctrl(dutya,dutyb);

				break;
			case '5':
				setdutycycle(&dutya,&dutyb,50);
								speed_ctrl(dutya,dutyb);

				break;
			case '6':
				setdutycycle(&dutya,&dutyb,60);
								speed_ctrl(dutya,dutyb);

				break;
			case '7':
				setdutycycle(&dutya,&dutyb,70);
								speed_ctrl(dutya,dutyb);

				break;
			case '8':
				setdutycycle(&dutya,&dutyb,80);
								speed_ctrl(dutya,dutyb);

				break;
			case '9':
				setdutycycle(&dutya,&dutyb,90);
								speed_ctrl(dutya,dutyb);

				break;
			case 'q':
				setdutycycle(&dutya,&dutyb,100);
								speed_ctrl(dutya,dutyb);

            case 'D':
                if (pick_flag==1)
                {
 PORTC &= ~(1<<PC4);
	    PORTC &= ~(1<<PC5);
	    PORTC &= ~(1<<PC2);
	    PORTC &= ~(1<<PC3);

        place();
                    pick_flag=0;
                }

				break;
		}
 }

else
{
	if (info=='B')
	{
	    setdirectiona(BACKWARD);
        setdirectionb(BACKWARD);
        speed_ctrl(dutya,dutyb);
    }

    else
    {
        PORTC &= ~(1<<PC4);
	    PORTC &= ~(1<<PC5);
	    PORTC &= ~(1<<PC2);
	    PORTC &= ~(1<<PC3);

	    if (info=='A')
        {
            rotate_forward();
            info='Z';
        }

        else if (info=='B')
        {
          pick();
          pick_flag=1;
        }
    }


}

}
}


