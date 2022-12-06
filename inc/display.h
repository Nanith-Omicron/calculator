 
#define ENABLE_TESTR 1
#define BUFFER_SIZE 20480
#define TFT_ENABLE_FONTS 1
#define TFT_ENABLE_ALL 1
#define TFT_ENABLE_ROTATE 1
#define TFT_HEIGHT 128
#define TFT_WIDTH 160
#define LCD_CS 17
#define LCD_DC 14
#define LCD_RES 15
#define LCD_SDA 19
#define LCD_MISO 16
#define LCD_SCL 18
#define LCD BL 0

// Refresh Speed of the LCD
#define MHZ 1000000
#define LCD_CLK_SPD (60 * MHZ) // 1Mhz
#define LCD_SPI_PORT spi0

#include <stdio.h>
#include <stdlib.h>

#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include "lib-st7735/include/ST7735_TFT.h"
#include "lib-st7735/include/hw.h"
 

extern bool m_initFailed;
extern bool m_textWrap;

extern uint8_t *m_buffer1;

extern bool lcdInit();
extern void buffer_setPixel(int x, int y, uint16_t col);
extern void buffer_drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color);
extern void buffer_drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color);
extern void buffer_setTextWrap(bool w);
extern void buffer_drawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size);
extern void buffer_drawText(uint8_t x, uint8_t y, const char *_text, uint16_t color, uint16_t bg, uint8_t size);
extern void buffer_fillBuffer(uint16_t color);

extern void lcdUpdate(uint64_t u);
extern void updateBuffer();
