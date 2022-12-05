#pragma once


#define ENABLE_TESTR 1

#define TFT_ENABLE_FONTS 1
#define TFT_ENABLE_ALL 1
#define TFT_ENABLE_ROTATE 1

#define LCD_CS 17
#define LCD_DC 14
#define LCD_RES 15
#define LCD_SDA 19
#define LCD_MISO 16
#define LCD_SCL 18
#define LCD BL 0

// Refresh Speed of the LCD
#define MHZ 1000000
#define LCD_CLK_SPD  (60 * MHZ) //1Mhz
#define LCD_SPI_PORT spi0

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "lib-st7735/include/ST7735_TFT.h"
#include "lib-st7735/include/hw.h"

extern bool m_initFailed;
//Init the LCD
extern uint16_t * _buffer;
extern bool lcdInit();
extern void lcdUpdate(uint64_t u);
 