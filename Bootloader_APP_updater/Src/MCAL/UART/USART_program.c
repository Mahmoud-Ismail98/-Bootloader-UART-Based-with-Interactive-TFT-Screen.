/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 23 DEC 2023     ****************/
/********** version     : V 01			  ****************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "../Inc/MCAL/UART/USART_interface.h"
#include "../Inc/MCAL/UART/USART_private.h"
#include "../Inc/MCAL/UART/USART_config.h"


void MUSART1_voidInit(void)
{
	/*	baud rate = 9600		*/
	USART1 -> BRR = 0x341;
	/*Enable Rx */
	SET_BIT((USART1-> CR[0]), 3);			/* Enabling Transmitter */
	/*Enable Tx */
	SET_BIT((USART1-> CR[0]), 2);			/* Enabling Receiver */
	/*Enable USART1 */
	SET_BIT((USART1-> CR[0]), 13);			/* Enabling USART */

	/* Clear Status Register */
	USART1 -> SR = 0;				
}

void MUSART1_voidTransmit(u8 arr[])
{
	u8 i = 0;
	while(arr[i] != '\0'){
		USART1 -> DR = arr[i];
		while((GET_BIT((USART1 -> SR), 6)) == 0);
	/* or 	while((USART1 -> SR & 0x40) == 0);  */
		i++;
	}
	
}

u8 MUSART1_u8Receive(u8 * receive_date)
{
	u8 Local_u8Result = 1;

	if ( (GET_BIT((USART1 -> SR), 5)) == 1 )
	{
		*receive_date = USART1 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}

	return (Local_u8Result);
}



















