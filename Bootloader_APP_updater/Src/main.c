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

//=====================================================================
//Global variables
//======================================================================
 u8 recieving_record[100];
volatile u8 char_count=0;
volatile u8 flash_pages_erased=0;
volatile u8 BL_wait_time_flag=0;
 u8 receve_state=0;
extern int app_apdated; //var that indicate which application is updated

/*BUTTON PINS B4 , B5*/
#define buttonA 4
#define buttonB 5

////////////////////*prototype for function*/////////////////

/*fun that select between the application you want to jump*/
void func_select_app(void);
/*fun that get the putton witch is pressed*/
int get_pressed_button(void);

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

	/*enable the uart and FPEC prephieral clock*/
	RCC_voidEnableClock(RCC_APB2,14); /* USART1 */
	RCC_voidEnableClock(RCC_AHB,4);   /* FPEC   */

	/*TFT Screen pin configuration */
	MGPIO_voidSetPinDirection(GPIOA,PIN1 ,OUTPUT_SPEED_2MHZ_PP); 	   //A0
	MGPIO_voidSetPinDirection(GPIOA,PIN2 ,OUTPUT_SPEED_2MHZ_PP);	  //RST
	MGPIO_voidSetPinDirection(GPIOA,PIN5 ,OUTPUT_SPEED_10MHZ_AFPP);	  //CLK
	MGPIO_voidSetPinDirection(GPIOA,PIN7 ,OUTPUT_SPEED_10MHZ_AFPP);	  //MOSI

	/*USART pin configuration*/
	MGPIO_voidSetPinDirection(GPIOA,9,0b1010);   /* TX AFPP */
	MGPIO_voidSetPinDirection(GPIOA,10,INPUT_FLOAT);  /* Rx Input Floating */

	/*Configuar  witches pins as pullup  */
	MGPIO_voidSetPinDirection(GPIOB,4,INPUT_PULL_UP_DOWEN);  /* B4 Input pullup */
	MGPIO_voidSetPinValue(GPIOB,4,PULLUP_SELECT);
	MGPIO_voidSetPinDirection(GPIOB,5,INPUT_PULL_UP_DOWEN);  /* B5 Input pullup */
	MGPIO_voidSetPinValue(GPIOB,5,PULLUP_SELECT);
	MUSART1_voidInit();/*baud rate 9600 -enable RX,TX*/

	/* Init STK */
	MSTK_voidInit();

	/* SPI Init */
	MSPI1_voidInit();
	
	/* TFT Init */
	HTFT_voidInitialize();
	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(0,5, "  Boot Loader ", Font_11x18, RED , BLACK);
	ST7735_WriteString(0,40, "wait update..", Font_11x18, MAGENTA , BLACK);
	/*wait for 25 sec for recieving any new updates for one of two application */
	MSTK_voidSetIntervalSec(25,func_select_app);

	while(BL_wait_time_flag == 0)
	{
		receve_state = MUSART1_u8Receive( &(recieving_record[char_count]) );  //recieve at buffer until end of record
		if (receve_state == 1)
		{
			MSTK_voidStopInterval();
			if(recieving_record[char_count] == '\n') //end of record
			{
				/*check on the second record that contain the base address of the application you want to update*/
				if (flash_pages_erased == 0 && recieving_record[8]=='0' )
				{
					FPEC_voidEraseAppArea(recieving_record);
					flash_pages_erased = 1;
				}
				/* Parse the recieved record */
				Parser_voidParseRecord(recieving_record);
				MUSART1_voidTransmit("ok");
				char_count = 0;
			}
			else
			{
				char_count ++ ;
			}
			/*after recieve a record and flashing it set the timer interval again */
			MSTK_voidSetIntervalSingle(12000000,func_select_app);
		}
		else
		{
		}
	}
}

int get_pressed_button(void)
{
	int local_buttonA=1;
	int local_buttonB=1;
	while((local_buttonA && local_buttonB)==1)
	{
		local_buttonA=MGPIO_u8GetPinValue(GPIOB,buttonA);
		local_buttonB=MGPIO_u8GetPinValue(GPIOB,buttonB);
		MSTK_voidSetBusyWait(4000000);
	}
	if(local_buttonA==0)
	{
		return 1;
	}
	else if(local_buttonB==0)
	{
		return 2;
	}
}

void func_select_app(void)
{
	HTFT_voidDrawRect(0,160,25,50,BLACK);
	switch(app_apdated)
	{
	case 0:
		ST7735_WriteString(0,40, "NO APP UPDATED ", Font_11x18, CYAN, BLACK);
		break;
	case 1:
		ST7735_WriteString(0,40, "APP 1 UPDATED ", Font_11x18, CYAN , BLACK);
		break;
	case 2:
		ST7735_WriteString(0,40, "APP 2 UPDATED ", Font_11x18, CYAN , BLACK);
		break;

	}
	MSTK_voidStopInterval();
	MSTK_voidSetBusyWait(4000000);
	MSTK_voidSetBusyWait(4000000);
	MSTK_voidSetBusyWait(4000000);
		HTFT_voidDrawRect(0,160,25,50,BLACK);
	ST7735_WriteString(0,25, "Select APP ", Font_11x18, GREEN , BLACK);
	ST7735_WriteString(0,50, " 1:APP1       ", Font_11x18,GREEN , BLACK);
	ST7735_WriteString(0,75, " 2:APP2       ", Font_11x18,GREEN , BLACK);
	int app_number=get_pressed_button();
	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	if(app_number==1)
	{
		ST7735_WriteString(0,30, "APP1 will run", Font_11x18,CYAN , BLACK);
		MSTK_voidSetBusyWait(5000000);
		SCB_VTOR = 0x08003C00;
		address_of_selective_app = *((adress_to_loc_t *)0x08003C04);
		address_of_selective_app();
	}
	else if(app_number==2)
	{
		ST7735_WriteString(0,30, "APP2 will run", Font_11x18,CYAN , BLACK);
		MSTK_voidSetBusyWait(5000000);
		SCB_VTOR = 0x08008C00;
		address_of_selective_app = *((adress_to_loc_t *)0x08008C00);
		address_of_selective_app();
	}

}
