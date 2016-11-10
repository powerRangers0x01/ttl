/*
 * UART.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: abanoub
 */

#include "UART.h"
#include <avr/io.h>
#include <math.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
/****************************************************************************
 * Function    : UART_Init_void
 *
 * DESCRIPTION : init the UART
 *
 * PARAMETERS  : unsigned int Bud_Rate
 *
 * Return Value: None.
 ******************************************************************************/

extern void UART_Init_void(unsigned int Baud_Rate)
{
	unsigned char urr;
	urr=lrint((F_CPU/(16L*Baud_Rate))-1);
	/*Set ubrr regster "boud rate" */
	UBRRH = (unsigned char)(urr>>8);
	UBRRL = (unsigned char)urr;
	/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);  //this 10001110 will be in regster ucsrc
}

/****************************************************************************
 * Function    : UART_Send_char_void
 *
 * DESCRIPTION : send a char
 *
 * PARAMETERS  : char data
 *
 * Return Value: None.
 ******************************************************************************/

extern void UART_SendChar_void(char data)
{
	while (!(UCSRA & (1<<UDRE)));		//whit until data register be empety
	UDR =data;							//put data in data register
	while (!(UCSRA & (1<<TXC)) );       //whit until all data sending
}
/****************************************************************************
 * Function    : UART_Send_char_void
 *
 * DESCRIPTION : recive a char
 *
 * PARAMETERS  : void
 *
 * Return Value: char
 ******************************************************************************/

extern char UART_ReciveChar_char (void)
{
	while (!(UCSRA & (1<<RXC)) );  //whit until reciv complet
	return UDR;					   //return data recived in UDR
}

////////////////////////////////////////////////******************************
extern char UART_ReciveChar_unwait_char (void)
{
	if(!(UCSRA & (1<<TXC)) )return -1;     //if reciv notcomplet return -1
	else return UDR;					   //return data recived in UDR
}
/****************************************************************************
 * Function    : UART_SendString_void
 *
 * DESCRIPTION : send a string
 *
 * PARAMETERS  : char *data:pointer to data
 *
 * Return Value: None.
 ******************************************************************************/

extern void UART_SendString_void(char*data)

{
	int i=0;

	while(data[i])
	{
		UART_SendChar_void( data[i] );
		i++;
	}

}

/****************************************************************************
* Function    : UART_ReciveString_void
*
* DESCRIPTION : send a string
*
* PARAMETERS  : pointer to recive data in it
*
* Return Value: void
******************************************************************************/
extern void UART_ReciveString_void (char * ptr)
{
	int i=0;
		ptr[i]=UART_ReciveChar_char();
		while(ptr[i] !='#')
		 {
			i++;
			ptr[i]=UART_ReciveChar_char();

		 }
		ptr[i]='\0';
}


