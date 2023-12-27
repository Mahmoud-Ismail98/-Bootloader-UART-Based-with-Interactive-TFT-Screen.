/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 23 DEC 2023     ****************/
/********** version     : V 01			  ****************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"
#include "../Inc/MCAL/SPI/SPI_config.h"
#include "../Inc/MCAL/SPI/SPI_private.h"

void (*CallBack)(u8);

void MSPI1_voidInit(void)
{
	MSPI1->CR1 = 0x0347;
}

void MSPI1_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive)
{
	/* Clear For Slave Select Pin */
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_LOW);
	
	/* Send Data */
	MSPI1 -> DR = Copy_u8DataToTransmit;
	
	/* Wait Busy Flag to finish */
	while (GET_BIT(MSPI1 -> SR, 7) == 1);

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI1 -> DR;
	
	/* Set Salve Select Pin */
	MGPIO_voidSetPinValue(MSPI1_SLAVE_PIN,GPIO_HIGH);
}

