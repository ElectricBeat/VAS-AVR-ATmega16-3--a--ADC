/*
 * ADC.c
 *
 * Created: 26-04-2024 15:37:28
 * Author : SRIDHAR
 */ 

#define F_CPU 1000000UL					/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */
#include <stdlib.h>
#include "lcd_4_bit.h"

char String[5];
int value;

void ADC_Init()
{
	DDRA	=	0xF0;					/* Make ADC port as input */
	ADCSRA	=	0x83;					/* Enable ADC, fr/8  */
	ADMUX	=	0x40;					/* Vref: internal 2, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);		/* Set input channel to read */

	ADCSRA |= (1<<ADSC);				/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);		/* Monitor end of conversion interrupt */
	
//	_delay_us(10);
	AinLow = (int)ADCL;					/* Read lower byte*/
	Ain = (int)ADCH*256;				/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);						/* Return digital value*/
}

int main()
{
	LCD_Init();							/* Initialize LCD */
	ADC_Init();							/* Initialization of ADC */

	while (1)
	{
		lcd_cursor(1,0);				/* Go to 1st line*/
		LCD_String("ADC:");				/* write string on 1st line of LCD*/
		lcd_cursor (1,4);
		value=ADC_Read(0);				/* Read ADC channel 0 */
		divider(value);
//		itoa(value,String,10);			/* int. to string conversion */
//		LCD_String(String);
//		LCD_String("  ");
	}
}