/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 23 OCT 2023     ****************/
/********** version     : V 01			  ****************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"
#include "../Inc/MCAL/SYSTICK/STK_interface.h"

#include "../Inc/HAL/TFT/TFT_interface.h"
#include "../Inc/HAL/TFT/TFT_private.h"
#include "../Inc/HAL/TFT/TFT_config.h"
#include "../Inc/HAL/TFT/fonts.h"



u16 _width=128;       ///< Display width as modified by current rotation
u16 _height=160;      ///< Display height as modified by current rotation
u16  cursor_x;     ///< x location to start print()ing text
u16 cursor_y;     ///< y location to start print()ing text
u8 rotation;     ///< Display rotation (0 thru 3)
u8 _colstart;   ///< Some displays need this changed to offset
u8 _rowstart;       ///< Some displays need this changed to offset
u8 _xstart;
u8 _ystart;
void HTFT_voidInitialize   (void)
{
	/* Reset Pulse */
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
	MSTK_voidSetBusyWait(120000);
	
	/* Sleep Out Command */
	voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	MSTK_voidSetBusyWait(150000);
	
	/* Color Mode Command */
	voidWriteCommand(0x3A);
	voidWriteData (0x05); /*RGB565 is the parameter for COlor Mode Command */
	
	/* Display On Command */
	voidWriteCommand(0x29);
}


void HTFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	
	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}
void HTFT_voidFillColor (u16 Copy_u16Color)
{
	u16 counter;
	u8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_u16Color >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_u16Color & 0x00ff;
		voidWriteData(Data);
	}
}
void HTFT_voidDrawRect(u8 x1 ,u8 x2 ,u8 y1 ,u8 y2 ,u16 Copy_u16Color)
{
	u16 size =(x2-x1) * (y2-y1);
	u16 counter;
	u8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(x1);
	voidWriteData(0);
	voidWriteData(x2);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(y1);
	voidWriteData(0);
	voidWriteData(y2);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< size ;counter++)
	{
		Data = Copy_u16Color >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_u16Color & 0x00ff;
		voidWriteData(Data);
	}
}
void voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Temp; /* this var has no effect as MISO pin not connected */
	
	/* Set A0 Pin to Low */
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_LOW);
	
	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Command,&Local_u8Temp);
	
}

void voidWriteData   (u8 Copy_u8Data)
{
	u8 Local_u8Temp;
	
	/* Set A0 Pin to High */
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_HIGH);
	
	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch(Copy_u8Data,&Local_u8Temp);	
}
void ST7735_Reset(void)
{
	/* Reset Pulse */
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN,GPIO_HIGH);
}

void ST7735_SetAddressWindow(u8 x0, u8 y0, u8 x1, u8 y1)
{
	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(x0);
	voidWriteData(0);
	voidWriteData(x1);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(y0);
	voidWriteData(0);
	voidWriteData(y1);
	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);
}
void ST7735_WriteChar(u16 x, u16 y, char ch, FontDef font, u16 color, u16 bgcolor) {
    u32 i, b, j;

    ST7735_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                u8 data[] = { color >> 8, color & 0xFF };
                for(u8 i=0;i<sizeof(data);i++)
                {
                	voidWriteData(data[i]);
                }
               // ST7735_WriteData(data, sizeof(data));
            } else {
                u8 data[] = { bgcolor >> 8, bgcolor & 0xFF };
                for(u8 i=0;i<sizeof(data);i++)
                {
                	voidWriteData(data[i]);
                }
                //ST7735_WriteData(data, sizeof(data));
            }
        }
    }
}

void ST7735_WriteString(u16 x, u16 y, const char* str, FontDef font, u16 color, u16 bgcolor) {
    while(*str) {
        if(x + font.width >= _width) {
            x = 0;
            y += font.height;
            if(y + font.height >= _height) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        ST7735_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

}

void drawPixel(u16 x, u16 y, u16 color) {
    if((x >= _width) || (y >= _height))
        return;
    ST7735_SetAddressWindow(x, y, x+1, y+1);
    u8 data[] = { color >> 8, color & 0xFF };
    for(u8 i=0;i<sizeof(data);i++)
    {
    	voidWriteData(data[i]);
    }
}

void writePixel(u16 x, u16 y, u16 color)
{
    drawPixel(x, y, color);
}

void writeLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 color)
{
    u16 steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    u16 dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    u16 err = dx / 2;
    u16 ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            writePixel(y0, x0, color);
        } else {
            writePixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void  drawFastVLine(u16 x, u16 y, u16 h, u16 color)
{
	writeLine(x, y, x, y + h - 1, color);
}
void  drawFastHLine(u16 x, u16 y, u16 w, u16 color)
{
	writeLine(x, y, x + w - 1, y, color);
}
void drawRect(u16 x, u16 y, u16 w, u16 h, u16 color)
{
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y+h-1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x+w-1, y, h, color);
}

void ST7735_SetRotation(u8 m)
{

  u8 madctl = 0;

  rotation = m % 4; // can't be higher than 3

  switch (rotation)
  {
  case 0:
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
      _xstart = _colstart;
      _ystart = _rowstart;
    break;
  case 1:
      madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
    break;
  case 2:
      madctl = ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
    _xstart = _colstart;
    _ystart = _rowstart;
    break;
  case 3:
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
    break;
  }
  voidWriteCommand(0x36);//ST7735_MADCTL
//  ST7735_WriteData(&madctl,1);
	voidWriteData(madctl);

}


