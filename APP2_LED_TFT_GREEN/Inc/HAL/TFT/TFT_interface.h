
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H
#include "fonts.h"

void HTFT_voidInitialize   (void);

void HTFT_voidDisplayImage (const u16* Copy_Image);
void HTFT_voidFillColor (u16 Copy_u16Color);
void HTFT_voidDrawRect(u8 x1 ,u8 x2 ,u8 y1 ,u8 y2 ,u16 Copy_u16Color);
void ST7735_WriteChar(u16 x, u16 y, char ch, FontDef font, u16 color, u16 bgcolor);
void ST7735_WriteString(u16 x, u16 y, const char* str, FontDef font, u16 color, u16 bgcolor);
void ST7735_Reset(void);

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


//#define _width 128
//#define _height 160

#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160

#define DELAY 0x80

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04

#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    u16 t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }

void drawPixel(u16 x, u16 y, u16 color);
void writePixel(u16 x, u16 y, u16 color);
void writeLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 color);
void  drawFastVLine(u16 x, u16 y, u16 h, u16 color);
void  drawFastHLine(u16 x, u16 y, u16 w, u16 color);
void drawRect(u16 x, u16 y, u16 w, u16 h, u16 color);
void ST7735_Reset(void);
void ST7735_SetRotation(u8 m);
void ST7735_WriteChar(u16 x, u16 y, char ch, FontDef font, u16 color, u16 bgcolor);

#endif
