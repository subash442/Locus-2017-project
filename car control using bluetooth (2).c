/*
 * motor.c
 *
 * Created: 1/16/2017 7:05:10 PM
 * Author : Subash
 */ 

#define F_CPU 16000000UL

#define BAUD 9600
#define BAUD_PRESCALE (((F_CPU)/(16UL * BAUD))-1)

#define FORWARD 1
#define BACKWARD 0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void pwm_init()
{
	TCCR1A |=(1<<WGM11)|(1<<COM1A1)|(1<<COM1B1);
	TCCR1B |=(1<<WGM12)|(1<<WGM13)|(1<<CS10);
	DDRD |=(1<<PD5)|(1<<PD4);
	ICR1 = 3999;
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



unsigned char USART_Receive()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}

void USART_Transmit( unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
}

void uart_num_transmit(int num)
{
	int numberArray[5];
	int c = 0;
	int n = num;
	/* extract each digit */
	while (n != 0)
	{
		numberArray[c] = n % 10;
		n /= 10;
		c++;
	}
	while(c>0)
	{
		USART_Transmit(numberArray[--c]+'0');
	}
}

void uart_str_transmit(char* str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		USART_Transmit(str[i]);
	}
}

void uart_init()
{
	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;
	UCSRB |= (1<<TXEN)|(1<<RXEN);
	UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
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
	unsigned char c;
	uart_init();
	pwm_init();
	OCR1A = dutya;
	OCR1B = dutyb;
	
    while (1) 
    {
		uart_str_transmit("\n\r Character for performance:");
		c=USART_Receive();
		switch(c)
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
				break;
			case '1':
				setdutycycle(&dutya,&dutyb,10);
				break;
			case '2':
				setdutycycle(&dutya,&dutyb,20);
				break;
			case '3':
				setdutycycle(&dutya,&dutyb,30);
				break;
			case '4':
				setdutycycle(&dutya,&dutyb,40);
				break;
			case '5':
				setdutycycle(&dutya,&dutyb,50);
				break;
			case '6':
				setdutycycle(&dutya,&dutyb,60);
				break;
			case '7':
				setdutycycle(&dutya,&dutyb,70);
				break;
			case '8':
				setdutycycle(&dutya,&dutyb,80);
				break;
			case '9':
				setdutycycle(&dutya,&dutyb,90);
				break;
			case 'q':
				setdutycycle(&dutya,&dutyb,100);
				break;
		}
	}
}