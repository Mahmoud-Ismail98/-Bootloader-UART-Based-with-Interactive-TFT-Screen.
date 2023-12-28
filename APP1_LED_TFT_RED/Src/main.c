/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 23 DEC 2023     ****************/
/********** version     : V 01			  ****************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "../Inc/HAL/TFT/fonts.h"
#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/STK_interface.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"
#include "../Inc/HAL/TFT/TFT_interface.h"

#include "../Inc/MCAL/UART/USART_interface.h"
#include "../Inc/MCAL/FPEC/FPEC_interface.h"

#define BLUE_LED 6
#define RED_LED 7
#define GREEN_LED 8
#define RESET_switch 0
volatile u8 RESET_switch_READ=1;

/*fun that save the adrress loction of the application selected in rom*/
typedef void (*adress_to_loc_t)(void);
adress_to_loc_t address_of_selective_app =0;
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

void main(void)
{

	RCC_voidInitSysClock();	/*enable HSI clock*/
	RCC_voidEnableClock(RCC_APB2 , 2);	/*enable GPIO A*/
	RCC_voidEnableClock(RCC_APB2 , 3);	/*enable GPIO B*/
	RCC_voidEnableClock(RCC_APB2 , 12); /* SPI Enable Clock */
	MGPIO_voidSetPinDirection(GPIOA,PIN1 ,OUTPUT_SPEED_2MHZ_PP); 	   //A0
	MGPIO_voidSetPinDirection(GPIOA,PIN2 ,OUTPUT_SPEED_2MHZ_PP);	  //RST
	MGPIO_voidSetPinDirection(GPIOA,PIN5 ,OUTPUT_SPEED_10MHZ_AFPP);	  //CLK
	MGPIO_voidSetPinDirection(GPIOA,PIN7 ,OUTPUT_SPEED_10MHZ_AFPP);	  //MOSI

	MGPIO_voidSetPinDirection(GPIOB,GREEN_LED ,OUTPUT_SPEED_2MHZ_PP);	  //GREEN_LED
	MGPIO_voidSetPinDirection(GPIOB,RED_LED,OUTPUT_SPEED_2MHZ_PP);	  //RED_LED
	MGPIO_voidSetPinDirection(GPIOB,BLUE_LED ,OUTPUT_SPEED_2MHZ_PP);	  //GREEN_LED
     /*Configuar  RESET_switch pins as input pullup  */
	MGPIO_voidSetPinDirection(GPIOB,RESET_switch,INPUT_PULL_UP_DOWEN);  /* B4 Input pullup */
	MGPIO_voidSetPinValue(GPIOB,RESET_switch,PULLUP_SELECT);
	/* Init STK */
	MSTK_voidInit();
	/* SPI Init */
	MSPI1_voidInit();

	/* TFT Init */
	HTFT_voidInitialize();
	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(0,10, "APPLLICATION 1", Font_11x18, RED , BLACK);
	ST7735_WriteString(0,50, "    RED LED  ", Font_11x18, RED , BLACK);

	MGPIO_voidSetPinValue(GPIOB,RED_LED,GPIO_HIGH);
	MGPIO_voidSetPinValue(GPIOB,BLUE_LED,GPIO_LOW);
	MGPIO_voidSetPinValue(GPIOB,GREEN_LED,GPIO_LOW);

	while(RESET_switch_READ==1)
	{
			RESET_switch_READ=MGPIO_u8GetPinValue(GPIOB,RESET_switch);
			MGPIO_voidSetPinValue(GPIOB,RED_LED,GPIO_HIGH);
			MSTK_voidSetBusyWait(5000000);
			RESET_switch_READ=MGPIO_u8GetPinValue(GPIOB,RESET_switch);
			MGPIO_voidSetPinValue(GPIOB,RED_LED,GPIO_LOW);
			MSTK_voidSetBusyWait(5000000);
	}
	if (RESET_switch_READ==0)
	{
		SCB_VTOR = 0x08000000;
		address_of_selective_app = *((adress_to_loc_t *)0x08000004);
		address_of_selective_app();
	}
	

}
